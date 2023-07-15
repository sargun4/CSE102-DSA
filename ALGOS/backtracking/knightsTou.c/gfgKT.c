// C program for Knight Tour problem
#include <stdio.h>
#define N 8

int solveKTUtil(int x, int y, int movei, int sol[N][N],
				int xMove[], int yMove[]);

/* A utility function to check if i,j are valid indexes
for N*N chessboard */
int isSafe(int x, int y, int sol[N][N])
{
	return (x >= 0 && x < N && y >= 0 && y < N
			&& sol[x][y] == -1);
}

/* A utility function to print solution matrix sol[N][N] */
void printSolution(int sol[N][N])
{
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++)
			printf(" %2d ", sol[x][y]);
		printf("\n");
	}
}

/* This function solves the Knight Tour problem using
Backtracking. This function mainly uses solveKTUtil()
to solve the problem. It returns false if no complete
tour is possible, otherwise return true and prints the
tour.
Please note that there may be more than one solutions,
this function prints one of the feasible solutions. */
int solveKT()
{
	int sol[N][N];

	/* Initialization of solution matrix */
	for (int x = 0; x < N; x++)
		for (int y = 0; y < N; y++)
			sol[x][y] = -1;

	/* xMove[] and yMove[] define next move of Knight.
	xMove[] is for next value of x coordinate
	yMove[] is for next value of y coordinate */
	int xMove[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
	int yMove[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

	// Since the Knight is initially at the first block
	sol[0][0] = 0;

	/* Start from 0,0 and explore all tours using
	solveKTUtil() */
	if (solveKTUtil(0, 0, 1, sol, xMove, yMove) == 0) {
		printf("Solution does not exist");
		return 0;
	}
	else
		printSolution(sol);

	return 1;
}

/* A recursive utility function to solve Knight Tour
problem */
int solveKTUtil(int x, int y, int movei, int sol[N][N],
				int xMove[N], int yMove[N])
{
	int k, next_x, next_y;
	if (movei == N * N)
		return 1;

	/* Try all next moves from the current coordinate x, y
	*/
	for (k = 0; k < 8; k++) {
		next_x = x + xMove[k];
		next_y = y + yMove[k];
		if (isSafe(next_x, next_y, sol)) {
			sol[next_x][next_y] = movei;
			if (solveKTUtil(next_x, next_y, movei + 1, sol,
							xMove, yMove)
				== 1)
				return 1;
			else
				sol[next_x][next_y] = -1; // backtracking
		}
	}

	return 0;
}
int main(){
	solveKT();
	return 0;
}



// 2
#include <stdio.h>
#include <stdbool.h>
#define N 8 // size of the chessboard
int moves[8][2] = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1},
                   {2, -1}, {1, -2}, {-1, -2}, {-2, -1}}; // possible knight moves
int board[N][N]; // chessboard
bool is_valid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}
bool solve(int x, int y, int move_count) {
    if (move_count == N*N) { // all squares have been visited
        return true;   }
    for (int i = 0; i < 8; i++) {
        int next_x = x + moves[i][0];
        int next_y = y + moves[i][1];
        if (is_valid(next_x, next_y)) {
            board[next_x][next_y] = move_count;
            if (solve(next_x, next_y, move_count+1)) {
                return true;
            }
            board[next_x][next_y] = -1; // backtrack
        }
    }
    return false;
}
int main() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = -1;
        }
    }
    int start_x = 0, start_y = 0;
    board[start_x][start_y] = 0;
    if (solve(start_x, start_y, 1)) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%2d ", board[i][j]);
            }
            printf("\n");
        }
    } else { printf("No solution exists.\n");}
    return 0;}
