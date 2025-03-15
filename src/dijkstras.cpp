#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph &G, int source, vector<int> &previous)
{
    int numVertices = G.size();

    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    previous.assign(numVertices, -1);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> minHeap; //pair<vertex,weight>
    minHeap.push({source,0});
    distances[source] = 0;

    while (!minHeap.empty())
    {
        int u = minHeap.top().second;
        minHeap.pop();

        if(visited[u]) continue;
        visited[u] = true;

        for(const Edge &edge: G[u])
        {
            int v = edge.dst;
            int weight = edge.weight;

            if(distances[u] != INF && (distances[u] + weight) < distances[v])
            {
                if(distances[u] + weight >= 0)
                {
                    distances[v] = distances[u] + weight;
                    previous[v] = u;
                    minHeap.push({distances[v], v});
                }
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{
    vector<int> dijkpath;
    if(destination != -1 && previous[destination]== -1)
        return {};

    for (int i = destination; i != -1; i = previous[i])
    {
        dijkpath.push_back(i);
    }
    reverse(dijkpath.begin(), dijkpath.end());
    return dijkpath;
}
void print_path(const vector<int>& v, int total)
{
    if(v.empty())
    {
        cout<<"\nTotal cost is " << total << "\n";
        return;
    }
    for(size_t i=0; i<v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout<<"\nTotal cost is " << total << "\n";
}
string get_arg(int argc, char *argv[], string def)
{
    if(argc > 1)
        return string(argv[1]);//return first argument
    else
        return def; //default value
}