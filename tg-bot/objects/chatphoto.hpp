#ifndef __TGBOT_OBJECTS_CHAT_PHOTO
#define __TGBOT_OBJECTS_CHAT_PHOTO

#include "_all.hpp"


class ChatPhoto
{
public:
    ChatPhoto(string);
    ChatPhoto(json&&);
    ChatPhoto(const ChatPhoto &that);
    ChatPhoto& operator=(const ChatPhoto &that);
};


#endif // __TGBOT_OBJECTS_CHAT_PHOTO