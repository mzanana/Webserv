#include "header.hpp"

// bool curly_brackets_even()

bool is_comment(std::string& line)
{
    size_t i = 0;
    while(line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == '#' || i == line.size())
        return true;
    else 
        return false;
    return true;
}

void skip_white_spaces(std::string& line, size_t &i)
{
    while (line[i] == ' ' || line[i] == '\t')
        i++;
}

void skip_directive(std::string& line, size_t &i)
{
    while (i < line.size() && !isspace(line[i]))
        i++;
}

bool path_file_exists(std::string& name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}