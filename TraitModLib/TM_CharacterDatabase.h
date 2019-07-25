#pragma once


#include "TM_Database.h"
#include "TM_Character.h"

#define TM_DEFAULT_CHARACTER_DATABASE "TraitModDatabase"
#define TM_DEFAULT_CHARACTER_TABLE "TM_Characters"

namespace TMLib
{
	/*
	This class accesses the table of characters in MySQL database
	*/
	class TM_CharacterDatabase : public TM_Database
	{
	public:
									TM_CharacterDatabase(TM_ILogger& logger);
									~TM_CharacterDatabase();
		void						CreateCharacter(const char* name);
		void						ChangeCharacter(const TM_Character &character);
		void						DeleteCharacter(const char* name);
		TM_Character*				GetCharacter(const char* name);
	private:
	};
};