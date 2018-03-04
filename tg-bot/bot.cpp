#include "bot.hpp"

#include <unistd.h>


void Bot::add_handler(MessageHandler h)
{
    if (registered_filters & h.filters)
        throw TelegramException("Attempt to rewrite already defined callback for filter!");

    registered_filters |= h.filters;
    
    if (h.filters & UpdateFilters::TEXT)
        handler_Text = std::make_shared<MessageHandler>(h);
    if (h.filters & UpdateFilters::AUDIO)
        handler_Audio = std::make_shared<MessageHandler>(h);
    if (h.filters & UpdateFilters::VIDEO)
        handler_Video = std::make_shared<MessageHandler>(h);
    if (h.filters & UpdateFilters::DOCUMENT)
        handler_Document = std::make_shared<MessageHandler>(h);
    if (h.filters & UpdateFilters::VOICE)
        handler_Voice = std::make_shared<MessageHandler>(h);
    if (h.filters & UpdateFilters::PHOTO)
        handler_Photo = std::make_shared<MessageHandler>(h);
    if (h.filters & UpdateFilters::STICKER)
        handler_Sticker = std::make_shared<MessageHandler>(h);
}

void Bot::add_handler(CommandHandler h)
{
    handlers_Command.push_back(h);
    registered_filters |= UpdateFilters::COMMAND;
}


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

    if (registered_filters != UpdateFilters::NONE) 
    {
        std::cout << "Bot started polling... Press [Ctrl+C] to exit.\n";
    
        while (true)
        {
            list<Update> upds = api->getUpdates(timeout_s);

            for (Update &u : upds)
            {
                if (!u.has_message()) // TODO: NOT ONLY MESSAGES
                    continue;
                Message m = u.get_message();

                i32_t update_checks = u.get_message().get_checks();
                i32_t able_checks = update_checks & registered_filters;

                std::cout << "update_checks = " << update_checks << std::endl;
                std::cout << "able_checks = " << able_checks << std::endl;
                std::cout << "UpdateFilters::COMMAND = " << UpdateFilters::COMMAND << std::endl;
                std::cout << "able_checks & UpdateFilters::COMMAND = " << (able_checks & UpdateFilters::COMMAND) << std::endl;
                
                if (able_checks & UpdateFilters::COMMAND)
                {
                    vector<string> words = {"/start"};//string_explode(m.get_text(), ' ');
                    string cmd = words[0];


                    for (CommandHandler &h : handlers_Command)
                        if (cmd == h.get_command())
                        {
                            h.callback(this, &u);
                            break;                            
                        }
                        else
                        {
                            std::cout << "No CmdHandler for " << cmd << std::endl;                            
                        }
                }
                else
                {
                    if (able_checks & UpdateFilters::TEXT)
                        handler_Text->callback(this, &u);
                    else if (able_checks & UpdateFilters::AUDIO)
                        handler_Audio->callback(this, &u);
                    else if (able_checks & UpdateFilters::VIDEO)
                        handler_Video->callback(this, &u);
                    else if (able_checks & UpdateFilters::DOCUMENT)
                        handler_Document->callback(this, &u);
                    else if (able_checks & UpdateFilters::VOICE)
                        handler_Voice->callback(this, &u);
                    else if (able_checks & UpdateFilters::PHOTO)
                        handler_Photo->callback(this, &u);
                    else if (able_checks & UpdateFilters::STICKER)
                        handler_Sticker->callback(this, &u);
                }


            }
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
