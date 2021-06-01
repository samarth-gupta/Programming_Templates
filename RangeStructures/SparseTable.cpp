class Node
{
public:
	ll val;

	Node()
	{
		val = INF;
	}

	Node(ll x)
	{
		val = x;
	}

	static Node merge(Node left, Node right)
	{
		Node result;

		result.val = min(left.val, right.val);

		return result;
	}

};

template<class T>
class SparseTable
{
public:
	int N, LG;
	vector<int> lg;
	vector<T> actual_value;
	vector<vector<T>> table;

	template<class U>
	SparseTable( vector<U> &a )
	{
		actual_value.assign(a.begin(), a.end());
		N = (int)actual_value.size()+5;

		lg.resize(N, 0);
		for(int i=2;i<N;i++) lg[i] = lg[i/2] + 1;
		for(LG=0;(1<<LG)<=N;LG++);

		actual_value.resize(N);
		table.resize(LG, vector<T>(N));

		build();
	}

	void build()
	{
		for(int i=0;i<N;i++)
			table[0][i] = actual_value[i];
		for(int j=1;j<LG;j++)
		{
			int len = (1<<j), half = (1<<(j-1));
			for(int i=0;i+len<=N;i++)
				table[j][i] = T::merge(table[j-1][i], table[j-1][i+half]);
		}
	}

	T operator[]( int pos )
	{
		return table[0][pos];
	}

	// returns result for interval [l,r]
	T cumulative_idem( int l, int r )
	{
		if( l > r ) return T();
		int lgg = lg[r-l], len = (1<<lgg);
		return T::merge(table[lgg][l], table[lgg][r-len]);
	}

	// returns result of non idempotent query function on [l,r]
	T cumulative( int l, int r )
	{
		T result;
		for(int bit=LG;bit>=0;bit--)
		{
			if( (1<<bit) <= r-l )
			{
				result = T::merge(result, table[bit][l]);
				l += (1<<bit);
			}
		}
		return result;
	}

};