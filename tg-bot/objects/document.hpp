#ifndef __TGBOT_OBJECTS_DOCUMENT
#define __TGBOT_OBJECTS_DOCUMENT

#include "_all.hpp"


class Document
{
public:
    Document(string);
    Document(json&&);

    string get_file_id() const noexcept
    {
        return file_id;
    }
    PhotoSize get_thumb() const;
    string get_file_name() const noexcept
    {
        return file_name.value_or("");
    }
    string get_mime_type() const noexcept
    {
        return mime_type.value_or("");
    }
    i32_t get_file_size() const noexcept
    {
        return file_size.value_or(0);
    }

private:
    string file_id;
    std::shared_ptr<PhotoSize> thumb;
    optional<string> file_name;
    optional<string> mime_type;
    optional<i32_t> file_size;
};


#endif // __TGBOT_OBJECTS_DOCUMENT