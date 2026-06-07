#include "header.hpp"
#include "Error.hpp"

std::string next_token(std::vector<std::string>& vector , size_t &i)
{
    if (i >= vector.size())
        throw Error::UnexpectedEndOfFile();
    return vector[i++];
}

void expected_token(std::vector<std::string>& vector, size_t &i, std::string& expected)
{
    std::string token = next_token(vector, i);
    if (token != expected)
        throw Error::SyntaxError();
}

void validate_file()
{
    size_t i = 0;
    size_t brace = 0;
    while (i < Conf_File::tokens.size())
    {
        if (Conf_File::tokens[i] == "{")
            brace++;
        else if (Conf_File::tokens[i] == "}")
            brace--;
        if (brace > 1)
            throw Error::Right_Brace();
        else if (brace < 0)
            throw Error::Left_Brace();
        i++;
    }
}

