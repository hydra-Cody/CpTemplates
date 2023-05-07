#include<bits/stdc++.h>
using namespace std;
#define ll long long 



//------------------------------------------------------------------------------
/*Treap*/

// Treap data structure supporting split and merge function
// Problem link: https://codeforces.com/gym/102787/problem/A

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct tdata {
    int val, pri, sz;
    tdata *ln, *rn;
    tdata(int val): val(val), pri(rng()), sz(1), ln(), rn() {} 
};
int sz(tdata *node) {return node ? node->sz : 0;}
void propagate(tdata *node) {
    if (!node) return;
}
void combine(tdata *node) {
    if (!node) return;
    propagate(node->ln); propagate(node->rn);
    node->sz = sz(node->ln) + sz(node->rn) + 1;
}
void heapify(tdata *node) {
    if (!node) return;
    auto mx = node;
    if (node->ln && node->ln->pri > node->pri) mx = node;
    if (node->rn && node->rn->pri > node->pri) mx = node;
    if (node != mx) {
        swap(node->pri, mx->pri);
        heapify(mx);
    }
}
tdata* build(vector<int> &arr, int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;
    auto node = new tdata(arr[mid]);
    node->ln = build(arr, start, mid - 1);
    node->rn = build(arr, mid + 1, end);
    heapify(node); combine(node);
    return node;
}
void split(tdata *node, tdata *&ln, tdata *&rn, int k) { // k nodes to ln
    propagate(node);
    if (!node) {
        ln = rn = NULL;
        return;
    }
    if (sz(node->ln) >= k) split(node->ln, ln, node->ln, k), rn = node;
    else split(node->rn, node->rn, rn, k - sz(node->ln) - 1), ln = node;
    combine(node);
}
void merge(tdata *&node, tdata *ln, tdata *rn) {
    propagate(ln); propagate(rn);
    if (!ln || !rn) {
        node = ln ? ln : rn;
        return;
    }
    if (ln->pri > rn->pri) merge(ln->rn, ln->rn, rn), node = ln;
    else merge(rn->ln, ln, rn->ln), node = rn;
    combine(node);
}
void print(tdata *node) {
    if (!node) return;
    print(node->ln);
    cout << node->val << " ";
    print(node->rn);
}

void solve() {
    int n; cin >> n;
    vector<int> arr(n);
    iota(arr.begin(), arr.end(), 1);
    auto tr = build(arr, 0, n - 1);
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b; 
        if (a >= b) continue;
        int len = min(b - a, n - b + 1);
        tdata *p1, *p2, *p3, *p4, *p5;
        split(tr, p3, p4, b - 1);
        split(p4, p4, p5, len);
        split(p3, p1, p2, a - 1);
        split(p2, p2, p3, len);
        merge(tr, p1, p4);
        merge(tr, tr, p3);
        merge(tr, tr, p2);
        merge(tr, tr, p5);
    }
    print(tr);
    cout << "\n";
}

/*SQRT*/
// Mo's Algorithm for answering offline queries
// Time complexity: O(n*sqrt(n))
// Problem link: https://cses.fi/problemset/task/1734

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 2e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

struct query{
    int SQRT = 500;
    int l, r, id;
    bool operator< (query b) {
        query a = *this;
        return ar<int,2>{a.l/SQRT, a.r} < ar<int,2>{b.l/SQRT, b.r};
    }
};

int n, q, arr[MAX_N], ans[MAX_N], cnt[MAX_N], cur;
query qs[MAX_N];

void add(int idx) {
    if (cnt[arr[idx]] == 0) cur++;
    cnt[arr[idx]]++;
}
 
void subtract(int idx) {
    if (cnt[arr[idx]] == 1) cur--;
    cnt[arr[idx]]--;
}

// compress used values from 1e9 to 2e5 
void compress() {
    map<int, int> mp;
    for (int i = 1; i <= n; i++) 
        mp[arr[i]] = i;
    for (int i = 1; i <= n; i++) 
        arr[i] = mp[arr[i]];
}

void mo_algo() {
    sort(qs + 1, qs + n + 1);
    int curL = 0, curR = 0;
    add(0);
    for (int i = 1; i <= n; i++) {
        int L = qs[i].l, R = qs[i].r;
        while (curL < L) subtract(curL++);
        while (curL > L) add(--curL);
        while (curR < R) add(++curR);
        while (curR > R) subtract(curR--);
        ans[qs[i].id] = cur;
    }
}

void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    compress();
    for (int i = 1; i <= q; i++) {
        cin >> qs[i].l >> qs[i].r;
        qs[i].id = i;
    }
    mo_algo();
    for (int i = 1; i <= q; i++) 
        cout << ans[i] << "\n";
}

/*Trie*/
// Prefix tree: storing strings based on their common prefix
// Problem link: https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ffc7/00000000001d3ff3

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

const int MAX_S = 2e6; // total number of characters in all strings
const int MAX_C = 26; // total number of distinct characters 

int N, K, num, ans;
int trie[MAX_S][MAX_C], cnt[MAX_S];

// initially all values in trie are 0 (not allocated)
// cnt[u] = number of strings that end at node u in the trie => this is to mark the end of a string in the trie
// "num" stores the total number of allocated nodes in the trie

void dfs(int u = 0, int d = 0) {
    for (int v = 0; v < 26; v++) {
        if (trie[u][v]) {
            dfs(trie[u][v], d + 1);
            // now cnt[u] stores the total number of strings that has a common prefix from the root to node u
            cnt[u] += cnt[trie[u][v]];
        }
    }
    // greedily dividing into groups of K
    while (cnt[u] >= K) { 
        cnt[u] -= K;
        ans += d;
    }
}

// insert a string into the trie
void insert(string s) {
    // start at the root node
    int u = 0; 
    for (char c : s) {
        // if this node has not been allocated, then allocate the node and increase num by 1
        if (!trie[u][c - 'A']) trie[u][c - 'A'] = ++num; 
        // move to the next node
        u = trie[u][c - 'A']; 
    }
    // mark the end of string
    cnt[u]++; 
}

// check if a string exist in the trie
bool search(string s) { 
    int u = 0;
    for (char c : s) {
        if (!trie[u][c - 'A']) return false;
        u = trie[u][c - 'A'];
    }
    return cnt[u] > 0;
}

void solve() {
    // need to reset after each test case
    ans = 0; num = 0;
    memset(trie, 0, sizeof trie);
    memset(cnt, 0, sizeof cnt);

    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        string s; cin >> s;
        insert(s);
    }
    dfs();
    cout << ans << "\n";
}

/*Suffix Array*/
// Suffix Array: storing all suffixes of a string, useful for many string-related problems
// Problem link: https://www.spoj.com/problems/SUBST1/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;



void solve() {
    string s; cin >> s; s += "$";
    int n = s.size();
    vector<int> p(n), c(n);
    vector<pair<char,int>> a(n);
    for (int i = 0; i < n; i++) a[i] = {s[i], i};
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) p[i] = a[i].second;
    for (int i = 1; i < n; i++) c[p[i]] = (a[i].first == a[i - 1].first) ? c[p[i - 1]] : c[p[i - 1]] + 1;
    for (int k = 0; (1 << k) < n; k++) {
        for (int i = 0; i < n; i++) p[i] = (p[i] - (1 << k) + n) % n;
        vector<int> np(n), nc(n), cnt(n), pos(n);
        for (int x : p) cnt[c[x]]++;
        for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
        for (int x : p) np[pos[c[x]]++] = x;
        p = np;
        for (int i = 1; i < n; i++) {
            pair<int,int> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
            pair<int,int> pre = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            nc[p[i]] = (cur == pre) ? nc[p[i - 1]] : nc[p[i - 1]] + 1;             
        }
        c = nc;
    } 
    vector<int> lcp(n);
    for (int i = 0, k = 0; i < n - 1; i++, k = max(k - 1, 0)) {
        int pi = c[i], j = p[pi - 1];
        while (s[i + k] == s[j + k]) k++;
        lcp[pi] = k;
    }
    
    ll ans = 0;
    for (int i = 0; i < n; i++) ans += (n - p[i] - 1) - lcp[i]; 
    cout << ans << "\n";
}

/*PBDS*/
// Policy based data structures C++ STL
// order_of_key(k): number of elements less than k
// find_by_order(k): returns the iterator of the k-th element in a set (0-index)
// Time complexity: O(logn) for both
// Problem link: https://cses.fi/problemset/task/1144

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

// 5 lines
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class K, class V> using ordered_map = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    int n, q; cin >> n >> q;
    int arr[n];
    ordered_set<pair<int,int>> os;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        os.insert({arr[i], i});
    }
    while (q--) {
        char c; cin >> c;
        if (c == '!') {
            int k, x; cin >> k >> x; k--;
            os.erase(os.find_by_order(os.order_of_key({arr[k], k})));
            os.insert({x, k});
            arr[k] = x;
        }
        else {
            int a, b; cin >> a >> b;
            cout << os.order_of_key({b + 1, 0}) - os.order_of_key({a, 0}) << "\n";
        }
    }
}

/*HLD*/
// Heavy-light decomposition (HLD) is a data structure to answer queries and update values on tree
// Splitting the trees into separate paths that allows us to use another data structure such as segment tree on a tree
// As we decompose the tree, we have enough information to build a lca function (which will be useful as an intermediate step for many types of queries)
// For this example, we will answer maximum edge cost query on the path between two nodes
// Problem link: https://www.spoj.com/problems/QTREE/

// Each edge is represented by the node that is further away to the root
// => Each node is associated only one unique edge, except the root node

// sz[u] = size of the subtree of u
// par[u] = parent node of u
// dep[u] = distance of u from the root

// chainNum = number of decomposed chains
// chainSize[s] = number of nodes in chain s
// chainHead[s] = the node closest to the root in chain s
// chainId[u] = the chain that node u belongs to
// chainPos[u] = the position of node u in the chain it belongs to (aka chainInd[u])

// adj: adjacency list
// el: edge list

// arr: array storing edge costs based on HLD
// pos: position of edges based on HLD
// st: segment tree

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e4 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

struct segtree { 
    struct tdata {
        ll mx;
        tdata(): mx() {}
        tdata(ll val): mx(val) {}
        tdata(tdata l, tdata r): mx(max(l.mx, r.mx)) {}
    };
    int ln(int node) {return 2 * node;}
    int rn(int node) {return 2 * node + 1;}
    int n; vector<tdata> st;
    void init(int _n) {
        n = _n;
        st.resize(4 * n);
    }
    void init(vector<int> &arr) {
        n = arr.size();
        st.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }
    void apply(int node, ll val) {
        st[node].mx = val;
    }
    void combine(int node) {
        st[node].mx = max(st[ln(node)].mx, st[rn(node)].mx);
    }
    void build(vector<int> &arr, int node, int start, int end) {
        if (start == end) {
            st[node] = tdata(arr[start]);
            return;
        }
        int mid = (start + end) / 2;
        build(arr, ln(node), start, mid);
        build(arr, rn(node), mid + 1, end);
        combine(node);
    }
    void update(int node, int start, int end, int idx, ll val) {
        if (start == end) {
            apply(node, val);
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) update(ln(node), start, mid, idx, val);
        else update(rn(node), mid + 1, end, idx, val);
        combine(node);
    }
    tdata query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return tdata();
        if (l <= start && end <= r) return st[node];
        int mid = (start + end) / 2;
        return tdata(query(ln(node), start, mid, l, r), query(rn(node), mid + 1, end, l, r));
    }
    void update(int idx, ll val) {update(1, 0, n - 1, idx, val);}
    tdata query(int l, int r) {return query(1, 0, n - 1, l, r);}
};

