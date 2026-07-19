#include "../../include/request/ClientRequest.hpp"

ClientRequest::ClientRequest() : state(START_LINE){}

ClientRequest::ClientRequest(const ClientRequest& other)
{
    *this = other;
}

ClientRequest& ClientRequest::operator=(const ClientRequest& other)
{
    if (this != &other)
    {
        state           =   other.state;
        method          =   other.method;
        request_path    =   other.request_path;
        cgi_extension   =   other.cgi_extension;
        version         =   other.version;
        headers         =   other.headers;
        cgi             =   other.cgi;
        body            =   other.body;
    }
    return *this;
}

ClientRequest::~ClientRequest(){}

const std::string& ClientRequest::getMethod() const
{
    return method;
}

const std::string& ClientRequest::getRequestPath() const
{
    return request_path;
}

const std::string& ClientRequest::getCgiExtension() const
{
    return cgi_extension;
}

const std::string& ClientRequest::getVersion() const
{
    return version;
}

const std::string& ClientRequest::getBody() const
{
    return body;
}

const std::string& ClientRequest::getCgi() const
{
    return cgi;
}

const std::map<std::string, std::string>& ClientRequest::getHeaders() const
{
    return headers;
}

ClientRequest::ParseState ClientRequest::getState() const
{
    return state;
}
