#pragma once
#include <string>

#define TM_DEFAULT_LOCATION "Town"

namespace TMLib 
{
	const int TM_LocationCount = 2;

	const std::string TM_LocationNames[] = {
		"Town",
		"Temple"
	};


	/*
		A class of a single location
	*/
	class TM_Location
	{
	public:
								TM_Location(const char* name);
								~TM_Location();
		const std::string&		GetName() const;	
		//friend bool				operator==(const TM_Location& loc1, const TM_Location& loc2);
	private:
		std::string				mName;
	};

};
