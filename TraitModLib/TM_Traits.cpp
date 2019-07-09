/*
TODO:
- using database;
*/

#include "TM_Traits.h"

TM_Trait::TM_Trait() : mName(""), mSide1(""), mSide2(""), mScale(0) {}

TM_Trait::~TM_Trait() {}

void TM_Trait::Create(std::string name, std::string side1, std::string side2)
{
	mName = name;
	mSide1 = side1;
	mSide2 = side2;
	mScale = 0;
}

void TM_Trait::Load(std::string name)
{
	//
}
