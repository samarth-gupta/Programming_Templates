// sample -> get range sum, add on range, set on range
template <class V, class U> class LazySegmentTree {
  public:
    int N;
    vector<V> data;
    vector<U> updates;

    LazySegmentTree() {}
    LazySegmentTree(int n) {
        N = n;
        data.resize(4 * N, V());
        updates.resize(4 * N, U());
        vector<int> a(n);
        build(1, 1, N, a);
    }
    template <class X> LazySegmentTree(vector<X>& a) {
        N = a.size();
        data.resize(4 * N, V());
        updates.resize(4 * N, U());
        build(1, 1, N, a);
    }
    template <class X> void build(int v, int l, int r, vector<X>& a) {
        data[v].l = l;
        data[v].r = r;
        if (l == r) {
            data[v].init(a[l]);
            return;
        }
        int m = l + (r - l) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
        data[v].merge(data[2 * v], data[2 * v + 1]);
    }
    void push(int v) {
        data[2 * v].apply(updates[v]);
        updates[2 * v].accumulate(updates[v]);

        data[2 * v + 1].apply(updates[v]);
        updates[2 * v + 1].accumulate(updates[v]);

        updates[v].clear();
    }
    void _update(int v, int l, int r, int ql, int qr, U upd) {
        if (qr < l || ql > r)
            return;
        if (ql <= l && r <= qr) {
            updates[v].accumulate(upd);
            data[v].apply(upd);
            return;
        }
        push(v);
        int m = l + (r - l) / 2;
        _update(2 * v, l, m, ql, qr, upd);
        _update(2 * v + 1, m + 1, r, ql, qr, upd);
        data[v].merge(data[2 * v], data[2 * v + 1]);
    }
    V _query(int v, int l, int r, int ql, int qr) {
        if (qr < l || ql > r)
            return V();
        if (ql <= l && r <= qr)
            return data[v];
        push(v);
        int m = l + (r - l) / 2;
        V current;
        current.merge(_query(2 * v, l, m, ql, qr),
                      _query(2 * v + 1, m + 1, r, ql, qr));
        return current;
    }

    void update(int l, int r, U upd) { _update(1, 1, N, l, r, upd); }
    V query(int l, int r) { return _query(1, 1, N, l, r); }
};

class Update {
#warning set data for lazy node, how to accumulate updates
  public:
    ll last_set, add;
    Update() { clear(); }
    Update(ll a, ll b) : last_set(a), add(b) {}
    void clear() {
        last_set = 0;
        add = 0;
    }

    void accumulate(Update& other) {
        if (other.last_set != 0) {
            last_set = other.last_set;
            add = other.add;
        } else {
            add += other.add;
        }
    }
};

class Node {
#warning set data for tree node, how to merge nodes, and apply updates
  public:
    int l, r;
    ll val;
    Node() {
        val = 0;
        l = r = -1;
    }
    template <class X> void init(X x) { val = x; }

    void merge(Node left, Node right) { val = left.val + right.val; }

    void apply(Update& u) {
        int len = r - l + 1;
        if (u.last_set != 0)
            val = u.last_set * len;
        val += u.add * len;
    }
};