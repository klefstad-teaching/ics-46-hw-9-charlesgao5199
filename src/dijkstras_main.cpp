#include "dijkstras.h"

int main() {
    string file = "small.txt";
    Graph graph;

    file_to_graph(file, graph);

    int source = 0;
    int destination = graph.numVertices - 1;
    vector<int> previous;
    
    // Run Dijkstra's algorithm
    vector<int> distances = dijkstra_shortest_path(graph, source, previous);

    vector<int> path = extract_shortest_path(distances, previous, destination);
    print_path(path, distances[destination]);

    return 0;
}