/* Suffix array + lcp O(n log n) 1-indexed with trash at 0
 * To compute SA of a vector, put -INFINITY at the end
 * and change string to vector
 * lcp[i] = lcp(s[sa[i-1]...], s[sa[i]...]) */
struct SA {
    int n;
    vector<int> sa, rank, lcp;
    SA(const string &s) :
            n(s.size() + 1), sa(n), rank(n), lcp(n) {
        vector<int> tmpSa(n), bucket(n);
        iota(sa.rbegin(), sa.rend(), 0);
        sort(next(sa.begin()), sa.end(),
             [&](int i,int j) { return s[i] < s[j]; });
        for (int i = 1, j = 0; i < n; i ++) {
            rank[sa[i]] = rank[sa[i - 1]] +
                          (i == 1 || s[sa[i - 1]] < s[sa[i]]);
            if (rank[sa[i]] != rank[sa[i - 1]])
                bucket[++j] = i;
        }
        for (int len = 1; len <= n; len += len) {
            for (int i = 0; i < n; i ++) {
                int j = sa[i] - len;
                if (j < 0) j += n;
                tmpSa[bucket[rank[j]] ++] = j;
            }
            bucket[0] = sa[tmpSa[0]] = 0;
            for (int i = 1, j = 0; i < n; i ++) {
                if (rank[tmpSa[i]] != rank[tmpSa[i - 1]] ||
                    rank[tmpSa[i] + len] != rank[tmpSa[i - 1] + len])
                    bucket[++j] = i;
                sa[tmpSa[i]] = j;
            }
            copy(sa.begin(), sa.end(), rank.begin());
            sa.swap(tmpSa);
            if (rank[sa[n - 1]] == n - 1) break;
        }
        for (int i = 0, j = rank[0], k = 0; i < n - 1; i ++, k ++) {
            while (k >= 0 && s[i] != s[sa[j - 1] + k])
                lcp[j] = k--, j = rank[sa[j] + 1];
        }
    }
};
