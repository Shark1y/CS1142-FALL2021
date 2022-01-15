#include "Array2D.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
* @author asharkot
* Artem Sharkot
* Program that has all the functions and allows me to get a good grade in this class 
*/

//printing the picture, thanks god we had draw programm earlier 
void array2DPrintASCII(int rows, int cols, double pixels[rows][cols]){
    for (int y = -1; y <= rows; y++) {

        for (int x = -1; x <= cols; x++) {

            //printing borders of the picture
            if ((y == -1 && x == -1) || (y == rows && x == -1) || (y == -1 && x == cols) || (y == rows && x == cols)) {
                
                //corners
                printf("+");
            
            } else if (y == -1 || y == rows) {
                //top border
                printf("-");

            } else if (x == -1 || x == cols) {
                //side borders
                printf("|");

            }

            //printing pixels itself 

            else if (pixels[y][x] < 0.1) {

                printf(" ");

            } else if (pixels[y][x] >= 0.1 && pixels[y][x] < 0.2) {

                printf(".");

            } else if (pixels[y][x] >= 0.2 && pixels[y][x] < 0.3) {

                printf(":");

            } else if (pixels[y][x] >= 0.3 && pixels[y][x] < 0.4) {

                printf("-");

            } else if (pixels[y][x] >= 0.4 && pixels[y][x] < 0.5) {

                printf("=");

            } else if (pixels[y][x] >= 0.5 && pixels[y][x] < 0.6) {

                printf("+");

            } else if (pixels[y][x] >= 0.6 && pixels[y][x] < 0.7) {

                printf("*");

            } else if (pixels[y][x] >= 0.7 && pixels[y][x] < 0.8) {

                printf("#");

            } else if (pixels[y][x] >= 0.8 && pixels[y][x] < 0.9) {

                printf("%%");

            } else if (pixels[y][x] >= 0.9 ) {

                printf("@");
            }
        }
        printf("\n");
    }
}

//priniting the stats of the provided stats 
void array2DPrintStats(const Array2DStats* stats){

    printf("mean %.3f, min %.3f, max %.3f\n", stats->mean, stats->min, stats->max);
}


//making picture looks like it's being showed in the mirror 
void array2DReverseRows(int rows, int cols, double a[rows][cols]){
    double second[rows][cols];


    for (int i = 0; i < rows; i++){
        int counter = 0; 
        for (int j = cols-1; j > -1; j--){
            second[i][counter] = a[i][j];
            counter++;
        }
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols+1; j++){
            a[i][j] = second[i][j];
        }
    }
}

//reversing image upside down 
void array2DReverseCols(int rows, int cols, double a[rows][cols]){
    double second[rows][cols];

    for (int i = 0; i < cols; i++){
        int counter = 0; 
        for (int j = rows-1; j >= 0; j-- ){
            second[counter][i] = a[j][i];
            counter++;
        }
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols+1; j++){
            a[i][j] = second[i][j];
        }
    }
    
}

//computing stats of the elements and stores them into the struct 
Array2DStats array2DComputeStats(int rows, int cols, double a[rows][cols]){
    
    Array2DStats stats;
    
    double minimum = a[0][0];
    double maximum = a[0][0];

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (a[i][j] < minimum)
            {
                minimum = a[i][j];
            }
            if (a[i][j] > maximum)
            {
                maximum = a[i][j];
            }
        }
    }

    double numOfEl = 0; //counter for how many elements 
    double sum = 0; //total sum of all elements 
    for (int r = 0; r < rows; r++){ //increment row by row 
        for (int c = 0; c < cols; c++){ //every element in the line 
           sum += a[r][c]; //add current element to the sum of the previous ones 
           numOfEl++; //increase number of elements 
        }
    }

    stats.mean = sum/numOfEl; //mean = sum/n of elements 
    stats.max = maximum;
    stats.min = minimum;

    //returning stats we just computed 
    return stats;
}

//tre best function i have ever done, i am sorry for how bad it is 
void array2DQuantize(int rows, int cols, double a[rows][cols], int numLevels, double levels[numLevels]){
    
    //if the provided levels are bw 
    if (numLevels == 2){

    //difference of each elements between 1.0 and 0.0 respectively 
    double dif1;
    double dif0;

        for (int r = 0; r < rows; r++){ //increment row by row 
            for (int c = 0; c < cols; c++){ //every element in the line 

                    //difference of each elements between 1.0 and 0.0 respectively 
                    dif1 = 1.0 - a[r][c];
                    dif0 = a[r][c] - 0.0;

                    //if the distance to 1 is less than 0, set to 1 
                    if (dif1 < dif0){
                        a[r][c] = 1.0;
                    } //if the distance to 0 is less than 1, set to 0 
                    if (dif1 > dif0){
                        a[r][c] = 0.0;
                    } //if the distances are the same, set to 0 because it's first in the array 
                    if (dif1 == dif0){
                        a[r][c] = 0.0;
                    }
                    
            }
        }

    }

    //we have 4 levels if we used command 4colors 
    if (numLevels == 4){

    //difference of each elements between 0.0, 0.33, 0.66 and 1.0 respectively 
    double dif0;
    double dif3;
    double dif6;        
    double dif1;

        for (int r = 0; r < rows; r++){ //increment row by row 
            for (int c = 0; c < cols; c++){ //every element in the line 

                //difference of each elements between 0.0, 0.33, 0.66 and 1.0 respectively 
                dif0 = fabs(a[r][c] - levels[0]);
                //printf("%.3f\n", dif0);
                dif3 = fabs(a[r][c] - levels[1]);
                //printf("%.3f\n", dif3);
                dif6 = fabs(a[r][c] - levels[2]);
                //printf("%.3f\n", dif6);
                dif1 = fabs(a[r][c] - levels[3]);
                //printf("%.3f\n", dif1);
                
                //if distance to the 0.0 is less than to the others, set to 0.0
                if (dif0 < dif3 && dif0 < dif6 && dif0 < dif1){
                    a[r][c] = levels[0];
                }//if distance to the 0.33 is less than to the others, set to 0.33
                if (dif3 < dif0 && dif3 < dif6 && dif3 < dif1){
                    a[r][c] = levels[1];
                }//if distance to the 0.66 is less than to the others, set to 0.66
                if (dif6 < dif0 && dif6 < dif3 && dif6 < dif1){
                    a[r][c] = levels[2];
                }//if distance to the 1.0 is less than to the others, set to 1.0
                if (dif1 < dif0 && dif1 < dif3 && dif1 < dif6){
                    a[r][c] = levels[3];
                } //if the distances are the same, set to 0 because it's first in the array 
                if (dif0 == dif3 == dif6 == dif1){
                    a[r][c] = levels[0];
                }
            }
        }
    }
}
