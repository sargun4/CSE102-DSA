#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 10000

bool allburnt(int building[][MAX_SIZE], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (building[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}
int time(int building[][MAX_SIZE], int m, int n) {
    int time_elapsed = 0;
    while (!allburnt(building, m, n)) {
        int temp_building[MAX_SIZE][MAX_SIZE];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                temp_building[i][j] = building[i][j];
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (building[i][j] == 1) {
                    int arr[3] = {-1, 0, 1};
                    for (int a = 0; a < 3; a++) {
                        for (int b = 0; b < 3; b++) {
                            if (i+arr[a] >= 0 && i+arr[a] < m && j+arr[b] >= 0 && j+arr[b] < n) {
                                temp_building[i+arr[a]][j+arr[b]] = 1;
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                building[i][j] = temp_building[i][j];
            }
        }
        time_elapsed++;
    }
    return time_elapsed;
}

int main() {
    int m, n;
    scanf("%d%d", &m, &n);

    // allocate memory for the building array
    int **building = (int **) malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        building[i] = (int *) malloc(n * sizeof(int));
    }
    // read the building matrix from input
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &building[i][j]);
        }
    }
    // calculate the time it takes for the fire to spread
    int time_elapsed = (int**)time(building, m, n);
    // print the result to output
    printf("%d\n", time_elapsed);
    // free the memory allocated for the building array
    for (int i = 0; i < m; i++) {
        free(building[i]);
    }
    free(building);
    return 0;
}
