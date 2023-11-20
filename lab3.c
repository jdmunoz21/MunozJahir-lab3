#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "lab3.h"

extern int** sudoku_board;
int* worker_validation;
int is_valid_row;
int is_valid_column;

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

    return sudoku_board;
}

void *check_Row(void* parameters){
    param_struct* sudoku = (param_struct*) parameters;

    int numbers[COL_SIZE] = {0};

    int row = sudoku->starting_row;

    for (int i = 0; i < 9; i++){
        numbers[sudoku_board[row][i] - 1] += 1;
    }

    for (int i = 0; i < 9; i++){
        if (numbers[i] != 1){
            is_valid_row = 0;
            return NULL;
        }
    }

    is_valid_row = 1;

    return NULL;
}

void *check_Column(void* parameters){
    param_struct* sudoku = (param_struct*) parameters;

    int numbers[COL_SIZE] = {0};

    int col = sudoku->starting_col;

    for (int i = 0; i < 9; i++){
        numbers[sudoku_board[col][i] - 1] += 1;
    }

    for (int i = 0; i < 9; i++){
        if (numbers[i] != 1){
            is_valid_column = 0;
            return NULL;
        }
    }

    is_valid_column = 1;

    return NULL;
}

int is_board_valid(){
    pthread_t tid;  /* the thread identifiers */
    pthread_attr_t attr;
    param_struct* parameters = (param_struct*)malloc(sizeof(param_struct)*18);
    
    // replace this comment with your code

    for (int i = 0; i < 9; i++){
        parameters[i].starting_row = i;
        parameters[i].ending_col = i;

        pthread_create(&tid, NULL, check_Row, &(parameters[i]));
        pthread_join(tid, NULL);
        pthread_create(&tid, NULL, check_Column, &(parameters[i]));
        pthread_join(tid, NULL);

        if (is_valid_row == 0 || is_valid_column == 0){
            return 0;
        }
    }

    return 1;
}
