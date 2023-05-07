#include <bits/stdc++.h>

using namespace std;

int n;
vector<vector<int>> g, gt;
vector<bool> visited;
vector<int> order, comp;
vector<bool> assignment;

void dfs1(int v) {
    visited[v] = true;
    for (int u : g[v]) {
        if (!visited[u])
            dfs1(u);
    }
    order.push_back(v);
}

void dfs2(int v, int id) {
    comp[v] = id;
    for (int u : gt[v]) {
        if (comp[u] == -1)
            dfs2(u, id);
    }
}

/* This function will return true if there is a possible solution,
 * otherwise return false */
bool solve() {
	//2-SAT Algorithm
    visited.assign(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs1(i);
    }

	// Find SCCs (Give an id to each component)
    comp.assign(n, -1);
    reverse(order.begin(),order.end()); 
    int id=0;
    
    for (auto v: order) {
        if (comp[v] == -1)
            dfs2(v, id++);
    }

    assignment.assign(n / 2, false);
    for (int i = 0; i < n; i += 2) {
        if (comp[i] == comp[i + 1])
            return false; // No solution possible
        assignment[i / 2] = comp[i] > comp[i + 1];
    }
    
    return true;
}

int main()
{
	// Take n/2 (no. of boolean variables) as input
	
	// Take input of graph g with n vertices
	// For any variable x_k:
	// (i) vertex 2k => x_k
	// (i) vertex 2k+1 => not(x_k)

	// Store reverse of graph in gt
	solve();
	
	return 0;
}