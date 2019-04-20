/*************************************************************************
    > File Name: sudoku.h
    > Author: Yiwen Xue
    > Mail: 15225434259xue@gmail.com 
    > Created Time: Sat 20 Apr 2019 05:29:28 PM IDT
*************************************************************************/

#include <stdio.h>
#include <stdbool.h>

void print_puzzle(int *puzzle);

bool unSeted(int grid[9][9],int *row, int *col);

bool solveSudoku(int grid[9][9],int level);

bool isSafe(int grid[9][9],int row,int col,int num);
