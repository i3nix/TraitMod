#pragma once

#include "TM_Database.h"
#include "TM_Character.h"

class TM_CharacterDatabase : public TM_Database
{
public:
								TM_CharacterDatabase();
								~TM_CharacterDatabase();
	void						CreateCharacter(const char* name);
	void						ChangeCharacter(const TM_Character &character);
	void						DeleteCharacter(const char* name);
	const TM_Character&			GetCharacter(const char* name);
private:
};
