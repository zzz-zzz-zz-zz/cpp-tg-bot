#include "photosize.hpp"


PhotoSize::PhotoSize(string jstr) : PhotoSize(json::parse(jstr))
{
}

PhotoSize::PhotoSize(json &j)
{ 
    file_id = j.at("file_id").get<string>();
    width = j.at("width").get<i32_t>();
    height = j.at("height").get<i32_t>();
    OMIT(file_size = j.at("file_size").get<i32_t>())
}

PhotoSize::PhotoSize(json &&j)
{
    file_id = j.at("file_id").get<string>();
    width = j.at("width").get<i32_t>();
    height = j.at("height").get<i32_t>();
    OMIT(file_size = j.at("file_size").get<i32_t>())
}