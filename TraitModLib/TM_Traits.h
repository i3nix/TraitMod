#pragma once
#include <string>

/*
Each trait:										Example:
- has a name:									Bravery
- be "2-sided":									brave-coward
- have a scale between sides (-1000 : 1000):	-1000 - coward, 1000 - brave
Initialisation sets up the names of a trait and sides. A scale sets to zero.
*/
const unsigned int TM_TraitCount = 1;
const std::string TM_TraitNames[] = {
	"bravery"
};

class TM_Trait
{
public:
	TM_Trait();
	~TM_Trait();

	//Creates a new trait
	void Create(std::string name, std::string side1, std::string side2);
	//Loads an existing trait
	void Load(std::string name);
private:
	std::string mName;
	std::string mSide1;
	std::string mSide2;
	int			mScale;
};
