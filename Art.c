// Displays an ASCII art image based on greyscale values read in from standard input
// 
// DO NOT MODIFY

#include "Array2D.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int rows = 0;
    int cols = 0;

    // File should start with two integers specifying size of image
    // We'll assume the input is well-formed so won't check scanf's result value
    scanf("%d %d", &rows, &cols);

    // We'll store the image in a 2D variable length array of doubles
    double pixels[rows][cols];

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            scanf("%lf", &pixels[row][col]);
        }
    }

    // Display the loaded greyscale values as ASCII art
    array2DPrintASCII(rows, cols, pixels);

    // Compute and display some stats about the image
    Array2DStats stats = array2DComputeStats(rows, cols, pixels);
    array2DPrintStats(&stats);
    
    return 0;
}
