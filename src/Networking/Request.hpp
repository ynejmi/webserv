#pragma once

#include "webserv.hpp"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>

namespace ws
{
    class Request
    {
    public:
        Request(int client_fd, std::vector<VServer*> & vservers);
        ~Request();

        std::string const &getHeader() const;
        std::string const &getBody() const;
        std::string const &getMethod() const;
        std::string const &getPath() const;
        std::string const &getQuery() const;
        int const& getClientFd() const;

        std::vector<VServer*> & getVServers() const;

        void process();
        bool isComplete() const;

    private:
        int _client_fd;
        std::string _request;
        std::string _method;
        std::string _path;
        std::string _query;
        std::string _header;
        std::string _body;
        bool _isHeaderSet;
        bool _isChunked;
        bool _isDone;
        std::map<std::string, std::string> _headers;
        std::vector<VServer*> & _vservers;

        //
        void parseHeader();
        void parseBody();
    };

} // namespace ws
