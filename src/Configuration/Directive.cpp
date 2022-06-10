

#include "Directive.hpp"

namespace parser
{
    SimpleDirective::SimpleDirective(
        const std::string& key, const std::vector<std::string>& params)
        : _key(key), _args(params)
    {
        ;
    }

    SimpleDirective::SimpleDirective()
    {
    }

    SimpleDirective::~SimpleDirective()
    {
    }

    std::string const& SimpleDirective::getKey() const
    {
        return _key;
    }
    std::vector<std::string> const& SimpleDirective::getArgs() const
    {
        return _args;
    }

    // const SimpleDirective &SimpleDirective::operator=(SimpleDirective const &rhs) const
    // {

    // }

    const SimpleDirective& SimpleDirective::operator=(SimpleDirective const& rhs)
    {
        if (this != &rhs)
        {
            _key = rhs._key;
            _args = rhs._args;
        }
        return *this;
    }

    void SimpleDirective::check() const
    {
        /*
        ** Normally we should know which block are we in, to check using the block-specific rules.
        **  However, this simple logic should be fine, as we only need to verify the args count
        **  for all directives, and the args validity for few directives ("methods" and "autoindex", for now).
        */

        if (_args.size() < directiveRulesMap.at(_key).min_args)
            throw std::runtime_error("Directive " + _key + " has too few arguments");
        if (_args.size() > directiveRulesMap.at(_key).max_args)
            throw std::runtime_error("Directive " + _key + " has too many arguments");

        if (_key == "methods")
        {
            std::vector<std::string>::const_iterator it = _args.begin();
            for (; it != _args.end(); ++it)
            {
                if (*it != "GET" && *it != "POST" && *it != "HEAD"
                    && *it != "PUT" && *it != "DELETE" && *it != "OPTIONS"
                    && *it != "TRACE" && *it != "CONNECT")
                    throw std::runtime_error("Invalid method " + *it);

                if (ImplementedMethods.find(*it) == ImplementedMethods.end())
                    throw std::runtime_error("Method " + *it + " is not implemented");
            }
        }
        else if (_key == "autoindex")
        {
            std::vector<std::string>::const_iterator it = _args.begin();
            for (; it != _args.end(); ++it)
            {
                if (*it != "on" && *it != "off")
                    throw std::runtime_error("Invalid autoindex " + *it);
            }

        }
    }

    void SimpleDirective::print() const
    {
        std::cout << _key << "\t:";
        for (auto arg : _args)
        {
            std::cout << " " << arg;
        }
        std::cout << std::endl;
    }

    ///////////////////

    BlockDirective::BlockDirective()
    {
    }

    BlockDirective::BlockDirective(const std::string& key, const std::vector<std::string>& _params)
    {
    }

    BlockDirective::~BlockDirective()
    {
    }

    std::string const& BlockDirective::getKey() const
    {
        return _key;
    }
    std::vector<std::string> const& BlockDirective::getArgs() const
    {
        return _args;
    }
    // std::map<std::string, SimpleDirective> const &  BlockDirective::getDirectives() const
    // {
    //     return _directives;
    // }
    std::vector<SimpleDirective> const& BlockDirective::getDirectives() const
    {
        return _directives_vec;
    }

    void BlockDirective::check() const
    {
    }

    void BlockDirective::print() const
    {
        std::cout << _key << ":";
        for (auto arg : _args)
        {
            std::cout << " " << arg;
        }
        std::cout << std::endl;
        for (auto smp : _directives_vec)
            smp.print();
    }

} // namespace parser
