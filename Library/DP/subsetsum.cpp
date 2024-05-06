#include<bits/stdc++.h>
using namespace std;
#define ll long long

//----
ll subset(vector<ll>& aa,vector<vector<ll>>& dp,ll l,ll s){
  if(s==0)return 1;
  if(s<0 || l<=0)return 0;
  if(dp[l][s]!=-1)return dp[l][s];
  ll ans=0;
  if(aa[l]<=s){
    ans|=subset(aa,dp,l-1,s-aa[l]);
  }
  ans|=subset(aa,dp,l-1,s);
  return dp[l][s]=ans;

}