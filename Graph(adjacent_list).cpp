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
struct Edge
{
	string src;
	string des;
	int cost;
};
class Graph
{
private:
	int num_nodes;
	int num_edges;
	map<int, string> nodes;
	map<int, Edge> edges;
	map<string, list<adjacent_node> > vertices;
public:
	Graph(string nodes[], int num_nodes, Edge edges[], int num_edges)
	{
		this->num_nodes = num_nodes;
		for (int i = 0; i < num_nodes; i++)
		{
			this->nodes[i] = nodes[i];
		}
		for (int i = 0; i < num_edges; i++)
		{
			vertices[edges[i].src].push_back({ edges[i].des, edges[i].cost, edges[i].src });
			vertices[edges[i].des].push_back({ edges[i].src, edges[i].cost, edges[i].des });
			//because it is undirected graph
		}
	}

	void display()
	{
		for (int i = 0; i < num_nodes; i++)
		{
			cout << nodes[i] << ": ";
			for (auto j = vertices[nodes[i]].begin(); j != vertices[nodes[i]].end(); j++)
			{
				cout << "(" << j->des << "," << j->cost << ") ";
			}
			cout << "\n";
		}
		cout << "\n\n";
	}
};

int main()
{
	int num_edge;
	int num_node;
	string name;
	Edge* edges1;
	string* nodes;

	cout << "Enter the number of towns: ";
	cin >> num_node;
	nodes = new string[num_node];
	for (int i = 0; i < num_node; i++)
	{
		cout << "Enter town " << i + 1 << ": ";
		cin >> nodes[i];
	}

	cout << "Enter the number of edges in the graph: ";
	cin >> num_edge;

	edges1 = new Edge[num_edge];
	for (int i = 0; i < num_edge; i++)
	{
		cout << "Enter the edge " << i + 1 << " information: \n";
		cout << "Source: ";
		cin >> edges1[i].src;

		cout << "Destination: ";
		cin >> edges1[i].des;

		cout << "Distance: ";
		cin >> edges1[i].cost;
		cout << "\n****************\n";
	}

	Graph graph(nodes, num_node, edges1, num_edge);
	graph.display();
	return 0;
}