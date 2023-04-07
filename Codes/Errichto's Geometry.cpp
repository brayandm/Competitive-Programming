/// Geometry

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ii pair <int,int>
#define F first
#define S second
#define ever (;;)

int T;

long double pi = 3.1415926535897932384626433;

struct point
{
    ll x,y;

    void read() { scanf("%lld%lld",&x,&y); }

    point operator + ( point p ) { return point { x+p.x , y+p.y }; }
    void operator += ( point p ) { x += p.x; y += p.y; }
    point operator - ( point p ) { return point { x-p.x , y-p.y }; }
    void operator -= ( point p ) { x -= p.x; y -= p.y; }

    ll operator * ( point p ) const { return x*p.y - p.x*y; }

    ll triangle (point p1,point p2) { return (p1-*this)*(p2-*this); }

    /// 0 same, 1 p1 and 2 p2
    int moreOnTheLeft ( point p1 , point p2 )
    {
        ll res = (p1-*this)*(p2-*this);

        if( res == 0 )
            return 0;
        if( res < 0 )
            return 1;
        return 2;
    }
};

struct pointDouble
{
    long double x,y;

    void read() { cin>>x>>y; }

    pointDouble operator + ( pointDouble p ) { return pointDouble { x+p.x , y+p.y }; }
    void operator += ( pointDouble p ) { x += p.x; y += p.y; }
    pointDouble operator - ( pointDouble p ) { return pointDouble { x-p.x , y-p.y }; }
    void operator -= ( pointDouble p ) { x -= p.x; y -= p.y; }

    long double operator * ( pointDouble p ) const { return x*p.y - p.x*y; }

    /// 0 same, 1 p1 and 2 p2
    int moreOnTheLeft ( pointDouble p1 , pointDouble p2 )
    {
        long double res = (p1-*this)*(p2-*this);

        if( res == 0 )
            return 0;
        if( res < 0 )
            return 1;
        return 2;
    }

    pointDouble rotateAboutRadian( pointDouble center , long double theta )
    {
        pointDouble ret = (*this);

        ret -= center;

        long double x = ret.x;
        long double y = ret.y;

        long double r = sqrt(x*x+y*y);

        long double t = acos(x/r);

        if( y < 0 )
            t = -t;

        t += theta;

        x = r * cos(t);
        y = r * sin(t);

        x += center.x;
        y += center.y;

        ret.x = x;
        ret.y = y;

        return ret;
    }

    long double angleDegree(pointDouble p1,pointDouble p2)
    {
        p1 -= (*this);
        p2 -= (*this);

        long double r1 = sqrt(p1.x*p1.x+p1.y*p1.y);
        long double t1 = acos(p1.x/r1);
        if( p1.y < 0 )
            t1 = -t1;

        long double r2 = sqrt(p2.x*p2.x+p2.y*p2.y);
        long double t2 = acos(p2.x/r2);
        if( p2.y < 0 )
            t2 = -t2;

        long double ret = t1-t2;

        ret = 180.0*ret/pi;

        return ret;
    }

    long double angleRadian(pointDouble p1,pointDouble p2)
    {
        p1 -= (*this);
        p2 -= (*this);

        long double r1 = sqrt(p1.x*p1.x+p1.y*p1.y);
        long double t1 = acos(p1.x/r1);
        if( p1.y < 0 )
            t1 = -t1;

        long double r2 = sqrt(p2.x*p2.x+p2.y*p2.y);
        long double t2 = acos(p2.x/r2);
        if( p2.y < 0 )
            t2 = -t2;

        long double ret = t1-t2;

        return ret;
    }

    long double dist(pointDouble p1) { pointDouble p2 = (*this); return sqrt( (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) ); }

    pointDouble reflectFromLine(pointDouble p1,pointDouble p2)
    {
        long double t = p1.angleRadian(p2,*(this));

        pointDouble newp2 = p2.rotateAboutRadian(p1,t);

        long double rtot = newp2.dist(p1);

        long double r = (*this).dist(p1);

        pointDouble ret;

        newp2 -= p1;

        ret.x = newp2.x*r/rtot;
        ret.y = newp2.y*r/rtot;

        ret += p1;

        return ret;
    }

