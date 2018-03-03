#ifndef __TGBOT_OBJECTS_MESSAGE
#define __TGBOT_OBJECTS_MESSAGE

#include "_all.hpp"


class Message
{
public:
    Message(string jstr);
    Message(json j);
    Message(const Message &that);
    Message(Message &&that) noexcept;

    int get_message_id() { return message_id; }
    int get_date() { return date; }
    Chat get_chat();
    User get_from();

    string get_text() { return text.value_or(""); }
    bool has_text() { return text.has_value(); }

    vector<PhotoSize> get_photo() 
    { 
        if (!photo) 
            throw TelegramNullObjectException("No photo array!");  
        return *photo; 
    }
    bool has_photo() { return photo != nullptr; }

    //
private:
    int message_id;
    shared_ptr<User> from = nullptr;
    int date;
    shared_ptr<Chat> chat = nullptr;
    // User *forward_from;
    // Chat *forward_from_chat;
    // optional<int> forward_from_message_id = nullopt;
    // optional<string> forward_signature = nullopt;
    // optional<int> forward_date = nullopt;
    // Message *reply_to_message;
    // optional<int> edit_date = nullopt;
    // optional<string> media_group_id = nullopt;
    // optional<string> author_signature = nullopt;
    optional<string> text = nullopt;
    // list<MessageEntity> *entities;
    // list<MessageEntity> *caption_entities;
    shared_ptr<Audio> audio = nullptr;
    // Document *document;
    // Game *game;
    shared_ptr<vector<PhotoSize>> photo = nullptr; //!! >> | > >
    // Sticker *sticker;
    // Video *video;
    // Voice *voice;
    // VideoNote *videonote;
    // string *caption;
    // Contact *contact;
    // Location *location;
    // Venue *venue;
    // list<User> *new_chat_members;
    // User *left_chat_member;
    // optional<string> new_chat_title;
    // list<PhotoSize> *new_chat_photo;
    // bool delete_chat_photo = false;
    // bool group_chat_created = false;
    // bool supergroup_chat_created = false;
    // bool channel_chat_created = false;
    // optional<int> migrate_to_chat_id = nullopt;
    // optional<int> migrate_from_chat_id = nullopt;
    // Message *pinned_message;
    // Invoice *invoice;
    // SuccessfulPayment *successful_payment;
    // string *connected_website;
};


#endif // __TGBOT_OBJECTS_MESSAGE