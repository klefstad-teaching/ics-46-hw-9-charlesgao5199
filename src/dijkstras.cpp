#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& graph, int source, vector<int>& previous) {
    // Initialize the distance vector with "infinity" for all vertices,
    // and set the source vertex's distance to 0.
    vector<int> distances(graph.numVertices, INF);
    distances[source] = 0;

    // Initialize the previous vector for path reconstruction.
    previous.assign(graph.numVertices, -1);

    // Min-heap (priority queue) to efficiently get the vertex with the smallest distance.
    // The queue holds pairs: {current_distance, vertex_index}.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> vertexQueue;
    vertexQueue.push({distances[source], source});

    // Process the graph until there are no more vertices to examine.
    while (!vertexQueue.empty()) {
        // Use structured bindings to unpack the top element.
        auto [currentDistance, u] = vertexQueue.top();
        vertexQueue.pop();

        // If this distance is outdated, skip it.
        if (currentDistance > distances[u])
            continue;

        // Iterate over all edges leaving vertex 'u'
        for (const auto& edge : graph[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            int newDistance = currentDistance + weight;

            // If a shorter path to vertex 'v' is found, update it.
            if (newDistance < distances[v]) {
                distances[v] = newDistance;
                previous[v] = u;
                vertexQueue.push({newDistance, v});
            }
        }
    }

    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;

    // Check if the destination is unreachable.
    if (distances[destination] == INF) {
        cout << "No path exists to destination " << destination << endl;
        return path;
    }

    // Reconstruct the path backwards using the 'previous' vector.
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }

    // Reverse to obtain the correct order from source to destination.
    reverse(path.begin(), path.end());

    // Calculate the total cost and print the path.
    int total = distances[destination];
    print_path(path, total);

    return path;
}

void print_path(const vector<int>& v, int total) {
    for (int vertex : v) {
        cout << vertex << " ";
    }
    cout << "\nTotal cost is " << total << '\n';
}