// BedrockTerminal.cpp : This file contains the 'main' function. Program execution begins and ends there.#include <iostream>
#include "BedrockTerminal.hpp"

void show_usage(string command) {
    switch (mapCommandList[command])
    {
    case eRDIR:
        cout << prog_name << " [<options>] rdir" << endl;
        cout << "options:\n  [-d <path>] Directory, sets the resource directory to <path>. Defaults to current working directory" << endl;
        cout << "  [-i <indent>] Indent, sets the output file's indent level. Defaults to 2" << endl;
        break;
    case eBDIR:
        cout << prog_name << " [<options>] bdir" << endl;
        cout << "options:\n  [-d <path>] Directory, sets the behavior directory to <path>. Defaults to current working directory" << endl;
        cout << "  [-i <indent>] Indent, sets the output file's indent level. Defaults to 2" << endl;
        break;
    case eCOGR:
        cout << prog_name << " [<options>] cogr" << endl;
        cout << "options:\n  [-i <indent>] Indent, sets the output file's indent level. Defaults to 2" << endl;
        cout << "  [-n <filename>] Name, uses bp/entities/<filename>.json as the file to modify" << endl;
        cout << "  [-f <family>] Family, modifies all entities in bp/entities/ with the desired family type" << endl;
        cout << "  Modifies all entites in bp/entities/ if [-n|-f] are not proided" << endl;
        break;
    case eCOMP:
        cout << prog_name << " [<options>] comp" << endl;
        cout << "options:\n  [-i <indent>] Indent, sets the output file's indent level. Defaults to 2" << endl;
        cout << "  [-n <filename>] Name, uses bp/entities/<filename>.json as the file to modify" << endl;
        cout << "  [-f <family>] Family, modifies all entities in bp/entities/ with the desired family type" << endl;
        cout << "  Modifies all entites in bp/entities/ if [-n|-f] are not proided" << endl;
        break;
    case eNENT:
        cout << prog_name << " [<options>] nent" << endl;
        cout << "options:\n  [-i <indent>] Indent, sets the output file's indent level. Defaults to 2" << endl;
        break;
    case eNITM:
        cout << prog_name << " [<options>] nitm" << endl;
        cout << "options:\n  [-i <indent>] Indent, sets the output file's indent level. Defaults to 2" << endl;
        break;
    case eNMAN:
        cout << prog_name << " nman" << endl;
        cout << "no options." << endl;
        break;
    case eNBLK:
        cout << prog_name << " [<options>] nblk" << endl;
        cout << "options:\n  [-i <indent>] Indent, sets the output file's indent level. Defaults to 2" << endl;
        break;
    case eFUNC:
        cout << prog_name << " [<options>] func" << endl;
        cout << "options:\n  [-c <count>] Count, the number of functions to create in the batch" << endl;
        cout << "  [-n <name>] Name, the name of the functions. Defaults to 'new_func'. Function names are appended with '_[#function_number]'" << endl;
        break;
    case eAFUNC:
        cout << prog_name << " [<options>] afunc" << endl;
        cout << "options:\n  [-n <name>] Name, the name of the entity to create the animation controller for. Defaults to 'player'" << endl;
        break;
    default:
        cout << "usage: " << prog_name << " [<args>] <command>" << endl;
        cout << "command list:" << endl;
        cout << "  rdir          Set resource directory" << endl;
        cout << "  bdir          Set behavior directory" << endl;
        cout << "  cogr          Add new component groups" << endl;
        cout << "  comp          Add new components" << endl;
        cout << "  nent          Create new entity" << endl;
        cout << "  nitm          Create new item" << endl;
        cout << "  nman          Create new resource/behavior packs" << endl;
        cout << "  nblk          Create new block" << endl;
        cout << "  func          Create new functions" << endl;
        cout << "  afunc         Create new animation controller function" << endl;
        cout << endl << "'" << prog_name << " -h <command>' for more information" << endl;
        break;
    }
}

void init_command_list() {
    mapCommandList["rdir"] = eRDIR;
    mapCommandList["bdir"] = eBDIR;
    mapCommandList["cogr"] = eCOGR;
    mapCommandList["comp"] = eCOMP;
    mapCommandList["nent"] = eNENT;
    mapCommandList["nitm"] = eNITM;
    mapCommandList["nman"] = eNMAN;
    mapCommandList["nblk"] = eNBLK;
    mapCommandList["func"] = eFUNC;
    mapCommandList["afunc"] = eAFUNC;
}

