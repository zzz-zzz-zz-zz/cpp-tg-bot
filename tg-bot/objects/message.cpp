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
    chat = std::make_shared<Chat>(j.at("chat").get<json>());

    try {
        from = std::make_shared<User>(j.at("from").get<json>());
    } catch (exception &e) {
        std::cerr << "Message::Message(json): from is empty!" << std::endl;
        from = nullptr;
    }

    OMIT(text = string(j.at("text").get<string>()))
    OMIT(audio = std::make_shared<Audio>(j.at("audio").get<json>()))
    OMIT(document = std::make_shared<Document>(j.at("document").get<json>()))
    OMIT(
        json jphoto = j.at("photo");
        photo = std::make_shared<vector<PhotoSize>>();

        for (json::iterator it = jphoto.begin(); it != jphoto.end(); it++)
            photo->push_back(PhotoSize(*it));
    )

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
    photo = that.photo;
    document = that.document;
}

Message::Message(Message &&that) noexcept
{
    message_id = std::move(that.message_id);
    date = std::move(that.date);
    chat = std::move(that.chat);
    text = std::move(that.text);
    from = std::move(that.from);
    audio = std::move(that.audio);
    photo = std::move(that.photo);
    document = std::move(that.document);
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

Document Message::get_document()
{
    if (!document)
        throw TelegramNullObjectException("No document!");
    return *document;
}