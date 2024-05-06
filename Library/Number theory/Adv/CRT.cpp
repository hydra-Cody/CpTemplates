#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007



//--------------------------------------------------------------------------------------
//Cht in o(n)log(l)

// ax + by = __gcd(a, b)
// returns __gcd(a, b)
ll extended_euclid(ll a, ll b, ll &x, ll &y) {
  ll xx = y = 0;
  ll yy = x = 1;
  while (b) {
    ll q = a / b;
    ll t = b; b = a % b; a = t;
    t = xx; xx = x - q * xx; x = t;
    t = yy; yy = y - q * yy; y = t;
  }
  return a;
}
// finds x such that x % m1 = a1, x % m2 = a2. m1 and m2 may not be coprime
// here, x is unique modulo m = lcm(m1, m2). returns (x, m). on failure, m = -1.
pair<ll, ll> CRT(ll a1, ll m1, ll a2, ll m2) {
  ll p, q;
  ll g = extended_euclid(m1, m2, p, q);
  if (a1 % g != a2 % g) return make_pair(0, -1);
  ll m = m1 / g * m2;
  p = (p % m + m) % m;
  q = (q % m + m) % m;
  return make_pair((p * a2 % m * (m1 / g) % m + q * a1 % m * (m2 / g) % m) %  m, m);
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout << (int)CRT(1, 31, 0, 7).first << '\n';
  return 0;
}


// pair<int, int> chinese_remainder_theorem( vector<int> A, vector<int> M ) {
//     if(A.size() != M.size()) return {-1,-1}; /** Invalid input*/
 
//     int n = A.size();
 
//     int a1 = A[0];
//     int m1 = M[0];
//     /** Initially x = a_0 (mod m_0)*/
 
//     /** Merge the solution with remaining equations */
//     for ( int i = 1; i < n; i++ ) {
//         int a2 = A[i];
//         int m2 = M[i];
 
//         int g = __gcd(m1, m2);
//         if ( a1 % g != a2 % g ) return {-1,-1}; /** No solution exists*/
 
//         /** Merge the two equations*/
//         int p, q;
//         ext_gcd(m1/g, m2/g, &p, &q);
 
//         int mod = m1 / g * m2; /** LCM of m1 and m2*/
 
//         /** We need to be careful about overflow, but I did not bother about overflow here to keep the code simple.*/
//         int x = (a1*(m2/g)*q + a2*(m1/g)*p) % mod;
 
//         /** Merged equation*/
//         a1 = x;
//         if (a1 < 0) a1 += mod; /** Result is not suppose to be negative*/
//         m1 = mod;
//     }
//     return {a1, m1};
// }