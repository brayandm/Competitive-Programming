#include<bits/stdc++.h>
using namespace std;
#define db(x) cerr << #x << ": " << (x) << '\n';
#define db_v(x) cerr << #x << ": ["; for( auto i : (x) ) cerr << i << ", "; cerr << "]\n";
#define db_p(x) cerr << #x << ": " << (x).first << " " << (x).second << '\n';

typedef long long ll;

typedef ll T;
typedef complex<T> pt;
#define x real()
#define y imag()

T sq(pt t){ return t.x*t.x+t.y*t.y; }
T sign(T t){ return ( t > T(0) ) - ( t < T(0) ); }
T cross(pt a,pt b){ return ( conj(a) * b ).y; }
T dot(pt a,pt b){ return ( conj(a) * b ).x; }
//pt rot(pt a,double angle){ return a * polar(double(1), angle); }
//double angle(pt a,pt b){ return acos(clamp( dot(a,b) / abs(a) / abs(b) , -1.0 , 1.0 )); }

bool half(pt a,pt first_angle,bool counter_clockwise){
    if( counter_clockwise )
        return ( cross(first_angle,a) < 0 ) || ( cross(first_angle,a) == 0 && dot(first_angle,a) < 0 );
    else
        return ( cross(first_angle,a) > 0 ) || ( cross(first_angle,a) == 0 && dot(first_angle,a) < 0 );
}

void polar_sort(vector<pt> &a,pt origin,pt first_angle,bool counter_clockwise){
    for( auto &i : a ) i -= origin;
    sort(a.begin(),a.end(),[&](pt u,pt v){
        if( counter_clockwise )
            return make_tuple(half(u,first_angle,counter_clockwise),0,sq(u)) <
                make_tuple(half(v,first_angle,counter_clockwise),cross(u,v),sq(v));
        else
            return make_tuple(half(u,first_angle,counter_clockwise),cross(u,v),sq(u)) <
                make_tuple(half(v,first_angle,counter_clockwise),0,sq(v));
    });
    for( auto &i : a ) i += origin;
}

int main() {
    cout.setf(ios::fixed); cout.precision(10);
    cerr.setf(ios::fixed); cerr.precision(10);

    vector<pt> a = {pt(1,0),pt(0,1),pt(0,-1),pt(-1,0),pt(2,0)};
    polar_sort(a,pt(0,0),pt(1,1),false);
    db_v(a)
}
