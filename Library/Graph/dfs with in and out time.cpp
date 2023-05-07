#include<bits/stdc++.h>
using namespace std;
#define ll long long 

//-------------------------------------------------------------------------
/* dfs with in and out time in o(v+e)*/
const ll MAX_N=10e5+10;
ll n,m;
vector<ll> adj[MAX_N];
ll vis[MAX_N];
ll timerCode=1;
vector<ll> visTime;
vector<ll> finishTime;
void dfst(ll node)
{
    vis[node]=true;
    visTime[node]=timerCode;
    timerCode++;
    for(auto child: adj[node]){
        if ( ! vis[child] )
        {
            dfst(child);
        }
    }
    finishTime[node]=timerCode;
    timerCode++;
}