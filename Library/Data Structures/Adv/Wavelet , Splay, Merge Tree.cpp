#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(), x.end()
//-----------------------------------------------------------------\
/* Merge sort tree  build - O(nlog(n)) query-O(log(n)) mermory-nlog(n)*/

const ll N=200005;
vector<ll> tree[5*N];
void init(ll n,ll b, ll e,vector<ll>& aa){
    if(b==e){
        tree[n].push_back(aa[b]);
        return;
    }
    ll l=n*2+1,r=l+1,mid=(b+e)/2;
    init(l,b,mid,aa);
    init(r,mid+1,e,aa);
    merge(all(tree[l]),all(tree[r]),back_inserter(tree[n]));

}
ll query(ll n, ll b, ll e, ll i, ll j, ll k){
    if( e < i || b > j ){
        return 0; 
    }
    if( i<=b && e<=j ){
    return lower_bound(tree[n].begin(),tree[n].end(),k)-tree[n].begin();
    }
    ll mid=b+(e-b)/2;
    return query(2*n+1,b,mid,i,j,k)+query(2*n+2,mid+1,e,i,j,k);
}

//-----------------------------------------------------------------------
const ll MAXN = (ll)3e5 + 9;
const ll MAXV = (ll)1e9 + 9; 
//array values can be negative too, use appropriate minimum and maximum value
struct wavelet_tree {
  ll lo, hi;
  wavelet_tree *l, *r;
  ll *b, *c, bsz, csz; // c holds the prefix sum of elements
  wavelet_tree() {
    lo = 1;
    hi = 0;
    bsz = 0;
    csz = 0, l = NULL;
    r = NULL;
  }

  void init(ll *from, ll *to, ll x, ll y) {
    lo = x, hi = y;
    if(from >= to) return;
    ll mid = (lo + hi) >> 1;
    auto f = [mid](ll x) {
      return x <= mid;
    };
    b = (ll*)malloc((to - from + 2) * sizeof(ll));
    bsz = 0;
    b[bsz++] = 0;
    c = (ll*)malloc((to - from + 2) * sizeof(ll));
    csz = 0;
    c[csz++] = 0;
    for(auto it = from; it != to; it++) {
      b[bsz] = (b[bsz - 1] + f(*it));
      c[csz] = (c[csz - 1] + (*it));
      bsz++;
      csz++;
    }
    if(hi == lo) return;
    auto pivot = stable_partition(from, to, f);
    l = new wavelet_tree();
    l->init(from, pivot, lo, mid);
    r = new wavelet_tree();
    r->init(pivot, to, mid + 1, hi);
  }
  //kth smallest element in [l, r]
  ll kth(ll l, ll r, ll k) {
    if(l > r) return 0;
    if(lo == hi) return lo;
    ll inLeft = b[r] - b[l - 1], lb = b[l - 1], rb = b[r];
    if(k <= inLeft) return this->l->kth(lb + 1, rb, k);
    return this->r->kth(l - lb, r - rb, k - inLeft);
  }
  //count of numbers in [l, r] Less than or equal to k
  ll LTE(ll l, ll r, ll k) {
    if(l > r || k < lo) return 0;
    if(hi <= k) return r - l + 1;
    ll lb = b[l - 1], rb = b[r];
    return this->l->LTE(lb + 1, rb, k) + this->r->LTE(l - lb, r - rb, k);
  }
  //count of numbers in [l, r] equal to k
  ll count(ll l, ll r, ll k) {
    if(l > r || k < lo || k > hi) return 0;
    if(lo == hi) return r - l + 1;
    ll lb = b[l - 1], rb = b[r];
    ll mid = (lo + hi) >> 1;
    if(k <= mid) return this->l->count(lb + 1, rb, k);
    return this->r->count(l - lb, r - rb, k);
  }
  //sum of numbers in [l ,r] less than or equal to k
  ll sum(ll l, ll r, ll k) {
    if(l > r or k < lo) return 0;
    if(hi <= k) return c[r] - c[l - 1];
    ll lb = b[l - 1], rb = b[r];
    return this->l->sum(lb + 1, rb, k) + this->r->sum(l - lb, r - rb, k);
  }
  ~wavelet_tree() {
    delete l;
    delete r;
  }
};
wavelet_tree t;
ll a[MAXN];
ll run() {
  ll i, j, k, n, m, q, l, r;
  cin >> n;
  for(i = 1; i <= n; i++) cin >> a[i];
  t.init(a + 1, a + n + 1, -MAXV, MAXV);
  //beware! after the init() operation array a[] will not be same
  cin >> q;
  while(q--) {
    ll x;
    cin >> x;
    cin >> l >> r >> k;
    if(x == 0) {
      //kth smallest
      cout << t.kth(l, r, k) << endl;
    } else if(x == 1) {
      //less than or equal to K
      cout << t.LTE(l, r, k) << endl;
    } else if(x == 2) {
      //count occurence of K in [l, r]
      cout << t.count(l, r, k) << endl;
    }
    if(x == 3) {
      //sum of elements less than or equal to K in [l, r]
      cout << t.sum(l, r, k) << endl;
    }
  }
  return 0;
}




