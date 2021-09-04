// BedrockTerminal.cpp : This file contains the 'main' function. Program execution begins and ends there.#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "getopt.h"
#include "json.hpp"
#include "DirectoryHandler.h"

using namespace std;
using json = nlohmann::json;

enum CommandList
{
	eRDIR,
	eBDIR,
	eCOGR
};

static std::map<string, CommandList> mapCommandList;

void ShowUsage(string command)
{
	//TODO modify function to show usage examples for a passed command name
	std::cout << "Try 'bed -h' for more information" << std::endl;
}

void init_command_list()
{
	mapCommandList["rdir"] = eRDIR;
	mapCommandList["bdir"] = eBDIR;
	mapCommandList["cogr"] = eCOGR;
}

int write_component_group(string family, string name, bool bUseReset)
{
	if (!name.empty())
	{
		//Get file from name
		ifstream i(user_data.behavior_path + "/entities/" + name + ".json");
		if (i.fail())
		{
			cerr << user_data.behavior_path + "/entities/" + name + ".json\nThe specified file doesn't exist." << endl;
			return -1;
		}

		//Get an ordered_json copy of the entity to preserve json order
		nlohmann::ordered_json entity;
		i >> entity;
		i.close();

		//Get component group input
		string input;
		std::cout << "New Component Group:" << endl;
		getline(cin, input);
		input = "{" + input + "}";
		json jo = json::parse(input);

		//Merge input into enity
		entity["minecraft:entity"]["component_groups"].merge_patch(jo);

		//Write modified entity
		ofstream o(user_data.behavior_path + "/entities/" + name + ".json");
		o << setw(2) << entity << endl;
		o.close();

		return 0;
	}

	return 0;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		ShowUsage("help");
		return -1;
	}

	string dirArg;
	string family;
	string name;
	int opt;
	bool bUseSource = true;
	bool bUseReset = false;

	while ((opt = bed_getopt(argc, argv, "d:f:n:sr")) != -1)
	{
		switch (opt)
		{
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
		case 'r':
			bUseReset = true;
			break;
		default:
			break;
		}
	}

	read_user_data();
	init_command_list();

	switch (mapCommandList[argv[argc-1]])
	{
	case eRDIR:
		write_resource_dir(bUseSource, dirArg);
		break;
	case eBDIR:
		write_behavior_dir(bUseSource, dirArg);
		break;
	case eCOGR:
		write_component_group(family, name, bUseReset);
		break;
	default:
		ShowUsage("help");
		break;
	}

	return 0;
}
