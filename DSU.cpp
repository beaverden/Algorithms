class DSU
{
public:
	DSU(const int MAX_NODES)
	{
		this->components = MAX_NODES;
		this->parent = new int[MAX_NODES];
		this->rank = new int[MAX_NODES];
		for (int i = 0; i < MAX_NODES; i++)
		{
			this->parent[i] = i;
			this->rank[i] = 1;
		}
	}
	~DSU()
	{
		delete[] this->parent;
		delete[] this->rank;
	}

	int findParent(int u)
	{
		if (this->parent[u] == u)
		{
			return u;
		}
		else
		{
			parent[u] = findParent(parent[u]);
			return parent[u];
		}
	}

	void merge(int u, int v)
	{
		int uParent = findParent(u);
		int vParent = findParent(v);
		if (uParent == vParent) return;
		
		if (rank[uParent] > rank[vParent])
		{
			rank[uParent] += rank[vParent];
			parent[vParent] = uParent;
		}
		else
		{
			rank[vParent] += rank[uParent];
			parent[uParent] = vParent;
		}
		this->components--;
	}

	bool areConnected(int u, int v)
	{
		return findParent(u) == findParent(v);
	}

	int size(int u)
	{
		return rank[findParent(u)];
	}

private:
	int * parent;
	int * rank;
	int components;
};