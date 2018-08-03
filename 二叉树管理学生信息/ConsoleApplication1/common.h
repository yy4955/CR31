#pragma once
#include <sstream>
#ifdef _DEBUG 
#define OUTPUTDBG(STR, STRERROR) \
	std::stringstream sstream; \
	sstream << __FILE__ << " " << __LINE__ << ": "; \
	sstream << STR; \
	std::getline(sstream, STRERROR); 
#else
#define OUTPUTDBG(STR, STRERROR) \
	std::stringstream sstream; \
	sstream << STR; \
	std::getline(sstream, STRERROR);
#endif