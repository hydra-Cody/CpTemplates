#include<bits/stdc++.h>
using namespace std;
// #define endl "\n"
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
ll n,m;
vl aa;
vector<set<ll>> g;
vl size;
vl val;
vl par;
vector<set<pl>> size2;
ll dfs(ll s,ll f){
  size[s]=1;
  val[s]=aa[s];
  par[s]=f;
  for(auto ch:g[s]){
    if(ch==f)continue;
    size[s]+=dfs(ch,s);
    val[s]+=val[ch];
    size2[s].insert({size[ch],ch});
  }
  return size[s];
}


void  chal(){
  cin>>n>>m;
  g.resize(n+1);
  aa.resize(n+1);
  size.resize(n+1);
  size2.resize(n+1);
  par.resize(n+1);
  val.resize(n+1);
  Fo(i,1,n+1){
    cin>>aa[i];
  }
  // debug(aa);
  fo(i,n-1){
    ll u,v;
    cin>>u>>v;
    g[u].insert(v);
    g[v].insert(u);
  }
  dfs(1,-1);
  // debug(val);
  // debug(size);
  // debug(size2);
  fo(i,m){
    ll x,y;
    cin>>x>>y;
    if(x==1){
      // cout<<y<<" ";
      cout<<val[y]<<endl;
    }else{
      if(g[y].size()<=1|| par[y]==-1){
        // cout<<-1<<endl;
        continue;
      }
      auto it=size2[y].begin();
      ll x=it->se;
      ll f=par[y];
      // cout<<x<<": "<<endl;
      // cout<<y<<" "<<x<<" "<<val[y]<<" "<<val[x]<<" ";
      g[f].erase(y);
      size2[f].erase({size[y],y});

      size[y]-=size[x];
      val[y]-=val[x];
      size[x]+=size[y];
      val[x]+=val[y];
      
      g[y].erase(x);
      size2[y].erase(it);        
      g[f].insert(x);
      size2[f].insert({size[x],x});
      par[x]=f;
      par[y]=x;
      // cout<<val[y]<<" "<<val[x]<<endl;
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