#pragma once
#include "core.h"
#include <map>
#include "file_manager.hpp"

using namespace std;
using namespace nlohmann;

namespace bedrock
{
	/// <summary>
	/// A class to store and modify entity type JSON.
	/// </summary>
	class entity
	{
	public:
		ordered_json entity_json;
		string file_path;

		const string& identifier();

		entity();
		entity(ordered_json &ent);
		entity(const string& file);
		entity(ordered_json &ent, string file);

		~entity();

		bool does_entity_contain_family(const string& family);
		void add_groups_to_entity(const json& groups); 
		void remove_groups_from_entity(const json& groups);
		void add_to_damage_sensor(const json& sensor, const bool& use_groups);
		void add_animation_controller(const string& anim_name, const string& query, const string& exit_query, const vector<string>& entry_line);
		void add_animation(const string& anim_name, const string& anim_length, const map<string, vector<string>>& timeline_entries, const bool& should_loop, const string& query);
	};

}