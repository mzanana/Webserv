#include "header.hpp"
#include "Error.hpp"

bool isKnownDirective(const std::string& token)
{
    return (token == "listen" || token == "host" || token == "server_name" ||
            token == "root" || token == "index" || token == "client_max_body_size" ||
            token == "error_page" || token == "allowed_methods" || token == "autoindex" ||
            token == "return" || token == "cgi_extension" || token == "cgi_path" ||
            token == "upload_store");
}

// void minimal_directives_exists(std::string& token)
// {
//     if (token == "location")
//         Conf_File::
// }

void parse_config_file()
{
    size_t i = 0;
    // size_t server_index = 0;
    bool in_server = false;
    size_t depth = 0;
    while (i < Conf_File::tokens.size())
    {
        std::string token = Conf_File::tokens[i];
        if (token == "server")
        {
            // std::cout << "reached 2 \n";
            if (depth > 0)
                throw std::runtime_error("Error\n'server' block cannot be nested inside another block!.");
            if (i + 1 >= Conf_File::tokens.size() || Conf_File::tokens[i + 1] != "{")
                throw std::runtime_error("Error\nExpected '{' right after 'server'");
            in_server = true;
            depth++;
            i++;
        }
        else if (token == "location")
        {
            if (!in_server)
                throw std::runtime_error("Error\n'location' directive cannot be nested outside 'server'!.");
            if (i + 2 >= Conf_File::tokens.size() || Conf_File::tokens[i + 2] != "{")
                throw std::runtime_error("Error\nExpected '{' after 'location <path>'!.");
            depth++;
            i += 2;
        }
        else if (token == "{")
            throw std::runtime_error("Error\nUnexpected '{'. only 'server' or 'location' can open a block!.");
        else if (token == "}")
        {
            depth--;
            if (depth < 0)
                throw std::runtime_error("Error\nUnbalanced '}'. too many closing braces!.");
            if (depth == 0)
                in_server = false;
        }
        else if (token != ";")
        {
            if (isKnownDirective(token))
            {
                if (!in_server)
                    throw std::runtime_error("Error\nDirective '" + token + "' found outside 'server' block!.");

            }
        }
    }
    if (depth != 0)
        throw std::runtime_error("Error\nUnclosed block at the end of the file!.");
}

// void parse_root_dir(std::string& line, size_t server_index)
// {
//     size_t i = 0;
//     size_t end = (line.size() - 1);
//     while (end > 0 && isspace(line[end]))
//             end--;
//     if (line[end] != ';')
//         throw Error::Root();
//     skip_white_spaces(line, i);
//     skip_directive(line, i);
//     if (i == line.size() || !isspace(line[i]))
//         throw Error::Root();
//     skip_white_spaces(line, i);
//     if (line[i] != '/')
//         throw Error::Root();
//     size_t start = i;
//     end;
//     while(i < line.size() && !isspace(line[i] && line[i] != ';'))
//         i++;
//     end = i;
//     if (end == start)
//         throw Error::Root();
//     Conf_File::Servers[server_index].root = line.substr(start, end - start);
//     if (!path_file_exists(Conf_File::Servers[server_index].root))
//         throw Error::Root();
// }

// void Parse_host(std::string& line, size_t server_index)
// {
//     size_t i = 0;
//     size_t dot_count = 0;
//     size_t end = (line.size() - 1);
//     while (end > 0 && isspace(line[end]))
//             end--;
//     if (line[end] != ';')
//         throw Error::Host_ip();
//     skip_white_spaces(line, i);
//     skip_directive(line, i);
//     if (i == line.size() || !isspace(line[i]))
//         throw Error::Missing_directive_value();
//     skip_white_spaces(line, i);
//     if (i == line.size() || !isdigit(line[i]))
//         throw Error::Non_Nemeric_value();
//     for (int octet = 0; octet < 4; octet++)
//     {
//         if (i == line.size() || !isdigit(line[i]))
//             throw Error::Host_ip();

//         if (line[i] == '0' && i + 1 < line.size() && isdigit(line[i + 1]))
//             throw Error::Host_ip();

//         char octet_buf[4];
//         size_t j = 0;
//         while (i < line.size() && isdigit(line[i]))
//         {
//             if (j == 3)
//                 throw Error::Host_ip();
//             octet_buf[j++] = line[i++];
//         }
//         octet_buf[j] = '\0';
//         long val = strtol(octet_buf, NULL, 10);
//         if (val < 0 || val > 255)
//             throw Error::Host_ip();
//         if (octet < 3)
//         {
//             if (i == line.size() || line[i] != '.')
//                 throw Error::Host_ip();
//             i++;
//             dot_count++;
//         }
//     }
//     skip_white_spaces(line, i);
//     if (i == line.size() || line[i] != ';')
//         throw Error::SyntaxError();
//     std::string ip(line.begin(), line.begin() + i);
//     size_t start = 0;
//     skip_white_spaces(line, start);
//     while (start < line.size() && !isspace(line[start]))
//         start++;
//     skip_white_spaces(line, start);
//     end = start;
//     while (end < line.size() && !isspace(line[end]) && line[end] != ';')
//         end++;
//     Conf_File::Servers[server_index].host = line.substr(start, end - start);
// }

