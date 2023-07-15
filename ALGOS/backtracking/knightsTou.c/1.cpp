#include <bits/stdc++.h>
using namespace std;

void display(vector<vector<int>> &chess){
    for(int i=0;i<chess.size();i++){
        for(int j=0;j<chess.size();j++){
            cout<<chess[i][j]<<" ";
        }cout<<endl;
    }cout<<endl;
}
void KT(vector<vector<int>> &chess,int n,int r,int c,int upcomingmoves){
    // invalid calls
    if(r<0 || c<0 || r>=n || c>=n || chess[r][c]!=0){
        return;
    }
    if(upcomingmoves==n*n){
        chess[r][c]=upcomingmoves;
        display(chess);
        chess[r][c]=0;
        return;
    }
    chess[r][c]=upcomingmoves;
    int row []={1,-1,-2,-2,1,-1,2,2};
    int col []={2,2,1,-1,-2,-2,1,-1};
    for(int i=0;i<n;i++){
        KT(chess,n,r+row[i],c+row[i],upcomingmoves+1);
}
    chess[r][c]=0;//backtracking
}
int main(){
    int n,r,c;
    cin>>n>>r>>c;
    vector<vector<int>> chess(n,vector<int> (n,0));
    KT(chess,n,r,c,1);
    return 0;
}