#include <LiquidCrystal.h>
LiquidCrystal lcd1(7, 8, 9, 10, 11, 12);
LiquidCrystal lcd2(7, 5, 9, 10, 11, 12);
LiquidCrystal lcd3(7, 4, 9, 10, 11, 12);
int receiver = 6;
int val;
#define DEBUG  true 
#define SHOW_MOVES true
int col = 0;
int row1 = 0;
int row2=2;
int row3=6;
int posX = 3;
int posY = 0;
int grid[9][9]={{0, 3, 5,  0, 0, 0,  2, 4, 0},   //hard
                {0, 0, 0,  0, 3, 2,  0, 0, 0},
                {0, 0, 1,  0, 0, 0,  9, 0, 0},
                {0, 7, 0,  4, 0, 8,  0, 0, 0},
                {0, 1, 0,  0, 2, 0,  0, 9, 0},
                {0, 0, 0,  6, 0, 7,  0, 8, 0},  
                {0, 0, 3,  0, 0, 0,  7, 0, 0},
                {0, 0, 0,  3, 6, 0,  0, 0, 0},
                {0, 5, 2,  0, 0, 0,  1, 6, 0}
                };
/*int grid[9][9]={{3, 0, 6, 5, 0, 8, 4, 0, 0}, //easy 
                {5, 2, 0, 0, 0, 0, 0, 0, 0}, 
                {0, 8, 7, 0, 0, 0, 0, 3, 1}, 
                {0, 0, 3, 0, 1, 0, 0, 8, 0}, 
                {9, 0, 0, 8, 6, 3, 0, 0, 5}, 
                {0, 5, 0, 0, 9, 0, 6, 0, 0}, 
                {1, 3, 0, 0, 0, 0, 2, 5, 0}, 
                {0, 0, 0, 0, 0, 0, 0, 7, 4}, 
                {0, 0, 5, 2, 0, 6, 3, 0, 0}};*/

void setup() {
  Serial.begin(9600);
  pinMode(receiver,INPUT);
  // set up the LCD's number of columns and rows:
  lcd1.begin(16, 2);
  lcd2.begin(20, 4);
  lcd3.begin(20, 4);
  // Print a message to the LCD.
  printLine1(0, "SUDOKU SOLVER");
  printLine2(0, "SUDOKU SOLVER1");
  printLine3(0, "SUDOKU SOLVER2");
  delay(2000);
  refreshLCD();
  lcd1.blink();
  lcd2.blink();
  lcd3.blink();
  
  
}
void loop() {
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(posX, posY);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
  val=digitalRead(receiver);
   switch(val) {
    case 1: solve(grid);    break;}
  delay(200);
}
void refreshLCD() {
  if (posY==0) {
    printLine1(posY, gridLine(row1));
    printLine1(posY+1, gridLine(row1+1));
    printLine2(posY, gridLine(row2));
    printLine2(posY+1, gridLine(row2+1));
    printLine2(posY+2, gridLine(row2+2));
    printLine2(posY+3, gridLine(row2+3));
    printLine3(posY, gridLine(row3));
    printLine3(posY+1, gridLine(row3+1));
    printLine3(posY+2, gridLine(row3+2));
    
  } else {
    printLine1(posY-1, gridLine(row1-1));
    printLine1(posY, gridLine(row1));
    printLine2(posY-3, gridLine(row2-1));
    printLine2(posY-2, gridLine(row2-1));
    printLine2(posY-1, gridLine(row2-1));
    printLine2(posY, gridLine(row2));
    printLine3(posY-2, gridLine(row3-1));
    printLine3(posY-1, gridLine(row3-1));
    printLine3(posY, gridLine(row3));
  }
  //lcd.setCursor(posX,posY);
}
String getValue(int v) {
  String s = String(v);
  if (v==0) {s=" ";}
  return s;
}
String gridLine(int row) {
  //String s = String(row+1) + " |";
  String s = getValue(grid[row][0]);
  s += getValue(grid[row][1]);
  s += getValue(grid[row][2]);
  s += "|";
  s += getValue(grid[row][3]);
  s += getValue(grid[row][4]);
  s += getValue(grid[row][5]);
  s += "|";
  s += getValue(grid[row][6]);
  s += getValue(grid[row][7]);
  s += getValue(grid[row][8]);
  s += "|";
  return s;
}
// Clear line r in lcd panel by printing spaces
// then rerurn the cursor to the first char of the line
void clearLine1(int r) {
  lcd1.setCursor(0,r);
  lcd1.print("                ");
  lcd1.setCursor(0,r);
}

