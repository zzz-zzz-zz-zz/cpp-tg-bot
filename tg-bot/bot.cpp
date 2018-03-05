#include "bot.hpp"

#include <unistd.h>


void Bot::on_message(i32_t filterflags, std::function<void(Bot, Message)> callback)
{
    if (filterflags == UpdateFilters::ALL_OTHERS)
        filterflags = ~registered_filters;


    MessageHandler h(filterflags, callback);

    if (i32_t regf = registered_filters & h.filters; regf)
        std::cerr << "Warning: Reassigning callback(-s) for filters " 
                  << std::bitset<16>(regf).to_string() << std::endl;
        //throw TelegramHandlerException("Attempt to rewrite already defined callback for filter!");

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

void Bot::on_command(string command, std::function<void(Bot, Update)> callback)
{
    command.insert(0, 1, '/');

    if (handlers_Command.count(command))
        std::cerr << "Warning: Reassigning command \"" << command << "\"" << std::endl;

    handlers_Command[command] = CommandHandler(command, callback);
    registered_filters |= UpdateFilters::COMMAND;
}


Bot::Bot(string token)
{
    api = new Api(token);
}

Bot::Bot(const Bot &that)
{
    api = new Api(*(that.api));
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
        cb_OnStart(*this);

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

                if (able_checks & UpdateFilters::COMMAND)
                {
                    // string_explode!                    
                    string buff = "";
                    vector<string> words;                    
                    
                    for (const auto &n : m.get_text())
                    {
                        if (n != ' ')
                        {
                            buff += n;             
                        } 
                        else if (n == ' ' && buff != "") 
                        { 
                            words.push_back(buff); 
                            buff = "";
                        }
                    }

                    if (buff != "") 
                        words.push_back(buff);
                    // string_explode!

                    string cmd = words[0];

                    if (handlers_Command.count(cmd))
                    {
                        handlers_Command[cmd].callback(*this, u);
                    }
                    else
                    {
                        std::cout << "No CmdHandler for " << cmd << std::endl;
                    }
                }
                else
                {
                    Message m = u.get_message();

                    if (able_checks & UpdateFilters::TEXT)
                        handler_Text->callback(*this, m);
                    else if (able_checks & UpdateFilters::AUDIO)
                        handler_Audio->callback(*this, m);
                    else if (able_checks & UpdateFilters::VIDEO)
                        handler_Video->callback(*this, m);
                    else if (able_checks & UpdateFilters::DOCUMENT)
                        handler_Document->callback(*this, m);
                    else if (able_checks & UpdateFilters::VOICE)
                        handler_Voice->callback(*this, m);
                    else if (able_checks & UpdateFilters::PHOTO)
                        handler_Photo->callback(*this, m);
                    else if (able_checks & UpdateFilters::STICKER)
                        handler_Sticker->callback(*this, m);
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


void Bot::on_start(std::function<void(Bot)> callback)
{
    cb_OnStart = callback;
}
