#pragma once
#include <string>

/*
Each trait:										Example:
- has a name:									Bravery
- be "2-sided":									brave-coward
- have a scale between sides (-1000 : 1000):	-1000 - coward, 1000 - brave
Initialisation sets up the names of a trait and sides. A scale sets to zero.
*/

const unsigned int TM_TraitCount = 2;
const std::string TM_TraitNames[] = {
	"bravery",
	"industry"
};
const std::string TM_TraitPositiveSides[] = 
{
	"brave",
	"industrious"
};
const std::string TM_TraitNegativeSides[] = 
{
	"coward",
	"lazy"
};
