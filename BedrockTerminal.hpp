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
int create_components(string family, string name, int spacing);
int create_new_entity(int spacing);
int create_new_item(int spacing, int stack_size);
int create_batch_funcs(int count, string name);
int create_anim_function(string name);
int create_manifest();

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
    eAFUNC
};

const char* prog_name;

static std::map < string, CommandList > mapCommandList;