#pragma once

#include "NoteLibrary.h"
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
		NoteTable[i]->name = "na"; // note
		NoteTable[i]->value = "na"; // output
		NoteTable[i]->degree = "na"; // input
		NoteTable[i]->mode = "na"; // pivot
		NoteTable[i]->step = 0; // position value
		NoteTable[i]->enharmonic = false; // theoretical
		NoteTable[i]->tonic = false; // root
		NoteTable[i]->active = false; // in the scale
		NoteTable[i]->next = NULL;
	}
}

void noteindex::SetNote(std::string, int)
{
	return;
}

void noteindex::FindNote(std::string)
{
	return;
}
