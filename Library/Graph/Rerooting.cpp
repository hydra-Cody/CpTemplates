#include<bits/stdc++.h>
using namespace std;
#define ll long long 


//--------------------------------------------------------------------------
//Rerooting Technique
const ll N = 3e5 + 9, LG = 18;
vector<ll> g[N];
ll size[N]; // cnt[i] = no. of nodes in subtree of i
ll dp[N]; // dp[i] = sum of distances of all the nodes in subtree of node i from node i
ll ans,n;
void dfs2(ll node, ll par)
{
  size[node]=1;
  dp[node]=0;
  for(auto it: g[node])
  {
     if(it==par)
        continue;
     dfs2(it,node);
     size[node]+=size[it];
     dp[node]+=dp[it];
  }
  dp[node]+=size[node];
}
void dfs(int v, int p = -1) {
   ans = max(ans, dp[v]);
   for (auto to : g[v]) {
      if (to == p) continue;
      
      dp[v] -= dp[to];
      dp[v] -= size[to];
      size[v] -= size[to];
      size[to] += size[v];
      dp[to] += size[v];
      dp[to] += dp[v];
      
      dfs(to, v);
      dp[to] -= dp[v];
      dp[to] -= size[v];
      size[to] -= size[v];
      size[v] += size[to];
      dp[v] += size[to];
      dp[v] += dp[to];
   }
}

  // ans=0;
  // dfs2(1,-1);
  // dfs(1);
