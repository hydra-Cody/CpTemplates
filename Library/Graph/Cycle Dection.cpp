#include<bits/stdc++.h>
using namespace std;
#define ll long long 
//-------------------------------------------------------------------------------
/*  Detection of cycle*/
bool cy(ll s,ll p,vector<vector<ll>>& g,vector<ll>& vis){
	if(vis[s])return 1;
	vis[s]=1;
	bool ans=0;
	for(auto ch:g[s]){
		if(ch!=p){
			if(vis[ch])return 1;
			ans|=cy(ch,s,g,vis);
		}
	}
	return ans;
}
//-------------------------------------------------------
/* Print the cycle */

void dfs(ll s,vector<ll>& g,vector<ll>& vis,
  vector<vector<ll>>& cy,vector<ll>& inst){
  vis[s]=1;
  inst[s]=1;
  ll ch=g[s];
  if(vis[ch]==0){
    dfs(ch,g,vis,cy,inst);
  }else if(inst[ch]==1){
    vector<ll> cy2;
    cy2.push_back(s);
    while(ch!=s){
      cy2.push_back(ch);
      ch=g[ch];
    }
    cy.push_back(cy2);
  }
  inst[s]=2;
 
}

