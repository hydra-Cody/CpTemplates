#include<bits/stdc++.h>
using namespace std;
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
#define PI 3.1415926535897932384626
#define MOD 1000000007
#define MOD1 998244353
typedef long long ll; typedef unsigned long long ull; typedef long double lld; typedef pair<ll, ll>  pii; typedef pair<ll, ll>    pl; typedef vector<ll> vi; typedef vector<vi> vvi; typedef vector<vvi>    vvvi; typedef vector<ll>  vl; typedef vector<vl>  vvl; typedef vector<pii> vpii; typedef vector<pl>  vpl; template <typename T> using prq_mx  = priority_queue<T>; template <typename T> using prq_mn = priority_queue<T, vector<T>, greater<T>>;
const double eps = 1e-9; const ll INF = (ll) 1e9; const ll inf64 = 2e18; const ll INF64 = 9e18;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" "; _prll(x); cerr << endl;
#else
#define debug(x)
#endif
void _prll(ll t) {cerr << t;} void _print(ll t) {cerr << t;} void _prll(string t) {cerr << t;} void _prll(char t) {cerr << t;} void _prll(lld t) {cerr << t;} void _prll(double t) {cerr << t;} void _prll(ull t) {cerr << t;} template <class T, class V> void _prll(pair <T, V> p); template <class T> void _prll(vector <T> v); template <class T> void _prll(set <T> v); template <class T, class V> void _prll(map <T, V> v); template <class T> void _prll(multiset <T> v); template <class T, class V> void _prll(pair <T, V> p) {cerr << "{"; _prll(p.fi); cerr << ","; _prll(p.se); cerr << "}";} template <class T> void _prll(vector <T> v) {cerr << "[ "; for (T i : v) {_prll(i); cerr << " ";} cerr << "]";} template <class T> void _prll(set <T> v) {cerr << "[ "; for (T i : v) {_prll(i); cerr << " ";} cerr << "]";} template <class T> void _prll(multiset <T> v) {cerr << "[ "; for (T i : v) {_prll(i); cerr << " ";} cerr << "]";} template <class T, class V> void _prll(map <T, V> v) {cerr << "[ "; for (auto i : v) {_prll(i); cerr << " ";} cerr << "]";}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ll n;
vl aa;
vl seg;
void build(ll id=1,ll l=0,ll r=n){
  if(r-l==1){
    seg[id]=aa[l];
    return;
  }
  ll mid= l+ (r-l)/2;
  build(2*id,l,mid);
  build(2*id+1,mid,r);
  seg[id]=seg[2*id]+seg[2*id+1];
}
void modify(ll pos,ll val,ll id=1,ll l=0,ll r=n){
  if(r-l==1){
    aa[pos]=val;
    seg[id]=val;
    return;
  }
  ll mid=l+(r-l)/2;
  if(pos<mid){
    modify(pos,val,2*id,l,mid);
  }else{
    modify(pos,val,2*id+1,mid,r);
  }
  seg[id]=seg[2*id]+seg[2*id+1];
}

ll query(ll x,ll y,ll id=1,ll l=0,ll r=n){
  if(l>=x && r<=y){
    return seg[id];
  }
  if(l>=y || r<=x){
    return 0;
  }
  ll mid=l+(r-l)/2;
  return query(x,y,2*id,l,mid)+query(x,y,2*id+1,mid,r);
}



void  chal(){
  ll n2,m;
  cin>>n2>>m;
  n=1;
  while(n<n2)n*=2;
  aa.resize(n,0);
  seg.resize(2*n,0);
  fo(i,n2){
    cin>>aa[i];
  }
  debug(aa);
  build();
  debug(seg);
  fo(i,m){
    ll x;
    cin>>x;
    // cout<<x<<endl;
    if(x==1){
      ll pos,val;
      cin>>pos>>val;
      modify(pos,val);
      debug(aa);
    }else{
      ll a,b;
      cin>>a>>b;
      cout<<query(a,b)<<endl;
    }
  }






}






//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int32_t main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); srand(chrono::high_resolution_clock::now().time_since_epoch().count());
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout); freopen("Error.txt", "w", stderr);
#endif
  ll  t; t = 1;
  // cin >> t;
  for (ll i = 1; i <= t; i++) {
    chal();
  } return 0;
}