// Clear line r and then print the text s
void printLine1(int r, String s) {
  clearLine1(r);
  lcd1.print(s);  
}

void clearLine2(int r) {
  lcd2.setCursor(0,r);
  lcd2.print("                ");
  lcd2.setCursor(0,r);
}

// Clear line r and then print the text s
void printLine2(int r, String s) {
  clearLine2(r);
  lcd2.print(s);  
}

void clearLine3(int r) {
  lcd3.setCursor(0,r);
  lcd3.print("                ");
  lcd3.setCursor(0,r);
}

// Clear line r and then print the text s
void printLine3(int r, String s) {
  clearLine3(r);
  lcd3.print(s);  
}
bool solve(int grid[9][9]) {


  if (solveGrid(grid)) {
    refreshLCD();
    return true;
  }

  int moves;
  if (solveBacktracking(grid, moves)) {
      printLine1(0, "SUDOKU SOLVED");
      printLine2(0, "SUDOKU SOLVED");
      printLine3(0, "SUDOKU SOLVED");
      delay(2000);
      //printLine(0,"I had to use backtracking method");
      printLine1(1, String(moves));
      delay(2000);
      refreshLCD();
   
       delay(2000);
      //printGrid(grid);
    } 
  else {
    printLine1(0, "NOT SOLVED");
    // SolveWithBruteForce(grid);
  };
  return false;
}
bool solveGrid (int grid[9][9]) {
  int values[9][9];       // Holds the predicted numbers for each step: values[r][c]
  bool numbers[9][9][9];  // Holds the prediction for each number in a cell: numbers[n][r][c]
  int empties = emptyCells(grid); // counts the empty cells
  int emptiesOld;
  int steps = 0;

  // clear the values table
  clearGrid(values);

  // loop until there are no empty cells
  while (empties>0) {
    emptiesOld = empties;
    steps++;
    // Fill the "numbers" table with predictions
    prepareCells(grid, numbers);
  
    checkCells(grid, numbers, values);
    copyValues(grid, values);
    empties = emptyCells(grid);
    if (empties == emptiesOld) {
      // Cannot solve SUDOKU
      return false;
    }
  }
  return true;
}

bool solveBacktracking (int grid[9][9], int &moves) {
  int r, c;

  moves++;
  // If there is no empty cell then we solved it!
  if (!findEmptyCell(grid, r, c)) return true;

  // test digits 1 to 9
  for (int n = 1; n <= 9; n++) {
    if (isSafe(grid, r, c, n)) {
      grid[r][c] = n;

      //return, if success
      if (solveBacktracking(grid, moves)) return true;

      // failure, unmake & try again
      grid[r][c] = 0;
    }
  }
  
  return false;
}
bool findEmptyCell(int grid[9][9], int &r, int &c) {
  for (r = 0; r < 9; r++) {
    for (c = 0; c < 9; c++) {
      if (grid[r][c] == 0) return true;
      }
    }
  return false;
}
void checkCells(int grid[9][9], bool numbers[9][9][9], int values[9][9]) {
  for (int r=0; r<9; r++) {
    for (int c=0; c<9; c++) {
      if (grid[r][c]!=0) continue;    // If the cell has a value then go to next cell
      if (values[r][c]!=0) continue;  // If the cell has a prediction then go to next cell
      
      for (int n=0; n<9; n++) {
        // check if the prediction is the only one in the box
        if (values[r][c]==0 && uniqueInBox(numbers, n, r-r%3, c-c%3) && numbers[n][r][c]) {
          values[r][c]=n+1;
          continue;
        }
        // check if the prediction is the only one in the row
        if (values[r][c]==0 && uniqueInRow(numbers, n, r) && numbers[n][r][c]) {
          values[r][c]=n+1;
          continue;
        }
        // check if the prediction is the only one in the column
        if (values[r][c]==0 && uniqueInCol(numbers, n, c) && numbers[n][r][c]) {
          values[r][c]=n+1;
          continue;
        }
        if (values[r][c]==0 && uniqueInCell(numbers, r, c) && numbers[n][r][c]) {
          values[r][c]=n+1;
          continue;
        }
      }
    }
  }
}
// Check if the given num exists in row
bool UsedInRow(int grid[9][9], int r, int num) {
  for (int c = 0; c < 9; c++) {
    if (grid[r][c] == num) return true;
  }   
  return false;
}

