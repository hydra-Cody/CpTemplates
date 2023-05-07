#include <bits/stdc++.h>
#define fr first
#define sc second

using namespace std;
const int MN = 2e5+7;

int dp[MN], dep[MN], timer, l, n, ans[MN], tin[MN], tout[MN];
vector<int> g[MN];
map<pair<int, int>, int> data;
vector<vector<int>> up;

bool is_ancestor(int u, int v){
    return (tin[u] <= tin[v] && tout[u] >= tout[v]);
}

int rise(int u, int v){
    if(dep[u] == dep[v]+1)return u;
    int ln = dep[u] - dep[v] - 1;
    int c = 0;
    while(ln){
        if(ln & 1)u = up[u][c];
        ln >>= 1;
        c++;
    }
    return u;
}

void cal(int nw, int pr){
    dp[nw] = 1;
    for(auto u : g[nw]){
        if(u == pr)continue;
        cal(u, nw);
        dp[nw] += dp[u];
    }
}

void store(int r, int u, int vl){
    data[{r, u}] = vl;
}

void dfs(int nw, int pr){
    int v = nw;

    tin[v] = ++timer;
    up[v][0] = pr;
    for (int i = 1; (1 << i) <= dep[v]; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for(auto u : g[nw]){
        if(u == pr)continue;
        dep[u] = dep[nw]+1;
        int fdpnw = dp[nw], fdpu = dp[u];

        store(nw, u, dp[u]);

        dp[nw] -= dp[u];
        dp[u] += dp[nw];

        store(u, nw, dp[nw]);
        dfs(u, nw);

        dp[nw] = fdpnw;
        dp[u] = fdpu;
    }

    tout[nw] = ++timer;
}

void preprocess(int root) {
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(root, root);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    int q;
    cin >> n >> q;
    for(int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cal(0, 0);
    for(int i = 0; i < n; i++)ans[i] = dp[i];
    preprocess(0);

    while(q--){
        int u, r;
        cin >> r >> u;
        r--; u--;
        if(r == u){
            cout << n << '\n';
            continue;
        }
        if(is_ancestor(u, r)){
            r = rise(r, u);
            cout << data[{r, u}] << '\n';
        }
        else{
            cout << ans[u] << '\n';
        }
    }
}