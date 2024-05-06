#include <bits/stdc++.h>
using namespace std;
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define LagaKar ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define mp make_pair
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ook order_of_key   //number of elements less than k
#define fbo find_by_order  //k th element
#define nline endl
#define YES cout<<"YES"<<nline
#define NO cout<<"NO"<<nline
#define Yes cout<<"Yes"<<nline
#define No cout<<"No"<<nline
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#define precise(ans)  cout<<fixed<<setprecision(15)<<ans
#define fo(i,n) for(ll i=0;i<n;i++)
#define Fo(i,k,n) for(ll i=k;k<n?i<n:i>n;k<n?i+=1:i-=1)
#define Tr(it, a) for(auto it = a.begin(); it != a.end(); it++)
#define Sz(x) ((ll)(x).size())
#define All(x) x.begin(), x.end()
#define Allr(x) x.rbegin(), x.rend()
#define MAX(x) *max_element(All(x))
#define MIN(x) *min_element(All(x))
#define SUM(x) accumulate(All(x), 0LL)
#define CNT(x) __builtin_popcountll(x)
//##################################################################################################################
typedef long long ll; typedef unsigned long long ull; typedef long double lld;
typedef pair<ll, ll>  pl;   typedef vector<ll>  vl;typedef vector<vl>  vvl; 
typedef vector<pl>  vpl;    template <typename T> using prq_mx  = priority_queue<T>; 
template <typename T> using prq_mn = priority_queue<T, vector<T>, greater<T>>;
//------------------------------------------------------------------------------------------------------------
template <typename T> using o_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R> using o_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using o_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
//************************************************************************************************
#define PI 3.1415926535897932384626
#define MOD 1000000007
#define MOD2 998244353
#define MOD3 1000000009
//===============================================================================================
