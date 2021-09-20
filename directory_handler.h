#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <limits.h>
#include <list>
#define DATAFILE "bedrock_directory.dat"

using namespace std;

struct UserData
{
	std::string resource_path;
	std::string behavior_path;

	UserData(std::string resource_path_in = "", std::string behavior_path_in = "") : resource_path(resource_path_in), behavior_path(behavior_path_in) {}
};

extern struct UserData user_data;

string get_path();
void write_user_data();
void read_user_data();
int write_resource_dir(bool bUseSource, string arg);
int write_behavior_dir(bool bUseSource, string arg);
list<string> get_directory_files(const string path);
int make_directory(const string path);