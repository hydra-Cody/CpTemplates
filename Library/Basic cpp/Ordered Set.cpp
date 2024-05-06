#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007

//--------------------------------------------------------------------------
/*Ordered Set && Map*/
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ook order_of_key   //number of elements less than k
#define fbo find_by_order  //k th element
template <typename T> using o_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R> using o_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// o_set<ll> se;
// *se.fbo(0) 
// se.ook(2)

void oderedSet() {
  o_set<ll> se;
  se.insert(1);
  se.insert(2);
  cout << *se.fbo(0) << endl; //k th element
  cout << se.ook(2) << endl; //number of elements less than k
  o_map<ll, ll>mp;
  mp.insert({1, 10});
  mp.insert({2, 20});
  cout << mp.fbo(0)->second << endl; ///k th element
  cout << mp.ook(2) << endl; ///number of first elements less than k
}



//----------------------------------------------------------------------------
/*Multi Ordered Set */
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
namespace __gnu_pbds{typedef tree<ll,null_type,less_equal<ll>,
                       rb_tree_tag,tree_order_statistics_node_update> ordered_set;}
using namespace __gnu_pbds;

template <typename T> using ordered_set = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;