// Check if the given num exists in column
bool UsedInCol(int grid[9][9], int c, int num) {
  for (int r = 0; r < 9; r++) {
    if (grid[r][c] == num) return true;
  }
  return false;
}

// Check if the given num exists in box
bool UsedInBox(int grid[9][9], int boxStartRow, int boxStartCol, int num) {
  for (int r = 0; r < 3; r++) {
    for (int c =0; c < 3; c++)
      if (grid[r + boxStartRow][c + boxStartCol] == num) return true;
  }
  return false;
}
// check if the given num is valid for the cell
bool isSafe(int grid[9][9], int r, int c, int num) {
  return !UsedInRow(grid, r, num) &&
    !UsedInCol(grid, c, num) &&
    !UsedInBox(grid, r - r % 3, c - c % 3, num) &&
    grid[r][c] == 0;
}

// check if the possible 
bool uniqueInRow(bool numbers[9][9][9], int n, int r) {
  int count=0;
  for (int c = 0; c < 9; c++) {
    if (numbers[n][r][c]) { count++; }
  }
  return count==1;
}

bool uniqueInCol(bool numbers[9][9][9], int n, int c) {
  int count=0;
  for (int r = 0; r < 9; r++) {
    if (numbers[n][r][c]) { count++; }
  }
  return count==1;
}

bool uniqueInBox(bool numbers[9][9][9], int n, int startRow, int startCol) {
  int count=0;
  for (int r = 0; r < 3; r++) {
    for (int c =0; c < 3; c++)
      if (numbers[r + startRow][c + startCol]) { count++; }
  }
  return count==1;
}

bool uniqueInCell(bool numbers[9][9][9], int r, int c) {
  int count=0;
  for (int n = 0; n < 9; n++) {
    if (numbers[n][r][c]) { count++; }
  }
  return count==1;
}

void copyValues(int grid[9][9], int values[9][9]) {
  for (int r=0; r<9; r++) {
    for (int c=0; c<9; c++) {
      if (values[r][c] != 0) { grid[r][c] = values[r][c]; }
      values[r][c] = 0;
    }
  }
}
void clearGrid(int grid[9][9]) {
  for (int r=0; r<9; r++) {
    for (int c=0; c<9; c++) { grid[r][c] = 0; }
  }
}
void prepareCells(int grid[9][9], bool numbers[9][9][9]) {
  for (int r=0; r<9; r++) {
    for (int c=0; c<9; c++) { setNumbers(r, c, grid, numbers); }
  }
}

void setNumbers(int r, int c, int grid[9][9], bool numbers[9][9][9]) {
  for (int n = 0; n < 9; n++) {
    //if (grid[r][c] != 0) {numbers[n][r][c] = false; continue;}
    numbers[n][r][c] = isSafe(grid, r, c, n+1);
  }
}
int emptyCells(int grid[9][9]) {
  int i=0;
  for (int r=0; r<9; r++) {
    for (int c=0; c<9; c++) {
      if (grid[r][c] == 0) {i++;}
    }
  }
  return i;
}
