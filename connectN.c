/* 
Bianca Dimaano (301550989) & Brandon Quon (301545786)
July 9, 2023
Connect N game. Red vs. black, whoever is able to connect N gamepieces in a row first (horizontally, vertically, or diagonally) wins!
*/

#include <stdio.h>
#include <stdlib.h>

int InitializeBoard(int** connectNBoard, int numRowsInBoard);
int MakeMove(int** connectNBoard, int numRowsInBoard, int playerID, int columnChosen);
int DisplayBoard(int** connectNBoard, int numRowsInBoard);
int CheckWinner(int** connectNBoard, int numRowsInBoard, int numConnect, int columnChosen, int playerID);

int main(void) {

  int numRows = 0;
  int numToConnect = 0;
  int c; // int c for while((c = getchar()) != '\n' && c != EOF);, alternative to fflush()
  int move = 1; 
  int chosenColumn = 0;
  int illegalMoves = 0;
  int lastMoveIllegal = 0;
  const int MINSIZE = 8;
  const int MAXSIZE = 25;
  const int MINCONNECTNUM = 4;

  /*Loop that prompts the user to enter the number of rows that the board will have.
    - If a non-integer is entered, an error message will print and the user will be reprompted.
    - If the number that is entered is too big or too small, the user will be reprompted. */
  while(1)
  {
    printf("Enter the number of squares along each edge of board\n");
    if(!(scanf("%d", &numRows)))
    {
      printf("ERROR: The value provided was not an integer\n");
      while((c = getchar()) != '\n' && c != EOF);
      continue;
    }
    if(numRows > MAXSIZE)
    {
      printf("ERROR: Board size too large (>%d)\n", MAXSIZE);
      while((c = getchar()) != '\n' && c != EOF);
      continue;
    }
    else if(numRows < MINSIZE)
    {
      printf("ERROR: Board size is too small (<%d)\n", MINSIZE);
      while((c = getchar()) != '\n' && c != EOF);
      continue;
    }
    break;
  }
    
  /*Loop that prompts the user to enter the number of pieces that must form a line to win.
    - If a non-integer is entered, an error message will print and the user will be reprompted.
    - If the number that is entered is too big or too small, the user will be reprompted. */
  while(1)
  {
    printf("Enter the number of pieces that must form a line to win\n");
    if(!(scanf("%d", &numToConnect)))
    {
      printf("ERROR: The value provided was not an integer\n");
      while((c = getchar()) != '\n' && c != EOF);
      continue;
    }
    if(numToConnect > numRows - MINCONNECTNUM)
    {
      printf("ERROR: Number to connect is too large (>%d)\n", numRows-MINCONNECTNUM);
      while((c = getchar()) != '\n' && c != EOF);
      continue;
    }
    else if(numToConnect < MINCONNECTNUM)
    {
      printf("ERROR: Number to connect is too small (<%d)\n", MINCONNECTNUM);
      while((c = getchar()) != '\n' && c != EOF);
      continue;
    }
    break;
  }

  // Dynamically allocating int array myConnectNBoard with dimensions numRows by numRows.
  int **myConnectNBoard = (int**)malloc(numRows*sizeof(int*));
  myConnectNBoard[0] = (int*)malloc(numRows*numRows*sizeof(int));
  for(int i = 1; i < numRows; i++)
  {
    myConnectNBoard[i] = myConnectNBoard[0] + i*numRows;
  }

  // Initializing the game board using the InitializeBoard function.
  if(!(InitializeBoard(myConnectNBoard, numRows)))
  {
    printf("ERROR: Could not initialize the game board");
    for(int i = 0; i < numRows; i++)
    {
      free(myConnectNBoard[i]);
    }
    free(myConnectNBoard);
    return 1;
  }

  /*Game loop*/
  while(1)
  {
    if(!(lastMoveIllegal))
    {
      printf("\n\n");
      if(!(DisplayBoard(myConnectNBoard, numRows)))
      {
        printf("ERROR: Could not display the game board");
        continue;
      }
    }
    
    if(move == 1 && !(lastMoveIllegal))
    {
      printf("Red moves");
    }
    else if(move == 2 && !(lastMoveIllegal))
    {
      printf("Black moves");
    }

    if(illegalMoves == 3)
    {
      printf("\nTOO MANY ILLEGAL MOVES\n");
      if(move == 1)
      {
        printf("Red has forfeited a turn");
        illegalMoves = 0;
        lastMoveIllegal = 0;
        move++;
        continue;
      }
      else if(move == 2)
      {
        printf("Black has forfeited a turn");
        illegalMoves = 0;
        lastMoveIllegal = 0;
        move--;
        continue;
      }
    }
    
    printf("\nEnter the column number where you want to put your piece\n");
    if(!(scanf("%d", &chosenColumn)))
    {
      printf("ERROR: The value provided was not a number");
      illegalMoves++;
      lastMoveIllegal = 1;
      while((c = getchar()) != '\n' && c != EOF);
      continue;
    }
    else
    {
      lastMoveIllegal = 0;
    }
    if(chosenColumn > MAXSIZE || chosenColumn < 0)
    {
      printf("ERROR: Column %d is not on the board: try again\nERROR: Column number should be >= 0 and < %d", chosenColumn, numRows);
      illegalMoves++;
      lastMoveIllegal = 1;
      while((c = getchar()) != '\n' && c != EOF);
      continue;
    }
    else
    {
      lastMoveIllegal = 0;
    }
    if(myConnectNBoard[0][chosenColumn] != 0)
    {
      printf("ERROR: Column %d is already completely full try again", chosenColumn);
      illegalMoves++;
      lastMoveIllegal = 1;
      while((c = getchar()) != '\n' && c != EOF);
      continue;
    } 
    else
    {
      lastMoveIllegal = 0;
      while((c = getchar()) != '\n' && c != EOF);
    }
    if(MakeMove(myConnectNBoard, numRows, move, chosenColumn))
    {
      if((CheckWinner(myConnectNBoard, numRows, numToConnect, chosenColumn, move)))
      {
        if(move == 1)
        {
          printf("Red has won\n");
        }
        if(move == 2)
        {
          printf("Black has won\n");
        }
        DisplayBoard(myConnectNBoard, numRows);

        // Freeing the memory allocated to myConnectNBoard
        for(int i = 0; i < numRows; i++)
        {
          free(myConnectNBoard[i]);
        }
        free(myConnectNBoard);

        return 2;
      }
      else
      {
        if(move == 1)
        {
          move++; 
          continue;
        }
        else
        {
          move--;
          continue;
        }
      }
    }
    else
    {
      illegalMoves++;
      while((c = getchar()) != '\n' && c != EOF);
      continue;
    }
  }

  // Freeing the memory allocated to myConnectNBoard
  for(int i = 0; i < numRows; i++)
  {
    free(myConnectNBoard[i]);
  }
  free(myConnectNBoard);

  return 0;
}

