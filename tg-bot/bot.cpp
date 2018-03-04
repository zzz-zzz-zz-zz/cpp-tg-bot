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

    if (cb_All != nullptr) 
    {
        std::cout << "Bot started polling... Press [Ctrl+C] to exit.\n";
    
        while (true)
        {
            list<Update> upds = api->getUpdates(timeout_s);

            for (Update &u : upds)
                cb_All(this, &u);
        }
    } 
    else 
    {
        throw std::invalid_argument("No callback for updates!");
    }
}


bool Bot::has_updates()
{
    return api->getUpdates(false).size() > 0;
}

void Bot::on_update(std::function<void(Bot*, Update*)> callback)
{
    cb_All = callback;
}

void Bot::on_start(std::function<void(Bot*)> callback)
{
    cb_OnStart = callback;
}
