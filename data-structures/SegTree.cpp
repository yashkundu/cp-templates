/**
*   author:  lazyhash(yashkundu)
*   created: 21 Feb, 2023 | 09:14:46
*   description: range query in O(LOG(N)), point updates in O(LOG(N))
*   verification: https://codeforces.com/contest/1793/submission/194412929
**/
#include <vector>
 

template<class T>
struct SegTree{
public:
    SegTree(int n, T (*f) (T, T), T def_val) : cmb(f), dVal(def_val), n(n) {
        tree.assign(4*n, def_val);
    }
    void build(vector<T> a) {
        build(a, 0, n-1, 0);
    }
    T query(int q1, int q2) {
        return query(q1, q2, 0, n-1, 0);
    }
    void update(int ind, T val) {
        update(0, n-1, 0, ind, val);
    }
private:
    vector<T> tree;
    int n;
    T (*cmb) (T, T);
    T dVal;
    // O(N)
    void build(vector<T> a, int t1, int t2, int tnode) {
        if(t1==t2) {
            tree[tnode] = a[t1];
            return;
        }
        int mid = (t1+t2)/2;
        build(a, t1, mid, 2*tnode+1), build(a, mid+1, t2, 2*tnode+2);
        tree[tnode] = cmb(tree[2*tnode+1], tree[2*tnode+2]);
    }
    // O(LOG(N))
    T query(int q1, int q2, int t1, int t2, int tnode) {
        if(q1>t2 || q2<t1) return dVal;
        if(q1<=t1 && q2>=t2) {
            return tree[tnode];
        }
        int mid = (t1+t2)/2;
        T q = cmb(query(q1, q2, t1, mid, 2*tnode+1), query(q1, q2, mid+1, t2, 2*tnode+2));
        return q;
    }
    // O(LOG(N))
    void update(int t1, int t2, int tnode, int ind, T val) {
        if(ind<t1 || ind>t2) return;
        if(t1==t2) {
            tree[tnode] = cmb(tree[tnode], val);
            return;
        } 
        int mid = (t1+t2)/2;
        update(t1, mid, 2*tnode+1, ind, val), update(mid+1, t2, 2*tnode+2, ind, val);
        tree[tnode] = cmb(tree[2*tnode+1], tree[2*tnode+2]);
    }
};
 
