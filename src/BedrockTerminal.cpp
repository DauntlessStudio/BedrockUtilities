#include "includes/BedrockTerminal.hpp"

/// <summary>
/// Prints help information to terminal.
/// </summary>
/// <param name="command">The command to print help info for. Shows command list if empty.</param>
void show_usage(const string& command) {
    switch (mapCommandList[command])
    {
    case eRDIR:
        cout << prog_name << " [<options>] rdir" << endl;
        cout << "options:\n  [-d <path>] Directory, sets the resource directory to <path>. Defaults to current working directory" << endl;
        cout << "  [-i <indent>] Indent, sets the output file's indent level. Defaults to 4" << endl;
        break;
    case eBDIR:
        cout << prog_name << " [<options>] bdir" << endl;
        cout << "options:\n  [-d <path>] Directory, sets the behavior directory to <path>. Defaults to current working directory" << endl;
        cout << "  [-i <indent>] Indent, sets the output file's indent level. Defaults to 4" << endl;
        break;
    case eCOGR:
        cout << prog_name << " [<options>] cogr" << endl;
        cout << "options:\n  [-i <indent>] Indent, sets the output file's indent level. Defaults to 4" << endl;
        cout << "  [-r] Remove, removes the component groups" << endl;
        cout << "  [-n <filename>,<filename2>] Name, uses bp/entities/<filename>.json as the file to modify" << endl;
        cout << "  [-f <family>] Family, modifies all entities in bp/entities/ with the desired family type" << endl;
        cout << "  [-d <directory>] Specifies a a subdirectory of bp/entities/" << endl;
        cout << "  Modifies all entites in bp/entities/ if [-n|-f] are not provided" << endl;
        break;
    case eCOMP:
        cout << prog_name << " [<options>] comp" << endl;
        cout << "options:\n  [-i <indent>] Indent, sets the output file's indent level. Defaults to 4" << endl;
        cout << "  [-r] Remove, removes the component groups" << endl;
        cout << "  [-n <filename>,<filename2>] Name, uses bp/entities/<filename>.json as the file to modify" << endl;
        cout << "  [-f <family>] Family, modifies all entities in bp/entities/ with the desired family type" << endl;
        cout << "  Modifies all entites in bp/entities/ if [-n|-f] are not provided" << endl;
        break;
    case eNENT:
        cout << prog_name << " [<options>] nent" << endl;
        cout << "options:\n  [-i <indent>] Indent, sets the output file's indent level. Defaults to 4" << endl;
        break;
    case eNITM:
        cout << prog_name << " [<options>] nitm" << endl;
        cout << "options:\n  [-i <indent>] Indent, sets the output file's indent level. Defaults to 4" << endl;
        break;
    case eNMAN:
        cout << prog_name << " nman" << endl;
        cout << "no options." << endl;
        break;
    case eNBLK:
        cout << prog_name << " [<options>] nblk" << endl;
        cout << "options:\n  [-i <indent>] Indent, sets the output file's indent level. Defaults to 4" << endl;
        break;
    case eFUNC:
        cout << prog_name << " [<options>] func" << endl;
        cout << "options:\n  [-c <count>] Count, the number of functions to create in the batch" << endl;
        cout << "  [-n <name>] Name, the name of the functions. Defaults to 'new_func'. Function names are appended with '_[#function_number]'" << endl;
        break;
    case eAFUNC:
        cout << prog_name << " [<options>] afunc" << endl;
        cout << "options:\n  [-i <indent>] Indent, sets the output file's indent level. Defaults to 4" << endl;
        cout << "  [-n <filename>,<filename2>] Name, uses bp/entities/<filename>.json as the file to modify" << endl;
        cout << "  [-f <family>] Family, modifies all entities in bp/entities/ with the desired family type" << endl;
        cout << "  [-d <directory>] Specifies a a subdirectory of bp/entities/" << endl;
        cout << "  [-q <query>] Query, uses the provided query in the entities animation" << endl;
        break;
    case eACFUNC:
        cout << prog_name << " [<options>] acfunc" << endl;
        cout << "options:\n  [-i <indent>] Indent, sets the output file's indent level. Defaults to 4" << endl;
        cout << "  [-n <filename>,<filename2>] Name, uses bp/entities/<filename>.json as the file to modify" << endl;
        cout << "  [-f <family>] Family, modifies all entities in bp/entities/ with the desired family type" << endl;
        cout << "  [-d <directory>] Specifies a a subdirectory of bp/entities/" << endl;
        break;
    case eSKIN:
        cout << prog_name << " [<options>] skin" << endl;
        cout << "options:\n  [-n <name>] Name, the name of the skin pack, in camel case'" << endl;
        break;
    case eDMGS:
        cout << prog_name << " [<options>] dmgs" << endl;
        cout << "options:\n  [-i <indent>] Indent, sets the output file's indent level. Defaults to 4" << endl;
        cout << "  [-n <filename>,<filename2>] Name, uses bp/entities/<filename>.json as the file to modify" << endl;
        cout << "  [-f <family>] Family, modifies all entities in bp/entities/ with the desired family type" << endl;
        cout << "  [-d <directory>] Specifies a a subdirectory of bp/entities/" << endl;
        cout << "  [-g] Groups, should modify the damage sensors listed in component groups" << endl;
        cout << "  Modifies all entites in bp/entities/ if [-n|-f] are not provided" << endl;
        break;
    case eTEMP:
        cout << prog_name << " [<options>] temp" << endl;
        cout << "options:\n  [-i <indent>] Indent, sets the output file's indent level. Defaults to 4" << endl;
        cout << "  [-n <filename>,<filename2>] Name, uses bp/entities/<filename>.json as the file to modify" << endl;
        cout << "  [-f <family>] Family, modifies all entities in bp/entities/ with the desired family type" << endl;
        cout << "  [-d <directory>] Specifies a a subdirectory of bp/entities/" << endl;
        cout << "  Modifies all entites in bp/entities/ if [-n|-f|-d] are not provided" << endl;
        break;
    default:
        cout << "usage: " << prog_name << " [<args>] <command>" << endl;
        cout << "command list:" << endl;
        cout << "  rdir          Set resource directory" << endl;
        cout << "  bdir          Set behavior directory" << endl;
        cout << "  cogr          Add or remove component groups" << endl;
        cout << "  comp          Add or remove components" << endl;
        cout << "  nent          Create new entity" << endl;
        cout << "  nitm          Create new item" << endl;
        cout << "  nman          Create new resource/behavior packs" << endl;
        cout << "  nblk          Create new block" << endl;
        cout << "  func          Create new functions" << endl;
        cout << "  afunc         Create new animation function" << endl;
        cout << "  acfunc        Create new animation controller function" << endl;
        cout << "  skin          Create new skin pack with the files in the working directory" << endl;
        cout << "  dmgs          Add value to damage sensor components" << endl;
        cout << "  temp          Temporary easy changes" << endl;
        cout << endl << "'" << prog_name << " -h <command>' for more information" << endl;
        break;
    }
}

