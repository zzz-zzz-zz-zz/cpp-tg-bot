#ifndef __TGBOT_OBJECTS_USER
#define __TGBOT_OBJECTS_USER

#include "_all.hpp"


class User
{
public:
    User(string jstr);
    User(json j);

    int get_id() { return id; }
    bool get_is_bot() { return is_bot; }
    string get_first_name() { return first_name; }
    string get_last_name() { return last_name.value_or(string("")); }
    string get_username() { return username.value_or(string("")); }
    string get_language_code() { return language_code.value_or(string("")); }

    // TODO: getters ?

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