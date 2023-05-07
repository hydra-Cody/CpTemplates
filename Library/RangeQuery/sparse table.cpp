#include<bits/stdc++.h>
using namespace std;
#define ll long long


//------------------------------------------------------------------------
const ll MX= 1e5+100,MAXK=25;
vector<vector<ll>> spt(MX,vector<ll>(MAXK+1));
vector<ll> aa(MX);
ll N;
void buildST(ll n)
{
  for(ll i=0; i<n; i++)
{
    spt[i][0] = aa[i];
}
for(ll k=1; k <= MAXK ; k++)
{
  for(ll i=0; i+( 1LL<<k)<=n; i++)
  { 
       spt[i][k] = min(spt[i][k-1],spt[ i + (1LL<<(k-1)) ][k-1]); 
  }
}
}
ll minquery(ll l, ll r)
{
  if(l>r) return INT_MAX;
  ll j = (ll)log2(r - l + 1);
  // ll j = 31 - __builtin_clz(r - l+1);
  return min (spt[l][j], spt[r - (1 << j) + 1][j]);
}
ll sumQuery(ll L,ll R){
  ll sum=0;
  for(ll k= MAXK; k>=0; k--){ 
    if ( (1<<k) <= R - L + 1 )
    {
      sum += spt[L][k];
      L += 1<<k;
    }
  }
}
vector<ll> lg;
void logcal(ll n){
  lg[1]=0;
  for(ll i=2; i<= N ; i++)
  {
    lg[i] = lg[i/2] + 1;
  }
}
