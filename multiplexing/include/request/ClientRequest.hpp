#ifndef CLIENTREQUEST_HPP
#define CLIENTREQUEST_HPP

#include <map>
#include <string>

struct Client;

class ClientRequest
{
	public:
    	ClientRequest();
    	ClientRequest(const ClientRequest &other);
    	ClientRequest& operator=(const ClientRequest& other);
    	~ClientRequest();
	
		enum ParseState
		{
			START_LINE,
	    	HEADERS,
    		BODY,
			DONE,
    		ERROR_STATE
		};
		
		void parse(Client& client, size_t n);
	
    	const std::string& getMethod() const;
    	const std::string& getRequestPath() const;
    	const std::string& getCgiExtension() const;
    	const std::string& getVersion() const;
    	const std::string& getBody() const;
    	const std::string& getCgi() const;
    	const std::map<std::string, std::string>& getHeaders() const;
    	ParseState getState() const;
		ParseState state;
		
	private:
		std::string method;
		std::string request_path;
		std::string cgi_extension;
		std::string version;
		std::map<std::string, std::string> headers;
		std::string cgi;
		std::string body;
};

#endif
