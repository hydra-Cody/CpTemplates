#include<bits/stdc++.h>
using namespace std;
#define ll long long 
//-------------------------------------------------------------------------------
/*  implementation for directed graph.*/
ll n;
vector<vector<ll>> adj;
vector<char> color;
vector<ll> parent;
ll cycle_start, cycle_end;
bool dfs(ll v) {
    color[v] = 1;
    for (ll u : adj[v]) {
        if (color[u] == 0) {
            parent[u] = v;
            if (dfs(u))
                return true;
        } else if (color[u] == 1) {
            cycle_end = v;
            cycle_start = u;
            return true;
        }
    }
    color[v] = 2;
    return false;
}

void find_cycle() {
    color.assign(n, 0);
    parent.assign(n, -1);
    cycle_start = -1;

    for (ll v = 0; v < n; v++) {
        if (color[v] == 0 && dfs(v))
            break;
    }

    if (cycle_start == -1) {
        cout << "Acyclic" << endl;
    } else {
        vector<ll> cycle;
        cycle.push_back(cycle_start);
        for (ll v = cycle_end; v != cycle_start; v = parent[v])
            cycle.push_back(v);
        cycle.push_back(cycle_start);
        reverse(cycle.begin(), cycle.end());

        cout << "Cycle found: ";
        for (ll v : cycle)
            cout << v << " ";
        cout << endl;
    }
}
//-------------------------------------------------------
/* implementation for undirected graph */

ll n;
vector<vector<ll>> adj;
vector<bool> visited;
vector<ll> parent;
ll cycle_start, cycle_end;

bool dfs(ll v, ll par) { // passing vertex and its parent vertex
    visited[v] = true;
    for (ll u : adj[v]) {
        if(u == par) continue; // skipping edge to parent vertex
        if (visited[u]) {
            cycle_end = v;
            cycle_start = u;
            return true;
        }
        parent[u] = v;
        if (dfs(u, parent[u]))
            return true;
    }
    return false;
}

void find_cycle() {
    visited.assign(n, false);
    parent.assign(n, -1);
    cycle_start = -1;

    for (ll v = 0; v < n; v++) {
        if (!visited[v] && dfs(v, parent[v]))
            break;
    }

    if (cycle_start == -1) {
        cout << "Acyclic" << endl;
    } else {
        vector<ll> cycle;
        cycle.push_back(cycle_start);
        for (ll v = cycle_end; v != cycle_start; v = parent[v])
            cycle.push_back(v);
        cycle.push_back(cycle_start);

        cout << "Cycle found: ";
        for (ll v : cycle)
            cout << v << " ";
        cout << endl;
    }
}
