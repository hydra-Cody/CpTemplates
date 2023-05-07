//0-1 Knapsack
void solve() {
    int n, w; cin >> n >> w;
    int weight[n], val[n];
    for (int i = 0; i < n; i++) cin >> weight[i];
    for (int i = 0; i < n; i++) cin >> val[i];

    int dp[w + 1] = {};
    for (int i = 0; i < n; i++)
        for (int j = w; j >= weight[i]; j--)
            dp[j] = max(dp[j], dp[j - weight[i]] + val[i]);
    cout << dp[w] << "\n";
}
//-------------------------------------------------------------------------------
//Coin Change
void solve() {
    int n, x; cin >> n >> x;
    int arr[n]; 
    for (int i = 0; i < n; i++) cin >> arr[i];

    // 1) Problem link: https://cses.fi/problemset/task/1635
    vector<int> dp(x + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= x; i++) 
        for (int j : arr) 
            if (i - j >= 0) 
                dp[i] = (dp[i] + dp[i - j]) % MOD; 
    cout << dp[x] << "\n";

    // 2) Problem link: https://cses.fi/problemset/task/1636
    vector<int> dp(x + 1, 0);
    dp[0] = 1;
    for (int j : arr) 
        for (int i = 1; i <= x; i++) 
            if (i - j >= 0) 
                dp[i] = (dp[i] + dp[i - j]) % MOD; 
    cout << dp[x] << "\n";

    // 3) Problem link: https://cses.fi/problemset/task/1634
    vector<int> dp(x + 1, INF);
    dp[0] = 0;
    for (int i = 1; i <= x; i++) 
        for (int j : arr) 
            if (i - j >= 0) 
                dp[i] = min(dp[i], dp[i - j] + 1);
    cout << (dp[x] == INF ? -1 : dp[x]) << "\n";
}
//------------------------------------------------------------------------------------
// Max Sum Subarray: 1D, 2D

void solve() {
    int n; cin >> n;
    // set to -LINF to return non-empty maximum subarray sum, otherwise set to 0
    ll ans = -LINF, cur = -LINF; 
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        cur = max(x, cur + x);
        // cur = max(0, cur + x);
        ans = max(ans, cur);
    }
    cout << ans << "\n";
}

void solve() {
    int n; cin >> n;
    ll ps[n + 1][n + 1] = {};
    // Creating a prefix sum table (horizontally)
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> ps[i][j];
            ps[i][j] += ps[i][j - 1];
        }
    }

    // 2D max sum subarray
    ll ans = 0;
    for (int l = 1; l <= n; l++) { // looping through all pairs of columns, running 1D maxsum on a column
        for (int r = l; r <= n; r++) {
            ll cur = 0;
            for (int i = 1; i <= n; i++) {
                ll x = ps[i][r] - ps[i][l - 1];
                cur = max(0ll, cur + x);
                ans = max(ans, cur);        
            }
        }
    }
    cout << ans << "\n";
}
//----------------------------------------------------------------------------
//Longest Common Subsequence
void solve() {
    string x, y; cin >> x >> y;
    int n = x.size(), m = y.size();
    int dp[n + 1][m + 1] = {};
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (x[i - 1] == y[j - 1]) 
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            else
                dp[i][j] = max({dp[i][j], dp[i - 1][j], dp[i][j - 1]});
        }
    }
    cout << dp[n][m];
}
//-----------------------------------------------------------------------------
//Longest Increasing Subsequence
void solve() {
    int n; cin >> n;
    vector<int> dp;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        auto it = lower_bound(dp.begin(), dp.end(), x);
        if (it == dp.end()) dp.push_back(x);
        else *it = x;
    }
    cout << dp.size() << "\n";
}
//----------------------------------------------------------------------------
//Digit DP
vector<int> num;
ll dp[10][9 * 10][2];

// dp[pos][sum][flag]
// pos = current position, starting from the left (0-index)
// sum = sum of all digits till the given position
// flag = the number we are building has already become smaller than b? [0 = no, 1 = yes]

ll memo(int pos, int sum, int flag) {
    if (pos == num.size()) return sum;
    if (dp[pos][sum][flag] != -1) return dp[pos][sum][flag];

    ll res = 0;
    int lmt = (flag) ? 9 : num[pos];
    for (int i = 0; i <= lmt; i++) {
        int next_flag = (i < lmt) ? 1 : flag;
        res += memo(pos + 1, sum + i, next_flag);
    }
    return dp[pos][sum][flag] = res;
}

