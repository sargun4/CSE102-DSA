#include <stdio.h>
#define N 8

int grid[N][N]={0};

struct Tuple {
    int x;
    int y;
};
struct Tuple possibilites[8];

// This function takes in the current position (x,y) and returns the number
// of possible moves from that position, updating the possibilites array accordingly
int getpossibilities(int x, int y){
    int posx []={2,1,-1,-2,-2,-1,1,2};
    int posy []={1,2,2,1,-1,-2,-2,-1};
    int count = 0;
    for (int i = 0; i < 8; i++) {
    // Check if the next move is within the board boundaries and hasn't been visited yet
        if (x + posx[i] >= 0 && x + posx[i] < N && y + posy[i] >= 0 && y + posy[i] < N && grid[x + posx[i]][y + posy[i]] == 0) {
              // Add the next move to the possibilites array
            possibilites[count].x = x + posx[i];
            possibilites[count].y = y + posy[i];
            count++;
        }
    }
    return count;
}
// This function recursively solves the Knight's Tour problem by trying out all
// possible next moves from the current position until a solution is found
int solve(int x, int y, int ctr){
    grid[x][y] = ctr;
    if (ctr == N*N){
         // If all squares have been visited, a solution has been found
        return 1;
    }

    int num_moves = getpossibilities(x, y);
    struct Tuple pos[num_moves];
    for (int j = 0; j < num_moves; j++) {
        pos[j] = possibilites[j];
    }

    for (int j = 0; j < num_moves; j++) {
        // Find the next move with the fewest number of possible moves
        struct Tuple min = pos[j];
        for (int k = j + 1; k < num_moves; k++) {
            if (getpossibilities(pos[k].x, pos[k].y) < getpossibilities(min.x, min.y)) {
                min = pos[k];
            }
        }
        int next_x = min.x;
        int next_y = min.y;
        int result = solve(next_x, next_y, ctr + 1);
        if (result == 1){
            // If a solution is found, return 1 to terminate the recursion
            return 1;
        }
    }
    // backtracking
    grid[x][y] = 0;
    return 0;
}

void print(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            printf("%d ",grid[i][j]);
        }printf("\n");
    }printf("\n");
}

int main(){
    int startx = 2, starty = 3;
    grid[startx][starty] = 1;
    if (solve(startx, starty, 2) == 1){
        printf("Solution found:\n");
        print();
    } else {
        printf("No solution found.\n");
    }
    return 0;
}
