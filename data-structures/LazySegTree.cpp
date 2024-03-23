// min segtree with lazy updation
struct SegTree{
    vector<int> tree;
    vector<int> lazy;
    int n;
    int inf = 1e9;

    SegTree(int n) {
        this->n = n;
        tree.assign(4*n, 0);
        lazy.assign(4*n, 0);
    }


    void build(int v, int tl, int tr, vector<int> a) {
        if(tl==tr) {
            tree[v] = a[tl];
            return;
        }
        int tm = (tl+tr)/2;
        build(2*v+1, tl, tm, a);
        build(2*v+2, tm+1, tr, a);
        tree[v] = min(tree[2*v+1], tree[2*v+2]);
    }


    void propagate(int v, int tl, int tr) {
        if(!lazy[v]) return;
        if(tl!=tr) {
            lazy[2*v+1] += lazy[v];
            lazy[2*v+2] += lazy[v];
        }
        tree[v] += lazy[v];
        lazy[v] = 0;
    }
    
    int query(int l, int r) {
        if(l>r) return inf;
        return query(0, 0, n-1, l, r);
    }

    int query(int v, int tl, int tr, int ql, int qr) {
        propagate(v, tl, tr);
        if(ql>tr || qr<tl) return inf;
        if(tl>=ql && tr<=qr) return tree[v];
        int tm = (tl+tr)/2;
        return min(query(2*v+1, tl, tm, ql, qr), query(2*v+2, tm+1, tr, ql, qr));
    }

    void update(int l, int r, int val) {
        if(l>r) return;
        update(0, 0, n-1, l, r, val);
    }

    // lazy propagation
    void update(int v, int tl, int tr, int ql, int qr, int val) {
        propagate(v, tl, tr);
        if(ql>tr || qr<tl) return;
        if(tl>=ql && tr<=qr) {
            lazy[v] = val;
            propagate(v, tl, tr);
            return;
        }
        int tm = (tl+tr)/2;
        update(2*v+1, tl, tm, ql, qr, val);
        update(2*v+2, tm+1, tr, ql, qr, val);
        tree[v] = min(tree[2*v+1], tree[2*v+2]);
    }
};