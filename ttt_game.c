
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
char grid[50][50]; //Initial Global char grid set to 50 each array representation rows and columns
const char PLAYER1 = 'X'; // Setting two players and each set to either 'X' or 'O'
const char PLAYER2 = 'O';

// All the fucntions used in this program
int resetgrid(int size); //To reset the grid each round finishes, indicating the size of grid based on what user entered.
int printgrid(int size); // To print the grid, taking size from user. Indicate and warn the user if size if over the Maximum. Print n X n grid with '_'.
int checkFreeSpaces(int size); //Eliminate and count spaces '_' and for each '_' is taken decrement spaces.
void playerMove(char player); // Let user enter x,y axises of where they wanted to. If position of grid is taken, then it warns user for invalid move.
int checkVerticalWin(char player, int size); // Function that checks vertical or y-axis, indicates and counts moves by player either 'X' or 'O.
int checkHorizontalWin(char player, int size); // Function that check horizontal or x-axis, indicates and counts moves by player either 'X' or 'O.
int checkDiagonalWin(char player, int size); // Function that check diagonal, indicates and counts moves by player either 'X' or 'O.
char checkWinner(char player, int size); // Previous three functions checks winning conditions, check which condition fits for winning, and return to which player wins.
void printWinner(char winner); // Printing function in terminal, showing shows who wins.

int main()
{
    int size; 
    char winner;
    char response = '_';
   printf("Welcome !\n");
   
   printf("Enter size of your grid: "); //Find size of your ideal grid and store in int size;
   scanf("%d", &size); 
   
   do
   {
      winner = '_'; // Initial winner and respone to '_' or spaces.
      response = '_';
      resetgrid(size); //Use initialgrid function, find what ideal size of grid based on size.

      while(winner == '_' && checkFreeSpaces(size) != 0) //While winner is still same as what it initialise at first. 
      {                                                  //Check for spaces not equals to 0 (indicate whether there are spaces in the grid).
         printgrid(size); //printing the grid, everytime during each attempt by player

         playerMove(PLAYER1);
         winner = checkWinner(PLAYER1, size); //Set winner to the player if it fits one of winning conditions
         if(winner != '_' || checkFreeSpaces(size) == 0)
         {
             printgrid(size);
            break;  // break the while loop when a winner came out
         }

         playerMove(PLAYER2);
         winner = checkWinner(PLAYER2, size);
         if(winner != '_' || checkFreeSpaces(size) == 0)
         {
             printgrid(size);
            break;
         }
      }
      printWinner(winner); 

      printf("\nWould you like to play again? (Y/N): ");
      scanf("\n%c", &response);
      response = toupper(response);
   } while (response == 'Y'); //Loop repeat if user enter 'Y' to play again

   printf("Thanks for playing!");

   return 0;
}

int resetgrid(int size) 
{
   for (int row = 0; row < size; row++)
   {
       for (int col = 0; col < size; col++)
       {
           grid[row][col]= '_'; //count rows and columns based on size, setting them to '_'.
       }
   }
}

int printgrid(int size)
{
    printf("\n");
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {   
            putchar (' '); //leave space after each column
            if (grid[row][col])
            {
                putchar (grid[row][col]); //set both row and column to grid.
            }
            else
            {
                putchar ('_'); //Then print them with '_'
            }
        }
        printf("\n"); //leave a space after each row
    }
}

int checkFreeSpaces(int size)
{
   int freeSpaces = (size * size); //Find actual size. 

   for(int i = 0; i < size; i++)
   {
      for(int j = 0; j < size; j++)
      {
         if(grid[i][j] != '_')
         {
            freeSpaces--; //Decrement after each space is taken. 
         }
      }
   }
   return freeSpaces;
}

void playerMove(const char player)
{
   int x;
   int y;

   do
   {
     printf("Player%c: Enter row and column: ", player == PLAYER1 ? '1' : '2'); //setting player first PLAYER1, set to another player (PLAYER2), when the loop break.
     scanf("%d %d", &x, &y);
      x--;
      y--; //record and decrement when x and y is entered.      

      if(grid[x][y] != '_') //if x and y is taken, warn for invalid move
      {
         printf("Invalid move!\n");
      }
      else
      {
         grid[x][y] = player; //set that particular x and y to 'X' or 'O'.
         break;
      }
   } while (grid[x][y] != '_');
   
}

int checkVerticalWin(char player, int size) {
    for(int row = 0; row < size; row++)
    {
        int count = 0;
        for (int col = 0; col < size; col++) {
            if (grid[row][col] == player) count++; //Add counts for either one of symbol, for every row after each column
        }
        if (count == size) return checkVerticalWin;
    }
    return 0;
}

int checkHorizontalWin(char player, int size) {

    for(int col = 0; col < size; col++) {
        int count = 0;
        for (int row = 0; row < size; row++) {
            if (grid[row][col] == player) count++; //Add counts, for every column after each row
        }
        if (count == size) return checkHorizontalWin;
    }
    return 0;
}

int checkDiagonalWin(char player, int size) {
    int leftCount = 0;
    // check left diagonal (top left to bottom right)
    for(int row = 0, col = 0; row < size; row++, col++) {
        if (grid[row][col] == player) leftCount++; //Add counts to player, increment row and column after each row. 
    }
    int leftDiagonalSet = leftCount == size; //Ensure counts = size to match digonal winning condition. 

    int rightCount = 0;
    // check right diagonal (bottom left to top right)
    for(int row = size - 1, col = 0; row >= 0; row--, col++) {
        if (grid[row][col] == player) rightCount++; //Add counts, starting from last row, decrement (moving up)row and increment(moving right) column. 
    }
    int rightDiagonalSet = rightCount == size; //Ensure counts = size to match digonal winning condition. 
    return leftDiagonalSet || rightDiagonalSet; 
}

char checkWinner(char player, int size) {
    if (checkHorizontalWin(player, size) || checkVerticalWin(player, size) || checkDiagonalWin(player, size)) {
        return player; //Return to the player who match one of winning condition
    } else {
        return '_'; //Return to '_' if nothing is match. This set for tie. 
    }
}

void printWinner(char winner)
{
   if(winner == PLAYER1) //If winner matches to one of player then declare who is winner. 
   {
      printf("Player1 Wins");
   }
   else if(winner == PLAYER2)
   {
      printf("Player2 Wins");
   }
   else{
      printf("It's a Draw!"); //if nothing or '_' return in checkWinner function. Then this will be a tie. 
   }
}