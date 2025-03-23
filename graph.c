#include "graph.h"

int graph[N][N] = {
    {0, 12, 10, INF, INF, INF, 12},
    {12, 0, 8, 12, INF, INF, INF},
    {10, 8, 0, 11, 5, INF, 9},
    {INF, 12, 11, 0, 11, 10, INF},
    {INF, INF, 3, 11, 0, 6, INF},
    {INF, INF, INF, 10, 6, 0, 9},
    {12, INF, 9, INF, 7, 9, 0}
};
