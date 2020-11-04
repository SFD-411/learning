#pragma once

#include "NoteTable.h"
#include <cstdlib>
#include <iostream>	
#include <map>
#include <sstream>
#include <string>
#include <vector>

noteindex::noteindex()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		NoteTable[i] = new index;
		NoteTable[i]->position = "na"; // constant position
		NoteTable[i]->name = "na"; // proper note
		NoteTable[i]->degree = "na"; // input values
		NoteTable[i]->value = "na"; // output properly defined numerals
		NoteTable[i]->enharmonic = false; // theoretical
		NoteTable[i]->tonic = false; // root
		NoteTable[i]->active = false; // in the scale
		NoteTable[i]->next = NULL;
	}
}

// assigns initial positions and notes data
const void noteindex::NotePosition(std::string Note, std::string Position, int pos)
{
	// if there is no note - set note and position to index pos
	if (NoteTable[pos]->position == "na") 
	{
		if (Position == "P1")
		{	NoteTable[pos]->tonic = true;	}
		NoteTable[pos]->pos = pos;
		NoteTable[pos]->name = Note;
		NoteTable[pos]->position = Position;
	}
	else  // set a new note to the same position
	{
		index* ptr = NoteTable[pos];
		index* n = new index;
		n->pos = pos;
		n->name = Note;
		n->position = Position;
		n->enharmonic = true;
		n->next = NULL;
		while (ptr->next != NULL)
		{	ptr = ptr->next;	}
		ptr->next = n;
	}
}

void noteindex::PrintIndices(int i)
{
	index* Ptr = NoteTable[i];
	if (Ptr->name == "na")
	{
		std::cout << " - // bucket #" << i << " is empty.\n";
	}
	else
	{
		while (Ptr != NULL)
		{
			std::cout << "\t||----||\t";
			std::cout << Ptr->pos << " - " << Ptr->position << " - " << Ptr->name;
			std::cout << "\t\t||----||\t" << std::endl;
			Ptr = Ptr->next;
		}
	}
}

void noteindex::FindNote(std::string)
{
	return;
}