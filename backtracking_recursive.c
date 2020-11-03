#include <stdio.h>
#include <stdlib.h>

unsigned int ROWS = 0;
unsigned int COLS = 0;

//Reference: 
//https://stackoverflow.com/questions/39395316/how-can-i-display-the-chess-board-content-as-strings-in-c-language-and-store-the
#define QUEEN_SQUARE_CHAR   "♜" 
#define BLANK_SQUARE_CHAR   "…"
#define QUEEN_SQUARE_VAL    255

static unsigned int **chess_board = NULL;
unsigned int num_of_sols = 0;

void clear_board() {
    num_of_sols = 0;
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++) {
            chess_board[i][j] = 0;
        }
    }
    return;
}

int add_queen(unsigned int row, unsigned int col) {
    if (row >= ROWS || col >= COLS) {
        printf("row %d, col %d is beyond the chess board with rows %d cols %d\n", 
               row, col, ROWS, COLS);
        return -1;
    }
    if(chess_board[row][col] >= QUEEN_SQUARE_VAL) {
        printf("Queen already present at row %d, col %d\n", row, col);
        return -2;
    }
    //save the current queen square value
    unsigned int curr_val = chess_board[row][col];

    //update cols reachability
    for(unsigned int i = 0; i < COLS; i++) {
        chess_board[row][i]++;
    }
    //update rows reachability
    for(unsigned int j = 0; j < ROWS; j++) {
        chess_board[j][col]++;
    }
    //update left upper diagonal
    int curr_row = row;
    int curr_col = col;
    while(++curr_row < ROWS && --curr_col >= 0) {
        chess_board[curr_row][curr_col]++;
    }
    //update right lower diagonal
    curr_row = row;
    curr_col = col;
    while(--curr_row >= 0 && ++curr_col < COLS) {
        chess_board[curr_row][curr_col]++;
    }
    //update left lower diagonal
    curr_row = row;
    curr_col = col;
    while(--curr_row >= 0 && --curr_col >= 0) {
        chess_board[curr_row][curr_col]++;
    }
    //update right upper diagonal
    curr_row = row;
    curr_col = col;
    while(++curr_row < ROWS && ++curr_col < COLS) {
        chess_board[curr_row][curr_col]++;
    }
    //put queen at row,col
    chess_board[row][col] = curr_val + QUEEN_SQUARE_VAL;
    
    return 0;
}

int remove_queen(unsigned int row, unsigned int col) {
    if (row >= ROWS || col >= COLS) {
        printf("row %d, col %d is beyond the chess board with rows %d cols %d\n", 
               row, col, ROWS, COLS);
        return -1;
    }
    if(chess_board[row][col] < QUEEN_SQUARE_VAL) {
        printf("Queen not present at row %d, col %d\n", row, col);
        return -2;
    }
    //save the current queen square value
    unsigned int curr_val = chess_board[row][col];

    //update cols reachability
    for(unsigned int i = 0; i < COLS; i++) {
        chess_board[row][i]--;
    }
    //update rows reachability
    for(unsigned int j = 0; j < ROWS; j++) {
        chess_board[j][col]--;
    }
    //update left upper diagonal
    int curr_row = row;
    int curr_col = col;
    while(++curr_row < ROWS && --curr_col >= 0) {
        chess_board[curr_row][curr_col]--;
    }
    //update right lower diagonal
    curr_row = row;
    curr_col = col;
    while(--curr_row >= 0 && ++curr_col < COLS) {
        chess_board[curr_row][curr_col]--;
    }
    //update left lower diagonal
    curr_row = row;
    curr_col = col;
    while(--curr_row >= 0 && --curr_col >= 0) {
        chess_board[curr_row][curr_col]--;
    }
    //update right upper diagonal
    curr_row = row;
    curr_col = col;
    while(++curr_row < ROWS && ++curr_col < COLS) {
        chess_board[curr_row][curr_col]--;
    }
    //put queen at row,col
    chess_board[row][col] = curr_val - QUEEN_SQUARE_VAL;
    

    return 0;
}

void print_char_board() {
    printf("------------------------\n");
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if(chess_board[i][j] >= QUEEN_SQUARE_VAL) {
                printf(" %s", QUEEN_SQUARE_CHAR);
            } else {
                printf(" %s", BLANK_SQUARE_CHAR);
            }
        }
        printf("\n");
    }
    printf("------------------------\n");
}

void print_val_board() {
    printf("------------------------\n");
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if(chess_board[i][j] >= QUEEN_SQUARE_VAL) {
                printf(" %c", 'Q');
            } else {
                printf(" %d", chess_board[i][j]);
            }
        }
        printf("\n");
    }
    printf("------------------------\n");
}

int place_n_queens(unsigned int col) {
    
    if(col >= COLS) {
        printf("%d col is beyond the board of cols %d\n", col, COLS);
        return -1;
    }
    
    //check for the queen present in this col
    int i = 0;
    int found_queen = 0;
    int success = 0;
    while(i < ROWS) { 
        success = 0;
    for(i = 0; i < ROWS; i++) {
        if(chess_board[i][col] == 0) {
            int res = add_queen(i, col);
            if(res == 0) {
                success = 1;
                if((col + 1) == COLS) {
                    num_of_sols++;
                    print_char_board();
                    //print_val_board();
                    res = remove_queen(i, col);
                    if(res != 0) {
                        return -1;
                    }
                    success = 0;
                    continue;
                }
                break;
            }
            else {
                return -1;
            }
        } else if(chess_board[i][col] >= QUEEN_SQUARE_VAL) {
            //remove current queen
            int res = remove_queen(i, col);
            if(res != 0) {
                return -1;
            }
            found_queen = 1;
            continue;
        } else {
            continue;
        }
    }
    if(i == ROWS && col == 0) {
        //no more solutions exit
        return 0;
    }
   
    if(success == 1) {
        if(i == ROWS) {
            return 0;
        } else {
            //queen placed in this col, move to the next col
            i = 0;
            if((col + 1) < COLS) { 
                place_n_queens(col + 1);
            }
        }
    } else if (success == 0) {
        //no queen could be placed in the col
        if(col == 0) {
            //no more solutions exit
            return 0;
        } else {
            //backtrack to previous col and move the queen to a new square
        }
    }
    }

    return 0;
}

int main(int argc, char **argv) {

    printf("Enter the number of rows in the board: ");
    scanf("%d", &ROWS); 
    COLS = ROWS;

    chess_board = (unsigned int **)malloc(sizeof(unsigned int *)*ROWS);

    for(int i = 0; i < ROWS; i++) {
        chess_board[i] = (unsigned int *)malloc(sizeof(unsigned int)*COLS);
    }
    
    clear_board();
    //print_char_board();
    //print_val_board();
    printf("Recursive Solution\n");
    place_n_queens(0);
    printf("Number of solutions is: %d\n", num_of_sols); 
    //print_char_board();
    //print_val_board();
    
    return 0;

}
