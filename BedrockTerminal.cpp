// BedrockTerminal.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <map>
#include "getopt.h"
#define DATAFILE "directory.dat"

using namespace std;

struct UserData
{
	std::string resource_path;
	std::string behavior_path;

	UserData(std::string resource_path_in = "", std::string behavior_path_in = "") : resource_path(resource_path_in), behavior_path(behavior_path_in) {}
};

enum CommandList
{
	eRDIR,
	eBDIR
};

static std::map<string, CommandList> mapCommandList;

UserData user_data;

void write_user_data()
{
	std::ofstream fout(DATAFILE);
	fout << user_data.resource_path << ' ' << user_data.behavior_path;
	fout.close();
}

void read_user_data()
{
	std::ifstream fin(DATAFILE);
	fin >> user_data.resource_path >> user_data.behavior_path;
	fin.close();
}

void ShowUsage()
{
	//TODO modify function to show usage examples for a passed command name
	std::cout << "Try 'bed -h' for more information" << std::endl;
}

void write_resource_dir(bool bUseSource, string arg)
{
	std::string path;
	if (bUseSource)
	{
		path = std::filesystem::current_path().string();
	}
	else
	{
		if (arg.empty())
		{
			ShowUsage();
			return;
		}
		path = arg;
	}

	user_data.resource_path = path;
	write_user_data();

	std::cout << "Resource Directory: " << path << std::endl;
	return;
}

void write_behavior_dir(bool bUseSource, string arg)
{
	std::string path;
	if (bUseSource)
	{
		path = std::filesystem::current_path().string();
	}
	else
	{
		if (arg.empty())
		{
			ShowUsage();
			return;
		}
		path = arg;
	}

	user_data.behavior_path = path;
	write_user_data();

	std::cout << "Behavior Directory: " << path << std::endl;
	return;
}

void init_command_list()
{
	mapCommandList["rdir"] = eRDIR;
	mapCommandList["bdir"] = eBDIR;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		ShowUsage();
		return -1;
	}

	char* dirArg = NULL;
	int opt;
	bool bUseSource = true;
	while ((opt = getopt(argc, argv, "d:s")) != -1)
	{
		switch (opt)
		{
		case 's':
			bUseSource = true;
			break;
		case 'd':
			bUseSource = false;
			dirArg = optarg;
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
	default:
		ShowUsage();
		break;
	}

	return 0;
}
