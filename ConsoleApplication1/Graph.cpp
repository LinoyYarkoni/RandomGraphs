#include "Graph.h"

Graph::Graph() {}

/*the constructor create the adjacency list*/
Graph::Graph(int v, float p)
{
	int i, j;
	size = v;

	/*initialize the adjacency list*/
	for (i = 0; i < size; i++)
	{
		table.push_back(vector<int>());
		for (j = 0; j < size; j++)
		{
			if (j < i && std::find(table[j].begin(), table[j].end(), i) != table[j].end())
			{
				table[i].push_back(j);
				continue;
			}
			if (i != j && (float)rand() / RAND_MAX <= p)
			{
				table[i].push_back(j);
			}
		}
	}
}

/*check if there is isolated vetex in the graph:*/
bool Graph::isIsolated()
{
	for (int i = 0; i < size; i++)
	{
		if (table[i].empty())/*if there is a row in the adjacency list, there is an isolated vertex*/
		{
			return true;
		}
	}
	return false;
}

/*check if there graph is connected:*/
bool Graph::connectivity()
{
	stack <int> stack_;
	vector <int> used;
	int node;
	int i;

	if (size <= 1)
	{
		return true;
	}

	/*starts with node in graph*/
	stack_.push(0);
	used.push_back(0);
	while (!stack_.empty())
	{
		node = stack_.top();/**/
		stack_.pop();
		for (int i : table[node])
		{
			/*check if node have neighboor that does not in used*/
			if (std::find(used.begin(), used.end(), i) == used.end())
			{
				/*add this neighboor to stack_. and to used */
				stack_.push(i);
				used.push_back(i);
			}
			/*if we found all the vertex*/
			if (used.size() >= size)
			{
				return true;
			}
		}
	}

	return false;
}

/*find the graph's diameter using BFS algorithem:*/
int Graph::doubleBFS(int source)
{
	bool visited[500];
	int dist[500];

	vector<int> queue;

	int i, x;

	/*initialize all vertices to "not visited" ans distance as infinity*/
	for (i = 0; i < size; i++)
	{
		visited[i] = false;
		dist[i] = 9999;
	}

	dist[source] = 0; /*the distance for the first vertex is 0*/
	visited[source] = true; /*update the visit status*/

	queue.push_back(source);/*push the start vertex on the queue*/
	while (!queue.empty())/*while queue is not empty*/
	{
		x = queue.front(); /*save the first vertex as x*/
		queue.erase(queue.begin());/*remove it from the queue*/

		for (int i : table[x]) /*for all the neighboors of vertex x*/
		{
			if (!visited[i]) /*if we did not visited this vertex*/
			{

				dist[i] = dist[x] + 1; /*update diatance*/
				visited[i] = true; /*update visit status*/
				queue.push_back(i); /*add x's children*/
			}
		}
	}

	/*find the most diatanced vertex */
	int farthest = -1;
	for (i = 0; i < size; i++)
	{
		if (9999 > dist[i] && dist[i] > farthest)
		{
			farthest = i;
		}
	}

	/*if there is not such vertex in the graph*/
	if (farthest == -1)
	{
		return 9999;
	}

	/*BFS again from farthest vertex*/	
	for (i = 0; i < size; i++)
	{
		visited[i] = false;
		dist[i] = 9999;
	}

	dist[farthest] = 0;
	visited[farthest] = true;

	queue.push_back(farthest);

	while (!queue.empty())
	{
		x = queue.front();
		queue.erase(queue.begin());

		for (int i : table[x])
		{
			if (!visited[i])
			{
				dist[i] = dist[x] + 1;
				visited[i] = true;
				queue.push_back(i);
			}
		}
	}

	/*finding max value after second BFS*/
	int max = -1;
	for (i = 0; i < size; i++)
	{
		if (9999 > dist[i] && dist[i] > max)
		{
			max = dist[i];
		}
	}

	return max;
}

int Graph::diameter()
{
	return doubleBFS(0);
}