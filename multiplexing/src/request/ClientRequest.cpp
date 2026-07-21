#include "../../include/request/ClientRequest.hpp"

ClientRequest::ClientRequest() : state(HEADERS), status_code(200){}

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
        status_code     =   other.status_code;
    }
    return *this;
}

ClientRequest::~ClientRequest(){}




const std::string& ClientRequest::getMethod() const {return method;}
const std::string& ClientRequest::getRequestPath() const {return request_path;}
const std::string& ClientRequest::getCgiExtension() const {return cgi_extension;}
const std::string& ClientRequest::getVersion() const {return version;}
const std::string& ClientRequest::getBody() const {return body;}
const std::string& ClientRequest::getCgi() const {return cgi;}
const short ClientRequest::getStatusCode() const {return status_code;}
const std::map<std::string, std::string>& ClientRequest::getHeaders() const  {return headers;}


void ClientRequest::setStatusCode(short StatusCode)
{
    this->status_code = StatusCode;
}



void ClientRequest::RequestLineParser(std::string line)
{
    if (line.empty() || !ValidLine(line))
        return;
    if (line.find(' ') == std::string::npos)
    {
        this->status_code = 400;
        this->state = ERROR_STATE;
        return;
    }
}

void ClientRequest::HeadersParser(std::string headers)
{
    std::string RequestLine;

    RequestLine = headers.substr(0, headers.find("\r\n"));
    RequestLineParser(RequestLine);
}

void ClientRequest::parse(Client& client)
{
    if (this->state == ERROR_STATE)
        return;
    if (client.request.length() > 8192)
    {
        this->status_code = 431;
        this->state = ERROR_STATE;
        return;
    }
    if (client.parsed_request.state == HEADERS)
    {
        size_t begin = removeWhitespace(client);
        if (begin > 0)
            client.request.erase(0, begin);
        if (client.request.empty())
            return;
        
        size_t check;
        check = client.request.find("\r\n\r\n");
        if (check != std::string::npos)
        {
            std::string headers;
            std::string extra;
            
            headers = client.request.substr(0, check + 2);
            HeadersParser(headers);
            if (this->state = ERROR_STATE)
                return;
            state = BODY;
            extra = client.request.substr(check + 4);
            client.request.clear();

        }
    }

}