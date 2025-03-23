#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007

/*
    Disclaimer: Can use Sparsh Table for - gcd,....  for O(1) query
*/
//---------------------------------------------------------------
/*  Generic all purpose segtree 
     T -> node, U->update.
*/



// struct update
// {
//   ll a,d;
//   update(){
//     a=0;
//     d=0;
//   }
//   update(ll a,ll d){
//     this->a=a;
//     this->d=d;
//   }
//   bool operator==(const update& other) const{
//     return ;
//   }

// };



template<class T, class U>
struct Lsegtree{
    vector<T>st;
    vector<U>lazy;
    ll n;
    T identity_element;          // apply (x,id_el)=x
    U identity_update;           // combine (x,id_upd)=x
    Lsegtree(ll n, T identity_element, U identity_update){
        this->n = n;
        this->identity_element = identity_element;
        this->identity_update = identity_update;
        st.assign(4*n,identity_element);
        lazy.assign(4*n, identity_update);
    }
    //------------------------------------------------ --------------------
    T combine(T l, T r){
        T ans = (l + r);
        return ans;
    }
    T apply(T curr, U upd, ll tl, ll tr){
        T ans = (tr-tl+1)*upd;
        return ans;
    }
    
    U combineUpdate(U old_upd, U new_upd, ll tl, ll tr){
        U ans = old_upd;
        ans=new_upd;
        return ans;
    }  

    //---------------------------------------------------------------------------
    void buildUtil(ll v, ll tl, ll tr, vector<T>&a){
        if(tl == tr){
            st[v] = a[tl];
            return;
        }
        ll tm = (tl + tr)>>1;
        buildUtil(2*v + 1, tl, tm,a);
        buildUtil(2*v + 2,tm+1,tr,a);
        st[v] = combine(st[2*v + 1], st[2*v + 2]);
    }
    void push_down(ll v, ll tl, ll tr){
        if(lazy[v] == identity_update)return;  // check "=="" define or not for update
        st[v] = apply(st[v], lazy[v], tl, tr);
        if(2*v + 2 < 4*n){
            ll tm = (tl + tr)>>1;
            lazy[2*v + 1] = combineUpdate(lazy[2*v+1], lazy[v], tl, tm);
            lazy[2*v + 2] = combineUpdate(lazy[2*v+2], lazy[v], tm+1,tr);            
        }
        lazy[v] = identity_update;
    }
    T queryUtil(ll v, ll tl, ll tr, ll l, ll r){
        push_down(v,tl,tr);
        if(l > r)return identity_element;
        if(tr < l or tl > r){
            return identity_element;
        }
        if(l <= tl and r >= tr){
            return st[v];
        }
        ll tm = (tl + tr)>>1;
        return combine(queryUtil(2*v+1,tl,tm,l,r), queryUtil(2*v+2,tm+1,tr,l,r));
    }
 
    void updateUtil(ll v, ll tl, ll tr, ll l, ll r, U upd){
        push_down(v,tl,tr); 
        if(tr < l or tl > r)return;
        if(tl >=l and tr <=r){
            lazy[v] = combineUpdate(lazy[v],upd,tl,tr);
            push_down(v,tl,tr);
        }else{
            ll tm = (tl + tr)>>1;
            updateUtil(2*v+1,tl,tm,l,r,upd);
            updateUtil(2*v+2,tm+1,tr,l,r,upd);
            st[v] = combine(st[2*v + 1], st[2*v+2]);
        }
    }



    void build(vector<T>a){
        assert(Sz(a) == n);
        buildUtil(0,0,n-1,a);
    }
    T query(ll l, ll r){
        return queryUtil(0,0,n-1,l,r);
    }
    void update(ll l,ll r, U upd){
        updateUtil(0,0,n-1,l,r,upd);
    }
};

/*
  Lsegtree<segtree,update> seg(n,identity_element,identity_update);
  seg.build(aa);
  seg.update(l,r,upd);
  seg.query(l,r);
*/




//-------------------------------------
/*  Segment Tree    ~ work for every associative operation.(a @ b) @ c = a @ (b @ c) 
*/
/*  
    [i,j]
    Segtree1 seg(n);
    seg.build(1,0,n-1);
    seg.update(1,0,n-1,l,val);
    seg.query(1,0,n-1,l,r);
*/
struct Segtree1 {
  vector<ll> t;
  Segtree1(ll n) {
      t.assign(4*n, 0);
  }
  void build(vector<ll>& a,ll n, ll b, ll e) {
    if (b == e) {
      t[n] = a[b];  
      return;
    }
    ll mid = (b + e) >> 1, l = n << 1, r = l | 1;
    build(a,l, b, mid);
    build(a,r, mid + 1, e);
    t[n] = t[l]+ t[r];
  }
  void update(ll n, ll b, ll e, ll i, ll x) {
    if (b > i || e < i) return;
    if (b == e && b == i) {
      t[n] = x;
      return;
    }
    ll mid = (b + e) >> 1, l = n << 1, r = l | 1;
    update(l, b, mid, i, x);
    update(r, mid + 1, e, i, x);
    t[n] = t[l]+ t[r];
  }
  ll query(ll n, ll b, ll e, ll i, ll j) {
    if (b > j || e < i) return 0;
    if (b >= i && e <= j) return t[n];
    ll mid = (b + e) >> 1, l = n << 1, r = l | 1;
    ll L = query(l, b, mid, i, j);
    ll R = query(r, mid + 1, e, i, j);
    return L+ R;
  }
};

//---------------------------------------------------------------------
/*  segment tree+Lazy propagation->Range update
*/
/*
    Segtree2 seg(n);
    seg.build(a,1,0,n-1);
    seg.query(1,0,n-1,l,r);
    seg.update(1,0,n-1,l,r,val);  [l,r]
*/
struct Segtree2{
    vector<ll> t, lazy, sz;
    Segtree2(ll n) {
        t.assign(4*n, 0);
        lazy.assign(4*n, 0);
        for(ll i=0;i<4*n;i++){
          lazy[i] = -1;
        }
        sz.assign(4*n, 0);
    }
    void build(vector<ll>& a, ll v, ll tl, ll tr){
        if(tl == tr){
            t[v] = a[tl];
            sz[v] = 1;
        }
        else{
            ll tm = (tl + tr)/2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = t[v*2] + t[v*2+1];
            sz[v] = sz[v*2] + sz[v*2+1];
        }
    }
    void push(ll v){
      if(lazy[v]==-1) return;
        t[v*2] = sz[v*2] * lazy[v];
        lazy[v*2] = lazy[v];
        t[v*2+1] = sz[v*2+1] * lazy[v];
        lazy[v*2+1] = lazy[v];
        lazy[v] = -1;
    }
    void update(ll v, ll tl, ll tr, ll l, ll r, ll chg){
        if(l > r){
            return;
        }
        if(l <= tl && tr <= r){
            t[v] = sz[v] * chg;
            lazy[v] = chg;
        } else {
            push(v);
            ll tm = (tl + tr)/2;
            update(v*2, tl, tm, l, min(r, tm), chg);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, chg);
            t[v] = t[v*2]+t[v*2+1];
        }
    }
    ll query(ll v, ll tl, ll tr, ll l, ll r) {
        if(l>r) return 0;
        if(l <= tl && tr <= r){
            return t[v];
        }
        push(v);
        ll tm = (tl + tr)/2;
        return query(v*2, tl, tm, l, min(r, tm)) + query(v*2+1, tm+1, tr, max(l, tm+1), r);
    }
};



