#ifndef CLIENTREQUEST_HPP
#define CLIENTREQUEST_HPP

class ClientRequest
{
	public:
    	ClientRequest();
    	ClientRequest(const ClientRequest &other);
    	ClientRequest& operator=(const ClientRequest& other);
    	~ClientRequest();
};

#endif