int create_component_group(string family, string name, int spacing) 
{
    string input;
    vector<bedrock::entity> entities = get_bp_entities(name, family);
    
    if(entities.size() <= 0) {
        cout << "No valid entities found\nAborting..." << endl;
        return -1;
    }

    cout << "Found " << entities.size() << " entities" << endl;

    ordered_json groups = read_json_from_input("New Component Groups:", "Invalid Json\nAborting...", true);
    for (auto& el : groups.items())
    {
        std::cout << "Create Reset For: " << el.key() << "? [y/n]:" << endl;
        getline(cin, input);
        if (input != "y" && input != "Y")
        {
            continue;
        }

        groups[el.key() + "_reset"] = el.value();
    }

    for (auto& entity : entities)
    {
        entity.add_groups_to_entity(groups);
    }

    //Confirm input and write file
    cout << "Save File(s)? [y/n]" << endl;
    getline(cin, input);
    cout << input << endl;
    if (input == "y" || input == "Y")
    {
        for (auto& entity : entities)
        {
            write_json_to_file(entity.entity_json, entity.file_path, spacing);
        }
    }
    else
    {
        cout << "Cancelled" << endl;
    }

    return 0;
}

int create_components(string family, string name, int spacing)
{
    string input;
    vector<bedrock::entity> entities = get_bp_entities(name, family);

    if (entities.size() <= 0)
    {
        cout << "No valid entities found\nAborting..." << endl;
        return -1;
    }

    cout << "Found " << entities.size() << " entities" << endl;

    ordered_json components = read_json_from_input("New Components", "Invalid Json\nAborting...", true);

    for (auto& entity : entities)
    {
        entity.entity_json["minecraft:entity"]["components"].merge_patch(components);
    }

    //Confirm input and write file
    cout << "Save File(s)? [y/n]";
    getline(cin, input);
    if (input == "y" || input == "Y")
    {
        for (auto& entity : entities)
        {
            write_json_to_file(entity.entity_json, entity.file_path, spacing);
        }
    }
    else
    {
        cout << "Cancelled" << endl;
    }

    return 0;
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

    vector<unsigned char> empty;
    write_texture_to_file(empty, user_data.resource_path + "/textures/entity/" + name + "/default.png");

    append_txt_file(user_data.resource_path + "/texts/en_us.lang", "entity." + input + ".name=" + format_name(name));

    if (entity_type != 'd')
    {
        append_txt_file(user_data.resource_path + "/texts/en_us.lang", "item.spawn_egg.entity." + input + ".name=Spawn " + format_name(name));
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
    bedrock::entity player(user_data.behavior_path + "/entities/player.json");
    if (player.entity_json.is_null()) player.entity_json = JsonSources::bp_default_player;

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
        player.add_animation_controller(name, "query.get_equipped_item_name == '" + name + "' && query.is_using_item", "!query.is_using_item", "/function " + name);
        write_json_to_file(player.entity_json, user_data.behavior_path + "/entities/player.json", spacing);
        overwrite_txt_file(user_data.behavior_path + "/functions/" + name + ".mcfunction", "say " + name);
        break;
    case 'p':
        item = JsonSources::bp_effect_item;
        player.add_animation_controller(name, "query.get_equipped_item_name == '" + name + "' && query.is_using_item", "!query.is_using_item", "/event entity @s " + input);
        projectile_group[input] = JsonSources::bp_spawn_snowball;
        player.add_groups_to_entity(projectile_group);
        write_json_to_file(player.entity_json, user_data.behavior_path + "/entities/player.json", spacing);
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
        vector<unsigned char> empty;
        write_texture_to_file(empty, user_data.resource_path + "/textures/items/" + name + ".png");
    }
    else
    {
        if (!copy_file(texture_path.c_str(), (user_data.resource_path + "/textures/items/" + name + ".png").c_str()))
        {
            vector<unsigned char> empty;
            write_texture_to_file(empty, user_data.resource_path + "/textures/items/" + name + ".png");
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
    append_txt_file(user_data.resource_path + "/texts/en_us.lang", "item." + input + ".name=" + format_name(name));
    
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
        vector<unsigned char> empty;
        write_texture_to_file(empty, user_data.resource_path + "/textures/blocks/" + name + ".png");
    }
    else
    {
        if (!copy_file(texture_path.c_str(), (user_data.resource_path + "/textures/blocks/" + name + ".png").c_str()))
        {
            vector<unsigned char> empty;
            write_texture_to_file(empty, user_data.resource_path + "/textures/blocks/" + name + ".png");
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
    append_txt_file(user_data.resource_path + "/texts/en_us.lang", "tile." + input + ".name=" + format_name(name));

    return 0;
}

int create_batch_funcs(int count, string name)
{
    if(name.empty()) name = "new_func";

    cout << "Function: (use $ to represent the function number)" << endl;
    string function = read_multiline_input();

    for (int i = 1; i < count + 1; i++)
    {
        string write = function;
        replace_all(write, "$", to_string(i));
        overwrite_txt_file(user_data.behavior_path + "/functions/" + name + "_" + to_string(i) + ".mcfunction", write);
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
    
    overwrite_txt_file(user_data.behavior_path + "/functions/" + func_name + ".mcfunction", function);

    bedrock::entity entity(user_data.behavior_path + "/entities/" + name + ".json");

    string write_func = func_name;
    replace_all(write_func, "/", ".");
    entity.add_animation_controller(write_func, query, exit_query, "/function " + func_name);
    write_json_to_file(entity.entity_json, user_data.behavior_path + "/entities/" + name + ".json", 2);

    return 0;
}

int create_manifest()
{
    string bp_name;
    cout << "Behavior Pack Name:" << endl;
    getline(cin, bp_name);

    size_t index = user_data.behavior_path.find_last_of(SLASH);
    string bp_path = user_data.behavior_path.substr(0, index) + SLASH + bp_name + "/";

    string rp_name;
    cout << "Resource Pack Name:" << endl;
    getline(cin, rp_name);

    index = user_data.resource_path.find_last_of(SLASH);
    string rp_path = user_data.resource_path.substr(0, index) + SLASH + rp_name + "/";

    nlohmann::ordered_json manifest = JsonSources::manifest;
    nlohmann::ordered_json sub_manifest = JsonSources::sub_manifest;

    manifest["header"]["uuid"] = uuid::generate_uuid_v4();
    sub_manifest["uuid"] = uuid::generate_uuid_v4();
    manifest["modules"] = json::array({ sub_manifest });

    write_json_to_file(manifest, bp_path + "manifest.json");
    overwrite_txt_file(bp_path + "texts/en_US.lang", "## BEHAVIOR PACK MANIFEST =======================================================\npack.name=" + bp_name + "\npack.description=This behavior pack is required for " + bp_name + " to run properly");
    write_json_to_file(json({"en_US"}), bp_path + "/texts/languages.json");

    manifest["header"]["uuid"] = uuid::generate_uuid_v4();
    sub_manifest["uuid"] = uuid::generate_uuid_v4();
    manifest["modules"] = json::array({ sub_manifest });

    write_json_to_file(manifest, rp_path + "manifest.json");
    overwrite_txt_file(rp_path + "/texts/en_US.lang", "## RESOURCE PACK MANIFEST =======================================================\npack.name=" + rp_name + "\npack.description=This behavior pack is required for " + rp_name + " to run properly");
    write_json_to_file(json({ "en_US" }), rp_path + "/texts/languages.json");

    return 0;
}

int main(int argc, char** argv) {
    prog_name = argv[0];

    if (argc < 2) {
        show_usage("help");
        return -1;
    }

    string dirArg;
    string family;
    string name;
    int opt;
    bool bUseSource = true;
    bool show_help = false;
    int indent = 2;
    int count = 64;

    while ((opt = bed_getopt(argc, argv, "i:d:f:n:c:h")) != -1) {
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
            case 'h':
                show_help = true;
                break;
            default:
            break;
        }
    }

    read_user_data();
    init_command_list();

    if (show_help)
    {
        show_usage(argv[argc-1]);
        return 0;
    }

    switch (mapCommandList[argv[argc-1]]) {
        case eRDIR:
            write_resource_dir(bUseSource, dirArg);
            break;
        case eBDIR:
            write_behavior_dir(bUseSource, dirArg);
            break;
        case eCOGR:
            create_component_group(family, name, indent);
            break;
        case eCOMP:
            create_components(family, name, indent);
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
        case eNMAN:
            create_manifest();
            break;
        default:
            show_usage("help");
            break;
    }

    return 0;
}