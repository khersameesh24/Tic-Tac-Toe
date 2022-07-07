#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

/*
 *@brief Tic-Tac-Toe
 */
typedef struct Game
{
    // game board
    char board[3][3];

    // assign player/comp symbols
    char PLAYER;
    char COMPUTER;

} Game;

void printBanner()
{
    printf("\n\n\t\t+-----------+");
    printf("\n\t\t|TIC-TAC-TOE|\t\n");
    printf("\t\t+-----------+");
}

/*
*@brief Reset the game-board to launch the game.
        Initializes each position with a `space`
*/
void resetBoard(Game *game)
{
    int i, j;
    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            game->board[i][j] = ' ';
        }
    }
}

/*
 *@brief Print the game-board to show the moves
 */
void printBoard(Game game)
{

    printf("\n\n\t\t----+---+----");
    printf("\n\t\t| %c | %c | %c |", game.board[0][0], game.board[0][1], game.board[0][2]);
    printf("\n\t\t----+---+----\n");
    printf("\t\t| %c | %c | %c |", game.board[1][0], game.board[1][1], game.board[1][2]);
    printf("\n\t\t----+---+----\n");
    printf("\t\t| %c | %c | %c |", game.board[2][0], game.board[2][1], game.board[2][2]);
    printf("\n\t\t----+---+----\n");
    printf("\n");
}

/*
 *@brief Check for free spaces on the game-board
 */
int checkFreeSpaces(Game *game)
{
    int freeSpaces = 9;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (game->board[i][j] != ' ')
            {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}

/*
 *@brief Get the location where player wants to
        make a move. rows #(1-3) columns #(1-3)
*/
void playerMove(Game *game)
{
    int x, y;
    do
    {
        printf("\n\t\tEnter row #(1-3): ");
        scanf("%d", &x);
        x--;
        printf("\n\t\tEnter column #(1-3): ");
        scanf("%d", &y);
        y--;

        if (game->board[x][y] != ' ')
        {
            printf("\t\tInvalid Move!");
        }
        else
        {
            game->board[x][y] = game->PLAYER;
            break;
        }
    } while (game->board[x][y] != ' ');
}

/*
 *@brief Show if there is a winner
 */
void printWinner(Game *game, const char winner)
{
    if (winner == game->PLAYER)
    {
        printf("\n\n\t\tYOU WIN!\n");
    }
    else if (winner == game->COMPUTER)
    {
        printf("\n\n\t\tYOU LOSE!\n");
    }
    else
    {
        printf("\n\n\t\tIT'S A TIE!\n");
    }
}

/*
*@brief Get the location of computer move
        Move if free space is available.
*/
void computerMove(Game *game, const char winner)
{
    // create a seed based on the current time
    srand(time(0));
    int x, y;
    if (checkFreeSpaces(game) > 0)
    {
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (game->board[x][y] != ' ');

        game->board[x][y] = game->COMPUTER;
    }
    else
    {
        printWinner(game, winner);
    }
}

/*
 *brief Check if there is a winner.
 */
char checkWinner(Game game)
{
    // check each row
    for (int i = 0; i < 3; ++i)
    {
        if (game.board[i][0] == game.board[i][1] && game.board[i][0] == game.board[i][2])
        {
            return game.board[i][0];
        }
    }
    // check each column
    for (int i = 0; i < 3; ++i)
    {
        if (game.board[0][i] == game.board[1][i] && game.board[0][i] == game.board[2][i])
        {
            return game.board[0][i];
        }
    }
    // check diagonals
    if (game.board[0][0] == game.board[1][1] && game.board[0][0] == game.board[2][2])
    {
        return game.board[1][1];
    }

    if (game.board[0][2] == game.board[1][1] && game.board[0][2] == game.board[2][0])
    {
        return game.board[1][1];
    }
    return ' ';
}

int main()
{
    Game game;
    char symbol;
    printBanner();
    printf("\n\tEnter a symbol to use (X/O):");
    scanf("%c", &symbol);
    if (symbol == 'X')
    {
        game.PLAYER = 'X';
        game.COMPUTER = 'O';
    }
    else if (symbol == 'O')
    {
        game.PLAYER = 'O';
        game.COMPUTER = 'X';
    }
    else
    {
        printf("\n\tInvalid Symbol! Using Defaults!");
        game.PLAYER = 'X';
        game.COMPUTER = 'O';
    }
    resetBoard(&game);
    char response = ' ';

    do
    {
        char winner = ' ';
        resetBoard(&game);
        printBanner();
        while (winner == ' ' && checkFreeSpaces(&game) != 0)
        {
            // print the board
            printBoard(game);

            // ask the player to make a move
            playerMove(&game);
            winner = checkWinner(game);
            if (winner != ' ' || checkFreeSpaces(&game) == 0)
            {
                // break if the player is the winner
                break;
            }

            // ask the comp to make a move
            computerMove(&game, winner);
            winner = checkWinner(game);
            if (winner != ' ' || checkFreeSpaces(&game) == 0)
            {
                // break if comp is the winner
                break;
            }
        }
        printBoard(game);
        printWinner(&game, winner);
        printf("\n\t\tWould you like to play again? (Y/N)\n\t\tPress Enter to exit.");
        getchar();
        scanf("%c", &response);
        response = toupper(response);
    } while (response == 'Y');
    printf("\n\t\tBYE! Thanks for playing!");

    return 0;
}
