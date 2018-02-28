#include "tg-bot/bot.hpp"

#include <limits>
#include <iostream>
#include <vector>
using std::vector;

/**
 * For switch-case with strings. C++11 feature
 **/
constexpr unsigned int hash(const char* str, int h=0)
{
    return !str[h] ? 5381 : (hash(str, h+1)*33) ^ str[h];
}

/**
 * Explode string with delimiter c
 **/
const vector<string> explode(const string &s, const char &c)
{
	string buff = "";
	vector<string> v;
	
	for (const auto &n : s)
	{
		if (n != c)
        {
            buff += n;             
        } 
        else if (n == c && buff != "") 
        { 
            v.push_back(buff); 
            buff = ""; 
        }
	}

	if (buff != "") 
        v.push_back(buff);
	
	return v;
}

int main(int argc, char *argv[])
{
    if (argc == 1) 
    {
        std::cerr << "Usage: " << argv[0] << " [TOKEN]" << std::endl;
        return 1;
    }

    Bot b = argv[1];

    // Passing only callback equals to UpdateFilers::ALL
    b.on_update(Bot::UpdateFilters::ALL, [](Bot *bot, Update *update) 
    {
        Message m = update->get_message();
        if (!m.has_text())
            return;

        long chat_id = m.get_chat().get_id();
        string text = m.get_text();
        auto words = explode(text, ' ');

        std::cout << "NEW UPDATE. TEXT: " << text << std::endl;

        switch (hash(words[0].c_str()))
        {
            case hash("sendMessage"):
                bot->api->sendMessage(chat_id, "Message");
                break;
            case hash("sendPhoto"):
                bot->api->sendPhoto(chat_id, Api::FileFrom::FILE_ID, 
                    "AgADAgADBqkxG3dYkUiNhAY9Am4gFQiZQw4ABH4Pbxwde2VqAckBAAEC");
                break;
            case hash("forwardMessage"):
                bot->api->forwardMessage(chat_id, chat_id, m.get_message_id());
                break;
            case hash("sendAudio"):
                bot->api->sendAudio(chat_id, Api::FileFrom::DISK, "media/audio.mp3");
                break;
            case hash("sendDocument"):
                std::cout << bot->api->sendDocument(chat_id, Api::FileFrom::DISK, "media/json.hpp");
                break;
            case hash("sendVideo"):
                std::cout << bot->api->sendVideo(chat_id, Api::FileFrom::DISK, "media/video.mp4");
                break;
            case hash("sendVoice"):
                bot->api->sendVoice(chat_id, Api::FileFrom::DISK, "media/voice.ogg");
                break;
            case hash("sendContact"):
                std::cout << bot->api->sendContact(chat_id, "+380977438313", "For", "Example");
                break;
            case hash("sendChatAction"):
                if (words.size() == 2)
                {
                    if (bot->api->sendChatAction(chat_id, words[1])) 
                    {
                        std::cout << "sendChatAction(" << words[1] << ") - TRUE\n";                        
                    }
                    else 
                    {
                        std::cout << "sendChatAction(" << words[1] << ") - FALSE\n";
                        bot->api->sendMessage(chat_id, "Invalid chat action!");
                    }
                }
                else
                {
                    bot->api->sendMessage(chat_id, "Please, specify chat action after space!");
                }
                break;
            default:
                bot->api->sendMessage(chat_id, 
                    "Options:\nsendMessage\nsendPhoto\nforwardMessage"
                            "\nsendAudio\nsendDocument\nsendVideo\nsendVoice"
                            "\nsendContact\nsendChatAction"
                );
        }

    }); 
    b.start_polling();

    return 0;
}
