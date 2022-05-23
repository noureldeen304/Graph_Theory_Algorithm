#include<iostream>
#include<list>
#include<vector>
#include<map>
using namespace std;
struct adjacent_node
{
	string des;
	int cost;
	string parent;
};
struct edge
{
	string src;
	string des;
	int cost;
};
class priorityqueue
{
private:
	vector<adjacent_node> heap;
	int right(int index_of_parent)
	{
		int p = (index_of_parent * 2) + 2;
		if (p >= heap.size())
			return -1;
		else
			return p;
	}
	int left(int index_of_parent)
	{
		int p = (index_of_parent * 2) + 1;
		if (p >= heap.size())
			return-1;
		else return p;
	}
	int parent(int index_of_child)
	{
		return (index_of_child == 0) ? -1 : (index_of_child - 1) / 2;
	}
	void reheapup(int pos)
	{
		if (pos == 0 || heap[parent(pos)].cost < heap[pos].cost)
			return;
		swap(heap[parent(pos)], heap[pos]);
		reheapup(parent(pos)); // parent(pos)--------> the new pos of our node after swapping
	}
	void reheapdown(int pos)
	{
		int smallestchildpos = left(pos);
		if (smallestchildpos == -1) // no left child therefore no right child
			return;


		int rightchildpos = right(pos);
		if (rightchildpos != -1)
			if (heap.size() >= 3)
			{
				if (heap[rightchildpos].cost <= heap[smallestchildpos].cost)
					smallestchildpos = rightchildpos;
			}

		if (heap.size() >= 2)
			if (heap[pos].cost > heap[smallestchildpos].cost)
			{
				swap(heap[pos], heap[smallestchildpos]);
				reheapdown(smallestchildpos);
			}
	}
public:
	void pop()
	{
		if (heap.size() > 0)
		{
			heap.front() = heap.back();
			heap.pop_back();
			reheapdown(0);
		}
	}
	adjacent_node exractmincost()
	{
		if (heap.size() != 0)
			return heap.front();
	}
	void push(adjacent_node newadjacent)
	{
		heap.push_back(newadjacent);
		reheapup(heap.size() - 1);
	}
	bool isempty()
	{
		return heap.size() == 0;
	}
};
class graph
{
private:
	int num_nodes;
	int num_edges;
	map<int, string> nodes;
	map<int, edge> edges;
	map<string, list<adjacent_node> > vertices;
	priorityqueue pq;
	map<string, int> dis;
	map<string, bool> visited;
public:
	graph(string nodes[], int num_nodes, edge edges[], int num_edges)
	{
		this->num_nodes = num_nodes;
		this->num_edges = num_edges;
		for (int i = 0; i < num_nodes; i++)
		{
			this->nodes[i] = nodes[i];
		}
		for (int i = 0; i < num_edges; i++)
		{
			vertices[edges[i].src].push_back({ edges[i].des, edges[i].cost, edges[i].src });
			vertices[edges[i].des].push_back({ edges[i].src, edges[i].cost, edges[i].des });
			this->edges[i] = edges[i];
		}
	}
	void dijkstra(string source, string destination)
	{
		map<string, vector<string> > path;
		for (int i = 0; i < num_nodes; i++)
		{
			visited[nodes[i]] = false;
			dis[nodes[i]] = INT_MAX;
		}
		adjacent_node cur;
		dis[source] = 0;
		visited[source] = true;
		path[source].push_back(source);
		for (auto i : vertices[source])
		{
			pq.push(i);
		}
		while (!pq.isempty())
		{
			cur = pq.exractmincost();
			pq.pop();
			if (dis[cur.parent] + cur.cost < dis[cur.des])
			{
				dis[cur.des] = dis[cur.parent] + cur.cost;

				while (!path[cur.des].empty())
					path[cur.des].pop_back();

				for (auto i = path[cur.parent].begin(); i != path[cur.parent].end(); i++)
				{
					path[cur.des].push_back(*i);
				}

				path[cur.des].push_back(cur.des);
			}
			visited[cur.des] = true;
			for (auto i : vertices[cur.des])
			{
				if (!visited[i.des])
					pq.push(i);
			}
		}
		cout << "the shortest path from " << source << " to " << destination << ": " << dis[destination] << "\n";
		for (auto j = path[destination].begin(); j != path[destination].end(); j++)
		{
			cout << *j;
			if (j != path[destination].end() - 1)
				cout << " -> ";
		}
		cout << "\n\n";
	}
	
};
int main()
{
	int num_edge;
	int num_node;
	string name;
	edge* edges1;
	string* nodes;

	cout << "enter the number of towns: ";
	cin >> num_node;
	nodes = new string[num_node];
	for (int i = 0; i < num_node; i++)
	{
		cout << "enter town " << i + 1 << ": ";
		cin >> nodes[i];
	}

	cout << "enter the number of edges in the graph: ";
	cin >> num_edge;

	edges1 = new edge[num_edge];
	for (int i = 0; i < num_edge; i++)
	{
		cout << "enter the edge " << i + 1 << " information: \n";
		cout << "source: ";
		cin >> edges1[i].src;

		cout << "destination: ";
		cin >> edges1[i].des;

		cout << "distance: ";
		cin >> edges1[i].cost;
		cout << "\n****************\n";
	}

	graph graph(nodes, num_node, edges1, num_edge);
	graph.display();

	string source, des;
	cout << "enter any two nodes to find the shortest path between them and compute it's distance: \n";
	cout << "source: "; cin >> source;
	cout << "destination: "; cin >> des;
	graph.dijkstra(source,des);
	cout << "\n\n";
	return 0;
}
