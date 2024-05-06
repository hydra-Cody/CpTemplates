#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007

//--------------------------------------------------------------------------------------
/*
	Mo Algorithum (Offline algorithm)
*/
//O((N + Q) * sqrt(N))

const ll N = 1e6 + 9, B = 440;

struct query {
  ll l, r, id;
  bool operator < (const query &x) const {
    if(l / B == x.l / B) return ((l / B) & 1) ? r > x.r : r < x.r;
    return l / B < x.l / B;
  }
} Q[N];
ll cnt[N], a[N];
ll sum;
inline void add_left(ll i) {
  ll x = a[i];
  sum += 1LL * (cnt[x] + cnt[x] + 1) * x;
  ++cnt[x];
}
inline void add_right(ll i) {
  ll x = a[i];
  sum += 1LL * (cnt[x] + cnt[x] + 1) * x;
  ++cnt[x];
}
inline void rem_left(ll i) {
  ll x = a[i];
  sum -= 1LL * (cnt[x] + cnt[x] - 1) * x;
  --cnt[x];
}
inline void rem_right(ll i) {
  ll x = a[i];
  sum -= 1LL * (cnt[x] + cnt[x] - 1) * x;
  --cnt[x];
}
long long ans[N];
void chal2() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  ll n, q;
  cin >> n >> q;
  for(ll i = 1; i <= n; i++) cin >> a[i];
  for(ll i = 1; i <= q; i++) {
    cin >> Q[i].l >> Q[i].r;
    Q[i].id = i;
  }
  sort(Q + 1, Q + q + 1);
  ll l = 1, r = 0;
  for(ll i = 1; i <= q; i++) {
    ll L = Q[i].l, R = Q[i].r;
    if(R < l) {
      while (l > L) add_left(--l);
      while (l < L) rem_left(l++);
      while (r < R) add_right(++r);
      while (r > R) rem_right(r--);
    } else {
      while (r < R) add_right(++r);
      while (r > R) rem_right(r--);
      while (l > L) add_left(--l);
      while (l < L) rem_left(l++);
    }
    ans[Q[i].id] = sum;
  }
  for(ll i = 1; i <= q; i++) cout << ans[i] << '\n';

}


//--------------------------------------------------------------------------
/*
	Square Root Decomposition
-Low constraints (n=5.10^4) and high time limits (greater than2s)
*/
struct Sqrt {
	ll block_size;
	vector<ll> nums;
	vector<ll> blocks;
	Sqrt(ll sqrtn, vector<ll> &arr) : block_size(sqrtn), blocks(sqrtn, 0) {
		nums = arr;
		for (ll i = 0; i < nums.size(); i++) {
			blocks[i / block_size] += nums[i];
		}
	}

	void update(ll x, ll v) {
		blocks[x / block_size] -= nums[x];
		nums[x] = v;
		blocks[x / block_size] += nums[x];
	}

	ll query(ll r) {
		ll res = 0;
		for (ll i = 0; i < r / block_size; i++) { res += blocks[i]; }
		for (ll i = (r / block_size) * block_size; i < r; i++) {
			res += nums[i];
		}
		return res;
	}

	ll query(ll l, ll r) { return query(r) - query(l - 1); }
};
/*
    [l,r]
    Sqrt sq((ll)ceil(sqrt(n)), arr);
    sq.update(l, v);
    sq.query(l, r); 
*/


//-------------------------------------------------------------------------

/*
	Using centroid Decomposition of a tree
	get_centroid- log(n) 
*/
const ll MN = 200010;
bool r[MN];
ll s[MN];
vector<vector<ll>> g;
ll dfs(ll n, ll p = 0) {
	s[n] = 1;
	for (ll x : g[n])
		if (x != p && !r[x]) s[n] += dfs(x, n);
	return s[n];
}
ll get_centroid(ll n,ll  ms,ll p = 0){
	for (ll x : g[n])
		if (x != p && !r[x])
			if (s[x] * 2 > ms) return get_centroid(x, ms, n);
	return n;
}
void centroid(ll n = 1) {
	ll C = get_centroid(n, dfs(n));

	// do something

	r[C] = 1;
	for (ll x : g[C])
		if (!r[x]) centroid(x);
}

//------------------------------------------------------------------------

/* 2 Sets*/

struct two_sat {
    ll n;
    vector<vector<ll>> g, gr;
    vector<ll> comp, topological_order, answer;
    vector<bool> vis;
    two_sat() {}
    two_sat(ll _n) { init(_n); }
    void init(ll _n) {
        n = _n;
        g.assign(2 * n, vector<ll>());
        gr.assign(2 * n, vector<ll>());
        comp.resize(2 * n);
        vis.resize(2 * n);
        answer.resize(2 * n);
    }
    void add_edge(ll u, ll v) {
        g[u].push_back(v);
        gr[v].push_back(u);
    }
    // At least one of them is true
    void add_clause_or(ll i, bool f, ll j, bool g) {
        add_edge(i + (f ? n : 0), j + (g ? 0 : n));
        add_edge(j + (g ? n : 0), i + (f ? 0 : n));
    }
    // Only one of them is true
    void add_clause_xor(ll i, bool f, ll j, bool g) {
        add_clause_or(i, f, j, g);
        add_clause_or(i, !f, j, !g);
    }
        // Both of them have the same value
    void add_clause_and(ll i, bool f, ll j, bool g) {
        add_clause_xor(i, !f, j, g);
    }
    void dfs(ll u) {
        vis[u] = true;

        for (const auto &v : g[u])
            if (!vis[v]) dfs(v);

        topological_order.push_back(u);
    }
    void scc(ll u, ll id) {
        vis[u] = true;
        comp[u] = id;

        for (const auto &v : gr[u])
            if (!vis[v]) scc(v, id);
    }
    bool satisfiable() {
        fill(vis.begin(), vis.end(), false);

        for (ll i = 0; i < 2 * n; i++)
            if (!vis[i]) dfs(i);

        fill(vis.begin(), vis.end(), false);
        reverse(topological_order.begin(), topological_order.end());

        ll id = 0;
        for (const auto &v : topological_order)
            if (!vis[v]) scc(v, id++);
        for (ll i = 0; i < n; i++) {
            if (comp[i] == comp[i + n]) return false;
            answer[i] = (comp[i] > comp[i + n] ? 1 : 0);
        }

        return true;
    }
};
//----------------------------------------------------------------------------