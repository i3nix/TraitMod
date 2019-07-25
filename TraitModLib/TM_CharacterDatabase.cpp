/*
TODO:
*/

#include "TM_CharacterDatabase.h"
#include "TM_Traits.h"
#include "TM_Exception.h"

namespace TMLib
{
	TM_CharacterDatabase::TM_CharacterDatabase(TM_ILogger& logger) : TM_Database(logger)
	{
	}

	TM_CharacterDatabase::~TM_CharacterDatabase()
	{
	}

	void TM_CharacterDatabase::CreateCharacter(const char* name)
	{
		try
		{
			AddRowByString("name",name);
		}
		catch(TM_Exception e)
		{
			e.Add("TM_CharacterDatabase","TM_CharacterDatabase::CreateCharacter");
			throw e;
		}
	}

	void TM_CharacterDatabase::ChangeCharacter(const TM_Character &character)
	{
		try
		{
			for(int t = 0; t < TM_TraitCount; t++)
				ChangeInteger("name",character.GetName(),TM_TraitNames[t].c_str(),character.GetTrait(TM_TraitNames[t].c_str()));
		}
		catch(TM_Exception e)
		{
			e.Add("TM_CharacterDatabase","TM_CharacterDatabase::ChangeCharacter");
			throw e;
		}
	}

	void TM_CharacterDatabase::DeleteCharacter(const char* name)
	{
		try
		{
			RemoveRowByString("name",name);
		}
		catch(TM_Exception e)
		{
			e.Add("TM_CharacterDatabase","TM_CharacterDatabase::DeleteCharacter");
			throw e;
		}
	}

	TM_Character* TM_CharacterDatabase::GetCharacter(const char* name)
	{
		TM_Character* character = new TM_Character();
		std::map<std::string,int> traits;
		try
		{
			for(int t = 0; t < TM_TraitCount; t++)
			{
				traits[TM_TraitNames[t]] = GetInteger("name",name,TM_TraitNames[t].c_str());
			}
		}
		catch(TM_Exception e)
		{
			e.Add("TM_CharacterDatabase","TM_CharacterDatabase::GetCharacter");
			throw e;
		}
		character->SetTraits(traits);
		character->SetName(name);
		return character;
	}
};
