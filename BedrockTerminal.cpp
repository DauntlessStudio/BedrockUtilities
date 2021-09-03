// BedrockTerminal.cpp : This file contains the 'main' function. Program execution begins and ends there.#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "getopt.h"
#include "DirectoryHandler.h"

using namespace std;

enum CommandList
{
	eRDIR,
	eBDIR
};

static std::map<string, CommandList> mapCommandList;


void ShowUsage()
{
	//TODO modify function to show usage examples for a passed command name
	std::cout << "Try 'bed -h' for more information" << std::endl;
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

	string dirArg;
	int opt;
	bool bUseSource = true;

	while ((opt = bed_getopt(argc, argv, "d:s")) != -1)
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
