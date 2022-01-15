#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "Array2D.h"

/*
* @author asharkot
* Artem Sharkot
* Program that can do operations based on the provided arguments to the program 
*/

int main(int argc, char *argv[]){

    //if we don't have enough armunets, print usage line and exit 
    if (argc < 3){
        printf("Usage: Process <in file> <out file> [command 1] ...\n");
        return 0; 
    }

    //if we don't have any additional commands 
    if (argc == 3){
        int rows, columns;

        FILE *input;
        input = fopen(argv[1], "r"); 

        if (!input){
            printf("ERROR: failed to open '%s'\n", argv[1]);
            return 0;
        }

        FILE *output;
        output = fopen(argv[2], "w"); 
        if (!output){
            printf("ERROR: failed to open '%s'\n", argv[2]);
            return 0;
        }

        fscanf(input, "%d", &rows);
        //printf ("DEBUG: number of rows: %d\n", rows);
        fscanf(input, "%d", &columns);
        //printf ("DEBUG: number of columns: %d\n", columns);

        //creating the array of the elements in the file 
        double elements[rows][columns];    

        //reading all the elements in the file 
        for (int r = 0; r < rows; r++){ //increment row by row 
            for (int c = 0; c < columns; c++){ //every element in the line 
                fscanf(input, "%lf", &elements[r][c]); //set the place in the array to the temp 
                //printf("DEBUG, Element read: %.3f, at row: %d, column: %d.\n", elements[r][c], r, c);
            }
        }


        //printing the rows and columns 
        fprintf(output, "%d %d", rows, columns);

        //reading all the elements in the file 
        for (int r = 0; r < rows; r++){ //increment row by row 
            fprintf(output, "\n");
            for (int c = 0; c < columns; c++){ //every element in the line 
                fprintf(output, "%.3f ", elements[r][c]); //printing the array of the provided elements because no opertions were made 
                //printf("DEBUG, Element read: %.3f, at row: %d, column: %d.\n", elements[r][c], r, c);
            }
        }

        //closing all the files and using good practive because i am a good boiii 
        fclose(input);
        fclose(output);
        printf("\n");
        return 0; 
    }

    //if we have additional arguments
    if (argc > 3){

        //initializing the variables 
        int rows, columns;

        //file we are reading from 
        FILE *input;
        input = fopen(argv[1], "r"); 

        //if we were not able to find the provided file, print an error and exit 
        if (!input){
            printf("ERROR: failed to open '%s'\n", argv[1]);
            return 0;
        }

        //file we are writing to 
        FILE *output;
        output = fopen(argv[2], "w"); 

        //if we were not able to find the provided file, print an error and exit 
        if (!output){
            printf("ERROR: failed to open '%s'\n", argv[2]);
            return 0;
        }

        //scanning for rows and storing them 
        fscanf(input, "%d", &rows);
        //printf ("DEBUG: number of rows: %d\n", rows);

        //scanning for columns and storing them 
        fscanf(input, "%d", &columns);
        //printf ("DEBUG: number of columns: %d\n", columns);

        //creating the array of the elements in the file 
        double elements[rows][columns];    

        //reading all the elements in the file 
        for (int r = 0; r < rows; r++){ //increment row by row 
            for (int c = 0; c < columns; c++){ //every element in the line 
                fscanf(input, "%lf", &elements[r][c]); //set the place in the array to the temp
                //printf("DEBUG, Element read: %.3f, at row: %d, column: %d.\n", elements[r][c], r, c);
            }
        }

        //check all the provided arguments and manipulate the picture with every of them 
        for (int i = 3; i < argc; i++){
            //if the command matched the print fucntion, print the pictire with the ascii code 
            if (strcmp(argv[i], "print") == 0){
                printf("Command: print\n");
                //printing fucntion 
                array2DPrintASCII(rows, columns, elements);

            }//if the command matched the stats command 
            if (strcmp(argv[i], "stats") == 0){
                printf("Command: stats\n");

                //initializing the stats struct to print the most recent stats 
                Array2DStats statsFin;

                //computing the values 
                statsFin = array2DComputeStats(rows, columns, elements);

                Array2DStats *statsToPass;
                statsToPass = malloc(sizeof(Array2DStats*));

                //setting the values and print them
                statsToPass->max = statsFin.max;
                statsToPass->mean = statsFin.mean;
                statsToPass->min = statsFin.min;

                //printing the values we just found 
                array2DPrintStats(statsToPass);

            } 
            if (strcmp(argv[i], "mirror") == 0){
                printf("Command: mirror\n");
                //reverse the array horizontally 
                array2DReverseRows(rows, columns, elements);

            } //if the command matched the flip command 
            if (strcmp(argv[i], "flip") == 0){
                printf("Command: flip\n");
                //reverse the array vertically 
                array2DReverseCols(rows, columns, elements);
            }//if the command mathced the bw function 
            if (strcmp(argv[i], "bw") == 0){
                //how many levels we have 
                int numLevels = 2;
                //hard coding is my best friend 
                double levels[numLevels];
                levels[0] = 0.0; 
                levels[1] = 1.0; 
                printf("Command: bw\n");
                //manipulating the array 
                array2DQuantize(rows, columns, elements, numLevels, levels);
            } //if command matched the 4color fucntion 
            if (strcmp(argv[i], "4color") == 0){
                //how many levels we have 
                int numLevels = 4;
                //hard coding is always better than thinking 
                double levels[numLevels];
                levels[0] = 0.0; 
                levels[1] = 0.33; 
                levels[2] = 0.66; 
                levels[3] = 1.0; 
                printf("Command: 4color\n");
                //manipulate the array 
                array2DQuantize(rows, columns, elements, numLevels, levels);
            } //if provided command doesn't match any abailable options, say that command is not found and continue 
            if ((strcmp(argv[i], "4color") != 0) &&(strcmp(argv[i], "bw") != 0) && 
            (strcmp(argv[i], "flip") != 0) &&  (strcmp(argv[i], "mirror") != 0) &&
            (strcmp(argv[i], "stats") != 0) && (strcmp(argv[i], "print") != 0)){
                printf("Command: %s\n", argv[i]);
                printf("ERROR: unknown command\n");
            }
        }

        fprintf(output, "%d %d", rows, columns);

        //reading all the elements in the file 
        for (int r = 0; r < rows; r++){ //increment row by row 
            fprintf(output, "\n");
            for (int c = 0; c < columns; c++){ //every element in the line 
                fprintf(output, "%.3f ", elements[r][c]);
                //printf("DEBUG, Element read: %.3f, at row: %d, column: %d.\n", elements[r][c], r, c);
            }
        }

        //closing all the files and using good practive because i am a good boiii 
        fclose(input);
        fclose(output);
        printf("\n");
        return 0; 
    }


}
