#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007

//------------------------------------------------------------------------------------
/*Length of longest palidrome centred at a point. there are N odd postions and
N-1 even postions centres in O(n)
*/

vector<ll> odd_palindrome(string& s){
  ll n = s.size();
  vector<ll> d1(n);
  for (ll i = 0, l = 0, r = -1; i < n; i++) {
    ll k = (i > r) ? 1 : min(d1[l + r - i], r - i);
    while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
      k++;
    }
    d1[i] = k--;
    if (i + k > r) {
      l = i - k;
      r = i + k;
    }
  }

  return d1;
}

vector<ll> even_palindrome(string& s){
  ll n = s.size();
  vector<ll> d2(n);
  for (ll i = 0, l = 0, r = -1; i < n; i++) {
    ll k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
    while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
      k++;
    }
    d2[i] = k--;
    if (i + k > r) {
      l = i - k - 1;
      r = i + k ;
    }
  }
  return d2;
}

/*
d1[i] = number of odd-length palindromes centered at i
d2[i] = number of even-length palindromes centered at (i-1,i)

Example
s = a {b a _b_ a b} c

d1[2] = 3

s = c {b a _a_ b} d

d2[2] = 2
*/