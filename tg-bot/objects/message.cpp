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
    from = std::make_shared<User>(j.at("from").get<json>());

    OMIT(text = string(j.at("text").get<string>()); 
        checks += UpdateFilters::TEXT;
        if (text.value()[0] == '/')
            checks += UpdateFilters::COMMAND;
    )
    OMIT(audio = std::make_shared<Audio>(j.at("audio").get<json>());
        checks += UpdateFilters::AUDIO; 
    )
    OMIT(document = std::make_shared<Document>(j.at("document").get<json>());
        checks += UpdateFilters::DOCUMENT;         
    )
    OMIT(sticker = std::make_shared<Sticker>(j.at("sticker").get<json>());
        checks += UpdateFilters::STICKER;
    )
    OMIT(
        json jphoto = j.at("photo");
        photo = std::make_shared<vector<PhotoSize>>();

        for (json::iterator it = jphoto.begin(); it != jphoto.end(); it++)
            photo->push_back(PhotoSize(*it));

        checks += UpdateFilters::PHOTO; 
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
    sticker = that.sticker;

    checks = that.checks;
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
    sticker = std::move(that.sticker);
    
    checks = std::move(that.checks);    
}




Chat Message::get_chat() const noexcept {
    return *chat;
}

User Message::get_from() const noexcept {
    return *from;
}

Document Message::get_document() const
{
    if (!document)
        throw TelegramNullObjectException("No document in message!");
    return *document;
}

Sticker Message::get_sticker() const
{
    if (!sticker)
        throw TelegramNullObjectException("No sticker in message!");
    return *sticker;
}