int n, cnt;
int sz[MAX_N], dep[MAX_N], par[MAX_N], child[MAX_N];
int chainNum, chainHead[MAX_N], chainSize[MAX_N], chainId[MAX_N], chainPos[MAX_N];
vector<int> arr; int pos[MAX_N];
vector<ar<int,2>> adj[MAX_N], el;
segtree st;
 
void reset() {
    memset(chainHead, -1, sizeof chainHead);
    arr.clear();
    for (int i = 1; i <= n; i++) adj[i].clear();
    el.clear();
    chainNum = cnt = 0;
}
 
void dfs(int u, int p = 0, int d = 0) {
    sz[u] = 1;
    dep[u] = d;
    par[u] = p;
    int mx = 0;
    for (auto [v, w] : adj[u]) {
        if (v != p) {
            dfs(v, u, d + 1);
            sz[u] += sz[v];
            if (sz[v] > mx) mx = sz[v], child[u] = v;
        }
    }
}

void hld(int u, int x = -INF) {
    if (chainHead[chainNum] == -1) chainHead[chainNum] = u;
    chainId[u] = chainNum;
    chainPos[u] = chainSize[chainNum]++;
    arr.push_back(x);
    pos[u] = cnt++;
    for (auto [v, w] : adj[u]) {
        if (v != par[u] && v == child[u]) {
            hld(v, w);
        }
    }
    for (auto [v, w] : adj[u]) {
        if (v != par[u] && v != child[u]) {
            chainNum++, hld(v, w);
        }
    }
}
 
int lca(int u, int v) {
    while (chainId[u] != chainId[v]) {
        if (dep[chainHead[chainId[u]]] > dep[chainHead[chainId[v]]]) u = par[chainHead[chainId[u]]];
        else v = par[chainHead[chainId[v]]];
    }
    return dep[u] > dep[v] ? v : u;
}
 
ll query_up(int u, int m) {
    ll res = 0;
    while (true) {
        if (u == m) break;
        if (chainId[u] == chainId[m]) {
            res = max(res, st.query(pos[m] + 1, pos[u]).mx);
            break;
        }
        res = max(res, st.query(pos[chainHead[chainId[u]]], pos[u]).mx);
        u = par[chainHead[chainId[u]]];        
    }
    return res;
}
 
ll query(int u, int v) {
    int m = lca(u, v);
    return max(query_up(u, m), query_up(v, m));
}
 
void update(int i, int x) {
    auto [u, v] = el[i];
    if (dep[u] < dep[v]) swap(u, v);
    st.update(pos[u], x);
}
 
void solve() {
    cin >> n;
    reset();
    for (int i = 0; i < n - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        el.push_back({u, v});
    }
    dfs(1);
    hld(1);
    st.init(arr);
    while (true) {
        string t; cin >> t;
        if (t == "CHANGE") {
            int i, x; cin >> i >> x; i--;
            update(i, x);
        }
        else if (t == "QUERY") {
            int u, v; cin >> u >> v;
            cout << query(u, v) << "\n";
        }
        else return;
    }
}



/*heap_using_multiset_max_min_insert_erase_update*/
/**
 * Description: A MaxMin priority queue that supports erase operation.
 * Usage: insert O(lg(N)), erase O(lg(N)), maxElement O(lg(N)), minElement O(lg(N)) 
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
#include <map>
#include <set>
using namespace std;

template<typename Tk, typename Tv>
class Heap {
    map<Tk, Tv> lookup;
    multiset< pair<Tv, Tk> > prQ;
public:
    void insert(Tk key, Tv val) {
        lookup[key] = val;
        prQ.insert(make_pair(val, key));
    }

    void update(Tk key, Tv val) {
        typename multiset<Tv>::iterator it = prQ.find(make_pair(lookup[key], key));
        prQ.erase(it);
        lookup[key] = val;
        prQ.insert(make_pair(val, key));
    }

    void erase(Tk key) {
        typename multiset<Tv>::iterator it = prQ.find(make_pair(lookup[key], key));
        prQ.erase(it);
        lookup.erase(key);
    }

    pair<Tv, Tk> maxElement() {
        return *prQ.rbegin();
    }

    pair<Tv, Tk> minElement() {
        return *prQ.begin();
    }
};

int main() {
    Heap<int,int> H;
    H.insert(1, 5);
    H.insert(2, 4);
    H.insert(3, 9);
    H.insert(4, 7);
    cout << H.minElement().first << " " << H.minElement().second << endl;
}

/*binary_trie_max_xor*/
/**
 * Max Xor queries : Find maximum xor of an integer with a set of integers
 * Usage: insert O(lg(N)), erase O(lg(N)), maximize O(lg(N))
 * Assumption: range of elements should be less than 2^45
 * Source: https://github.com/dragonslayerx
 */

#include <iostream>
#include <cstdio>
using namespace std;

int size=0;
struct node {
    node *left;
    node *right;
    int count;
    node() {
        left = right = NULL;
        count = 0;
    }
} pool[5000005];

class Trie {
    #define MAXB 45
    node *root;
    Trie() {
        root = &pool[size++];
    }

    node* create_new_node(){
        node *t = &pool[size++];
        return t;
    }

    void tostring(char *s, long long x){
        int i;
        long long j;
        for (j = 1LL << MAXB, i = 0; j > 0; j >>= 1, i++) {
            s[i] = ((x & j) != 0) + '0';
        }
        s[i] = '\0';
    }

    void insert_trie(char *s){
        node *t = root;
        for (int i = 0; s[i]; i++) {
            if (s[i] == '0') {
                if (t->left == NULL) {
                    t->left = create_new_node();
                }
                t = t->left;
            } else {
                if (t->right == NULL) {
                    t->right = create_new_node();
                }
                t = t->right;
            }
            t->count++;
        }
    }

    void erase_trie(char *s){
        node *t = root;
        for (int i = 0; s[i]; i++) {
            if (s[i] == '0') {
                t = t->left;
            } else {
                t = t->right;
            }
            t->count--;
        }
    }

public:
    long long maximize(long long x){
        char s[50];
        tostring(s, x);
        long long answer = 0;
        node *t = root;
        for (int i = 0; s[i]; i++) {
            answer <<= 1;
            if (s[i] == '0') {
                if (t->right == NULL || (t->right->count==0)) {
                    t = t->left;
                } else {
                    t = t->right;
                    answer |= 1;
                }
            } else {
                if (t->left == NULL || (t->left->count==0)) {
                    t = t->right;
                } else {
                    t = t->left;
                    answer |= 1;
                }
            }
        }
        return answer;
    }

    void insert(long long x){
        char s[50];
        tostring(s, x);
        insert_trie(s);
    }

    void erase(long long x) {
        char s[50];
        tostring(s, x);
        erase_trie(s);
    }
};

int main() {
}


/*bigint_library.*/
/*
 * Description: BigInt (Big Integer library)
 * Usage:  See constructors, operators like +, -, *, /, >, >=, <, <=, ==, toString
 * Note: Remove references '&' in overloaded operators for chaining operations.
 * Source: https://github.com/dragonslayerx
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

class Bigint {

    const static int MAX = 100005;
    char x[MAX];
    int length;

    void align(char *X, int numDigits) {
        int length = strlen(X);
        for (int i = length; i < numDigits; i++) X[i]='0';
        X[numDigits]='\0';
    }

    int add(char *X, int lenX, char *Y, int lenY, int carry, char *Z) {
        int maxLen = max(lenX, lenY);
        align(X, maxLen); align(Y, maxLen);
        for (int i = 0; i < maxLen; i++) {
            int num = (X[i]-'0') + (Y[i]-'0') + carry;
            Z[i] = num%10 + '0';
            carry = num / 10;
        }
        if (carry) Z[maxLen++] = carry+'0';
        Z[maxLen] = '\0';

        //Put everything back to original state
        X[lenX]='\0'; Y[lenY]='\0';

        return maxLen;
    }

    int substract(char *X, int lenX, char *Y, int lenY, char *Z){
        int maxLen = max(lenX, lenY);
        align(X, maxLen); align(Y, maxLen);
        for (int i = 0; i < maxLen; i++) Y[i]=('9'-Y[i])+'0';
        int len = add(X, lenX, Y, maxLen, 1, Z);
        Z[len--] = '\0';

        //Put everything back to original state
        for (int i = 0; i < maxLen; i++) Y[i]=('9'-Y[i])+'0';
        X[lenX]='\0'; Y[lenY]='\0';

        return len;
    }

    int multiply(char *X, int lenX, char *Y, int lenY, char *Z) {
        if (lenX < lenY) {
            swap(X, Y); swap(lenX, lenY);
        }
        char result[MAX];
        int lenZ = 0;
        for (int i = 0; Y[i]; i++) {
            int digit = Y[i]-'0';
            int carry = 0, size = 0;
            for (int j = 0; X[j]; j++) {
                int val = ((X[j]-'0')*digit) + carry;
                carry = val/10;
                val %= 10;
                result[size++] = val+'0';
            }
            if (carry) result[size++] = carry + '0';
            result[size]='\0';

            for (int j = size; j >= 0; j--) result[j+i] = result[j];
            for (int j = 0; j < i; j++) result[j]='0';

            char finalResult[MAX];
            lenZ = add(result, size+i, Z, lenZ, 0, finalResult);
            strcpy(Z, finalResult);
        }
        return lenZ;
    }

    template<class T>
        int divideNmodulo(char *X, int lenX, T divisor, char *Z, T &modulo) {
            int remainder = 0;
            int size = 0;
            for(int i = lenX-1; i >= 0; i--){
                remainder *= 10;
                remainder += X[i]- '0';
                Z[size++] = remainder/divisor + '0';
                remainder %= divisor;
            }
            Z[size]='\0';
            reverse(Z, Z+size);
            modulo = remainder;
            return size;
        }

    // Relational Operations
    bool equals(char *X, int lenX, char *Y, int lenY) {
        int maxLen = max(lenX, lenY);
        align(X, maxLen); align(Y, maxLen);
        for (int i = maxLen; i >= 0; i--) {
            if (X[i] != Y[i]) return false;
        }

        //Put everything back to original state
        X[lenX] = '\0'; Y[lenY] = '\0';

        return true;
    }

    bool greater(char *X, int lenX, char *Y, int lenY) {
        int maxLen = max(lenX, lenY);
        align(X, maxLen); align(Y, maxLen);
        for (int i = maxLen - 1; i >= 0; i--) {
            if (X[i] > Y[i]) return true;
            if (X[i] < Y[i]) return false;
        }

        //Put everything back to original state
        X[lenX] = '\0'; Y[lenY] = '\0';

        return false;
    }

public:
    //Constructors
    Bigint() {
        x[0]='0'; x[1]='\0';
        length=1;
    }

    Bigint(string s) {
        length = s.size();
        for (int i=0, j=length-1; i < s.size(); i++, j--) x[j]=s[i];
        x[length]='\0';
    }

    Bigint(int v) {
        int size = 0;
        while (v) {
            x[size++] = v % 10 + '0';
            v /= 10;
        }
        x[size]='\0';
        length = size;
    }

    //Arithmetic Operations
    Bigint operator +(Bigint &b) {
        Bigint r;
        r.length = add(this->x, this->length, b.x, b.length, 0, r.x);
        return r;
    }

    Bigint operator *(Bigint &b) {
        Bigint r;
        r.length = multiply(this->x, this->length, b.x, b.length, r.x);
        return r;
    }

    Bigint operator -(Bigint &b) {
        Bigint r;
        r.length = substract(this->x, this->length, b.x, b.length, r.x);
        return r;
    }

    Bigint operator /(int divisor) {
        Bigint r;
        int modulo = 0;
        r.length = divideNmodulo(this->x, this->length, divisor, r.x, modulo);
        return r;
    }

    int operator %(int divisor) {
        Bigint r;
        int modulo = 0;
        r.length = divideNmodulo(this->x, this->length, divisor, r.x, modulo);
        return modulo;
    }

    // Relational Operators
    bool operator ==(Bigint &b) {
        return equals(this->x, this->length, b.x, b.length);
    }

    bool operator >(Bigint &b) {
        return greater(this->x, this->length, b.x, b.length);
    }

    bool operator >=(Bigint &b) {
        return (((*this)>b) || ((*this)==b));
    }

    bool operator <(Bigint &b) {
        return !((*this)>=b);
    }

    bool operator <=(Bigint &b) {
        return !((*this)>b);
    }


    string trimZeros(string &s) {
        int start = 0;
        while (s[start]=='0') start++;
        return s.substr(start);
    }

    string toString() {
        string s(x, x+length);
        reverse(s.begin(), s.end());
        s = trimZeros(s);
        if(s.length() == 0)
            return "0";
        return s;
    }

    friend std::ostream& operator<<(ostream &o, Bigint v) {
        o << v.toString();
        return o;
    }
};

int main() {
    Bigint A("123456789"); // Construct Bigint using string representation
    Bigint B(987654321); // Construct Bigint using integer representation
    Bigint C("456789");
    Bigint D("0");
    cout << "A * B: " << A * B << endl; // Overridden ostream
    cout << "A * B + C: " << A * B + C << endl; // Chaining operations
    cout << "(A > B): " << (A > B) << endl;
    cout << "D: " << D << endl;
    // logical operations
    if (A > B) cout << "A is greater than B" << endl;
    if (B > A) cout << "B is greater than A" << endl;
    if (A == B) cout << "A is equal to B" << endl;
}

/*orderstat_rank_query_augmented_bst*/
/**
 * Description: Augmented tree for order statistics, rank query
 * Usage: See below O(lg(N))
 * Source: https://github.com/dragonslayerx 
 */

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> //required
#include <ext/pb_ds/tree_policy.hpp> //required
using namespace __gnu_pbds; //required
using namespace std;
template <typename T> using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ordered_set <int> s;
/* or:
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
ordered_set s;
This works in C++98 but the above version only works in C++11
*/
int main(){
    // It has C++ `set` functions:
    for(auto i: {1,3,5,8})
        s.insert(i);
    s.erase(8);
    s.erase(s.find(8));
    cout << * s.begin() << endl;
    if(s.begin() == s.end() or s.empty())
        cout << "empty" << endl;
    s.lower_bound(3);
    s.upper_bound(1);
    cout << s.size() << endl;
    // special `tree` functions:
    cout << s.order_of_key(3) << endl; // the number of elements in s less than 3 (in this case, 0-based index of element 3)
    cout << *s.find_by_order(1) << endl; // 1-st elemt in s (in sorted order, 0-based)
}

