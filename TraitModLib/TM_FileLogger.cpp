#include "TM_FileLogger.h"
#include "TM_Exception.h"

namespace TMLib
{
	TM_FileLogger::TM_FileLogger(const char* path) : mFile()
	{
		mFile.open(path,std::ofstream::out | std::ofstream::app);
	}

	TM_FileLogger::~TM_FileLogger()
	{
	}

	TM_ILogger& TM_FileLogger::operator<<(const char* str)
	{
		mFile << str;
		return *this;
	}

	TM_ILogger& TM_FileLogger::operator<<(const int value)
	{
		mFile << value;
		return *this;
	}
};
