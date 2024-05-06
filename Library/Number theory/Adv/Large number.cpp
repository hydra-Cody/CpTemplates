#include<bits/stdc++.h>
using namespace std;
#define ll long long int

//----------------------------------------------------------------------------------------

/*Sum of two number */
string findSum(string str1, string str2)
{
    if (str1.length() > str2.length())
        swap(str1, str2); 
    string str = ""; 
    ll n1 = str1.length(), n2 = str2.length();
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end()); 
    int carry = 0;
    for (ll i=0; i<n1; i++){
        ll sum = ((str1[i]-'0')+(str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    } 
    for (ll i=n1; i<n2; i++){
        ll sum = ((str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }
     if (carry)
        str.push_back(carry+'0'); 
    reverse(str.begin(), str.end());
    return str;
}

/*Differnce of two number*/

bool isSmaller(string str1, string str2){
    ll n1 = str1.length(), n2 = str2.length();
    if (n1 < n2)
        return true;
    if (n2 < n1)
        return false;
 
    for (ll i = 0; i < n1; i++)
        if (str1[i] < str2[i])
            return true;
        else if (str1[i] > str2[i])
            return false; 
    return false;
}
 
string findDiff(string str1, string str2){
    if (isSmaller(str1, str2))
        swap(str1, str2);
    string str = "";
    ll n1 = str1.length(), n2 = str2.length();
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end()); 
    int carry = 0;
    for (ll i = 0; i < n2; i++) {
        ll sub
            = ((str1[i] - '0') - (str2[i] - '0') - carry);
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0; 
        str.push_back(sub + '0');
    }
    for (ll i = n2; i < n1; i++) {
        ll sub = ((str1[i] - '0') - carry);
         if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
        str.push_back(sub + '0');
    } 
    reverse(str.begin(), str.end());
    return str;
}

/*Multiplication of two number*/
string multiply(string num1, string num2)
{
    ll len1 = num1.size();
    ll len2 = num2.size();
    if (len1 == 0 || len2 == 0)
    return "0";
    vector<ll> result(len1 + len2, 0);
    ll i_n1 = 0;
    ll i_n2 = 0;     
    for (ll i=len1-1; i>=0; i--){
        ll carry = 0;
        ll n1 = num1[i] - '0'; 
        i_n2 = 0;         
        for (ll j=len2-1; j>=0; j--)
        {
           ll n2 = num2[j] - '0';
           ll sum = n1*n2 + result[i_n1 + i_n2] + carry;
             carry = sum/10; 
            result[i_n1 + i_n2] = sum % 10;
 
            i_n2++;
        } 
        if (carry > 0)
            result[i_n1 + i_n2] += carry;
        i_n1++;
    }
    ll i = result.size() - 1;
    while (i>=0 && result[i] == 0)
    i--;
    if (i == -1)
    return "0"; 
    string s = "";
    while (i >= 0)
        s += std::to_string(result[i--]);
    return s;
}

/* Divistion of two number*/
string longDivision(string number, ll divisor){
    string ans;
    ll idx = 0;
    ll temp = number[idx] - '0';
    while (temp < divisor)
        temp = temp * 10 + (number[++idx] - '0');
    while (number.size() > idx) {
        ans += (temp / divisor) + '0'; 
        temp = (temp % divisor) * 10 + number[++idx] - '0';
    } 
    if (ans.length() == 0)
        return "0";
     return ans;
}