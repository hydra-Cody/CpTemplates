#include<bits/stdc++.h>
using namespace std;
#define ll long long 

//--------------------------------------------------------------------------------------
/*dsu with rank and path comp[***] in o(1)*/

struct DSU {
  vector<ll> par, rnk, sz;
  ll c;
  DSU(ll n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 1), c(n) {
    for (ll i = 1; i <= n; ++i){
      par[i] = i;
    }
  }
  ll find(ll i) {
    if(par[i]==i)return i;
    ll p=find(par[i]);
    return par[i] = p;
  }
  bool same(ll i, ll j) {
    return find(i) == find(j);
  }
  ll get_size(ll i) {
    return sz[find(i)];
  }
  ll count() {
    return c;    //connected components
  }
  ll merge(ll i, ll j) {
    if ((i = find(i)) == (j = find(j))) return -1;
    else --c;
    if (rnk[i] > rnk[j]) swap(i, j);
    par[i] = j;
    sz[j] += sz[i];
    if (rnk[i] == rnk[j]) rnk[j]++;
    return j;
  }
};
//---------------------------------------------------------------------------------------
/*
  weight dsu
*/

//-----------------------------------------------------------------------

/*
  DSU On Tree
*/

const int N = 1e5 + 9;
vector<int> g[N];
int ans[N], col[N], sz[N], cnt[N];
bool big[N];
void dfs(int u, int p) {
  sz[u] = 1;
  for (auto v : g[u]) {
    if (v == p) continue;
    dfs(v, u);
    sz[u] += sz[v];
  }
}
void add(int u, int p, int x) {
  cnt[col[u]] += x;
  for (auto v : g[u]) {
    if (v == p || big[v] == 1) continue;
    add(v, u, x);
  }
}
void dsu(int u, int p, bool keep) {
  int bigchild = -1, mx = -1;
  for (auto v : g[u]) {
    if (v == p) continue;
    if (sz[v] > mx) mx = sz[v], bigchild = v;
  }
  for (auto v : g[u]) {
    if (v == p || v == bigchild) continue;
    dsu(v, u, 0);
  }
  if (bigchild != -1) dsu(bigchild, u, 1), big[bigchild] = 1;
  add(u, p, 1);
  ans[u] = cnt[u];
  if (bigchild != -1) big[bigchild] = 0;
  if (keep == 0) add(u, p, -1);
}




//----------------------------------------------------------------------------
/*
  DSU with ROllbacks
*/

// const int N = 2e5 + 9;

struct DSU1 {
  vector<int> par, sz, w;
  vector<array<int, 3>> op;
  bool flag;
  DSU1() {}
  DSU1(int n) {
    par.resize(n + 1);
    sz.resize(n + 1);
    w.resize(n + 1);
    flag = true;
    for (int i = 1; i <= n; i++) {
      par[i] = i; 
      sz[i] = 1; w[i] = 0;
    }
  }
  bool is_bipartite() {
    return flag;
  }
  pair<int, int> find(int u) {
    int ans = 0;
    while (par[u] != u)  {
      ans ^= w[u];
      u = par[u];
    }
    return make_pair(u, ans);
  }
  bool merge(int u, int v) {
    auto pu = find(u), pv = find(v);
    u = pu.first;
    v = pv.first;
    int last = flag;
    int z = pu.second ^ pv.second ^ 1;
    if (u == v) {
      if (z) {
        flag = false;
      }
      op.push_back({-1, -1, last});
      return false;
    }
    if (sz[u] > sz[v]) {
      swap(u, v);
    }
    op.push_back({u, w[u], last});
    par[u] = v;
    w[u] = z;
    sz[v] += sz[u];
    return true;
  }
  void undo() {
    assert(!op.empty());
    auto x = op.back();
    flag = x[2];
    int u = x[0];
    if (u != -1) {
      sz[par[u]] -= sz[u];
      par[u] = u;
      w[u] = x[1];
    }
    op.pop_back();
  }
};
struct update {
  bool type;
  int x, y;
  update(int _x, int _y) {
    x = _x; y = _y;
    type = 0;
  }
};
struct DSUQueue {
  DSU1 D;
  vector<update> S;
  DSUQueue(int n) {
    D = DSU1(n);
  }
  void push(update u) {
    D.merge(u.x, u.y);
    S.push_back(u);
  }
  void pop() {
    assert(!S.empty());
    vector<update> t[2];
    do {
      t[S.back().type].push_back(S.back());
      S.pop_back();
      D.undo();
    } while (t[1].size() < t[0].size() && !S.empty());
    if (t[1].empty()) {
      for (auto &u : t[0]) {
        u.type = 1;
        push(u);
      }
    } 
    else {
      for (int i : {0, 1}) {
        reverse(t[i].begin(), t[i].end());
        for (auto &u : t[i]) push(u);
      }
    }
    S.pop_back();
    D.undo();
  }
  bool is_bipartite() {
    return D.is_bipartite();
  }
};
int u[N], v[N], a[N];
void  chal() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m, q; cin >> n >> m >> q;
  DSU P(n);
  for (int i = 1; i <= m; i++) {
    cin >> u[i] >> v[i];
  }
  DSUQueue D(n);
  for (int i = 1; i <= m; i++) {
    D.push(update(u[i], v[i]));
  }
  for (int l = 1, r = 1; l <= m; l++) {
    while (r < l || (!D.is_bipartite() && r <= m)) {
      D.pop();
      ++r;
    }
    if (D.is_bipartite()) a[l] = r - 1;
    else a[l] = m + 1;
    D.push(update(u[l], v[l]));
  }
  while (q--) {
    int l, r; cin >> l >> r;
    if (a[l] <= r) {
      cout << "NO\n";
    }
    else {
      cout << "YES\n";
    }
  }
}

//-----------------------------------------------------------------------------------
/*
  Small to large merging techinq
*/


//-------------------------------------------------------------------------------------
/*dsu with rank with only rank comp*/