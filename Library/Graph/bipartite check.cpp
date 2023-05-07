#include<bits/stdc++.h>
using namespace std;
#define ll long long 


//------------------------------------------------------------------------------------
/*bipartite check with bfs 1/0 */
const ll MAX_N=10e5+10;
ll n,m;
vector<ll> adj[MAX_N];
ll colors[MAX_N]; 
bool isBipartite(ll index, ll col){
    if(colors[index]!=-1){
        if(colors[index]==col) return 1;
        return 0;
    }
    colors[index] = col;
    for(auto& it: adj[index]){
        if(!isBipartite(it, 1-col)) return false;
    }
    return true;
}