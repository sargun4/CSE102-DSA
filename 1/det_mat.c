#include <stdio.h>

#define N 3

void printmat(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int det1(int mat[N][N]) {
    int determinant = 0;
    int submat[N-1][N-1];
    
    if (N == 1) { // Base case
        return mat[0][0];
    }
    else if (N == 2) { // Base case
        return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
    }
    else { // Recursive case: a mat larger than 2x2
        for (int k = 0; k < N; k++) {
            int i = 0;
            int j = 0;
            for (int row = 1; row < N; row++) {
                for (int col = 0; col < N; col++) {
                    if (col == k) {
                        continue;
                    }
                    submat[i][j] = mat[row][col];
                    j++;
                    if (j == N-1) {
                        j = 0;
                        i++;
                    }
                }
            }
            determinant += mat[0][k] * det1(submat) * (k%2 == 0 ? 1 : -1);
        }
    }
    return determinant;
}
int main() {
    int mat[N][N];
    printf("Enter the mat:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
    printf("The mat you entered is:\n");
    printmat(mat);
    int determinant = det1(mat);
    printf("The determinant of the mat is: %d\n", determinant);
    return 0;
}




//2nd method
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int det(int A[100][100], int n){
    int Minor[100][100];
    int i,j,k,c1,c2;
    int determinant;
    int c[100];
    int O=1;

    if(n == 2){
        determinant = 0;
        determinant = A[0][0]*A[1][1]-A[0][1]*A[1][0];
        return determinant;
    }
    else{
        for(i = 0 ; i < n ; i++){
            c1 = 0, c2 = 0;
            for(j = 0 ; j < n ; j++){
                for(k = 0 ; k < n ; k++){
                    if(j != 0 && k != i){
                        Minor[c1][c2] = A[j][k];
                        c2++;
                        if(c2>n-2){
                            c1++;
                            c2=0;
                        }
                    }
                }
            }
            determinant = determinant + O*(A[0][i]*det(Minor,n-1));
            O=-1*O;
        }
    }
    return determinant;
}
main(){
    int A[100][100];
    int i,j,k,n,res;
    printf("Enter the order of the mat: \n");
    scanf("%d",&n);
    printf("\nEnter the elements of the mat one by one: \n");
    for(i = 0 ; i < n ; i++){
        for(j = 0 ; j < n ; j++){
            scanf("%d",&A[i][j]);
        }
    }
    for(i = 0 ; i < n ; i++){
        for(j = 0 ; j < n ; j++){
            printf("%5d",A[i][j]);
        }
        printf("\n");
    }
    res = det(A,n);
    printf("%d",res);
}
