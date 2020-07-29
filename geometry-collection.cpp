// Geometry collection
// uncompleted
#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 123;
const int oo = 1e9 + 123;
const long long mod = 1e9 + 7;
const double eps = 1e-9;
const double PI = acos(-1);

typedef pair<int,int> pi;
#define mp make_pair
#define getSz(x) ((x).size())
#define SetLength2(a, n, t) a=((t*) calloc(n, sizeof(t))) + (n)/2

int n,m;

double DEG_TO_RAD(double x){
    return x * M_PI/180;
}
double RAD_TO_DEG(double x){
    return x * 180/M_PI;
}

int cmp(double x,double y){
    if(fabs(x - y) < eps) return 0;
    return x < y ? -1 : 1;
}


// point & vector

struct Point{
    double x,y;
    Point(){ x = y = 0.0;}
    Point(double _x,double _y) : x(_x),y(_y){}

    bool operator == (Point other) const {
        return fabs(x - other.x) < eps && fabs(y - other.y) < eps;
    }
    bool operator < (Point other) const{
        return fabs(x - other.x) > eps ? x < other.x : y < other.y;
    }
    Point operator - (Point other){
        return Point(x - other.x,y - other.y);
    }
    Point operator * (double u){
        return Point(x * u,y * u);
    }
    double norm(){
        return x * x + y * y;
    }
    Point conj(){
        return Point(x,-y);
    }
    double operator % (Point other){ // cross product
        return x * other.y - y * other.x;
    }
    double operator * (Point other){ // dot product
        return x * other.x + y * other.y;
    }
    double length(){
        return hypot(x,y); // sqrt(norm())
    }
    Point rotate(double theta){ // to the left
        double rad = DEG_TO_RAD(theta);
        cout << " ok " << theta <<" degrees => " << rad << " radian" << " / " << sin(rad) << " / " << cos(rad) << endl;
        cout << "rotating " << x <<","<<y<< " ~> " << rad << " radian" << endl;
        Point A(x * cos(rad) - y * sin(rad),x * sin(rad) + y * cos(rad));
        cout << " ~> " << A.x<<","<<A.y<< endl;

        return A;
    }
    Point(Point A,Point B){
        x = B.x - A.x; y = B.y - A.y;
    }
};

typedef Point MathVector;
typedef Point vec;

double dist(Point a,Point b){
    return (b - a).length();
}
Point translate(Point a,vec u){
    return Point(a.x + u.x,a.y + u.y);
}
// line

struct line{
    // ax + by + c = 0
    double a,b,c; // if the line is vertical => b = 0, otherwise b = 1
    line(){ a = 1; b = c = 0; }
    line(double _a,double _b,double _c) : a(_a),b(_b),c(_c){}
    line(Point A,Point B){
        if(fabs(A.x - B.x) < eps){
            a = 1;
            b = 0;
            c = -A.x;
        }else{
            Point n(B.y - A.y,A.x - B.x);
            a = n.x; b = n.y;
            c = -a * A.x - b*A.y;
            //
            return ;
            a /= b;
            c /= b;
            b /= b;
        }
    }
    double val(Point A){
        return a * A.x + b * A.y + c;
    }
};
bool areParallel(const line &l1,const line &l2){
    return fabs(l1.a - l2.a) < eps && fabs(l1.b - l2.b) < eps;
}
bool areSame(const line &l1,const line &l2){
    return fabs(l1.a - l2.a) < eps && fabs(l1.b - l2.b) < eps && fabs(l1.c - l2.c) < eps;
}
bool areIntersect(const line &l1,const line &l2,Point &p){
    if(areParallel(l1,l2)) return false;
    p.x = (l1.c * l2.b - l2.c * l1.b) / (l2.a * l1.b - l1.a * l2.b);
    if(cmp(l1.b,0) == 0) p.y = -l2.a * p.x - l2.c;
    else p.y = -l1.a * p.x - l1.c;
    return true;
}
double distToLine(Point p,Point a,Point b,Point &c){ // a should be different from b, unless this function will fail
    // calculate distance from point p to line ab, c is the projection of p on line ab
    // vector(a,c) = u x vector (a,b)
    // now the goal is to find the point C, and to avoid using sqrt function, so it would be more precise
    double u = vec(a,p) * vec(a,b)/vec(a,b).norm();
    c = translate(a,(b - a) * u);
    return (p - c).length();
}
bool collinear(Point A,Point B,Point C){
    return cmp(vec(A,B) % vec(A,C),0) == 0;
}
bool ccw(Point A,Point B,Point C){ // A -> B -> C
    return cmp(vec(A,B) * vec(A,C),0) > 0;
}
double distToLineSegment(Point p,Point a,Point b,Point &c){
    if(a == b){
        c = a;
        return (p - a).length();
    }
    double u = vec(a,p) * vec(a,b) / vec(a,b).norm();
    if(u < 0.0){
        c = a;
        return (p - a).length();
    }else if(u > 1.0){
        c = b;
        return (p - b).length();
    }
    return distToLine(p,a,b,c);
}
double angle(Point a,Point o,Point b){ // return angle AOB in rad
    vec u(o,a),v(o,b);
    return acos((u * v) / sqrt(u.norm() * v.norm()));
}
double directedAngle(Point a,Point o,Point b){ // return directed angle from vector OA to OB
    double rr = angle(A,O,B);
    return ccw(A,O,B) ? -rr : rr; // it's impossible to use cross product because sin(x) = sin(180 - x) so it's too dangerous
}
// circle
// pi = acos(-1.0) or pi = 2 * acos(0.0)
int insideCircle(Point p,Point i,Point r){
    // compare dist(pi)^2 to r^2
    double d = (p-i).norm();
    int rr = cmp(d,r*r);
    return rr == 0 ? 1 : (rr == 1 ? 2 : 0);
    // 0 1 2 => inside/border/outside
}
// compute the length of chord given r and alpha : len = 2 * r * sin(alpha/2)

