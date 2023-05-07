#include<bits/stdc++.h>
using namespace std;
#define ll long long 

//--------------------------------------------------------------------------------------
/*dsu with rank and path comp[***] in o(1)*/
const ll MAX_N=10e5+10;
ll n,m;
vector<ll> adj[MAX_N];
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
//-------------------------------------------------------------------------------------
/*kruskal MST[***]  in O(ELogE + ELogV) */
vector<pair<ll,pair<ll,ll>>> edges;
void kruskal() {
    sort(edges.begin(), edges.end());
    make_set(n);
    ll cnt = 0, cost = 0;
    for (auto x : edges) {
        ll w=x.first;
        ll u=x.second.first;
        ll v=x.second.second;
        u = find(u), v = find(v);
        if (u != v) {
            merge(u,v);
            cost += w;
            cnt++;
        }
    }
    if (cnt == n - 1) cout << cost << "\n";
    else cout << "IMPOSSIBLE\n";
}