//-----------------------------------------------------------------------------
const ll N=101234;
struct jilu{ll key,cnt,size,ls,rs,fa;}tree[N*20];
struct jilu2{ll tail,ls,next;}tr[N];
ll n,m,k,size[N],que[10000000],ans,e[N*2],next[N*2],lis[N],cost[N],dist[N],tot;
ll root[N],l,fa[N];
bool mark[N];
inline void Renew(ll x)
{
  tree[x].size=tree[tree[x].ls].size+tree[tree[x].rs].size+tree[x].cnt;
}
inline void Zig(ll x)
{
  ll y=tree[x].fa,z=tree[y].fa;
  tree[y].ls=tree[x].rs,tree[tree[x].rs].fa=y;
  tree[x].fa=z;
  if (tree[z].ls==y) tree[z].ls=x;
  else tree[z].rs=x;
  tree[y].fa=x,tree[x].rs=y;
  Renew(y);
}
inline void Zag(ll x)
{
  ll y=tree[x].fa,z=tree[y].fa;
  tree[y].rs=tree[x].ls,tree[tree[x].ls].fa=y;
  tree[x].fa=z;
  if (tree[z].ls==y) tree[z].ls=x;
  else tree[z].rs=x;
  tree[y].fa=x,tree[x].ls=y;
  Renew(y);
}
inline void Splay(ll x,ll &root)
{
  for (;tree[x].fa!=0;){
    ll y=tree[x].fa,z=tree[y].fa;
      if (z==0){
      if (tree[y].ls==x) Zig(x);
        else Zag(x);
        }
      else{
        if (tree[z].ls==y)
          if (tree[y].ls==x) Zig(y),Zig(x);
          else Zag(x),Zig(x);       
        else
          if (tree[y].rs==x) Zag(y),Zag(x);
          else Zig(x),Zag(x);
        }
    }
  root=x; Renew(x);
}
inline void Find(ll &root,ll x)
{
  ll p=root;
  for (;;){
    if (x==tree[p].key) break;
    if (x>tree[p].key)
      if (tree[p].rs!=0) p=tree[p].rs;
      else break;
      else
        if (tree[p].ls!=0) p=tree[p].ls;
        else break;
    }
  Splay(p,root);
  if (tree[p].key==x) ans+=tree[p].cnt;
}
inline void Insert(ll x,ll &root)
{
  ll p=root;
  for (;;){
    if (x==tree[p].key) break;
    if (x>tree[p].key)
      if (tree[p].rs!=0) p=tree[p].rs;
        else {tree[p].rs=tot+1;break;}
      else
        if (tree[p].ls!=0) p=tree[p].ls;
        else {tree[p].ls=tot+1;break;}
      }
  if (tree[p].key==x) tree[p].cnt++,Splay(p,root);
    else{
      tot++;
      tree[tot].cnt=1;
      tree[tot].key=x;
      tree[tot].fa=p;
      Splay(tot,root);
      }
}
void Dfs(ll u)
{
  mark[u]=true;
    for (ll v=tr[u].ls;v!=0;v=tr[v].next) Dfs(v);
  ll max=0,maxv=-1;
  for (ll v=tr[u].ls;v!=0;v=tr[v].next)
  if (size[v]>max) max=size[v],maxv=v;
  if (maxv!=-1){
    for (ll v=tr[u].ls;v!=0;v=tr[v].next)
    if (v!=maxv){
      ll head=0,tail=1;que[1]=v;
      while (head<tail){
          head++;
          for (ll i=tr[que[head]].ls;i!=0;i=tr[i].next)
            que[++tail]=i;
          }
        for (ll i=1;i<=tail;i++)
          Find(root[maxv],k+2*dist[u]-dist[que[i]]);
        for (ll i=1;i<=tail;i++)
          Insert(dist[que[i]],root[maxv]);
        }
      Find(root[maxv],k+2*dist[u]-dist[u]);
      Insert(dist[u],root[maxv]);
      root[u]=root[maxv];
      }
    else{
      root[u]=++tot;
      tree[tot].key=dist[u];
      tree[tot].cnt=1;
      tree[tot].size=1;
      } 
}

ll chal()
{
    scanf("%d%d",&n,&k);
    ll x,y,z;char c;
    for (ll i=1;i<n;i++){
      scanf("%d%d",&x,&y);
      e[++l]=y,next[l]=lis[x],lis[x]=l;cost[l]=1;
      e[++l]=x;next[l]=lis[y],lis[y]=l;cost[l]=1;
      }
    ll u,v,head=0,tail=1;que[1]=1;mark[1]=true;dist[1]=0;
    while (head<tail){
      u=que[++head];
      for (ll i=lis[u];i!=0;i=next[i]){
        v=e[i];
        if (!mark[v]){
          if (!tr[u].ls) tr[u].ls=v;
          else tr[tr[u].tail].next=v;
          dist[v]=dist[u]+cost[i];
          tr[u].tail=v; que[++tail]=v; fa[v]=u;
          mark[v]=true;
        }
      }
      }
    for (ll i=tail;i>0;i--)
    size[que[i]]++,size[fa[que[i]]]+=size[que[i]];
  ans=0; tot=0; Dfs(1);
  prllf("%d\n",ans); return 0;
}


