#include<bits/stdc++.h>
using namespace std;
#define ll long long 
//-----------------------------------------------------------------------------------
/*dijkstra for single source shortest path in o(e+vlog(v)) with no negative edge*/
const ll MAX_N=10e5+10;
ll n,m;
vector<vector<pair<ll,ll>>> adj;
vector<ll> dist,vis,parent;
void dijkstra(ll s)
{  
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>> , greater<pair<ll,ll>> > pq;
    for(ll i=0; i<n; i++)
    {
        dist[i]=1e15; 
        vis[i]=0;
    }
    dist[s]=0;
    pq.push({dist[s], s});
    while (!pq.empty()){
        ll u=pq.top().second;
        pq.pop();
        if (vis[u]) continue;
        vis[u]=true;
        for(auto p: adj[u]){
            ll v=p.first;
            ll w=p.second;
            if(!vis[v] && dist[u] + w < dist[v]) {
                dist[v] =dist[u] + w;
                parent[v] = u;   
                pq.push({dist[v], v});
            }
        }
    }
}
