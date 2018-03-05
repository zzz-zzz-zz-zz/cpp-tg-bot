#include "chat.hpp"

ChatPhoto Chat::get_photo() {
    if (photo == nullptr)
        throw std::invalid_argument("Chat::photo is empty!");
    return *photo;
}

Message Chat::get_pinned_message() {
    if (pinned_message == nullptr)
        throw std::invalid_argument("Chat::pinned_message is empty!");
    return *pinned_message;
}

Chat::Chat(string jstr) : Chat::Chat(json::parse(jstr))
{
}

Chat::Chat(json &&j)
{
    id = j["id"].get<int>();
    
    const char *typecstr = j["type"].get<string>().c_str();
    if (!strcmp(typecstr, "private")) {
        type = PRIVATE;
    } else if (!strcmp(typecstr, "group")) {
        type = GROUP;
    } else if (!strcmp(typecstr, "supergroup")) {
        type = SUPERGROUP;
    } else if (!strcmp(typecstr, "channel")) {
        type = CHANNEL;
    } else {
        throw std::invalid_argument(string("Invalid type of chat - ") + typecstr);
    }

    OMIT(title = j.at("title").get<string>())
    OMIT(username = j.at("username").get<string>())
    OMIT(first_name = j.at("first_name").get<string>())
    OMIT(last_name = j.at("last_name").get<string>())
    OMIT(all_members_are_administrators = 
            j.at("all_members_are_administrators").get<bool>())
    OMIT(photo = std::make_unique<ChatPhoto>(j.at("photo").get<json>()))
    OMIT(description = j.at("description").get<string>())
    OMIT(invite_link = j.at("invite_link").get<string>())
    OMIT(pinned_message = std::make_unique<Message>(j.at("pinned_message").get<json>()))
    OMIT(sticker_set_name = j.at("sticker_set_name").get<string>())
    OMIT(can_set_sticker_set = j.at("can_set_sticker_set").get<bool>())
}

Chat::Chat(const Chat &that)
{
    id = that.id;
    type = that.type;
    title = that.title;
    username = that.username;
    first_name = that.first_name;
    last_name = that.last_name;
    all_members_are_administrators = that.all_members_are_administrators;
    photo = that.photo;
    description = that.description;
    invite_link = that.invite_link;
    pinned_message = that.pinned_message;
    sticker_set_name = that.sticker_set_name;
    can_set_sticker_set = that.can_set_sticker_set;
}