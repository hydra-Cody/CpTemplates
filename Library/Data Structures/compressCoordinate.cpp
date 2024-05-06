#include<bits/stdc++.h>
using namespace std;
#define ll long long 
//-------------------------------------------
/* Compress range numbers*/
void comp(vector<ll>& aa,ll& n){
  map<ll,ll> pos;
  for(ll i=0;i<n;i++){
    pos[aa[i]]=i;
  }
  ll val=0;
  for(auto it=pos.begin();it!=pos.end();it++){
    aa[it->second]=++val;
  }
}


//------------------------------------------------
/*remove duplicate element from array */
void compress(vector<ll>& vs){
  sort(vs.begin(),vs.end());
  vs.resize(unique(vs.begin(), vs.end()) - vs.begin());
}

//------------------------------------------------
//--------------------------------------------

map<ll, ll> pnt_compression(vector<ll> &pnt){ 
  map<ll, ll> u; 
  ll i=0,ct=0; 
  for(ll i=0;i<pnt.size();i++){
    u[pnt[i]]=0;
  }
  for(auto &it:u){ 
    it.second=ct; 
    ct++;
  } 
  return u; 
}