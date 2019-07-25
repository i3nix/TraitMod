#pragma once

namespace TMLib
{
	/*
		An interface for output information
	*/
	class TM_ILogger
	{
	public:
		virtual TM_ILogger&	operator<<(const char* str) = 0;
		virtual TM_ILogger&	operator<<(const int value) = 0;
	};
};
