#include<bits/stdc++.h>
using namespace std;
#define ll long long 


//-----------------------------------------------------------------------------------
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

//-------------------------------------------------------------------------
/* Return the lsb bit */
ll lsb(ll n){ return  n & (-n); }
ll unsetlsb(ll n){return n = n - ( n &(-n)  );
    // return n = n ^ ( n &(-n)  );
}
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
//------------------------------------------------------------------
/*number n, iterate through all the submasks of n */
void submask(ll n){
    for( ll x=n; x>0; x = (x-1) & n){
        cout<<x<<endl;
    }
    cout<<0<<endl; 
}
//-------------------------------------------------------
/*set of n elements, iterate through all the subsets (submasks) of all the subsets (submasks) of size n*/
void subsubmask(ll n){
    for( int i=0; i< (1<<n) ; i++){
        for( int x=i; x>0; x = (x-1) & i){
            cout<<x<<endl;
        }
        cout<<0<<'\n'; // treat 0 separately
    }
}

//--------------------------------------------------------------------
/*Check whether y is submask of x*/
bool submask(ll x,ll y){return (x & y == x); }
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


