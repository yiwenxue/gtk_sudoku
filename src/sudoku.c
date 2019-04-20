/*************************************************************************
    > File Name: sudoku.c
    > Author: Yiwen Xue
    > Mail: 15225434259xue@gmail.com 
    > Created Time: Sat 20 Apr 2019 05:28:59 PM IDT
*************************************************************************/

#include "sudoku.h"

bool unSeted(int grid[9][9],int *row, int *col){
    for(*row =0;*row<9;(*row)++){
        for(*col=0;*col<9;(*col)++){
            if(grid[*row][*col] == 0)
                return true;
        }
    }
    return false;
}

bool solveSudoku(int grid[9][9],int level){
    int row, col; 
    if(!unSeted(grid,&row,&col))
        return true;
    for(int i=1;i<=9;i++){
        if(isSafe(grid,row,col,i)){
            grid[row][col] = i;
            //printf("level = %d\n",level);
            //print_puzzle((int*)grid);
            if(solveSudoku(grid,level+1))
                return true;
            grid[row][col] = 0;
        } 
    }
    return false;
}

bool isSafe(int grid[9][9],int row,int col,int num){
    for(int i=0;i<9;i++){
        if(num == grid[row][i]){
            return false;
        }
        if(num == grid[i][col]){
            return false;
        }
    }
    int y = row/3;
    y = y*3;
    int x = col/3;
    x = x*3;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(num == grid[y+i][x+j]){
                return false;
            }
        }
    }
    return true;
}

void print_puzzle(int *puzzle){
    for(int i=0;i<9;i++){
        printf(" ");
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

