#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "lab3.h"

extern int** sudoku_board;
int* worker_validation;

int** read_board_from_file(char* filename){
    FILE *fp = NULL;
    int** board = NULL;

    fp = fopen(filename, "r");

    int** sudoku_board = (int**)malloc(sizeof(int*)*ROW_SIZE);
    for(int row = 0; row < ROW_SIZE; row++){
        sudoku_board[row] = (int*)malloc(sizeof(int)*COL_SIZE);
    }

    for (int i = 0; i<ROW_SIZE*COL_SIZE; i++){
        fscanf(fp, "%d,", &sudoku_board[i/9][i%9]);
    }

    /* traversing the rows
    for (int i = 0; i < ROW_SIZE; i++){
        for (int j = 0; j < COL_SIZE; j++){
            printf("%d", sudoku_board[i][j]);
        }
    } */

    /* traversing the columns
    for (int i = 0; i < ROW_SIZE; i++){
        for (int j = 0; j < COL_SIZE; j++){
            printf("%d", sudoku_board[j][i]);
        }
    } */

    return sudoku_board;
}

void *check_Column(void* parameters){
    int numbers[COL_SIZE] = {0};

    param_struct* sudoku = (param_struct*) parameters;

    for (int row = sudoku->starting_row; row < sudoku->ending_row; row++){
        for (int column = 0; column < ROW_SIZE; column++){
            int current_Number = sudoku_board[row][column];
            if (numbers[current_Number - 1] == 1){
                return 0;
            } else {
                numbers[current_Number - 1] = 1;
            }
        }
    }

    return 1;
}

void *check_Row(void* parameters){
    int numbers[COL_SIZE] = {0};

    param_struct* sudoku = (param_struct*) parameters;

    for (int row = sudoku->starting_row; row < sudoku->ending_row; row++){
        for (int column = 0; column < ROW_SIZE; column++){
            int current_Number = sudoku_board[column][row];
            if (numbers[current_Number - 1] == 1){
                return 0;
            } else {
                numbers[current_Number - 1] = 1;
            }
        }
    }
    return 1;
}


int is_board_valid(){
    pthread_t* tid;  /* the thread identifiers */
    pthread_attr_t attr;
    param_struct* parameter;
    
    // replace this comment with your code
    


}
