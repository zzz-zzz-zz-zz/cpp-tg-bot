#include "../tg-bot/bot.hpp"

#include <iostream>
#include <vector>
using std::vector;

const i32_t admin_id = 354454314; // It's my chat_id. Just for example needs

void on_cmd_start(Bot *bot, Update *update)
{
    bot->api->sendMessage(update->get_message().get_chat().get_id(), "Hello!");
}

void echo_photo(Bot* bot, Update* update)
{
    Message m = update->get_message();
    i32_t chat_id = m.get_chat().get_id();
    string file_id = m.get_photo()[0].get_file_id();

    bot->api->sendPhoto(chat_id, Api::FileFrom::FILE_ID, file_id);
}


int main(int argc, char *argv[])
{
    Bot b("---TOKEN---");
    string hello = "Hello world!";

    // Register callback(as lambda) on when bot launched
    b.on_start([](Bot *bot) {
        bot->api->sendMessage(admin_id, "Bot started!");
    });

    // Register callback(as C function) on '/start' [args] command
    b.on_command("start", on_cmd_start);

    // Capturing variables into lambda also works as expected
    b.on_command("hello", [&](Bot *bot, Update *update) {
        i32_t chat_id = update->get_message().get_chat().get_id();
        
        bot->api->sendMessage(chat_id, hello);
    });


    // Register callback on when it's plain text message(and not command obviously)
    b.on_message(UpdateFilters::TEXT, [](Bot* bot, Update* update) {
        Message m = update->get_message();
        i32_t chat_id = m.get_chat().get_id();

        bot->api->sendMessage(chat_id, m.get_text());
    });

    // Callback on when it's photo(as C function)
    b.on_message(UpdateFilters::PHOTO, echo_photo);

    // Callback on when it's not TEXT or PHOTO(declared above)(and not command obviously)
    b.on_message(UpdateFilters::ALL_OTHERS, [](Bot* bot, Update* update) {
        Message m = update->get_message();
        i32_t chat_id = m.get_chat().get_id();

        bot->api->sendMessage(chat_id, "Not photo or text!");
    });

    // Indicate bot to start infinite listening for updates with long polling(Press Ctrl+C to exit)
    b.start_polling();
    return 0;
}