ll calc(int n) {
    num.clear();
    while (n) {
        num.push_back(n % 10);
        n /= 10;
    }
    reverse(num.begin(), num.end());
    memset(dp, -1, sizeof dp);
    return memo(0, 0, 0);
}

void solve() {
    while (true) {
        int a, b; cin >> a >> b;
        if (a == -1 && b == -1) return;
        cout << calc(b) - calc(a - 1) << "\n";
    }
}
//--------------------------------------------------------------------------------
//SOS DP
int inv(int x) {return x ^ ((1 << MAX_M) - 1);}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    vector<int> dp(1 << MAX_M), dp_inv(1 << MAX_M);
    for (int &x : a) {
        cin >> x;
        dp[x]++;
        dp_inv[inv(x)]++;
    }
    for (int i = 0; i < MAX_M; i++) {
        for (int mask = 0; mask < (1 << MAX_M); mask++) {
            if (mask & (1 << i)) {
                dp[mask] += dp[mask ^ (1 << i)];
                dp_inv[mask] += dp_inv[mask ^ (1 << i)];
            }
        }
    }
    for (int x : a) {
        cout << dp[x] << " " << dp_inv[inv(x)] << " " << n - dp[inv(x)] << "\n";
    }
}
//------------------------------------------------------------------------------
//Weighted Job Scheduling
void solve() {
    int n; cin >> n;
    ar<ll,3> arr[n];
    for (int i = 0; i < n; i++) cin >> arr[i][1] >> arr[i][0] >> arr[i][2];
    sort(arr, arr + n); // sort based on end time
    ll dp[n];
    dp[0] = arr[0][2];
    for (int i = 1; i < n; i++) {
        int k = lower_bound(arr, arr + n, ar<ll,3>{arr[i][1], 0, 0}) - arr - 1;
        if (k >= 0)
            dp[i] = max(dp[i - 1], dp[k] + arr[i][2]);
        else
            dp[i] = max(dp[i - 1], arr[i][2]);
 
    }
    cout << dp[n - 1] << "\n";
}
//------------------------------------------------------------------------------
//Cutting Sticks
int opt[MAX_N][MAX_N];

void solve() {
    while (true) {
        int x; cin >> x;
        if (!x) return;

        int n; cin >> n;
        int arr[n + 2];
        // adding the beginning point and the ending point
        arr[0] = 0; arr[n + 1] = x;
        for (int i = 1; i <= n; i++) cin >> arr[i];
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, INF));
        for (int i = 0; i < n + 1; i++) {
            dp[i][i + 1] = 0;
            opt[i][i + 1] = i;
        }
        // range dp
        for (int i = n + 1; i >= 0; i--) {
            for (int j = i; j <= n + 1; j++) {
                for (int k = i + 1; k < j; k++) {
                    if (dp[i][j] > dp[i][k] + dp[k][j] + arr[j] - arr[i]) {
                        dp[i][j] = dp[i][k] + dp[k][j] + arr[j] - arr[i];
                    }
                }
                // Knuth Optimization (only need to change 2 lines)
                // Condition: dp[i][j] = min{i < k < j}(dp[i][k] + dp[k][j]) + C[i][j]
                // for (int k = opt[i][j - 1]; k <= opt[i + 1][j]; k++) {
                //     if (dp[i][j] > dp[i][k] + dp[k][j] + arr[j] - arr[i]) {
                //         dp[i][j] = dp[i][k] + dp[k][j] + arr[j] - arr[i];
                //         opt[i][j] = k;
                //     }
                // }
            }
        }
        cout << "The minimum cutting is " << dp[0][n + 1] << ".\n"; 
    }
}

//-----------------------------------------------------------------
//Matrix Chain
void solve() {
    int n;
    while(cin >> n) {
        int arr[n][n];
        for (int i = 0; i < n; i++) cin >> arr[i][i];
        int dp[n][n];
        // diagonal dp (another way to achieve the same thing as range dp)
        for (int l = 0; l < n; l++) {
            for (int i = 0, j = i + l; j < n; i++, j++) {
                if (l == 0) dp[i][j] = 0;
                else {
                    dp[i][j] = INF;
                    for (int k = i; k < j; k++) {
                        if (dp[i][j] > dp[i][k] + dp[k + 1][j] + arr[i][k] * arr[k + 1][j]) {
                            dp[i][j] = dp[i][k] + dp[k + 1][j] + arr[i][k] * arr[k + 1][j];
                            arr[i][j] = (arr[i][k] + arr[k + 1][j]) % 100;
                        }
                    }
                }
            }
        }
        cout << dp[0][n - 1] << "\n";
    }
}

