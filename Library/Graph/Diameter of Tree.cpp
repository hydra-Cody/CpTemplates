#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007

//-----------------------------------------------------------------------------
/*
  Diameter of Tree
*/
const ll MX=2e5+9;

struct TreeDiameter {
    ll n, dist[MX], pre[MX];
    vector<ll> adj[MX];
 
    void addEdge(int a, int b) {
        adj[a].push_back(b), adj[b].push_back(a);
    }
 
    void dfs(ll cur) {
        for (ll i: adj[cur]) if (i != pre[cur]) {
            pre[i] = cur;
            dist[i] = dist[cur]+1;
            dfs(i);
        }
    }
 
    void genDist(ll cur) {
        memset(dist,0,sizeof dist);
        pre[cur] = -1;
        dfs(cur);
    }
 
    ll diameterLength() {
        genDist(1);
        ll bes = 0; for(ll i=1;i<=n;i++) if (dist[i] > dist[bes]) bes = i;
        genDist(bes); for(ll i=1;i<=n;i++) if (dist[i] > dist[bes]) bes = i;
        return dist[bes];
    }
 
    vector<ll> genCenter() {
        ll t = diameterLength();
        ll bes = 0; for(ll i=1;i<=n;i++) if (dist[i] > dist[bes]) bes = i;
 
        for(ll i=0;i<t/2;i++) bes = pre[bes];
        if (t&1) return {bes,pre[bes]};
        return {bes};
    }
};

