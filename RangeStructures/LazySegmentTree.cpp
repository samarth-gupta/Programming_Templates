// sample -> get range sum, add on range, set on range
struct Vertex
{
    #warning set data for tree node
    ll val;
    int l, r;
    Vertex(): val(0), l(-1), r(-1){}
    Vertex(ll x, int a, int b): val(x), l(a), r(b){}
    static void merge( Vertex &parent, Vertex lch, Vertex rch )
    {
        parent.val = lch.val + rch.val;
    }
};

struct Update
{
    #warning set data for lazy node, and clear / apply / accumulate functions
    ll last_set, total_add;
    Update(): last_set(0), total_add(0){}
    Update(ll A, ll B): last_set(A), total_add(B){}
    // clear the lazy from this node
    void clear()
    {
        last_set = total_add = 0;
    }
    // apply lazy from this to tree node
    void apply(Vertex &t)
    {
        int len = t.r - t.l + 1;
        if( last_set != 0 )
        {
            t.val = len * last_set;
        }
        t.val += len * total_add;
    }
    // add lazy from this to other lazy node
    void accumulate(Update &other)
    {
        if( last_set != 0 )
        {
            other.last_set = last_set;
            other.total_add = total_add;
        }
        else
        {
            other.total_add += total_add;
        }
    }
};

template<class V, class U>
class LazySegmentTree
{
public:
    int N, sz;
    vector<V> data;
    vector<U> updates;
    LazySegmentTree( int n )
    {
        N = n;
        sz = 4*N;
        data.resize(sz,V());
        updates.resize(sz,U());
    }
    template <class X>
    LazySegmentTree( vector<X>&a )
    {
        N = a.size();
        sz = 4*N;
        data.resize(sz,V(X()));
        updates.resize(sz,U(X()));
        build(0,0,N-1,a);
    }
    template<class X>
    void build( int v, int l, int r, vector<X>&a )
    {
        data[v].l = l;
        data[v].r = r;
        if( l == r )
        {
            data[v].val = a[l];
            return;
        }
        int m = l + (r-l)/2;
        build( 2*v+1, l, m, a );
        build( 2*v+2, m+1, r, a );
        V::merge( data[v], data[2*v+1], data[2*v+2] );
    }
    void push( int v )
    {
        // cout<<"PUSH vertex:"<<v,nl;
        updates[v].apply(data[2*v+1]);
        updates[v].accumulate(updates[2*v+1]);

        updates[v].apply(data[2*v+2]);
        updates[v].accumulate(updates[2*v+2]);

        updates[v].clear();
    }
    void range( int v, int l, int r, int ql, int qr, U upd )
    {
        if( qr < l || ql > r )
            return;
        if( ql <= l && r <= qr )
        {
            upd.accumulate(updates[v]);
            upd.apply(data[v]);
            return;
        }
        int m = l + (r-l)/2;
        push(v);
        range(2*v+1, l, m, ql, qr, upd);
        range(2*v+2, m+1, r, ql, qr, upd);
        V::merge( data[v], data[2*v+1], data[2*v+2] );
    }
    V query( int v, int l, int r, int ql, int qr )
    {
        // #warning
        if( qr < l || ql > r )
            return V();
        if( ql <= l && r <= qr )
            return data[v];
        int m = l + (r-l)/2;
        push(v);
        V current;
        V::merge( current, query(2*v+1,l,m,ql,qr), query(2*v+2,m+1,r,ql,qr) );
        return current;
    }
    V get( int l, int r )
    {
        return query(0,0,N-1,l,r);
    }
    void range_modify( int l, int r, U val )
    {
        range(0,0,N-1,l,r,val);
    }
    void modify( int pos, U val )
    {
        range_modify(pos,pos,val);
    }
};
