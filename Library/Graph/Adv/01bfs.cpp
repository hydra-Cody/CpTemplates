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