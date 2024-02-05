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
void Insert(ordered_set &s,ll x){ //this function inserts one more occurrence of (x) into the set.
    s.insert(x);
}
bool Exist(ordered_set &s,ll x){ //this function checks weather the value (x) exists in the set or not.
     if((s.upper_bound(x))==s.end()){
        return 0;
     }
     return ((*s.upper_bound(x))==x);
}
void Erase(ordered_set &s,ll x){ //this function erases one occurrence of the value (x).
     if(Exist(s,x)){
        s.erase(s.upper_bound(x));
     }
}
ll FirstIdx(ordered_set &s,ll x){ //this function returns the first index of the value (x)..(0 indexing).
    if(!Exist(s,x)){
        return -1;
    }
    return (s.order_of_key(x));
}
ll Value(ordered_set &s,ll idx){ //this function returns the value at the index (idx)..(0 indexing).
   return (*s.find_by_order(idx));
}
ll LastIdx(ordered_set &s,ll x){ //this function returns the last index of the value (x)..(0 indexing).
    if(!Exist(s,x)){
        return -1;
    }
    if(Value(s,(int)s.size()-1)==x){
        return (int)(s.size())-1;
    }
    return FirstIdx(s,*s.lower_bound(x))-1;
}
ll Count(ordered_set &s,ll x){ //this function returns the number of occurrences of the value (x).
     if(!Exist(s,x)){
        return 0;
     }
     return LastIdx(s,x)-FirstIdx(s,x)+1;
}
void Clear(ordered_set &s){ //this function clears all the elements from the set.
     s.clear();
}
ll Size(ordered_set &s){ //this function returns the size of the set.
     return (ll)(s.size());
}



