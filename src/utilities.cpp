#include "includes/utilities.hpp"

/// <summary>
/// Removes underscores and capitilizes words in the provided string.
/// </summary>
/// <param name="name">The string to format.</param>
/// <returns>The formatted string.</returns>
string format_name(const string& name)
{
    string lang_name = name;
    bool caps_next = true;
    for (size_t i = 0; i < name.length(); i++)
    {
        if (caps_next)
        {
            lang_name[i] = toupper(lang_name[i]);
            caps_next = false;
        }

        if (name[i] == '_')
        {
            lang_name[i] = ' ';
            caps_next = true;
        }
    }

    return lang_name;
}

/// <summary>
/// Replaces all instances of the From string with the To string in the referenced string.
/// </summary>
/// <param name="str">The string to modify.</param>
/// <param name="from">The value to replace.</param>
/// <param name="to">The replacing value.</param>
void replace_all(std::string& str, const std::string& from, const std::string& to)
{
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

/// <summary>
/// Reads multiline CIN inputs.
/// </summary>
/// <returns>The multiline string value.</returns>
string read_multiline_input()
{
    string multiline;

    while (!cin.eof())
    {
        string line;
        getline(cin, line);

        if (cin.fail())
            break;

        multiline += line + '\n';
    }

    multiline.erase(multiline.end() - 1); // Remove Trailing \n
    cin.clear();
    return multiline;
}

/// <summary>
/// Spaces out camel case values.
/// </summary>
/// <param name="ref">The camel case string.</param>
/// <returns>The formatted string.</returns>
string space_camel_case(const string& ref)
{
    string value;
    for (size_t i = 0; i < ref.length(); i++)
    {
        if (ref[i] >= 'A' && ref[i] <= 'Z' && i > 0)
        {
            value += " ";
        }

        value += ref[i];
    }
    return value;
}

/// <summary>
/// Gets substrings based on a delimating character.
/// </summary>
/// <param name="ref">The string to search.</param>
/// <param name="deliminator">The delimating character.</param>
/// <returns>A vector of substrings.</returns>
vector<string> get_substrings(const string& ref, const char& deliminator)
{
    vector<string> result;
    stringstream s_stream(ref);

    while (s_stream.good())
    {
        string substr;
        getline(s_stream, substr, deliminator);
        result.push_back(substr);
    }

    return result;
}

/// <summary>
/// Rounds a float to the second decimal place.
/// </summary>
/// <param name="var">The float to round.</param>
/// <returns>The rounded float.</returns>
float round_second(float var)
{
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}