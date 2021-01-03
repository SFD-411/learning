/*
 * =====================================================================================
 *
 *       Filename:  word.cpp
 *
 *    Description: Word Search program 
 *
 *        Version:  1.0
 *        Created:  09/27/20 05:23:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string>

const std::string words[14] = { 
    "Hyper",
    "Religion",
    "Stereotype",
    "Wicked", // 
    "Belief", //
    "Hypocrite",
    "Purist", //
    "Stupidity",
    "Wordsearch", //
    "Maths", //
    "Whatever",//
    "Bullshit",
    "Humanity",
    "Control" //
};

const char grid[121] = {
    'W', 'G', 'C', 'A', 'P', 'K', 'I', 'Y', 'F', 'G', 'J', 
    'H', 'O', 'E', 'Y', 'U', 'T', 'F', 'K', 'M', 'N', 'B', 
    'A', 'Y', 'R', 'M', 'R', 'J', 'K', 'F', 'L', 'T', 'X', 
    'T', 'T', 'E', 'D', 'I', 'D', 'F', 'E', 'O', 'B', 'C', 
    'E', 'F', 'G', 'E', 'S', 'B', 'J', 'I', 'R', 'U', 'Y', 
    'V', 'N', 'H', 'K', 'T', 'E', 'R', 'G', 'T', 'E', 'V', 
    'E', 'X', 'S', 'C', 'E', 'L', 'A', 'G', 'N', 'B', 'H', 
    'R', 'B', 'D', 'I', 'F', 'I', 'S', 'R', 'O', 'R', 'H', 
    'X', 'B', 'E', 'W', 'T', 'E', 'H', 'D', 'C', 'M', 'B', 
    'I', 'U', 'O', 'P', 'L', 'F', 'M', 'A', 'T', 'H', 'S',
    'K', 'T', 'H', 'J', 'Y', 'R', 'F', 'G', 'H', 'R', 'F'
};

int main(){
  for(auto key : words){ // iterate through list of words
      int angul = 0;
      int verti = 0;
      int horiz = 0;
      for(auto letters = 0; letters < 11 - key.length(); letters++){ // iterate the height and width of the grid minus length of word
          for(for index = 0; index < key.length(); index++) { // iterate through letters in word
               if (grid[index + letters] == key[index + letters]){
                   horiz++;
               }
               if ()
          }
      }
  }
}
