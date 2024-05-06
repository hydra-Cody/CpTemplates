#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007

//---------------------------------------------------------------------------------
/*seive with lookup table nlog(log(n))*/
const ll max_N=1e5+10;
vector<bool> prime(max_N, true);
void primesieve(){
    prime[0] = false;
    prime[1] = false;
    for (ll i = 2; i * i <max_N; i++)
    {
        if (prime[i] == true)
        {
            for (int j = i * i; j < max_N; j = j + i)
            {
                prime[j] = false;
            }
        }
    }
}
vector<ll> aa;
void primesieve2(){
    for(ll i=2;i<max_N;i++){
      if(prime[i]){
        aa.push_back(i);
      }
    }
}









// *********************Less Used*******************************************

//--------------------------------------------------------------------------
/*gcdextende  for eqation of type ax+by=gcd(a,b) with Bezout coefficients(x,y)=(x*+k*(b/gcd(a,b)),y*–k*(a/gcd(a,b)))*/ 
ll gcdExtended(ll a, ll b, ll *x, ll *y){
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }
    ll x1, y1;
    ll gcd = gcdExtended(b%a, a, &x1, &y1);
    *x = y1 - (b/a) * x1;
    *y = x1;
    return gcd;
}

//----------------------------------------------------------------------------------------
/*Check Number is prime or not in sqrt(n)*/
bool isprime(ll n){
    ll i;
    if(n<=1) return false;
    if(n==2) return true;
    if(n%2==0) return false;
    for(i=3;i*i<=n;i+=2)
        if(n%i==0) return false;
    return true;
}
//-----------------------------------------------------------------------------------
/*coprime test*/
bool isCoprime(ll a,ll b){
    if(((a|b)&1)==0){
        return 0;
    }
    return __gcd(a,b)==1;
}
//--------------------------------------------------------------------------------------
/*segmentedSieve for prime number till 1e9 in sqrt(n) of tc and mc*/
vector<ll> pans;
void simpleSieve(ll limit, vector<ll> &prime)
{
    vector<bool> mark(limit + 1, true);
    for (ll p=2; p*p<limit; p++)
    {
        if (mark[p] == true)
        {
            for (ll i=p*p; i<limit; i+=p)
                mark[i] = false;
        }
    }
     for (ll p=2; p<limit; p++)
    {
        if (mark[p] == true)
        {
            prime.push_back(p);
            // cout << p << " ";
            pans.push_back(p);
        }
    }
}
void segmentedSieve(ll n)
{
    ll limit = floor(sqrt(n))+1;
    vector<ll> prime;
    prime.reserve(limit);
    simpleSieve(limit, prime);
    ll low = limit;
    ll high = 2*limit;
    while (low < n)
    {
        if (high >= n)
           high = n;
        bool mark[limit+1];
        memset(mark, true, sizeof(mark));
        for (ll i = 0; i < prime.size(); i++)
        {
            ll loLim = floor(low/prime[i]) * prime[i];
            if (loLim < low)
                loLim += prime[i];
            for (ll j=loLim; j<high; j+=prime[i])
                mark[j-low] = false;
        }
         for (ll i = low; i<high; i++)
            if (mark[i - low] == true){
                // cout << i << " "; 
                pans.push_back(i);              
            }
        low = low + limit;
        high = high + limit;
    }
}
//------------------------------------------------------------------------------
//sevie in O(n)
const ll MAXN=1e5+5;
vector <int> primee;
bool is_composite[MAXN];

void sieve (int n) {
    fill (is_composite, is_composite + n, false);
    for (int i = 2; i < n; ++i) {
        if (!is_composite[i]) prime.push_back (i);
        for (int j = 2; i * j < n; ++j)
            is_composite[i * j] = true;
    }
}
//-----------------------------------------------------------
/*gcd-lcm log(min(a,b))*/
ll gcd(ll a, ll b){
    if (b == 0){
        return a;
    }
    else{
        return gcd(b, a % b);
    }
}
ll lcm(ll a, ll b){
    return (a / gcd(a, b)) * b;
}