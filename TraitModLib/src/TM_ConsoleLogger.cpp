#include "TM_ConsoleLogger.h"
#include "TM_Exception.h"

namespace TMLib
{
	TM_ConsoleLogger::TM_ConsoleLogger()
	{
	}

	TM_ConsoleLogger::~TM_ConsoleLogger()
	{
	}
	
	TM_ILogger& TM_ConsoleLogger::operator<<(const char* str)
	{
		std::cout << str;
		return *this;
	}

	TM_ILogger& TM_ConsoleLogger::operator<<(const int value)
	{
		std::cout << value;
		return *this;
	}

	TM_ConsoleLogger& TM_ConsoleLogger::GetDefaultLogger()
	{
		return mCLogger;
	}

	TM_ConsoleLogger TM_ConsoleLogger::mCLogger = TM_ConsoleLogger();
};
