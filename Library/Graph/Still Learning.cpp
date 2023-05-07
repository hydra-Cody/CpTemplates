#include<bits/stdc++.h>
using namespace std;
#define ll long long 

//--------------------------------------------------------------------------------------
// Grph Moduling
//---------------------------------------------------------------------------------------
/*Lowest Common Ancestor/LCA (RMQ)*/
const int MAX_N = 2e5 + 1;
const int MAX_L = 30;
int n, q, idx;
int dep[2 * MAX_N], euler[2 * MAX_N], first[MAX_N], lg[2 * MAX_N];
ar<int,2> dp[2 * MAX_N][MAX_L]; // need to store both the indices and the min value
vector<int> adj[MAX_N];

void dfs(int u, int p = 0, int h = 0) {
    euler[++idx] = u;
    dep[idx] = h;
    first[u] = idx;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, h + 1);
            euler[++idx] = u;
            dep[idx] = h;
        }
    }
}

void build_lg_table() {
    lg[1] = 0;
    for (int i = 2; i <= 2 * n; i++) 
        lg[i] = lg[i / 2] + 1;
}
 
void build_sparse_table() {
    for (int i = 1; i <= 2 * n; i++)
        dp[i][0] = {dep[i], euler[i]};
    for (int j = 1; j < MAX_L; j++)
        for (int i = 1; i + (1 << j) <= 2 * (n + 1); i++)
            dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
}
int min_query(int l, int r) { 
    int k = lg[r - l + 1];
    return min(dp[l][k], dp[r - (1 << k) + 1][k])[1]; // return the index with min value
}
int lca(int u, int v) {
    int l = first[u], r = first[v];
    if (l > r) swap(l, r);
    return min_query(l, r);
}
//------------------------------------------------------------------------------------

/*Tarjan*/
const int MAX_N = 1e5 + 1;
int n, m, scc, dfsCounter;
int dfs_num[MAX_N], dfs_low[MAX_N], visited[MAX_N];
stack<int> st;
vector<int> adj[MAX_N], comp[MAX_N];
// Modified DFS
void tarjan(int u) { 
    dfs_low[u] = dfs_num[u] = dfsCounter++;
    visited[u] = 1;
    st.push(u);
    for (int v : adj[u]) {
        if (dfs_num[v] == -1) tarjan(v); 
        if (visited[v]) dfs_low[u] = min(dfs_low[u], dfs_low[v]); 
    }

    if (dfs_low[u] == dfs_num[u]) {
        scc++;
        while (st.size()) {
            int v = st.top(); st.pop();
            visited[v] = 0;
            comp[scc].push_back(v);
            if (v == u) break;
        }
    }
}
//------------------------------------------------------------------------------
/*Max Flow/Edmonds_Karp*/
const int MAX_N = 1e5 + 5;
struct max_flow_graph {
    struct edge {
        int u, v, cap, flow;
    };
    int n; 
    vector<edge> el; 
    vector<vector<int>> adj;
    vector<int> dist, par;
    max_flow_graph(int n) : n(n), adj(n) {}
    void add_edge(int u, int v, int w) {
        adj[u].push_back(el.size());
        el.push_back({u, v, w, 0});
        adj[v].push_back(el.size());
        el.push_back({v, u, 0, 0}); 
    }
    int send_one_flow(int s, int e) {
        int nf = INF;
        for (int u = e; u != s; u = el[par[u]].u) {
            nf = min(nf, el[par[u]].cap - el[par[u]].flow);
        }
        for (int u = e; u != s; u = el[par[u]].u) {
            el[par[u]].flow += nf;
            el[par[u]^1].flow -= nf;
        }
        return nf;
    }
    bool bfs(int s, int e) {
        dist.assign(n, INF);
        par.assign(n, 0);
        queue<int> q;
        q.push(s); dist[s] = 0;
        while (q.size()) {
            int u = q.front(); q.pop();
            if (u == e) break;
            for (int idx : adj[u]) {
                if (el[idx].cap > el[idx].flow && dist[el[idx].v] > dist[el[idx].u] + 1) {
                    dist[el[idx].v] = dist[el[idx].u] + 1;
                    par[el[idx].v] = idx;
                    q.push(el[idx].v);
                }
            }
        }
        return dist[e] < INF;
    }
    ll edmonds_karp(int s, int e) {
        ll mf = 0;
        while (bfs(s, e)) mf += send_one_flow(s, e);
        return mf;
    }
};

//----------------------------------------------------------------------------------------
/*Max Flow/Dinic*/
const int MAX_N = 1e5 + 5;
struct max_flow_graph {
    struct edge {
        int u, v, cap, flow;
    };
    int n; 
    vector<edge> el; 
    vector<vector<int>> adj;
    vector<int> dist, par;
    max_flow_graph(int n) : n(n), adj(n) {}
    void add_edge(int u, int v, int w) {
        adj[u].push_back(el.size());
        el.push_back({u, v, w, 0});
        adj[v].push_back(el.size());
        el.push_back({v, u, 0, 0}); 
    }
    int send_one_flow(int s, int e) {
        int nf = INF;
        for (int u = e; u != s; u = el[par[u]].u) {
            nf = min(nf, el[par[u]].cap - el[par[u]].flow);
        }
        for (int u = e; u != s; u = el[par[u]].u) {
            el[par[u]].flow += nf;
            el[par[u]^1].flow -= nf;
        }
        return nf;
    }
    bool bfs(int s, int e) {
        dist.assign(n, INF);
        par.assign(n, 0);
        queue<int> q;
        q.push(s); dist[s] = 0;
        while (q.size()) {
            int u = q.front(); q.pop();
            if (u == e) break;
            for (int idx : adj[u]) {
                if (el[idx].cap > el[idx].flow && dist[el[idx].v] > dist[el[idx].u] + 1) {
                    dist[el[idx].v] = dist[el[idx].u] + 1;
                    par[el[idx].v] = idx;
                    q.push(el[idx].v);
                }
            }
        }
        return dist[e] < INF;
    }
    int dfs(int s, int e, int f = INF) {
        if (s == e || f == 0) return f;
        for (int idx : adj[s]) {
            if (dist[el[idx].v] != dist[s] + 1) continue;
            if (int nf = dfs(el[idx].v, e, min(f, el[idx].cap - el[idx].flow))) {
                el[idx].flow += nf;
                el[idx^1].flow -= nf;
                return nf;
            }
        }
        return 0;
    }
    ll dinic(int s, int e) {
        ll mf = 0;
        while (bfs(s, e)) {
            while (int nf = dfs(s, e)) mf += nf;
        }
        return mf;
    }
};
//--------------------------------------------------------------------------
/*Dijkstra in dense graphs*/
/**
 * Description: Dijkstra (Find shortest path from single source in dense graph)
 * Usage: dijkstra O(V^2) 
 * Source: https://github.com/dragonslayerx 
 */