/// <summary>
/// Initializes the command list to get an enum value from user input.
/// </summary>
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
    mapCommandList["acfunc"] = eACFUNC;
    mapCommandList["skin"] = eSKIN;
    mapCommandList["dmgs"] = eDMGS;
    mapCommandList["temp"] = eTEMP;
}

/// <summary>
/// Creates a new component group in the desired entity files.
/// </summary>
/// <returns>Success value.</returns>
int create_component_group()
{
    string input;
    ordered_json groups = read_json_from_input("New Component Groups:", "Invalid Json\nAborting...", true);

    for (auto& entity : entities)
    {
        entity.add_groups_to_entity(groups);
    }

    write_entities_to_files();

    return 0;
}

/// <summary>
/// Removes an existing component group in the desired entity files.
/// </summary>
/// <returns>Success value.</returns>
int remove_component_group()
{
    string input;
    ordered_json groups = read_json_from_input("Component Groups to Remove:", "Invalid Json\nAborting...", true);

    cout << "Removing Groups" << endl;

    for (auto& entity : entities)
    {
        entity.remove_groups_from_entity(groups);
    }

    write_entities_to_files();

    return 0;
}

/// <summary>
/// Creates a new base component in the desired entity files.
/// </summary>
/// <returns>Success value.</returns>
int create_components()
{
    string input;
    ordered_json components = read_json_from_input("New Components", "Invalid Json\nAborting...", true);

    for (auto& entity : entities)
    {
        entity.entity_json["minecraft:entity"]["components"].merge_patch(components);
    }

    write_entities_to_files();

    return 0;
}

