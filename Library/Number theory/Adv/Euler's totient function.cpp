#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007


//---------------------------------------------------------------------------
//In sqrt(n)
ll phii(ll n) {
    ll result = n;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

//-----------------------------------------------------------------------
// 1 to n phin in nloglogn
const ll N = 1e5 + 9;
ll phi[N];
void totient() {
  for (ll i = 1; i < N; i++) phi[i] = i;
  for (ll i = 2; i < N; i++) {
    if (phi[i] == i) {
      for (ll j = i; j < N; j += i) phi[j] -= phi[j] / i;
    }
  }
}
//------------------------------------------------------------------------
// 1 to n phin in using the divisor sum property
void phi_1_to_n2(ll n) {
    vector<ll> phi(n + 1);
    phi[0] = 0;
    phi[1] = 1;
    for (ll i = 2; i <= n; i++)
        phi[i] = i - 1;

    for (ll i = 2; i <= n; i++)
        for (ll j = 2 * i; j <= n; j += i)
              phi[j] -= phi[i];
}

//---------------------------------------------------------------------
