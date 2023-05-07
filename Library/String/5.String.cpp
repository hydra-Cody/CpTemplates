#include<bits/stdc++.h>
using namespace std;
#define ll long long



//---------------------------------------------------------------------------
/* check palindrome or not*/
bool palindrome(const string &s){
    ll n = s.length();
     for (ll i = 0; i < n; i++) {
        if (s[i] != s[n - i - 1]) return false;
    } 
    return true;
}

//----------------------------------------------------------------------------------
//convert string upper and lower case
string to_upper(string a){ 
    for(int i=0;i<(int)a.size();++i){ 
        if (a[i]>='a' && a[i]<='z'){ 
            a[i]-='a'-'A';
        }
    }
    return a;
 }
string to_lower(string a){ 
    for(int i=0;i<(int)a.size();++i){
        if(a[i]>='A' && a[i]<='Z'){ 
            a[i]+='a'-'A';
            }
    } 
    return a; 
}

//-------------------------------------------------------------------------------------------------
/*Rolling String Hashing*/
 
long long power(long long n, long long m, long long MOD){
    if (m == 0) return 1;
    long long x = power(n, m/2, MOD);
    if (!(m & 1)) return (x * x) % MOD;
    else return (((x * x) % MOD) * n) % MOD;
}

class StringHash {
    const static int MAX = 300005;

    ll b = 100000009;
    ll m = 1000000007;

    ll B[MAX], inverseB[MAX];
    
    void initialize() {
        B[0]=1;
        for (int i = 1; i < MAX; i++) {
            B[i]=(B[i-1]*b)%m;
        }
        inverseB[MAX-1]=power(B[MAX-1], m-2, m);
        for (int i = MAX-2; i >= 0; i--) {
            inverseB[i]=(inverseB[i+1]*b)%m;
        }
    }
 
public:
    StringHash() {
        initialize();
    }

    ll getHash(char *s) {
        long long h = 0;
        for (int i = 0; s[i]; i++) {
            h = (h + (s[i] * B[i])) % m;
        }
        return h;
    }

    int length=0;
    ll h[MAX], revh[MAX];
    ll construct(char *s) {
        length = strlen(s);
        h[0]=0, revh[length+1]=0;
        for (int i = 0, j = 1; s[i]; i++, j++) {
            h[j] = (h[j-1] + (s[i] * B[i]) % m) % m ;
        }
        for (int i = length-1, j = length, k = 0; i >= 0; i--, j--, k++) {
            revh[j] = (revh[j+1] + ((s[i] * B[k]) % m)) % m;
        }
        return h[length];
    }

    ll getSubHash(int i, int j) {
        i++, j++;
        return ((h[j] + (m-h[i-1])) * inverseB[i-1]) % m;
    }

    ll getRevHash(int i, int j) {
        i++, j++;
        return ((revh[i] + (m-revh[j+1])) * inverseB[length-j]) % m;
    }
};


/*Rolling String Hashing for Dynamic Strings*/

long long power(long long n, long long m, long long MOD)
{
    if (m == 0) return 1;
    long long x = power(n, m / 2, MOD);
    if (!(m & 1)) return (x * x) % MOD;
    else return (((x * x) % MOD) * n) % MOD;
}

const long long B = 100000007;
const long long M = 1000000009;
const long long invB = power(B-1, M-2, M); //inverse of B-1

long long pB[MAX];
void pInit() {
    pB[0] = 1;
    for (int i = 1; i < MAX; i++) {
        pB[i] = (pB[i-1] * B) % M;
    }
}

struct node {
    long long val;
    bool flag;
    long long lazy;
    node() {
        flag = false;
        val = lazy = 0;
    }
} st[4*MAX];

long long update(int n, int l, int r, int ql, int qr, int c) {
    if (st[n].flag) {
        st[n].val = (((st[n].lazy * (pB[r-l+1]+M-1) % M) % M) * invB) % M;
        if (l != r) {
            st[2*n+1].flag = true;
            st[2*n+1].lazy = st[n].lazy;
            st[2*n+2].flag = true;
            st[2*n+2].lazy = st[n].lazy;
        }
        st[n].flag = false;
        st[n].lazy = 0;
    }

    if (qr < l or ql > r) {
        return st[n].val;
    } else if (l >= ql and r <= qr) {
        st[n].val = (((c * (pB[r-l+1]+M-1) % M) % M) * invB) % M;
        if (l != r) {
            st[2*n+1].flag = true;
            st[2*n+1].lazy = c;
            st[2*n+2].flag = true;
            st[2*n+2].lazy = c;
        }
        return st[n].val;
    } else {
        int mid = (l + r)/2;
        long long leftHash = update(2*n+1, l, mid, ql, qr, c);
        long long rightHash = update(2*n+2, mid+1, r, ql, qr, c);
        st[n].val = ((leftHash * pB[r - mid]) % M + rightHash) % M;
        return st[n].val;
    }
}

