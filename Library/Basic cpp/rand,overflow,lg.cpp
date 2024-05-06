#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007
// ----------------------------------------------------
ll my_rand(){
  ll a=rand();
  ll b=rand();
  return a*(RAND_MAX+1)+b;
}
//---------------------------------------------------
bool isOverflow(int x, int y){
  return (x > LLONG_MAX / y or y > LLONG_MAX / x);
}
//-----------------------------------------------
/*
	Calculating log array
*/
const int MAX=1e3+5;
int lg[MAX];
void pre(){
  lg[0]=-1;
  for(int i=1;i<=1000;i++) lg[i]=lg[i>>1]+1;
}