#ifndef __TGBOT_OBJECTS_CHAT
#define __TGBOT_OBJECTS_CHAT

#include "_all.hpp"


class Chat
{
public:
    Chat(string);
    Chat(json&&);
    Chat(const Chat &that);

    enum Type {
        PRIVATE, GROUP, SUPERGROUP, CHANNEL
    };

    int get_id() { return id; }
    Type get_type() { return type; }
    bool get_all_members_are_administrators() { return all_members_are_administrators; }
    bool get_set_can_sticker_set() { return can_set_sticker_set; }
    string get_title() { return title.value_or(""); }
    string get_username() { return username.value_or(""); }
    string get_first_name() { return first_name.value_or(""); }
    string get_last_name() { return last_name.value_or(""); }
    ChatPhoto get_photo();
    string get_description() { return description.value_or(""); }
    string get_invite_lint() { return description.value_or(""); }
    Message get_pinned_message();
    string get_sticker_set_name() { return sticker_set_name.value_or(""); }
    bool get_can_set_sticker_set() { return can_set_sticker_set; }
    bool has_title() { return title.has_value(); }
    bool has_username() { return username.has_value(); }
    bool has_first_name() { return first_name.has_value(); }
    bool has_last_name() { return last_name.has_value(); }
    bool has_photo() { return photo != nullptr; }
    bool has_description() { return description.has_value(); }
    bool has_invite_link() { return invite_link.has_value(); }
    bool has_pinned_message() { return pinned_message != nullptr; }
    bool has_sticker_set_name() { return sticker_set_name.has_value(); }
private:
    int id;
    Type type;
    optional<string> title = nullopt;
    optional<string> username = nullopt;
    optional<string> first_name = nullopt;
    optional<string> last_name = nullopt;
    bool all_members_are_administrators = false;
    shared_ptr<ChatPhoto> photo = nullptr;
    optional<string> description = nullopt;
    optional<string> invite_link = nullopt;
    shared_ptr<Message> pinned_message = nullptr;
    optional<string> sticker_set_name = nullopt;
    bool can_set_sticker_set = false;
};


#endif //__TGBOT_OBJECTS_CHAT