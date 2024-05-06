#include <bits/stdc++.h>
using namespace std;
#define LagaKar ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define mp make_pair
#define fi first
#define se second
#define precise(ans)  cout<<fixed<<setprecision(15)<<ans
#define fo(i,n) for(ll i=0;i<n;i++)
#define Fo(i,k,n) for(ll i=k;k<n?i<n:i>n;k<n?i+=1:i-=1)
#define tr(it, a) for(auto it = a.begin(); it != a.end(); it++)
#define sz(x) ((ll)(x).size())
#define all(x) x.begin(), x.end()
#define lb lower_bound
#define ub upper_bound
#define MAX(x) *max_element(all(x))
#define MIN(x) *min_element(all(x))
#define SUM(x) accumulate(all(x), 0LL)
#define CNT(x) __builtin_popcountll(x)
#define nline "\n"
#define PI 3.1415926535897932384626
#define MOD 1000000007
#define MOD1 998244353
typedef long long ll; typedef unsigned long long ull; typedef long double lld;
typedef pair<ll, ll>  pl;typedef vector<ll>  vl;typedef vector<vl>  vvl; typedef vector<pl>  vpl;
template <typename T> using prq_mx  = priority_queue<T>; 
template <typename T> using prq_mn = priority_queue<T, vector<T>, greater<T>>;
const double eps=1e-9;const ll INF=(ll)1e9;const ll inf64=2e18;const ll INF64=9e18;
#ifdef hydracody
    #include <C:\Users\Anurag Dwivedi\Desktop\cpc\debug.h>
#else
#define debug(x)
#endif
 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
 
 
 
 
/////////////////////////////////////////////////////////////////////////////////////////////////


 
void  chal(){
  




 
 
 
 
 
 
 
 
 
 
 
 
 
 
}
 
 
 
 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void main_(){
// int main(){
  LagaKar;
#ifdef hydracody
  freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout); freopen("error.txt", "w", stderr);
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