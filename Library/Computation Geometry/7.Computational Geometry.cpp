/*Closest Pairs*/
// Given n points (x, y) on a plane, find the minimum distance between a pair of points
// Time complexity: (nlogn)
// Problem link: https://vjudge.net/problem/UVA-10245

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e4 + 1;
const ll MOD = 1e9 + 7;
const ll INF = 1e4;

struct pt {
    double x, y;
    bool operator< (pt a) { // sort based on x
        return (x == a.x) ? y < a.y : x < a.x;
    }
};

struct cmp { // custom comparator for set (sort based on y)
    bool operator() (pt a, pt b) {
        return (a.y == b.y) ? a.x < b.x : a.y < b.y;
    }
};

void solve() {
    while (true) {
        int n; cin >> n;
        if (!n) return;
        
        pt pnts[n];
        set<pt,cmp> box;
        for (int i = 0; i < n; i++) cin >> pnts[i].x >> pnts[i].y;
        sort(pnts, pnts + n); // sort bases on x-coordinates (from left to right)

        double ans = INF;
        /* Naive approach O(n^2) -> Searching through all pair of points
        for (int l = 0; l < n; l++) {
            for (int r = l + 1; r < n; r++) {
                if (pnts[r].second - pnts[l].second > ans) break; // this helps speed up the approach
                ans = min(ans, hypot(pnts[r].first - pnts[l].first, pnts[r].second - pnts[l].second));
            }
        }
        */
        box.clear();
        box.insert(pnts[0]);
        for (int l = 0, r = 1; r < n; r++) {
            // removing leftmost points that will not contribute to the minimum distance
            while (l < r && pnts[r].x - pnts[l].x >= ans)
                box.erase(pnts[l++]);
            auto lo = box.lower_bound({pnts[r].x, pnts[r].y - ans});
            auto hi = box.upper_bound({pnts[r].x, pnts[r].y + ans});
            for (; lo != hi; lo++)
                ans = min(ans, hypot(pnts[r].x - lo->x, pnts[r].y - lo->y));
            // A more succinct way to write
            // for (auto it = box.lower_bound({pnts[r].x - ans, pnts[r].y - ans}); it != box.end() && it->y - pnts[r].y <= ans; it++)
                // ans = min(ans, hypot(pnts[r].x - it->x, pnts[r].y - it->y));
            box.insert(pnts[r]);
        }

        if (ans == INF) cout << "INFINITY\n";
        else cout << fixed << setprecision(4) << ans << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}


/*Rectangle Union*/

// Given n rectangles on a plane (they are all parallel to the axis), find the union area of all the rectangles
// Each rectangle is defined by two points (x1, y1) bottom left and (x2, y2) top right
// Time complexity: O(n^2), can be improved to O(nlogn)
// Problem link: https://cses.fi/problemset/task/1741/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const l MOD = 1e9 + 7;
const ll INF = 1e9;

struct event {
    int id; // Index of rectangle in rects
    int type; // Type of event: 0 = Lower-left ; 1 = Upper-right
    event() {};
    event(int id, int type) : id(id), type(type) {};
};

struct point{
    int x, y;
};

int n, e = 0; // n = no. of rectangles, e = no. of events
point rects[MAX_N][2]; // Each rectangle consists of 2 points: [0] = lower-left ; [1] = upper-right
event events_v [2 * MAX_N]; // Events of horizontal sweep line
event events_h [2 * MAX_N]; // Events of vertical sweep line

bool in_set[MAX_N] = {0}; // Boolean array in place of balanced binary tree (set)
long long area = 0; // The output: Area of the union

bool compare_x(event a, event b) {
    return rects[a.id][a.type].x < rects[b.id][b.type].x;
}

bool compare_y(event a, event b) {
    return rects[a.id][a.type].y < rects[b.id][b.type].y;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> rects[i][0].x >> rects[i][0].y; // Lower-left coordinate
        cin >> rects[i][1].x >> rects[i][1].y; // Upper-right coordinate
        events_v[e] = event(i, 0);
        events_h[e++] = event(i, 0);
        events_v[e] = event(i, 1);
        events_h[e++] = event(i, 1);
    }
    sort(events_v, events_v + e, compare_x);
    sort(events_h, events_h + e, compare_y); // Pre-sort set of horizontal edges
    in_set[events_v[0].id] = 1;

    // Vertical sweep line
    for (int i = 1; i < e; i++){
        event cur = events_v[i], precur = events_v[i - 1];
        int cnt = 0; // Counter to indicate how many rectangles are currently overlapping

        // Delta_x: Distance between current sweep line and previous sweep line
        ll delta_x = rects[cur.id][cur.type].x - rects[precur.id][precur.type].x;
        if (delta_x < 0) continue;

        int begin_y;
        // Horizontal sweep line
        for (int j = 0; j < e; j++){
            if (in_set[events_h[j].id]){
                if (events_h[j].type == 0) {
                    if (cnt == 0) begin_y = rects[events_h[j].id][0].y; // Block starts
                    cnt++;
                }
                else {
                    cnt--;
                    if (cnt == 0) { // Block ends
                        ll delta_y = rects[events_h[j].id][1].y - begin_y;
                        area += delta_x * delta_y;
                    }
                }
            }
        }
        in_set[cur.id] = (cur.type == 0);
    }
    cout << area << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}

