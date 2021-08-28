#include <stdio.h>
#include <stdbool.h>
#include <math.h>

void drawBoard();
int checkValid(int pos);
void markBoard(int pos, bool playerOne);
int checkForWinByRow();
int checkForWinByCol();
int checkForWinByDia();
bool checkForFullBoard();
int checkForWin();

/**
 * Numbers 1 to 9 represent empty grid spaces.
 * Character o represents grid space played by Player 1.
 * Character x represents grid space played by Player 2.
 */
char board[3][3] = { { '1', '2', '3' }, { '4', '5', '6' }, { '7', '8', '9' } };

void drawBoard()
{
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[0][0], board[0][1], board[0][2]);
    printf("-----|-----|-----\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[1][0], board[1][1], board[1][2]);
    printf("-----|-----|-----\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[2][0], board[2][1], board[2][2]);
    printf("-----|-----|-----\n");
}

int checkInvalid(int pos)
{
    int row, col;
    row = floor( pos / 3 );
    col = pos % 3 - 1;

    if (board[row][col] == 'o' || board[row][col] == 'x') {
        return 1;
    }
    return 0;
}

void markBoard(int pos, bool playerOne)
{
    int row, col;
    row = floor(pos / 3);
    col = pos % 3 - 1;

    if (playerOne == 1) {
        board[row][col] = 'o';
    } else {
        board[row][col] = 'x';
    }
}

int checkForWinByRow()
{
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] == board[i][2]) {
            if (board[i][0] == 'o') {
                return 1;
            } else {
                return 2;
            }
        } else {
            return 0;
        }
    }
}

int checkForWinByCol()
{
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] == board[2][i]) {
            if (board[0][i] == 'o') {
                return 1;
            } else {
                return 2;
            }
        } else {
            return 0;
        }
    }
}

int checkForWinByDia()
{
    if (board[0][0] == board[1][1] == board[2][2]
        || board[0][2] == board[1][1] == board[2][0]) {
        if (board[1][1] == 'o') {
            return 1;
        } else {
            return 2;
        }
    } else {
        return 0;
    }
}

bool checkForFullBoard()
{
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row][col] != 'o' && board[row][col] != 'x') {
                return 0;
            }
        }
    }
    return 1;
}

int checkForWin()
{
    int game;
    int win = checkForWinByRow() + checkForWinByCol() + checkForWinByDia();
    bool fullBoard = checkForFullBoard();
    if (win == 1 || win == 2) {
        game = win;
    } else if (win == 0 && fullBoard == 1) {
        game = 0;
    } else if (win == 0 && fullBoard == 0) {
        game = 3;
    }
    return game;
}

int main()
{
    printf("This is a 2-player tic-tac-toe game.\n");
    printf("Players take turns to input the position to put a circle \n");
    printf("(player 1) and a cross (player 2) on the board.\n");
    printf("Starting with player 1.\n\n");

    int playerInput;
    bool invalidInput;
    int gameStatus;

    for (bool player = 1;; player = !player) {
        drawBoard();
        scanf("%i", &playerInput);
        invalidInput = checkInvalid(playerInput);
        while (invalidInput == 1) {
            printf("Invalid input. Try again: ");
            scanf("%i", &playerInput);
            invalidInput = checkInvalid(playerInput);
        }
        markBoard(playerInput, player);
        gameStatus = checkForWin();
        if (gameStatus != 3) {
            if (gameStatus == 0) {
                printf("The game is a draw.\n");
            } else if (gameStatus == 1) {
                printf("Player 1 wins.\n");
            } else if (gameStatus == 2) {
                printf("Player 2 wins.\n");
            }
            break;
        }
    }

    return 0;
}
