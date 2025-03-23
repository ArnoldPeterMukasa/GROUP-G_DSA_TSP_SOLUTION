#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"

#define ITERATIONS 1000
#define LEARNING_RATE 0.8
#define DECAY_RATE 0.995

double neurons[N][2];  // 2D array to hold the positions of the neurons

void initialize_neurons() {
    // Initialize neurons' positions randomly in 2D space
    for (int i = 0; i < N; i++) {
        neurons[i][0] = rand() % 100;  // X-coordinate of neuron
        neurons[i][1] = rand() % 100;  // Y-coordinate of neuron
    }
}

double euclidean_distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void train_som() {
    double lr = LEARNING_RATE;

    for (int iter = 0; iter < ITERATIONS; iter++) {
        // Randomly select a city to act as the input for the SOM
        int city = rand() % N;

        // Find the winner neuron based on the minimum Euclidean distance
        int winner = 0;
        double min_dist = euclidean_distance(neurons[0][0], neurons[0][1], city * 10, city * 10);

        for (int i = 1; i < N; i++) {
            double dist = euclidean_distance(neurons[i][0], neurons[i][1], city * 10, city * 10);
            if (dist < min_dist) {
                min_dist = dist;
                winner = i;
            }
        }

        // Adjust the winner's position towards the city
        neurons[winner][0] += lr * (city * 10 - neurons[winner][0]);
        neurons[winner][1] += lr * (city * 10 - neurons[winner][1]);

        // Decay the learning rate over time
        lr *= DECAY_RATE;
    }
}

void extract_tsp_route(int tsp_route[]) {
    // Extract a route that visits all cities in the correct order
    int visited[N] = {0};  // Initialize all cities as unvisited

    for (int i = 0; i < N; i++) {
        int closest_city = -1;
        double min_dist = INFINITY;

        // Find the unvisited city that is closest to the current city
        for (int j = 0; j < N; j++) {
            if (!visited[j]) {
                double dist = euclidean_distance(neurons[i][0], neurons[i][1], neurons[j][0], neurons[j][1]);
                if (dist < min_dist) {
                    min_dist = dist;
                    closest_city = j;
                }
            }
        }

        visited[closest_city] = 1;  // Mark this city as visited
        tsp_route[i] = closest_city; // Add the city to the route
    }

    // Close the loop by returning to the starting city
    tsp_route[N] = tsp_route[0];
}

int compute_tsp_cost(int tsp_route[]) {
    int cost = 0;
    for (int i = 0; i < N; i++) {
        cost += graph[tsp_route[i]][tsp_route[i + 1]]; // Sum distances between consecutive cities
    }
    return cost;
}

void solve_som() {
    initialize_neurons();  // Randomly initialize neuron positions
    train_som();  // Train the SOM model to cluster cities

    int tsp_route[N + 1];  // Array to hold the TSP path
    extract_tsp_route(tsp_route);  // Extract the TSP route from the trained SOM

    int total_cost = compute_tsp_cost(tsp_route);  // Compute the total cost of the TSP path

    // Print the TSP path and total cost
    printf("SOM TSP Path: ");
    for (int i = 0; i <= N; i++) {
        printf("%d ", tsp_route[i] + 1);  // Output the path, adjusting for 1-based indexing
    }
    printf("\nTotal Cost: %d\n", total_cost);  // Output the total cost
}
