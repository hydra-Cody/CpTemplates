#include<bits/stdc++.h>
using namespace std;
#define ll long long 

//----------------------------------------------------------------------------------------------
//Diameter of tree with dfs and deapth
vector<ll> depth,ans;
vector<vector<ll>> adj;
void dfs(ll s,ll par)
{
    ll m1=-1,m2=-1;
    for(ll i=0;i<adj[s].size();i++)
    {
        ll ch=adj[s][i];
        if(ch!=par)
        {
            dfs(ch,s);
            if(depth[ch]>=m1){
                m2=m1;
                m1=depth[ch];
            }else if(depth[ch]>m2){
                m2=depth[ch];
            }
        }
    }
    depth[s]=m1+1;
    ans[s]=m1+m2+2;
}
ll diameter(){
    return *max_element(ans.begin(),ans.end());
}

//diameter with 2 dfs
Assume any node a as root
Start dfs from a and find that node b, having max dist from a
[ Using depth[child]=depth[node]+1 ]
(This node b will be an endpoint of a diameter)
Now, Start dfs from node b and find the node c,  which is at max distance (d) from b.
This value of d is the diameter of the tree.
int n, m, x, y; 
vector<int> adj[SZ];
 
pair<int,int> bfs(int src)
{
    int d = 0;
    queue<pair<int,int> > q;
    q.push({src, 0});
    vector<bool> vis(SZ, false);
    pair<int,int>  u;
 
    while(!q.empty()) {
        u = q.front();
        vis[u.first] = true;
        q.pop();
        for(int v: adj[u.first])
            if(!vis[v])
            q.push({v, u.second + 1});
    }
    return u;
}
 
int main() {
    cin >> n;
    for(int i = 0; i < n-1; i++) {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    pair<int,int>  end1 = bfs(1);
    pair<int,int>  end2 = bfs(end1.first);
    cout << end2.second << endl;
}

