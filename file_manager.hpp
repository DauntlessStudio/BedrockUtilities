#pragma once
#include <fstream>
#include <string>
#include <iomanip>
#include "directory_handler.h"
#include "json.hpp"
#include "lodepng.h"

using namespace std;

int write_json_to_file(const nlohmann::ordered_json& entity, string path, int spacing = 2);
int overwrite_txt_file(string path, string entry);
int append_txt_file(string path, string entry);
bool copy_file(const char* SRC, const char* DEST);
void write_texture_to_file(vector<unsigned char> png, string path, int width = 16, int height = 16);