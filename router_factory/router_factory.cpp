// using the Prototype pattern w/ Factory
// @to-do all:
// build choices from script (input string)
// use Meyers' singleton for: protocol, host, lang, topic
// keep new for optionals

#include <iostream>
#include <string_view>
//#include <vector>

std::string_view protocol_delim = "://";

class details {
public:
    details(std::string comp_str): data(comp_str) {}

    virtual void get_info() const = 0;
    virtual ~details() {}

protected:
    std::string data;
};

class protocol : public details {
public:
    protocol(std::string comp_str) :details(comp_str) {};

    void get_info() const override {
        std::cout << "Used protocol: " << data << std::endl;
    }
};

class host : public details {
public:
    host(std::string comp_str) :details(comp_str) {};

    void get_info() const override {
        std::cout << "Used host: " << data << std::endl;
    }
};

class lang : public details {
public:
    lang(std::string comp_str) :details(comp_str) {};

    void get_info() const override {
        std::cout << "Used lang: " << data << std::endl;
    }
};

class topic : public details {
public:
    topic(std::string comp_str) :details(comp_str) {};

    void get_info() const override {
        std::cout << "Used topic: " << data << std::endl;
    }
};

class optional : public details {
public:
    optional(std::string comp_str) :details(comp_str) {};

    void get_info() const override {
        std::cout << "Used option: " << data << std::endl;
    }
};

class component_factory {
public:
    enum class component_type {
        protocol_,
        host_,
        lang_,
        topic_,
        optional_
    };

    static std::unique_ptr<details> create_details(component_type type, std::string comp_str);
private:
    //std::unordered_map<component_type, unique_ptr<details>, hash<int>> m_components;
};

std::unique_ptr<details> component_factory::create_details(component_type type, std::string comp_str) {
    switch (type) {
        case component_factory::component_type::protocol_: return std::make_unique<protocol>(comp_str);
        case component_factory::component_type::host_:     return std::make_unique<host>(comp_str);
        case component_factory::component_type::lang_:     return std::make_unique<lang>(comp_str);
        case component_factory::component_type::topic_:    return std::make_unique<topic>(comp_str);
        case component_factory::component_type::optional_: return std::make_unique<optional>(comp_str);
    }

    throw "invalid component type";
}

void url_info(component_factory::component_type type, std::string comp_str)
{
    std::unique_ptr<details> url_details = component_factory::create_details(type, comp_str);
    url_details->get_info();
}

int main() {
    std::string url = "https://www.dw.com/de/themen/s-9077";
    std::cout << "url: " << url << std::endl;

    // @to-do implement also the read of optional components of the URL
    //std::vector<std::unique_ptr<details>> optional_topic_reg;

    // @to-do implement proper error handling
    std::size_t protocol_found = url.find(protocol_delim);

    if (protocol_found != std::string::npos)
    {
        url_info(component_factory::component_type::protocol_, url.substr(0, protocol_found));
    }
    else
    {
        std::cout << "host not found";
        return -1;
    }

    // @to-do create object for automatic searching between '/'-delimiters instead of manual
    std::size_t idx = protocol_found + protocol_delim.length();
    std::size_t delim_found = url.find('/', idx);
    std::string host_name;

    if (delim_found != std::string::npos)
    {
        host_name = url.substr(idx, delim_found - idx);
        url_info(component_factory::component_type::host_, host_name);
    }

    idx = delim_found + 1;
    delim_found = url.find('/', idx);
    std::string lang_name;

    if (delim_found != std::string::npos)
    {
        lang_name = url.substr(idx, delim_found - idx);
        url_info(component_factory::component_type::lang_, lang_name);
    }

    idx = delim_found + 1;
    delim_found = url.find('/', idx);
    std::string topic_name;

    if (delim_found != std::string::npos)
    {
        topic_name = url.substr(idx, delim_found - idx);
        url_info(component_factory::component_type::topic_, topic_name);
    }

    //optional_topic_reg.push_back(
    //        Factory::create_details(choice));
    //}

//    for (auto& opt_object:optional_topic_reg)
//    {
//        opt_object->get_info();
//    }

    return 0;
}