#include <iostream>

#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>

int main()
{
	plog::init(plog::debug, "logging.csv", 10000, 10);
	return 0;
}
