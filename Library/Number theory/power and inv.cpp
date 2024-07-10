#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007

//--------------------------------------------------------------------------
/*power with modp log(y)*/
ll power(ll x,ll y, ll p){
    if(y==0)return 1;
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
/*inverse in log(m) */
ll inv(ll a, ll m)
{
    // ll g = gcd(a, m);
    // if (g != 1){
    //     return -1;
    // }
    return power(a, m - 2, m);
}
//------------------------------------------------------------------------------------
/*power without mod in log(n)*/
ll power(ll a, ll b){