/// <summary>
/// Creates a new component group in the desired entity files.
/// </summary>
/// <returns>Success value.</returns>
int remove_components()
{
    string input;
    ordered_json components = read_json_from_input("Components to Remove", "Invalid Json\nAborting...", true);

    cout << "Removing Components" << endl;

    for (auto& entity : entities)
    {
        for (auto& it : components.items())
        {
            entity.entity_json["minecraft:entity"]["components"].erase(it.key());
        }
    }

    write_entities_to_files();

    return 0;
}

/// <summary>
/// Creates a new entity.
/// </summary>
/// <param name="spacing">The indentation level for the JSON file.</param>
/// <returns>Success value.</returns>
int create_new_entity(const int& spacing)
{
    if (!user_data.valid_bp()) abort_program("Invalid Behavior Path at " + user_data.behavior_path + "\nAborting...");

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

    char confirm;
    cout << "Create Resource Pack Files? [y/n]" << endl;
    cin >> confirm;
    if (confirm != 'y' && confirm != 'Y')
    {
        cout << "Aborting..." << endl;
        return 0;
    }

    if (!user_data.valid_rp()) abort_program("Invalid Resource Path at " + user_data.resource_path + "\nAborting...");

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

/// <summary>
/// Creates a new item.
/// </summary>
/// <param name="spacing">The indentation level for the JSON file</param>
/// <param name="stack_size">The max count of the item.</param>
/// <returns>Success value.</returns>
int create_new_item(const int& spacing, const int& stack_size)
{
    if (!user_data.valid_bp()) abort_program("Invalid Behavior Path at " + user_data.behavior_path + "\nAborting...");

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
        player.add_animation_controller(name, "query.get_equipped_item_name == '" + name + "' && query.is_using_item", "!query.is_using_item", vector<string> {"/function " + name});
        write_json_to_file(player.entity_json, user_data.behavior_path + "/entities/player.json", spacing);
        overwrite_txt_file(user_data.behavior_path + "/functions/" + name + ".mcfunction", "say " + name);
        break;
    case 'p':
        item = JsonSources::bp_effect_item;
        player.add_animation_controller(name, "query.get_equipped_item_name == '" + name + "' && query.is_using_item", "!query.is_using_item", vector<string> {"/event entity @s " + input});
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

    if (!user_data.valid_rp()) abort_program("Invalid Resource Path at " + user_data.resource_path + "\nAborting...");

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
    nlohmann::ordered_json item_texture;
    read_json_from_file(item_texture, user_data.resource_path + "/textures/item_texture.json", "Invalid texture.json");
    json texture_entry;
    texture_entry[name]["textures"] = "textures/items/" + name;
    item_texture["texture_data"].merge_patch(texture_entry);
    write_json_to_file(item_texture, user_data.resource_path + "/textures/item_texture.json", 2);

    //Modify lang file
    append_txt_file(user_data.resource_path + "/texts/en_us.lang", "item." + input + ".name=" + format_name(name));
    
    return 0;
}

/// <summary>
/// Creates a new block
/// </summary>
/// <param name="spacing">The indentation level for the JSON file</param>
/// <returns>Success value.</returns>
int create_new_block(const int& spacing)
{
    if (!user_data.valid_bp()) abort_program("Invalid Behavior Path at " + user_data.behavior_path + "\nAborting...");

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

    if (!user_data.valid_rp()) abort_program("Invalid Resource Path at " + user_data.resource_path + "\nAborting...");

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
    nlohmann::ordered_json terrain_texture;
    read_json_from_file(terrain_texture, user_data.resource_path + "/textures/terrain_texture.json", "Creating Terrain Texture");
    if(terrain_texture.is_null()) terrain_texture = JsonSources::rp_terrain_tex;
    json texture_entry;
    texture_entry[name]["textures"] = "textures/blocks/" + name;
    terrain_texture["texture_data"].merge_patch(texture_entry);
    write_json_to_file(terrain_texture, user_data.resource_path + "/textures/terrain_texture.json", 2);

    // Modify blocks.json
    nlohmann::ordered_json blocks;
    read_json_from_file(blocks, user_data.resource_path + "/blocks.json", "Creating blocks.json");
    json block_entry;
    block_entry[input]["sound"] = "stone";
    block_entry[input]["textures"] = name;
    blocks.merge_patch(block_entry);
    write_json_to_file(blocks, user_data.resource_path + "/blocks.json", 2);

    //Modify lang file
    append_txt_file(user_data.resource_path + "/texts/en_us.lang", "tile." + input + ".name=" + format_name(name));

    return 0;
}

/// <summary>
/// Creates x number of mcfunctions.
/// </summary>
/// <param name="count">The number of mcfunctions to create.</param>
/// <param name="name">The function name, appended by _#.</param>
/// <returns>Success value.</returns>
int create_batch_funcs(const int& count, string& name)
{
    if (!user_data.valid_bp()) abort_program("Invalid Behavior Path at " + user_data.behavior_path + "\nAborting...");

    if(name.empty()) name = "new_func";

    cout << "Function: (use $ to represent the function number)" << endl;
    string function = read_multiline_input();

    for (int i = 0; i < count + 1; i++)
    {
        string write = function;
        replace_all(write, "$", to_string(i));
        overwrite_txt_file(user_data.behavior_path + "/functions/" + name + "_" + to_string(i) + ".mcfunction", write);
    }

    return 0;
}

/// <summary>
/// Creates an animation controller for the provided entities.
/// </summary>
/// <returns>Success value.</returns>
int create_animation_controller()
{
    string func_name;

    cout << "Controller Name:" << endl;
    getline(cin, func_name);

    string query;
    string exit_query;

    cout << "Query:" << endl;
    getline(cin, query);

    cout << "Exit Query:" << endl;
    getline(cin, exit_query);

    string function;
    cout << "Commands:" << endl;

    vector<string> commands;
    while (!cin.eof())
    {
        string line;
        getline(cin, line);

        if (cin.fail())
            break;

        commands.push_back(line);
    }

    for (auto& entity : entities)
    {
        string tmp_func_name = func_name;
        string tmp_func = function;

        entity.add_animation_controller(tmp_func_name, query, exit_query, commands);
    }

    write_entities_to_files();

    create_functions_from_strings(commands);

    return 0;
}

/// <summary>
/// Creates an animation for the provided entities.
/// </summary>
/// <param name="query">An optional conditional query as an animation condition.</param>
/// <returns>Success value.</returns>
int create_animation(string& query)
{
    if (!user_data.valid_bp()) abort_program("Invalid Behavior Path at " + user_data.behavior_path + "\nAborting...");

    string func_name;

    cout << "Animation Name:" << endl;
    getline(cin, func_name);

    string input;
    string anim_length;
    map<string, vector<string>> timeline_entries;
    bool should_loop;
    bool contains_function = false;

    cout << "Animation Length:" << endl;
    getline(cin, input);
    anim_length = input;

    cout << "Looping: [y/n]" << endl;
    getline(cin, input);
    should_loop = input == "Y" || input == "y";

    cout << "Timeline Entries (#.#:command,command):" << endl;
    while (!cin.eof())
    {
        string line;
        getline(cin, line);

        if (cin.fail())
            break;
        if (!contains_function)
            contains_function = line.find("function") != line.npos;

        string time = line.substr(0, line.find(':'));
        string command = line.substr(line.find(':') + 1, line.length());
        vector<string> commands = get_substrings(command, ',');
        timeline_entries.insert({time, commands});
    }

    for (auto& entity : entities)
    {
        entity.add_animation(func_name, anim_length, timeline_entries, should_loop, query);
    }

    write_entities_to_files();

    if (!contains_function)
    {
        return 0;
    }

    for (const auto& entry : timeline_entries)
    {
        create_functions_from_strings(entry.second);
    }

    return 0;
}

/// <summary>
/// Prompts the user to create any non-existant functions detected in the list of commands.
/// </summary>
/// <param name="commands">The list of commands to search for function calls.</param>
/// <returns>Success value.</returns>
int create_functions_from_strings(const vector<string>& commands)
{
    for (const auto& command : commands)
    {
        if (command.find("function") != command.npos && !valid_file(user_data.behavior_path + "/functions/" + command.substr(10)))
        {
            cout << "Function: \"" + command.substr(10) + "\" Does Not Exist" << endl << "Would You Like To Create It? (y/n)";
            cin.clear();
            fflush(stdin);
            string input;
            getline(cin, input);
            if (input != "Y" && input != "y")
                continue;
        }
        else
        {
            continue;
        }

        for (auto& entity : entities)
        {
            string use_name = command;
            replace_all(use_name, "$", entity.identifier());

            cout << "Function:" << endl;
            string function = read_multiline_input();

            string use_function = function;
            replace_all(use_function, "$", entity.identifier());

            overwrite_txt_file(user_data.behavior_path + "/functions/" + use_name.substr(10) + ".mcfunction", use_function);
        }
    }
    return 0;
}

/// <summary>
/// Creates a skin pack using all of the .png files in the working directory.
/// </summary>
/// <param name="name">The name of the skin pack.</param>
/// <returns>Success value.</returns>
int create_skin_pack(const string& name)
{
    // Create skins.json
    vector<string> files = get_directory_files(get_working_directory() + "/", ".png");
    vector<string> loc_names;
    vector<ordered_json> skin_vect;
    vector<string> cape_names;
    for (const auto& file : files)
    {
        if (file.find("cape") != file.npos || file.find("Cape") != file.npos)
        {
            cape_names.push_back(file.substr(file.find_last_of('/') + 1, file.length()));
            continue;
        }

        string file_name = file.substr(file.find_last_of('/') + 1, file.length());
        string loc_name = file_name.substr(0, file_name.find_last_of('_'));
        loc_names.push_back(loc_name);

        ordered_json skin;
        skin["localization_name"] = loc_name;
        skin["geometry"] = file.find("Slim") != file.npos || file.find("slim") != file.npos ? "geometry.humanoid.customSlim" : "geometry.humanoid.custom";
        skin["texture"] = file_name;
        skin["type"] = "paid";

        skin_vect.push_back(skin);
    }

    for (const auto& cape : cape_names)
    {
        string cape_name = cape.substr(0, cape.find_last_of('_'));

        for (auto& skin : skin_vect)
        {
            if (skin["localization_name"] == cape_name)
            {
                skin["cape"] = cape;
            }
        }
    }

    ordered_json skins;
    skins["skins"] = skin_vect;
    skins["serialization_name"] = name;
    skins["localization_name"] = name;
    write_json_to_file(skins, get_working_directory() + "/skins.json");

    // Create manifest.json
    ordered_json mod = { {"version", {1, 0, 0}}, {"type", "skin_pack"}, {"uuid", uuid::generate_uuid_v4()} };
    ordered_json modules[] = {mod};
    ordered_json header = { {"name", "pack.name"}, {"version", {1, 0, 0}}, {"uuid", uuid::generate_uuid_v4()} };
    ordered_json manifest = { {"header", header}, {"modules", modules}, {"format_version", 1} };
    write_json_to_file(manifest, get_working_directory() + "/manifest.json");

    // Create languages.json
    overwrite_txt_file(get_working_directory() + "/texts/languages.json", "[\n\"en_US\"\n]");

    // Create en_US.lang
    string lang = "skinpack." + name + "=" + space_camel_case(name) + "\n" + "pack.name" + "=" + space_camel_case(name) + "\n";
    string prev_name;
    for (const auto& skin_name : loc_names)
    {
        string formatted_name = format_name(skin_name);
        //format_name[0] -= 32;

        if (prev_name != formatted_name)
        {
            lang += "\n";
            prev_name = formatted_name;
        }

        lang += "skin." + name + "." + skin_name + "=" + formatted_name + "\n";
    }
    overwrite_txt_file(get_working_directory() + "/texts/en_US.lang", lang);
    return 0;
}

/// <summary>
/// Creates a new behavior and resource pack in the same folder as the current user bp and rp.
/// </summary>
/// <returns>Success value.</returns>
int create_manifest()
{
    if (!user_data.valid_bp()) abort_program("Invalid Behavior Path at " + user_data.behavior_path + "\nAborting...");

    string bp_name;
    cout << "Behavior Pack Name:" << endl;
    getline(cin, bp_name);

    size_t index = user_data.behavior_path.find("development_behavior_packs") + 27;
    string bp_path = user_data.behavior_path.substr(0, index) + bp_name + "/";

    string rp_name;
    cout << "Resource Pack Name:" << endl;
    getline(cin, rp_name);

    index = user_data.resource_path.find("development_resource_packs") + 27;
    string rp_path = user_data.resource_path.substr(0, index) + rp_name + "/";

    nlohmann::ordered_json manifest = JsonSources::manifest;
    nlohmann::ordered_json sub_manifest = JsonSources::sub_manifest;

    manifest["header"]["uuid"] = uuid::generate_uuid_v4();
    sub_manifest["uuid"] = uuid::generate_uuid_v4();
    sub_manifest["type"] = "data";
    manifest["modules"] = json::array({ sub_manifest });

    write_json_to_file(manifest, bp_path + "manifest.json");
    overwrite_txt_file(bp_path + "texts/en_US.lang", "## BEHAVIOR PACK MANIFEST =======================================================\npack.name=" + bp_name + "\npack.description=This behavior pack is required for " + bp_name + " to run properly");
    write_json_to_file(json({"en_US"}), bp_path + "/texts/languages.json");

    if (!user_data.valid_rp()) abort_program("Invalid Resource Path at " + user_data.resource_path + "\nAborting...");

    manifest["header"]["uuid"] = uuid::generate_uuid_v4();
    sub_manifest["uuid"] = uuid::generate_uuid_v4();
    sub_manifest["type"] = "resources";
    manifest["modules"] = json::array({ sub_manifest });

    write_json_to_file(manifest, rp_path + "manifest.json");
    overwrite_txt_file(rp_path + "/texts/en_US.lang", "## RESOURCE PACK MANIFEST =======================================================\npack.name=" + rp_name + "\npack.description=This resource pack is required for " + rp_name + " to run properly");
    write_json_to_file(json({ "en_US" }), rp_path + "/texts/languages.json");

    return 0;
}

/// <summary>
/// Modifies the damage sensors for the entities.
/// </summary>
/// <param name="include_groups">Should modify damage sensors in component groups as well</param>
/// <returns></returns>
int add_to_damage_sensors(const bool& include_groups)
{
    ordered_json sensor = read_json_from_input("New Damage Sensors:", "Invalid Json\nAborting...", true);

    for (auto& entity : entities)
    {
        entity.add_to_damage_sensor(sensor, include_groups);
    }

    write_entities_to_files();

    return 0;
}

/// <summary>
/// Can be easily altered to make needed changes.
/// </summary>
/// <returns></returns>
int temp_mod()
{
    for (auto& entity : entities)
    {
        entity.entity_json["minecraft:entity"]["description"]["animations"].merge_patch(json({ {"heart_type_6_tagged", "animation.mob.heart_type_6"} }));
        json tmp;
        tmp["heart_type_6_tagged"] = "query.out_of_control";
        entity.entity_json["minecraft:entity"]["description"]["scripts"]["animate"].push_back(tmp);
    }

    write_entities_to_files();

    return 0;
}

/// <summary>
/// Gets a list of entities from provided data.
/// </summary>
/// <param name="family">Families to search for entities</param>
/// <param name="name">File name ending in .json</param>
/// <param name="dir_name">A directory to apply changes to</param>
void get_entities(const string& family, const string& name, const string& dir_name)
{
    if (!user_data.valid_bp()) abort_program("Invalid Behavior Path at " + user_data.behavior_path + "\nAborting...");

    string input;
    vector<bedrock::entity> entities = get_bp_entities(name, family, dir_name);

    if (entities.size() <= 0)
    {
        abort_program("No valid entities found\nAborting...");
    }

    cout << "Found " << entities.size() << " entities" << endl;
}

/// <summary>
/// Write the modified list of entities.
/// </summary>
void write_entities_to_files()
{
    //Confirm input and write file
    string input;
    cout << "Save File(s)? [y/n]" << endl;
    getline(cin, input);
    cout << input << endl;
    if (input == "y" || input == "Y")
    {
        for (auto& entity : entities)
        {
            write_json_to_file(entity.entity_json, entity.file_path, indent);
        }
    }
    else
    {
        cout << "Cancelled" << endl;
    }
}

/// <summary>
/// Aborts program printing message to the terminal.
/// </summary>
/// <param name="message">The message to print to the terminal.</param>
void abort_program(const string& message)
{
    cout << message << endl;
    exit(-1);
}

/// <summary>
/// Main, execution starts here.
/// </summary>
int main(int argc, char** argv) {
    prog_name = argv[0];

    if (argc < 2) {
        show_usage("help");
        return -1;
    }

    string dirArg;
    string family;
    string name;
    string query;
    int opt;
    bool bUseSource = true;
    bool show_help = false;
    bool remove = false;
    bool groups = false;
    int count = 64;

    while ((opt = bed_getopt(argc, argv, "q:i:d:f:n:c:rhg")) != -1) {
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
            case 'r':
                remove = true;
                break;
            case 'g':
                groups = true;
                break;
            case 'q':
                query = bed_optarg;
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
            if (remove)
            {
                get_entities(family, name, dirArg);
                remove_component_group();
            }
            else
            {
                get_entities(family, name, dirArg);
                create_component_group();
            }
            break;
        case eCOMP:
            if (remove)
            {
                get_entities(family, name, dirArg);
                remove_components();
            }
            else
            {
                get_entities(family, name, dirArg);
                create_components();
            }
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
        case eACFUNC:
            get_entities(family, name, dirArg);
            create_animation_controller();
            break;
        case eAFUNC:
            get_entities(family, name, dirArg);
            create_animation(query);
            break;
        case eNMAN:
            create_manifest();
            break;
        case eSKIN:
            create_skin_pack(name);
            break;
        case eDMGS:
            get_entities(family, name, dirArg);
            add_to_damage_sensors(groups);
            break;
        case eTEMP:
            get_entities(family, name, dirArg);
            temp_mod();
            break;
        default:
            show_usage("help");
            break;
    }

    return 0;
}