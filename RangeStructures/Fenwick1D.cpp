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

	static Node unmerge(Node left, Node right)
	{
		Node result;

		result.val = left.val - right.val;

		return result;
	}

};

template<class T>
class FenwickTree
{
public:
	int N;
	vector<T> tree, actual_value;
	
	FenwickTree( int n )
	{
		N = n+5;
		tree.resize(N);
		actual_value.resize(N);
	}

	void add( int pos, T addend )
	{
		pos += 2;

		actual_value[pos] = T::merge(actual_value[pos], addend);
		while( pos < N )
		{
			tree[pos] = T::merge(tree[pos], addend);
			pos += pos & -pos;
		}
	}

	void set( int pos, T val )
	{
		val = T::unmerge(val, actual_value[pos+2]);
		add(pos, val);
	}

	T operator[]( int pos )
	{
		return actual_value[pos+2];
	}

	T get( int pos )
	{
		return actual_value[pos+2];
	}

	// return cumulative value on range [0, pos]
	T cumulative( int pos )
	{
		T result;

		pos += 2;
		while( pos > 0 )
		{
			result = T::merge(result, tree[pos]);
			pos -= pos & -pos;
		}
		return result;
	}

	// return cumulative value on range [l, r]
	T cumulative( int l, int r )
	{
		T result = cumulative(r);
		result = T::unmerge(result, cumulative(l-1));
		return result;
	}

};