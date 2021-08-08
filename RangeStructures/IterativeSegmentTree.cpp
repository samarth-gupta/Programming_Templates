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
	vector<T>tree;

	SegmentTree( int n )
	{
		N = n+5;
		sz = 2*N;
		tree.resize(sz);
	}

	SegmentTree( vector<T>&a )
	{
		N = a.size()+5;
		sz = 2*N;
		tree.resize(sz);

		for(int i=0;i<(int)a.size();i++)
			tree[i+N] = a[i];

		for(int i=N-1;i>0;i--)
			tree[i] = T::merge( tree[i<<1], tree[i<<1|1] );
	}

	void set( int pos, T val )
	{
		for( tree[pos+=N] = val; pos > 1 ; pos >>= 1 )
			tree[pos/2] = T::merge( tree[(pos|1)^1], tree[pos|1] );
	}

	// NOTE BEFORE USING
	// returns cumulative value of range [l,r)
	T cumulative( int l, int r )
	{
		#warning half open interval
		T left, right;
		for( l+=N, r+=N; l < r ; l >>= 1, r >>= 1 )
		{
			if( l&1 )
				left = T::merge( left, tree[l++] );
			if( r&1 )
				right = T::merge( tree[--r], right );
		}
		return T::merge( left, right );
	}

	T operator[]( int pos )
	{
		return tree[pos+N];
	}

	T get( int pos )
	{
		return tree[pos+N];
	}

	void add( int pos, T addend )
	{
		set( pos, T::merge( tree[pos+N], addend ) );
	}

};