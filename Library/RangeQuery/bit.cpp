#include<bits/stdc++.h>
using namespace std;
#define ll long long 
//--------------------------------------------------------------------------------------------
ll n;
vector<ll> bit(n+1,0);
void update(ll k,ll val)
{
  while(k<=n)
  {
    bit[k]+=val;
    k+=(k&(-k));
  }
}
ll sum(ll k)
{
  ll res=0;
  while(k>0)
  {
    res+=bit[k];
    k-=(k&(-k));
  }
return res;
}
ll query(ll l,ll r)
{
 return sum(r)-sum(l-1);
}