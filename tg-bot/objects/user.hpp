#ifndef __TGBOT_OBJECTS_USER
#define __TGBOT_OBJECTS_USER

#include "_all.hpp"


class User
{
public:
    User(string jstr);
    User(json j);
    User(const User &that) : id(that.id), is_bot(that.is_bot),
            first_name(that.first_name), last_name(that.last_name),
            username(that.username), language_code(that.language_code) 
    { }
    User(User &&that) noexcept : id(that.id), is_bot(that.is_bot),
            first_name(std::move(that.first_name)), last_name(std::move(that.last_name)),
            username(std::move(that.username)), language_code(std::move(that.language_code)) 
    { }
    
    User& operator=(User that)
    {
        std::swap(id, that.id);
        std::swap(is_bot, that.is_bot);
        std::swap(first_name, that.first_name);
        last_name.swap(that.last_name);
        username.swap(that.username);
        language_code.swap(that.language_code);
    }

    int get_id() { return id; }
    bool get_is_bot() { return is_bot; }
    string get_first_name() { return first_name; }
    string get_last_name() { return last_name.value_or(string("")); }
    string get_username() { return username.value_or(string("")); }
    string get_language_code() { return language_code.value_or(string("")); }

    string to_string();
    string to_string_pretty();
private:
    int id;
    bool is_bot;
    string first_name;
    optional<string> last_name = nullopt;
    optional<string> username = nullopt;
    optional<string> language_code = nullopt;
};


#endif // __TGBOT_OBJECTS_USER