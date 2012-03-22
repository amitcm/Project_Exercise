#include "stdafx.h"
#include <stdio.h>
#include <string>

using namespace std;

#define MAX_N 100

// Adjacency list implementation
// Look at an image of Adjacency list on web. Look at the array thing and the nodes [list] connected to it. 

struct edgenode
{
							// First vertex is implicit in edge.
	int y;					// The vertex which this vertex is pointing to.
	int weight;				// The edge weight between vertex which this vertex is pointing to and itself.
	struct edgenode *next;
};

class graph
{
private:
	struct edgenode *edges[MAX_N];
	int outdegree[MAX_N];
	int nvertices;
	int nedges;
	bool directed;
public:
	graph(bool bDirected) 
	{
		nvertices = 0;
		nedges = 0;
		directed = bDirected;

		for(int i = 0; i < MAX_N; i++)
		{
			outdegree[i] = -1;
			edges[i] = NULL;			// An null pointing 'array of pointers'. It's going to point to the would be lists.
		}
	}
	void initialize_graph(bool directed);	// Can be used later to clear or re-initialize. But, make sure it doesn't leak
	void read_graph(bool directed);
	void insert_edge(int x, int y, bool directed);
	void print_graph();
	int BFS(const graph g, int key);
	int DFS(const graph g, int key);
	//friend void insert_edge(graph *g, int x, int y, bool directed);
};