/*monotone_priority_queue*/
/**
 * Description: Monotone Priority Queues (Supports sliding window queries)   
 * Usage: pushmax, pushmin, O(N)  
 * Source: https://github.com/dragonslayerx 
 */

deque<int> maxq, minq;
void pushmax(int element) {
    while (!maxq.empty() && element > maxq.back()) maxq.pop_back();
    maxq.push_back(element);
}


void pushmin(int element) {
    while (!minq.empty() && element < minq.back()) minq.pop_back();
    minq.push_back(element);
}

/*Point Update Range Query*/
/**
 * Description: BIT (Returns associative operation like sum for a prefix query i.e. say sum[1...i]) 
 * Usage: query O(lg(N)), update O(lg(N))
 * Note: Use 1-based indexing. 
 * Source: https://github.com/dragonslayerx 
 */

#define MAX 100005
long long bit[MAX];

long long query(int indx){
    long long sum = 0;
    while (indx) {
        sum += bit[indx];
        indx -= (indx & -indx);
    }
    return sum;
}

void update(int indx, int x){
   assert(indx != 0);
   while (indx < MAX) {
        bit[indx] += x;
        indx += (indx & -indx);
    }
}

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        update(i, a[i]);
    }
    int q;
    cin >> q;
    while (q--) {
        int choice;
        cin >> choice;
        if (choice) {
            int l, r;
            cin >> l >> r;
            cout << query(r) - query(l-1) << endl;
        } else {
            int p; 
            long long x;
            cin >> p >> x; 
            update(p, x);
        }
    }
}
        

/*Range Update Range Query*/

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MOD = 1000000000+7;
const int INF = 1000000000+5;

/**
 * Description: BIT RURQ (Support range queries and range updates of 1-D array)
 * Usage: query O(lg(N)), update O(lg(N))
 * Source: https://github.com/dragonslayerx
 * Note: Use 1-based indexing
 */

// Remember to use 1 based indexing
class BIT {
    static const int MAX = 100005;
    public:
    static long long query(long long *bit, int indx)
    {
        long long sum = 0;
        while (indx) {
            sum += bit[indx];
            indx -= (indx & -indx);
        }
        return sum;
    }

    static void update(long long *bit, int indx, long long x)
    {
        while (indx < MAX) {
            bit[indx] += x;
            indx += (indx & -indx);
        }
    }
};

class BitRPRQ {
    static const int MAX = 100005;
    long long B1[MAX];
    long long B2[MAX];

    public:
    BitRPRQ() {
        memset(B1, 0, sizeof(B1));
        memset(B2, 0, sizeof(B2));
    }

    long long Rquery(int p){
        long long tempB1 = BIT::query(B1, p);
        long long tempB2 = BIT::query(B2, p);
        long long sum = tempB1 * p + tempB2;
        return sum;
    }

    long long Rupdate(int l, int r, long long v){
        BIT::update(B1, l, v);
        BIT::update(B1, r+1, -v);
        BIT::update(B2, l, -((l-1)*v));
        BIT::update(B2, r+1, r*v);
    }
};

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, q;
        scanf("%d%d", &n, &q);
        BitRPRQ B;
        while (q--) {
            int choice;
            scanf("%d", &choice);
            int p, q;
            long long v;
            scanf("%d%d", &p, &q);
            if (choice==0) {
                long long v;
                scanf("%lld", &v);
                B.Rupdate(p, q, v);
            } else {
                long long Answer = B.Rquery(q)-B.Rquery(p-1);
                printf("%lld\n", Answer);
            }
        }
    }
}

/*Order Statistic Query*/
/**
 * Description: BIT Orderstat (Returns Kth order statistic).
 * Usage: update O(lg(N)), statquery O(lg^2(N))
 * Note: Perform range compression if range is large.
 * Source: https://github.com/dragonslayerx
 */

 #include <iostream>
 #include <cstdio>
 #include <cassert>
 using namespace std;

const int MAX = 100005;
typedef long long ll;

ll bit[MAX];

ll query(int indx){
    ll sum = 0;
    while (indx) {
        sum += bit[indx];
        indx -= (indx & -indx);
    }
    return sum;
}

void update(ll indx, ll x){
    while (indx < MAX) {
        bit[indx] += x;
        indx += (indx & -indx);
    }
}

int statquery(int k){
    int low = 0, high = MAX-1, ans = 0;
    while (low <= high) {
        int mid = low + ((high - low)>>1);
        int qr = query(mid);
        if (qr >= k) {ans = mid, high = mid - 1;}
        else if (qr < k) low = mid + 1;
    }
    return ans;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char choice[2];
        scanf("%s", &choice);
        if (choice[0]=='i') {
            int value;
            scanf("%d", &value);
            assert(value >= 1);
            update(value, 1);
        } else {
            int k;
            scanf("%d", &k);
            printf("%d\n", statquery(k));
        }
    }
}

/*2D Binary Indexed Trees*/

/**
 * Bit 2D: Support point updates and associative operations like sum over a 2-D matrix
 * Complexity: lg(n) per query and update 
 * Usage: query and update. Indexes should be 1-based 
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

#define MAX 1010

long long bit[MAX][MAX];
bool grid[MAX][MAX];

long long queryx(int x, int y){
    long long sum = 0;
    while (y) {
        sum += bit[x][y];
        y -= y & -y;
    }
    return sum;
}

long long query(int x, int y){
    long long sum = 0;
    while (x) {
        sum += queryx(x, y);
        x -= x & -x;
    }
    return sum;
}

void updatex(int x, int y, int v){
    while (y < MAX) {
        bit[x][y] += v;
        y += y & -y;
    }
}

void update(int x, int y, int v){
    while (x < MAX) {
        updatex(x, y, v);
        x += x & -x;
    }
}

int main()
{
    int tc;
    scanf("%d", &tc);
    for (int t = 1; t <= tc; t++) {
        memset(bit, 0, sizeof(bit));
        memset(grid, 0, sizeof(grid));

        printf("Case %d:\n", t);
        int q;
        scanf("%d", &q);
        while (q--) {
            int ch;
            scanf("%d", &ch);
            if (ch == 0) {
                int x, y;
                scanf("%d%d", &x, &y);
                x++, y++;
                if (!grid[x][y]) {
                    update(x, y, 1);
                    grid[x][y] = 1;
                }
            } else if (ch == 1) {
                int x1, y1, x2, y2;
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                x1++, y1++, x2++, y2++;
                printf("%d\n", query(x2, y2) - query(x2, y1-1) - query(x1-1, y2) + query(x1-1, y1-1));
            }
        }
    }
}

/**/
/*lowest_common_ancestor_lca*/
/**
 * Description: LCA (Finds the lowest common ancestor of two nodes in a tree)
 * Usage: LCA constructor O(Nlg(N)), query O(lg(N))
 * Source: https://github.com/dragonslayerx
 */

template<typename value_type> class RMQ {
    vector<int> a;
    vector<vector<value_type> > rmq;

    int size;
    int log2(int x){
        int i = 0, n = 1;
        while (x >= n) {
            i++; n <<= 1;
        }
        i--;
        return i;
    }

public:
    RMQ() {}

    RMQ(vector<value_type> &a) : a(a) {
        size = log2(a.size()) + 1;
        rmq.resize(size, vector<value_type> (a.size()));
        construct(a);
    }

    void construct(vector<value_type> &array){
        for (int i = 0; i < array.size(); i++) rmq[0][i] = i;
        for (int k = 1; k < size; k++) {
            for (int i = 0; i < a.size(); i++) {
                int length = 1 << (k - 1);
                if (i + length >= a.size() || a.at(rmq[k - 1][i]) < a.at(rmq[k - 1][i + length])){
                    rmq[k][i] = rmq[k - 1][i];
                } else {
                    rmq[k][i] = rmq[k - 1][i + length];
                }
            }
        }
    }

    int query(int i, int j){
        int range = j - i + 1;
        int logr = log2(range);
        if (a[rmq[logr][i]] < a[rmq[logr][j - (1 << logr) + 1]])
            return rmq[logr][i];
        else
            return rmq[logr][j - (1 << logr) + 1];
    }
};

class LCA {
    typedef vector<vector<int> > tree;
    vector<int> E, H, L;
    RMQ<int> R;
    tree T;
    vector<bool> isvisited;

