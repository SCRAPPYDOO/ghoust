#include "stdafx.h"
#include "Logger.h"
#include <string>
#include <iostream>

using namespace std;
using namespace std::chrono;

Logger::Logger()
{
}


Logger::~Logger()
{
}

void Logger::log(string log)
{
	cout << "Today: "  << log << endl;
}
