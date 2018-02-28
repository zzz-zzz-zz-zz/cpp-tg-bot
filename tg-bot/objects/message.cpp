#include "message.hpp"

Message::Message(string jstr) : Message::Message(json::parse(jstr))
{
}

Message::Message(json j)
{
    std::cout << "TODO: Message::Message(json) JSON: " << j.dump(2) << std::endl;

    OMIT(
        if (j.at("ok").get<bool>())
            j = j["result"];
        else
            throw std::invalid_argument("Message::Message(json): \"result\" is false!");
    )

    message_id = j.at("message_id").get<int>();
    date = j.at("date").get<int>();
    chat = new Chat(j.at("chat").get<json>());

    try {
        from = new User(j.at("from").get<json>());
    } catch (exception &e) {
        std::cerr << "Message::Message(json): from is empty!" << std::endl;
        from = nullptr;
    }

    OMIT(text = string(j.at("text").get<string>()))
    OMIT(audio = new Audio(j.at("audio").get<json>()))

    std::cout << "TOFINISH: Message::Message(json)!" << std::endl;
    // TODO: other
}


Chat Message::get_chat() {
    return *chat;
}

User Message::get_from() {
    if (from == nullptr)
        throw std::invalid_argument("Message.from is empty!");
    return *from;
}