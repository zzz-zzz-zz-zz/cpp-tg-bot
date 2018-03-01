#ifndef __TGBOT_EXCEPTIONS
#define __TGBOT_EXCEPTIONS

#include <exception>
#include <string>


class TelegramApiException : public std::exception
{
public:
    TelegramApiException(const std::string msg="No message specified!")
    {
        message = "TelegramApiException: " + msg;
    }

    ~TelegramApiException(void) {}
    virtual const char* what() { return message.c_str(); }
protected:
    std::string message;
};


class TelegramBadRequestException : public TelegramApiException
{
public:
    TelegramBadRequestException(const std::string msg="No message specified!")
    {
        message = "TelegramBadRequestException: " + msg;
    }

    ~TelegramBadRequestException(void) {}
};


#endif // __TGBOT_EXCEPTIONS