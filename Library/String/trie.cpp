#include<bits/stdc++.h>
using namespace std;
#define ll long long 


//----------------------------------------------------------------------
struct node{
    int val,cnt;
    node* child[2];
    node(){
        cnt=0;
        child[0] = child[1] = NULL;
    }
};
 
struct tries{
    ll len = 31;
    node *root;
    tries(){
        root = new node;
    }
 
    void insert(ll x){
        node *cur = root;
 
        for(ll i=len-1;i>=0;i--){
            ll bit = (x>>i)&1;
            cur->cnt++;
 
            if(cur->child[bit]==NULL){
                cur->child[bit] = new node;
            }
 
            cur = cur->child[bit];
        }
        cur->cnt++;
    }
    void remove(ll x){
        node *cur = root;
 
        for(ll i=len-1;i>=0;i--){
            ll bit = (x>>i)&1;
            cur->cnt--;
 
            cur = cur->child[bit];
        }
        cur->cnt--;
    }
 
    ll query(ll x){
        ll ans = 0;
        node *cur = root;
 
        for(ll i=len-1;i>=0;i--){
            ll bit = (x>>i)&1;
 
            if(cur->child[1-bit]!=NULL and cur->child[1-bit]->cnt>0){
                cur = cur->child[1-bit];
                ans |= (1<<i);
            }
            else{
                cur = cur->child[bit];                
            }
        }
 
        return ans;
    }
};
