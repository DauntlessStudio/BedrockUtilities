#pragma once
#include "core.h"
#include "file_manager.hpp"

using namespace std;
using namespace nlohmann;

namespace bedrock
{
	class entity
	{
	public:
		ordered_json entity_json;
		string file_path;

		entity();
		entity(ordered_json &ent);
		entity(string file);
		entity(ordered_json &ent, string file);

		~entity();

		bool does_entity_contain_family(string family);
		void add_groups_to_entity(const json& groups);
		void add_animation_controller(const string anim_name, const string query, const string exit_query, const string entry_line);
	};

}