//-----------------------------------------------------------------------
//Elevator Rides

void solve() {
    int n, x; cin >> n >> x;
    int weight[n]; 
    for (int i = 0; i < n; i++) cin >> weight[i];

    ar<int,2> dp[1 << n];
    // dp[i][0] = the minimum number of rides for bitmask i
    // dp[i][1] = the minimum weight of the last ride for bitmask i
    dp[0] = {0, 0};
    for (int i = 1; i < (1 << n); i++) {
        // upper bound is n + 1 rides
        dp[i] = {n + 1, 0};
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                auto cur = dp[i ^ (1 << j)];
                if (cur[1] + weight[j] <= x) { // add j to the current ride
                    cur[1] += weight[j];
                }
                else { // reserves a new ride for j
                    cur[0]++;
                    cur[1] = weight[j];
                }
                dp[i] = min(dp[i], cur);
            }
        }
    }
    // if dp[i].second > 0, then the answer is dp[i].first + 1
    cout << dp[(1 << n) - 1][0] + (dp[(1 << n) - 1][1] > 0);
}
//-----------------------------------------------------------------------
//Travelling Salesman Problem

int n, x[MAX_N], y[MAX_N], adj[MAX_N][MAX_N], dp[1 << MAX_N][MAX_N];

int tsp(int mask, int u) {
    if (mask == (1 << n) - 1) return adj[u][0]; // finish all nodes (bitmask == 11...11)
    if (dp[mask][u] != -1) return dp[mask][u];

    int ans = INF;
    // Visit all the unvisited nodes and take the best route
    for (int v = 0; v < n; v++) {
        if (!(mask & (1 << v))) { // this node is unvisited
            int cur = adj[u][v] + tsp(mask | (1 << v), v);
            ans = min(ans, cur);
        }
    }
    return dp[mask][u] = ans;
}

void solve() {
    int xs, ys; cin >> xs >> ys; // not important
    cin >> x[0] >> y[0] >> n; n++;
    for (int i = 1; i < n; i++) cin >> x[i] >> y[i];
    for (int i = 0; i < n; i++) 
        for (int j = i; j < n; j++)
            adj[i][j] = adj[j][i] = abs(x[i] - x[j]) + abs(y[i] - y[j]);
    memset(dp, -1, sizeof dp);
    // start from node 0 (bitmask = 00...01)
    cout << "The shortest path has length " << tsp(1, 0) << "\n";
}
//------------------------------------------------------------------------
//Deque Trick
void solve() {
    int n, k, x; cin >> n >> k >> x;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    ll dp[n + 1][x + 1]; // dp[i][j] = answer using j pictures from the first i-th pictures
    memset(dp, -0x3f, sizeof dp);
    dp[0][0] = 0;
    for (int j = 1; j <= x; j++) {
        deque<ar<ll,2>> dq; // {id, value}
        dq.push_back({j - 1, dp[j - 1][j - 1]});
        for (int i = j; i <= n; i++) {
            while (dq.size() && dq.front()[0] < i - k) dq.pop_front();
            dp[i][j] = dq.front()[1] + a[i];
            while (dq.size() && dp[i][j - 1] >= dq.back()[1]) dq.pop_back();
            dq.push_back({i, dp[i][j - 1]});
        }

    }
    ll ans = -1;
    for (int i = 0; i < k; i++) ans = max(ans, dp[n - i][x]);
    cout << ans << "\n";
}
//---------------------------------------------------------------------------------
//Divide & Conquer Trick

int n, m, a[MAX_N];
int ps[MAX_N][MAX_N], dp[MAX_N][MAX_N];
// dp[i][j] = minimum unhappiness when splitting the first j-th people into i rows

int cost(int i, int j) {
    return ps[j][j] - ps[i - 1][j] - ps[j][i - 1] + ps[i - 1][i - 1];
}

