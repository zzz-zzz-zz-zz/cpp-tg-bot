#ifndef __TGBOT_BOT
#define __TGBOT_BOT

#include "objects/_all.hpp"
#include "api.hpp"


class Bot
{
public:
    Bot(string);
    ~Bot();

    bool has_updates();

    void on_start(std::function<void(Bot*)> callback);
    void on_update(std::function<void(Bot*, Update*)> callback);
    void start_polling(i32_t timeout_s);
    void start_polling();

    Api *api;
private:
    std::function<void(Bot*, Update*)> cb_All = nullptr;
    std::function<void(Bot*)> cb_OnStart = nullptr;

};


#endif // __TGBOT_BOT