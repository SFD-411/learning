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
#include <iterator>
#include <map>
#include <vector>
#include <cmath>

int solution = 0;
int shape_size = 20;
std::vector<std::vector<int>> mappings;

void checkVals(std::vector<int> &sample){
  bool match = false;
  do{
    for(auto test : mappings){
      int checker = 0;
      for (int offset = 0; offset < shape_size; offset++){
        int matcher = 0;
        int inverter = 0;
        for (int stepper = 0; stepper < shape_size; stepper++){
          if (sample[stepper] == test[(offset + stepper) % shape_size]){
            matcher++;
          }
          if (sample[stepper] == test[int(sqrt(pow(double(offset + (shape_size - stepper)), double(2))))  % shape_size]){
            inverter++;
          }
        }
        if(matcher == shape_size || inverter == shape_size){
          match = true;
          break;
        }
      }
      if(match == true){ break; }
    }
    if(match == false){
      solution++;
      mappings.push_back(sample);
      match = true;
      std :: cout << solution << "\t";
      for(auto n : sample){
        std::cout << n;
      }
      std::cout << "\n";
    }
  }while(match == false);
}

int main(){
  int sequence = 0;
  int counter = shape_size;
  std::vector<int> shape;

  counter--;
  // std::cout << "VALUE\tBINARY\t  NEXT BIT MODIFIED\n";

  for(int ass = 0; ass < shape_size; ass++){
    shape.push_back(0);
  }

  solution++;
  std :: cout << solution << "\t";
  for(auto n : shape){
    std::cout << n;
  }
  std::cout << "\n";

  mappings.push_back(shape);


  while(counter >= 0){
    checkVals(shape);
      // find the left most 0
      while(shape[counter] == 1){              // while the digit is 1
          counter--;                               // move the cursor left
      }

      if (shape[counter] == 0 && counter > -1){                   // if the digit is zero
          if (counter == shape_size){                   // if it is in the first position
              shape[counter] = 1;                              // turn it into a one
              counter--;                                       // and move the counter left
          }                                                  // now try again
          else {                                        // if the zero is not in the first position
              shape[counter] = 1;                               // turn it into a one
              while(counter < shape_size - 1){                        // iterate back to the first position
                  counter++;
                  shape[counter] = 0;                             // turning all the values into 0
              }
          }
      }
  }

/*  for(auto n : mappings){
        std::cout << sequence << "\t";
        for (auto m : n){
            std::cout << m;
        }
        std::cout << "\n";
    }
*/

    return 0;
}
