#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
/* @author asharkot 
* Artem Sharkota 
* Program to generate certain amount of random points in 2 dimensional plane
*/

//function that generates random in range and takes me 3 days to make it work properly
double randomInRange(double low, double high){
    double f = (double)rand() / RAND_MAX;
    return low + f * (high - low);
}

//just main of this great program 
int main(int argc, char *argv[]){

    //if less then 5 arguments, provide usage i guess
    if (argc < 5){
        printf("Usage: RandomPoints <num points> <max id> <low> <high> <seed>\n");
        return 0;
    }
    
    //An integer specifying the number of points to output.
    int numPoints = atoi(argv[1]);
    //An integer specifying the maximum integer ID of points.
    int maxId = atoi(argv[2]);
    //number of sprinklers
    double low = atof(argv[3]);
    //minimum radius 
    double high = atof(argv[4]);
    //seed for random generation 
    int seed = atoi(argv[5]);

    //all the parameters tests we need 
    //prints error message if something is wrong 
    if (numPoints < 1){
        printf("ERROR: num points and max id must be positive!\n");
        return 0;
    }
    if (maxId < 1){
        printf("ERROR: num points and max id must be positive!\n");
        return 0;
    }

    if (low > high){
        printf("ERROR: low must be less than or equal to high!\n");
        return 0;
    }

    //setting up random with the provided seed
    srand(seed);

    //creating 2D array (waiting for the area)
    double points[numPoints][3];

    //print number of points
    printf("%d \n", numPoints);

    //inserting the values inside the array 
    for (int i =0; i < numPoints; i++ ){
        points[i][0] = (rand() % (maxId - 1 + 1)) + 1; //id 
        points[i][1] = randomInRange(low, high); // x coordinate 
        points[i][2] = randomInRange(low, high); // y coordinate
        printf("%.0f %.2f %.2f\n", i+1, points[i][0], points[i][1],points[i][2]); //final print for the program
    }

    //being good boi requires using good practices 
    printf("\n"); //good practice #1
    return 0; //good practice #2
}


 