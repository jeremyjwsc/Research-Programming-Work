// Greedy_Colory_Graph_FINAL_JW.cpp - Defines the entry point for the console application.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdio.h>

using namespace std;

struct edge {
	string src;
	string dst;
};



// Function prototypes
string get_file(string fileName);
int get_vertices_edges(string xml, vector<string> &vertices, vector<edge> &edges);
int get_vertice_id(string vertice, vector <string> vertices);
string get_vertice_Name(size_t id, vector <string> vertices);
void greedyColoring(int maxnum, vector<int> &color, vector<vector<int>> graph);

int main()
{
	int n = 0; 
	int e = 0;
	string fileName = "greedy_color_graph.xml";
	vector <string> vertices;
	vector <edge> edges;
	vector <vector<int>> graph;
	vector <int> color;
	string text = {};
	int nReply = 0;

	text = get_file(fileName);
	if (text == "")  goto CANCEL;

	nReply = get_vertices_edges(text, vertices, edges);
	if (nReply == -1) goto CANCEL;

	cout << "Total Number of Vertices: " << vertices.size() << endl;
	cout << "Total Number of Edges: " << edges.size() << endl;

	if (vertices.size() < 2) { cout << "Vertices must be more than one." << endl; goto CANCEL; }
	if (edges.size() < 1) { cout << "Edges cannot be zero." << endl; goto CANCEL; }

	n = vertices.size();
	e = edges.size();
	graph.resize(n);
	color.resize(n);
	
	
	for (int i = 0; i < e; i++)
	{
		int x = get_vertice_id(edges[i].src, vertices);
		if (x == -1) { cout << "id not found of vertice " << edges[i].src << endl; goto CANCEL; }
		int y = get_vertice_id(edges[i].dst, vertices);
		if (x == -1) { cout << "id not found of vertice " << edges[i].dst << endl; goto CANCEL; }

		graph[x].push_back(y);
		graph[y].push_back(x);
	}

	for (size_t i = 0; i < graph.size(); i++)
	{
		for (size_t j = 0; j < graph[i].size(); j++)
		{
			cout << "Vertex " << get_vertice_Name(i,vertices) << " or " << i << " is connected with " 
			     << "Vertex " << get_vertice_Name(graph[i][j],vertices) << " or " << graph[i][j] <<  endl;
		}
	}
	
	greedyColoring(n, color, graph);

	for (int i = 0; i<n; i++)
	{
	    
		cout << "Vertex " << get_vertice_Name(i,vertices) << " is coloured " << color[i] + 1 << "\n";
	}
CANCEL:
	system("PAUSE");
    return 0;
}

void greedyColoring(int maxnum, vector<int> &color, vector<vector<int>> graph)
{
	int i = 0;
	size_t j = 0;
	int n = maxnum;
	bool* unused;
	unused = new bool[n];

	color[0] = 0;
	for (i = 1; i<n; i++)
		color[i] = -1;


	for (i = 0; i<n; i++)
		unused[i] = 0;

	for (i = 1; i < n; i++)
	{
		for (j = 0; j<graph[i].size(); j++)
			if (color[graph[i][j]] != -1)
				unused[color[graph[i][j]]] = true;
		int cr;
		for (cr = 0; cr<n; cr++)
			if (unused[cr] == false)
				break;

		color[i] = cr;

		for (j = 0; j<graph[i].size(); j++)
			if (color[graph[i][j]] != -1)
				unused[color[graph[i][j]]] = false;
	}

}

int get_vertice_id(string vertice, vector <string> vertices){

	for (size_t i = 0; i < vertices.size(); i++)
	{
		if (vertices[i] == vertice) return i;
	}
	return -1;
}

string get_vertice_Name(size_t id, vector <string> vertices) {
	if (id < vertices.size()) return vertices[id];
	return "";
}

