#include "includes/file_manager.hpp"
#include "includes/entity.h"

/// <summary>
/// Writes a JSON object to a file.
/// </summary>
/// <param name="object">The JOSN object to write.</param>
/// <param name="path">The path to find a JSON file at.</param>
/// <param name="spacing">The indentation of the JSON file.</param>
/// <returns>Success value.</returns>
int write_json_to_file(const nlohmann::ordered_json& object, string path, int spacing)
{
    //Write modified entity
    make_directory(path);
    ofstream o(path);

	try
	{
		o << setw(spacing) << object << endl;
	}
	catch (const std::exception&)
	{
		cerr << "Error writing json at: " << path << endl;
        return -1;
	}

    cout << "Saved json at: " + path << endl;
    o.close();

    return 0;
}

/// <summary>
/// Reads a JSON object from a file.
/// </summary>
/// <param name="object">The new JSON object.</param>
/// <param name="path">The path to read a JSON file from.</param>
/// <param name="error_message">An error message to pring if reading fails.</param>
/// <returns>Success value.</returns>
int read_json_from_file(nlohmann::ordered_json& object, string path, string error_message)
{
    ifstream i;
    i.open(path);

    try
    {
        object = nlohmann::ordered_json::parse(i, nullptr, true, true);
    }
    catch (const std::exception& e)
    {
        cout << error_message << endl;
        cerr << e.what() << endl;
        return -1;
    }

    i.close();

    return 0;
}

/// <summary>
/// Reads a JSON object from the user's input.
/// </summary>
/// <param name="input_message">The message to print to the user.</param>
/// <param name="error_message">The message to pring if the JSON is invalid.</param>
/// <param name="abort_on_fail">Should the program exit if reading fails?</param>
/// <returns>The new JSON from the input.</returns>
nlohmann::ordered_json read_json_from_input(string input_message, string error_message, bool abort_on_fail)
{
    cout << input_message << endl;
    string input = read_multiline_input();

    if (input[0] != '{')
    {
        input.insert(0, "{");
        input.push_back('}');
    }

    ordered_json jo;
    try
    {
        jo = ordered_json::parse(input, nullptr, true, false);
    }
    catch (...)
    {
        cerr << error_message << endl;
        if(abort_on_fail) exit(-1);
    }

    return jo;
}

/// <summary>
/// Writes a string to a given path, overwriting the file if it exists already.
/// </summary>
/// <param name="path">The path to write to.</param>
/// <param name="entry">The string to write.</param>
/// <returns>Success value.</returns>
int overwrite_txt_file(string path, string entry)
{
    make_directory(path);
    ofstream o;
    o.open(path);

    o << entry;

    cout << "Wrote File At: " + path << endl;
    o.close();

    return 0;
}

/// <summary>
/// Writes a string to a given path, appending to the file if it exists already.
/// </summary>
/// <param name="path">The path to write to.</param>
/// <param name="entry">The string to append.</param>
/// <returns>Success value.</returns>
int append_txt_file(string path, string entry)
{
    make_directory(path);
    cout << "Adding Entry to: " + path << endl;
    ofstream o;
    o.open(path, ios_base::app);

    o << endl << entry;

    o.close();

    return 0;
}

/// <summary>
/// Copies a file from the source path to the destination path.
/// </summary>
/// <param name="SRC">The source path.</param>
/// <param name="DEST">The destination path.</param>
/// <returns>True if the copy succeeded.</returns>
bool copy_file(const char* SRC, const char* DEST)
{
    ifstream src(SRC, ios::binary);
    ofstream dest(DEST, ios::binary);
    dest << src.rdbuf();
    return src && dest;
}

/// <summary>
/// Writes a png texture to a path.
/// </summary>
/// <param name="png">The png to write.</param>
/// <param name="path">The destination path.</param>
/// <param name="width">The png width.</param>
/// <param name="height">The png height.</param>
void write_texture_to_file(vector<unsigned char> png, string path, int width, int height)
{
    make_directory(path);

    if (png.empty())
    {
        std::vector<unsigned char> image;
        image.resize(width * height * 4);
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
            {
                image[4 * width * y + 4 * x + 0] = 255 * ~(x & y);
                image[4 * width * y + 4 * x + 1] = x ^ y;
                image[4 * width * y + 4 * x + 2] = x | y;
                image[4 * width * y + 4 * x + 3] = 255;
            }

        unsigned error = lodepng::encode(png, image, width, height);
        cout << "Creating New Texture..." << endl;
    }

    lodepng::save_file(png, path);
    cout << "Saved Texture At: " + path << endl;
}

/// <summary>
/// Gets all behavior pack entity files from the user data bp that match the filters.
/// </summary>
/// <param name="name">The file names, seperated by commas.</param>
/// <param name="family">The family type to search for.</param>
/// <returns>A vector of entities.</returns>
vector<bedrock::entity> get_bp_entities(string name, string family, string dir_name)
{
    vector<bedrock::entity> entities;
    if (!name.empty())
    {
        vector<string> names = get_substrings(name, ',');
        for (const auto& file : names)
        {
            bedrock::entity entity(user_data.behavior_path + "/entities/" + file + ".json");
            entities.push_back(entity);
        }
    }
    else
    {
        vector<string> files = get_directory_files(user_data.behavior_path + "/entities/" + dir_name, ".json");
        for (const auto& file : files)
        {
            bedrock::entity entity(file);

            if (!family.empty() && entity.does_entity_contain_family(family))
            {
                entities.push_back(entity);
            }
            else if (family.empty())
            {
                entities.push_back(entity);
            }
        }
    }
    return entities;
}