#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007


//----------------------------------------------------------------------------------------
ll n,m,t;
vector<vector<pair<ll,ll>>> g;
vector<vector<ll>> par,dp;
vector<ll> vis;
ll dfs(ll s){
  vis[s]=1;
  for(auto ch:g[s]){
    if(vis[ch.first]==0){
      dfs(ch.first);
    }
    for(ll i=1;i<n+1;i++){
      dp[s][i]=min(dp[s][i],dp[ch.first][i]+ch.second);
    }
  }
}