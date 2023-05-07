#include<bits/stdc++.h>
using namespace std;
#define ll long long 
//---------------------------------------------------------------------------
const ll MAX_N=10e5+10;
ll n,m;
vector<ll> adj[MAX_N];
ll vis[MAX_N];
void dfsg(ll u) {
    vis[u] = 1;
    for (ll v : adj[u]) {
        if (vis[v]) continue;
        dfsg(v);
    }
}
/* dfs TREE in O(n)*/
ll dfst(ll i,ll p){
    for(auto child: adj[i] ){
        if(child == p)
            continue;
        dfst(child,i);
    }
}