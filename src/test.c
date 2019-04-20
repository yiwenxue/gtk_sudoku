/*************************************************************************
    > File Name: test.c
    > Author: Yiwen Xue
    > Mail: 15225434259xue@gmail.com 
    > Created Time: Sat 20 Apr 2019 04:14:59 PM IDT
*************************************************************************/

#include<stdio.h>

void print_puzzle(int *puzzle){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            printf("%d ",*(puzzle+j+i*9));
            if( (j+1)%3==0 && j!=8 )
                printf("| ");
            else if(j==8)
                printf("\n");
        }
        if((i+1)%3 == 0 && i!= 8)
            printf("---------------------\n");
    }
}

void set_grid(int grid[9][9]){
    for(int i=0;i<9;i++){
        int j=9;
        while(j--){
            grid[i][j] = 0;
        }
    }
}

int main(){
    int grid[9][9];
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            grid[i][j] = 1;
        }
    }
    print_puzzle((int*)grid);
    set_grid(grid);
    print_puzzle((int*)grid);
    return 0;
}
