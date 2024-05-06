#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007
//----------------------------------------------------------------------------------
/*mod operations*/
ll mod_add(ll a, ll b,ll mod) {
    a = a % mod; b = b % mod; 
    return (((a + b) % mod) + mod) % mod;
}
ll mod_mul(ll a, ll b,ll mod) {
    a = a % mod; b = b % mod; 
    return (((a * b) % mod) + mod) % mod;
}
ll mod_sub(ll a, ll b,ll mod) {
    a = a % mod; b = b % mod;
     return (((a - b) % mod) + mod) % mod;
 }
//-----------------------------------------------------------------------------------------------------
/*interger square root int sqrt(x)*/
ll int_sqrt (ll x) {
    ll ans = 0; 
    for (ll k = 1LL << 30; k != 0; k /= 2) {
        if ((ans + k) * (ans + k) <= x) {
            ans += k;
        }
    } 
    return ans;
}
//------------------------------------------------------------------------------------
ll logceil(ll x){
  ll s=0;
  while(x>0){
    s++;
    x=x/2;
  }
  return s;
}

//-----------------------------------------------------------------------------
unsigned int myrand(){
    static unsigned long long seed=0;
    seed=6364136223846793005ULL*seed+1;
    return (unsigned int)(seed>>30);
}
//--------------------------------------------------------------------
unsigned int digitSumFast(unsigned long long x)
{
    unsigned int result = 0;
    while (x >= 10) {
        result + x % 10;
        x/= 10;
    }
    return result + x;
}
//--------------------------------------------------------------------
