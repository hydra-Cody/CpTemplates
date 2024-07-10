#include<bits/stdc++.h>
using namespace std;
#define ll long long 
//------------------------------------------------------------------------------------------
/* 01bfs */
const ll MAX_N=10e5+10;
ll n,m;
vector<pair<ll,ll>> adj[MAX_N];
vector<ll> dist;
void bfs01(ll s) {
    dist.assign(n + 1, -1);
    deque<ll> q;
    dist[s] = 0; q.push_front(s);
    while (q.size()) {
        ll u = q.front(); q.pop_front();
        for (auto x : adj[u]) {
          ll v=x.first,w=x.second;
            if (dist[v] == -1) {
                dist[v] = dist[u] + w;
                if (w == 1) q.push_back(v);
                else q.push_front(v);
            }
        }
    }
}



//-----------------------------------------------------------------------------------------------
/*0K bfs even weights in between [0,K] in O(N*K+M) : Dial's algorithm */

vector<int> SmallDijkstra(vvl& graph, int src, int lim) {
  vector<vector<int>> qs(lim);
  vector<int> dist(graph.size(), -1);

  dist[src] = 0; qs[0].push_back(src);
  for (int d = 0, maxd = 0; d <= maxd; ++d) {
    for (auto& q = qs[d % lim]; q.size(); ) {
      int node = q.back(); q.pop_back();
      if (dist[node] != d) continue;
      for (auto [vec, cost] : graph[node]) {
        if (dist[vec] != -1 && dist[vec] <= d + cost) continue;
        dist[vec] = d + cost;
        qs[(d + cost) % lim].push_back(vec);
        maxd = max(maxd, d + cost);
      }
    }
  }
  return dist;
}