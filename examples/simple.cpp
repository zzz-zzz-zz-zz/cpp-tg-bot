#include "../tg-bot/bot.hpp"

#include <iostream>
#include <vector>
using std::vector;

const vector<i32_t> admins = {354454314};



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
{ // ECHOBOT which stores prev messages
    Bot b("[[TOKEN]]");
    string messages = "";

    b.on_start([&](Bot *bot)
    { // When bot started
        std::cout << "Bot @" << bot->api->getMe().get_username() << " started!" << std::endl;
    });
    b.on_update([&](Bot *bot, Update *update)
    { // On each update this function calls
        if (!update->has_message())
            return;

        if (Message m = update->get_message(); m.has_text())
        {
            messages += m.get_text() + "\n";
            bot->api->sendMessage(m.get_chat().get_id(), messages);
        }
    });
    b.start_polling();

    return 0;
}
