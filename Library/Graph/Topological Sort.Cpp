#include<bits/stdc++.h>
using namespace std;
#define ll long long 

//--------------------------------------------------------------------------------
/*topological sort with dfs*/
const ll MAX_N=10e5+10;
ll n,m;
vector<ll> adj[MAX_N];
ll visited[MAX_N];
vector<ll> topo;
ll t;
void dfs(ll u) {
    visited[u] = 1;
    for (ll v : adj[u]) {
        if (!visited[v]) dfs(v);
        else if (visited[v] == 1) {
            t=1; //cycle present
            return;
        }
        if(t)return;
    }
    visited[u] = 2;
    topo.push_back(u);
}

//-----------------------------------------------------------

/*toposort with (in-out degree) bfs*/
void topo2(){
    ll in_deg[n]={0};
    for(ll i=0;i<m;i++){
        ll x,y;
        cin>>x>>y;
        adj[x].push_back(y);
        in_deg[y]++;
    }
    queue<ll> q;
    for(ll i=0;i<n;i++){
        if(in_deg[i]==0){
            q.push(i);
        }
    }
    vector<ll> topo_sort;
    while(!q.empty()){
        ll x  = q.front();
        q.pop();
        topo_sort.push_back(x);
        for(ll i=0;i<adj[x].size();i++){
            ll y = adj[x][i];
            in_deg[y]--;
            if(in_deg[y]==0){
                q.push(y);
            }
        }
    }
}
