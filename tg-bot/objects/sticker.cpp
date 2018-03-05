#include "sticker.hpp"


Sticker::Sticker(string jstr) : Sticker(json::parse(jstr))
{ }

Sticker::Sticker(json j)
{
    std::cout << "Sticker(json): " << j.dump(2) << std::endl;
    file_id = j["file_id"].get<string>();
    width = j["width"].get<i32_t>();
    height = j["height"].get<i32_t>();

    OMIT(thumb = std::make_shared<PhotoSize>(j.at("thumb").get<json>()))
    OMIT(emoji = j.at("emoji").get<string>())
    OMIT(set_name = j.at("set_name").get<string>())
    //TODO: OMIT(mask_position = j.at("mask_position").get<json>())
    OMIT(file_size = j.at("file_size").get<i32_t>())
}

PhotoSize Sticker::get_thumb() const
{
    if (!thumb)
        throw TelegramNullObjectException("No thumb in sticker!");
    return *thumb;
}
