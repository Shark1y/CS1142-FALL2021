#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdio.h>
#include <unistd.h>

/*
* @author asharkot
* Artem Sharkot
* Program reads the data from the file and stores it inside the array and manipulate it 
*/

//fucntion to find the largest number between the three numbers provided 
double ScaleRelatively(double value){
    double result = 0.00;
    result = (((value - 0.00) * (1.00 - 0.00)) / (255.00 - 0.00)) + 0.00;
    if (result >= 1.0){
        result = 1.0;
    }
    return result;
}

//funtion to find the largest number between the three numbers provided 
int MaxTriple(int red, int green, int blue){

    //variable to store the maximum number here 
    int max; 

    //comparison and storing algorithm 
    if(red > green) {
        if(red > blue) {
            max = red;
        } else {
            max = blue;
        }
    }
    else {
        if(green > blue) {
            max = green;
        } else {
            max = blue;
        }
    }
    //returning maximum value between three
    return max;
}

//fucntion to find the minimum number between the three numbers provided 
int MinTriple(int red, int green, int blue){
    //variable to store the minimum number here 
    int min; 
    //comparison and storing algorithm 
    if(red < green && red < blue)
	{
        min = red;
	}
	else if(green < blue)
	{
        min = green;
	}
	else
	{
        min  = blue;
	}
    //returning minimum number between three
    return min; 
}

//function to convert the rgb values to the greyscale and store them 
void Lightness(int rows, int numOfElementsInLine, double factor, int columns, int elements[rows][numOfElementsInLine], double greyscale[rows][columns]){

    //provided lighting factor 
    double multiplier;


    //very nice way to hard code something and do less work 
    if (factor == 0.00){
        multiplier = 1.00; 
    } else {
        multiplier = factor; 
    }

    double max; //container to store min value of RGB values 
    double min; //container to store max value of RGB values 
    double temp; //temp to store the sum/2 value 
    double container; //edited element 

    //for every element in the matrix 
    for (int r = 0; r < rows; r++){
        //resetting element we are working on to 0
        int element = 0; 
        for (int c = 0; c < numOfElementsInLine; c = c+3){
            max = MaxTriple(elements[r][c],elements[r][c+1],elements[r][c+2]); //calculating the max of the three numbers
            min = MinTriple(elements[r][c],elements[r][c+1],elements[r][c+2]); //calculating the min of the three numbers
            temp = ((max+min)/2); //store sum/2 in temp 
            container = (ScaleRelatively(temp)*factor);  //scale the temp and multiply by the brightness factor 
            if (container > 1.0){ //again great way how to do a lot of job by hard coding it 
                container = 1.0;
            }
            if (container < 0){
                container = 0.0;
            }

            greyscale[r][element] = container; //setting new value of the edited element 
            //printf("DEBUG, Element made: %.3f, at row: %d, column: %d.\n", greyscale[r][element], r, element);
            // printf("%d %d\n", r, element);
            printf("%.3f ", greyscale[r][element]); //printing elements in a required format 
            element++;
        }
        printf("\n"); //printing new line after each line and go to the next one 
    }
}

int main(int argc, char *argv[]){

    //storing the greyscale factor 
    double greyscaleFactor;
    if (argc >1){ //if we have the greyscale factor, store it 
        greyscaleFactor = atof(argv[1]);
    } else {
        greyscaleFactor = 1.0; //if factor is not provided, make brightness standart 
    }

    //initializing the variables for the rgb files 
    int rows; //number of rows in the picture
    int columns; //number of columns in the picture
    int numOfElementsInLine; //number of elements in the picture in one line
    int numOfElementsFinal; //number of elements in one file 

    scanf("%d", &rows); //scanning for the number of rows in the file

    //printf("DEBUG, num of rows: %d\n", rows);

    scanf("%d", &columns);//scanning for the number of columns in the file

    //printf("DEBUG, num of columns: %d\n", columns);

    numOfElementsInLine = 3*columns; //computing number of elements in the file 

    numOfElementsFinal = numOfElementsInLine * rows;

    int elements[rows][numOfElementsInLine]; //creating the array of the elements in the file 

    double greyscale[rows][numOfElementsInLine]; //storing final greyscale values in this array 

    //printf("DEBUG, num of elements in line: %d\n", numOfElementsInLine);

    //printf("DEBUG, num of elements in total: %d\n", numOfElementsFinal);

    //reading all the elements in the file 
    int counter = 0; //counter to read as much elements as we need 
    while (counter < numOfElementsFinal){ //while not end of the file, read integers 
        for (int r = 0; r < rows; r++){ //increment row by row 
            for (int c = 0; c < numOfElementsInLine; c++){ //every element in the line 
                scanf("%d", &elements[r][c]); //set the place in the array to the temp
                //printf("DEBUG, Element read: %d, at row: %d, column: %d.\n", elements[r][c], r, c);
                counter++;
                //printf("DEBUG num of elems read: %d\n", counter);
            }
        }
    }

    //final printing methods in a required formats 
    printf("%d %d\n", rows, columns);
    Lightness(rows, numOfElementsInLine, greyscaleFactor, columns, elements, greyscale);

    //good practice requires being a good boiii
    printf("\n");
    return 0; 
}
