#pragma once
#include <map>
#include "TM_Traits.h"


namespace TMLib
{
	/*
		This class holds an information about a single character
	*/
	class TM_Character
	{
	public:
											TM_Character();
											~TM_Character();

		void								SetTraits(const std::map<std::string,int> &traits);
		void								SetTrait(const char* trait, const int value);
		void								SetName(const char* name);

		const std::map<std::string,int>&	GetTraits() const;
		int									GetTrait(const char* trait) const;
		const char*							GetName() const;
	private:
		std::map<std::string,int>			mTraits;
		std::string							mName;
	};
};