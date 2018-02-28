#include "chatphoto.hpp"

ChatPhoto::ChatPhoto(string jstr) : ChatPhoto::ChatPhoto(json::parse(jstr))
{
}

ChatPhoto::ChatPhoto(json j)
{
    std::cout << "TODO: ChatPhoto::ChatPhoto(json). JSON: " << j.dump(2) << std::endl;
}