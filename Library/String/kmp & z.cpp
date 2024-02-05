#include<bits/stdc++.h>
using namespace std;
#define ll long long 

//----------------------------------------------------------------------------
/* Give the longest common prefix suffix "ending at i" in O(n)
*/
void kmp(string p, string s) {
  ll n = p.length();
  vector<ll> lps(n);
  lps[0] = 0;
  for (ll i = 1; i < n; i++){
    ll j = lps[i - 1];
    while (j > 0 && p[i] != p[j] ){
      j = lps[ j - 1 ];
    }
    if (p[i] == p[j]){
      j++;
    }
    lps[i] = j;
  }
  ll m = s.length();
  ll i = 0, j = 0;
  while (i < m){
    if (s[i] == p[j])
    {
      i++;
      j++;
      if (j == n){
        cout << "Pattern found at " << i - j; // 1-based index
      }
    }else if (i < m && s[i] != p[j] ) {
      if (j > 0)
        j = lps[j - 1];
      else
        i++;
    }
  }

}


//--------------------------------------------------------------------
/*
  Longest common prefix suffix "starting at i" in O(n)
*/
vector<ll> z_function(string s) {
    ll n = (ll) s.length();
    vector<ll> z(n);
    z[0]=0;  // =n as per need
    for (ll i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}