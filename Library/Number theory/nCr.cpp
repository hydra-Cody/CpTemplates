#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007

//---------------------------------------------------------------------------------
/*fatorial of a number with mod O(n)*/
ll factMO(ll n){
    ll ans=1;
    while(n--){
        ans*=(n+1);
        ans%=MOD;
    }
    return ans;
}
//-----------------------------------------------------------------------------------
/*factorail in series vector with mod in (n)*/
vector<ll> fact1;
void factorial(ll n){
    fact1.resize(n+1);
    fact1[0]=1;
    for(ll i=1;i<n+1;i++){
        fact1[i]=(fact1[i-1]*i)%MOD;
    }
}
ll nCr1(ll n, ll r)
{
    return fact1[n] / (fact1[r] * fact1[n - r]);
}
//------------------------------------------------------------------------
ll power(ll x,ll y, ll p){
    ll res = 1;
    x = x % p;
    if (x == 0) return 0;
    while (y > 0)
    {
        if (y & 1)
            res = (res*x) % p;
 
        y = y>>1;
        x = (x*x) % p;
    }
    return res;
}
ll inv2(ll a, ll m){   return power(a, m - 2, m);}
/*ncr frome formul (n!)*inv(r!)*inv((n-r)!)a with mod in (n)*/
ll nCr2(ll n,ll r){
    if (r==0 || n==0) return 1;
    vector<ll> fac(n+1);
    fac[0]=1;
    for(ll i=1;i<n+1;i++)
        fac[i]=(fac[i-1]*i)%MOD;
    return (fac[n]*inv2(fac[r],MOD)%MOD*inv2(fac[n-r],MOD)%MOD)%MOD;
}
//------------------------------------------------------------------------------------
/*ncr Calculation for multi query in (n) precompute with mod and 1 for query*/
const int N = 2e5 + 1;
ll fact[N], inv[N], invfact[N];
void factInverse() {
  fact[0] = inv[1] = fact[1] = invfact[0] = invfact[1] = 1;
  for (ll i = 2; i < N; i++) {
    fact[i] = (fact[i - 1] * i) % MOD;
    inv[i] = MOD - (inv[MOD % i] * (MOD / i) % MOD);
    invfact[i] = (inv[i] * invfact[i - 1]) % MOD;
  }
}
ll nCr(ll n, ll r) {
  if (r > n)
    return 0;
  ll ans= (fact[n]%MOD);
  ans=  ( (ans%MOD)*(invfact[r]%MOD)   )%MOD;
  ans= (  (ans%MOD)*(invfact[n-r]%MOD)  )%MOD;
  return ans;
}
//-------------------------------------------------------------------------------
/*catalan with ncr formula in o(n)*/
ll binomialCoeff(ll n,ll k){
    ll res = 1;
    if (k > n - k)
        k = n - k;
    for (ll i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}
ll catalan(ll n){
    ll c = binomialCoeff(2 * n, n);
    return c / (n + 1);
}
/*Catalan Dp in n^2*/
ll catalanDP(ll n)
{
    ll catalan[n + 1];
    catalan[0] = catalan[1] = 1;
    for (int i = 2; i <= n; i++) {
        catalan[i] = 0;
        for (int j = 0; j < i; j++)
            catalan[i] += catalan[j] * catalan[i - j - 1];
    }
    return catalan[n];
}