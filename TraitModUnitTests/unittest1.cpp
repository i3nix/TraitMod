#include "stdafx.h"
#include "CppUnitTest.h"
#include "../TraitModLib/TM_CharacterDatabase.h"
#include "../TraitModLib/TM_Exception.h"
#include "../TraitModLib/TM_Map.h"
#include "../TraitModLib/TM_FileLogger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TMLib;

namespace TraitModUnitTests
{		
	TEST_CLASS(TraitModLibTestClass)
	{
	public:
		
		TEST_METHOD(CharacterDatabaseTest)
		{
			try
			{
				TM_CharacterDatabase db;
				db.Connect(TM_DEFAULT_MYSQL_HOST,TM_DEFAULT_MYSQL_PORT,TM_DEFAULT_MYSQL_LOGIN,TM_DEFAULT_MYSQL_PASSWORD);
				db.SetDatabase(TM_DEFAULT_CHARACTER_DATABASE);
				db.SetTable(TM_DEFAULT_CHARACTER_TABLE);
			}
			catch(TM_Exception e)
			{
				wchar_t err[100];
				mbtowc(err,e.GetError().c_str(),e.GetError().length() + 1);
				Assert::Fail(err);
			}
		}
		TEST_METHOD(MapTest)
		{
			TM_Map map;
			map.AddLocation("loc1");
			map.AddLocation("loc2");
			map.AddLocation("loc3");
			map.AddLocation("loc4");
			map.AddRoad("loc4","loc2",3);
			map.AddRoad("loc4","loc3",5);
			map.AddRoad("loc4","loc1",9);
			map.AddRoad("loc2","loc3",1);
			map.AddRoad("loc3","loc1",2);
			std::list<std::shared_ptr<TM_Location> > path = map.FindPath("loc1","loc4");
			int ans = 6;
			int cur = -1;
			std::shared_ptr<TM_Location> prev;
			for(std::list<std::shared_ptr<TM_Location> >::iterator it = path.begin(); it != path.end(); it++)
			{
				if(cur == -1)
					cur = 0;
				else 
					cur += map.GetDistance(prev->GetName().c_str(),(*it)->GetName().c_str());
				prev = *it;
			}
			Assert::AreEqual(ans,cur);
		}
	};
}