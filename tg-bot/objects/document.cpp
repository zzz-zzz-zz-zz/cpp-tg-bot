#include "document.hpp"


Document::Document(string jstr) : Document(json::parse(jstr))
{ }

Document::Document(json j)
{
    std::cout << "Document(json): " << j.dump(2) << std::endl;

    file_id = j.at("file_id").get<string>();
    OMIT(file_name = j.at("file_name").get<string>())
    OMIT(mime_type = j.at("mime_type").get<string>())
    OMIT(file_size = j.at("file_size").get<i32_t>())
    OMIT(thumb = std::make_shared<PhotoSize>(j.at("thumb").get<json>()))
}

 PhotoSize Document::get_thumb() const
{
    if (!thumb)
        throw TelegramNullObjectException("No thumb in document");
    return *thumb;
}