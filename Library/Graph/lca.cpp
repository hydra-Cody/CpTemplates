#include<bits/stdc++.h>
using namespace std;
#define ll long long 

//---------------------------------------------------------------------------
/*Lowest Common Ancestor/LCA (Binary Lifting)*/
const ll MAX_N = 2e5 + 1;
const ll MAX_L = 20;//log(n)+1;
ll n, q, par[MAX_N][MAX_L], dep[MAX_N];
vector<ll> adj[MAX_N];
void dfs(ll u, ll p = 0) {
    par[u][0] = p;
    for (ll i = 1; i < MAX_L; i++) 
        par[u][i] = par[par[u][i - 1]][i - 1];
    for (ll v : adj[u]) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}
ll find_kth(ll u, ll k) {
    for (ll i = 0; i < MAX_L; i++) 
        if (k & (1 << i)) 
            u = par[u][i];
    return u;
}
ll lca(ll u, ll v) {
    if (dep[u] < dep[v]) swap(u, v);
    u = find_kth(u, dep[u] - dep[v]);
    if (u == v) return u;
    for (int i = MAX_L - 1; i >= 0; i--)
        if (par[u][i] != par[v][i])
            u = par[u][i], v = par[v][i];
    return par[u][0];
}