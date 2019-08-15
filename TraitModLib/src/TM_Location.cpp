#include "TM_Location.h"

namespace TMLib
{
	TM_Location::TM_Location(const char* name) : mName(name)
	{
	}

	TM_Location::~TM_Location()
	{
	}

	const std::string& TM_Location::GetName() const
	{
		return mName;
	}
	/*
	bool operator==(const TM_Location& loc1, const TM_Location& loc2)
	{
		return (loc1.mName == loc2.mName);
	}*/
};