/*Function that initializes the board with zeroes.*/
int InitializeBoard(int** connectNBoard, int numRowsInBoard)
{
  // If the number of rows is illegal, return false.
  if (numRowsInBoard < 0) 
  {
    printf("ERROR: illegal number of rows in board");
    return 0;
  }

  // Initialize the board with zeroes in every element.
  for (int rows = 0; rows < numRowsInBoard; rows++)
  {
    for (int cols = 0; cols < numRowsInBoard; cols++)
    { 
      connectNBoard[rows][cols] = 0;
    }
  }

  // If the pointer to the board is NULL, return false.
  if (connectNBoard == NULL)
  {
    printf("ERROR: cannot initialize the board because the pointer to the board is NULL");
    return 0;
  }

  return 1;
} 


/*Function that places gamepieces in the bottom-most '0' element in the chosen column of the board array*/
int MakeMove(int** connectNBoard, int numRowsInBoard, int playerID, int columnChosen)
{

  // If the pointer to the board is NULL, return false.
  if (connectNBoard == NULL)
  {
    printf("ERROR: cannot print the board because the pointer to the board is NULL");
    return 0;
  }

  // If the move is not legal (the column chosen is not part of the board, or the column chosen
  // has no empty elements) print a line of text to the screen that says Illegal Move and return false
  if(columnChosen >= numRowsInBoard || columnChosen < 0 || connectNBoard[0][columnChosen] != 0)
  {
    printf("Illegal move\n");
    return 0;
  }

  for(int row = numRowsInBoard - 1; row >= 0; row--)
  {
    if (connectNBoard[row][columnChosen] == 0) 
    {
        connectNBoard[row][columnChosen] = playerID;
          if(playerID == 1)
          {
            printf("Red has moved\n");
          }
          else
          {
            printf("Black has moved\n");
          }

          return 1;
    }
  }
  
  return 0;

}

/*Function that prints the game board to the screen*/
int DisplayBoard(int** connectNBoard, int numRowsInBoard)
{

  // If the pointer to the board is NULL, return false.
  if (connectNBoard == NULL)
  {
    printf("ERROR: cannot print the board because the pointer to the board is NULL");
    return 0;
  }

  // If the number of rows is illegal (negative), return false.
  if(numRowsInBoard < 0)
  {
    printf("ERROR: illegal number of rows in board");
    return 0;
  }

  // Prints the row above the board which shows the column numbers
  printf("   ");
  for(int row = 0; row < numRowsInBoard; row++)
  {
    printf("%3d", row);
  }
  printf("\n");

  // Prints the row numbers and the contents of the board.
  for(int row = 0; row < numRowsInBoard; row++)
  {
    for(int col = 0; col < numRowsInBoard; col++)
    {
        if(col == 0)
        {
          printf("%3d", row);
        }

        if(connectNBoard[row][col] == 0)
        {
          printf("%3c", 'o');
        }
        else if(connectNBoard[row][col] == 1)
        {
          printf("%3c", 'R');
        }
        else if(connectNBoard[row][col] == 2)
        {
          printf("%3c", 'B');
        }
    }
    printf("\n");
  }
  
  return 1;

}

