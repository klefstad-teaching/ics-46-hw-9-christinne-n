#include "dijkstras.h"


vector<int> dijkstra_shortest_path(const Graph &G, int source, vector<int> &previous)
{
    int numVertices = G.size();

    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    previous.assign(numVertices, -1);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> minHeap; //pair<vertex,weight>
    minHeap.push({0, source});
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

            if(distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{
    if(destination != -1 && previous[destination] == -1)
        return {};
    vector<int> dijkpath;
    for (int i = destination; i != -1; i = previous[i])
        dijkpath.push_back(i);
    size_t v = dijkpath.size();
    for (size_t n = 0; n < v/2; ++n)
        swap(dijkpath[n], dijkpath[v-n-1]);//swap to ensure it prints descending order
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