#include<bits/stdc++.h>
using namespace std;
#define ll long long 
//-----------------------------------------------
/* DFS on Complement of Graph */

void dfsComp(){
  ll n,m;
  cin>>n>>m;
  vector<set<ll>> g(n);
  for(ll i=0;i<m;i++){
    ll x,y;
    cin>>x>>y;
    x--;
    y--;
    g[x].insert(y);
    g[y].insert(x);
  }
  ll ans=0;
  set<ll> bb;
  for(ll i=0;i<n;i++)bb.insert(i);
  for(ll i=0;i<n;i++){
    if(bb.count(i)){
      queue<ll> q;
      ans++;
      bb.erase(i);
      q.push(i);
      while(!q.empty()){
        ll ch=q.front();
        q.pop();
        vector<ll> cc;
        for(auto ch2:bb){
          if(!g[ch].count(ch2)){
            cc.push_back(ch2);
          }
        }
        for(ll i=0;i<cc.size();i++){
          bb.erase(cc[i]);
          q.push(cc[i]);
        }
      }
    }
  }
  cout<<ans-1<<endl;
 
 
}