    long double distFromLine(pointDouble p1,pointDouble p2)
    {
        pointDouble reflect = (*this).reflectFromLine(p1,p2);

        return reflect.dist((*this))/2.0;
    }

    pointDouble moveTowards(pointDouble p1,double d)
    {
        pointDouble p = (*this);

        long double rtot = p.dist(p1);

        long double r = d;

        p1 -= p;

        pointDouble ret;

        ret.x = p1.x*r/rtot;
        ret.y = p1.y*r/rtot;

        ret += p;

        return ret;
    }
};

ll polygonAreaTimes2(vector <point> &v)
{
    int sz = (int)(v.size());
    ll ret = 0;

    for(int i=0;i<sz-1;i++)
        ret += v[i]*v[i+1];

    ret += v[sz-1]*v[0];

    return abs(ret);
}

bool twoSegmentsIntersect(point p1,point p2,point p3,point p4)
{
    if( (p2-p1)*(p4-p3) == 0 )
    {
        if( p1.moreOnTheLeft(p2,p3) == 0 )
        {
            ll x1 = min( p1.x , p2.x );
            ll y1 = min( p1.y , p2.y );
            ll x2 = max( p1.x , p2.x );
            ll y2 = max( p1.y , p2.y );
            ll x3 = min( p3.x , p4.x );
            ll y3 = min( p3.y , p4.y );
            ll x4 = max( p3.x , p4.x );
            ll y4 = max( p3.y , p4.y );

            ll x5 = max( x1 , x3 );
            ll y5 = max( y1 , y3 );
            ll x6 = min( x2 , x4 );
            ll y6 = min( y2 , y4 );

            if( x5 > x6 || y5 > y6 )
                return 0;
            else
                return 1;
        }

        return 0;
    }

    for(int i=1;i<=2;i++)
    {
        int sign1 = p1.moreOnTheLeft(p2,p3);
        int sign2 = p1.moreOnTheLeft(p2,p4);

        if( ( sign1 == 1 && sign2 == 1 ) || ( sign1 == -1 && sign2 == -1 ) )
            return 0;

        swap(p1,p3);
        swap(p2,p4);
    }

    return 1;
}

bool pointOnSegment(point a,point b,point p)
{
    if( (a-b)*(a-p) != 0 )
        return 0;

    ll x1 = min( a.x , b.x );
    ll y1 = min( a.y , b.y );
    ll x2 = max( a.x , b.x );
    ll y2 = max( a.y , b.y );

    return ( p.x >= x1 && p.x <= x2 && p.y >= y1 && p.y <= y2 );
}

/// 0 Outside, 1 inside and 2 on boundary
int pointInsidePolygon(vector <point> &v,point p)
{
    int sz = (int)(v.size());

    for(int i=0;i<sz;i++)
        if( pointOnSegment(v[i],v[i+1==sz?0:i+1],p) )
            return 2;

    point p2 = {p.x+1,1000000001LL};
    int cnt = 0;
    for(int i=0;i<sz;i++)
        cnt += twoSegmentsIntersect(p,p2,v[i],v[i+1==sz?0:i+1]);

    return cnt%2;
}

ll latticePointsOnBoundaryOfPolygon(vector <point> &v)
{
    int sz = (int)(v.size());
    ll ret = 0;
    for(int i=0;i<sz;i++)
    {
        point p1 = v[i];
        point p2 = v[i+1==sz?0:i+1];

        ll diffx = abs(p1.x-p2.x);
        ll diffy = abs(p1.y-p2.y);

        ll g = __gcd(diffx,diffy);

        ret += g;
    }

    return ret;
}

ll latticePointsInsidePolygon(vector <point> &v)
{
    ll area = polygonAreaTimes2(v);
    ll boundary = latticePointsOnBoundaryOfPolygon(v);

    return (area-boundary+2)/2;
}

int main()
{

}
