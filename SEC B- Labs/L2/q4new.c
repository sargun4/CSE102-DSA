#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 10000
// int m, n; // size of the building
// int time_elapsed = 0; // time
// int building[MAX_SIZE][max];

bool sare_ghar_jal_gaye(int building[], int m, int n)
{
    // return (row >= 0 && row < m && col >= 0 && col < n && building[row][col] == 1);
    bool out = true;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (building[i][j] == 0){
                out = false;
                break;
            }
        }
    }
    return out;
}

int kitne_sec_me_jale(int building, int m, int n)
{
    int time_elapsed = 0;
    while (!sare_ghar_jal_gaye(building, m, n)) //jab tak sare ghar nhi jale
    {
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){

                int arr[3]={-1,0,1};
                for(int a=0;a<3;a++){
                    for(int b=0;b<3;b++){
                        if(i+arr[a]<m && i+arr[a]>0 && j+arr[b]>0 &&j+arr[b]<n){
                            building[i+a][j+b]=1;
                        }
                    }
                }
            }
        }
        time_elapsed++;
    }

    return time_elapsed;
}
int main(){
    scanf()
    return 0;
}