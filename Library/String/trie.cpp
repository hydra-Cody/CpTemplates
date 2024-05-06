#include<bits/stdc++.h>
using namespace std;
#define ll long long 


//----------------------------------------------------------------------
/*
    "Disclaimer"-> Always use pointer trie as there can be memory tight in questions
*/
/* Binary trie -> Tree + bitmask */
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


//-----------------------------------------------------------------
/*
    String Trie
*/
struct Trie {
  Trie* children[26];
  ll cnt = 0;
  Trie() {
      for(ll i=0;i<26;i++)children[i]=NULL;
  }
  
  void insert(string word) {
      Trie* cur = this;
      cur->cnt++;
      for(auto i:word){
          if(!cur->children[i-'a']) cur->children[i-'a'] = new Trie();
          cur = cur->children[i-'a'];
          cur->cnt++;
      }
  }
  
  ll search(string word) {
      ll len = word.size();
      Trie* cur = this;
      ll res = 0;
      for(ll i=0;i<len;i++){
          char c = word[i];
          if(!cur->children[c-'a'])break;
          cur = cur->children[c-'a'];
          res += cur->cnt;
      }
      return res;
  }
};
