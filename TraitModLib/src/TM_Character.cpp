#include "TM_Character.h"
#include "TM_Map.h"

namespace TMLib
	{
	TM_Character::TM_Character() : mName(""), mLocation(TM_Map::GetMap().GetLocation(TM_DEFAULT_LOCATION))
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

	void TM_Character::SetLocation(const char* loc)
	{
		mLocation = TM_Map::GetMap().GetLocation(loc);
	}

	const std::map<std::string,int>& TM_Character::GetTraits() const
	{
		return mTraits;
	}

	const std::string& TM_Character::GetName() const
	{
		return mName.c_str();
	}

	int	TM_Character::GetTrait(const char* trait) const
	{
		return mTraits.find(trait)->second;
	}

	std::shared_ptr<TM_Location> TM_Character::GetLocation() const
	{
		return mLocation;
	}
};
