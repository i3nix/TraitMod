#pragma once
#include <fstream>

#include "TM_ILogger.h"

namespace TMLib
{
	/*
		A class for logging into a file
	*/
	class TM_FileLogger : public TM_ILogger
	{
	public:
								TM_FileLogger(const char* path);
								~TM_FileLogger();
		TM_ILogger&				operator<<(const char* str);
		TM_ILogger&				operator<<(const int value);
	private:
		std::ofstream mFile;
	};
};
