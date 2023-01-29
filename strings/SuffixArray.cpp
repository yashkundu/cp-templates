/**
*    author:  lazyhash(yashkundu)
*    created: 29 Jan, 2023 | 13:35:32
*    https://judge.yosupo.jp/submission/123419
*    https://cp-algorithms.com/string/suffix-array.html#on-log-n-approach
*    sufArray - O(n*logn), lcp - O(n) (n - length of string)
**/
#include <iostream>
#include <vector>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;

vector<int> suffix_array(string s) {
    s = s + "$";
    // now sort the cylclic shifts, res will be same as suffix array
    int n = s.length();
    const int alphabet = 256;
    vector<int> cnt(max(alphabet, n), 0);

    // permutation & equivalence classes
    vector<int> p(n), c(n);
    for(int i=0;i<n;i++) {
        cnt[s[i]]++;
    }
    for(int i=1;i<alphabet;i++) cnt[i] += cnt[i-1];
    for(int i=0;i<n;i++) p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int eqClass = 1;
    for(int i=1;i<n;i++) {
        if(s[p[i]]==s[p[i-1]]) c[p[i]] = c[p[i-1]];
        else c[p[i]] = eqClass++;
    }

    // temperary permutation and equivalence classes
    vector<int> pt(n), ct(n);
    for(int k=0;(1<<k)<n;k++){
        // prearranging for stable radix sort
        for(int i=0;i<n;i++) {
            pt[i] = p[i] - (1<<k);
            if(pt[i]<0) pt[i] += n;
        }
        fill(cnt.begin(), cnt.begin()+eqClass, 0);
        for(int i=0;i<n;i++) cnt[c[pt[i]]]++;
        for(int i=1;i<eqClass;i++) cnt[i] += cnt[i-1];

        for(int i=n-1;i>=0;i--) {
            p[--cnt[c[pt[i]]]] = pt[i];
        }
        ct[p[0]] = 0;
        eqClass = 1;
        for(int i=1;i<n;i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1<<k))%n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1<<k))%n]};
            if(cur==prev) ct[p[i]] = ct[p[i-1]];
            else ct[p[i]] = eqClass++;
        }
        for(int i=0;i<n;i++) c[i] = ct[i];
    }

    vector<int> ans(n-1, 0);
    for(int i=0;i<n-1;i++) ans[i] = p[i+1];
    return ans;
}
 
vector<int> generate_lcp(string s, vector<int> &sufArray) {
    int n = s.length();
    vector<int> rank(n, -1);

    for(int i=0;i<n;i++) rank[sufArray[i]] = i;

    int k = 0;
    vector<int> lcp(n-1, 0);

    for(int i=0;i<n;i++) {
        if(rank[i]==n-1) {
            k = 0;
            continue;
        }
        int j = sufArray[rank[i]+1];
        while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
        lcp[rank[i]] = k;
        if(k) k--;
    }
    return lcp;
}

 
void solve() {
    string str;
    cin >> str;
    vector<int> sufArr = suffix_array(str);
    vector<int> lcp = generate_lcp(str, sufArr);
    for(int &x : sufArr) cout << x << " ";
    cout << "\n";
    for(int &x: lcp) cout << x << " ";
    cout << "\n";
}
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}