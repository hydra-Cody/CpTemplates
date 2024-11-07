#include<bits/stdc++.h>
using namespace std;
#define ll long long 
//--------------------------------------------------------------------------------------------
/*
  Binary Index Tree or Fenwick Tree
  Range Query and Point Update
  all functions which are associative and reversible,
  XOR (^) . But it can't be used for GCD() or min() or max().
*/

// 1 based

const int N = 3e5 + 9;

template <class T>
struct BIT { //1-indexed
  int n; vector<T> t;
  BIT() {}
  BIT(int _n) {
    n = _n; t.assign(n + 1, 0);
  }
  T query(int i) {
    T ans = 0;
    for (; i >= 1; i -= (i & -i)) ans += t[i];
    return ans;
  }
  void upd(int i, T val) {
    if (i <= 0) return;
    for (; i <= n; i += (i & -i)) t[i] += val;
  }
  void upd(int l, int r, T val) {
    upd(l, val);
    upd(r + 1, -val);
  }
  T query(int l, int r) {
    return query(r) - query(l - 1);
  }
};


//------------------------------------------------------------------------------------
/* Lower bound on bit */
// const ll N=1e5;
const ll LOGN=20;
ll bit_search(ll v){
  ll sum = 0;
  ll pos = 0;
  
  for(ll i=LOGN; i>=0; i--)
  {
    if(pos + (1 << i) < N and sum + bit[pos + (1 << i)] < v)
    {
      sum += bit[pos + (1 << i)];
      pos += (1 << i);
    }
  }

  return pos + 1; // +1 because 'pos' will have position of largest value less than 'v'
}


//-------------------------------------------------------------
/* 
  2D RMQ in O(n*m*logn*logm),
*/
const ll N = 505, LG = 10;

ll st[N][N][LG][LG];
ll a[N][N], lg2[N];

ll yo(ll x1, ll y1, ll x2, ll y2) {
  x2++;
  y2++;
  ll a = lg2[x2 - x1], b = lg2[y2 - y1];
  return max(
         max(st[x1][y1][a][b], st[x2 - (1 << a)][y1][a][b]),
         max(st[x1][y2 - (1 << b)][a][b], st[x2 - (1 << a)][y2 - (1 << b)][a][b])
       );
}

void build(ll n, ll m) { // 0 indexed
  for (ll i = 2; i < N; i++) lg2[i] = lg2[i >> 1] + 1;
  for (ll i = 0; i < n; i++) {
    for (ll j = 0; j < m; j++) {
      st[i][j][0][0] = a[i][j];
    }
  }
  for (ll a = 0; a < LG; a++) {
    for (ll b = 0; b < LG; b++) {
      if (a + b == 0) continue;
      for (ll i = 0; i + (1 << a) <= n; i++) {
        for (ll j = 0; j + (1 << b) <= m; j++) {
          if (!a) {
            st[i][j][a][b] = max(st[i][j][a][b - 1], st[i][j + (1 << (b - 1))][a][b - 1]);
          } else {
            st[i][j][a][b] = max(st[i][j][a - 1][b], st[i + (1 << (a - 1))][j][a - 1][b]);
          }
        }
      }
    }
  }
}




//--------------------------------------------------
/*
Converting Tree to Linear Array-When a node is visited, push it to an array.
(this is also called DFS Traversal Array)
*/

// Subtree Queries- Find sum of nodes in subtree
/*
all nodes in subtree of a node will become adjacent. 
Each subtree of the tree corresponds to a continuous subarray of the
 DFS traversal array
For each node in the DFS traversal array, we need 3 things: 
 ->node-id, its subtree size and its node value
*/


vector<int> vec,cnt;
vector<vector<ll>> adj;
void dfsTArray(int node,int par){
  cnt[node]=1;
  vec.push_back(node);
  for(auto ch: adj[node]){
    if(ch!=par){ 
      dfsTArray (ch,node);
     cnt[node]+=cnt[ch];
   }
 }
}

//Path Queries from root to node
/*
• change the value of a node
• calculate the sum of values on a path from the root to a node
For each node in the DFS traversal array, we need 3 things: 
 ->node-id, subtree size and the path sum from root to that node 
 When the value of a node increases by x, 
 the sums of all nodes in its subtree increase by x. 
 use fenwick
*/




//------------------------------------------------
/*
  For all functions which are associative and reversible, 
  you can use prefix arrays to answer range queries.
*/