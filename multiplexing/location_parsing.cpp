#include "header.hpp"

extern int server_index;

void parse_root_path(size_t &index)
{
    if (index + 2 >= Conf_File::tokens.size())
        throw Error::Root();
    if (Conf_File::tokens[index + 2] !=  ";")
        throw Error::SemiColon();
    if (path_file_exists(Conf_File::tokens[index + 1]))
        throw std::runtime_error(Conf_File::tokens[index + 1] + " : No such File or Directory!.");
    Conf_File::Servers[server_index].location.root = next_token(Conf_File::tokens, index);
    index += 2;
}

void parse_autoindex(size_t &index)
{
    if (index + 2 >= Conf_File::tokens.size())
        throw Error::Root();
    if (Conf_File::tokens[index + 2] !=  ";")
        throw Error::SemiColon();
    if (!is_autoindex_id(Conf_File::tokens[index + 1]))
        throw Error::Unkonwn_Directive_value();
    Conf_File::Servers[server_index].location.autoindex = next_token(Conf_File::tokens, index);
    index += 2;
}


void parse_upload_store(size_t &index)
{
    if (index + 2 >= Conf_File::tokens.size())
        throw Error::Root();
    if (Conf_File::tokens[index + 2] !=  ";")
        throw Error::SemiColon();
    if (path_file_exists(Conf_File::tokens[index + 1]))
    {
        if (mkdir(Conf_File::tokens[index + 1].c_str(), 777) != 0)
            throw std::runtime_error("Could not create the path : " + Conf_File::tokens[index + 1]);
    }
    Conf_File::Servers[server_index].location.upload_path = next_token(Conf_File::tokens, index);
    index += 2;
}

void parse_methods(size_t &index)
{
    size_t i = 0;
    if (index + 2 >= Conf_File::tokens.size())
        throw Error::Methods();
    index++;
    // std::cout << "reached\n";
    // std::cout << next_token(Conf_File::tokens, index);
    while (i < Conf_File::tokens.size() && Conf_File::tokens[index] != ";")
    {
        if (!is_http_method(Conf_File::tokens[index]))
            throw Error::Unkonwn_Directive_value();
        Conf_File::Servers[server_index].location.allowed_methods.push_back(Conf_File::tokens[index++]);
        i++;
    }
    if (index >= Conf_File::tokens.size())
        throw Error::UnexpectedEndOfFile();
    index++;
}

void parse_cgi_extension(size_t &index)
{
    if (index + 2 >= Conf_File::tokens.size() || Conf_File::tokens[index + 1][0] != '.')
        throw Error::CGI_Extension();
    if (Conf_File::tokens[index + 2] !=  ";")
        throw Error::SemiColon();
    Conf_File::Servers[server_index].location.cgi_extension = next_token(Conf_File::tokens, index);
    index += 2;
}

void parse_cgi_path(size_t &index)
{
    if (index + 2 >= Conf_File::tokens.size())
        throw Error::CGI_Extension();
    if (Conf_File::tokens[index + 2] !=  ";")
        throw Error::SemiColon();
    if (!path_file_exists(Conf_File::tokens[index + 1]))
        throw Error::CGI_Path();
    Conf_File::Servers[server_index].location.cgi_path = next_token(Conf_File::tokens, index);
    index += 2;
}

void parse_return(size_t &index)
{
    // size_t i = 0;
    if (index + 2 >= Conf_File::tokens.size())
        throw Error::Root();
    if (Conf_File::tokens[index + 2] != ";")
        throw Error::Root();
    
}