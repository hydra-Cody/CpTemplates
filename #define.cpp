#include<bits/stdc++.h>
using namespace std;
// #include "atcoder/math.hpp"
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC optimize("O0,trapv")
#define endl "\n"
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define mp make_pair
#define fi first
#define se second
#define set_bits __builtin_popcountll
#define precise(ans)  cout<<fixed<<setprecision(15)<<ans
#define fo(i,n) for(ll i=0;i<n;i++)
#define Fo(i,k,n) for(ll i=k;k<n?i<n:i>n;k<n?i+=1:i-=1)
#define tr(it, a) for(auto it = a.begin(); it != a.end(); it++)
#define sz(x) ((ll)(x).size())
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, 0, sizeof(x))
#define yes  cout << "YES" << endl;
#define no  cout << "NO" << endl;
#define case  cout<<"Case #"<<i<<": ";
#define PI 3.1415926535897932384626
#define MOD 1000000007
#define MOD1 998244353
typedef long long ll; typedef unsigned long long ull; typedef long double lld; typedef pair<ll, ll>  pii; typedef pair<ll, ll>    pl; typedef vector<ll> vi; typedef vector<vi> vvi; typedef vector<vvi>    vvvi; typedef vector<ll>  vl; typedef vector<vl>  vvl; typedef vector<pii> vpii; typedef vector<pl>  vpl; template <typename T> using prq_mx  = priority_queue<T>; template <typename T> using prq_mn = priority_queue<T, vector<T>, greater<T>>;
const double eps = 1e-9; const ll INF = (ll) 1e9; const ll inf64 = 2e18; const ll INF64 = 9e18;
// template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template <class K, class V> using ordered_map = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" "; _prll(x); cerr << endl;
#else
#define debug(x)
#endif
void _prll(ll t) {cerr << t;} void _print(ll t) {cerr << t;} void _prll(string t) {cerr << t;} void _prll(char t) {cerr << t;} void _prll(lld t) {cerr << t;} void _prll(double t) {cerr << t;} void _prll(ull t) {cerr << t;} template <class T, class V> void _prll(pair <T, V> p); template <class T> void _prll(vector <T> v); template <class T> void _prll(set <T> v); template <class T, class V> void _prll(map <T, V> v); template <class T> void _prll(multiset <T> v); template <class T, class V> void _prll(pair <T, V> p) {cerr << "{"; _prll(p.fi); cerr << ","; _prll(p.se); cerr << "}";} template <class T> void _prll(vector <T> v) {cerr << "[ "; for (T i : v) {_prll(i); cerr << " ";} cerr << "]";} template <class T> void _prll(set <T> v) {cerr << "[ "; for (T i : v) {_prll(i); cerr << " ";} cerr << "]";} template <class T> void _prll(multiset <T> v) {cerr << "[ "; for (T i : v) {_prll(i); cerr << " ";} cerr << "]";} template <class T, class V> void _prll(map <T, V> v) {cerr << "[ "; for (auto i : v) {_prll(i); cerr << " ";} cerr << "]";}
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
 
using namespace std;
namespace __gnu_pbds{
          typedef tree<int,
                       null_type,
                       less_equal<int>,
                       rb_tree_tag,
                       tree_order_statistics_node_update> ordered_set;
}
using namespace __gnu_pbds;
 
 
 
 
 
 
void Insert(ordered_set &s,int x){ //this function inserts one more occurrence of (x) into the set.
 
     s.insert(x);
 
}
 
 
bool Exist(ordered_set &s,int x){ //this function checks weather the value (x) exists in the set or not.
 
     if((s.upper_bound(x))==s.end()){
        return 0;
     }
     return ((*s.upper_bound(x))==x);
 
}
 
 
void Erase(ordered_set &s,int x){ //this function erases one occurrence of the value (x).
 
     if(Exist(s,x)){
        s.erase(s.upper_bound(x));
     }
 
}
 
 
int FirstIdx(ordered_set &s,int x){ //this function returns the first index of the value (x)..(0 indexing).
 
    if(!Exist(s,x)){
        return -1;
    }
    return (s.order_of_key(x));
 
}
 
 
int Value(ordered_set &s,int idx){ //this function returns the value at the index (idx)..(0 indexing).
 
   return (*s.find_by_order(idx));
 
}
 
 
int LastIdx(ordered_set &s,int x){ //this function returns the last index of the value (x)..(0 indexing).
 
    if(!Exist(s,x)){
        return -1;
    }
    if(Value(s,(int)s.size()-1)==x){
        return (int)(s.size())-1;
    }
    return FirstIdx(s,*s.lower_bound(x))-1;
 
}
 
 
int Count(ordered_set &s,int x){ //this function returns the number of occurrences of the value (x).
 
     if(!Exist(s,x)){
        return 0;
     }
     return LastIdx(s,x)-FirstIdx(s,x)+1;
 
}
 
 
void Clear(ordered_set &s){ //this function clears all the elements from the set.
 
     s.clear();
 
}
 
 
int Size(ordered_set &s){ //this function returns the size of the set.
 
     return (int)(s.size());
 
}
 