#include <stdio.h>
#include <stdbool.h>

/*Initializing the functions*/
int sudokuSolver(char grid[9][9], int row,int col);
int isValid();
void printGrid();
void resetArray();

/*2D array of size (9 * 9) */
char grid[9][9];
int row, col;


int main()
{ 
  int chr;
  /*Temporary array to hold the character*/
  char temp[100];
  /*initializing to check if the character and number are valid*/
  int validChar  = 1;
  int validNum = 1;
  /*row and column to go through the array*/
  int row, col;
  int n,i;
  row = col = 0;
  n =0;
  while (( chr = getchar()) != EOF)
  {
    /*Storing character in the temporary array*/
    temp[n] = chr;
    /*Printing out the character*/
    printf("%c", chr);
    n++;
    if (chr == '\n')
    {
      /*Error if the number of character is more or less than 81*/
      if (n < 82 || n > 82) printf("Error\n\n");
      else
      {
        for (i = 0; i< 81; i++)
        {
          /*Conditions for the sudoku to be valid*/
          if(temp[i] != '.')
          {
            if (!(temp[i] > '0' && temp[i] <='9' )) validNum = 0;
          }
          if(temp[i] != '.' && !(isValid(row,col,temp[i]))) validChar = 0;
          grid[row][col]=temp[i];
          col++;
          if(col == 9)
          {
            row++;
            col = 0;
          }
        }
        if (validChar == 1 && validNum == 1)
        {
          /*Sudoku function is called*/
          if(sudokuSolver(grid, 0, 0))
          {
            /*Prints the solved sudoku puzzle*/
            printGrid();
            printf("\n\n");
          }
          else if (sudokuSolver(grid, 0,0) == 0) printf("No solution\n\n");
        }
        else if (validChar == 0 || validNum == 0) printf("Error\n\n");
      }
      /*Function call to reset the grid*/
      resetArray();
      /*Resetting all the variables*/
      n =0;
      row = 0;
      col = 0;
      validChar = 1;
      validNum = 1;
    }
  }
  return 0;  
}

/*function to check if the number in sudoku is valid or not*/
int isValid(int cellRow, int cellCol, int num)
{
  int i,j;
  int rowStart = (cellRow/3) * 3;
  int colStart = (cellCol/3) * 3;

  /*Checking if the number is valid in row and column*/
  for ( j=0; j<9; j++)
  {
    if (grid[cellRow][j] == (num + '0')) return 0;
    if (grid[j][cellCol] == (num + '0')) return 0;
  }

  /*Checking if the number is valid in 3*3 box*/
  for (i = rowStart; i <= (rowStart + 2); i ++)
  {
    for (j = colStart; j <= (colStart + 2); j++)
    {
      if (grid[i][j] == (num + '0')) return 0;
    }
  }
  return 1;
}


/*Function to solve the sudoku*/ 
int sudokuSolver( char grid[9][9], int row, int col)
{
  int nextCol = 0;
  int nextRow = 0;
  int digit = 1;
  /* if row and column is greater than 9 returns true*/
  if (row >= 9 && col >= 9)
  {
    return 1;
  }
  else
  {
    /*Checking if the box contain '.' character*/
    if (grid[row][col] == '.')
    {
      /*Passing number so that it fits the current sudoku grid*/
      for(digit = 1; digit <= 9 ; digit++)
      {
        if (isValid(row,col,digit))
        {
          /*Passing the number as character if it is valid in the current position*/
          grid[row][col] = digit + '0';
          if ( col < 8)
          {
            nextCol = col + 1;
          }
          else if (row<8)
          {
            nextCol = 0;
            nextRow = row + 1;
          }
          else return 1;
          /*Using recurssive call to the function*/
          if (sudokuSolver(grid, nextRow,nextCol)) return 1;
        }
        /*Backtracking if the number doesnt fit the position*/
        grid[row][col] = '.';
      }
    }
    else 
    {
      /*Moving in the next cell*/
      if (col < 8)
      {
        col++;
      }
      else if (row < 8)
      {
        col = 0;
        row++;
      }
      else return 1;
      return sudokuSolver(grid,row,col);
    }
    return 0;
  }
}


/*Function to print sudoku*/
void printGrid()
{
  int i, j;
  for(i = 0; i<9; i++)
  {
    for (j =0; j<9; j++)
    {
      printf("%c", grid[i][j]);
    }
  }
}

/*function to reset array*/
void resetArray()
{
  int i, j;
  for (i = 0; i<9; i++)
  {
    for(j = 0; j<9;j++)
    {
      grid[i][j] = '\0';
    }
  }
}
