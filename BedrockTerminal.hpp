#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "getopt.h"
#include "json.hpp"
#include "JsonSources.h"
#include "directory_handler.h"
#include "file_manager.hpp"

#ifdef _WIN32
#define LINE_GREEN ""
#define LINE_RESET ""
#else
#define LINE_GREEN "\033[32m"
#define LINE_RESET "\033[0m"
#endif

using namespace std;
using json = nlohmann::json;

json get_component_groups_from_input();
int add_groups_to_entity(const json& groups, nlohmann::ordered_json& entity);
bool does_entity_contain_family(string family, json entity);
int process_component_group(string family, string name, int spacing);
int create_new_entity(int spacing);
int create_new_item(int spacing, int stack_size);
int create_batch_funcs(int count, string name);
int create_anim_function(string name);
int add_animation_controller(nlohmann::ordered_json& entity, const string anim_name, const string query, const string exit_query, const string entry_line);
string format_name(string name);
void replace_all(std::string& str, const std::string& from, const std::string& to);

enum CommandList
{
    eNULL,
    eRDIR,
    eBDIR,
    eCOGR,
    eNENT,
    eNITM,
    eNBLK,
    eFUNC,
    eAFUNC
};

const char* prog_name;

static std::map < string, CommandList > mapCommandList;