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
class graph
{
private:
	int num_nodes;
	int num_edges;
	map<int, string> nodes;
	map<int, edge> edges;
	map<string, list<adjacent_node> > vertices;
	map<string, int> dis;
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
	void bellmam_ford(string source, string destination)
	{
		cout << "bellmam ford:\n";
		map<string, vector<string> > path;
		for (int i = 0; i < num_nodes; i++)
		{
			dis[nodes[i]] = INT_MAX;
		}
		dis[source] = 0;
		path[source].push_back(source);
		for (int max_edges = 0; max_edges < num_nodes - 1; max_edges++)
		{
			for (int i = 0; i < num_nodes; i++)
			{
				for (auto j = vertices[nodes[i]].begin(); j != vertices[nodes[i]].end(); j++)
				{
					if (dis[j->parent] != INT_MAX && dis[j->parent] + j->cost < dis[j->des])
					{
						dis[j->des] = dis[j->parent] + j->cost;
						while (!path[j->des].empty())
						{
							path[j->des].pop_back();
						}
						for (auto i : path[j->parent])
						{
							path[j->des].push_back(i);
						}
						path[j->des].push_back(j->des);
					}
				}
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

	string source, des;
	cout << "enter any two nodes to find the shortest path between them and compute it's distance: \n";
	cout << "source: "; cin >> source;
	cout << "destination: "; cin >> des;
	graph.bellmam_ford(source, des);



	cout << "\n\n";
	return 0;
}
 