//-------------------------------------------------------------------------------------------
// Closet Pairs
struct pt {
    double x, y;
    bool operator< (pt a) { // sort based on x
        return (x == a.x) ? y < a.y : x < a.x;
    }
};

struct cmp { // custom comparator for set (sort based on y)
    bool operator() (pt a, pt b) {
        return (a.y == b.y) ? a.x < b.x : a.y < b.y;
    }
};

void solve() {
    while (true) {
        int n; cin >> n;
        if (!n) return;
        
        pt pnts[n];
        set<pt,cmp> box;
        for (int i = 0; i < n; i++) cin >> pnts[i].x >> pnts[i].y;
        sort(pnts, pnts + n); // sort bases on x-coordinates (from left to right)

        double ans = INF;
        /* Naive approach O(n^2) -> Searching through all pair of points
        for (int l = 0; l < n; l++) {
            for (int r = l + 1; r < n; r++) {
                if (pnts[r].second - pnts[l].second > ans) break; // this helps speed up the approach
                ans = min(ans, hypot(pnts[r].first - pnts[l].first, pnts[r].second - pnts[l].second));
            }
        }
        */
        box.clear();
        box.insert(pnts[0]);
        for (int l = 0, r = 1; r < n; r++) {
            // removing leftmost points that will not contribute to the minimum distance
            while (l < r && pnts[r].x - pnts[l].x >= ans)
                box.erase(pnts[l++]);
            auto lo = box.lower_bound({pnts[r].x, pnts[r].y - ans});
            auto hi = box.upper_bound({pnts[r].x, pnts[r].y + ans});
            for (; lo != hi; lo++)
                ans = min(ans, hypot(pnts[r].x - lo->x, pnts[r].y - lo->y));
            // A more succinct way to write
            // for (auto it = box.lower_bound({pnts[r].x - ans, pnts[r].y - ans}); it != box.end() && it->y - pnts[r].y <= ans; it++)
                // ans = min(ans, hypot(pnts[r].x - it->x, pnts[r].y - it->y));
            box.insert(pnts[r]);
        }

        if (ans == INF) cout << "INFINITY\n";
        else cout << fixed << setprecision(4) << ans << "\n";
    }
}
//-----------------------------------------------------------------------------------
//Rectangle Union
struct event {
    int id; // Index of rectangle in rects
    int type; // Type of event: 0 = Lower-left ; 1 = Upper-right
    event() {};
    event(int id, int type) : id(id), type(type) {};
};

struct point{
    int x, y;
};

int n, e = 0; // n = no. of rectangles, e = no. of events
point rects[MAX_N][2]; // Each rectangle consists of 2 points: [0] = lower-left ; [1] = upper-right
event events_v [2 * MAX_N]; // Events of horizontal sweep line
event events_h [2 * MAX_N]; // Events of vertical sweep line

bool in_set[MAX_N] = {0}; // Boolean array in place of balanced binary tree (set)
long long area = 0; // The output: Area of the union

bool compare_x(event a, event b) {
    return rects[a.id][a.type].x < rects[b.id][b.type].x;
}

bool compare_y(event a, event b) {
    return rects[a.id][a.type].y < rects[b.id][b.type].y;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> rects[i][0].x >> rects[i][0].y; // Lower-left coordinate
        cin >> rects[i][1].x >> rects[i][1].y; // Upper-right coordinate
        events_v[e] = event(i, 0);
        events_h[e++] = event(i, 0);
        events_v[e] = event(i, 1);
        events_h[e++] = event(i, 1);
    }
    sort(events_v, events_v + e, compare_x);
    sort(events_h, events_h + e, compare_y); // Pre-sort set of horizontal edges
    in_set[events_v[0].id] = 1;

    // Vertical sweep line
    for (int i = 1; i < e; i++){
        event cur = events_v[i], precur = events_v[i - 1];
        int cnt = 0; // Counter to indicate how many rectangles are currently overlapping

        // Delta_x: Distance between current sweep line and previous sweep line
        ll delta_x = rects[cur.id][cur.type].x - rects[precur.id][precur.type].x;
        if (delta_x < 0) continue;

        int begin_y;
        // Horizontal sweep line
        for (int j = 0; j < e; j++){
            if (in_set[events_h[j].id]){
                if (events_h[j].type == 0) {
                    if (cnt == 0) begin_y = rects[events_h[j].id][0].y; // Block starts
                    cnt++;
                }
                else {
                    cnt--;
                    if (cnt == 0) { // Block ends
                        ll delta_y = rects[events_h[j].id][1].y - begin_y;
                        area += delta_x * delta_y;
                    }
                }
            }
        }
        in_set[cur.id] = (cur.type == 0);
    }
    cout << area << "\n";
}
//---------------------------------------------------------------------------------------
