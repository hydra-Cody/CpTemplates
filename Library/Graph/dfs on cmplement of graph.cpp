#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007

//--------------------------------------

void chal(){
  ll n,m;
  cin>>n>>m;
  vector<set<ll>> g(n);
  fo(i,m){
    ll x,y;
    cin>>x>>y;
    x--;
    y--;
    g[x].insert(y);
    g[y].insert(x);
  }
  ll ans=0;
  set<ll> bb;
  fo(i,n)bb.insert(i);
  fo(i,n){
    if(bb.count(i)){
      queue<ll> q;
      ans++;
      bb.erase(i);
      q.push(i);
      while(!q.empty()){
        ll ch=q.front();
        q.pop();
        vl cc;
        for(auto ch2:bb){
          if(!g[ch].count(ch2)){
            cc.pb(ch2);
          }
        }
        fo(i,sz(cc)){
          bb.erase(cc[i]);
          q.push(cc[i]);
        }
      }
    }
  }
  cout<<ans-1<<endl;
 
 
 
  /*
  life is a drink and love’s a drug oh now I think I must be miles up
  when I was a river dried up you came to rain a flood ooa  
  */
 
 
}