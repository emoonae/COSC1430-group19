#include <iostream>
#include <fstream>
using namespace std;

int main () {
    string line;
    ifstream myfile ("samplesudoku1.txt");
    
    if (myfile.is_open())
    {
        cout << endl;
        while (getline(myfile,line))
        {
            if (line != "") {
                cout << "-------------------------------------" << endl;
                for (int i = 0; i < line.length(); i++)
                {
                    if (i == 0) 
                    {
                        cout << "|";
                    }
                    
                    if (isdigit(line[i])) 
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

                }
                cout << endl;
            }
        }
        cout << "-------------------------------------\n" << endl;
        myfile.close();
    }
    else
    {
        cout << "Cannot open file." << endl;
    }

    myfile.close();
    
    return 0;
}