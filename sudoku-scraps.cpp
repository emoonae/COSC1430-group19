int main() 
{
    int* board = new int[9];
    int** temp = new int*[3];

    for (int row = 0; row < 3; row++) 
    {
        temp[row] = &board[row * 3];
    }

    temp[0][0] = 6; // READ FILE TO POPULATE ARRAY

    delete[] temp;
    delete[] board;

    cout << "OK" << endl;

    return 0;
}