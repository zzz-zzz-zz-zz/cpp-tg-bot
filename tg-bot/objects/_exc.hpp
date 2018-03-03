#ifndef __TGBOT_EXCEPTIONS
#define __TGBOT_EXCEPTIONS

#include <exception>
#include <string>

class TelegramException : public std::exception
{
public:
    TelegramException(const std::string msg="No message specified!")
    {
        message = "TelegramException: " + msg;
    }

    virtual ~TelegramException(void) {}
    virtual const char* what() { return message.c_str(); }
protected:
    std::string message;
};

class TelegramApiException : public TelegramException
{
public:
    TelegramApiException(const std::string msg="No message specified!")
    {
        message = "TelegramApiException: " + msg;
    }
};


class TelegramBadRequestException : public TelegramApiException
{
public:
    TelegramBadRequestException(const std::string msg="No message specified!")
    {
        message = "TelegramBadRequestException: " + msg;
    }
};

class TelegramObjectException : public TelegramException
{
public:
    TelegramObjectException(const std::string msg="No message specified!")
    {
        message = "TelegramObjectException: " + msg;
    }
};

class TelegramNullObjectException : public TelegramObjectException
{
public:
    TelegramNullObjectException(const std::string msg="No message specified!")
    {
        message = "TelegramNullObjectException: " + msg;
    }
};


#endif // __TGBOT_EXCEPTIONS