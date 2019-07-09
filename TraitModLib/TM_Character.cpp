#include "TM_Character.h"

TM_Character::TM_Character() : mName("")
{
	for(int t = 0; t < TM_TraitCount; t++)
		mTraits[TM_TraitNames[t]] = 0;
}

TM_Character::~TM_Character()
{
}

void TM_Character::SetTraits(const std::map<std::string,int> &traits)
{
	mTraits = traits;
}

void TM_Character::SetTrait(const char* trait, const int value)
{
	mTraits[trait] = value;
}

void TM_Character::SetName(const char* name)
{
	mName = name;
}

const std::map<std::string,int>& TM_Character::GetTraits() const
{
	return mTraits;
}

const char* TM_Character::GetName() const
{
	return mName.c_str();
}

int	TM_Character::GetTrait(const char* trait) const
{
	return mTraits.find(trait)->second;
}
