#include "includes/entity.h"

using namespace bedrock;

/// <summary>
/// Default constructor. Creates a new entity as an empty ordered JSON object.
/// </summary>
entity::entity() : entity_json(ordered_json()) {}

/// <summary>
/// Constructor. Creates a new entity from an ordered JSON object.
/// </summary>
/// <param name="ent">The ordered JSON object</param>
entity::entity(ordered_json& ent) : entity_json(ent) {}

/// <summary>
/// Constructor. Creates a new entity from a JSON file on disk.
/// </summary>
/// <param name="file">The file path.</param>
entity::entity(const string& file) : file_path(file)
{
    read_json_from_file(entity_json, file_path, "Failed to open json at: " + file_path);
}

/// <summary>
/// Constructor. Creates a new entity from an ordered JSON object, and initializes it's file path.
/// </summary>
/// <param name="ent">The ordered JSON.</param>
/// <param name="file">The file path for the entity.</param>
entity::entity(ordered_json& ent, string file) : entity_json(ent), file_path(file) {}

/// <summary>
/// Default destructor.
/// </summary>
entity::~entity() {}

/// <summary>
/// Does the entity contain the provided family type?
/// </summary>
/// <param name="family">The family type to search for.</param>
/// <returns>True if the provided family type was found.</returns>
bool entity::does_entity_contain_family(const string& family)
{
    for (const auto& it : entity_json["minecraft:entity"]["components"]["minecraft:type_family"]["family"].items())
    {
        if (it.value() == family)
        {
            return true;
        }
    }

    for (const auto& it : entity_json["minecraft:entity"]["component_groups"].items())
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

/// <summary>
/// Adds component groups to this entity.
/// </summary>
/// <param name="groups">The component groups to add.</param>
void entity::add_groups_to_entity(const json& groups)
{
    //Process resets
    json groups_tmp = groups;

    for (auto& el : groups.items())
    {
        json tmp;
        for (auto& it : el.value().items())
        {

            if (el.key().find("reset") != string::npos)
            {
                tmp.merge_patch(entity_json["minecraft:entity"]["components"][it.key()]);

                if (!tmp.empty())
                {
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
    entity_json["minecraft:entity"]["component_groups"].merge_patch(groups_tmp);

    //Create events
    ordered_json events;
    for (auto& el : groups.items())
    {
        if (el.key().find("reset") != string::npos) continue;

        string val[] = { el.key() };
        string val_reset[] = { el.key() + "_reset" };

        if (groups_tmp.contains(el.key() + "_reset"))
        {
            events[el.key() + "_reset"]["add"]["component_groups"] = val_reset;
        }

        events[el.key()]["add"]["component_groups"] = val;
        events[el.key() + "_reset"]["remove"]["component_groups"] = val;
    }

    //Merge events
    entity_json["minecraft:entity"]["events"].merge_patch(events);

    string name = entity_json["minecraft:entity"]["description"]["identifier"];
    cout << name + ":\n" << "Adding Component Groups:\n" << LINE_GREEN << groups_tmp.dump(2) << LINE_RESET << "\nAdding Events:\n" << LINE_GREEN << events.dump(2) << LINE_RESET << endl;
    
    return;
}

/// <summary>
/// Removes component groups from this entity.
/// </summary>
/// <param name="groups">The component groups to remove.</param>
void entity::remove_groups_from_entity(const json& groups)
{
    for (auto& el : groups.items())
    {
        entity_json["minecraft:entity"]["component_groups"].erase(el.key());
        entity_json["minecraft:entity"]["component_groups"].erase(el.key() + "_reset");
        entity_json["minecraft:entity"]["events"].erase(el.key());
        entity_json["minecraft:entity"]["events"].erase(el.key() + "_reset");
    }

    return;
}

/// <summary>
/// Adds a new animation controller to this entity.
/// </summary>
/// <param name="anim_name">The animation name.</param>
/// <param name="query">The query to advance the animation state.</param>
/// <param name="exit_query">The query to return to the default animation state.</param>
/// <param name="entry_line">The commands to run when the animation state is entered.</param>
void entity::add_animation_controller(const string& anim_name, const string& query, const string& exit_query, const vector<string>& entry_line)
{
    make_directory(user_data.behavior_path + "/animation_controllers/");
    string full_name = entity_json["minecraft:entity"]["description"]["identifier"];
    size_t index = full_name.find(':') + 1;
    string name = full_name.substr(index, full_name.length() - index);
    string anim_title_name = anim_name;
    replace_all(anim_title_name, "/", ".");
    replace_all(anim_title_name, name + ".", "");

    entity_json["minecraft:entity"]["description"]["animations"].merge_patch(json({ {anim_title_name, "controller.animation." + name + "." + anim_title_name} }));
    entity_json["minecraft:entity"]["description"]["scripts"]["animate"].push_back(anim_title_name);

    ordered_json animation_controller = nlohmann::ordered_json::parse(R"({"format_version": "1.10.0", "animation_controllers": {}})");

    read_json_from_file(animation_controller, user_data.behavior_path + "/animation_controllers/" + name + ".animation_controller.json", "Creating Controller...");

    ordered_json controller;
    controller["states"]["default"]["transitions"] = json::array({ json({{ "effect", query }}) });
    if (!exit_query.empty())
    {
        controller["states"]["effect"]["transitions"] = json::array({ json({{"default", exit_query}}) });
    }

    vector<string> use_entries;
    for (string element : entry_line)
    {
        string val = element;
        replace_all(val, "$", name);
        use_entries.push_back(val);
    }
    controller["states"]["effect"]["on_entry"] = use_entries;

    animation_controller["animation_controllers"]["controller.animation." + name + "." + anim_title_name] = controller;
    write_json_to_file(animation_controller, user_data.behavior_path + "/animation_controllers/" + name + ".animation_controller.json", 2);
    return;
}

/// <summary>
/// Adds a new animation to this entity.
/// </summary>
/// <param name="anim_name">The animation name.</param>
/// <param name="anim_length">The duration of the animation.</param>
/// <param name="timeline_entries">The entries in the timetable, with the key being the time, and the value being the commands to execute.</param>
/// <param name="should_loop">Should this animation loop?</param>
/// <param name="query">An optional query to play this animation based on a condition.</param>
void entity::add_animation(const string& anim_name, const string& anim_length, const map<string, vector<string>>& timeline_entries, const bool& should_loop, const string& query)
{
    make_directory(user_data.behavior_path + "/animation_controllers/");
    string full_name = entity_json["minecraft:entity"]["description"]["identifier"];
    size_t index = full_name.find(':') + 1;
    string name = full_name.substr(index, full_name.length() - index);
    string anim_title_name = anim_name;
    replace_all(anim_title_name, "/", ".");
    replace_all(anim_title_name, name + ".", "");

    entity_json["minecraft:entity"]["description"]["animations"].merge_patch(json({ {anim_title_name, "animation." + name + "." + anim_title_name} }));
    if (query.empty())
    {
        entity_json["minecraft:entity"]["description"]["scripts"]["animate"].push_back(anim_title_name);
    }
    else
    {
        json tmp;
        tmp[anim_title_name] = query;
        entity_json["minecraft:entity"]["description"]["scripts"]["animate"].push_back(tmp);
    }

    ordered_json animation = nlohmann::ordered_json::parse(R"({"format_version": "1.10.0", "animations": {}})");

    read_json_from_file(animation, user_data.behavior_path + "/animations/" + name + ".json", "Creating Animation...");

    ordered_json anim;
    anim["animation_length"] = stof(anim_length);
    anim["loop"] = should_loop;
    nlohmann::ordered_json timeline;
    for (const auto& entry : timeline_entries)
    {
        vector<string> use_values;
        for (string element : entry.second)
        {
            string val = element;
            replace_all(val, "$", name);
            use_values.push_back(val);
        }
        timeline[entry.first] = use_values;
    }
    anim["timeline"] = timeline;

    animation["animations"]["animation." + name + "." + anim_title_name] = anim;
    write_json_to_file(animation, user_data.behavior_path + "/animations/" + name + ".json", 2);
    return;
}
