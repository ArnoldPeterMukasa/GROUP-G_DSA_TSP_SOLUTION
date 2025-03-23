#include <stdio.h>
#include <limits.h>
#include "graph.h"

int min_cost = INT_MAX;  // Minimum cost found
int best_path[N + 1];    // Best path found

// Function to copy the current path into the best_path
void copy_path(int path[]) {
    for (int i = 0; i <= N; i++) {
        best_path[i] = path[i];
    }
}

// Recursive utility function for branch and bound approach
void tsp_branch_bound_util(int level, int cost, int path[], int visited[]) {
    // Base case: all cities have been visited, calculate cost
    if (level == N) {
        cost += graph[path[level - 1]][path[0]];  // Add cost to return to the start
        if (cost < min_cost) {
            min_cost = cost;  // Update minimum cost
            copy_path(path);  // Copy the current path to best_path
        }
        return;
    }

    // Explore all possible cities that haven't been visited
    for (int i = 0; i < N; i++) {
        if (!visited[i] && graph[path[level - 1]][i] != INF) {  // Check for valid path
            visited[i] = 1;  // Mark the city as visited
            path[level] = i; // Add city to current path
            tsp_branch_bound_util(level + 1, cost + graph[path[level - 1]][i], path, visited); // Recurse
            visited[i] = 0;  // Backtrack: mark city as unvisited
        }
    }
}

// Solve the TSP using Branch and Bound
void solve_branch_bound() {
    int path[N + 1] = {0};  // Initialize the path array with the start city (0)
    int visited[N] = {0};    // Array to keep track of visited cities
    visited[0] = 1;          // Mark the start city as visited

    tsp_branch_bound_util(1, 0, path, visited);  // Start solving from city 0

    // Output the best TSP path and the minimum cost
    printf("Branch and Bound TSP Path: ");
    for (int i = 0; i <= N; i++) {
        printf("%d ", best_path[i] + 1);  // Convert 0-based index to 1-based for output
    }
    printf("\nTotal Cost: %d\n", min_cost);
}
