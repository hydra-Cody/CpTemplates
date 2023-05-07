#include<bits/stdc++.h>
using namespace std;
#define ll long long 


//----------------------------------------------------------------------
//Binary Lifting
ll n;
ll x=log(n)+1; //max possible jump req to reach 
// a parent (You can also take x=30)
vector<vector<ll> > v; // adjacency list of tree
ll par[n][x]; 
void dfs(ll s,ll p){// s-->source node// p-->parent of s..
    par[s][0]=p;
    for(ll j=1;j<=x;j++)
        par[s][j]=par[par[s][j-1]][j-1];
    for(ll i=0;i<v[s].size();i++){
        ll ch=v[s][i];
        if(ch!=p)
            dfs(ch,s)
    }
}
int find_kth(ll s,ll k){
    for(ll j=x;j>=0;j--){
    if((1<<j)&k){//jth bit set or not in k..
    s=par[s][j];//jump of 2^j
    k-=(1<<j);
    }
    return s;
}