/*Function to check if a winning pattern is found*/
int CheckWinner(int** connectNBoard, int numRowsInBoard, int numConnect, int columnChosen, int playerID)
{

  int beforeCount = 0; // Counts from the left of the newest gamepiece
  int afterCount = 0; // Counts from the right of the newest gamepiece

  // If the move is not legal (the column chosen is not part of the board, > numRowsInBoard) return false.
  if(columnChosen > numRowsInBoard - 1)
  {
    printf("ERROR: invalid column chosen, cannot check for winner");
    return 0;
  }

  // If the pointer to the board is NULL, return false.
  if (connectNBoard == NULL)
  {
    printf("ERROR: cannot print the board because the pointer to the board is NULL");
    return 0;
  }

  /*Determine which row the last gamepiece was placed in.
    for loop starts at the bottom-most row, subtracting a row (going up the column) for every row that is not a 0.
    Once a 0 has been reached, the loop terminates and the row index is found.*/
  int findRow;
  for(int i = numRowsInBoard-1; i > 0; i--)
  {
    if(connectNBoard[i-1][columnChosen] == 0)
    {
      findRow = i;
      break;
    }
  }

  // Check for a horizontal win.

  // Finds beforeCount
  int i = columnChosen-1;
  while(i >= 0)
  {
    if(connectNBoard[findRow][i] == playerID)
    {
      beforeCount++;
      i--;
    }
    else
    {
      break;
    }
  }
  
  
  // Finds afterCount
  i = columnChosen+1;
  while(i < numRowsInBoard)
  {
    if(connectNBoard[findRow][i] == playerID)
    {
      afterCount++;
      i++;
    }
    else
    {
      break;
    }
  }
  

  if((afterCount + beforeCount + 1) >= numConnect)
  {
    return 1;
  }

  // Check for a vertical win.
  beforeCount = 0; // Counts from beneath the newest gamepiece
  afterCount = 0; // Counts from above the newest gamepiece

  // Finds beforeCount
  i = 1;
  while(findRow+i < numRowsInBoard)
  {
    if(connectNBoard[findRow+i][columnChosen] == playerID)
    {
      beforeCount++;
      i++;
    }
    else
    {
      break;
    }
  }

  // Finds afterCount
  i = 1;
  while(findRow-i >= 0)
  {
    if(connectNBoard[findRow-i][columnChosen] == playerID)
    {
      afterCount++;
      i++;
    }
    else
    {
      break;
    }
  }

  if((afterCount + beforeCount + 1) >= numConnect)
  {
    return 1;
  }

  /*Check for a diagonal win.
    Have to check for two different types of diagonals: 
    1. Bottom left tail to top right tail
    2. Top left tail to bottom right tail*/ 

  // Positive linear diagonal (bottom-left tail to top-right tail)
  beforeCount = 0; // Counts diagonally left from the newest gamepiece
  afterCount = 0; // Counts diagonally right from the newest gamepiece

  for(int i = 1; findRow+i < numRowsInBoard && columnChosen-i >= 0; i++)
  {
    // Diagonal by down and left
    if(connectNBoard[findRow+i][columnChosen-i] == playerID)
    {
      beforeCount++;
    }
    else
    {
      break;
    }
  }

  for(int i = 1; findRow-i >= 0 && columnChosen+i < numRowsInBoard; i++)
  {
    // Diagonal by up and right
    if(connectNBoard[findRow-i][columnChosen+i] == playerID)
    {
      afterCount++;
    }
    else
    {
      break;
    }
  }

  if((afterCount + beforeCount + 1) >= numConnect)
  {
    return 1;
  }

  // Negative linear diagonal (top-left tail to bottom-right tail)
  beforeCount = 0; // Counts diagonally left from the newest gamepiece
  afterCount = 0; // Counts diagonally right from the newest gamepiece

  for(int i = 1; findRow-1 >= 0 && columnChosen-i >= 0; i++)
  {
    // Diagonal by up and left
    if(connectNBoard[findRow-i][columnChosen-i] == playerID)
    {
      beforeCount++;
    }
    else
    {
      break;
    }
  }

  for(int i = 1; findRow+i < numRowsInBoard && columnChosen+i < numRowsInBoard; i++)
  {
    // Diagonal by down and right
    if(connectNBoard[findRow+i][columnChosen+i] == playerID)
    {
      afterCount++;
    }
    else
    {
      break;
    }
  }

  if((afterCount + beforeCount + 1) >= numConnect)
  {
    return 1;
  }
  
  return 0;
}