#include<bits/stdc++.h>
using namespace std;
#define ll long long 

//--------------------------------------------------------------------------------------- 
/*prim O(V2)*/
const ll MAX_N = 1e5 + 1;
ll n, m, visited[MAX_N];
vector<pair<ll,ll>> adj[MAX_N];
void prim(ll s = 1) {
    ll cost = 0;
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
    visited[s] = 1; 
    for (auto ch: adj[s]){ 
        ll u=ch.first,d=ch.second;
        if (!visited[u]) 
            pq.push({d, u});
    }
    while (pq.size()) {
        auto ch2= pq.top();
        ll d=ch2.first, u=ch2.second;  
        pq.pop();
        if (!visited[u]) {
            cost += d;
            visited[u] = 1;
            for (auto ch3 : adj[u]){ 
                ll v=ch3.first, w=ch3.second;
                if (!visited[v]) 
                    pq.push({w, v});
            }
        }
    } 
    for (ll i = 1; i <= n; i++) {
        if (!visited[i]) {
            cout << "IMPOSSIBLE\n";
            exit(0);
        }
    }
    cout << cost << "\n";
}




// Dense graphs:O(n^2)
// int n;
// vector<vector<int>> adj; // adjacency matrix of graph
// const int INF = 1000000000; // weight INF means there is no edge

// struct Edge {
//     int w = INF, to = -1;
// };

// void prim() {
//     int total_weight = 0;
//     vector<bool> selected(n, false);
//     vector<Edge> min_e(n);
//     min_e[0].w = 0;

//     for (int i=0; i<n; ++i) {
//         int v = -1;
//         for (int j = 0; j < n; ++j) {
//             if (!selected[j] && (v == -1 || min_e[j].w < min_e[v].w))
//                 v = j;
//         }

//         if (min_e[v].w == INF) {
//             cout << "No MST!" << endl;
//             exit(0);
//         }

//         selected[v] = true;
//         total_weight += min_e[v].w;
//         if (min_e[v].to != -1)
//             cout << v << " " << min_e[v].to << endl;

//         for (int to = 0; to < n; ++to) {
//             if (adj[v][to] < min_e[to].w)
//                 min_e[to] = {adj[v][to], v};
//         }
//     }

//     cout << total_weight << endl;
// }





// Sparse graphs:mlog(n)
// const int INF = 1000000000;

// struct Edge {
//     int w = INF, to = -1;
//     bool operator<(Edge const& other) const {
//         return make_pair(w, to) < make_pair(other.w, other.to);
//     }
// };

// int n;
// vector<vector<Edge>> adj;

// void prim() {
//     int total_weight = 0;
//     vector<Edge> min_e(n);
//     min_e[0].w = 0;
//     set<Edge> q;
//     q.insert({0, 0});
//     vector<bool> selected(n, false);
//     for (int i = 0; i < n; ++i) {
//         if (q.empty()) {
//             cout << "No MST!" << endl;
//             exit(0);
//         }

//         int v = q.begin()->to;
//         selected[v] = true;
//         total_weight += q.begin()->w;
//         q.erase(q.begin());

//         if (min_e[v].to != -1)
//             cout << v << " " << min_e[v].to << endl;

//         for (Edge e : adj[v]) {
//             if (!selected[e.to] && e.w < min_e[e.to].w) {
//                 q.erase({min_e[e.to].w, e.to});
//                 min_e[e.to] = {e.w, v};
//                 q.insert({e.w, e.to});
//             }
//         }
//     }

//     cout << total_weight << endl;
// }