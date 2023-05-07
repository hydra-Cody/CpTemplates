#include <bits/stdc++.h>
using namespace std;
#define ll long long

//---------------------------------------------------------------------------------------
vector<ll> num;
ll a, b, d, k;
ll DP[12][12][2];
ll call(ll pos, ll cnt, ll f) {
    if (cnt > k) return 0;
    if (pos == num.size()) {
        if (cnt == k) return 1;
        return 0;
    }
    if (DP[pos][cnt][f] != -1) return DP[pos][cnt][f];
    ll res = 0;
    ll LMT=(f?9:num[pos]);
    for (ll dgt = 0; dgt <= LMT; dgt++) {
        ll nf = f;
        ll ncnt = cnt;
        if (f == 0 && dgt < LMT) nf = 1; 
        if (dgt == d) ncnt++;
        if (ncnt <= k) res += call(pos + 1, ncnt, nf);
    }
    return DP[pos][cnt][f] = res;
}

ll solve2(ll b) {
    num.clear();
    while (b > 0) {
        num.push_back(b % 10);
        b /= 10;
    }
    reverse(num.begin(), num.end());
    memset(DP, -1, sizeof(DP));
    ll res = call(0, 0, 0);
    return res;
}