    void euler_tour(int node, int level){
        isvisited[node] = 1;
        E.push_back(node);
        L.push_back(level);
        for (vector<int>::iterator i = T[node].begin(); i != T[node].end(); i++) {
            if (!isvisited[*i]) {
                euler_tour(*i, level + 1);
                E.push_back(node);
                L.push_back(level);
            }
        }
    }

public:
    LCA(tree &T, int root): T(T){
        isvisited.resize(T.size());
        H.resize(T.size(), -1);
        euler_tour(root, 0);
        for (int i = 0; i < E.size(); i++) {
            if (H[E[i]] == -1)
                H[E[i]] = i;
        }
        R = RMQ<int>(L);
    }

    int lca(int a, int b){
        if (H[a] > H[b]) swap(a, b);
        int index = R.query(H[a], H[b]);
        return E[index];
    }
};


/*kth_ancestor_tree*/

/**
 * Description: Level Ancestor (Finds the Kth level ancestor of a node in tree using sparse table)
 * Usage: assign, process O(N lg(N)), query O(lg(N))
 * Note: The tree should in form of an array P where P[i] represents parent of i th node.
 * Source: https://github.com/dragonslayerx
 */

class levelAncestor
{
    private:
        vector<size_t> tree;
        vector<vector<size_t> > LA;

    public:
        levelAncestor(){}

        levelAncestor(size_t size){
            assign(size);
        }

        template<class value> levelAncestor(const vector<value> &T){
            assign(T);
        }

        template<class value> void assign(const vector<value> &T){
            clear();
            tree.resize(T.size());
            for(size_t i=0;i<tree.size();i++) tree[i]=T[i];
        }

        void process(){
            size_t lgn=0;
            for(size_t sz=tree.size();sz;sz>>=1,lgn++);

            LA.resize(lgn,vector<size_t>(tree.size()));

            for(size_t j=0;j<LA[0].size();j++)
                LA[0][j]=tree[j];

            for(size_t i=1;i<LA.size();i++)
                for(size_t j=0;j<LA[i].size();j++)
                    LA[i][j]=LA[i-1][LA[i-1][j]];
        }

        size_t& operator [](size_t pos){
            return tree[pos];
        }

        size_t query(size_t node,size_t level) const{
            int k=0;
            int current=node;
            for(;level;level>>=1,k++) {
                if(level&1) {
                    current=LA[k][current];
                }
            }
            return current;
        }

        size_t size() const{
            return tree.size();
        }

        void clear(){
            tree.clear();
        }

        ~levelAncestor(){
            clear();
        }
};



/*trees_path_query_sparse_tables*/

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef vector< vector<int> > Tree;

template<class valueType, class MF>
class SparseTable {
private:
    int counter;

    int n, root;
    Tree &T;
    vector<valueType> &w;

    vector<int> parent, level;
    vector<int> prestamp, poststamp;
    vector<vector<valueType> > ancestor, aggregate;

    static const int INVALID = -1;

    bool isInSubtree(int u, int v) {
        return ((prestamp[u] <= prestamp[v]) && (poststamp[u] >= poststamp[v]));
    }

    void processTree() {
        //perform a DFS
            performDfs(root, INVALID, 0);
        //Get Ancestors
            processAncestors();
        //Get Aggregate
            processAggregate();
    }

    void performDfs(int u, int p, int l) {
        prestamp[u] = counter++;
        parent[u] = p;
        level[u] = l;
        for (int v : T[u]) {
            if (v != p) {
                performDfs(v, u, l+1);
            }
        }
        poststamp[u] = counter++;

    }

    void processAncestors() {
        for (int j = 0; j < n; j++) {
            ancestor[0][j] = parent[j];
        }
        for (int i = 1; i < ancestor.size(); i++) {
            for (int j = 0; j < n; j++) {
                if (ancestor[i-1][j] != INVALID) {
                    ancestor[i][j] = ancestor[i-1][ancestor[i-1][j]];
                } else {
                    ancestor[i][j] = INVALID;
                }
            }
        }
    }

    void processAggregate() {
        for (int j = 0; j < n; j++) {
            aggregate[0][j] = w[j];
        }
        for (int i = 1; i < aggregate.size(); i++) {
            for (int j = 0; j < n; j++) {
                if (ancestor[i-1][j] != INVALID) {
                    aggregate[i][j] =  mergeFunction(aggregate[i-1][j], aggregate[i-1][ancestor[i-1][j]]);
                } else {
                    aggregate[i][j] = INVALID;
                }
            }
        }
    }

    int getLog(int n){
        int i=0;
        while (n) {
            i++, n>>=1;
        }
        return i;
    }

public:
    MF mergeFunction;

    SparseTable(Tree &T, vector<valueType> &w, const int root) : T(T), w(w) {
        this->counter = 0;
        this->root = root;
        this->n = T.size();

        parent.resize(n);
        level.resize(n);
        prestamp.resize(n); poststamp.resize(n);

        int size = getLog(n)+5;
        ancestor.resize(size, vector<valueType>(n));
        aggregate.resize(size, vector<valueType>(n));

        processTree();
    }

    int getLCA(int u, int v) {
        if (isInSubtree(u, v)) return u;
        if (isInSubtree(v, u)) return v;
        int size = ancestor.size();
        for (int i = size-1; i >= 0; --i) {
            if (ancestor[i][u] == INVALID) continue;
            if (!isInSubtree(ancestor[i][u], v)) {
                u = ancestor[i][u];
            }
        }
        return ancestor[0][u];
    }

    valueType query(int x, int y) {
        if (level[x] <= level[y]) {
            swap(x, y);
        }
        //y should be an ancestor of x
        int currentNode = x, dif = level[x]-level[y]+1;
        int i = 0;
        valueType v = 0;
        while (dif) {
            if (dif & 1) {
                v = mergeFunction(v, aggregate[i][currentNode]);
                currentNode = ancestor[i][currentNode];
            }
            i++, dif>>=1;
        }
        return v;
    }

};

template <class valueType>
class MF {
    public:
    valueType operator()(valueType left, valueType right) {
        return left+right;
    }
};

int main() {
    int n;
    cin >> n;
    vector< vector<int> > T(n);
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        T[a].push_back(b);
        T[b].push_back(a);
    }
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    SparseTable< int, MF<int> > S(T, w, 0);
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int lcaUV = S.getLCA(u, v);
        int sumU = S.query(u, lcaUV);
        int sumV = S.query(v, lcaUV);
        cout << lcaUV << " " << sumU << " " << sumV << endl;
        cout << sumU + sumV - w[lcaUV] << endl;
    }
}


/*heavy_light_decomposition_wieghted_vertices(hld)*/

/**
 * Description: Heavy Light Decomposition (Perform point updates and aggregate query over paths between two nodes in tree in case vertices are weighted)
 * Usage: update O(lg(N)), path_query O(lg^2(N)), See below for more details. 
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cassert>

using namespace std;

//----------Modifiable------
#define MAX 50050
//--------------------------
#define INVALID -1

bool isvisited[MAX];

int st_size[MAX]; // subtree_size
int p[MAX]; // parent of node
int lvl[MAX]; // level of node

vector<vector<int> > G;

int calc_size(int u, int level)
{
    isvisited[u] = 1;
    lvl[u] = level;

    st_size[u] = 1;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (!isvisited[v]) {
            p[v] = u;
            st_size[u] += calc_size(v, level+1);
        }
    }
    return st_size[u];
}

int node[MAX];
int chain_head[MAX], chain_link[MAX], chain[MAX];

//----------Modifiable------
int chain_id = 0, node_id = 1; // change this as per requiremnt bit donot support 0 base indexing
//--------------------------

int decompose(int u)
{
    isvisited[u] = 1;

    chain[u] = chain_id;
    node[u] = node_id++;
    if (chain_head[chain_id] == INVALID) {
        chain_head[chain_id] = u;
        chain_link[chain_id] = p[u];
    }

    int special_child = INVALID, max_subtree_size = 0;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (!isvisited[v] && max_subtree_size < st_size[v]) {
            special_child = v;
            max_subtree_size = st_size[v];
        }
    }
    if (special_child != INVALID) decompose(special_child);
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (!isvisited[v] && v != special_child) {
            chain_id++;
            decompose(v);
        }
    }
}

void hld_decompose(int root, int v)
{
    chain_id = 0, node_id = 1; // change this as per requiremnt bit donot support 0 base indexing
    memset(isvisited, 0, sizeof(isvisited));
    calc_size(root, 0);
    memset(isvisited, 0, sizeof(isvisited));
    for (int i = 0; i < v; i++) {
        chain_head[i] = INVALID;
        chain_link[i] = INVALID;
    }
    decompose(root);
}

int lca(int v1, int v2)
{
    int x = v1, y = v2;
    while (chain[x] != chain[y]){
        if (lvl[chain_head[chain[x]]] >= lvl[chain_head[chain[y]]])
            x = chain_link[chain[x]];
        else
            y = chain_link[chain[y]];
    }
    if (lvl[x] < lvl[y]) return x;
    else return y;
}

//---- BIT -----
long long _query(long long *bit, int indx){
    long long sum = 0;
    while (indx) {
        sum += bit[indx];
        indx -= indx & -indx;
    }
    return sum;
}

void update(long long *bit, int indx, long long val){
    while (indx < MAX) {
        bit[indx] += val;
        indx += indx & -indx;
    }
}

long long query(long long *bit, int x, int y){
    if (x > y) swap(x, y);
    return _query(bit, y) - _query(bit, x-1);
}
//--------------


//-----Modifiable---
long long path_query(long long *bit, int x, int y) // y is some ancestor of x in the actual tree
{
    long long aggregate = 0; // Set it as per the problem statement
    while (chain[x] != chain[y]){
        aggregate += query(bit, node[x], node[chain_head[chain[x]]]); // Set it as per the problem statement
        x = chain_link[chain[x]];
    }
    aggregate += query(bit, node[x], node[y]);
    return aggregate;
}

void node_update(long long *bit, int x, long long y) // pass the actual id of the nodes not the hashed ids
{
    update(bit, node[x], y);
}
//------------------


long long a[MAX], t[MAX], bit[MAX];

int main()
{
    int tc;
    scanf("%d", &tc);
    for (int t = 1; t <= tc; t++)
    {
        printf("Case %d:\n", t);
        int v;
        scanf("%d", &v);
        G.clear();
        G.resize(v);
        for (int i = 0; i < v; i++) {
            scanf("%lld", &a[i]);
        }
        memset(bit, 0, sizeof(bit));
        tree.process();
        for (int i = 1; i <= v-1; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            G[a].push_back(b);
            G[b].push_back(a);
        }

        hld_decompose(0, v);

        for (int i = 0; i < v; i++) {
            update(bit, node[i], a[i]);
        }

        int q;
        scanf("%d", &q);
        while (q--) {
            int ch;
            scanf("%d", &ch);
            int x;
            scanf("%d", &x);
            if (!ch) {
                int y;
                scanf("%d", &y);
                long long sum = 0;
                int lca_xy = lca(x, y);
                sum += path_query(bit, x, lca_xy);
                sum += path_query(bit, y, lca_xy);
                sum -= a[lca_xy];
                printf("%lld\n", sum);
            } else {
                long long y;
                scanf("%lld", &y);
                node_update(bit, x, y - a[x]);
                a[x] = y;
            }
        }
    }
}

/*heavy_light_decomposition_weighted_edges (hld)*/

/**
 * Heavy Light decomposition:  Perform point updates and aggregate queries over path between two nodes in a tree in case edges are weighted
 * Complexity: O(lg^2(N)) 
 * Source: https://github.com/dragonslayerx 
 */

