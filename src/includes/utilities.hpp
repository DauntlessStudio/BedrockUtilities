#pragma once
#include "core.h"
#include <limits>
#include <sstream>

using namespace std;

string format_name(const string& name);

void replace_all(std::string& str, const std::string& from, const std::string& to);

string read_multiline_input();

string space_camel_case(const string& ref);

vector<string> get_substrings(const string& ref, const char& deliminator);

float round_second(float var);