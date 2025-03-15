#include "dijkstras.h"


int main(int argc, char *argv[]) {
    //i just replace src/small.txt with other file names in src
    // so the output in terminal is not long
    string filename = get_arg(argc, argv, "src/largest.txt");
    Graph G;
    file_to_graph(filename, G);

    int source=0;
    vector<int> previous(G.numVertices);

    cout << "dijkstra .txt test: " << endl;
    vector<int> dijk_tst = dijkstra_shortest_path(G, source, previous);

    for (int dest = 0; dest < G.numVertices; ++dest)
    {
        vector<int> path = extract_shortest_path(dijk_tst, previous, dest);
        print_path(path, dijk_tst[dest]);
    }

    return 0;
}