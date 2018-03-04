#ifndef __TGBOT_BOT
#define __TGBOT_BOT

#include "objects/_all.hpp"
#include "api.hpp"

enum UpdateFilters
{
    ALL_OTHERS = -9000,
    NONE     = 0,
    TEXT     = 0b0000000000000001,
    AUDIO    = 0b0000000000000010,
    VIDEO    = 0b0000000000000100,
    DOCUMENT = 0b0000000000001000,
    VOICE    = 0b0000000000010000,
    COMMAND  = 0b0000000000100000,
    PHOTO    = 0b0000000001000000,
    STICKER  = 0b0000000010000000,
    // TODO: more
    ALL      = 0b1111111111111111
};


class Handler
{
protected:
    Handler(i32_t filters, std::function<void(Bot*, Update*)> callback)
    {
        this->filters = filters;
        this->callback = callback;
    }

    i32_t filters;
    std::function<void(Bot*, Update*)> callback;

    friend class Bot;
};

class MessageHandler : public Handler
{
public:
    MessageHandler(i32_t filters, std::function<void(Bot*, Update*)> callback)
            : Handler(filters, callback)
    { }
};

class CommandHandler : public Handler
{
public:
    CommandHandler(string command, std::function<void(Bot*, Update*)> callback)
            : Handler(UpdateFilters::COMMAND, callback), command("/" + command)
    { }

    string get_command() { return command; }
private:
    string command;
};

class Bot
{
public:
    Bot(string);
    ~Bot();

    bool has_updates();

    void on_start(std::function<void(Bot*)> callback);
    void on_command(string command, std::function<void(Bot*, Update*)> callback);
    void on_message(i32_t filterflags, std::function<void(Bot*, Update*)> callback);

    void start_polling(i32_t timeout_s);
    void start_polling();

    Api *api;
private:
    std::function<void(Bot*)> cb_OnStart = nullptr;
    
    i32_t registered_filters = 0;
    shared_ptr<MessageHandler> handler_Text = nullptr;
    shared_ptr<MessageHandler> handler_Audio = nullptr;
    shared_ptr<MessageHandler> handler_Video = nullptr;
    shared_ptr<MessageHandler> handler_Document = nullptr;
    shared_ptr<MessageHandler> handler_Voice = nullptr;
    vector<CommandHandler> handlers_Command;
    shared_ptr<MessageHandler> handler_Photo = nullptr;
    shared_ptr<MessageHandler> handler_Sticker = nullptr;
};


#endif // __TGBOT_BOT