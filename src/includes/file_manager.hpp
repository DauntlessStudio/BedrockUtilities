#pragma once
#include "core.h"
#include <iomanip>
#include "lodepng.h"
#include "directory_handler.h"
#include "utilities.hpp"

using namespace std;

namespace bedrock
{
	class entity;
}

int write_json_to_file(const nlohmann::ordered_json &object, string path, int spacing = 2);
int read_json_from_file(nlohmann::ordered_json &object, string path, string error_message);
nlohmann::ordered_json read_json_from_input(string input_message, string error_message, bool abort_on_fail = false);
int overwrite_txt_file(string path, string entry);
int append_txt_file(string path, string entry);
bool copy_file(const char* SRC, const char* DEST);
void write_texture_to_file(vector<unsigned char> png, string path, int width = 16, int height = 16);
vector<bedrock::entity> get_bp_entities(string name, string family, string dir_name = "");