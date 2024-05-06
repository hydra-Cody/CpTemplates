#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007
//---------------------------------------------------------------------------------
/*
  max, stores strictly decreasing sequence of the current queue
*/
const ll N = 3e5 + 9;
struct monotonous_queue { 
  ll a[N + 10], b[N + 10], l = 0, r = -1;
  void push(ll val) {
    ll cnt = 0;
    while(l <= r && a[r] <= val) {
      cnt += b[r] + 1;
      r--;
    }
    a[++r] = val, b[r] = cnt;
  };
  ll top() {
    return a[l];
  }
  void pop() {
    if(l > r) return;
    if (b[l] > 0) {
      b[l] --;
      return;
    }
    l++;
  }
};