#include<iostream>
#include<iostream>
#include<cmath>
#include<map>
#include<limits>
#include<vector>
#include<list>
#include<queue>
using namespace std;


const long long INF = 1000000000000000005LL;

long long mul(long long a, long long b) {
    pair<long long, long long> s, t, result;
    t.first = a / 1000000000;
    t.second = a % 1000000000;

    s.first = b / 1000000000;
    s.second = b % 1000000000;

    long long r1, r2, r3, r4;

    r1 = t.first * s.first;
    r2 = t.first * s.second;
    r3 = t.second * s.first;
    r4 = t.second * s.second;

    if (r1 && (r2 || r3 || r4)) return INF;
    else if ((r2 + r3) > 1000000000) return INF;
    else if ((r2 + r3)*1000000000 + r4 > INF) return INF;
    else return (r2 + r3)*1000000000 + r4;
}

class HLD
{
    public:
        typedef vector<list<int> > tree;
    private:
        tree &T;

        void doHLD(int cur=0)
        {
            chainNumber[cur]=chainSize.size()-1;
            chainPosition[cur]=chainSize.back();
            chainSize.back()++;

            int maxTreeSize=numeric_limits<int>::min();
            int maxTreeSizeNode=-1;

            for(list<int>::iterator i=T[cur].begin();i!=T[cur].end();i++)
                if(nodeLevel[*i]>nodeLevel[cur])
                    if(maxTreeSize<treeSize[*i])
                    {
                        maxTreeSize=treeSize[*i];
                        maxTreeSizeNode=*i;
                    }

            if(maxTreeSizeNode==-1)
                return;
            doHLD(maxTreeSizeNode);

            for(list<int>::iterator i=T[cur].begin();i!=T[cur].end();i++)
                if(nodeLevel[*i]>nodeLevel[cur])
                    if(*i!=maxTreeSizeNode)
                    {
                        chainSize.push_back(0);
                        chainHead.push_back(cur);
                        doHLD(*i);
                    }
        }

        void calculateTreeSize(int node)
        {
            treeSize[node]=1;
            for(list<int>::iterator i=T[node].begin();i!=T[node].end();i++)
            {
                if(nodeLevel[*i]>nodeLevel[node])
                {
                    calculateTreeSize(*i);
                    treeSize[node]+=treeSize[*i];
                }
            }
        }

    public:
        vector<int> chainHead;
        vector<int> chainNumber;
        vector<int> chainPosition;
        vector<int> chainSize;
        vector<int> nodeLevel;
        vector<int> treeSize;
        HLD(tree &t,int start=0):T(t)
        {
            chainHead.reserve(T.size());
            chainNumber.resize(T.size());
            chainPosition.resize(T.size());
            chainSize.reserve(T.size());
            nodeLevel.resize(T.size(),-1);
            treeSize.resize(T.size());


            chainSize.push_back(0);
            chainHead.push_back(-1);
            // bfs for finding the level of the node

            queue<int> Q;
            nodeLevel[start]=0;
            Q.push(start);
            while(!Q.empty())
            {
                int current=Q.front();
                Q.pop();
                for(list<int>::iterator i=T[current].begin();i!=T[current].end();i++)
                {
                    if(nodeLevel[*i]==-1)
                    {
                        nodeLevel[*i]=nodeLevel[current]+1;
                        Q.push(*i);
                    }
                }
            }

            // dfs
            calculateTreeSize(start);
            doHLD(start);
        }
        size_t chainCount() const
        {
            return chainSize.size();
        }
};

template<class T,class MF,class UN> class segmentTree
{
    public:
        typedef T value_type;

    private:
        vector<value_type> tree;
        MF mergeFunction;
        UN updateNode;
        size_t sz;

        bool inRange(size_t queryLeft,size_t queryRight,size_t nodeLeft,size_t nodeRight) const
        {
            if(nodeLeft > nodeRight || nodeLeft > queryRight || nodeRight < queryLeft)
                return false;
            return true;
        }

        size_t leftChild(size_t node)
        {
            return (node<<1)+1;
        }
        size_t rightChild(size_t node)
        {
            return (node<<1)+2;
        }

        void buildTree(const vector<value_type> &A,size_t low,size_t high, size_t node)
        {

            if(low==high)
                tree[node]=A[low];
            else if(low>high)
                return;
            else
            {
                buildTree(A,low,(low+high)/2,leftChild(node));
                buildTree(A,(low+high)/2+1,high,rightChild(node));
                tree[node]=mergeFunction(tree[leftChild(node)],tree[rightChild(node)]);
            }
        }

        value_type query(size_t queryLeft,size_t queryRight,size_t nodeLeft,size_t nodeRight,size_t node)
        {
            if(nodeLeft>=queryLeft&&nodeRight<=queryRight)
                return tree[node];
            else
            {
                bool leftInRange=inRange(queryLeft,queryRight,nodeLeft,(nodeLeft+nodeRight)/2);
                bool rightInRange=inRange(queryLeft,queryRight,(nodeLeft+nodeRight)/2+1,nodeRight);

                if(leftInRange&&!rightInRange)
                    return query(queryLeft,queryRight,nodeLeft,(nodeLeft+nodeRight)/2,leftChild(node));

                else if(!leftInRange&&rightInRange)
                    return query(queryLeft,queryRight,(nodeLeft+nodeRight)/2+1,nodeRight,rightChild(node));

                else
                    return mergeFunction(query(queryLeft,queryRight,nodeLeft,(nodeLeft+nodeRight)/2,leftChild(node)),query(queryLeft,queryRight,(nodeLeft+nodeRight)/2+1,nodeRight,rightChild(node)));
            }
        }

        void update(size_t queryLeft,size_t queryRight,size_t nodeLeft,size_t nodeRight,size_t node,value_type value)
        {
            if(!inRange(queryLeft,queryRight,nodeLeft,nodeRight))
                return;

            if(nodeLeft==nodeRight)
                tree[node]=updateNode(tree[node],value);
            else
            {
                update(queryLeft,queryRight,nodeLeft,(nodeLeft+nodeRight)/2,leftChild(node),value);
                update(queryLeft,queryRight,(nodeLeft+nodeRight)/2+1,nodeRight,rightChild(node),value);

                tree[node]=mergeFunction(tree[leftChild(node)],tree[rightChild(node)]);
            }
        }

    public:
        segmentTree()
        {
            sz=0;
        }

        segmentTree(size_t size,value_type initial=value_type())
        {
            assign(size,initial);
        }

        segmentTree(const vector<value_type> &A)
        {
            clear();
            assign(A);
        }

        void assign(size_t size,value_type initial=value_type())
        {
            clear();
            sz=size;
            tree.resize(4*size,initial);
        }

        void assign(const vector<value_type> &A) // assumes vector to be 0 indexed
        {
            assign(A.size());
            buildTree(A,0,A.size()-1,0);
        }

        void clear()
        {
            sz=0;
            tree.clear();
        }

        void update(size_t pos,const value_type &value)
        {
            update(pos,pos,0,sz-1,0,value);
        }

        value_type query(size_t low,size_t high)
        {
            return query(low,high,0,sz-1,0);
        }
        ~segmentTree()
        {
            clear();
        }
};
struct updateNode
{
    long long operator()(int node, long long newValue)
    {
        return newValue;
    }
};

struct mergeNode
{
    long long operator()(long long left, long long right)
    {
        return mul(left, right);
    }
};

struct edge
{
    int a,b;
    long long cost;
};

template<class T> class rmq
{
    private:
        vector<vector<T> > RMQ;
    public:
        rmq()
        {
        }
        rmq(vector<T> &arr)
        {
    //------------------------------------------------
            int n=arr.size();
            RMQ.resize(n);
            int len=5+ceil(log(arr.size()));
            for(int i=0;i<n;i++)
            {
                RMQ[i].resize(len);
            }


    //----------------------------------------------
            for(int i=0;i<n;i++)
            RMQ[i][0]=arr[i];

            for(int j=1,p=2;p<=n;j++,p*=2)
            {
                for(int i=0;i+p<=n;i++)
                RMQ[i][j]=min(RMQ[i][j-1],RMQ[i+p/2][j-1]);
            }
        }

        T query(int i,int j)
        {

            int gap=j-i+1;
            int p=-1;
            int po=1;

            while(gap) // calculates 2^(floor(logk)) and floor(logk)
            {
                gap=gap/2;
                p++;
                po<<=1;
            }
            po/=2;

            return min(RMQ[i][p],RMQ[j-po+1][p]);
        }
};

class LCA
{
    public:
        typedef vector<list<int> > tree; // change this according to your problem.
    private:
        tree &T;

        vector<bool> istraversed;
        vector<int> level;
        vector<int> position;
        vector<pair<int,int> > rmqArray;
        rmq<pair<int,int> >  RMQ;

        void dfs(int source)
        {
            if(!istraversed[source])
            {
                istraversed[source]=true;
                position[source]=rmqArray.size();
                rmqArray.push_back(make_pair(level[source],source));
                for(tree::value_type::iterator i=T[source].begin();i!=T[source].end();i++)
                {
                    if(!istraversed[*i])          // vertex point here
                    {
                        dfs(*i);
                        rmqArray.push_back(make_pair(level[source],source));
                    }
                }
            }
        }

        void bfs(int start)
        {
            queue<int> Q;
            level[start]=0;
            Q.push(start);

            while(!Q.empty())
            {
                int current=Q.front();
                Q.pop();
                for(tree::value_type::iterator i=T[current].begin();i!=T[current].end();i++)
                {
                    if(level[*i]==-1)
                    {
                        level[*i]=level[current]+1;
                        Q.push(*i);
                    }
                }
            }
        }


    public:
        LCA(tree &t,int start=0):T(t)
        {
            level.resize(t.size(),-1);
            bfs(start);

            position.resize(t.size());
            istraversed.resize(t.size());
            rmqArray.reserve(t.size());
            dfs(start);

            RMQ=rmq<pair<int,int> >(rmqArray);
        }

        int query(int nodeA,int nodeB)
        {
            return RMQ.query(min(position[nodeA],position[nodeB]),max(position[nodeA],position[nodeB])).second;
        }
};