int get_vertices_edges(string xml, vector<string> &vertices, vector<edge> &edges) {
	string tagGraph = "<graph>";
	string tagGraphEnd = "</graph>";
	string tagNodes = "<nodes>";
	string tagNodesEnd = "</nodes>";
	string tagNode = "<node";
	string Node = {};
	string Edge = {};
	string tagEdges = "<edges>";
	string tagEdgesEnd = "</edges>";
	string tagEdge = "<edge";
	string tagEnd = "/>";
	string atbName = "name=";
	string atbSrc = "src=";
	string atbDst = "dst=";
	string Src = {};
	string Dst = {};
	size_t nStart = 0;
	size_t nEnd = 0;
	size_t nOffset = 0;
	bool isValid = false;

		// scan for valid graph xml node
	isValid = false;
	nStart = xml.find(tagGraph);
	if (nStart != string::npos)
	{
		nStart = xml.find(tagGraphEnd, tagGraph.length());
		if (nStart != string::npos) isValid = true;
	}
	if (isValid == false)
	{
		cout << "Invalid graph xml node found." << endl;
		return -1;
	}

	// scan for valid nodes xml node
	isValid = false;
	nStart = xml.find(tagNodes);
	if (nStart != string::npos)
	{
		nStart = xml.find(tagNodesEnd, tagNodes.length());
		if (nStart != string::npos) isValid = true;
	}
	if (isValid == false)
	{
		cout << "Invalid nodes xml node found." << endl;
		return -1;
	}

	// scan for valid edges xml node
	isValid = false;
	nStart = xml.find(tagEdges);
	if (nStart != string::npos)
	{
		nStart = xml.find(tagEdgesEnd, tagEdges.length());
		if (nStart != string::npos) isValid = true;
	}
	if (isValid == false)
	{
		cout << "Invalid edges xml node found." << endl;
		return -1;
	}
	
	// find Nodes
	nStart = xml.find(tagGraph);
	if (nStart != string::npos)
	{
		nOffset = tagGraph.length();
		nStart = xml.find(tagNodes, nOffset);
		if (nStart != string::npos)
		{
			nOffset = nStart + tagNodes.length();
			nStart = xml.find(tagNode, nOffset);
			while (nStart != string::npos)
			{
				nOffset = nStart + tagNode.length();
				nStart = xml.find(atbName, nOffset);
				if (nStart != string::npos)
				{
					nOffset = nStart + atbName.length();
					nEnd = xml.find(tagEnd, nOffset);
					if (nEnd != string::npos)
					{
						Node = xml.substr(nOffset, nEnd - nOffset);
						Node = Node.substr(1, Node.length() - 2);
						vertices.push_back(Node);
						cout << "Vertex " << Node << " is " << get_vertice_id(Node, vertices) << endl;
						nOffset = nEnd + tagEnd.length();
						nStart = xml.find(tagNode, nOffset);
					}
					else
					{
						cout << "Invalid end of node." << endl;
						return -1;
					}

				}
				else
				{
					cout << "Attribute 'Name' not found." << endl;
					return -1;
				}
			}
		}
	}

	// find Edges
	nStart = xml.find(tagGraph);
	if (nStart != string::npos)
	{
		nOffset = tagGraph.length();
		nStart = xml.find(tagEdges, nOffset);
		if (nStart != string::npos)
		{
			nOffset = nStart + tagEdges.length();
			nStart = xml.find(tagEdge, nOffset);
			while (nStart != string::npos)
			{
				nOffset = nStart + tagEdge.length();
				nStart = xml.find(atbSrc, nOffset);
				if (nStart != string::npos)
				{
					nOffset = nStart + atbSrc.length();
					nEnd = xml.find(atbDst, nOffset);
					if (nEnd != string::npos)
					{
						Src = xml.substr(nOffset, nEnd - nOffset);
						Src = Src.substr(1, Src.length() - 3);
						//cout << "edge source " << Src << endl;
						nStart = nEnd;
						nOffset = nEnd + atbDst.length();
						nEnd = xml.find(tagEnd, nOffset);
						if (nEnd != string::npos)
						{
							Dst = xml.substr(nOffset, nEnd - nOffset);
							Dst = Dst.substr(1, Dst.length() - 3);
							//cout << "edge destination " << Dst << endl;
						}
						else
						{
							cout << "Invalid end of edge node." << endl;
							return -1;
						}
						edge e;
						e.src = Src; e.dst = Dst;
						edges.push_back(e);
						cout << "Edge " << Src << "--" << Dst << endl;
						nOffset = nEnd + tagEnd.length();
						nStart = xml.find(tagEdge, nOffset);
					}
					else
					{
						cout << "Invalid end of attribute 'Dst'." << endl;
						return -1;
					}

				}
				else
				{
					cout << "Attribute 'Src' not found." << endl;
					return -1;
				}
			}
		}
	}

	return 0;
}

string get_file(string fileName)
{
	string buffer;
	char c;

	ifstream in(fileName);   if (!in) { cout << fileName << " not found \n"; }
	while (in.get(c)) buffer += c;
	in.close();

	return buffer;
}