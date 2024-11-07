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
#define fbo find_by_order  //k th element (0 index)
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
//********************************************************************************************************************
#ifdef hydracody
    #include </home/anurag/Desktop/cpc/debug.h>
#else
#define debug(x)
#endif
//------------------------------------------------------------------------------------------------------------
const double eps=1e-9;const ll INF=(ll)1e9;const ll inf64=2e18;const ll INF64=9e18;
#define PI 3.1415926535897932384626
#define MOD 998244353
#define MOD1 1000000007
#define MOD2 1000000009
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll gcd(ll a, ll b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
ll lcm(ll a, ll b){return (a / gcd(a, b)) * b;}
ll power(ll x,ll y, ll p){if(y==0)return 1;ll res = 1;x = x % p;if (x == 0) return 0;while (y > 0){if (y & 1)res = (res*x) % p;y = y>>1;x = (x*x) % p;}return res;}
ll pinv(ll a, ll m){ return power(a, m - 2, m); }
 ll logceil(ll x){ll s=0;while(x>0){s++;x=x/2;}return s;}
ll mod_add(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
ll mod_mul(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
ll mod_sub(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}
ll mod_div(ll a, ll b, ll m) {a = a % m; b = b % m; return (mod_mul(a, pinv(b, m), m) + m) % m;}  //only for prime m
ll phin(ll n) {ll number = n; if (n % 2 == 0) {number /= 2; while (n % 2 == 0) n /= 2;} for (ll i = 3; i <= sqrt(n); i += 2) {if (n % i == 0) {while (n % i == 0)n /= i; number = (number / i * (i - 1));}} if (n > 1)number = (number / n * (n - 1)) ; return number;} //O(sqrt(N))
ll getRandomNumber(ll l, ll r) {return uniform_int_distribution<ll>(l, r)(rng);} 
void starter(ll t) {cout << "Case #" << t << ": ";}
void starter1(ll t) {cerr << "Case #" << t << ": ";}
void compress(vector<ll>& vs){sort(vs.begin(),vs.end());vs.resize(unique(vs.begin(), vs.end()) - vs.begin());}
/////////////////////////////////////////////////////////////////////////////////////////////////
// **Stay Strong,Believe in YOURSELF,Never give UP




ll dek(ll& mid,vvl& aa){
    cout<<mid<<nline;
    ll ans=0,n=Sz(aa),m=Sz(aa[0]);
    map<ll,ll> bb;
    for(ll i=0;i<=min(n-1,mid-1);i++){
    for(ll j=0;j<=min(m-1,mid-1);j++)bb[aa[i][j]]++;
    }
    for(ll i=0;i<Sz(aa);i++){
        if(i+mid<Sz(aa)){
            for(ll j=0;j<min(m,mid-1);j++){
                bb[aa[i+mid][j]]++;
            }
        }
        for(ll j=0;j<Sz(aa[0]);j++){
            if(j+mid<Sz(aa[0]))for(ll k=0;k<min(n,i+mid+1);k++)bb[aa[k][j+mid]]++;
            if((j-mid-1)>=0)for(ll k=0;k<min(n,i+mid+1);k++)bb[aa[k][j-mid-1]]--;
            ll r1 = max(0LL, i - mid);
            ll c1 = max(0LL, j - mid);
            ll r2 = min(n - 1, i + mid);
            ll c2 = min(m - 1, j + mid);
            ll n1=(r2-r1+1),m1=(c2-c1+1);
            ll t=n1*m1 ;
            ll t2=bb[aa[i][j]];
            ll ans1=t  - t2;
            cout<<i<<" "<<j<<" "<<aa[i][j]<<"["<<t<<","<<t2<<"]"<<"["<<n1<<","<<m1<<"]"<<nline;
            ans+=ans1;
        }
        for(ll k=i-mid;k<min(n,i+mid+1);k++)
        for(ll j=max(0ll,m-(2*mid+1));j<m;j++)bb[aa[k][j]]--;
    }
    cout<<ans<<nline;
    return ans;

}



 
void  chal(){
    ll n,m,k;
    cin>>n>>m>>k;
    vvl aa(n,vl(m));
    fo(i,n)fo(j,m)cin>>aa[i][j];
    ll s=1,e=max(n,m);
    ll ans=-1;
    cout<<nline;
    while(s<=e){
        ll mid=s+(e-s)/2;
        if(dek(mid,aa)>=k){
            ans=mid;
            e=mid-1;
        }else s=mid+1;
    }
    cout<<ans<<nline;


















 
 
 
 
 
 
 
 
 
 
 
 
 
 
}
 
 
 
 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void main_(){
// int main(){
  LagaKar;
#ifdef hydracody
  freopen("input.txt", "r", stdin); 
  freopen("output1.txt", "w", stdout); 
  freopen("error.txt", "w", stderr);
#endif
  ll  t; t = 1;
  cin>>t;
  for (ll i = 1; i <= t; i++) {
    // cerr<<"Case : "<<i<<endl;
    cout<<"Case #"<<i<<": ";
    chal();
  } 
  // return 0;
}
// Increase stack size
static void run_with_stack_size(void (*func)(void), size_t stsize) {
    char *stack, *send;
    stack = (char *)malloc(stsize);
    send = stack + stsize - 16;
    send = (char *)((uintptr_t)send / 16 * 16);
    asm volatile(
        "mov %%rsp, (%0)\n"
        "mov %0, %%rsp\n"
        :
        : "r"(send));
    func();
    asm volatile("mov (%0), %%rsp\n" : : "r"(send));
    free(stack);
}
int main() {
    run_with_stack_size(main_, 1024 * 1024 * 1024); // run with a 1 GiB stack
    return 0;
}