#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007


//------------------------------------------------------------------------
/*
  BST using STL
*/

const ll N = 3e5 + 9;
set<ll>se;
map<ll, ll>l, r; //l contains the left child of the node, r contains right child of the node
void bst() {
  ll n;
  cin >> n;
  ll k;
  cin >> k; //root of the tree
  se.insert(k);
  for(ll i = 1; i < n; i++) {
    ll k;
    cin >> k;
    auto it = se.upper_bound(k);
    if(it != se.end() && l.find(*it) == l.end()) l[*it] = k;
    else --it, r[*it] = k;
    se.insert(k);
  }
  for(ll i = 1; i <= n; i++) cout << l[i] << ' ' << r[i] << '\n';

}