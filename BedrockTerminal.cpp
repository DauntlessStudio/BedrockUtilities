// BedrockTerminal.cpp : This file contains the 'main' function. Program execution begins and ends there.#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "getopt.h"
#include "json.hpp"
#include "DirectoryHandler.h"

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
int add_groups_to_entity(const json &groups, nlohmann::ordered_json &entity);
int write_entity_to_file(const nlohmann::ordered_json &entity, string name, int spacing);
bool does_entity_contain_family(string family, json entity);

const char* prog_name;

enum CommandList
{
    eNULL,
    eRDIR,
    eBDIR,
    eCOGR
};

static std::map < string, CommandList > mapCommandList;

void ShowUsage(string command) {
    //TODO modify function to show usage examples for a passed command name
    std::cout << "Try '" << prog_name << " -h' for more information" << std::endl;
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
        nlohmann::ordered_json *entity;
        entity = new nlohmann::ordered_json;
        try
        {
            *entity = entity->parse(i, nullptr, true, true);
        }
        catch (const std::exception& e)
        {
            cerr << e.what() << endl;
        }
        i.close();
        
        //Add data to entity
        json groups = get_component_groups_from_input();
        add_groups_to_entity(groups, *entity);

        //Confirm input and write file
        cout << "Save File? [y/n]";
        string input;
        cin >> input;
        if (input == "y" || input == "Y")
        {
            write_entity_to_file(*entity, user_data.behavior_path + "/entities/" + name + ".json", spacing);
        }
        else
        {
            cout << "Cancelled" << endl;
        }

        return 0;
    }

    if (!family.empty())
    {
        list<string> files = get_directory_files(user_data.behavior_path + "/entities/");
        list<string> new_files;
        list<nlohmann::ordered_json> entities;
        for (const auto& file : files)
        {
            //Get an ordered_json copy of the entity to preserve json order
            ifstream i(file);

            nlohmann::ordered_json* entity;
            entity = new nlohmann::ordered_json;
            try
            {
                *entity = entity->parse(i, nullptr, true, true);
            }
            catch (const std::exception& e)
            {
                cerr << e.what() << endl;
            }
            i.close();

            if (does_entity_contain_family(family, *entity))
            {
                entities.push_back(*entity);
                new_files.push_back(file);
            }
        }

        cout << "Found " << entities.size() << " entities that contain the family type: " << family << endl;
        json groups = get_component_groups_from_input();

        for (auto& entity : entities)
        {
            add_groups_to_entity(groups, entity);
        }

        //Confirm input and write file
        cout << "Save File(s)? [y/n]";
        string input;
        cin >> input;
        if (input == "y" || input == "Y")
        {
            auto file = new_files.begin();
            for (auto& entity : entities)
            {
                write_entity_to_file(entity, *file, spacing);
                advance(file, 1);
            }
        }
        else
        {
            cout << "Cancelled" << endl;
        }

        return 0;
    }

    list<string> files = get_directory_files(user_data.behavior_path + "/entities/");
    list<nlohmann::ordered_json> entities;
    for (const auto& file : files)
    {
        //Get an ordered_json copy of the entity to preserve json order
        ifstream i(file);

        nlohmann::ordered_json* entity;
        entity = new nlohmann::ordered_json;
        try
        {
            *entity = entity->parse(i, nullptr, true, true);
        }
        catch (const std::exception& e)
        {
            cerr << e.what() << endl;
        }
        i.close();

        entities.push_back(*entity);
    }

    cout << "Found " << entities.size() << " entities" << endl;
    json groups = get_component_groups_from_input();

    for (auto& entity : entities)
    {
        add_groups_to_entity(groups, entity);
    }

    //Confirm input and write file
    cout << "Save File(s)? [y/n]";
    string input;
    cin >> input;
    if (input == "y" || input == "Y")
    {
        auto file = files.begin();
        for (auto& entity : entities)
        {
            write_entity_to_file(entity, *file, spacing);
            advance(file, 1);
        }
    }
    else
    {
        cout << "Cancelled" << endl;
    }

    return 0;
}

bool does_entity_contain_family(string family, json entity)
{
    for (const auto& it : entity["minecraft:entity"]["components"]["minecraft:type_family"]["family"].items())
    {
        if (it.value() == family)
        {
            return true;
        }
    }

    for (const auto& it : entity["minecraft:entity"]["component_groups"].items())
    {
        if (it.value().contains("minecraft:type_family"))
        {
            for (const auto& en : it.value()["minecraft:type_family"]["family"].items())
            {
                if (en.value() == family)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

json get_component_groups_from_input() {
    string input;
    std::cout << "New Component Groups:" << endl;
    getline(cin, input);
    input = "{" + input + "}";
    json jo;
    try
    {
        jo = json::parse(input);
    }
    catch (...)
    {
        cerr << "Invalid Entry, Aborting..." << endl;
        exit(-1);
    }
    
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

int add_groups_to_entity(const json &groups, nlohmann::ordered_json &entity) {
    //Process resets
    json groups_tmp = groups;
    for(auto& el: groups.items()) {
        json tmp;
        for(auto& it: el.value().items()) {
            if(el.key().find("reset") != string::npos) {
            tmp.merge_patch(entity["minecraft:entity"]["components"][it.key()]);
            
                if(!tmp.empty()) {
                    groups_tmp[el.key()][it.key()] = tmp;
                }
                else
                {
                    groups_tmp.erase(el.key());
                }
            }
        }
    }
    //Merge component_groups
    entity["minecraft:entity"]["component_groups"].merge_patch(groups_tmp);

    //Create events
    nlohmann::ordered_json events;
    for(auto& el: groups.items()) {
        if(el.key().find("reset") != string::npos) continue;

        string val[] = { el.key() };
        string val_reset[] = {el.key() + "_reset"};

        if(groups_tmp.contains(el.key() + "_reset")) {
            events[el.key() + "_reset"]["add"]["component_groups"] = val_reset;
        }

        events[el.key()]["add"]["component_groups"] = val;
        events[el.key() + "_reset"]["remove"]["component_groups"] = val;
    }

    //Merge events
    entity["minecraft:entity"]["events"].merge_patch(events);

    string name = entity["minecraft:entity"]["description"]["identifier"];
    cout << name + ":\n" << "Adding Component Groups:\n" << LINE_GREEN << groups_tmp.dump(2) << LINE_RESET << "\nAdding Events:\n" << LINE_GREEN << events.dump(2) << LINE_RESET << endl;
    return 0;
}

int write_entity_to_file(const nlohmann::ordered_json &entity, string name, int spacing)
{
    //Write modified entity
    cout << "Saving " + name << endl;
    ofstream o(name);
    o << setw(spacing) << entity << endl;
    o.close();

    return 0;
}

int main(int argc, char** argv) {
    prog_name = argv[0];

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

    while ((opt = bed_getopt(argc, argv, "i:d:f:n:")) != -1) {
        switch (opt) {
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