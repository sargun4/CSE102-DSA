#include <stdio.h>
int grid[8][8]={0};
int solve(int x,int y,int n){

}
void print(void){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            printf("%d ",grid[i][j]);
        }printf("\n");
    }printf("\n\n\n");
}
int main(){
    // printf();
    print();
    solve(0,0,0);
    
    return 0;
}
