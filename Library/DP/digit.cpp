#include <bits/stdc++.h>
using namespace std;
#define ll long long

//---------------------------------------------------------------------------------------
/*
    [0,l]
*/
ll DP[12][2];
ll call(ll pos, ll f,string& st) {
    if (pos ==st.length()) return 1;
    if (DP[pos][f] != -1) return DP[pos][f];
    ll res = 0;
    ll LMT=(f?9:(ll)(st[pos]-'0'));
    for (ll dgt = 0; dgt <= LMT; dgt++) {
        // call(pos + 1, f || dgt<LMT,st);
    }
    return DP[pos][f] = res;
}

//--------------------------------------------------------
/*
    [l,r]
*/
ll dp[105][2][2];
ll rec(ll l,ll t1,ll t2,string& lo,string& hi){
    if(l==lo.length()){
        return 1;
    }
    if(dp[l][t1][t2]!=-1){
        return dp[l][t1][t2];
    }
    ll s=(t1?0:(int)(lo[l]-'0'));
    ll e=(t2?9:(int)(hi[l]-'0'));
    ll ans=0;
    for(ll i=s;i<=e;i++){
        // rec(l+1,(t1||i>s),(t2||i<e),lo,hi)
    }
    return dp[l][t1][t2]=ans;
}
//---------------------------------------------------------