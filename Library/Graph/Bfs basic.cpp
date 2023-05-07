#include<bits/stdc++.h>
using namespace std;
#define ll long long 

//----------------------------------------------------------------------------------
/*Distance of node with bfs in O(v+e)*/
const ll MAX_N=10e5+10;
ll n,m;
vector<ll> g[MAX_N];
vector<ll>  dist;
void bfs(ll s) {
    dist.assign(n + 1, -1);
    queue<ll> q;
    dist[s] = 0; 
    q.push(s);
    while (q.size()) {
        ll u = q.front(); q.pop();
        // cout<<u<<"->";
        for (ll v : g[u]) {
            if (dist[v] == -1) {
                // cout<<v<<" ";
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
        // cout<<endl;
    }
}