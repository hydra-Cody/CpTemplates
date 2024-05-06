#include<bits/stdc++.h>
using namespace std;
#define ll long long
//---------------------------------------------------------------
/*Find first possition where bi differ*/
ll find(ll x){
  ll t=0;
  while(x){
    x=x>>1;
    t++;
  }
  return t;
}
//------------------------------------------------------------------
/*
    iterate through all bitmasks and 
    for each mask,iterate through all of its submasks in 3^n
*/
void allsubmask(ll n){
    for (ll m=0; m<(1<<n); ++m){
        for (ll s=m; s; s=(s-1)&m){

        }
    }
}

/* iterate through all the submasks of a mask(m=(1ll<<n)) in 3^n*/
void submask(ll m){
    for( ll x=m; x>0; x = (x-1) & m){
        cout<<x<<endl;
    }
    cout<<0<<endl; 
}
//--------------------------------------------------------------------
/*Check whether y is submask of x*/
bool submask(ll x,ll y){return (x & y == x); }
//-------------------------------------------------------------------------
/* Return the lsb bit */
ll lsb(ll n){ return  n & (-n); }
ll unsetlsb(ll n){return n = n - ( n &(-n)  );
    // return n = n ^ ( n &(-n)  );
}
//-----------------------------------------------------------------------------------
#define zerobits(x) __builtin_ctzll(x)
#define set_bits __builtin_popcountll
/*Basic Build in fuctions  in cpp*/
// __builtin_ffsll(x); //return postion first set bit 1 + index
// __builtin_clz(x); // number of leading 0-bits of x which starts from most significant bit position.
// __builtin_ctz(x); //number of trailing 0-bits of x which starts from least significant bit position.
// __builtin_popcount(x); //number of 1-bits of x


//---------------------------------------------------------------------------
/* Retuen the ith bit of number*/
bool get_bit(ll &x, ll &bt) { return (x >> bt) & 1; }

//----------------------------------------------------------------------------------
/* Set the ith bit of number */
void make_one(ll &x, ll &bt) { x |= (1 << bt); }

//------------------------------------------------------------------------------------
void make_null(ll &x, ll &bt) { x &= (~(1 << bt)); }

//----------------------------------------------------------------------------------
/* Number of set bit in a number*/
ll countSetBits(ll n){
  ll ans=0;
  while(n>0){ans+=(n&1);n=n>>1;}
  return ans;
}

//--------------------------------------------------------------------------------
/* Change the ith bit  0->1 or 1->0*/
ll toggle(ll n,ll x){ return n = n ^ (1<<x); }

//---------------------------------------------------------------------------------
/* Check Whether a number is pow of 2*/
bool isPowerOfTwo(ll x){ return x && (!(x & (x - 1))); }

//--------------------------------------------------------------------------------
/* Make 0 all bi in range i to j*/
void clearRangeItoJBits(ll &n, ll i, ll j) {
    ll ma=(~0)<<(j+1);
    ll mb=~((~0)<<i);
    ll mask=ma|mb;
    n=n&mask;
}

//---------------------------------------------------------------------------------
ll computeXOR1ton(ll n){
    if (n % 4 == 0)
        return n;
    if (n % 4 == 1)
        return 1;
    if (n % 4 == 2)
        return n + 1;
    return 0;
}


