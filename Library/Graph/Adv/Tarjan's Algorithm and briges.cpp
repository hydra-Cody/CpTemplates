#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007

//---------------------------------------
/*
    Articulation points (Tarjan's Algorithm)
*/
//Finding Articulation point in a graph in  in o(n+m)
ll n;
vector<vector<ll>> adj;
vector<ll> disc, low,ap;
ll Time;
ll dfsAP(ll u, ll p) {
  ll children = 0;
  low[u] = disc[u] = ++Time;
  for (ll& v : adj[u]) {
    if (v == p) continue;
    if (!disc[v]) {
      children++;
      dfsAP(v, u);
      if (disc[u] <= low[v])
        ap[u] = 1;
      low[u] = min(low[u], low[v]);
    } else
      low[u] = min(low[u], disc[v]);
  }
  return children;
}

void AP() {
  ap = low = disc = vector<ll>(adj.size());
  Time = 0;
  for (ll u = 0; u < adj.size(); u++)
    if (!disc[u])
      ap[u] = dfsAP(u, u) > 1;
}


//---------------------------------------
//Finding bridges in a graph in  in o(n+m)
ll n; // number of nodes
vector<vector<ll>> adj; // adjacency list of graph

vector<bool> visited;
vector<ll> tin, low;
ll timer;

void dfs(ll v, ll p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (ll to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v]){
                // IS_BRIDGE(v, to);
            }
        }
    }
}

void find_bridges() {
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (ll i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i);
    }
}