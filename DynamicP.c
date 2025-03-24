#include <stdio.h>

#define N 7  // Number of cities
#define INF 99999  // this represents no direct connection 

// TSP Graph being represented using arrays showing distances from individual cities using indexes
int graph[N][N] = {
    {0, 12, 10, INF, INF, INF, 12},  // City 1 
    {12, 0, 8, 12, INF, 3, INF},     // City 2 
    {10, 8, 0, 11, 3, INF, 9},       // City 3 
    {INF, 12, 11, 0, 11, INF, INF},  // City 4
    {INF, INF, 3, 11, 0, 6, 7},      // City 5 
    {INF, 3, INF, INF, 6, 0, 9},     // City 6 
    {12, INF, 9, INF, 7, 9, 0}       // City 7 
};

// DP table for memoization ( for storing previously computed results and reuse them later)
int dp[1 << N][N]; // THis declares a 2d array to store dynamic programming table 
                   //  [1<< N] represents 2^N hence 2^7

int path[1 << N][N]; // new table to store the next city in the route

// TSP function using Dynamic Programming and Bitmasking
int tsp(int mask, int pos) { // if all cites are visited (128 in binary) return to the start
    if (mask == (1 << N) - 1) {
        return graph[pos][0]; 
    }

    if (dp[mask][pos] != -1) {
        return dp[mask][pos]; 
    }

    int min_cost = INF;
    int next_city = -1;

    for (int city = 0; city < N; city++) {
        if ((mask & (1 << city)) == 0 && graph[pos][city] != INF) {
            int new_cost = graph[pos][city] + tsp(mask | (1 << city), city);
            if (new_cost < min_cost) {
                min_cost = new_cost;
                next_city = city; // store the city that gives min cost
            }
        }
    }

    path[mask][pos] = next_city; // store the best next city for the current mask and pos
    return dp[mask][pos] = min_cost; // Store result in memoization table
}

// Utility function to initialize DP table
void initializeDP() {
    for (int i = 0; i < (1 << N); i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = -1;
            path[i][j] = -1;
        }
    }
}

//  function to print the route taken
void printRoute() {
    int mask = 1, pos = 0; // Start at City 0 (City 1 in human terms), so mask = 1 means only City 0 is visited
    printf("Route Taken: City %d", pos + 1); // Print the starting city (City 1)

    while (1) {
        int next = path[mask][pos]; // Gettting the next city to visit based on current mask and position
        if (next == -1) break;// If there's no next city (end of route), stop the loop

        printf(" -> City %d", next + 1); // Print the next city
        mask |= (1 << next);// Mark the next city as visited in the mask using bitwise OR
        pos = next; //// Move to the next city
    }
    printf(" -> City %d (Back to start)\n", 1);
}

// Main function
int main() {
    initializeDP();
    int shortest_distance = tsp(1, 0); // Start from City 1 (index 0)
    printf("Shortest Route Distance: %d\n", shortest_distance);
    printRoute(); // <-- calling the new function to show route
    return 0;
}