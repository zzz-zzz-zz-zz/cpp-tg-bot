#ifndef __TGBOT_OBJECTS_PHOTO_SIZE
#define __TGBOT_OBJECTS_PHOTO_SIZE

#include "_all.hpp"


class PhotoSize
{
public:
    PhotoSize() {}
    PhotoSize(string jstr);
    PhotoSize(json &j);
    PhotoSize(json &&j);

    string get_file_id() const noexcept { return file_id; }
    i32_t get_width() const noexcept { width > 0 ? width : 0; }
    i32_t get_height() const noexcept { height > 0 ? height : 0; }
    i32_t get_file_size() const noexcept { file_size > 0 ? file_size : 0; }
private:
    string file_id;
    i32_t width = -1;
    i32_t height = -1;
    i32_t file_size = -1;
};


#endif // __TGBOT_OBJECTS_PHOTO_SIZE