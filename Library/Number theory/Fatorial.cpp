#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007

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