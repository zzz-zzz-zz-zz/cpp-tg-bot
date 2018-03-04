#include "bot.hpp"

#include <unistd.h>


Bot::Bot(string token)
{
    api = new Api(token);
}

Bot::~Bot()
{
    delete api;
}

void Bot::start_polling()
{
    start_polling((i32_t)10);
}

void Bot::start_polling(i32_t timeout_s)
{
    if (cb_OnStart != nullptr)
        cb_OnStart(this);

    if (!update_flags) 
        throw std::invalid_argument("0 callbacks specified!");
    
    std::cout << "Bot started polling... Press [Ctrl+C] to exit.\n";

    if (update_flags == Api::UpdateFilters::ALL && cb_All != nullptr) {
        while (true)
        {
            list<Update> upds = api->getUpdates(timeout_s);

            for (Update &u : upds)
                cb_All(this, &u);
        }
    } else {
        throw std::invalid_argument("No case for not ALL filters!");
    }
}


bool Bot::has_updates()
{
    // return api->getUpdates(false).size() > 0;
    std::cout << "WARNING: Bot.has_updates() always false!!!\n";
    return false;
}

void Bot::on_update(i32_t update_filters, std::function<void(Bot*, Update*)> callback)
{
    if (update_filters == Bot::UpdateFilters::ALL) {
        on_update(callback);
        return;
    }
}

void Bot::on_update(std::function<void(Bot*, Update*)> callback)
{
    update_flags = Api::UpdateFilters::ALL;
    cb_All = callback;
}

void Bot::on_start(std::function<void(Bot*)> callback)
{
    cb_OnStart = callback;
}
