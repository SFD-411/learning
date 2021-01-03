#pragma once

#include <cstdlib>
#include <iostream>	
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "Positions.h"

#define HASH_H

// takes in notes per fifths indexing
class noteindex
{
public:
	noteindex();
	
	void SetNote(std::string, int); // sets the name data of the note
	void FindNote(std::string); // returns the note info

private:
	intervals modes;
	static const int TABLE_SIZE = 12;
	struct index
	{
		std::string name; // takes the note name
		std::string degree; // takes the degree
		std::string mode; // finds the position of a note
		std::string value; // finds the value of the note degree

		int step; // takes the index of active notes
		bool enharmonic;
		bool tonic; // if note is first
		bool active;
		index* next;
	};
	index* NoteTable[TABLE_SIZE]; // stores notes in fifths incriments
};