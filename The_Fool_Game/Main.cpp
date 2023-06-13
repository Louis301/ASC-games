#include <iostream>


int main()
{
    const int n = 8, m = 5;

    int matrix[n][m];
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            matrix[i][j] = 0;


    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            matrix[i][j] = 0;

            std::cout.width(4);
            std::cout << matrix[i][j];
        }
        std::cout << std::endl;
    }

    return 0;
};