/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description: I'm is Gonna SOLVER IT 
 * 
 *        Version:  1.0
 *        Created:  11/07/20 17:35:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (SFD), 
 *   Organization:  STEM POTD
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <map>

void ShapeStepper(bool shape[], int counter, int overloaded){
    // prints out the current state of the values
    for(int position = 0; position < overloaded; position++){
       std::cout << shape[position];
    }
    std::cout << "\n";

    if (shape[counter] == 0){                   // if the digit is zero
        if (counter == overloaded){                       // if it is in the first position
            shape[counter] == 1;                              // turn it into a one
            counter--;                                        // move the counter left
        }                                                     // start over
        else {                                            // if the zero is not in the first position
            shape[counter] = 1;                               // turn it into a one
            while(counter < overloaded){                        // iterate back to the first position
                counter++;                                 
                shape[counter] = 0;                             // turning all the values into 0
            }
        }
    } else if (shape[counter] == 1){            // else it is a one
        while (shape[counter] != 0){
            counter--;                                    // decriment the counter until you find a zero
        }
    }    
    
    // until all of the values are 1 run this loop
    if (shape[0] == 0 || 
        shape[1] == 0 ||
        shape[2] == 0 ||
        shape[3] == 0){
            ShapeStepper(shape, counter, overloaded);
    }
}


int main(){
    //    int point_counter, position_counter;
    const int shape_size = 4;                                                    // number of points on a polygon
    bool shape[shape_size];                                                // true/false statements represent on/off state of points
    
    ShapeStepper(shape, shape_size, shape_size);


    return 0;
}

