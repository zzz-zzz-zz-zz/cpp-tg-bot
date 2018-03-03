#ifndef __TGBOT_API
#define __TGBOT_API

#include "objects/_all.hpp"


class Api
{
public:
    enum UpdateFilters 
    {
        NONE                  =   0b000000000,
        MESSAGE               =   0b000000001,
        EDITED_MESSAGE        =   0b000000010,
        CHANNEL_POST          =   0b000000100,
        EDITED_CHANNEL_POST   =   0b000001000,
        INLINE_QUERY          =   0b000010000,
        CHOSEN_INLINE_RESULT  =   0b000100000,
        CALLBACK_QUERY        =   0b001000000,
        SHIPPING_QUERY        =   0b010000000,
        PRE_CHECKOUT_QUERY    =   0b100000000,
        ALL                   =   0b111111111,
    };

    enum class FileFrom 
    {
        URL,     // External url
        FILE_ID, // File id in Telegram
        DISK,    // Filename on disk(full or relative)
    };

    class ParseMode 
    {
        public:
            static const char *HTML;
            static sonst char *MARKDOWN;
        private:
            ParseMode() = delete;
            ParseMode(const ParseMode &) = delete;
            ParseMode& operator=(const ParseMode &) = delete;
    }

    Api(const Api&);
    Api(string);


    list<Update> getUpdates();
    list<Update> getUpdates(bool validate);
    list<Update> getUpdates(i32_t timeout_s);
    list<Update> getUpdates(i32_t timeout_s, bool validate);

    User getMe();
    Message sendMessage(i32_t chat_id, string text);
    Message sendMessage(i32_t chat_id, string text, string parse_mode);
    Message sendMessage(string chat_id, string text);
    Message sendMessage(string chat_id, string text, const char *parse_mode);
    Message sendMessage(string chat_id, string text, const char *parse_mode, 
                        bool disable_page_preview);
    Message sendMessage(string chat_id, string text, const char *parse_mode, 
                        bool disable_page_preview, bool disable_notification);
    Message sendMessage(string chat_id, string text, const char *parse_mode, 
                        bool disable_page_preview, bool disable_notification,
                        i32_t reply_to_message_id);
    Message sendMessage(string chat_id, string text, map args);

    Message forwardMessage(i32_t chat_id, i32_t from_chat_id, i32_t message_id);
    Message forwardMessage(i32_t chat_id, i32_t from_chat_id, i32_t message_id, 
                           bool disable_notification);
    Message forwardMessage(i32_t chat_id, string from_chat_id, i32_t message_id);
    Message forwardMessage(i32_t chat_id, string from_chat_id, i32_t message_id, 
                           bool disable_notification);
    Message forwardMessage(string chat_id, i32_t from_chat_id, i32_t message_id);
    Message forwardMessage(string chat_id, i32_t from_chat_id, i32_t message_id, 
                           bool disable_notification);
    Message forwardMessage(string chat_id, string from_chat_id, i32_t message_id);
    Message forwardMessage(string chat_id, string from_chat_id, i32_t message_id, 
                           bool disable_notification);

    //TODO: change return to Message and realize PhotoSize[]
    //TODO: 2: overload for additional paramaters
    string sendPhoto(i32_t chat_id, FileFrom from, string filename);
    string sendPhoto(string chat_id, FileFrom from, string filename);

    //TODO: change return to Message and realize Audio
    //TODO: 2: overload for additional paramaters
    string sendAudio(i32_t chat_id, FileFrom from, string filename);
    string sendAudio(string chat_id, FileFrom from, string filename);

    //TODO: change return to Message and realize Document
    //TODO: 2: overload for additional paramaters
    string sendDocument(i32_t chat_id, FileFrom from, string filename);
    string sendDocument(string chat_id, FileFrom from, string filename);

    //TODO: change return to Message and realize Document
    //TODO: 2: overload for additional paramaters
    string sendVideo(i32_t chat_id, FileFrom from, string filename);
    string sendVideo(string chat_id, FileFrom from, string filename);

    //TODO: change return to Message and realize Voice
    //TODO: 2: overload for additional paramaters
    string sendVoice(i32_t chat_id, FileFrom from, string filename);
    string sendVoice(string chat_id, FileFrom from, string filename);

