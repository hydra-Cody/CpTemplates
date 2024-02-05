#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007


//-------------------------------------------------------------------------
/*
    Segment Tree Persistent.
*/
const int N = 1e5 + 9;

struct PST {
#define lc t[cur].l
#define rc t[cur].r
  struct node {
    int l = 0, r = 0, val = 0;
  } t[20 * N];
  int T = 0;
  int build(int b, int e) {
    int cur = ++T;
    if(b == e) return cur;
    int mid = b + e >> 1;
    lc = build(b, mid);
    rc = build(mid + 1, e);
    t[cur].val = t[lc].val + t[rc].val;
    return cur;
  }
  int upd(int pre, int b, int e, int i, int v) {
    int cur = ++T;
    t[cur] = t[pre];
    if(b == e) {
      t[cur].val += v;
      return cur;
    }
    int mid = b + e >> 1;
    if(i <= mid) {
      rc = t[pre].r;
      lc = upd(t[pre].l, b, mid, i, v);
    } else {
      lc = t[pre].l;
      rc = upd(t[pre].r, mid + 1, e, i, v);
    }
    t[cur].val = t[lc].val + t[rc].val;
    return cur;
  }
  int query(int pre, int cur, int b, int e, int k) {
    if(b == e) return b;
    int cnt = t[lc].val - t[t[pre].l].val;
    int mid = b + e >> 1;
    if(cnt >= k) return query(t[pre].l, lc, b, mid, k);
    else return query(t[pre].r, rc, mid + 1, e, k - cnt);
  }
} t;

//the code returns k-th number in a range l to r if the range were sorted
int V[N], root[N], a[N];
int32_t main() {
  map<int, int>mp;
  int n, q;
  cin >> n >> q;
  for(int i = 1; i <= n; i++) cin >> a[i], mp[a[i]];
  int c = 0;
  for(auto x : mp) mp[x.first] = ++c, V[c] = x.first;
  root[0] = t.build(1, n);
  for(int i = 1; i <= n; i++) {
    root[i] = t.upd(root[i - 1], 1, n, mp[a[i]], 1);
  }
  while(q--) {
    int l, r, k;
    cin >> l >> r >> k;
    cout << V[t.query(root[l - 1], root[r], 1, n, k)] << '\n';
  }
  return 0;
}


//----------------------------------------------------------------
/*
	Persistent Array
*/

template<typename T>
struct PersistentArray { // 0-indexed
  struct node {
    node* l, * r; T x;
  };
  int n = 1;
  vector<node*> root;
  int build(vector<T> v) {
    while (n < v.size()) n <<= 1;
    root.push_back(build(0, n - 1, v));
    return root.size() - 1;
  }
  node* build(int l, int r, vector<T>& v) {
    node* cur = new node();
    if (l == r) {
      if (l < v.size()) cur -> x = v[l];
      else cur -> x = 0;
    }
    else {
      cur -> l = build(l, (l + r) >> 1, v);
      cur -> r = build(((l + r) >> 1) + 1, r, v);
    }
    return cur;
  }
  // get the ith value of the rth array
  T get_val(int r, int i) {
    return get_val(root[r], i, 0, n - 1);
  }
  T get_val(node* cur, int i, int l, int r) {
    if (l == r) return cur -> x;
    if (i <= ((l + r) >> 1)) return get_val(cur -> l, i, l, (l + r) >> 1);
    else return get_val(cur -> r, i, ((l + r) >> 1) + 1, r);
  }
  // update the ith value if the rth array by x and return the new root of the array
  int upd(int r, int i, T x) {
    root.push_back(upd(root[r], i, x, 0, n - 1));
    return root.size() - 1;
  }
  node* upd(node* pre, int i, T x, int l, int r) {
    node* cur = new node();
    if (l == r){
      cur -> x = x;
    }
    else {
      if (i <= ((l + r) >> 1)) {
        cur -> l = upd(pre -> l, i, x, l, (l + r) >> 1);
        cur -> r = pre -> r;
      }
      else {
        cur -> l = pre -> l;
        cur -> r = upd(pre -> r, i, x, ((l + r) >> 1) + 1, r);
      }
    }
    return cur;
  }
};

template<typename T>
struct PersistentQueue {
  int cur = 0; // queue ids
  vector<int> L, R;
  PersistentArray<T> st;
  PersistentQueue() {}
  PersistentQueue(int q) { // max size of a queue
    L.assign(q, 0);
    R.assign(q, 0);
    st.build(vector<T>(q, 0));
    cur++;
  }
  void push(int r, T x) { // push x at the end of the rth queue
    st.upd(r, R[r], x);
    L[cur] = L[r];
    R[cur] = R[r] + 1;
    cur++;
  }
  T pop(int r) { // pops the top element of the rth queue and returns the popped element
    st.upd(r, L[r], 0);
    L[cur] = L[r] + 1;
    R[cur] = R[r];
    cur++;
    return st.get_val(r, L[r]);
  }
};

int32_t main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int q; cin >> q;
  PersistentQueue<int> Q(q + 1);
  while (q--) {
    int ty; cin >> ty;
    if (ty == 0) {
      int id, x; cin >> id >> x;
      Q.push(id + 1, x);
    }
    else {
      int id; cin >> id;
      cout << Q.pop(id + 1) << '\n';
    }
  }
}
// https://judge.yosupo.jp/problem/persistent_queue