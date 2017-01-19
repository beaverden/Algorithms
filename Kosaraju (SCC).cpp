/* The function takes an adjacency list representation of the graph g
    and two integers N and M as specified in the problem statement
    You are required to complete this method. */
#include <stack>
#include <algorithm>
#define MAX 50

stack <int> s;
bool vis[MAX];
bool used[MAX];

void dfsTraversal(int source, vector<int> g[MAX])
{
    vis[source] = true;

    for (int i = 0; i<g[source].size(); i++)
    {
        int next = g[source][i];
        if (!vis[next]) dfsTraversal(next, g);
    }
    s.push(source);
}

void processSCC(int source, vector <int> gT[MAX])
{
    used[source] = true;
    //printf("%d ", source);
    for (int i = 0; i<gT[source].size(); i++)
    {
        int next = gT[source][i];
        if (!used[next]) processSCC(next, gT);
    }   
}

int kosaraju(vector<int> g[MAX], int N, int M)
{
    for (int i = 1; i<=N; i++)
    {
        vis[i] = false;
        used[i] = false;
    }
    for (int i = 1; i<=N; i++)
    {
        if (!vis[i])
        dfsTraversal(i, g);
    }
    
    vector<int> gT[MAX];
    
	// Get the transpose adjacent list
    for (int i = 1; i<=N; i++)
    {
        for (int j = 0; j<g[i].size(); j++)
        {
            int adj = g[i][j];
            gT[adj].push_back(i);
        }
    }

    int res = 0;
    while (!s.empty())
    {
        int next = s.top();
        s.pop();
        if (!used[next])
        {
            res++;
            processSCC(next, gT);
        }
    }
    return res;
}