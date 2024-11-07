
#include<bits/stdc++.h>
using namespace std;
#define ll long long 

//-------------------------------------------------------------------
/*
	function is associative/idempotent function in O(1) 
	(Minimum / Maximum / GCD in O(1)) without update
    1D
*/

// vector<ll> lg(MX);
// void logcal(){
//   lg[1]=0;
//   for(ll i=2; i<= MX ; i++)
//   {
//     lg[i] = lg[i/2] + 1;
//   }
// }
const ll MX= 1e5+100,MAXK=25;
vector<vector<ll>> spt(MX,vector<ll>(MAXK+1));
void buildST(ll n,vector<ll>& aa){
  for(ll i=0; i<n; i++){
    spt[i][0] = aa[i];
  }
  for(ll k=1; k <= MAXK ; k++){
    for(ll i=0; i+( 1LL<<k)<=n; i++){ 
       spt[i][k] = min(spt[i][k-1],spt[ i + (1LL<<(k-1)) ][k-1]); 
     }
   }
   // logcal();
}
ll minquery(ll l, ll r){
  if(l>r) return INT_MAX;
  // ll j = (ll)lg[r - l + 1];
  ll j = 31 - __builtin_clz(r - l+1);
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
