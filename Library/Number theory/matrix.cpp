#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007

//-----------------------------------
//wo matrices, how to find their product,
vector<vector<ll>> mulMat(vector<vector<ll>> mat1,vector<vector<ll>> mat2)
{
	ll R1=mat1.size(),R2=mat2.size();
	ll C1=mat1[0].size(),C2=mat2.size();
    vector<vector<ll>> rslt(R1,vector<ll>(C2)); 
    for (ll i = 0; i < R1; i++) {
        for (ll j = 0; j < C2; j++) {
            rslt[i][j] = 0;
            for (ll k = 0; k < R2; k++) {
                rslt[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
  
    }
    return rslt;
}



//------------------------------------------------------------------------------------
// given the product matrix of two matrices, and one of them, how to find the other O(n3) 
void getCofactor(vector<vector<ll>> A,vector<vector<ll>>& temp, ll p, ll q,ll n){
    ll i = 0, j = 0,N=A.size(); 
    for (ll row = 0; row < n; row++) {
        for (ll col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = A[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
//In O(n3) 
ll determinant(vector<vector<ll>> A, ll n)
{
    ll D = 0,N=A.size();
    if (n == 1)
        return A[0][0];
    vector<vector<ll>> temp(N,vector<ll>(N));
    ll sign = 1; 
    for (ll f = 0; f < n; f++) {
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);
         sign = -sign;
    } 
    return D;
}
 
void adjoint(vector<vector<ll>> A,vector<vector<ll>> adj)
{
	ll N=A.size();
    if (N == 1) {
        adj[0][0] = 1;
        return;
    }
    ll sign = 1;
    vector<vector<ll>>  temp(N,vector<ll>(N)); 
    for (ll i = 0; i < N; i++) {
        for (ll j = 0; j < N; j++) {
            getCofactor(A, temp, i, j, N);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = (sign) * (determinant(temp, N - 1));
        }
    }
}
bool inverse(vector<vector<ll>> A, vector<vector<float>> inverse)
{
	ll N=A.size();
    ll det = determinant(A, N);
    if (det == 0) {
        cout << "Singular matrix, can't find its inverse";
        return false;
    }
    vector<vector<ll>> adj(N,vector<ll>(N));
    adjoint(A, adj);
    for (ll i = 0; i < N; i++)
        for (ll j = 0; j < N; j++)	
            inverse[i][j] = adj[i][j] / float(det);
 
    return true;
}

//-----------------------------------------------------------------------
//matrix of size d x d, how to find its n'th power in O( d3log(n) )



