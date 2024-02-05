#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007

//---------------------------------------------------------
/*Priority queue #defines */
#define pqh priority_queue
template <typename Y> using pql = priority_queue<Y, vector<Y>, greater<Y>>;

//--------------------------------------------------------------
/* string tolower and toupper  */
#define tol(s) transform(s.begin(),s.end(),s.begin(),::tolower);
#define tou(s) transform(s.begin(),s.end(),s.begin(),::toupper);

//----------------------------------------------------
template <typename Y>
void make_unique(Y &vec) {
    vec.erase(unique(vec.begin(),vec.end()), vec.end());
}