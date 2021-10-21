#include "includes/utilities.hpp"

string format_name(string name)
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

float round_second(float var)
{
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}