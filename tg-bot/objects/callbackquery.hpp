#ifndef __TGBOT_OBJECTS_CALLBACK_QUERY
#define __TGBOT_OBJECTS_CALLBACK_QUERY

#include "_all.hpp"


class CallbackQuery
{
public:
    CallbackQuery(string);
    CallbackQuery(json);
};


#endif // __TGBOT_OBJECTS_CALLBACK_QUERY