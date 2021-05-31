class FenwickNode
{
public:
	ll val;

	FenwickNode()
	{
		val = 0;
	}

	FenwickNode(ll x)
	{
		val = x;
	}

	void merge(FenwickNode other)
	{
		val += other.val;
	}

	void unmerge(FenwickNode other)
	{
		val -= other.val;
	}
};

template<class T>
class FenwickTree
{
public:
	int N;
	vector<T> tree, actual_value;
	
	FenwickTree(int n)
	{
		N = n+5;
		tree = vector<T>(N);
		actual_value = vector<T>(N);
	}

	void add(int pos, T addend)
	{
		pos += 2;

		actual_value[pos].merge(addend);
		while( pos < N )
		{
			tree[pos].merge(addend);
			pos += pos & -pos;
		}
	}

	void set(int pos, T val)
	{
		val.unmerge(actual_value[pos+2]);
		add(pos, val);
	}

	T get(int pos)
	{
		return actual_value[pos+2];
	}

	// return cumulative value on range [0, pos]
	T cumulative(int pos)
	{
		T result;

		pos += 2;
		while( pos > 0 )
		{
			result.merge(tree[pos]);
			pos -= pos & -pos;
		}
		return result;
	}

	// return cumulative value on range [l, r]
	T cumulative(int l, int r)
	{
		T result = cumulative(r);
		result.unmerge(cumulative(l-1));
		return result;
	}

};