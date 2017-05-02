#include <iostream>
#include <fstream>

using namespace std;

const int BOARD_SIZE = 81;
const int SIZE = 9;

int main () {
    int* board = new int[BOARD_SIZE];
    int** temp = new int*[SIZE];
    
    for (int row = 0; row < SIZE; row++) 
    {
        temp[row] = &board[row * SIZE];
    }

    string line;
    ifstream myfile ("samplesudoku4.txt");
    
    // read file, print initial board & populate multi-dimensional array
    if (myfile.is_open())
    {
        int x = 0, solved = 0;
        cout << endl;

        while (getline(myfile,line))
        {
            if (line != "") {
                cout << "\n-------------------------------------" << endl;
                int index = 0;

                for (int i = 0; i < line.length(); i++)
                {
                    if (i == 0) 
                    {
                        cout << "|";
                    }
                    
                    if (isdigit(line[i])) 
                    {
                        // populate multi-dimensional array
                        temp[x][index] = line[i] - '0';
                        if (line[i] == '0')
                        {
                            cout << "   |";
                            // count the number of zeroes
                            solved++;
                        }
                        else 
                        {
                            cout << " " << line[i] << " |";
                        }
                        index++;
                    }
                }
                x++;
            }
        }
        cout << "\n-------------------------------------\n" << endl;

        cout << "EMPTY SPACES: " << solved << endl; // inital number of empty spaces

        int check[SIZE], otherCheck[SIZE], adjacentCheck[SIZE]; // arrays of possibilities -- index: 1-9
 
        // while there are still zeroes in the multi-dimensional array
        while (solved != 0)
        {
            for (int row=0; row<SIZE; row++)
            {
                for (int col=0; col<SIZE; col++)
                {
                    int rowBlock = row / 3; // assigns 0,1,2 -- based on row value
                    int colBlock = col / 3; // assigns 0,1,2 -- based on col value
                    
                    for (int a = 1; a <= SIZE; a++)
                    {
                        check[a] = 1; // assign each value '1' (true) by default
                        otherCheck[a] = 0; // initalize each value to 0
                        adjacentCheck[a] = 0; // assign each value '0' (false) by default
                    }
            
                    // solving board
                    if (temp[row][col] == 0) // temp[0][6]
                    {
                        // check rows
                        for (int look=0; look < SIZE; look++)
                        {
                            int cell = temp[row][look]; // temp[0][0-8]
                            check[cell] = 0; // check[1], check[3], check[6], check[7], check[8] = 0
                        }
                        // check cols
                        for (int look=0; look < SIZE; look++)
                        {
                            int cell = temp[look][col]; // temp[0-8][8]
                            check[cell] = 0; // check[1], check[3], check[5] = 0
                        }
                        // check 3x3 grid
                        for (int checkRow=0; checkRow < SIZE; checkRow++)
                        {
                            for (int checkCol=0; checkCol < SIZE; checkCol++)
                            {
                                int cell = temp[checkRow][checkCol];
                                
                                if ((checkRow / 3 == rowBlock) && (checkCol / 3 == colBlock)) // rows in same row block, columns in same column block
                                {
                                    check[cell] = 0; // check[1], check[2], check[6], check[7] = 0
                                }
                            }
                        }

                        /*
                            POSSIBLE TESTS: (actual answers that should be obvious for samplesudoku4.txt)
                            ---------------
                            temp[5][4] = 6  
                        */

                        // check adjacent grids
                        for (int checkRow=0; checkRow < SIZE; checkRow++) // loop through rows
                        {
                            for (int checkCol=0; checkCol < SIZE; checkCol++) // loop through columns
                            {
                                if ((checkRow / 3 == rowBlock) && (checkCol / 3 != colBlock)) // grids in row block, but not in column block
                                {
                                    int startRow = rowBlock * 3; 
                                    int end = startRow + 3; 
                                    for (int start = startRow; start < end; start++) // only loop through rows in row block
                                    {
                                        for (int colCheck=0; colCheck < SIZE; colCheck++) // loop through columns
                                        {
                                            if ((start != row) && (colCheck / 3 != colBlock)) // only loop through items where row is different and column is in different column block
                                            {
                                                int other = temp[start][colCheck]; // [1][0-5], [2][0-5]
                                                if (check[other] == 1) // haven't ruled it out? answer -- 4,9
                                                {
                                                    otherCheck[other] = otherCheck[other] + 1; // otherCheck[4] = 1; otherCheck[9] = 2;
                                                }
                                            }
                                        }
                                    }
                                } // end of "if"
                                else if ((checkRow / 3 != rowBlock) && (checkCol / 3 == colBlock)) // grids in column block, but not in row block
                                {
                                    for (int rowCheck=0; rowCheck < SIZE; rowCheck++) // loop through rows
                                    {
                                        int startCol = colBlock * 3;
                                        int end = startCol + 3;
                                        for (int start = startCol; start < end; start++) // only loop through columns in column block
                                        {
                                            if ((start != col) && (rowCheck / 3 != rowBlock)) // only loop through items where row is in different row block and column is different
                                            {
                                                int other = temp[rowCheck][start]; // [3-8][7], [3-8][8]
                                                if (check[other] == 1) // haven't ruled it out? answer -- 4,9
                                                {
                                                    otherCheck[other] = otherCheck[other] + 1; // otherCheck[4] = 2; otherCheck[9] = 3;
                                                }
                                            }
                                        }
                                    }
                                } // end of "else if"
                            } // end of initial loop through columns
                        } // end of initial loop through rows

                        for (int dumb=0; dumb<=SIZE; dumb++) // I am not sure why the values in otherCheck[SIZE] are stored in denominations of 18.
                        {
                            otherCheck[dumb] /= 18;
                        }

                        //cout << "[" << row << "][" << col << "]" << endl;
                        for (int a = 1; a <= SIZE; a++)
                        {
                            int countEmpty, countFound;
                            if ((check[a] == 1) && (otherCheck[a] == 4)) // number is possibility & only possibility
                            {
                                for (int b = 1; b <= SIZE; b++) // loop through every possibility
                                {
                                    if (a == b) // number = iterator
                                    {
                                        check[b] = 1;
                                    }
                                    else
                                    {
                                        check[b] = 0;
                                        otherCheck[b] = 0;
                                    }
                                }
                            }
                            else if ((check[a] == 1) && (otherCheck[a] == 3)) // a = 9
                            {
                                countEmpty = 0;
                                countFound = 0;
                                // loop through adjacent rows and colums that correspond to "empty intersections"
                                // -- in this example, temp[2][0-5] & temp[3-8][7], and update adjacentCheck[a]
                                for (int checkRow=0; checkRow < SIZE; checkRow++) // loop through rows
                                {
                                    for (int checkCol=0; checkCol < SIZE; checkCol++) // loop through columns
                                    {
                                        // first check adjacent empty columns
                                        if ((checkRow == row) && (checkCol / 3 == colBlock) && (temp[checkRow][checkCol] == 0) && (checkCol != col)) // row = 0; colBlock = 2; empty space
                                        {
                                            countEmpty++; // increment by 1

                                            for (int rowCheck=0; rowCheck < SIZE; rowCheck++) // loop through rows
                                            {
                                                if (rowCheck / 3 != rowBlock) // rowBlock = 1 or rowBlock = 2;
                                                {
                                                    int cell = temp[rowCheck][checkCol];
                                                    if (cell == a)
                                                    {
                                                        countFound++; // you found +1 instances of 9
                                                    }
                                                }
                                            }
                                        }
                                        // then check adjacent empty rows
                                        else if ((checkCol == col) && (checkRow / 3 == rowBlock) && (temp[checkRow][checkCol] == 0) && (checkRow != row))
                                        {
                                            countEmpty++; // increment by 1

                                            for (int colCheck=0; colCheck < SIZE; colCheck++) // loop through columns
                                            {
                                                if (colCheck / 3 != colBlock) // colBlock = 0 or colBlock = 1
                                                {
                                                    int cell = temp[checkRow][colCheck];
                                                    if (cell == a)
                                                    {
                                                        countFound++; // you found +1 instances of 9
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                if ((countEmpty != 0) && (countEmpty == countFound))
                                {
                                    adjacentCheck[a] = 1;
                                    for (int b=1; b<=SIZE; b++)
                                    {
                                        if (b == a)
                                        {
                                            check[b] = 1;
                                        }
                                        else
                                        {
                                            check[b] = 0;
                                        }
                                    }
                                }
                            }
                            //cout << a << ". Check: " << check[a] << " | Other Check: " << otherCheck[a] << " | Adjacent Check: " << adjacentCheck[a] << endl;
                        }

                        int answer, sum = 0;
                        // loop through possible answers
                        for (int look=1; look<=SIZE; look++) 
                        {
                            if (adjacentCheck[look] == 1)
                            {
                                answer = look;
                            }
                            else if (check[look] == 1)
                            {
                                answer = look; // answer is only possibility, OR last possibility
                            }
                            sum += check[look]; // sum of all check values
                        }
                        // only one possibility
                        if (sum == 1)
                        {
                            temp[row][col] = answer; // change zero to answer
                            solved--; // decrement the total number of zeroes
                        }
                    } // end of solving board
                } // end of column loop 
            } // end of row loop

            cout << "\n-------------------------------------" << endl;
            
            for (int x = 0; x < SIZE; x++)
            {
                for (int index = 0; index < SIZE; index++)
                {
                    cout << "| ";
                    if (temp[x][index] == 0)
                    {
                        cout << "  ";
                    }
                    else 
                    {
                        cout << temp[x][index] << " ";
                    }
                }
                cout << "|\n-------------------------------------" << endl;
            }
        } // end of while loop

        // print solved puzzle
        cout << "\n-------------------------------------" << endl;
        for (int row = 0; row < SIZE; row++)
        {
            for (int col=0; col < SIZE; col++)
            {
                if (col == 0) 
                {
                    cout << "|";
                }
                cout << " " << temp[row][col] << " |";
            }
            cout << "\n-------------------------------------" << endl;
        }
        cout << "\nEMPTY SPACES: " << solved << "\n" << endl; // final number of empty spaces (should be 0)
    }

    // unable to open file
    else
    {
        cout << "Cannot open file." << endl;
    }

    myfile.close();

    delete[] temp;
    delete[] board;

    return 0;
}
