/*
TODO:
CreateCharacter() - maybe possible to make better insert(...)
*/

#include "TM_CharacterDatabase.h"
#include "TM_Traits.h"

TM_CharacterDatabase::TM_CharacterDatabase()
{
	try{
		Connect(TM_DEFAULT_MYSQL_HOST,TM_DEFAULT_MYSQL_PORT,TM_DEFAULT_MYSQL_LOGIN,TM_DEFAULT_MYSQL_PASSWORD);
		SetDatabase("TraitModDatabase");
		SetTable("TM_Characters");
	}
	catch(mysqlx::Error e)
	{
		throw e.what();
	}
}

TM_CharacterDatabase::~TM_CharacterDatabase()
{
}

void TM_CharacterDatabase::CreateCharacter(const char* name)
{
	try{
		mTable->insert("name","bravery").values(name, 0).execute();
	}
	catch(mysqlx::Error e)
	{
		throw e.what();
	}
}

void TM_CharacterDatabase::ChangeCharacter(const TM_Character &character)
{
	try{
		for(int t = 0; t < TM_TraitCount; t++)
			mTable->update().set(TM_TraitNames[t], character.GetTrait(TM_TraitNames[t].c_str())).where("name like :name").bind("name",character.GetName()).execute();
	}
	catch(mysqlx::Error e)
	{
		throw e.what();
	}
}

void TM_CharacterDatabase::DeleteCharacter(const char* name)
{
	try{
		mTable->remove().where("name like :name").bind("name",name).execute();
	}
	catch(mysqlx::Error e)
	{
		throw e.what();
	}
}

const TM_Character& TM_CharacterDatabase::GetCharacter(const char* name)
{
	try{
		TM_Character character;
		std::map<std::string,int> traits;
		mysqlx::RowResult res = mTable->select().where("name like :name").bind("name",name).execute();
		for(int t = 0; t < TM_TraitCount; t++)
		{
			mysqlx::Row x = res.fetchOne();
			traits[TM_TraitNames[t]] = x[t + 2];
		}
		character.SetTraits(traits);
		character.SetName(name);
		return character;
	}
	catch(mysqlx::Error e)
	{
		throw e.what();
	}
}
