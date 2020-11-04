#pragma once

#include "Positions.h"
#include "NoteTable.h"

int notes::posNumber(std::string pos)
{
	return PositionNUM[pos];
}

// creates all keys of music based on fifths, fourths and C Major in four note groups
//		with each key assigned a Position i.e. "P1-M7"
void notes::populateKeys(std::vector<std::string> scale)
{
	{
		// assign C Major Scale root and position
		root.root = scale[0];
		root.position = POSITION[P1];

		// assigns C Major scale
		for (auto i : scale)
		{
			root.scale.push_back(i);
		}
		root.scale.push_back(scale[P1]);

		// creates sharps keys in fifths through 9 iterations 
		// assigns current and previous scales 4 notes at a time using previous keys
		notecount = 4;
		for (int index = 0; index < 9; index++)
		{
			fifth = (fifth + P5) % P8; // moves fifths counter by 7
			prev = index - 1; // allows access to previous scale

			// assigns root note and position name
			if (index < 2) // assignes initial values from original scale
			{
				sharps[index].root = scale[notecount];
				sharps[index].position = POSITION[fifth];
			}
			else if (index < 8) // assigns initial values from previous assignments
			{
				sharps[index].root = sharps[prev - 1].scale[1];
				sharps[index].position = POSITION[fifth];
			}

			// iterates fifth position due to 5th note
			for (int i = 0; i < 4; i++) // iterates 4 notes per scale
			{
				if (index == 0) // start G Major
				{
					sharps[index].scale.push_back(scale[notecount]); // GABC
					notecount = (notecount + 1) % 7;
				}
				else if (index > 0 && index < 8) // if it isn't the first 4
				{
					if (index == 1) // finishing G Major
					{
						if (i != 2)
						{
							sharps[prev].scale.push_back(scale[notecount]); // DE-G
						}
						else
						{
							sharps[prev].scale.push_back(scale[notecount] + "#"); // --F#-
						}
						notecount = (notecount + 1) % 7;
					}
					else if (index > 1 && index < 8) // inherets previous
					{
						if (i != 2)
						{
							sharps[prev].scale.push_back(sharps[prev - 1].scale[i + 1]); // DE-G
						}
						else // adds sharp to 7th of previous scale
						{
							sharps[prev].scale.push_back(sharps[prev - 1].scale[i + 1] + "#"); //  --F#-
						}
					}
					// next 4 notes from previous
					sharps[index].scale.push_back(sharps[prev].scale[4 + i]);
				}
				else // end of G#
				{
					if (i != 2)
					{
						sharps[prev].scale.push_back(sharps[prev - 1].scale[i + 1]);
					}
					else
					{
						sharps[prev].scale.push_back(sharps[prev - 1].scale[i + 1] + "#");
					}
				}
			}
		}
				
		// creates flat keys in fourths through 9 iterations 
		// assigns current and previous scales 4 notes at a time using previous keys
		notecount = 3;
		for (int index = 0; index < 9; index++)
		{
			fourth = (fourth + P4) % P8; // iterates in 4ths
			prev = index - 1; // allows access to previous key

			// sets root note and position.
			if (index == 0)
			{
				flats[index].root = scale[notecount];
				flats[index].position = POSITION[fourth];
			}
			else if (index < 8)
			{
				flats[index].root = flats[prev].scale[3];
				flats[index].position = POSITION[fourth];
			}
			// iterates fourths position due to 4 notes
			for (int i = 0; i < 4; i++)
			{
				if (index == 0) // start F Major
				{
					if (i != 3)
					{
						flats[index].scale.push_back(scale[notecount]); // FGA
					}
					else
					{
						flats[index].scale.push_back(scale[notecount] + "b"); // ---Bb
					}
					notecount = (notecount + 1) % 7;
				}
				else if (index > 0 && index < 8) // if it isn't the first 4
				{
					if (index == 1) // finishing F Major
					{
						flats[prev].scale.push_back(scale[notecount]); // CDEF

						notecount = (notecount + 1) % 7;
					}
					else if (index > 1 && index < 8) // inherets previous
					{
						flats[prev].scale.push_back(flats[prev - 1].scale[i]);
					}

					// next 4 notes from previous starting on 4
					if (i != 3)
					{
						flats[index].scale.push_back(flats[prev].scale[3 + i]);
					}
					else
					{
						flats[index].scale.push_back(flats[prev].scale[3 + i] + "b"); // add flat
					}
				}
				else // end of Fb
				{
					flats[prev].scale.push_back(flats[prev - 1].scale[i + 1]);
				}
			}
		}
	}
}

// assigns degrees to scales
void notes::scaleDegrees(std::vector<std::string> scale, int key)
{
	for (int j = 0; j < scale.size() - 1; j++)
	{
		if (isSharp)
		{
			sharps[key].scale_degree.insert(std::make_pair(scale[j], DEGREE[j]));
			sharps[key].degree_scale.insert(std::make_pair(DEGREE[j], scale[j]));
		}
		else if (isFlat)
		{
			flats[key].scale_degree.insert(std::make_pair(scale[j], DEGREE[j]));
			flats[key].degree_scale.insert(std::make_pair(DEGREE[j], scale[j]));
		}
		else
		{
			root.scale_degree.insert(std::make_pair(scale[j], DEGREE[j]));
			root.degree_scale.insert(std::make_pair(DEGREE[j], scale[j]));
		}
	}
}