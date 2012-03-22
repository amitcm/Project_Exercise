#include "stdafx.h"
#include "Graphs.h"

using namespace std;

#define MAX_N 100

int graph::BFS(const graph g, int key)
{
	return 1;
}

int graph::DFS(const graph g, int key)
{
	return 1;
}


/*static*/ void graph::initialize_graph(bool directed)
{
	this->nvertices = 0;
	this->nedges = 0;
	this->directed = directed;

	for(int i = 0; i < MAX_N; i++)
	{
		this->outdegree[i] = -1;
		this->edges[i] = NULL;			// An null pointing 'array of pointers'. It's going to point to the would be lists.
	}
}

//void insert_edge(graph *g, int x, int y, bool directed)
//{
//	g->directed = directed;
//	edgenode *node;
//
//	// Allocate node
//	node = (edgenode *)malloc(sizeof(edgenode));
//
//	// Fill the node with available data
//	node->y = y;
//	node->weight = NULL;
//	node->next = g->edges[x];			// Store the address that the vertex was pointing to. As, this node will be attached in-between
//
//	// Insert at the head of the list <===== Note the 'list'
//	g->edges[x] = node;
//	g->outdegree[x] ++;
//
//	if(!g->directed)
//		insert_edge(g, y, x, true);
//	else
//		g->nedges++;
//}


// Actually populates graph from user data.

/*static*/ void graph::read_graph(bool directed)
{
	this->directed = directed;
	int nedges = 0;
	int x, y;
	this->initialize_graph(this->directed);
	// Requirements:
	// Number of vertices to make the null pointing 'array of pointers'
	// Number of edges to iterate and populate the graph. Because, we need to populate data for the connected edges.
	scanf("%d", &nedges);
	for(int i = 0; i < nedges; i++)
	{
		scanf("%d %d", &x, &y);
		insert_edge(x, y, this->directed);
	}
}

/*static*/ void graph::insert_edge(int x, int y, bool directed)
{
	directed = this->directed;
	edgenode *node;

	// Allocate node
	node = (edgenode *)malloc(sizeof(edgenode));

	// Fill the node with available data
	node->y = y;
	if(this->outdegree[y] == -1){
		nvertices++;
		this->outdegree[y] = 0;
	}
	node->weight = NULL;
	node->next = this->edges[x];			// Store the address that the vertex was pointing to. As, this node will be attached in-between

	// Insert at the head of the list <===== Note the 'list'
	if(this->outdegree[x] == -1){
		nvertices++;
		this->outdegree[x] = 0;
	}
	this->edges[x] = node;
	this->outdegree[x] ++;
	
	if(!this->directed)
		insert_edge(y, x, true);
	else
		this->nedges++;
}

// Wrong at i < this->nvertices !!!
/*static*/ void graph::print_graph()
{
	edgenode *node;
	for(int i = 0; i < this->nvertices; i++)
	{
		printf("%d: ", i);
		node = this->edges[i];
		while(node != NULL)
		{
			printf(" %d", node->y);
			node = node->next;
		}
		printf("\n");
	}
}