int main(){
        //  freopen("testQTREE.txt","r",stdin);
        //  freopen("outQtree1.txt","w",stdout);

        ios_base::sync_with_stdio(false);

        int n, q;
        cin>>n >> q;

        vector<edge> E(n-1);
        HLD::tree T(n);

        for(int i=0;i<n-1;i++)
        {

            cin>>E[i].a>>E[i].b>>E[i].cost;
            E[i].a--;
            E[i].b--;
            T[E[i].a].push_back(E[i].b);
            T[E[i].b].push_back(E[i].a);
        }

        HLD hld(T);

        vector<segmentTree<long long,mergeNode,updateNode> > ST(hld.chainCount())   ;

        for(int i=0;i<hld.chainCount();i++)
            ST[i].assign(hld.chainSize[i]);

        for(int i=0;i<E.size();i++)
        {
            int target=(hld.nodeLevel[E[i].a]>hld.nodeLevel[E[i].b]?E[i].a:E[i].b);
            ST[hld.chainNumber[target]].update(hld.chainPosition[target],E[i].cost);
        }

        LCA lca(T,0);

        while(q--)
        {
            int choice;
            cin>>choice;
            if(choice==1)
            {
                int a,b;
                long long k;
                cin>>a>>b>>k;
                if(a==b)
                {
                    cout<<k<<endl;
                    continue;
                }
                a--;
                b--;

                int l=lca.query(a,b);

                long long ans=1;
                while(1)
                {
                    if(hld.chainNumber[l]==hld.chainNumber[a])
                    {
                        if(l==a)
                            break;
                        ans=mul(ans, ST[hld.chainNumber[a]].query(hld.chainPosition[l]+1,hld.chainPosition[a]));
                        break;
                    }
                    ans=mul(ans, ST[hld.chainNumber[a]].query(0,hld.chainPosition[a]));
                    a=hld.chainHead[hld.chainNumber[a]];
                }
                while(1)
                {
                    if(hld.chainNumber[l]==hld.chainNumber[b])
                    {
                        if(l==b)
                            break;
                        ans=mul(ans, ST[hld.chainNumber[b]].query(hld.chainPosition[l]+1,hld.chainPosition[b]));
                        break;
                    }
                    ans=mul(ans, ST[hld.chainNumber[b]].query(0,hld.chainPosition[b]));
                    b=hld.chainHead[hld.chainNumber[b]];
                }
                cout<<k/ans<<endl;
            }else if(choice==2){
                int i;
                long long value;
                cin>>i>>value;
                i--;
                int target=(hld.nodeLevel[E[i].a]>hld.nodeLevel[E[i].b]?E[i].a:E[i].b);
                ST[hld.chainNumber[target]].update(hld.chainPosition[target],value);
            }
        }
}

/*tree_diameter*/
/**
 * Description: Find the diameter of the tree.
 * Usage: getDiameter O(V + E)
 * Source: https://github.com/dragonslayerx
 */

 #include <iostream>
 #include <cstdio>
 #include <cstring>
 #include <vector>
 using namespace std;

typedef vector< vector<pair<int,int> > > tree;
void dfs(tree &g, int u, int parent, int d, int dt[]){
    dt[u] = d;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i].first;
        if (v != parent) {
            dfs(g, v, u, d + g[u][i].second, dt);
        }
    }
}

const int MAX = 100005;
int getDiameter(tree &g) {
    int dt[MAX] = {};
    dfs(g, 0, 0, 0, dt);
    int max_dist = 0, max_pos = 0;
    int n = g.size();
    for (int i = 0; i < n; i++) {
        if (max_dist < dt[i]) {
            max_dist = dt[i];
            max_pos = i;
        }
    }
    memset(dt, 0, sizeof(dt));
    dfs(g, max_pos, max_pos, 0, dt);
    max_dist = 0;
    for (int i = 0; i < n; i++) max_dist = max(max_dist, dt[i]);
    return max_dist;
}

int main() {
    int n, m;
    cin >> n >> m;
    tree T;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        int w;
        cin >> w;
        T[a].push_back({b, w});
        T[b].push_back({a, w});
    }
    cout << getDiameter(T) << endl;
}

/*tree_dfs_preorder_postorder_isInSubtree*/
/**
 * Description: Preorder and Postorder stamps (Finds the preorder and postorder stamps for vertices of tree. Useful for checking if vertex is in subtree)
 * Usage: preprocess O(V)
 * Source: https://github.com/dragonslayerx
 */
#include <iostream>
#include <vector>
using namespace std;

const int MAX = 100005;

vector< vector<int> > T;

int prestamp[MAX], poststamp[MAX];
int counter = 0;
void preprocess(int u, int p) {
    prestamp[u] = counter++;
    for (int v : T[u]) {
        if (v != p) {
            preprocess(v, u);
        }
    }
    poststamp[u] = counter++;
}

bool isInSubtree(int u, int v) {
    return ((prestamp[u] <= prestamp[v]) && (poststamp[u] >= poststamp[v]));
}

int main() {
    int n;
    cin >> n;
    T.resize(n);
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        T[a].push_back(b);
        T[b].push_back(a);
    }
    int root;
    cin >> root;
    preprocess(root, root);
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        // Check if v is in subtree of u
        cout << isInSubtree(u, v) << endl;
    }
}

/**/
/*Point Update Range Query*/
/**
 * Description: Segment Tree Range query Point update.
 * Usage: construct O(N), update O(lg(N)), query O(lg(N))
 * Source: https://github.com/dragonslayerx
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
using namespace std;

#define MAX 100005

long long a[MAX];

int st[4*MAX];

int construct (int node, int ll, int rl){
    if (ll == rl) st[node] = a[ll];
    else {
        int left = construct(2*node+1, ll, (ll+rl)/2);
        int right = construct(2*node+2, (ll+rl)/2 + 1, rl);
        st[node] = left + right;
    }
    return st[node];
}

int query(int node, int ll, int rl, int ql, int qr){
    if (ll >= ql && rl <= qr) return st[node];
    else if (rl < ql || ll > qr) return 0;
    int left = query(2*node+1, ll, (ll+rl)/2, ql, qr);
    int right = query(2*node+2, (ll+rl)/2 + 1, rl, ql, qr);
    return left + right;
}

int update(int node, int ll, int rl, int q, int val){
    if (rl < q || ll > q) return st[node];
    if (q == ll && q == rl) st[node] = val;
    else {
        int left = update(2*node+1, ll, (ll+rl)/2, q, val);
        int right = update(2*node+2, (ll+rl)/2 + 1, rl, q, val);
        st[node] = left + right;
    }
    return st[node];
}


int main()
{
    int tc;
    scanf("%d", &tc);
    for (int t=1; t<=tc; t++ ) {
        printf("Case %d:\n", t);
        memset(a, 0, sizeof(a));
        int n, q;
        scanf("%d%d", &n, &q);
        for (int i = 0; i < n; i++)
            scanf("%lld", &a[i]);
        construct(0, 0, n-1);
        while (q--) {
            int x, y;
            scanf("%d%d", &x, &y);
            x--, y--;
            printf("%d\n", query(0, 0, n-1, x, y));
        }
    }
}

/*Fast Iterative Segtrees*/
/**
 * Description: Fast iterative segment tree. 
 * Usgae: build O(N), query O(lg(N)), modify O(lg(N))
 * Note: The code is taken from http://codeforces.com/blog/entry/18051
 * Source: https://github.com/dragonslayerx 
 */

int n,m,q;
int arr[600][600];
int a,b,t[50000];

void build(){
    for(int i = n - 1; i > 0 ; --i) t[i] = max(t[i<<1], t[i<<1|1]);
}

void modify(int p, int v){
    for(t[p += n] = v; p > 1 ; p>>=1) t[p>>1] = max(t[p], t[p^1]);
}

int query(int l, int r){
    int ans = 0;
    for(l += n, r+=n; l < r; l >>= 1, r >>= 1)
        ans = max(ans, max( ((l&1) ? t[l++] : 0), ((r&1) ? t[--r] : 0)));
    return ans;
}

/*Range Update Point Query - Lazy Propogation*/
/**
 * Description: Segment Tree Range query Range update.  
 * Usage: construct O(N), update O(lg(N)), query O(lg(N)) 
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

#define MAX 100100

struct node {
    long long val, lazy;
    bool flag;
    node()
    {
        val = lazy = 0;
        flag = false;
    }
};

node st[4*MAX];

long long query(int n, int ll, int rl, int ql, int qr)
{
    if (st[n].flag) {
        st[n].val += (rl-ll+1)*st[n].lazy;
        if (ll != rl) {
            st[(n<<1)+1].flag = true;
            st[(n<<1)+1].lazy += st[n].lazy;
            st[(n<<1)+2].flag = true;
            st[(n<<1)+2].lazy += st[n].lazy;
        }
        st[n].flag = false;
        st[n].lazy = 0;
    }

    if (qr < ll || ql > rl) return 0;
    if (ll >= ql && rl <= qr) return st[n].val;
    else {
        long long left = query((n<<1)+1, ll, ((ll+rl)>>1), ql, qr);
        long long right = query((n<<1)+2, ((ll+rl)>>1) + 1, rl, ql, qr);
        return left + right;
    }
}

node update(int n, int ll, int rl, int ql, int qr, long long val)
{
    //cout << n << " " << ll << " " << rl << " " << ql << " " << qr << endl;
    if (st[n].flag) {
        st[n].val += (rl-ll+1)*st[n].lazy;
        if (ll != rl) {
            st[(n<<1)+1].flag = true;
            st[(n<<1)+1].lazy += st[n].lazy;
            st[(n<<1)+2].flag = true;
            st[(n<<1)+2].lazy += st[n].lazy;
        }
        st[n].flag = false;
        st[n].lazy = 0;
    }

    if (qr < ll || ql > rl) return st[n];
    if (ll >= ql && rl <= qr) {
        st[n].val += (rl-ll+1)*val;
        if (ll != rl) {
            st[(n<<1)+1].flag = true;
            st[(n<<1)+1].lazy += val;
            st[(n<<1)+2].flag = true;
            st[(n<<1)+2].lazy += val;
        }
    } else {
        node left = update((n<<1)+1, ll, ((ll+rl)>>1), ql, qr, val);
        node right = update((n<<1)+2, ((ll+rl)>>1) + 1, rl, ql, qr, val);
        st[n].val = left.val + right.val;
    }
    return st[n];
}

int main()
{
    int tc;
    scanf("%d", &tc);
    for (int t = 1; t <= tc; t++) {
        memset(st, 0, sizeof(st));
        printf("Case %d:\n", t);
        int n, q;
        scanf("%d%d", &n, &q);
        while (q--) {
            int ch;
            scanf("%d", &ch);
            int x, y;
            scanf("%d%d", &x, &y);
            if (ch)
                printf("%lld\n", query(0, 0, n-1, x, y));
            else {
                long long val;
                scanf("%lld", &val);
                update(0, 0, n-1, x, y, val);
            }
            /*for (int i = 0; i < 4*n; i++) {
                cout << "(" << st[i].mod0 << " " << st[i].mod1 << " " << st[i].mod2 << " " << st[i].flag << " " << st[i].lazy << "), ";
            }*/
        }
   }
}

/*Max subsegment sum in range*/

/**
 * Description: Segment Tree with custom merge function.
 * Usage: construct O(N), query O(lg(N)), update O(lg(N))
 * Source: https://github.com/dragonslayerx
 */

#include <iostream>
#include <cstdio>
using namespace std;

#define MAX 50100
#define INF -1000000000

struct node {
    int sum;
    int maxs, prefix, suffix;
    node(){
        sum = prefix = suffix = 0;
        maxs = INF;
    }

    node(int sum, int maxs, int prefix, int suffix) {
        setNode(sum, maxs, prefix, suffix);
    }

    void setNode(int sum, int maxs, int prefix, int suffix){
        this->sum =sum;
        this->maxs=maxs;
        this->prefix=prefix;
        this->suffix=suffix;
    }
};

int a[MAX];
node st[4*MAX];

node merge(node left, node right){
    node t;
    t.prefix = max(left.prefix, left.sum+right.prefix);
    t.suffix = max(right.suffix, right.sum+left.suffix);
    t.sum = left.sum+right.sum;
    t.maxs = left.maxs;
    t.maxs = max(t.maxs, right.maxs);
    t.maxs = max(t.maxs, left.suffix+right.prefix);
    return t;
}

node construct(int n, int ll, int rl){
    if (ll == rl) {
        st[n].setNode(a[ll], a[ll], a[ll], a[ll]);
    } else {
        node left = construct(2*n+1, ll, (ll+rl)/2);
        node right = construct(2*n+2, (ll+rl)/2+1, rl);
        st[n] = merge(left, right);
    }
    return st[n];
}

