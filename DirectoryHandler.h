#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <limits.h>
#define DATAFILE "directory.dat"

using namespace std;

struct UserData
{
	std::string resource_path;
	std::string behavior_path;

	UserData(std::string resource_path_in = "", std::string behavior_path_in = "") : resource_path(resource_path_in), behavior_path(behavior_path_in) {}
};

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

#ifdef _WIN32
#include <filesystem>
int write_resource_dir(bool bUseSource, string arg)
{
	cout << "Write Path" << endl;
	std::string path;
	if (bUseSource)
	{
		path = std::filesystem::current_path().string();
	}
	else
	{
		if (arg.empty())
		{
			return 0;
		}
		path = arg;
	}

	user_data.resource_path = path;
	write_user_data();

	std::cout << "Resource Directory: " << path << std::endl;
	return 1;
}

int write_behavior_dir(bool bUseSource, string arg)
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
			return 0;
		}
		path = arg;
	}

	user_data.behavior_path = path;
	write_user_data();

	std::cout << "Behavior Directory: " << path << std::endl;
	return 1;
}
#else
#include <unistd.h>
int write_resource_dir(bool bUseSource, string arg)
{
	std::string path;
	if (bUseSource)
	{
		char buffer[PATH_MAX];
		getcwd(buffer, sizeof(buffer) != NULL);
		path = buffer;
	}
	else
	{
		if (arg.empty())
		{
			return 0;
		}
		path = arg;
	}

	user_data.resource_path = path;
	write_user_data();

	std::cout << "Resource Directory: " << path << std::endl;
	return 1;
}

int write_behavior_dir(bool bUseSource, string arg)
{
	std::string path;
	if (bUseSource)
	{
		char buffer[PATH_MAX];
		getcwd(buffer, sizeof(buffer) != NULL);
		path = buffer;
	}
	else
	{
		if (arg.empty())
		{
			return 0;
		}
		path = arg;
	}

	user_data.behavior_path = path;
	write_user_data();

	std::cout << "Behavior Directory: " << path << std::endl;
	return 1;
}
#endif // _WIN32