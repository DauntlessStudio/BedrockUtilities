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

int create_component_group(string family, string name, int spacing);
int remove_component_group(string family, string name, int spacing);
int create_components(string family, string name, int spacing);
int remove_components(string family, string name, int spacing);
int create_new_entity(int spacing);
int create_new_item(int spacing, int stack_size);
int create_batch_funcs(int count, string name);
int create_animation_controller_function(string name);
int create_animation_function(string name);
int create_manifest();
int abort_program(string message);

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
    eACFUNC
};

const char* prog_name;

static std::map < string, CommandList > mapCommandList;