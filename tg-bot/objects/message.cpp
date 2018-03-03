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
    chat = std::make_unique<Chat>(j.at("chat").get<json>());

    try {
        from = std::make_unique<User>(j.at("from").get<json>());
    } catch (exception &e) {
        std::cerr << "Message::Message(json): from is empty!" << std::endl;
        from = nullptr;
    }

    OMIT(text = string(j.at("text").get<string>()))
    OMIT(audio = std::make_unique<Audio>(j.at("audio").get<json>()))

    std::cout << "TOFINISH: Message::Message(json)!" << std::endl;
    // TODO: other
}

Message::Message(const Message &that)
{
    message_id = that.message_id;
    date = that.date;
    chat = that.chat; //shared_ptr
    text = that.text;
    from = that.from; //shared_ptr
    audio = that.audio; //shared_ptr
}

Message::Message(Message &&that) noexcept
{
    message_id = std::move(that.message_id);
    date = std::move(that.date);
    chat = std::move(that.chat);
    text = std::move(that.text);
    from = std::move(that.from);
    audio = std::move(that.audio);
}




Chat Message::get_chat() {
    if (!chat) // Most likely !!EXCESS!! check
        throw TelegramNullObjectException("Message::get_chat(): chat is empty!");
    
    return *chat;
}

User Message::get_from() {
    if (!from) // Most likely !!EXCESS!! check
        throw TelegramNullObjectException("Message::get_from(): from is empty!");

    return *from;
}