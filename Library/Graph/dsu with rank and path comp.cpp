#include<bits/stdc++.h>
using namespace std;
#define ll long long 

//--------------------------------------------------------------------------------------
/*dsu with rank and path comp[***] in o(1)*/
const ll MAX=100005;
ll par[MAX];
ll rnk[MAX];
void make_set(ll n)
{
    for(ll i=1; i<=n; i++)
    {
        par[i] = i;
        rnk[i] = 1;
    }
}
ll find(ll x)
{
    if(par[x]==x)
    return x;
    else
    return par[x]=find(par[x]);
}

void merge(ll x,ll y)
{
    ll px=find(x);
    ll py=find(y);
    if(rnk[px]>rnk[py])
    {
        par[py]=px;
        rnk[px]+=rnk[py];
    }
    else
    {
        par[px]=py;
        rnk[py]+=rnk[px];
    }
}