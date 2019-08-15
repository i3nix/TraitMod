#pragma once
#include <iostream>

#include "TM_ILogger.h"

namespace TMLib
{
	/*
		A class for logging into a console
	*/
	class TM_ConsoleLogger : public TM_ILogger
	{
	public:
									TM_ConsoleLogger();
									~TM_ConsoleLogger();
		TM_ILogger&					operator<<(const char* str);
		TM_ILogger&					operator<<(const int value);
		//Returns a reference to a static TM_ConsoleLogger
		static TM_ConsoleLogger&	GetDefaultLogger();
	private:
		static TM_ConsoleLogger		mCLogger;
	};
};
