#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "json.hpp"

#ifdef _WIN32
#define LINE_GREEN ""
#define LINE_RESET ""
#else
#define LINE_GREEN "\033[32m"
#define LINE_RESET "\033[0m"
#endif