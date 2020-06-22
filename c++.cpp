g++ -std=c++11 a.cpp -o a

////

#include <cmath>

M_PI

cos sin acos asin => rad

hypot(x,y) = sqrt(x^2 + y^2) => hypotenuse
// => float/double/long double <=> depending on the data type of x & y

atan2 = atan(y/x) = alpha (rad) => y = D,x = K

Point{
    x,y;
    
    conjugate = {x,-y};
    norm = {x^2 + y^2}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

{
   ::function_name(); // => call the function which named function_name outside the current block
}

#define x(i) ...
#undef x

#include <tuple>

tuple <int,int,string,...> SS(-1,3,"abc",...);
make_tuple(-1,3,"abc")

std::tie(a,b,c) = SS; /// tuple variable

std::get<0> (SS); // => -1
std::get<2> (SS); // => "abc"

auto x = SS;

for(auto x : map_var){
  cout << x.first << " " << x.second;
}

auto r = equal_range(a.begin(),a.end(),x); 
// r.first = lower_bound
// r.second = upper_bound


priority_queue <int,vector<int>,greater<int>> heap; // => min 

next_permutation(S.begin(),S.end()); // => true/false

//

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
//#include <functional> // for less 

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> indexed_tree;

indexed_set s;
s.insert(2);
auto x = s.find_by_order(2);
cout << s.order_of_key(6) << "\n"; // 2

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

signed main() {
    ordered_set d;
    d.insert(0);
    d.insert(1);
    d.erase(d.lower_bound(0));
    for (auto i: d) {
        cout << i << ' ';
    }
}

// 
set <int> SS;

SS.insert(vector_name.begin(),vector_name.end());

//