    //TODO: sendVideoNote. Later...           Difficulty: ##___
    //TODO: sendMediaGroup. Later...          Difficulty: ####_
    //TODO: sendLocation. Later...            Difficulty: ###__
    //TODO: editMessageLiveLocation. Later... Difficulty: ###__
    //TODO: stopMessageLiveLocation. Later... Difficulty: ###__
    //TODO: sendVenue. Later...               Difficulty: ##___

    //TODO: change return to Message and realize Contact
    string sendContact(i32_t chat_id, string phone_number, string first_name);
    string sendContact(i32_t chat_id, string phone_number, 
                       string first_name, string last_name);
    string sendContact(i32_t chat_id, string phone_number, 
                       string first_name, bool disable_notification,
                       i32_t reply_to_message_id);
    string sendContact(i32_t chat_id, string phone_number, 
                       string first_name, string last_name,
                       bool disable_notification);
    string sendContact(i32_t chat_id, string phone_number, 
                       string first_name, string last_name, bool disable_notification,
                       i32_t reply_to_message_id);
    string sendContact(i32_t chat_id, string phone_number, 
                       string first_name, string last_name,
                       i32_t reply_to_message_id);
    string sendContact(string chat_id, string phone_number, string first_name);
    string sendContact(string chat_id, string phone_number, 
                       string first_name, string last_name);
    string sendContact(string chat_id, string phone_number, 
                       string first_name, bool disable_notification,
                       i32_t reply_to_message_id);
    string sendContact(string chat_id, string phone_number, 
                       string first_name, string last_name,
                       bool disable_notification);
    string sendContact(string chat_id, string phone_number, 
                       string first_name, string last_name, bool disable_notification,
                       i32_t reply_to_message_id);
    string sendContact(string chat_id, string phone_number, 
                       string first_name, string last_name,
                       i32_t reply_to_message_id);

    bool sendChatAction(i32_t chat_id, string action);
    bool sendChatAction(string chat_id, string action);

    // TODO: change return to UserProfilePhotos and realize UserProfilePhotos 
    string getUserProfilePhotos(i32_t user_id);
    string getUserProfilePhotos(i32_t user_id, i32_t offset);
    string getUserProfilePhotos(i32_t user_id, i32_t offset, i32_t limit);

    // TODO: change return to File and realize File
    string getFile(string file_id);

    // TODO: add easy ban for N-days/hours/minutes
    bool kickChatMember(i32_t chat_id, i32_t user_id);
    bool kickChatMember(i32_t chat_id, i32_t user_id, i32_t until_date);
    bool kickChatMember(string chat_id, i32_t user_id);
    bool kickChatMember(string chat_id, i32_t user_id, i32_t until_date);

    bool unbanChatMember(i32_t chat_id, i32_t user_id);
    bool unbanChatMember(string chat_id, i32_t user_id);

    bool restrictChatMember(i32_t chat_id, i32_t user_id);
    bool restrictChatMember(i32_t chat_id, i32_t user_id, i32_t until_date);
    bool restrictChatMember(i32_t chat_id, i32_t user_id, 
            bool can_send_messages, bool can_send_media_messages, 
            bool can_send_other_messages, bool can_add_web_page_previews);
    bool restrictChatMember(i32_t chat_id, i32_t user_id, i32_t until_date, 
            bool can_send_messages, bool can_send_media_messages, 
            bool can_send_other_messages, bool can_add_web_page_previews);
    bool restrictChatMember(string chat_id, i32_t user_id);
    bool restrictChatMember(string chat_id, i32_t user_id, i32_t until_date);
    bool restrictChatMember(string chat_id, i32_t user_id, 
            bool can_send_messages, bool can_send_media_messages, 
            bool can_send_other_messages, bool can_add_web_page_previews);
    bool restrictChatMember(string chat_id, i32_t user_id, i32_t until_date, 
            bool can_send_messages, bool can_send_media_messages, 
            bool can_send_other_messages, bool can_add_web_page_previews);

    
    // TODO: next methods...
private:
    string execute(const char *method, map args);
    string execute(const char *method, json args);
    string executeSend(const char *method, map args, const char *fieldname, string filename);

    inline string escape_string(string s);

    string token;
    i32_t last_update_id = -1;
};

size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, string *s);


#endif // __TGBOT_API

