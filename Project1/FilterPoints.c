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
* Program that makes sure we don't have points with the same id's
*/

//making struct because why else did i even learn them?
typedef struct{
    int id;
    float xVal;
    float yVal;
}Record;



int main(){

    Record* records; //assinging place to store the values 
    
    int numOfPoints; //number of points we have at the beggining of the file 
    scanf("%d", &numOfPoints); // scanning number of points 

    records = malloc(numOfPoints * sizeof *records); // allocating memory for our struct 

    int x; // counter 
    for(x = 0; x < numOfPoints; x++){
        scanf("%d", &records[x].id); // scan the id and stores it at Record struct
        
        scanf("%f", &records[x].xVal); // scan the x Value and stores it at Record struct

        scanf("%f", &records[x].yVal);// scan the y Value and stores it at Record struct
    }


    //loop to go through the array and delete the elements 
    for(int i=0; i<numOfPoints; i++)
    {
        for(int j=i+1; j<numOfPoints; j++)
        {
            //if we found any duplicates
            if(records[i].id == records[j].id)
            {
                //delete the duplicated element and shift everything back 
                for(int k=j; k < numOfPoints - 1; k++)
                {
                    records[k].id = records[k+1].id;
                }

                //removing number of points left 
                numOfPoints--;

                //if we shift elements, we don't move the coursor of the comparison 
                j--;
            }
        }
    }

    //final printing the nodes that left 
    printf("%d\n", numOfPoints);
    for(int i = 0; i < numOfPoints; i++)  {
        printf("%d %.2f %.2f\n", records[i].id, records[i].xVal, records[i].yVal);
    }
    
    free(records); //freeing the allocated memory 

    printf("\n"); //good practice #1
    return 0; //good practice #2
}
