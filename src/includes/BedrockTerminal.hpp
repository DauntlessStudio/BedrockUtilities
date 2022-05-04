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
void get_entities(const string& family, const string& name, const string& dir_name);
void write_entities_to_files();
int create_component_group();
int remove_component_group();
int create_components();
int remove_components();
int create_new_entity(const int& spacing);
int create_new_item(const int& spacing, const int& stack_size);
int create_new_block(const int& spacing);
int create_batch_funcs(const int& count, string& name);
int create_animation_controller();
int create_animation(string& query);
int create_functions_from_strings(const vector<string>& commands);
int create_skin_pack(const string& name);
int create_manifest();
int add_to_damage_sensors(const bool& include_groups);
int temp_mod();
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
    eSKIN,
    eDMGS,
    eTEMP
};

const char* prog_name;
vector<bedrock::entity> entities;
int indent = 4;

static std::map < string, CommandList > mapCommandList;