#include <iostream>
#include <vector>
#include <queue>
#include <limits>

#define INF std::numeric_limits<int>::max()

// Structure to represent a vertex and its distance from the source
struct Vertex {
    int index;
    int distance;

    bool operator<(const Vertex& other) 
	const {
        return distance > other.distance;
    	}
};

// Dijkstra's algorithm to find the shortest path between two vertices
std::pair<std::vector<int>, int> dijkstra(const std::vector<std::vector<int>>& graph, int source, int destination)
{
    int numVertices = graph.size();

    // Create a vector to store the distances from the source
    std::vector<int> distances(numVertices, INF);

    // Create a vector to store the previous vertex in the shortest path
    std::vector<int> previous(numVertices, -1);

    // Create a priority queue to store the vertices to be processed
    std::priority_queue<Vertex> pq;

    // Set the distance of the source vertex to 0 and add it to the priority queue
    distances[source] = 0;
    pq.push({source, 0});

    while (!pq.empty()) {
        // Get the vertex with the minimum distance from the priority queue
        Vertex current = pq.top();
        pq.pop();

        // Stop if the destination vertex is reached
        if (current.index == destination)
            break;

        // Explore the neighbors of the current vertex
        for (int i = 0; i < numVertices; ++i) {
            int weight = graph[current.index][i];
            if (weight > 0) { // If there is an edge to the neighbor
                int distance = current.distance + weight;

                // Update the distance if a shorter path is found
                if (distance < distances[i]) {
                    distances[i] = distance;
                    previous[i] = current.index;
                    pq.push({i, distance});
                }
            }
        }
    }

    // Reconstruct the shortest path from the source to the destination
    std::vector<int> shortestPath;
    int current = destination;
    while (current != -1) {
        shortestPath.insert(shortestPath.begin(), current);
        current = previous[current];
    }

    // Return the shortest path and the minimum distance
    return {shortestPath, distances[destination]};
}

// Function to display the shortest path
void displayShortestPath(const std::vector<int>& shortestPath, int minDistance) {
    std::cout << "Shortest path: ";
    for (int i = 0; i < shortestPath.size(); ++i) {
        std::cout << shortestPath[i];
        if (i != shortestPath.size() - 1)
            std::cout << " -> ";
    }
    std::cout << std::endl;
    
    std::cout << "Min distance from source to destination: " << minDistance << std::endl;
}

int main() {
    int numVertices = 9; // Number of vertices in the graph

    // Example graph represented using an adjacency matrix
    std::vector<std::vector<int>> graph = {
                        { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
						{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
						{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
						{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
						{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
						{ 0, 0, 4, 14, 10, 0, 2, 0, 0 },
						{ 0, 0, 0, 0, 0, 2, 0, 1, 6 },
						{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
						{ 0, 0, 2, 0, 0, 0, 6, 7, 0 }
    };

    int source = 0; // Source vertex
    int destination = 4; // Destination vertex

    // Run Dijkstra's algorithm to find the shortest path and minimum distance
    std::pair<std::vector<int>, int> result = dijkstra(graph, source, destination);

    // Display the shortest path and minimum distance
    displayShortestPath(result.first, result.second);

    return 0;
}
