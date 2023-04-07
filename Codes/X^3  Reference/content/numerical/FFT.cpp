#pragma once

typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
	int n = a.size(), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		for(int i = k; i < 2*k; i++)
			rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vector<int> rev(n);
	for(int i = 0; i < n; i++)
		rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	for(int i = 0; i < n; i++)
		if (i < rev[i])
			swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k)
			for(int j = 0; j < k; j++) {
			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}
vector<double> conv(const vector<double>& a, const vector<double>& b) {
	if (a.empty() || b.empty()) return {};
	vector<double> res((int)a.size() + (int)b.size() - 1);
	int L = 32 - __builtin_clz(res.size()), n = 1 << L;
	vector<C> in(n), out(n);
	copy(all(a), begin(in));
	for(int i = 0; i < (int)b.size(); i++)
		in[i].imag(b[i]);
	fft(in);
	for (C& x : in) x *= x;
	for(int i = 0; i < n; i++)
		out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	for(int i = 0; i < (int)res.size(); i++)
		res[i] = imag(out[i]) / (4 * n);
	return res;
}
