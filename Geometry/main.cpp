#include <iostream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <cstring>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <complex>
#include <cmath>
#include <limits>
#include <cfloat>
#include <climits>
#include <ctime>
#include <cassert>
#include <numeric>
#include <fstream>
#include <functional>
#include <bitset>

using namespace std;

#define INF 1e10
#define EPS (1e-10)    //誤差
#define PI 3.1415926535897932384626433832795028841971
typedef complex<double> P;
 
struct star{
    P point[5];    
};
 
//実数同士の比較
bool EQ(double a, double b){
    return (abs(a - b) < EPS);
}
 
//二つのベクトルが等しいかどうか
bool EQV(P a, P b){
    return (EQ(a.real(), b.real()) && EQ(a.imag(), b.imag()));
}
 
//内積
double dot(P a, P b){
    return (a.real() * b.real() + a.imag() * b.imag());
}
 
//外積
double cross(P a, P b){
    return (a.real() * b.imag() - a.imag() * b.real());
}
 
// 点a,bを通る直線と点cとの距離
double distance_l_p(P a, P b, P c) {
  return abs(cross(b-a, c-a)) / abs(b-a);
}
 
// 点cが線分a,b上にあるかないか(3)
int is_point_on_line(P a, P b, P c) {
  // |a-c| + |c-b| <= |a-b| なら線分上
  return (abs(a-c) + abs(c-b) < abs(a-b) + EPS);
}
 
// 点a,bを端点とする線分と点cとの距離
double distance_ls_p(P a, P b, P c) {
  if ( dot(b-a, c-a) < EPS ) return abs(c-a);
  if ( dot(a-b, c-b) < EPS ) return abs(c-b);
  return abs(cross(b-a, c-a)) / abs(b-a);
}

//図を思い出す
int ccw(P a, P b, P c) {
    b -= a; c -= a;
    if( cross(b,c) > EPS ) return +1;
    if( cross(b,c) < -EPS ) return -1;
    if( dot(b,c) < 0 ) return +2;
    if( norm(b) < norm(c) ) return -2;
    return 0;
}
 
// a1,a2を端点とする線分とb1,b2を端点とする線分の交差判定
int is_intersected_ls(P a1, P a2, P b1, P b2) {
  return ( ccw(a1,a2,b1) * ccw(a1,a2,b2) <= 0 ) &&
           ( ccw(b1,b2,a1) * ccw(b1,b2,a2) <= 0 );
}
 
// a1,a2を通る直線とb1,b2を通る直線の交点計算
P intersection_l(P a1, P a2, P b1, P b2) {
  P a = a2 - a1; P b = b2 - b1;
  return a1 + a * cross(b, b1-a1) / cross(b, a);
}


// 点a1,a2を短点とする線分と、点b1,b2を端点とする線分との距離
double distance_ls_ls(P a1, P a2, P b1, P b2){
    if(is_intersected_ls(a1, a2, b1, b2)) return 0.0;
    double ret = INF;
    ret = min(ret, distance_ls_p(a1, a2, b1));
    ret = min(ret, distance_ls_p(a1, a2, b2));
    ret = min(ret, distance_ls_p(b1, b2, a1));
    ret = min(ret, distance_ls_p(b1, b2, a2));
    return ret;
}
 


signed main(){
    return 0;
}