// Polygon

bool isConvex(const vector<Point> &P){
    int sz = P.size();
    if(sz <= 2) return false;
    bool isLeft = ccw(P[0],P[1],P[2]); // it's important to check if there are any 3 consecutive vertices which are collinear
    for(int i = 1; i < P.size(); ++i){
        if(ccw(P[i],P[(i + 1) % sz],P[(i + 2) % sz]) != isLeft) return false;
    }
    return true;
}
bool isInsidePolygon(vector <Point> &Q,Point p){ // the last point is different from the first point
    // my own version
    double total = 0;
    for(int i = 0; i < Q.size(); ++i){
        int j = (i + 1) % (int)Q.size();
        if(collinear(Q[i],Q[j],p) && p.x >= min(Q[i].x,Q[j].x) && p.x <= max(Q[i].x,Q[j].x)){
            return 1;
        }
        total += directedAngle(Q[i],p,Q[j]);
    }
    return cmp(fabs(total),PI * 2) == 0;
}

void buildConvexHull(vector <Point> &Q){// the last point must be different from the first point
    sort(Q.begin(),Q.end());
    vector <Point> convex;
    for(int i = 0; i < Q.size(); ++i){
        while(convex.size() > 1 && !ccw(Q[i],convex.back(),convex[convex.size() - 2])) convex.pop_back();
        convex.push_back(Q[i]);
    }
    int t = convex.size();
    for(int i = Q.size() - 2; i >= 0; --i){
        while(convex.size() > t && !ccw(Q[i],convex.back(),convex[convex.size() - 2])) convex.pop_back();
        convex.push_back(Q[i]);
    }
    Q = convex; // now Q.first() = Q.back()
    Q.pop_back();
}

vector <Point> cutPolygon(Point A,Point B,const vector <Point> &Q){
    vector <Point> P;

    for(int i = 0; i < Q.size(); ++i){
        int j = (i + 1) % (int)Q.size();
        double left = ccw(A,B,Q[i]),right = ccw(A,B,Q[j]);
        if(cmp(left,0) == 1) P.push_back(Q[i]);
        if(cmp(left,0) * cmp(right,0) < 0){
            Point p1;
            if(areIntersect(line(A,B),line(Q[i],Q[j]),p1)) P.push_back(p1);
        }
    }

    // if(P.size() && !(P.first() == P.back())) P.push_back(P.first());
    return P;
}
void testcase(){
    cout << setprecision(9) << fixed << endl;
    Point A(23,34);
    Point B(83,19);
    line ll(A,B);

    cout << ll.a<<"x + "<<ll.b<<"y + " << ll.c << " = " << 0 << endl;

    cout << "okay " << ll.val(A) << " " << ll.val(B) << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    #ifndef ONLINE_JUDGE
        freopen("a.inp","r",stdin);
        freopen("a.out","w",stdout);
    #else
        // online submission
    #endif

    // main program here

    int tcase = 1;
    //cin >> tcase;

    for(int i = 1; i <= tcase; ++i) testcase();

    // 

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    
    return 0;
}
