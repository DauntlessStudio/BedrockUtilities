// BedrockTerminal.cpp : This file contains the 'main' function. Program execution begins and ends there.#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "getopt.h"
#include "json.hpp"
#include "DirectoryHandler.h"

using namespace std;
using json = nlohmann::json;

json get_component_groups_from_input();
int write_component_groups(json groups, nlohmann::ordered_json entity, string name, int spacing);

enum CommandList
{
    eRDIR,
    eBDIR,
    eCOGR
};

static std::map < string, CommandList > mapCommandList;

void ShowUsage(string command) {
    //TODO modify function to show usage examples for a passed command name
    std::cout << "Try 'bed -h' for more information" << std::endl;
}

void init_command_list() {
    mapCommandList["rdir"] = eRDIR;
    mapCommandList["bdir"] = eBDIR;
    mapCommandList["cogr"] = eCOGR;
}

int process_component_group(string family, string name, int spacing = 2) {
    if (!name.empty()) {
        //Get file from name
        ifstream i(user_data.behavior_path + "/entities/" + name + ".json");
        if (i.fail()) {
            cerr << user_data.behavior_path + "/entities/" + name + ".json\nThe specified file doesn't exist." << endl;
            return -1;
        }

        //Get an ordered_json copy of the entity to preserve json order
        nlohmann::ordered_json entity;
        i >> entity;
        i.close();
        
        json groups = get_component_groups_from_input();
        write_component_groups(groups, entity, name, spacing);
        }

    return 0;
}

json get_component_groups_from_input() {
    string input;
    std::cout << "New Component Groups:" << endl;
    getline(cin, input);
    input = "{" + input + "}";
    json jo = json::parse(input);
    
    json tmp = jo;
    //Process reset inputs
    for(auto& el: jo.items()) {
        std::cout << "Create Reset For: " << el.key() << "? [y/n]:";
        cin >> input;
        if(input != "y" && input != "Y") {
            continue;
        }

        tmp[el.key() + "_reset"] = el.value();
    }

    return tmp;
}

int write_component_groups(json groups, nlohmann::ordered_json entity, string name, int spacing) {
    //Process resets
    for(auto& el: groups.items()) {
        json tmp;
        for(auto& it: el.value().items()) {
            if(el.key().find("reset") != string::npos){
            tmp.merge_patch(entity["minecraft:entity"]["components"][it.key()]);
            
            if(!tmp.empty()) {
                cout << tmp.dump(4) << endl;
                //groups[el.key()] = tmp;
                }
            }
        }
    }
    
    //Merge component_groups
    entity["minecraft:entity"]["component_groups"].merge_patch(groups);

    //Create events
    nlohmann::ordered_json events;
    for(auto& el: groups.items()) {
        if(el.key().find("reset") != string::npos) continue;
        if(groups.contains(el.key() + "_reset")) {
            events[el.key() + "_reset"]["add"]["component_groups"] = "[" + el.key() + "_reset" + "]";
        }

        events[el.key()]["add"]["component_groups"] = "[" + el.key() + "]";
        events[el.key() + "_reset"]["remove"]["component_groups"] = "[" + el.key() + "]";
    }

    //Merge events
    entity["minecraft:entity"]["events"].merge_patch(events);

    cout << setw(spacing + 2) << name + ":\n" << "Adding Component Groups:\n\033[32m" + groups.dump(spacing) << "\033[0m\nAdding Events:\n\033[32m" << events.dump(spacing) << "\033[0m" << endl;

    //Write modified entity
    ofstream o(user_data.behavior_path + "/entities/" + name + ".json");
    o << setw(spacing) << entity << endl;
    o.close();

    return 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        ShowUsage("help");
        return -1;
    }

    string dirArg;
    string family;
    string name;
    int opt;
    bool bUseSource = true;
    int indent = 2;

    while ((opt = bed_getopt(argc, argv, "i:d:f:n:s")) != -1) {
        switch (opt) {
            case 's':
            bUseSource = true;
            break;
            case 'd':
            bUseSource = false;
            dirArg = bed_optarg;
            break;
            case 'f':
            family = bed_optarg;
            break;
            case 'n':
            name = bed_optarg;
            break;
            case 'i':
            indent = atoi(bed_optarg);
            break;
            default:
            break;
        }
    }

    read_user_data();
    init_command_list();

    switch (mapCommandList[argv[argc-1]]) {
        case eRDIR:
        write_resource_dir(bUseSource, dirArg);
        break;
        case eBDIR:
        write_behavior_dir(bUseSource, dirArg);
        break;
        case eCOGR:
        process_component_group(family, name, indent);
        break;
        default:
        ShowUsage("help");
        break;
    }

    return 0;
}