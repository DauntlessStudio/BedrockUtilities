// BedrockTerminal.cpp : This file contains the 'main' function. Program execution begins and ends there.#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "getopt.h"
#include "json.hpp"
#include "JsonSources.h"
#include "DirectoryHandler.h"
#include "lodepng.h"

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
int write_json_to_file(const nlohmann::ordered_json &entity, string name, int spacing);
bool does_entity_contain_family(string family, json entity);
int create_new_entity(int spacing);
int create_new_item(int spacing, int stack_size);
int create_batch_funcs(int count, string name);
int create_anim_function(string name);
int add_animation_controller(nlohmann::ordered_json& entity, const string anim_name, const string query, const string exit_query, const string entry_line);
string format_name(string name);
vector<unsigned char> create_texture(int width, int height);
void save_texture(vector<unsigned char> png, string path);
void replace_all(std::string& str, const std::string& from, const std::string& to);

const char* prog_name;

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

static std::map < string, CommandList > mapCommandList;

void ShowUsage(string command) {
    //TODO modify function to show usage examples for a passed command name
    std::cout << "Try '" << prog_name << " -h' for more information" << std::endl;
}

void init_command_list() {
    mapCommandList["rdir"] = eRDIR;
    mapCommandList["bdir"] = eBDIR;
    mapCommandList["cogr"] = eCOGR;
    mapCommandList["nent"] = eNENT;
    mapCommandList["nitm"] = eNITM;
    mapCommandList["nblk"] = eNBLK;
    mapCommandList["func"] = eFUNC;
    mapCommandList["afunc"] = eAFUNC;
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
            write_json_to_file(*entity, user_data.behavior_path + "/entities/" + name + ".json", spacing);
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
            if (i.fail()) {
            cerr << file << "The specified file doesn't exist." << endl;
            continue;
        }

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
        
        if(entities.size() <= 0) {
            cout << "No valid entities found\nAborting..." << endl;
            return -1;
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
                write_json_to_file(entity, *file, spacing);
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
    
        if(entities.size() <= 0) {
            cout << "No valid entities found\nAborting..." << endl;
            return -1;
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
            write_json_to_file(entity, *file, spacing);
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

int write_json_to_file(const nlohmann::ordered_json &_json, string name, int spacing)
{
    //Write modified entity
    cout << "Saving " + name << endl;
    make_directory(name);
    ofstream o(name);
    o << setw(spacing) << _json << endl;
    o.close();

    return 0;
}

int add_txt_entry(string path, string entry)
{
    make_directory(path);
    cout << "Adding Entry to: " + path << endl;
    ofstream o;
    o.open(path, ios_base::app);
    o << endl << entry;
    o.close();

    return 0;
}

int overwrite_txt_entry(string path, string entry)
{
    make_directory(path);
    cout << "Writing File At: " + path << endl;
    ofstream o;
    o.open(path);
    o << entry;
    o.close();

    return 0;
}

vector<unsigned char> create_texture(int width, int height)
{
    std::vector<unsigned char> image;
    image.resize(width * height * 4);
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            image[4 * width * y + 4 * x + 0] = 255 * !(x & y);
            image[4 * width * y + 4 * x + 1] = x ^ y;
            image[4 * width * y + 4 * x + 2] = x | y;
            image[4 * width * y + 4 * x + 3] = 255;
        }

    vector<unsigned char> png;
    unsigned error = lodepng::encode(png, image, width, height);
    cout << "Creating New Texture..." << endl;
    return png;
}

void save_texture(vector<unsigned char> png, string path)
{
    make_directory(path);
    cout << "Saving Texture To: " + path << endl;
    lodepng::save_file(png, path);
}

int create_new_entity(int spacing)
{
    string input;
    cout << "Entity Name:" << endl;
    getline(cin, input);

    size_t index = input.find(':') + 1;
    string name = input.substr(index, input.length() - index);
    string _namespace = input.substr(0, index - 1);

    nlohmann::ordered_json entity;
    vector<string> family = {_namespace, name};

    char entity_type;
    cout << "Entity Framework (dummy|passive|hostile): [d/p/h]" << endl;
    cin >> entity_type;
    switch (entity_type)
    {
    case 'd':
        entity = JsonSources::bp_dummy_entity;
        family.push_back("dummy");
        break;
    case 'p':
        entity = JsonSources::bp_passive_entity;
        family.push_back("mob");
        break;
    case 'h':
        entity = JsonSources::bp_hostile_entity;
        family.push_back("mob");
        family.push_back("monster");
        break;
    default:
        cout << "Invalid Input\nAborting..." << endl;
        return -1;
    }

    entity["minecraft:entity"]["components"]["minecraft:type_family"]["family"] = family;
    entity["minecraft:entity"]["description"]["identifier"] = input;
    write_json_to_file(entity, user_data.behavior_path + "/entities/" + name + ".json", spacing);

    if(entity_type == 'd') return 0;

    char confirm;
    cout << "Create Resource Pack Files? [y/n]" << endl;
    cin >> confirm;
    if (confirm != 'y' && confirm != 'Y')
    {
        cout << "Aborting..." << endl;
        return 0;
    }

    nlohmann::ordered_json rp_ent = JsonSources::rp_entity;
    rp_ent["minecraft:client_entity"]["description"]["identifier"] = input;
    rp_ent["minecraft:client_entity"]["description"]["textures"]["default"] = "textures/entity/" + name + "/default";
    rp_ent["minecraft:client_entity"]["description"]["geometry"]["default"] = "geometry." + name;
    write_json_to_file(rp_ent, user_data.resource_path + "/entity/" + name + ".entity.json", spacing);
    
    nlohmann::ordered_json rp_mod = JsonSources::rp_model;
    nlohmann::ordered_json rp_geo = JsonSources::rp_geo;
    rp_geo["description"]["identifier"] = "geometry." + name;
    rp_mod["minecraft:geometry"] = nlohmann::ordered_json::array({ rp_geo });
    write_json_to_file(rp_mod, user_data.resource_path + "/models/entity/" + name + ".geo.json", spacing);

    save_texture(create_texture(64, 32), user_data.resource_path + "/textures/entity/" + name + "/default.png");

    add_txt_entry(user_data.resource_path + "/texts/en_us.lang", "entity." + input + ".name=" + format_name(name));

    if (entity_type != 'd')
    {
        add_txt_entry(user_data.resource_path + "/texts/en_us.lang", "item.spawn_egg.entity." + input + ".name=Spawn " + format_name(name));
    }

    return 0;
}

int create_new_item(int spacing, int stack_size)
{
    string input;
    cout << "Item Name:" << endl;
    getline(cin, input);

    size_t index = input.find(':') + 1;
    string name = input.substr(index, input.length() - index);
    string _namespace = input.substr(0, index - 1);

    // Get Player
    ifstream player_stream;
    player_stream.open(user_data.behavior_path + "/entities/player.json");
    nlohmann::ordered_json player;
    player_stream >> player;
    if (player.is_null()) player = JsonSources::bp_default_player;

    nlohmann::ordered_json item;
    json projectile_group;
    
    char item_type;
    cout << "Item Type (Default|Effect|Projectile): [d/e/p]" << endl;
    cin >> item_type;
    switch (item_type)
    {
    case 'd':
        item = JsonSources::bp_default_item;
        break;
    case 'e':
        item = JsonSources::bp_effect_item;
        add_animation_controller(player, name, "query.get_equipped_item_name == '" + name + "' && query.is_using_item", "!query.is_using_item", "/function " + name);
        write_json_to_file(player, user_data.behavior_path + "/entities/player.json", spacing);
        overwrite_txt_entry(user_data.behavior_path + "/functions/" + name + ".mcfunction", "say " + name);
        break;
    case 'p':
        item = JsonSources::bp_effect_item;
        add_animation_controller(player, name, "query.get_equipped_item_name == '" + name + "' && query.is_using_item", "!query.is_using_item", "/event entity @s " + input);
        projectile_group[input] = JsonSources::bp_spawn_snowball;
        add_groups_to_entity(projectile_group, player);
        write_json_to_file(player, user_data.behavior_path + "/entities/player.json", spacing);
        break;
    default:
        cout << "Invalid Input\nAborting..." << endl;
        return -1;
    }

    // Write Item BP
    item["minecraft:item"]["description"]["identifier"] = input;
    item["minecraft:item"]["components"]["minecraft:max_stack_size"] = stack_size > 64 ? 64 : stack_size;
    write_json_to_file(item, user_data.behavior_path + "/items/" + name + ".json", spacing);

    // Write Item Texture
    string texture_path;
    cout << "Texture Path:" << endl;
    cin.ignore();
    getline(cin, texture_path);
    if (texture_path.empty())
    {
        save_texture(create_texture(16, 16), user_data.resource_path + "/textures/items/" + name + ".png");
    }
    else
    {
        if (!copy_file(texture_path.c_str(), (user_data.resource_path + "/textures/items/" + name + ".png").c_str()))
        {
            save_texture(create_texture(16, 16), user_data.resource_path + "/textures/items/" + name + ".png");
        }
    }

    // Write Item RP
    nlohmann::ordered_json item_rp = JsonSources::rp_item;
    item_rp["minecraft:item"]["description"]["identifier"] = input;
    item_rp["minecraft:item"]["components"]["minecraft:icon"] = name;
    write_json_to_file(item_rp, user_data.resource_path + "/items/" + name + ".json", spacing);

    // Modify item_texture.json
    ifstream i;
    i.open(user_data.resource_path + "/textures/item_texture.json");
    nlohmann::ordered_json item_texture;
    i >> item_texture;
    i.close();
    json texture_entry;
    texture_entry[name]["textures"] = "textures/items/" + name;
    item_texture["texture_data"].merge_patch(texture_entry);
    write_json_to_file(item_texture, user_data.resource_path + "/textures/item_texture.json", 2);

    //Modify lang file
    add_txt_entry(user_data.resource_path + "/texts/en_us.lang", "item." + input + ".name=" + format_name(name));
    
    return 0;
}

int create_new_block(int spacing)
{
    string input;
    cout << "Block Name:" << endl;
    getline(cin, input);

    size_t index = input.find(':') + 1;
    string name = input.substr(index, input.length() - index);
    string _namespace = input.substr(0, index - 1);

    nlohmann::ordered_json block = JsonSources::bp_default_block;
    block["minecraft:block"]["description"]["identifier"] = input;

    cout << "Light Emmision:" << endl;
    float emission;
    cin >> emission;
    block["minecraft:block"]["components"]["minecraft:block_light_emission"] = emission;

    cout << "Explosion Resistance" << endl;
    float resistance;
    cin >> resistance;
    block["minecraft:block"]["components"]["minecraft:explosion_resistance"] = resistance;

    // Write Block BP
    write_json_to_file(block, user_data.behavior_path + "/blocks/" + name + ".json", spacing);

    // Write Block Texture
    string texture_path;
    cout << "Texture Path:" << endl;
    cin.ignore();
    getline(cin, texture_path);
    if (texture_path.empty())
    {
        save_texture(create_texture(16, 16), user_data.resource_path + "/textures/blocks/" + name + ".png");
    }
    else
    {
        if (!copy_file(texture_path.c_str(), (user_data.resource_path + "/textures/blocks/" + name + ".png").c_str()))
        {
            save_texture(create_texture(16, 16), user_data.resource_path + "/textures/blocks/" + name + ".png");
        }
    }
    

    // Modify terrain_texture.json
    ifstream i;
    i.open(user_data.resource_path + "/textures/terrain_texture.json");
    nlohmann::ordered_json terrain_texture;
    i >> terrain_texture;
    i.close();
    if(terrain_texture.is_null()) terrain_texture = JsonSources::rp_terrain_tex;
    json texture_entry;
    texture_entry[name]["textures"] = "textures/blocks/" + name;
    terrain_texture["texture_data"].merge_patch(texture_entry);
    write_json_to_file(terrain_texture, user_data.resource_path + "/textures/terrain_texture.json", 2);

    // Modify blocks.json
    i.open(user_data.resource_path + "/blocks.json");
    nlohmann::ordered_json blocks;
    i >> blocks;
    json block_entry;
    block_entry[input]["sound"] = "stone";
    block_entry[input]["textures"] = name;
    blocks.merge_patch(block_entry);
    write_json_to_file(blocks, user_data.resource_path + "/blocks.json", 2);

    //Modify lang file
    add_txt_entry(user_data.resource_path + "/texts/en_us.lang", "tile." + input + ".name=" + format_name(name));

    return 0;
}

int create_batch_funcs(int count, string name)
{
    if(name.empty()) name = "new_func";

    string function;
    cout << "Function: (use $ to represent the function number)" << endl;

    while (!cin.eof())
    {
        string line;
        getline(cin, line);

        if (cin.fail())
            break;

        function += line + '\n';
    }

    // Remove Trailing \n
    function.erase(function.end() - 1);

    for (int i = 1; i < count + 1; i++)
    {
        string write = function;
        replace_all(write, "$", to_string(i));
        overwrite_txt_entry(user_data.behavior_path + "/functions/" + name + "_" + to_string(i) + ".mcfunction", write);
    }

    return 0;
}

int create_anim_function(string name)
{
    if (name.empty()) name = "player";

    string func_name;

    cout << "Function Name:" << endl;
    getline(cin, func_name);

    string query;
    string exit_query;

    cout << "Query:" << endl;
    getline(cin, query);

    cout << "Exit Query:" << endl;
    getline(cin, exit_query);

    string function;
    cout << "Function:" << endl;

    while (!cin.eof())
    {
        string line;
        getline(cin, line);

        if (cin.fail())
            break;

        function += line + '\n';
    }

    // Remove Trailing \n
    function.erase(function.end() - 1);
    
    overwrite_txt_entry(user_data.behavior_path + "/functions/" + func_name + ".mcfunction", function);

    ifstream i;
    make_directory(user_data.behavior_path + "/entities/");
    i.open(user_data.behavior_path + "/entities/" + name + ".json");
    nlohmann::ordered_json entity;
    try
    {
        i >> entity;
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
    }
    i.close();

    string write_func = func_name;
    replace_all(write_func, "/", ".");
    add_animation_controller(entity, write_func, query, exit_query, "/function " + func_name);
    write_json_to_file(entity, user_data.behavior_path + "/entities/" + name + ".json", 2);

    return 0;
}

int add_animation_controller(nlohmann::ordered_json& entity, const string anim_name, const string query, const string exit_query, const string entry_line)
{
    make_directory(user_data.behavior_path + "/animation_controllers/");
    string full_name = entity["minecraft:entity"]["description"]["identifier"];
    size_t index = full_name.find(':') + 1;
    string name = full_name.substr(index, full_name.length() - index);

    entity["minecraft:entity"]["description"]["animations"].merge_patch(json({ {anim_name, "controller.animation." + name + "." + anim_name} }));
    entity["minecraft:entity"]["description"]["scripts"]["animate"].push_back(anim_name);

    ifstream i;
    i.open(user_data.behavior_path + "/animation_controllers/" + name + ".animation_controller.json");
    nlohmann::ordered_json animation_controller;
    try
    {
        i >> animation_controller;
    }
    catch (const std::exception&)
    {
        cout << "Creating Controller..." << endl;
    }
    i.close();
    if (animation_controller.is_null()) animation_controller = JsonSources::bp_default_anim_controller;

    nlohmann::ordered_json controller;
    controller["states"]["default"]["transitions"] = json::array({ json({{ "effect", query }}) });
    controller["states"]["effect"]["transitions"] = json::array({ json({{"default", exit_query}}) });

    string val[] = { entry_line };
    controller["states"]["effect"]["on_entry"] = val;

    animation_controller["animation_controllers"]["controller.animation." + name + "." + anim_name] = controller;
    write_json_to_file(animation_controller, user_data.behavior_path + "/animation_controllers/" + name + ".animation_controller.json", 2);
    return 0;
}

string format_name(string name)
{
    string lang_name = name;
    bool caps_next = true;
    for (size_t i = 0; i < name.length(); i++)
    {
        if (caps_next)
        {
            lang_name[i] = toupper(lang_name[i]);
            caps_next = false;
        }

        if (name[i] == '_')
        {
            lang_name[i] = ' ';
            caps_next = true;
        }
    }
    
    return lang_name;
}

void replace_all(std::string& str, const std::string& from, const std::string& to)
{
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
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
    int count = 64;

    while ((opt = bed_getopt(argc, argv, "i:d:f:n:c:")) != -1) {
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
            case 'c':
                count = atoi(bed_optarg);
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
        case eNENT:
            create_new_entity(indent);
            break;
        case eNITM:
            create_new_item(indent, count);
            break;
        case eNBLK:
            create_new_block(indent);
            break;
        case eFUNC:
            create_batch_funcs(count, name);
            break;
        case eAFUNC:
            create_anim_function(name);
            break;
        default:
            ShowUsage("help");
            break;
    }

    return 0;
}