node query(int n, int ll, int rl, int x, int y){
    int mid = (ll+rl)/2;
    if (x==ll &&  y==rl) return st[n];
    else if (y <= mid) return query(2*n+1, ll, mid, x, y);
    else if (x > mid) return query(2*n+2, mid+1, rl, x, y);
    else {
        node left = query(2*n+1, ll, (ll+rl)/2, x, mid);
        node right = query(2*n+2, (ll+rl)/2+1, rl, mid+1, y);
        return merge(left, right);
    }
}

node update(int n, int ll, int rl, int p, int val){
    if (p < ll || p > rl) return st[n];
    if (p == ll &&  p == rl) {
        st[n].setNode(val, val, val, val);
        return st[n];
    } else {
        int mid = (ll+rl)/2;
        node left = update(2*n+1, ll, (ll+rl)/2, p, val);
        node right = update(2*n+2, (ll+rl)/2+1, rl, p, val);
        st[n] = merge(left, right);
    }
    return st[n];
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", a+i);
    construct(0, 0, n-1);
    int q;
    scanf("%d", &q);
    while (q--) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--, y--;
        printf("%d\n", query(0, 0, n-1, x, y).maxs);
    }
}


/*2D Segment Trees*/

e.i/**
 * Description: Segment Tree 2D (Support point updates and associative operations like sum, max on a 2-D integer matrix)
 * Usage: construct O(NM),
 *      query O( lg(N) lg(M) ),
 *  update O( lg(N) lg(M) )
 * Source: https://github.com/dragonslayerx
 */
class SegTree2D {
    vector<vector<long long> > segtree;
    size_t n, m;

    bool OUT(int l, int r, int ql, int qr){
        return (qr < l || ql > r);
    }

    bool IN(int l, int r, int ql, int qr){
        return (ql >= l && qr <= r);
    }

    long long build_y(int node_x, int lx, int rx, int node_y, int ly, int ry, vector<vector<long long> > &array){
        if (ly == ry) {
            if (lx == rx) {
                segtree[node_x][node_y] = array[lx][ly];
            } else {
                segtree[node_x][node_y] = operation(segtree[node_x * 2 + 1][node_y], segtree[node_x * 2 + 2][node_y]);
            }
            return segtree[node_x][node_y];
        }
        int my = (ly + ry)/2;
        long long left = build_y(node_x, lx, rx, node_y * 2 + 1, ly, my, array);
        long long right = build_y(node_x, lx, rx, node_y * 2 + 2, my + 1, ry, array);
        segtree[node_x][node_y] = operation(left, right);
        return segtree[node_x][node_y];
    }

    long long build_x(int node_x, int lx, int rx, vector<vector<long long> > &array){
        if (lx != rx) {// demarcs that branching is still possible
            int mx = (lx + rx)/2;
            build_x(node_x * 2 + 1, lx, mx, array);
            build_x(node_x * 2 + 2, mx + 1, rx, array);
        }
        build_y(node_x, lx, rx, 0, 0, m - 1, array);
    }


    long long query_y(int node_x, int node_y, int ly, int ry, int qly, int qry){
        if (OUT(qly, qry, ly, ry)) {
            return def;
        } else if (IN(qly, qry, ly, ry)) {
            return segtree[node_x][node_y];
        }
        int my = (ly + ry)/2;
        long long left = query_y(node_x, node_y * 2 + 1, ly, my, qly, qry);
        long long right = query_y(node_x, node_y * 2 + 2, my + 1, ry, qly, qry);
        return operation(left, right);
    }

    long long query_x(int node_x, int lx, int rx, int qlx, int qrx, int qly, int qry){
        if (OUT(qlx, qrx, lx, rx)) {
            return def;
        } else if (IN(qlx, qrx, lx, rx)) {
            return query_y(node_x, 0, 0, m - 1, qly, qry);
        }
        int mx = (lx + rx)/2;
        long long left = query_x(node_x * 2 + 1, lx, mx, qlx, qrx, qly, qry);
        long long right = query_x(node_x * 2 + 2, mx + 1, rx, qlx, qrx, qly, qry);
        return operation(left, right);
    }

    long long update_y(int node_x, int lx, int rx, int node_y, int ly, int ry, int uy, int update_value){
        if (uy > ry || uy < ly) {
            return segtree[node_x][node_y];
        }
        if (ly == ry && ly == uy) {
            if (lx == rx) {
                segtree[node_x][node_y] = update_value;
            } else {
                segtree[node_x][node_y] = operation(segtree[node_x * 2 + 1][node_y], segtree[node_x * 2 + 2][node_y]);
            }
            return segtree[node_x][node_y];
        }
        int my = (ly + ry)/2;
        long long left = update_y(node_x, lx, rx, node_y * 2 + 1, ly, my, uy, update_value);
        long long right = update_y(node_x, lx, rx, node_y * 2 + 2, my + 1, ry, uy, update_value);
        segtree[node_x][node_y] = operation(left, right);
        return segtree[node_x][node_y];
    }

    void update_x(int node_x, int lx, int rx, int ux, int uy, long long update_value){
        if (ux > rx || ux < lx) {
            return;
        } if (lx == rx && lx == ux) {
            update_y(node_x, lx, rx, 0, 0, m - 1, uy, update_value);
            return;
        }
        int mx = (lx + rx)/2;
        update_x(node_x * 2 + 1, lx, mx, ux, uy, update_value);
        update_x(node_x * 2 + 2, mx + 1, rx, ux, uy, update_value);

        update_y(node_x, lx, rx, 0, 0, m - 1, uy, update_value);
    }


public:
    SegTree2D(int n, int m, long long def): def(def), n(n), m(m) {
         segtree.resize(4*n, vector<long long>(4*m));
    }

    SegTree2D(vector<vector<long long> > &array, int n, int m, long long def): def(def), n(n), m(m) {
        segtree.resize(4*n, vector<long long>(4*m));
        construct(array);
    }

    void construct(vector<vector<long long> > &array){
        build_x(0, 0, n - 1, array);
    }

    long long query(int qlx, int qrx, int qly, int qry){
        return query_x(0, 0, n - 1, qlx, qrx, qly, qry);
    }

    void update(int ux, int uy, long long update_value){
        update_x(0, 0, n - 1, ux, uy, update_value);
    }

#ifdef DEBUG
 void print(){
    for (int i = 0; i < 4*n; i++) {
        for (int j = 0; j < 4*m; j++)
            printf("(%d, %d)", segtree[i][j].maxx, segtree[i][j].count);
        cout << endl;
    }
 }
#endif

private:
    long long operation(long long left, long long right){
        return max(left, right);
    }
};

int main()
{
    int tc;
    scanf("%d", &tc);
    for (int t=1; t<=tc; t++) {
        printf("Case %d:\n", t);
        int n, q;
        scanf("%d%d", &n, &q);
        vector<vector<int> > array(n, vector<int> (n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &array[i][j]);
            }
        }
        SegTree2D<int> S(array, n, n, 0);
        while (q--) {
            int x, y, s;
            scanf("%d%d%d", &x, &y, &s);
            x--, y--;
            //cout << x << " " << y << " " << x+s-1 << " " << y+s-1 << endl;
            printf("%d\n", S.query(x, x+s-1, y, y+s-1));
        }
    }
}

/*Dynamic Segment Trees - Insertion/Deletion between elements*/
/**
 * Description: Dynamic segment tree (Perform associative operations on dynamic array. Support insertion, deletion of elements at any index, point updates)
 * Usage: insert O(lg(N)), erase O(lg(N)), update O(lg(N)), query O(lg(N)) 
 * Source: https://github.com/dragonslayerx 
 * Note: Override augment function for supporting other associative operations
 */

template<typename Tv>
struct node {
    Tv val, mval;
    int size, pr;
    node *l, *r;
    node(Tv val, int pr) {
        this->val = this->mval = val;
        this->size = 1;
        this->pr = pr;
        this->l = this->r = NULL;
    }
};
 
template <typename Tv>
ostream& operator <<(ostream &o, node<Tv> &x) {
    o << "{val=" << x.val << ", mval=" << x.mval << ", size=" << x.size << ", pr=" << x.pr << "}";
    return o;
}
 
template<typename Tv>
class DST {
    node<Tv> *root;
 
    int getSize(node<Tv> *p) {
        if (p == NULL) return 0;
        else return p->size;
    }
 
    Tv getVal(node<Tv> *p) {
        if (p==NULL) return 0;
        else return p->mval;
    }
 
    void augment(node<Tv> *p) {
        if (p==NULL) return;
        else {
            p->size = getSize(p->l) + getSize(p->r) + 1;
            // Change here 
            p->mval = p->val + getVal(p->l) + getVal(p->r);
        }
    }
 
    node<Tv>* rightRotate(node<Tv>* x){
        node<Tv> *y = x->l;
        node<Tv> *B = y->r;
 
        x->l = B;
        y->r = x;
 
        augment(x); augment(y);
        return y;
    }
 
    node<Tv>* leftRotate(node<Tv>* x){
        node<Tv> *y = x->r;
        node<Tv> *B = y->l;
 
        x->r = B;
        y->l = x;
 
        augment(x); augment(y);
        return y;
    }
 
    node<Tv>* insert(node<Tv> *p, int pos, Tv x, int pr) {
        if (p==NULL) {
            return new node<Tv>(x, pr);
        } else {
            int sz = getSize(p->l);
            if (pos <= sz) {
                p->l = insert(p->l, pos, x, pr);
                augment(p);
                node<Tv> *l = p->l;
                if (l->pr < p->pr) {
                    return rightRotate(p);
                }
            } else {
                p->r = insert(p->r, pos-sz-1, x, pr);
                augment(p);
                node<Tv> *r = p->r;
                if (r->pr < p->pr) {
                    return leftRotate(p);
                }
            }
            return p;
        }
    }
 
    void update(node<Tv> *p, int pos, Tv x) {
        int sz = getSize(p->l);
        if (pos == sz) {
            p->val += x;
        } else if (pos < sz) {
            update(p->l, pos, x);
        } else {
            update(p->r, pos-sz-1, x);
        }
        augment(p);
    }
 
 
    node<Tv>* merge(node<Tv> *lt, node<Tv> *rt) {
        if (lt==NULL) return rt;
        else if (rt==NULL) return lt;
        else {
            if (lt->pr < rt->pr) {
                lt->r = merge(lt->r, rt);
                augment(lt);
                return lt;
            } else {
                rt->l = merge(lt, rt->l);
                augment(rt);
                return rt;
            }
        }
    }
 
    pair<node<Tv>*, node<Tv>*> split(node<Tv> *p, int pos) {
        node<Tv> *tmpRt = insert(p, pos, 0, -1);
        return make_pair(tmpRt->l, tmpRt->r);
    }
 
    void inorder(node<Tv> *p, ostream &o) {
        if (p==NULL) return;
        else {
            inorder(p->l, o);
            o << *p << endl;
            inorder(p->r, o);
        }
    }
 
public:
    DST() {srand(time(NULL)); this->root = NULL;}
 
    void insert(int pos, Tv x) {
        root = insert(root, pos, x, rand()%100000);
    }
 
    void update(int pos, Tv x) {
        update(root, pos, x);
    }
 
    void erase(int pos) {
        pair<node<Tv>*, node<Tv>*> p = split(root, pos);
        pair<node<Tv>*, node<Tv>*> q = split(p.second, 1);
        root = merge(p.first, q.second);
    }
 
    Tv query(int l, int r) {
        pair<node<Tv>*, node<Tv>* > p = split(root, l);
        pair<node<Tv>*, node<Tv>* > q = split(p.second, r-l+1);
        Tv v = q.first->mval;
        root = merge(merge(p.first, q.first), q.second);
        return v;
    }
 
