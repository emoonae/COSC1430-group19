#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main () {
    int* board = new int[81];
    int** temp = new int*[9];
    
    for (int row = 0; row < 9; row++) 
    {
        temp[row] = &board[row * 9];
    }

    string line;
    ifstream myfile ("samplesudoku1.txt");
    
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

        int check[9]; // array of possibilities -- index: 1-9
 
        // while there are still zeroes in the multi-dimensional array
        while (solved != 0)
        {
            for (int row=0; row<9; row++)
            {
                for (int col=0; col<9; col++)
                {
                    int rowBlock = row / 3; // assigns 0,1,2 -- based on row value
                    int colBlock = col / 3; // assigns 0,1,2 -- based on col value

                    for (int a = 1; a <= 9; a++)
                    {
                        check[a] = 1; // assign each value '1' (true) by default
                    }
            
                    // solving board
                    if (temp[row][col] == 0)
                    {
                        // check rows
                        for (int look=0; look < 9; look++)
                        {
                            int cell = temp[row][look];
                            check[cell] = 0;
                        }
                        // check cols
                        for (int look=0; look < 9; look++)
                        {
                            int cell = temp[look][col];
                            check[cell] = 0;
                        }
                        // check 3x3 grid
                        for (int checkRow=0; checkRow < 9; checkRow++)
                        {
                            if (checkRow / 3 == rowBlock)
                            {
                                for (int checkCol=0; checkCol < 9; checkCol++)
                                {
                                    if (checkCol / 3 == colBlock)
                                    {
                                        int cell = temp[checkRow][checkCol];
                                        check[cell] = 0;
                                    }
                                }
                            }
                        }

                        int answer, sum = 0;
                        // loop through possible answers
                        for (int look=1; look<=9; look++) {
                            if (check[look] == 1)
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
        } // end of while loop

        // print solved puzzle
        cout << "\n-------------------------------------" << endl;
        for (int row = 0; row < 9; row++)
        {
            for (int col=0; col < 9; col++)
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