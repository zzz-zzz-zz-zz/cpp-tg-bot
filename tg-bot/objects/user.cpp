#include "user.hpp"


string User::to_string()
{
    std::stringstream ss;

    ss << "\"user\": { " << "\"id\": " << id 
       << ", \"first_name\": " << "\"" << first_name << "\""
       << ", \"last_name\": " << "\"" << last_name.value_or("") << "\""
       << ", is_bot: " << std::boolalpha << is_bot
       << ", username: " << "\"" << username.value_or(string("")) << "\""
       << ", language_code: " << "\"" << language_code.value_or(string("")) << "\""
       << "}";
    return ss.str();
}

string User::to_string_pretty()
{
    std::stringstream ss;

    ss << "\"user\": {\n\t\"id\": " << id << ",\n";
    ss << "\t\"first_name\": \"" << first_name << "\",\n";
    ss << "\t\"last_name\": \"" << last_name.value_or(string("")) << "\",\n";  
    ss << "\t\"is_bot\": " << std::boolalpha << is_bot << ",\n";
    ss << "\t\"username\": \"" << username.value_or(string("")) << "\",\n";
    ss << "\t\"language_code\": \"" << language_code.value_or(string("")) << "\",\n";
    ss << "}\n";

    return ss.str();
}

User::User(string jstr) : User::User(json::parse(jstr)) { }

User::User(json j)
{
    OMIT(
        if (j.at("ok").get<bool>())
            j = j["result"];
        else
            throw std::invalid_argument("not ok"); // TODO: it not throws from constructor bcz in OMIT()!!!
    )

    id = j["id"].get<int>();
    is_bot = j["is_bot"].get<bool>();
    first_name = j["first_name"].get<string>();

    OMIT(last_name = j.at("last_name").get<string>())
    OMIT(username = j.at("username").get<string>())
    OMIT(language_code = j.at("language_code").get<string>())
}