    void inorder(ostream &o) {
        inorder(root, o);
    }
 
    friend std::ostream& operator<<(ostream &o, DST<Tv> D) {
        D.inorder(o);
        return o;
    }
};


/*Dynamic Segment Trees - Reverse a segment*/
/**
 * Description: Dynamic Segment tree (Support for inbetween insertion and array reversal)   
 * Usage: See below. insert O(lg(N)), reverse O(lg(N)), get O(lg(N))
 * Note: Override augment function appropriately for supporting distinct aggregate operation.
 * Source: https://github.com/dragonslayerx 
 */

const int MAX = 100005;
const int MOD = 1000000000+7;
const int INF = 1000000000;

struct node {
    int val, cnt[15];
    int size, pr;
    bool rev;
    node *l, *r;
    node(int val, int pr) {
        this->val = val;
        this->pr = pr;
        this->l = this->r = NULL;
        this->rev = false;
        this->size = 1;
        memset(cnt, 0, sizeof(cnt));
        this->cnt[val]++;
    }

    friend ostream& operator <<(ostream &o, node &x) {
        o << "{ x= " << &x << ", val=" << x.val << ", size=" << x.size << ", rev=" << x.rev << ", pr=" << x.pr;
        o << "l = " << x.l << " " << ", r = " << x.r << " ";
        o << " [";
        for (int i = 0; i < 15; i++) {
            o << x.cnt[i] << " ";
        }
        o << "] }";
    }
};


class Treap {
    node *root;

    int getSize(node *p) {
        if (p == NULL) return 0;
        else return p->size;
    }

    int getCnt(node *p, int i) {
        if (p == NULL) return 0;
        else return p->cnt[i];
    }

    void augment(node *p) {
        if (p==NULL) return;
        else {
            if (p->rev) {
                if (p->l) p->l->rev ^= 1;
                if (p->r) p->r->rev ^= 1;
                swap(p->l, p->r);
                p->rev=false;
            }
            p->size = getSize(p->l)+getSize(p->r)+1;
            // Change here for support for a different augment function
    for (int i = 0; i < 15; i++) p->cnt[i] = getCnt(p->l, i)+getCnt(p->r, i);
            p->cnt[p->val]++;
    //
        }
    }

    node* rightRotate(node* x){
        node *y = x->l;
        node *B = y->r;

        x->l = B;
        y->r = x;

        augment(x); augment(y);
        return y;
    }

    node* leftRotate(node* x){
        node *y = x->r;
        node *B = y->l;

        x->r = B;
        y->l = x;

        augment(x); augment(y);
        return y;
    }

    node* insert(node *p, int pos, int x, int pr) {
        if (p==NULL) {
            return new node(x, pr);
        } else {
            augment(p);
            int sz = getSize(p->l);
            if (pos <= sz) {
                p->l = insert(p->l, pos, x, pr);
                augment(p);
                node* l = p->l;
                if (l->pr < p->pr) {
                    return rightRotate(p);
                }
            } else {
                p->r = insert(p->r, pos-sz-1, x, pr);
                augment(p);
                node* r = p->r;
                if (r->pr < p->pr) {
                    return leftRotate(p);
                }
            }
            return p;
        }
    }

    node* merge(node *lt, node *rt) {
        if (lt==NULL) return rt;
        else if (rt==NULL) return lt;
        else {
            if (lt->pr < rt->pr) {
                augment(lt);
                lt->r = merge(lt->r, rt);
                augment(lt);
                return lt;
            } else {
                augment(rt);
                rt->l = merge(lt, rt->l);
                augment(rt);
                return rt;
            }
        }
    }

    pair<node*, node*> split(node* p, int pos) {
        node* tmpRt = insert(p, pos, 0, -1);
        return make_pair(tmpRt->l, tmpRt->r);
    }

    void inorder(node *p, ostream &o) {
        if (p==NULL) return;
        else {
            inorder(p->l, o);
            o << *p << endl;
            inorder(p->r, o);
        }
    }

public:
    Treap(){
        srand(time(NULL));
        root=NULL;
    }

    void insert(int pos, int x) {
        root = insert(root, pos, x, rand());
    }

    void reverse(int l, int r) {
        pair<node*, node*> p = split(root, l);
        pair<node*, node*> q = split(p.second, r-l+1);
        (q.first)->rev ^= 1;
        root = merge(merge(p.first, q.first), q.second);
    }

    void get(int l, int r, int cnt[]) {
        pair<node*, node*> p = split(root, l);
        pair<node*, node*> q = split(p.second, r-l+1);
        for (int i = 0; i < 15; i++) {
            cnt[i] = (q.first)->cnt[i];
        }
        root = merge(merge(p.first, q.first), q.second);
    }

    void inorder(ostream &o) {
        inorder(root, o);
    }

    friend std::ostream& operator<<(ostream &o, Treap D) {
        D.inorder(o);
        return o;
    }

};


/*segment_tree_persistent*/

/**
 * Description: Persistent Segment trees (Version Query)
 * Usage: See below update O(lg(N)), query O(lg(N)), construct O(Nlg(N)) 
 * Source: https://github.com/dragonslayerx 
 */

struct Node {
    long long value;
    Node *left, *right;
    Node() {
        left=right=NULL;
    }
};

const int MAX = 100005; // # of updates
Node *root[MAX];
class PersistentST {

    const int n; //size of array
    int version; // current version
    int size;

    Node* createNewNode() {
        return new Node;
    }

    long long mergeFunction(Node *left, Node *right) {
        return left->value + right->value;
    }


    Node* construct(long long val[], int l, int r) {
        Node *x = createNewNode();;
        if (l == r) {
            x->value = (val==NULL)?0:val[l]; // NULL in case to be initialized with 0 initially
            return x;
        } else {
            int mid = (l+r)/2;
            x->left = construct(val, l, mid);
            x->right = construct(val, mid+1, r);
            x->value = mergeFunction(x->left, x->right);
            return x;
        }
    }

    Node* update(int l, int r, Node *prevVersionPtr, const int pos, const long long updatedVal) {
        Node *x = createNewNode();
        if (l == r) {
            x->value = prevVersionPtr->value + updatedVal;
        } else {
            int mid = (l+r)/2;
            if (pos <= mid) {
                x->left = update(l, mid, prevVersionPtr->left, pos, updatedVal);
                x->right = prevVersionPtr->right;
            } else {
                x->right = update(mid+1, r, prevVersionPtr->right, pos, updatedVal);
                x->left = prevVersionPtr->left;
            }
            x->value = mergeFunction(x->left, x->right);
        }
        return x;
    }

    long long query(Node *x, int l, int r, const int ql, const int qr) {
        if (r < ql || l > qr) {
            return 0;
        } else if (l >= ql && r <= qr) {
            return x->value;
        } else {
            int mid = (l+r)/2;
            long long left = query(x->left, l, mid, ql, qr);
            long long right = query(x->right, mid+1, r, ql, qr);
            return left+right;
        }
    }

public:

    PersistentST(int n): n(n) {
        version = 0;
        size = 0;
    }

    void construct(long long val[]) {
        root[0]=construct(val, 0, n-1);
    }

    void update(int p, long long x) {
        root[version+1]=update(0, n-1, root[version], p, x);
        version++;
    }

    long long query(int queryVersion, int l, int r) {
        return query(root[queryVersion], 0, n-1, l, r);
    }

    Node *getVersion(int ver) {
        return root[ver];
    }
};

int main() {
    long long a[5] = {1, 2, 3, 4, 5};
    PersistentST S(5);
    S.construct(a);
    cout << S.query(0, 1, 2) << endl;
    S.update(1, 5);
    cout << S.query(1, 1, 2) << endl;
}


/*segment_tree_persistent_order_stat*/

/**
 * Description: Persistent Segment trees (Order Statistics)
 * Usage: See below <O(Nlg(N)), O(lg(N))> 
 * Source: https://github.com/dragonslayerx 
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

struct Node {
    long long value;
    Node *left, *right;
    Node() {
        left=right=NULL;
    }
};

const int MAX = 100005; // # of updates
Node *root[MAX];
class PersistentST {

    const int n; //size of array
    int version; // current version
    int size;
    
    Node* createNewNode() {
        return new Node;
    }

    long long mergeFunction(Node *left, Node *right) {
        return left->value + right->value;
    }


    Node* construct(long long val[], int l, int r) {
        Node *x = createNewNode();;
        if (l == r) {
            x->value = (val==NULL)?0:val[l]; // NULL in case to be initialized with 0 initially
            return x;
        } else {
            int mid = (l+r)/2;
            x->left = construct(val, l, mid);
            x->right = construct(val, mid+1, r);
            x->value = mergeFunction(x->left, x->right);
            return x;
        }
    }

    Node* update(int l, int r, Node *prevVersionPtr, const int pos, const long long updatedVal) {
        Node *x = createNewNode();
        if (l == r) {
            x->value = prevVersionPtr->value + updatedVal;
        } else {
            int mid = (l+r)/2;
            if (pos <= mid) {
                x->left = update(l, mid, prevVersionPtr->left, pos, updatedVal);
                x->right = prevVersionPtr->right;
            } else {
                x->right = update(mid+1, r, prevVersionPtr->right, pos, updatedVal);
                x->left = prevVersionPtr->left;
            }
            x->value = mergeFunction(x->left, x->right);
        }
        return x;
    }

    long long query(Node *x, int l, int r, const int ql, const int qr) {
        if (r < ql || l > qr) {
            return 0;
        } else if (l >= ql && r <= qr) {
            return x->value;
        } else {
            int mid = (l+r)/2;
            long long left = query(x->left, l, mid, ql, qr);
            long long right = query(x->right, mid+1, r, ql, qr);
            return left+right;
        }
    }

public:

    PersistentST(int n): n(n) {
        version = 0;
        size = 0;
    }

    void construct(long long val[]) {
        root[0]=construct(val, 0, n-1);
    }

    void update(int p, long long x) {
        root[version+1]=update(0, n-1, root[version], p, x);
        version++;
    }

    long long query(int queryVersion, int l, int r) {
        return query(root[queryVersion], 0, n-1, l, r);
    }

    Node *getVersion(int ver) {
        return root[ver];
    }
};

class OrderStat {
public:
    const int n;
    PersistentST S;

    OrderStat(long long a[], int n) : n(n), S(n) {
        S.construct(NULL);
        // Map all elements of a from 0..n-1 first
        for (int i = 0; i < n; i++) {
            S.update(a[i], +1);
        }
        /*for (int i = 0; i <= n; i++) {
            for (int j = 0; j < n; j++) {
                cout << S.query(i, j, j) << " ";
            }
            cout << endl;
        }*/
    }

    int getOrderStat(int ql, int qr, int k) {
        assert(k <= qr-ql+1);
        int l = 0, r = n-1;
        Node *pL = S.getVersion(ql), *pR = S.getVersion(qr+1);
        while (l < r) {
            int mid = (l+r)/2;
            int count = (pR->left->value - pL->left->value);
            if (count >=  k) {
                pL=pL->left, pR=pR->left;
                r = mid;
            } else {
                k-=count;
                pL=pL->right, pR=pR->right;
                l = mid+1;
            }
        }
        return l;
    }
};

int main() {
    long long a[5] = {1, 1, 3, 2, 4};
    OrderStat O(a, 5);
    cout << O.getOrderStat(0, 4, 5) << endl;;
}


/**/