void dac(int i, int l, int r, int ql, int qr) {
    if (l > r) return;
    int mid = (l + r) / 2;
    ar<int,2> res = {INF, INF};
    for (int k = ql; k <= min(mid, qr); k++) {
        res = min(res, {dp[i - 1][k - 1] + cost(k, mid), k});
    }
    dp[i][mid] = res[0];
    dac(i, l, mid - 1, ql, res[1]);
    dac(i, mid + 1, r, res[1], qr);
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {  
        for (int j = 1; j < i; j++) {
            ps[i][j] = a[j] > a[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ps[i][j] = ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1] + ps[i][j];
        }
    }
    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;

    // Naive O(mn^2) by directly applying dp[i][j] = min{dp[i - 1][k - 1] + cost(k, j)} for 1 <= k <= j
    // for (int i = 1; i <= m; i++) {
    //     for (int j = 1; j <= n; j++) {
    //         for (int k = 1; k <= j; k++) {
    //             dp[i][j] = min(dp[i][j], dp[i - 1][k - 1] + cost(k, j));
    //         }
    //     }
    // }
    
    // Optimised O(mnlogn) using D&C
    for (int i = 1; i <= m; i++) dac(i, i, n, i, n);

    cout << dp[m][n] << "\n";
}
//--------------------------------------------------------------------------------
//Convex Hull Trick

struct lichaotree {
    struct line {
        ll m, c;
        line(ll m, ll c): m(m), c(c) {}
        ll operator()(ll x) {return m * x + c;}
    };
    struct tdata {
        line seg;
        tdata *ln, *rn;
        tdata(line seg): seg(seg) {}
    };
    int n; tdata *st;
    lichaotree(int n): n(n) {st = new tdata({INF, INF});}
    void update(tdata *node, int start, int end, line y) {
        int mid = (start + end) / 2;
        bool b1 = y(start) < node->seg(start);
        bool b2 = y(mid) < node->seg(mid);
        if (b2) swap(node->seg, y);
        if (start + 1 == end) return;
        if (b1 != b2) {
            if (node->ln) update(node->ln, start, mid, y);
            else node->ln = new tdata(y);
        }
        else {
            if (node->rn) update(node->rn, mid, end, y);
            else node->rn = new tdata(y);
        }
    }
    ll query(tdata *node, ll start, ll end, ll x) {
        if (start + 1 == end) return node->seg(x);
        ll mid = (start + end) / 2;
        if (x < mid && node->ln) return min(node->seg(x), query(node->ln, start, mid, x));
        else if (node->rn) return min(node->seg(x), query(node->rn, mid, end, x));
        return node->seg(x);
    }
    void update(line y) {update(st, 0, n, y);}
    ll query(int x) {return query(st, 0, n, x);}
}; 

struct convexhull {
    struct line {
        ll m, c; 
        line(ll m, ll c): m(m), c(c) {}
        ll operator()(ll x) {return m * x + c;}
    };
    deque<line> dq;
    bool check(line p1, line p2, line p3) {
        return (p2.m - p1.m) * (p3.c - p2.c) >= (p3.m - p2.m) * (p2.c - p1.c);
    }
    void add(line y) { // decreasing slope
        while (dq.size() >= 2 && check(dq[dq.size() - 2], dq[dq.size() - 1], y)) dq.pop_back();
        dq.push_back(y);
    }
    ll query(ll x) { // min query, increasing x
        while (dq.size() >= 2 && dq[0](x) >= dq[1](x)) dq.pop_front();
        return dq[0](x);
    }
    ll query(ll x) { // min query, any x
        int lo = -1, hi = dq.size() - 1;
        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if (dq[mid](x) >= dq[mid + 1](x)) lo = mid;
            else hi = mid;
        }
        return dq[hi](x);
    }
};

void solve() {
    int n; ll c; cin >> n >> c;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<ll> dp(n, LINF);
    dp[0] = 0;
    lichaotree st(1e6 + 1);
    // convexhull cht;
    for (int i = 1; i < n; i++) {
        // Naive O(n^2)
        // for (int j = 0; j < i; j++) {
        //     dp[i] = min(dp[i], dp[j] + (a[i] - a[j]) * (a[i] - a[j]) + c);
        // }
        
        // dp[i] = a[i] * a[i] + c + min{-2 * a[j] * a[i] + a[j] * a[j] + dp[j]}
        // Better O(nlogn)

        st.update({-2 * a[i - 1], a[i - 1] * a[i - 1] + dp[i - 1]});
        dp[i] = a[i] * a[i] + c + st.query(a[i]);
    
        // cht.add({- 2 * a[i - 1], a[i - 1] * a[i - 1] + dp[i - 1]});
        // dp[i] = a[i] * a[i] + c + cht.query(a[i]);
    }
    cout << dp[n - 1] << "\n";
}
