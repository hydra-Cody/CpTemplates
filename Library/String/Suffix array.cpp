#include<bits/stdc++.h>
using namespace std;
#define ll long long 


//----------------------------------------------------------------------


//-Suffix arrays
void suffix(string s,ll n){
    s+='$';
    n+=1;
    vl p(n),c(n);
    vector<pair<char,ll>> aa(n);
    for(ll i=0;i<n;i++)aa[i]={s[i],i};
      sort(all(aa));
    for(ll i=0;i<n;i++)p[i]=aa[i].se;
      c[p[0]]=0;
    for(ll i=1;i<n;i++){
      if(aa[i].fi==aa[i-1].fi){
        c[p[i]]=c[p[i-1]];
      }else{
        c[p[i]]=c[p[i-1]]+1;
      }
    }
    ll k=0;
    while((1<<k)<n){
      vector<pair<pair<ll,ll>,ll>> a(n);
      for(ll i=0;i<n;i++){
        a[i]={{c[i],c[(i+(1<<k))%n]},i};
      }
      sort(all(a));
      for(ll i=0;i<n;i++)p[i]=a[i].se;
        c[p[0]]=0;
      for(ll i=1;i<n;i++){
        if(a[i].fi==a[i-1].fi){
          c[p[i]]=c[p[i-1]];
        }else{
          c[p[i]]=c[p[i-1]]+1;
        }
      }
      k++;
    }
    for(ll i=0;i<n;i++){
      cout<<p[i]<<endl;
    }
}
//--op suffix array
void count_sort(vector<ll> &p,vl& c){
  ll n=p.size();
  vl cnt(n);
  for(auto x:c){
    cnt[x]++;
  }
  vl p_new(n);
  vl pos(n);
  pos[0]=0;
  for(ll i=1;i<n;i++){
    pos[i]=pos[i-1]+cnt[i-1];
  }
  for(auto x:p){
    int i=c[x];
    p_new[pos[i]]=x;
    pos[i]++;
  }
  p=p_new;
}


void suffix(string s,ll n){
    s+='$';
    n+=1;
    vl p(n),c(n);
    vector<pair<char,ll>> aa(n);
    for(ll i=0;i<n;i++)aa[i]={s[i],i};
      sort(all(aa));
    for(ll i=0;i<n;i++)p[i]=aa[i].se;
      c[p[0]]=0;
    for(ll i=1;i<n;i++){
      if(aa[i].fi==aa[i-1].fi){
        c[p[i]]=c[p[i-1]];
      }else{
        c[p[i]]=c[p[i-1]]+1;
      }
    }
    ll k=0;
    while((1<<k)<n){
      for(ll i=0;i<n;i++){
        p[i]=(p[i]-(1<<k)+n)%n;
      }
      count_sort(p,c);
      vl c_new(n);
      c_new[p[0]]=0;
      for(ll i=1;i<n;i++){
        pl prev={c[p[i-1]],c[(p[i-1]+(1<<k))%n]};
        pl now={c[p[i]],c[(p[i]+(1<<k))%n]};
        if(now==prev){
          c_new[p[i]]=c_new[p[i-1]];
        }else{
          c_new[p[i]]=c_new[p[i-1]]+1;
        }
      }
      c=c_new;
      k++;
    }
    for(ll i=0;i<n;i++){
      cout<<p[i]<<' ';
    }
    cout<<endl;
}