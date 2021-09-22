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