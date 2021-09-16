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

UserData user_data;
string get_path();

void write_user_data()
{
	std::ofstream fout(get_path());
	fout << user_data.resource_path << ' ' << user_data.behavior_path;
	fout.close();
}

void read_user_data()
{
	std::ifstream fin(get_path());
	fin >> user_data.resource_path >> user_data.behavior_path;
	fin.close();
}

bool copy_file(const char* SRC, const char* DEST)
{
	ifstream src(SRC, ios::binary);
	ofstream dest(DEST, ios::binary);
	dest << src.rdbuf();
	return src && dest;
}

#ifdef _WIN32
#include <filesystem>

string get_path()
{
	const char* userpath = getenv("USERPROFILE");
	string path;
	if (userpath != nullptr)
	{
		path = string(userpath) + "\\AppData\\Local\\BedrockTerminal\\" + DATAFILE;
	}
	return path;
}

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

list<string> get_directory_files(const string path)
{
	list<string> files;
	for (const auto& file : std::filesystem::recursive_directory_iterator(path))
		files.push_back(file.path().string());
	return files;
}

int make_directory(const string path)
{
	size_t index = path.find_last_of('/');
	string tmp = path.substr(0, index + 1);
	filesystem::path dir(tmp);
	if (!filesystem::exists(dir))
	{
		cout << "Directory Doesn't Exist. Creating..." << endl;
		filesystem::create_directories(dir);
	}
	return 0;
}



#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

string get_path()
{
	const char* userpath = getenv("HOME");
	string path;
	if (userpath != nullptr)
	{
		path = string(userpath) + "/" + DATAFILE;
	}
	return path;
}

int make_directory(const string path)
{
	size_t index = path.find_last_of('/');
	string tmp = path.substr(0, index + 1);
	const char* p = tmp.c_str();
	mkdir(p, 0777);
	return 0;
}

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
		if (val.find(".json") != string::npos)
		{
			files.push_back(val);
		}
		else if (val.find(".") != string::npos)
		{
			//cout << "Found Sub" << endl;
			list<string> sub_list = get_directory_files(val + "/");
			for (const auto& sub_val : sub_list)
			{
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
