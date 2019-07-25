#include "TM_CharacterDatabase.h"
#include "TM_ConsoleLogger.h"

using namespace TMLib;
using namespace std;

int main()
{
	TM_CharacterDatabase db(TM_ConsoleLogger::Get());
	db.Connect(TM_DEFAULT_MYSQL_HOST,TM_DEFAULT_MYSQL_PORT,TM_DEFAULT_MYSQL_LOGIN,TM_DEFAULT_MYSQL_PASSWORD);
	db.SetDatabase(TM_DEFAULT_CHARACTER_DATABASE);
	db.SetTable(TM_DEFAULT_CHARACTER_TABLE);
	return 0;
}
