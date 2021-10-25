#include "includes/directory_handler.h"

struct UserData user_data;

/// <summary>
/// Writes the user data struct to the directory.dat.
/// </summary>
void write_user_data()
{
	std::ofstream fout(get_path());
	fout << user_data.resource_path << ' ' << user_data.behavior_path;
	fout.close();
}

/// <summary>
/// Reades the directory.dat file into the user data struct.
/// </summary>
void read_user_data()
{
	std::ifstream fin(get_path());
	fin >> user_data.resource_path >> user_data.behavior_path;
	fin.close();
}

/// <summary>
/// Checks if the development behavior pack is valid.
/// </summary>
/// <returns>True if the bp is valid.</returns>
bool UserData::valid_bp()
{
	return behavior_path.find("development_behavior_packs") != string::npos;
}

/// <summary>
/// Checks if the development resource pack is valid.
/// </summary>
/// <returns>True if the rp is valid.</returns>
bool UserData::valid_rp()
{
	return resource_path.find("development_resource_packs") != string::npos;
}

/// <summary>
/// Checks if a given file exists.
/// </summary>
/// <param name="path">The path of the file.</param>
/// <returns>True if the file exists.</returns>
bool valid_file(const string& path)
{
	ifstream i(path.c_str());
	return i.good();
}

#ifdef _WIN32
#include <filesystem>

/// <summary>
/// Gets the Windows path of the directory.dat path.
/// </summary>
/// <returns>The path to directory.dat.</returns>
string get_path()
{
	const char* userpath = getenv("USERPROFILE");
	string path;
	if (userpath != nullptr)
	{
		path = string(userpath) + "\\AppData\\Local\\BedrockUtilities\\" + DATAFILE;
	}
	return path;
}

/// <summary>
/// Gets the working directory of the terminal.
/// </summary>
/// <returns>The string path of the working directory.</returns>
string get_working_directory()
{
	return std::filesystem::current_path().string();
}

/// <summary>
/// Writes a new resource development pack path to directory.dat.
/// </summary>
/// <param name="bUseSource">Should the working directory be used?</param>
/// <param name="arg">The path to the new rp.</param>
/// <returns>Success value.</returns>
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

/// <summary>
/// Writes a new behavior development pack path to directory.dat.
/// </summary>
/// <param name="bUseSource">Should the working directory be used?</param>
/// <param name="arg">The path to the new bp.</param>
/// <returns>Success value.</returns>
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

/// <summary>
/// Gets all files recursively in the given path.
/// </summary>
/// <param name="path">The path to check files for.</param>
/// <param name="filter">A filter that files must contain, such as (.png).</param>
/// <returns>A string vector of file paths.</returns>
vector<string> get_directory_files(const string path, const string filter)
{
	vector<string> files;
	for (const auto& file : std::filesystem::recursive_directory_iterator(path))
	{
		if (file.path().string().find(filter) != string::npos)
		{
			files.push_back(file.path().string());
		}
	}
		
	return files;
}

/// <summary>
/// Makes a new directory at given path.
/// </summary>
/// <param name="path">The path to create a directory at.</param>
/// <returns>Success value.</returns>
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

string get_working_directory()
{
	char buffer[PATH_MAX];
	getcwd(buffer, sizeof(buffer));
	string path = buffer;
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

vector<string> get_directory_files(const string path, const string filter)
{
	vector<string> files;
	string tmp_str = "ls " + path;
	char* command = new char[tmp_str.size()];
	std::copy(tmp_str.begin(), tmp_str.end(), command);
	FILE* proc = popen(command, "r");
	char buf[1024];
	while (!feof(proc) && fgets(buf, sizeof(buf), proc))
	{
		string val = path + buf;
		val.erase(remove(val.begin(), val.end(), '\n'), val.end());
		if (val.find(filter) != string::npos)
		{
			files.push_back(val);
		}
		else if (val.find(".") != string::npos)
		{
			//cout << "Found Sub" << endl;
			vector<string> sub_vector = get_directory_files(val + "/", filter);
			for (const auto& sub_val : sub_vector)
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
