#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <limits.h>
#include <list>
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
		path = std:: filesystem::current_path().string();
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

list<string> get_directory_files(const string path)
{
	list<string> files;
	for (const auto& file : std::filesystem::recursive_directory_iterator(path))
		files.push_back(file.path().string());
	return files;
}

#else
#include <unistd.h>
list<string> get_directory_files(const string path)
{
	list<string> files;
	string tmp_str = "ls " + path;
	char* command = new char[tmp_str.size()];
	std::copy(tmp_str.begin(), tmp_str.end(), command);
	FILE* proc = popen(command, "r");
	char buf[1024];
	while (!feof(proc) && fgets(buf, sizeof(buf), proc))
	{
	    string val = path + buf;
	    val.erase(remove(val.begin(), val.end(), '\n'), val.end());
	    if(val.find(".json") != string::npos) {
		files.push_back(val);
	    }else if (val.find(".") != string::npos){
	        //cout << "Found Sub" << endl;
	        list<string> sub_list = get_directory_files(val + "/");
	        for (const auto& sub_val : sub_list) {
	            files.push_back(sub_val);
	        }
	    }
	}
	return files;
}

int write_resource_dir(bool bUseSource, string arg)
{
	std::string path;
	if (bUseSource)
	{
		char buffer[PATH_MAX];
		getcwd(buffer, sizeof(buffer));
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
		getcwd(buffer, sizeof(buffer));
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