// void parse_index(std::string& line, size_t server_index)
// {
//     size_t i = 0;
//     size_t j = 0;
//     size_t end = (line.size() - 1);
//     while (end > 0 && isspace(line[end]))
//             end--;
//     if (line[end] != ';')
//         throw Error::Host_ip();
//     skip_white_spaces(line, i);
//     skip_directive(line, i);
//     if (i == line.size() || !isspace(line[i]))
//         throw Error::Index();
//     skip_white_spaces(line, i);
//     if (i == line.size())
//         throw Error::Index();
//     size_t start = i;
//     while (i < line.size() && !isspace(line[i]))
//     {
//         i++;
//     }
//     end = i;
//     if (start == end)
//         throw Error::Index();
//     size_t tmp = Conf_File::Servers[server_index].index_count++;
//     Conf_File::Servers[server_index].index_files[tmp] = line.substr(start, end - start);
// }

// void parse_server_name(std::string& line, size_t server_index)
// {
//     size_t i = 0;
//     size_t j = 0;
//     size_t end = (line.size() - 1);
//     while (end > 0 && isspace(line[end]))
//             end--;
//     if (line[end] != ';')
//         throw Error::Server_name();
//     skip_white_spaces(line, i);
//     skip_directive(line, i);
//     if (i == line.size() || !isspace(line[i]))
//         throw Error::Server_name();
//     skip_white_spaces(line, i);
//     size_t start = i;
//     while (i < line.size() && !isspace(line[i]))
//     {
        
//     }
// }

// void parse_max_uploads(std::string& line, size_t server_index)
// {
//     char buffer[10];
//     size_t i = 0;
//     size_t j = 0;

//     size_t end = (line.size() - 1);
//     while (end > 0 && isspace(line[end]))
//             end--;
//     if (line[end] != ';')
//         throw Error::MaxUploads();
//     skip_white_spaces(line, i);
//     skip_directive(line, i);
//     if (i == line.size() || !isspace(line[i]))
//         throw Error::Missing_directive_value();
//     skip_white_spaces(line, i);
//     if (!isdigit(line[i]))
//         throw Error::Non_Nemeric_value();
//     while (isdigit(line[i]))
//     {
//         buffer[j] = line[i];
//         j++;
//         i++;
//         if(j == 9)
//             throw Error::MaxUploads();
//     }
//     buffer[j] = '\0';
//     if (line[i] == 'm' || line[i] == 'M')
//         Conf_File::Servers[server_index].body_size_is_MB = true;
//     else if (line[i] == 'G' || line[i] == 'g')
//         Conf_File::Servers[server_index].body_size_is_GB = true;
//     else if (line[i] == 'k' || line[i] == 'K')
//         Conf_File::Servers[server_index].body_size_is_KB = true;
//     else if (i == line.size() || line[i] == ' ' || line[i] == '\t')
//         Conf_File::Servers[server_index].body_size_is_BT = true;
//     else
//         throw Error::Non_Nemeric_value();
//     Conf_File::Servers[server_index].max_body_size = strtol(buffer, NULL, 10);
// }

// void parse_listen_port(std::string& line, size_t server_index)
// {
//     char buffer[10];
//     size_t i = 0;
//     size_t j = 0;
//     size_t end = (line.size() - 1);
//     while (end > 0 && isspace(line[end]))
//             end--;
//     if (line[end] != ';')
//         throw Error::Listen();
//     skip_white_spaces(line, i);
//     skip_directive(line, i);
//     if (i == line.size() || !isspace(line[i]))
//         throw Error::Missing_directive_value();
//     skip_white_spaces(line, i);
//     if (!isdigit(line[i]))
//         throw Error::Non_Nemeric_value();
//     while (isdigit(line[i]))
//     {
//         buffer[j] = line[i];
//         j++;
//         i++;
//         if(j == 9)
//             throw Error::MaxUploads();
//     }
//     buffer[j] = '\0';
//     Conf_File::Servers[server_index].max_body_size = strtol(buffer, NULL, 10);
// }


// void parse_file()
// {
//     size_t i = 0;
//     while (i < Conf_File::rawLines.size())
//     {
//         size_t pos = Conf_File::rawLines[i].find("server");
//         if (pos != std::string::npos)
//         {
            
//         }
//     }
// }