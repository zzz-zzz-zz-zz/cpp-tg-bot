# Telegram Bot API C++
Handy Telegram bot API wrapper. **IN DEVELOPMENT**.

## Status
- Current status: **In Development**
- Version: __0.1a__
- Depencencies: 
  - [libcurl](https://www.github.com/curl/curl)(install with [this guide](https://curl.haxx.se/docs/install.html))
  - [nlohmann/json](https://www.github.com/nlohmann/json)(1 .hpp file. Easy to remove this dep)
- Realized bot features: *polling*, *callbacks*

## Simple Example

```C++
#include "tg-bot/bot.hpp"

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

```

## Realised API methods:
|Method name|Status|Overloads|Note|
|---|---|---|---|
|sendMessage|Good|+7|`Message` is not finished yet|
|forwardMessage|Good|+7|☝️|
|sendPhoto|Raw|+1|*TODO: overloads?*|
|sendAudio|Raw|+1|`Audio` is not realized yet|
|sendDocument|Raw|+1|`Document` is not realized yet|
|sendVideo|Raw|+1|`Video` is not realized yet|
|sendVoice|Raw|+1|`Voice` is not realized yet|
|sendVideoNote|TODO||`VideoNote` is not realized yet|
|sendMediaGroup|TODO|||
|sendLocation|TODO||`Location` is not realized yet|
|editMessageLiveLocation|TODO||☝️|
|stopMessageLiveLocation|TODO||☝️|
|sendVenue|Not exists||`Venue` is not realized yet|
|sendContact|Good|+11|`Contact` is not realized yet
|sendChatAction|Good|+1|No constants for chat actions|
|getUserProfilePhotos|Good|+2|`UserProfilePhotos` is not realized yet|
|getFile|Good||`File` is not realized yet|
|kickChatMember|Nice|+3|*TODO: add easy ban for mins/hours/days*|
|unbanChatMember|Done|+1||
|restrictChatMember|Nice|+7|*TODO: add easy ban for mins/hours/days*|
|**Nothing else yet**|**...**|**...**|**TODO next methods**|

## Realized API object types:
|Type|Status|Note|
|---|---|---|
|User|Done||
|Chat|Good|*TODO: Add move-constr, operator=*|
|Message|Raw|A lot of *TODO* there|
|PhotoSize|Nice|*TODO: tests?*|
|Sticker|Nice|*TODO: `MaskPosition`*|
|**Empty or nonexistent types**|**...**|**TODO next types**|

## TODO list:
- Realize and finish off more methods
- Realize and finish off more types
- More tools + WebHook
- Multithreading + Async
- Own exceptions
- Shield with namespace
- **...**