#include "graph.h"
#include <stdio.h>

void solve_nearest_neighbor() {
    int visited[N] = {0};  // Keeps track of visited cities
    int path[N + 1];       // To store the path
    int total_cost = 0;
    int current_city = 0;  // Start from city 0 (city 1)
    visited[current_city] = 1;
    path[0] = current_city;

    for (int i = 1; i < N; i++) {
        int next_city = -1;
        int min_distance = INF; // Start with an infinite distance
        
        // Find the nearest unvisited city
        for (int j = 0; j < N; j++) {
            if (!visited[j] && graph[current_city][j] < min_distance) {
                min_distance = graph[current_city][j];
                next_city = j;
            }
        }

        // Update the total cost and the path
        visited[next_city] = 1;
        path[i] = next_city;
        total_cost += min_distance;
        current_city = next_city;
    }

    // Return to the starting city to complete the cycle
    total_cost += graph[current_city][path[0]];

    // Print the path and total cost
    printf("Nearest Neighbor TSP Path: ");
    for (int i = 0; i < N; i++) {
        printf("%d -> ", path[i] + 1);  // Convert 0-based index to 1-based
    }
    printf("%d\n", path[0] + 1);  // Complete the cycle
    printf("Total Cost: %d\n", total_cost);
}
