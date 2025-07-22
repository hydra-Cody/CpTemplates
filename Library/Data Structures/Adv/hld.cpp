#include "bits/stdc++.h"
using namespace std;

const ll N = 2e5 + 5;

ll n, q, v[N];
vector<ll> adj[N];

ll sz[N], p[N], dep[N];
ll  id[N], tp[N];


/*
	Segment Tree
struct Segtree1 {
  vector<ll> t;
  Segtree1(ll n) {
      t.assign(4*n, 0);
  }
  
  void update(ll n, ll b, ll e, ll i, ll x) {
    if (b > i || e < i) return;
    if (b == e && b == i) {
      t[n] = x;
      return;
    }
    ll mid = (b + e) >> 1, l = n << 1, r = l | 1;
    update(l, b, mid, i, x);
    update(r, mid + 1, e, i, x);
    t[n] = t[l]^ t[r];
  }
  ll query(ll n, ll b, ll e, ll i, ll j) {
    if (b > j || e < i) return 0;
    if (b >= i && e <= j) return t[n];
    ll mid = (b + e) >> 1, l = n << 1, r = l | 1;
    ll L = query(l, b, mid, i, j);
    ll R = query(r, mid + 1, e, i, j);
    return L^ R;
  }
}st(N+1);

*/

/*

	Spare table
const ll D = 19;
const ll S = (1 << D);
ll st[S]
void update(ll idx, ll val) {
	st[idx += n] = val;
	for (idx /= 2; idx; idx /= 2) st[idx] = max(st[2 * idx], st[2 * idx + 1]);
}

ll query(ll lo, ll hi) {
	ll ra = 0, rb = 0;
	for (lo += n, hi += n + 1; lo < hi; lo /= 2, hi /= 2) {
		if (lo & 1) ra = max(ra, st[lo++]);
		if (hi & 1) rb = max(rb, st[--hi]);
	}
	return max(ra, rb);
}

*/

ll dfs_sz(ll cur, ll par) {
	sz[cur] = 1;
	p[cur] = par;
	for (ll chi : adj[cur]) {
		if (chi == par) continue;
		dep[chi] = dep[cur] + 1;
		p[chi] = cur;
		sz[cur] += dfs_sz(chi, cur);
	}
	return sz[cur];
}

ll ct = 1;

void dfs_hld(ll cur, ll par, ll top) {
	id[cur] = ct++;
	tp[cur] = top;
	update(id[cur], v[cur]);
	ll h_chi = -1, h_sz = -1;
	for (ll chi : adj[cur]) {
		if (chi == par) continue;
		if (sz[chi] > h_sz) {
			h_sz = sz[chi];
			h_chi = chi;
		}
	}
	if (h_chi == -1) return;
	dfs_hld(h_chi, cur, top);
	for (ll chi : adj[cur]) {
		if (chi == par || chi == h_chi) continue;
		dfs_hld(chi, cur, chi);
	}
}

ll path(ll x, ll y) {
	ll ret = 0;
	while (tp[x] != tp[y]) {
		if (dep[tp[x]] < dep[tp[y]]) swap(x, y);
		ret = max(ret, query(id[tp[x]], id[x]));
		x = p[tp[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	ret = max(ret, query(id[x], id[y]));
	return ret;
}

int main() {
	scanf("%d%d", &n, &q);
	for (ll i = 1; i <= n; i++) scanf("%d", &v[i]);
	for (ll i = 2; i <= n; i++) {
		ll a, b;
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs_sz(1, 1);
	dfs_hld(1, 1, 1);
	while (q--) {
		ll t;
		scanf("%d", &t);
		if (t == 1) {
			ll s, x;
			scanf("%d%d", &s, &x);
			v[s] = x;
			update(id[s], v[s]);
		} else {
			ll a, b;
			scanf("%d%d", &a, &b);
			ll res = path(a, b);
			prllf("%d ", res);
		}
	}
}