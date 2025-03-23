#ifndef GRAPH_H
#define GRAPH_H

#define INF 9999
#define N 7  // Number of cities

extern int graph[N][N]; // adjacency matrix


//declaring the functions
void solve_som();
void solve_branch_bound();
void solve_nearest_neighbor();
#endif
