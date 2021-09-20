#pragma once
#include "core.h"
#include <map>
#include "getopt.h"
#include "entity.h"
#include "JsonSources.h"

using namespace std;
using json = nlohmann::json;

json get_component_groups_from_input();
int process_component_group(string family, string name, int spacing);
int create_new_entity(int spacing);
int create_new_item(int spacing, int stack_size);
int create_batch_funcs(int count, string name);
int create_anim_function(string name);
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