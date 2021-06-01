class Node
{
public:
	ll val;

	Node()
	{
		val = 0;
	}

	Node(ll x)
	{
		val = x;
	}

	static Node merge(Node left, Node right)
	{
		Node result;

		result.val = left.val + right.val;

		return result;
	}

};

template<class T>
class SegmentTree
{
public:
	int N, sz;
	vector<T>tree, actual_value;

	SegmentTree( int n )
	{
		N = n+5;
		sz = 2*N;
		tree.resize(sz);
		actual_value.resize(N);
	}

	template<class U>
	SegmentTree( vector<U> &a )
	{
		actual_value.assign(a.begin(), a.end());

		N = (int)actual_value.size()+5;
		sz = 2*N;

		tree.resize(sz);
		actual_value.resize(N);

		build(0,0,N-1);
	}

	void build( int v, int l, int r )
	{
		// if( l > r ) return;
		if( l == r )
		{
			tree[v] = actual_value[l];
			return;
		}
		int m = l + (r-l)/2;
		build( v+1, l, m );
		build( v+2*(m-l+1), m+1, r );
		tree[v] = T::merge( tree[v+1], tree[v+2*(m-l+1)] );
	}

	void set( int v, int l, int r, int p, T val )
	{
		if( p < l || p > r ) return;
		if( l == r )
		{
			tree[v] = val;
			actual_value[l] = val;
			return;
		}
		int m = l + (r-l)/2;
		set( v+1, l, m, p, val );
		set( v+2*(m-l+1), m+1, r, p, val );
		tree[v] = T::merge( tree[v+1], tree[v+2*(m-l+1)] );
	}

	void add( int v, int l, int r, int p, T addend )
	{
		if( p < l || p > r ) return;
		if( l == r )
		{
			tree[v] = T::merge( tree[v], addend );
			actual_value[l] = T::merge( actual_value[l], addend );
			return;
		}
		int m = l + (r-l)/2;
		add( v+1, l, m, p, addend );
		add( v+2*(m-l+1), m+1, r, p, addend );
		tree[v] = T::merge( tree[v+1], tree[v+2*(m-l+1)] );
	}

	T query( int v, int l, int r, int ql, int qr )
	{
		if( qr < l || ql > r )
			return T();
		if( ql <= l && r <= qr )
			return tree[v];
		int m = l + (r-l)/2;
		return T::merge( query(v+1,l,m,ql,qr), query(v+2*(m-l+1),m+1,r,ql,qr) );
	}

	T operator[]( int pos )
	{
		return actual_value[pos];
	}

	T get( int pos )
	{
		return actual_value[pos];
	}

	T cumulative( int l, int r )
	{
		return query(0,0,N-1,l,r);
	}

	void set( int pos, T val )
	{
		set(0,0,N-1,pos,val);
	}

	void add( int pos, T addend )
	{
		add(0,0,N-1,pos,addend);
	}

};