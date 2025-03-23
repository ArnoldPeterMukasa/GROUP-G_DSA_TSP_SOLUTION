#include <stdio.h>
#include "graph.h"

void solve_som();
void solve_branch_bound();
void solve_nearest_neighbor();

int main() {
    printf("\n=== Solving TSP ===\n");

    printf("\nRunning Self-Organizing Map (SOM):\n");
    solve_som();

    printf("\nRunning Branch and Bound:\n");
    solve_branch_bound();

    printf("\nRunning Nearest Neighbor:\n");
    solve_nearest_neighbor();

    return 0;
}
