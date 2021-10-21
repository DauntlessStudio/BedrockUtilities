#include "includes/entity.h"

using namespace bedrock;

entity::entity() : entity_json(ordered_json()) {}

entity::entity(ordered_json& ent) : entity_json(ent) {}

entity::entity(string file) : file_path(file)
{
    read_json_from_file(entity_json, file_path, "Failed to open json at: " + file_path);
}

entity::entity(ordered_json& ent, string file) : entity_json(ent), file_path(file) {}

entity::~entity() {}

bool entity::does_entity_contain_family(string family)
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

    controller["states"]["effect"]["on_entry"] = entry_line;

    animation_controller["animation_controllers"]["controller.animation." + name + "." + anim_title_name] = controller;
    write_json_to_file(animation_controller, user_data.behavior_path + "/animation_controllers/" + name + ".animation_controller.json", 2);
    return;
}

void entity::add_animation(const string& anim_name, const float& anim_length, const float& time_entry, const bool& should_loop, const vector<string>& commands)
{
    make_directory(user_data.behavior_path + "/animation_controllers/");
    string full_name = entity_json["minecraft:entity"]["description"]["identifier"];
    size_t index = full_name.find(':') + 1;
    string name = full_name.substr(index, full_name.length() - index);
    string anim_title_name = anim_name;
    replace_all(anim_title_name, "/", ".");
    replace_all(anim_title_name, name + ".", "");

    entity_json["minecraft:entity"]["description"]["animations"].merge_patch(json({ {anim_title_name, "animation." + name + "." + anim_title_name} }));
    entity_json["minecraft:entity"]["description"]["scripts"]["animate"].push_back(anim_title_name);

    ordered_json animation = nlohmann::ordered_json::parse(R"({"format_version": "1.10.0", "animations": {}})");

    read_json_from_file(animation, user_data.behavior_path + "/animations/" + name + ".json", "Creating Animation...");

    ordered_json anim;
    anim["animation_length"] = anim_length;
    anim["loop"] = should_loop;
    anim["timeline"] = nlohmann::ordered_json({ {to_string(time_entry), commands} });

    animation["animations"]["animation." + name + "." + anim_title_name] = anim;
    write_json_to_file(animation, user_data.behavior_path + "/animations/" + name + ".json", 2);
    return;
}
