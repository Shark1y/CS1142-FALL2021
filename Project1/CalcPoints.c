#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdio.h>
#include <unistd.h>

/*
*@author asharkot
*Artem Sharkot
*/

//making struct because why else did i even learn them?
typedef struct{
    int id;
    float xVal;
    float yVal;
}Record;

//making another struct to make life much more easier 
typedef struct{
    int idFistPoint;
    int idSecondPoint;
    float distance;
}SmallestDistancePoints;

//method to calculate the distance between two poits provided to the function 
float distanceBetween(Record point1, Record point2){
    float underRoot = pow((point2.xVal - point1.xVal),2) + pow((point2.yVal - point1.yVal),2);
    float result = sqrt(underRoot);
    return result;
}
//method to calculate the complete tour distance between all points including last and first 
double tourDistance(Record* records, int numOfPoints){
    float totalDist;
    
    //we are calculating the distance between point 1 and 2, 2 and 3,... n and numOfPoints 
    //adding the distance every time to the counter 
    for (int i = 0; i+1 < numOfPoints; i++){
        totalDist = totalDist + distanceBetween(records[i], records[i+1]);
    }

    //calculating the distance between the last point and the first point and adding in to the counter 
    totalDist = totalDist + distanceBetween(records[numOfPoints-1], records[0]);

    //returning total distance to the user 
    return totalDist;
}

//method to compute the largest element in the array 
float largest(float arr[], int numOfPoints){
    // Initialize maximum element
    float largest = arr[0];
 
    // Iterate through the array to find even larger element  
    for (int i = 1; i < numOfPoints; i++){
        if (arr[i] > largest){
            largest = arr[i];
        }
    }
    //return largest element from the array
    return largest;
}
//method to compute the smallest element in the array 
float minimum(float arr[], int numOfPoints){
    // Initialize minimum element
    float smallest = arr[0];
    // Iterate through the array to find even smaller element 
    for (int i = 1; i < numOfPoints; i++) {
        if (arr[i] < smallest) {
            smallest = arr[i];
        }
    }
    //return smallest element from the array
    return smallest;
}
//method to compute the average element in the array 
float average(float arr[], int numOfPoints){

   double avg, sum; //crating a temporary variables that we need in the future 
   int loop; //counter need to be outside for perfection 
   sum = avg = 0; //assigning value to the variables we made before;
   
   //going through all elements of the array 
   for(loop = 0; loop < numOfPoints; loop++) {
      sum = sum + arr[loop];
   }
   avg = (double)sum / loop;
   avg = avg + 0.0000001;
   return avg;
}

void findClosest(Record* records, SmallestDistancePoints* SDP, int numOfPoints, int* bestID1, int* bestID2, double* minDist){
    //creating a smallest 
    float smallestD = (distanceBetween(records[0], records[1]));
    SDP[0].distance = smallestD;
    SDP[0].idFistPoint = records[0].id;
    SDP[0].idSecondPoint = records[1].id;


    // Iterate through the array to find even smaller element 
    for (int i = 0; i < numOfPoints-1; i++){
        for ( int j = i+1; j < numOfPoints; j++){
            
            //printf("%d %d %.2f\n",i+1, j+1, (distanceBetween(records[i], records[j])));
            if ((distanceBetween(records[i], records[j])) < smallestD){
                smallestD = (distanceBetween(records[i], records[j]));
                SDP[0].distance = (distanceBetween(records[i], records[j]));
                SDP[0].idFistPoint = records[i].id;
                SDP[0].idSecondPoint = records[j].id;
            }

        }
    }

}

