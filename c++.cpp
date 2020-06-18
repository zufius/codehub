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





