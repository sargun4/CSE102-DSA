
#include <stdio.h>
#include <stdlib.h>

#define MAXCITIES 200001

struct City {
    int count;
    int* connections;
    int visited;
};

struct City* createcity(int n) {
    struct City* city = malloc(sizeof(struct City));
    city->count = 0;
    city->connections = malloc(n * sizeof(int));
    city->visited = 0;
    return city;
}

void add_connction(struct City* city, int v) {
    city->connections[city->count++] = v;
}

int dfs(struct City** cities, int city, int parent, int dist, int target) {
    int count = 0;
    
    if (dist == 0 && city == target)
        count++;
    
    cities[city]->visited = 1;
    
    for (int i = 0; i < cities[city]->count; i++) {
        int child = cities[city]->connections[i];
        
        if (child != parent && cities[child]->visited == 0)
            count += dfs(cities, child, city, dist - 1, target);
    }
    
    return count;
}

int main() {
    int N, T;
    scanf("%d %d", &N, &T);
    
    struct City** cities = malloc((N + 1) * sizeof(struct City*));
    for (int i = 1; i <= N; i++) {
        cities[i] = createcity(N);
    }
    
    for (int i = 1; i < N; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        add_connction(cities[u], v);
        add_connction(cities[v], u);
    }
    
    while (T--) {
        int V, D;
        scanf("%d %d", &V, &D);
        
        for (int i = 1; i <= N; i++) {
            cities[i]->visited = 0;
        }
        int count = dfs(cities, 1, -1, D, V);
        printf("%d\n", count);
    }
    for (int i = 1; i <= N; i++) {
        free(cities[i]->connections);
        free(cities[i]);
    }
    free(cities);
    return 0;
}
