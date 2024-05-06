#include<bits/stdc++.h>
using namespace std;
#define ll long long 

//--------------------------------------------------------------------------------
/*Kosaraju in O(V+E)*/
const ll MAX_N = 1e5 + 1;
ll n, m, scc, visited[MAX_N];
vector<ll> adj[2][MAX_N], comp[MAX_N], dfn;
void dfs(ll u, ll t) {
    visited[u] = 1;
    if (t == 1) comp[scc].push_back(u);
    for (ll v : adj[t][u]) {
        if (!visited[v]) {
            dfs(v, t);
        }
    }
    if (t == 0) dfn.push_back(u);
}
void kosaraju() {
    for (ll i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, 0);
        }
    }
    memset(visited, 0, sizeof visited);
    for (ll i = n - 1; i >= 0; i--) {
        if (!visited[dfn[i]]) {
            scc++;
            dfs(dfn[i], 1);
        }
    }
}