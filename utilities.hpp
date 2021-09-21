#pragma once
#include "core.h"
#include <limits>

using namespace std;

string format_name(string name);

void replace_all(std::string& str, const std::string& from, const std::string& to);

string read_multiline_input();