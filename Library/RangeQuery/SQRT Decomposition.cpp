#include <bits/stdc++.h>
#define int long long
using namespace std;
#define ll long long

ll n,len;
vector<ll> b,a;
const ll inf=1e18;
void pre(){
	len = (ll) sqrt (n + .0) + 1; // size of the block and the number of blocks	
	b.assign(len,inf);
	for (ll i=0; i<n; ++i)
		b[i / len] = min(b[i/len],a[i]);	
}

ll query(ll l, ll r)
{
    ll ans = inf;
    ll i=l;
    while(i<=r)
    {
        if (i % len == 0 && i + len - 1 <= r) {
            // if the whole block starting at i belongs to [l, r]
            ans = min(ans, b[i / len]);
            i += len;
        }
        else {
            ans = min(ans,a[i]);
            ++i;
        }	
	}
	return ans;
}

void chal(){
	cin>>n;
	a.resize(n);
	for(ll i=0; i<n; i++){
		cin>>a[i];
	}
	pre(); // pre-processing
	ll q;
	cin>>q;
	while(q--){
    ll l, r;
	cin>>l>>r;
	// print the minimum for each query
	cout<<query(l,r)<<'\n';
	// For updating an element, 
     // just recalculate b[i] value for its block
     // and also update that element in the array a 
}
}