const int MAX = 1005
const int INF = 1e9
    
void dijkstra(int v, int source, int path_estimate[], int W[][MAX]) {
    bool isvisited[MAX];
    for (int i = 0; i < v; i++) {
                isvisited[i] = false;
        path_estimate[i] = INF;
    }

    path_estimate[source] = 0;
    for (int i = 0; i < v; i++) {
        int mindist = INF, vertex;
        for (int j = 0; j < v; j++) {
            if (!isvisited[j] && mindist > path_estimate[j]) {
                mindist = path_estimate[j];
                vertex = j;
            }
        }
        isvisited[vertex] = true;
        for (int i = 0; i < v; i++) {
            if (!isvisited[i]) {
                    if (path_estimate[i] > path_estimate[vertex] + W[vertex][i]) {
                        path_estimate[i] = path_estimate[vertex] + W[vertex][i];
                    }
            }
        }
    }
}



/*Kth Shortest Path between Nodes using Dijkstra*/
/**
 * Description: Finds Kth shortest path from s to t.
 * Usage : getCost O((V + E) lg(V) * k)
 * Source: https://github.com/dragonslayerx
 */
const int INF = 1e9;
int getCost(vector< vector< pair<int,int> > > &G, int s, int t, int k) {
    int n = G.size();
    int dist[MAX], count[MAX];
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        count[i] = 0;
    }
    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > Q;
    Q.push(make_pair(0, s));
    while (!Q.empty() && (count[t] < k)) {
        pair<int,int> node = Q.top();
        int u = node.second;
        int w = node.first;
        Q.pop();
        if ((dist[u] == INF) or (w > dist[u])) { // remove equal paths
            count[u]++;
            dist[u] = w;
        }
        if (count[u] <= k) {
            for (int i = 0;  i < G[u].size(); i++) {
            int v = G[u][i].first;
            int w = G[u][i].second;
            Q.push(make_pair(dist[u] + w, v));
            }
        }
    }
    return dist[t];
}




/*max_bipartite_matching_hopcroft_karp*/
/**
 * Desciption: Maximum bipartite matching:  
 * Usage: max matching O(E sqrt(V))
 * Source: https://github.com/dragonslayerx 
 */

class Max_Bipartite_Match {
    vector<vector<int> > &G;
    public:

    vector<int> match, mark;
    int max_match, stamp;

    Max_Bipartite_Match(vector<vector<int> > &bipartite_graph, int v): G(bipartite_graph){
        match.resize(v);
        mark.resize(v);
        for (int i = 0; i < v; i++) {
            match[i] = -1;
            mark[i] = -1;
        }
        stamp = 0;
    }

    bool augment_path(int vertex){
        for (int i = 0; i < G[vertex].size(); i++) {
            int v = G[vertex][i];
            if (mark[v] == stamp)
                continue;
            mark[v] = stamp;
            if (match[v] == -1 || augment_path(match[v])) {
                match[v] = vertex;
                return true;
            }
        }
        return false;
    }

    int max_matching(){
        max_match = 0;
        for (int i = 0; i < G.size(); i++) {
            stamp++;
            if (augment_path(i)) max_match++;
        }
        return max_match;
    }
};


/*max_flow_network_dinic_algorithm*/

#define NN 1505
 
int cap[NN][NN];
vector<vector<int> > adj;

int q[NN], prev[NN];
int dinic( int n, int s, int t )
{
    int flow = 0;
    while( true )
    {
        // find an augmenting path
        memset( prev, -1, sizeof(prev) );
        int qf = 0, qb = 0;
        prev[q[qb++] = s] = -2;
        while( qb > qf && prev[t] == -1 )
            for( int u = q[qf++], i = 0, v; i < adj[u].size(); i++ )
                if( prev[v = adj[u][i]] == -1 && cap[u][v] )
                    prev[q[qb++] = v] = u;
 
        // see if we're done
        if( prev[t] == -1 ) break;
 
        // try finding more paths
        for( int z = 0; z < n; z++ ) if( cap[z][t] && prev[z] != -1 )
        {
            int bot = cap[z][t];
            for( int v = z, u = prev[v]; u >= 0; v = u, u = prev[v] )
                bot = min(bot, cap[u][v]);
            if( !bot ) continue;
 
            cap[z][t] -= bot;
            cap[t][z] += bot;
            for( int v = z, u = prev[v]; u >= 0; v = u, u = prev[v] )
            {
                cap[u][v] -= bot;
                cap[v][u] += bot;
            }
            flow += bot;
        }
    }
    return flow;
}

