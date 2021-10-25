#pragma once
#include "core.h"
#include <map>
#include "getopt.h"
#include "entity.h"
#include "JsonSources.h"
#include "file_manager.hpp"
#include "utilities.hpp"
#include "directory_handler.h"
#include "uuid.h"

using namespace std;
using json = nlohmann::json;

void show_usage(const string& command);
int create_component_group(const string& family, const string& name, const int& spacing);
int remove_component_group(const string& family, const string& name, const int& spacing);
int create_components(const string& family, const string& name, const int& spacing);
int remove_components(const string& family, const string& name, const int& spacing);
int create_new_entity(const int& spacing);
int create_new_item(const int& spacing, const int& stack_size);
int create_new_block(const int& spacing);
int create_batch_funcs(const int& count, string& name);
int create_animation_controller(string& name);
int create_animation(string& name, string& query);
int create_functions_from_strings(const vector<string>& commands, const vector<string>& names);
int create_skin_pack(const string& name);
int create_manifest();
void abort_program(const string& message);

enum CommandList
{
    eNULL,
    eRDIR,
    eBDIR,
    eCOGR,
    eCOMP,
    eNENT,
    eNITM,
    eNMAN,
    eNBLK,
    eFUNC,
    eAFUNC,
    eACFUNC,
    eSKIN
};

const char* prog_name;

static std::map < string, CommandList > mapCommandList;