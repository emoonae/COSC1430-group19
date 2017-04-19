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
    
    if (myfile.is_open())
    {
        int x = 0, rowCounter = 0;
        cout << endl;

        while (getline(myfile,line))
        {
            int colCounter = 0;

            if (line != "") {
                if ((rowCounter == 3) || (rowCounter == 6))
                {
                    cout << "---------------------------------------\n";
                }
                cout << "---------------------------------------" << endl;
                int index = 0;

                for (int i = 0; i < line.length(); i++)
                {
                    
                    if (i == 0) 
                    {
                        cout << "|";
                    }
                    
                    if (isdigit(line[i])) 
                    {
                        ++colCounter;
                        temp[x][index] = line[i];
                        //cout << "(" << x << "," << index << ")=" << line[i] << endl;
                        if ((colCounter == 3) || (colCounter == 6))
                        {
                            if (line[i] == '0')
                            {
                                cout << "   ||";
                            }
                            else 
                            {
                                cout << " " << line[i] << " ||";
                            }
                        }
                        else 
                        {
                            if (line[i] == '0')
                            {
                                cout << "   |";
                            }
                            else 
                            {
                                cout << " " << line[i] << " |";
                            }
                        }
                        index++;
                    }

                }
                cout << "Done"<< endl;
                rowCounter++;
                x++;
            }
        }
        cout << "---------------------------------------\n" << endl;
        myfile.close();
    }
    else
    {
        cout << "Cannot open file." << endl;
    }

    myfile.close();

    delete[] temp;
    delete[] board;

    return 0;
}