int main(int argc, char **argv){

    Record* records; //assinging place to store the values 
    SmallestDistancePoints* SDP;

    int numOfPoints; //number of points we have at the beggining of the file 
    scanf("%d", &numOfPoints); // scanning number of points 

    records = malloc(numOfPoints * sizeof *records);
    SDP = malloc(numOfPoints * sizeof *SDP);

    int x; // counter 
    for(x = 0; x < numOfPoints; x++){
        scanf("%d", &records[x].id); // scan the id and stores it at Record struct
        
        scanf("%f", &records[x].xVal); // scan the x Value and stores it at Record struct

        scanf("%f", &records[x].yVal);// scan the y Value and stores it at Record struct
    }

    int ids[numOfPoints]; //array for the ids
    float xValues[numOfPoints]; //array for the x values
    float yValues[numOfPoints]; //array for the y values 

    //loading up the values into the arrays for further calculations (works)
    for (int i = 0; i < numOfPoints; i++){
        ids[i] = records[i].id;
        xValues[i] = records[i].xVal;
        yValues[i] = records[i].yVal;
    }
    

    //smallest values
    float smallestX = minimum(xValues,numOfPoints);
    float smallestY = minimum(yValues,numOfPoints);
    
    //largest values
    float largestX = largest(xValues,numOfPoints);
    float largestY = largest(yValues,numOfPoints);
   
    //average values
    float averageX = average(xValues,numOfPoints);
    float averageY = average(yValues,numOfPoints);
    
    int* blank1, blank2;
    double* blank3;
    //finding closest points and store them in the struct we created
    findClosest(records, SDP, numOfPoints, blank1, blank2, blank3 );

    float distanceRAND = tourDistance(records, numOfPoints);

    printf("x: avg %.2f, min %.2f, max %.2f\n", averageX, smallestX, largestX);
    printf("y: avg %.2f, min %.2f, max %.2f\n", averageY, smallestY, largestY);
    printf("complete tour distance = %.2f\n", distanceRAND);
    printf("id %d and id %d are closest, distance = %.2f\n", SDP[0].idFistPoint, SDP[0].idSecondPoint, SDP[0].distance);


    //if we have ids of the two points 
    if ( argc > 2){
        int id1 = atoi(argv[1]);
        int id2 = atoi(argv[2]);
        int id1Pos = -9;
        int id2Pos = -9;

        //loading up the values into the arrays for further calculations 
        for (int i = 0; i < numOfPoints; i++){
            records[i].id = ids[i];
        }

        for (int i = 0; i < numOfPoints; i++){
            if (records[i].id == id1){
                id1Pos = i;
            }
            if (id2 == records[i].id){
                id2Pos = i;
            }
        }

        if (id1Pos == -9 || id2Pos == -9){
            printf("ERROR: invalid path ids!\n");
            return 0;
        }
        
        printf("partial tour from id %d to %d\n", id1, id2);

        double hello;
        double distanceTEMP;

        if (id2Pos > id1Pos){

            for(int i = id1Pos; i < id2Pos; i++){
                double distanceTEMP = distanceBetween(records[i], records[i+1]);
                hello += distanceBetween(records[i], records[i+1]);
                printf("from id %d to %d, distance = %.2f\n", records[i].id, records[i+1].id, distanceTEMP);
            }
        }

        if (id1Pos > id2Pos){

            int i;
            for ( i =id1Pos; i < numOfPoints + id1Pos -1 ; i++){
                if ( (i%numOfPoints) == numOfPoints-1){
                    hello += distanceBetween(records[numOfPoints-1], records[0]);
                    printf("from id %d to %d, distance = %.2f\n", records[(numOfPoints-1)].id, records[0].id, distanceTEMP);
                    continue;
                }

                distanceTEMP = distanceBetween(records[(i%numOfPoints)], records[(i%numOfPoints)+1]);
                hello += distanceBetween(records[(i%numOfPoints)], records[(i%numOfPoints)+1]);
                printf("from id %d to %d, distance = %.2f\n", records[(i%numOfPoints)].id, records[(i%numOfPoints)+1].id, distanceTEMP);
            }
            
        }

        // if(id1 == id2){
        //     printf("partial tour distance = 0.00\n");
        //     return 0;
        // }

        printf("partial tour distance = %.2f\n", hello);

    }

    free(records); //freeing the allocated memory 
    free(SDP); //freeing the allocated memory 

    printf("\n"); //good practice #1
    return 0; //good practice #2
}
