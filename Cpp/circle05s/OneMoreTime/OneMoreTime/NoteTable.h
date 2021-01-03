#pragma once

#include <cstdlib>
#include <iostream>	
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "Positions.h"

#define HASH_H

// takes in notes per position value
class noteindex
{
public:
	noteindex();
	
	const void NotePosition(std::string Note, std::string Position, int pos); // sets the initial data of the notes
	void PrintIndices(int index); // returns filled containers
	void FindNote(std::string); // returns the note info

private:
	static const int TABLE_SIZE = 12;

	struct index
	{
		int pos;
		std::string position; // sets the position of the table
		std::string name; // stores the notes name

		std::string degree; // takes the degree of an active note
		std::string value; // returns the value of the note degree

		bool enharmonic;
		bool tonic; // if note is first
		bool active;
		index* next;
	};
	index* NoteTable[TABLE_SIZE]; // stores notes in fifths incriments
};