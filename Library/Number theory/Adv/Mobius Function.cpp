#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007

//--------------------------------------------------------------------------

const ll N = 5e5 + 9;

ll mob[N];
void mobius() {
  mob[1] = 1;
  for (ll i = 2; i < N; i++){
    mob[i]--;
    for (ll j = i + i; j < N; j += i) {
      mob[j] -= mob[i];
    }
  }
}

