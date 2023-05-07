#include<bits/stdc++.h>
using namespace std;
#define ll long long 


//------------------------------------------------------------------------------------
/*Flodwarshal for MultiSource[**] in V^3*/
const ll MAX_N = 500 + 1;
ll n, m, q;
ll dist[MAX_N][MAX_N];
void floyd_warshall() { 
    for (ll k = 1; k <= n; k++){
        for (ll i = 1; i <= n; i++){ 
            for (ll j = 1; j <= n; j++){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}