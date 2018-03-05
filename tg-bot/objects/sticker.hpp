#ifndef __TGBOT_OBJECTS_STICKER
#define __TGBOT_OBJECTS_STICKER

#include "_all.hpp"


class Sticker
{
public:
    Sticker(string jstr);
    Sticker(json j);

    string get_file_id() const noexcept
    {
        return file_id;
    }
    i32_t get_width() const noexcept
    {
        return width;
    }
    i32_t get_height() const noexcept
    {
        return height;
    }
    PhotoSize get_thumb() const;
    string get_emoji() const noexcept
    {
        return emoji.value_or("");
    }
    string get_set_name() const noexcept
    {
        return set_name.value_or("");
    }
    i32_t get_file_size() const noexcept
    {
        return file_size.value_or(0);
    }

private:
    string file_id;
    i32_t width;
    i32_t height;
    shared_ptr<PhotoSize> thumb = nullptr;
    optional<string> emoji;
    optional<string> set_name;
    //TODO: shared_ptr<MaskPosition> mask_position = nullptr
    optional<i32_t> file_size;
};


#endif // __TGBOT_OBJECTS_STICKER