#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007

//---------------------------------------------------------------------------------
/*All Divisers of number in sqr(n)*/
vector<ll> Divisors(ll n){
    vector<ll> aa;
    for (ll i=1; i<=sqrt(n); i++)
    {
        if (n%i == 0)
        {
            if (n/i == i){
              aa.push_back(i);
            }else{
              aa.push_back(i);
              aa.push_back(n/i);
            }
        }
    }
    return aa;
}
//-------------------------------------------------------------------------------
/* prime factor in log(n) (greatest prime divisor gpd)*/
ll const N = 2e5 + 10;
ll spf[N];
void factor_sieve() {  
    spf[1] = 1; 
    for (ll i = 2; i < N; i++){
        spf[i] = i; 
    }
    for (ll i = 4; i < N; i += 2){
        spf[i] = 2; 
    }
    for (ll i = 3; i * i < N; i++) {
            if (spf[i] == i) {
                for (ll j = i * i; j < N; j += i){
                if (spf[j] == j){
                    spf[j] = i;
                }
            }
            }
    }
}
set<ll> getFactorization(ll x) {
     set<ll> ret;
     while (x != 1) {
        ret.insert(spf[x]);
        x = x / spf[x];
     } 
     return ret;
}


//-----------------------------------------------------------------------------------
/*[vector] of prime factor in sqrt(n) */
vector<ll> factors(ll n) {
    vector<ll> f; 
    while (n % 2 == 0) {
        f.push_back(2) ;   
         n = n / 2  ;
     } 
         for (ll x = 3; x * x <= n; x += 2) {
            while (n % x == 0) {
                f.push_back(x);
                 n /= x;
             }
         } 
         if (n > 1) 
            f.push_back(n); 
        return f;
}

//---------------------------------------------------------------
 /*[frequecy map] of prime factors in sqrt(n) one is not prime*/
map<ll, ll> primeFactorize(ll x) {
    ll num = x;
     map<ll, ll> store;
      for (ll i = 2; i <= sqrt(x); i++) {
        ll cnt = 0;
         while ((num % i) == 0) {
            num /= i; cnt++;
        }
         if (cnt)
          store[i] = cnt;
  } 
  if (num > 1)
   store[num]++; 
return store;
}


//---------------------------------------------------------------
/*
    Pre compute in O(N log N)
*/
const ll N = 1e6+10;
vector<vector<ll>> divisors(N+1);

void Divisors2(){
  for (ll i = 1; i <= N; i++) {
    for (ll j = i; j <= N; j += i) {
        divisors[j].push_back(i);
    }
    }
}