long long getHash(int n, int l, int r, int ql, int qr) {
    if (st[n].flag) {
        st[n].val = (((st[n].lazy * (pB[r-l+1]+M-1) % M) % M) * invB) % M;
        if (l != r) {
            st[2*n+1].flag = true;
            st[2*n+1].lazy = st[n].lazy;
            st[2*n+2].flag = true;
            st[2*n+2].lazy = st[n].lazy;
        }
        st[n].flag = false;
        st[n].lazy = 0;
    }
    if (qr < l or ql > r) {
        return 0;
    } else if (l >= ql &&  r <= qr) {
        return (st[n].val * pB[qr - r]) % M;
    } else {
        int mid = (l + r)/2;
        long long leftHash = getHash(2*n+1, l, mid, ql, qr);
        long long rightHash = getHash(2*n+2, mid+1, r, ql, qr);
        long long h = (leftHash + rightHash) % M;
        return h;
    }
}

int main(){
    pInit();
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    char s[MAX];
    scanf("%s", s);
    for (int i = 0; i < n; i++) {
        update(0, 0, n-1, i, i, s[i] - '0');
    }
    for (int i = 0; i < m+k; i++) {
        int choice;
        scanf("%d", &choice);
        if (choice == 1){
            int l, r, c;
            scanf("%d%d%d", &l, &r, &c);
            l--, r--;
            update(0, 0, n-1, l, r, c);
        } else if (choice == 2) {
            int l, r, c;
            scanf("%d%d%d", &l, &r, &c);
            l--, r--;
            if (r-c < l) {
                printf("YES\n");
            } else {
                long long h1 = getHash(0, 0, n-1, l, r-c);
                long long h2 = getHash(0, 0, n-1, l+c, r);
                if (h1 == h2) {
                    printf("YES\n");
                } else {
                    printf("NO\n");
                }
            }
        }
    }
}



/*Suffix Array **/
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <climits>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cassert>
#include <cmath>
#include <queue>
using namespace std;

//----------------------
// inputs
string s;
int n;

const int MAX = 1000005;
const int INF = 1000000000+5;

int lgn=0;
int sa[25][MAX];
int rankSuf[MAX];
void constructSA() {
    map<int,int> rank;
    for (int i=0; i<n; i++) rank[s[i]]=0;
    int ctr=1;
    for (auto it=rank.begin(); it!=rank.end(); it++) it->second=ctr++;
    int p2=1;
    while (p2<=n) {p2<<=1; lgn++;}
    for (int i=0; i<n; i++) sa[0][i]=rank[s[i]];
    for (int i=1, l=1; i<=lgn; i++, l<<=1) {
        vector<pair<pair<int,int>,int>> rank;
        for (int j=0; j<n; j++) {
            pair<pair<int,int>, int> r = {{sa[i-1][j], ((j+l<n)?sa[i-1][j+l]:0)}, j};
            rank.push_back(r);
        }
        sort(rank.begin(), rank.end());
        for (int j=0, ctr=1; j<n; j++) {
            if (j>0 && (rank[j].first!=rank[j-1].first)) ctr++;
            sa[i][rank[j].second]=ctr;
        }
    }
    for (int i=0; i<n; i++) rankSuf[sa[lgn][i]-1]=i;
}

int getLCP(int p, int q) {
    int l=0;
    for (int i=lgn, len=(1<<lgn); i>=0; i--, len>>=1) {
        if (sa[i][p]==sa[i][q]) {
            l+=len; p+=len, q+=len;
        }
        if (p>=n || q>=n) break;
    }
    return l;
}

int lcp[25][MAX];
void processlcp() {
    int N=n-1;
    for (int i=0; i<N; i++) lcp[0][i]=getLCP(rankSuf[i], rankSuf[i+1]);
    int lgn=0, p2=1;
    while (p2<=N) {p2<<=1; lgn++;}
    for (int i=1,l=1; i<=lgn; i++,l<<=1) {
        for (int j=0; j<n; j++) {
            lcp[i][j] = min(lcp[i-1][j], (j+l<N)?lcp[i-1][j+l]:INF);
        }
    }
}

int frameSize[MAX];
int processFrameSize(){
    for(int i=0, pow2=1; pow2<MAX;  pow2*=2, i++) frameSize[pow2]=i;
    for(int i=3;i<MAX;i++) {
        if(frameSize[i]==0) {
            frameSize[i]=frameSize[i-1];
        }
    }
}

inline int query(int l, int r){
    int p = frameSize[r-l+1];
    return min(lcp[p][l], lcp[p][r-(1<<p)+1]);
}
//---------------------

int main() {
    s = "banana";
    n = s.size();

    constructSA();
    for (int i = 0; i < n; i++) cout << s.substr(rankSuf[i]) << endl;

    cout << getLCP(1, 3) << endl;

    processlcp();
    processFrameSize();

    cout << query(1, 1) << endl;
}

//----------------------------------------------------------------------------------------------------
//-trie
int x[MAX_NUMBER_OF_NODES][MAX_ASCII_CODE], next = 1; //initially all numbers in x are -1
void build(string s){
    int i = 0, v = 0;
    while(i < s.size()){
        if(x[v][s[i]] == -1)
            v = x[v][s[i++]] = next ++;
        else
            v = x[v][s[i++]];
    }
}