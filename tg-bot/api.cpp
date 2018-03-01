#include "api.hpp"


const char* Api::PARSE_MODE_HTML = "HTML";
const char* Api::PARSE_MODE_MARKDOWN = "Markdown";


Api::Api(string tkn)
{
    token = tkn;
    last_update_id = -1;
    getUpdates(false);
}

Api::Api(const Api &a)
{
    token = a.token;
    last_update_id = a.last_update_id;
}

User Api::getMe()
{
    return User(execute("getMe", map()));
}

/*====================================================*/
/*==================== getUpdates ====================*/
/*====================================================*/
list<Update> Api::getUpdates()
{
    return getUpdates(10, true);
};

list<Update> Api::getUpdates(bool validate)
{
    return getUpdates(10, validate);
}

list<Update> Api::getUpdates(i32_t timeout_s)
{
    return getUpdates(timeout_s, true);
}

list<Update> Api::getUpdates(i32_t timeout_s, bool validate)
{
    list<Update> updates;
    map args;
    args["timeout"] = std::to_string(timeout_s);

    if (validate && last_update_id > 0)
        args["offset"] = std::to_string(last_update_id+1); // +1

    json jupdates = json::parse(execute("getUpdates", args));

    if (!jupdates.at("ok").get<bool>())
        throw std::invalid_argument("Error response from getUpdates()!");

    for (json &j : jupdates.at("result").get<list<json>>())
        updates.push_back(Update(j));

    if (!updates.empty() && validate) {
        last_update_id = updates.back().get_update_id();
    }

    return updates;
}
/*==================== END OF getUpdates ====================*/


inline string Api::escape_string(string s)
{
    string find = "\n";
    string replace = "%0A";

    for(string::size_type i = 0; (i = s.find(find, i)) != string::npos;)
    {
        s.replace(i, find.length(), replace);
        i += replace.length();
    }

    return s;
}

/*=====================================================*/
/*==================== sendMessage ====================*/
/*=====================================================*/
Message Api::sendMessage(string chat_id, string text)
{
    map args;
    args["chat_id"] = chat_id;
    args["text"] = escape_string(text);

    return Message(execute("sendMessage", args));
}

Message Api::sendMessage(i32_t chat_id, string text)
{
    return sendMessage(std::to_string(chat_id), text);
}

Message Api::sendMessage(i32_t chat_id, string text, string parse_mode)
{
    return sendMessage(std::to_string(chat_id), text, parse_mode.c_str());
}

Message Api::sendMessage(string chat_id, string text, const char *parse_mode)
{
    map args;
    args["chat_id"] = chat_id;
    args["text"] = escape_string(text);
    args["parse_mode"] = string(parse_mode);

    return Message(execute("sendMessage", args));
}
Message Api::sendMessage(string chat_id, string text, const char *parse_mode, 
                    bool disable_page_preview)
{
    map args;
    args["chat_id"] = chat_id;
    args["text"] = escape_string(text);
    args["parse_mode"] = string(parse_mode);
    args["disable_page_preview"] = string(disable_page_preview ? "true" : "false");

    return Message(execute("sendMessage", args));
}
Message Api::sendMessage(string chat_id, string text, const char *parse_mode, 
                    bool disable_page_preview, bool disable_notification)
{
    map args;
    args["chat_id"] = chat_id;
    args["text"] = escape_string(text);
    args["parse_mode"] = string(parse_mode);
    args["disable_page_preview"] = string(disable_page_preview ? "true" : "false");
    args["disable_notification"] = string(disable_notification ? "true" : "false");

    return Message(execute("sendMessage", args));
}

Message Api::sendMessage(string chat_id, string text, const char *parse_mode, 
                    bool disable_page_preview, bool disable_notification,
                    i32_t reply_to_message_id)
{
    map args;
    args["chat_id"] = chat_id;
    args["text"] = escape_string(text);
    args["parse_mode"] = string(parse_mode);
    args["disable_page_preview"] = string(disable_page_preview ? "true" : "false");
    args["disable_notification"] = string(disable_notification ? "true" : "false");
    args["reply_to_message_id"] = std::to_string(reply_to_message_id);

    return Message(execute("sendMessage", args));
}

Message Api::sendMessage(string chat_id, string text, map args)
{
    args["chat_id"] = chat_id;
    args["text"] = escape_string(text);

    return Message(execute("sendMessage", args));
}
/*==================== END OF sendMessage ====================*/



/*========================================================*/
/*==================== forwardMessage ====================*/
/*========================================================*/
Message Api::forwardMessage(i32_t chat_id, i32_t from_chat_id, i32_t message_id)
{
    return forwardMessage(std::to_string(chat_id), std::to_string(from_chat_id), 
            message_id);
}
Message Api::forwardMessage(i32_t chat_id, i32_t from_chat_id, i32_t message_id, 
                        bool disable_notification) 
{
    return forwardMessage(std::to_string(chat_id), std::to_string(from_chat_id), 
            message_id, disable_notification);
}

Message Api::forwardMessage(i32_t chat_id, string from_chat_id, i32_t message_id)
{
    return forwardMessage(std::to_string(chat_id), from_chat_id, message_id);
}

Message Api::forwardMessage(i32_t chat_id, string from_chat_id, i32_t message_id, 
                        bool disable_notification) 
{
    return forwardMessage(std::to_string(chat_id), from_chat_id, 
            message_id, disable_notification);
}

Message Api::forwardMessage(string chat_id, i32_t from_chat_id, i32_t message_id)
{
    return forwardMessage(chat_id, std::to_string(from_chat_id), message_id);
}

Message Api::forwardMessage(string chat_id, i32_t from_chat_id, i32_t message_id, 
                        bool disable_notification) 
{
    return forwardMessage(chat_id, std::to_string(from_chat_id), 
            message_id, disable_notification);
}

Message Api::forwardMessage(string chat_id, string from_chat_id, i32_t message_id)
{
    map args;
    args["chat_id"] = chat_id;
    args["from_chat_id"] = from_chat_id;
    args["message_id"] = std::to_string(message_id);

    return Message(execute("forwardMessage", args));
}

Message Api::forwardMessage(string chat_id, string from_chat_id, i32_t message_id, 
                           bool disable_notification)
{
    map args;
    args["chat_id"] = chat_id;
    args["from_chat_id"] = from_chat_id;
    args["message_id"] = std::to_string(message_id);
    args["disable_notification"] = string(disable_notification ? "true" : "false");

    return Message(execute("forwardMessage", args));
}
/*==================== END OF forwardMessage ====================*/



/*===================================================*/
/*==================== sendPhoto ====================*/
/*===================================================*/
string Api::sendPhoto(i32_t chat_id, FileFrom from, string filename)
{
    return sendPhoto(std::to_string(chat_id), from, filename);
}

string Api::sendPhoto(string chat_id, FileFrom from, string filename)
{
    map args;
    args["chat_id"] = chat_id;

    switch (from)
    {
        case DISK:
            return executeSend("sendPhoto", args, "photo", filename);
        case FILE_ID:
        case URL:
            args["photo"] = filename;
            return execute("sendPhoto", args);
        default:
            throw std::invalid_argument("Invalid file type!");
    }
}
/*==================== END OF sendPhoto ====================*/



/*===================================================*/
/*==================== sendAudio ====================*/
/*===================================================*/
string Api::sendAudio(i32_t chat_id, FileFrom from, string filename)
{
    return sendAudio(std::to_string(chat_id), from, filename);
}

string Api::sendAudio(string chat_id, FileFrom from, string filename)
{
    map args;
    args["chat_id"] = chat_id;

    switch (from)
    {
        case DISK:
            return executeSend("sendAudio", args, "audio", filename);
        case FILE_ID:
        case URL:
            args["audio"] = filename;
            return execute("sendAudio", args);
        default:
            throw std::invalid_argument("Invalid file type!");
    }
}
/*==================== END OF sendAudio ====================*/



/*======================================================*/
/*===================== sendDocument ===================*/
/*======================================================*/
string Api::sendDocument(i32_t chat_id, FileFrom from, string filename)
{
    return sendDocument(std::to_string(chat_id), from, filename);
}

string Api::sendDocument(string chat_id, FileFrom from, string filename)
{
    map args;
    args["chat_id"] = chat_id;

    switch (from)
    {
        case DISK:
            return executeSend("sendDocument", args, "document", filename);
        case FILE_ID:
        case URL:
            args["document"] = filename;
            return execute("sendDocument", args);
        default:
            throw std::invalid_argument("Invalid file type!");
    }
}
/*==================== END OF sendDocument ====================*/



/*======================================================*/
/*===================== sendVideo ======================*/
/*======================================================*/
string Api::sendVideo(i32_t chat_id, FileFrom from, string filename)
{
    return sendVideo(std::to_string(chat_id), from, filename);
}

string Api::sendVideo(string chat_id, FileFrom from, string filename)
{
    map args;
    args["chat_id"] = chat_id;

    switch (from)
    {
        case DISK:
            return executeSend("sendVideo", args, "video", filename);
        case FILE_ID:
        case URL:
            args["video"] = filename;
            return execute("sendVideo", args);
        default:
            throw std::invalid_argument("Invalid file type!");
    }
}
/*==================== END OF sendVideo ====================*/



/*======================================================*/
/*===================== sendVoice ======================*/
/*======================================================*/
string Api::sendVoice(i32_t chat_id, FileFrom from, string filename)
{
    return sendVoice(std::to_string(chat_id), from, filename);
}

string Api::sendVoice(string chat_id, FileFrom from, string filename)
{
    map args;
    args["chat_id"] = chat_id;

    switch (from)
    {
        case DISK:
            return executeSend("sendVoice", args, "voice", filename);
        case FILE_ID:
        case URL:
            args["voice"] = filename;
            return execute("sendVoice", args);
        default:
            throw std::invalid_argument("Invalid file type!");
    }
}
/*==================== END OF sendVoice ====================*/



/*======================================================*/
/*===================== sendContact ====================*/
/*======================================================*/
string Api::sendContact(i32_t chat_id, string phone_number, string first_name)
{
    return sendContact(std::to_string(chat_id), phone_number, first_name);
}
string Api::sendContact(i32_t chat_id, string phone_number, 
                    string first_name, string last_name)
{
    return sendContact(std::to_string(chat_id), phone_number, first_name, last_name);
}
string Api::sendContact(i32_t chat_id, string phone_number, 
                    string first_name, bool disable_notification,
                    i32_t reply_to_message_id)
{
    return sendContact(std::to_string(chat_id), phone_number, first_name, 
                disable_notification, reply_to_message_id);
}
string Api::sendContact(i32_t chat_id, string phone_number, 
                    string first_name, string last_name,
                    bool disable_notification)
{
    return sendContact(std::to_string(chat_id), phone_number, 
                first_name, last_name, disable_notification);
}
string Api::sendContact(i32_t chat_id, string phone_number, 
                    string first_name, string last_name, bool disable_notification,
                    i32_t reply_to_message_id)
{
    return sendContact(std::to_string(chat_id), phone_number, 
                first_name, last_name, disable_notification, reply_to_message_id);
}
string Api::sendContact(i32_t chat_id, string phone_number, 
                       string first_name, string last_name, i32_t reply_to_message_id)
{
    return sendContact(std::to_string(chat_id), phone_number, 
                first_name, last_name, reply_to_message_id);
}

string Api::sendContact(string chat_id, string phone_number, string first_name)
{
    map args;
    args["chat_id"] = chat_id;
    args["phone_number"] = phone_number;
    args["first_name"] = first_name;

    return execute("sendContact", args);
}
string Api::sendContact(string chat_id, string phone_number, 
                    string first_name, string last_name)
{
    map args;
    args["chat_id"] = chat_id;
    args["phone_number"] = phone_number;
    args["first_name"] = first_name;
    args["last_name"] = last_name;

    return execute("sendContact", args);
}
string Api::sendContact(string chat_id, string phone_number, 
                    string first_name, bool disable_notification,
                    i32_t reply_to_message_id)
{
    map args;
    args["chat_id"] = chat_id;
    args["phone_number"] = phone_number;
    args["first_name"] = first_name;
    args["disable_notification"] = string(disable_notification? "true" : "false");
    args["reply_to_message_id"] = std::to_string(reply_to_message_id);

    return execute("sendContact", args);
}
string Api::sendContact(string chat_id, string phone_number, 
                    string first_name, string last_name,
                    bool disable_notification)
{
    map args;
    args["chat_id"] = chat_id;
    args["phone_number"] = phone_number;
    args["first_name"] = first_name;
    args["last_name"] = last_name;
    args["disable_notification"] = string(disable_notification? "true" : "false");

    return execute("sendContact", args);
}
string Api::sendContact(string chat_id, string phone_number, 
                    string first_name, string last_name, bool disable_notification,
                    i32_t reply_to_message_id)
{
    map args;
    args["chat_id"] = chat_id;
    args["phone_number"] = phone_number;
    args["first_name"] = first_name;
    args["last_name"] = last_name;
    args["disable_notification"] = string(disable_notification? "true" : "false");
    args["reply_to_message_id"] = std::to_string(reply_to_message_id);

    return execute("sendContact", args);
}
string Api::sendContact(string chat_id, string phone_number, 
                       string first_name, string last_name,
                       i32_t reply_to_message_id)
{
    map args;
    args["chat_id"] = chat_id;
    args["phone_number"] = phone_number;
    args["first_name"] = first_name;
    args["last_name"] = last_name;
    args["reply_to_message_id"] = std::to_string(reply_to_message_id);

    return execute("sendContact", args);
}
/*==================== END OF sendContact ====================*/

/*===========================================================*/
/*======================= sendChatAction ====================*/
/*===========================================================*/
bool Api::sendChatAction(i32_t chat_id, string action)
{
    return sendChatAction(std::to_string(chat_id), action);
}

bool Api::sendChatAction(string chat_id, string action)
{
    map args;
    args["chat_id"] = chat_id;
    args["action"] = action;

    json jres = json::parse(execute("sendChatAction", args));

    return jres.at("ok").get<bool>() && jres.at("result").get<bool>();
}
/*==================== END OF sendChatAction ====================*/



/*==============================================================*/
/*==================== getUserProfilePhotos ====================*/
/*==============================================================*/
string Api::getUserProfilePhotos(i32_t user_id)
{
    map args;
    args["user_id"] = std::to_string(user_id);

    return execute("getUserProfilePhotos", args);
}

string Api::getUserProfilePhotos(i32_t user_id, i32_t offset)
{
    map args;
    args["user_id"] = std::to_string(user_id);
    args["offset"] = std::to_string(offset);

    return execute("getUserProfilePhotos", args);
}

string Api::getUserProfilePhotos(i32_t user_id, i32_t offset, i32_t limit)
{
    map args;
    args["user_id"] = std::to_string(user_id);
    args["offset"] = std::to_string(offset);
    args["limit"] = std::to_string(limit);

    return execute("getUserProfilePhotos", args);
}
/*==================== END OF getUserProfilePhotos ====================*/



/*==============================================================*/
/*=========================== getFile ==========================*/
/*==============================================================*/
string Api::getFile(string file_id)
{
    map args;
    args["file_id"] = file_id;

    return execute("getFile", args);
}
/*======================= END OF getFile =========================*/



/*=====================================================================*/
/*=========================== kickChatMember ==========================*/
/*=====================================================================*/
bool Api::kickChatMember(i32_t chat_id, i32_t user_id)
{
    return kickChatMember(std::to_string(chat_id), user_id);
}

bool Api::kickChatMember(i32_t chat_id, i32_t user_id, i32_t until_date)
{
    return kickChatMember(std::to_string(chat_id), user_id, until_date);
}

bool Api::kickChatMember(string chat_id, i32_t user_id)
{
    map args;
    args["chat_id"] = chat_id;
    args["user_id"] = std::to_string(user_id);

    json jres = json::parse(execute("kickChatMember", args));

    return jres.at("ok").get<bool>();
}

bool Api::kickChatMember(string chat_id, i32_t user_id, i32_t until_date)
{
    map args;
    args["chat_id"] = chat_id;
    args["user_id"] = std::to_string(user_id);
    args["until_date"] = std::to_string(until_date);

    json jres = json::parse(execute("kickChatMember", args));

    return jres.at("ok").get<bool>();
}
/*=========================== END OF kickChatMember ==========================*/


/*======================================================================*/
/*=========================== unbanChatMember ==========================*/
/*======================================================================*/
bool Api::unbanChatMember(i32_t chat_id, i32_t user_id)
{
    return unbanChatMember(std::to_string(chat_id), user_id);
}
bool Api::unbanChatMember(string chat_id, i32_t user_id)
{
    map args;
    args["chat_id"] = chat_id;
    args["user_id"] = std::to_string(user_id);

    json jres = json::parse(execute("unbanChatMember", args));
    
    return jres.at("ok").get<bool>();
}
/*=========================== END OF unbanChatMember ==========================*/



/*======================================================*/
/*===================== restrictChatMember ====================*/
/*======================================================*/
bool Api::restrictChatMember(i32_t chat_id, i32_t user_id)
{
    return restrictChatMember(std::to_string(chat_id), user_id);
}
bool Api::restrictChatMember(i32_t chat_id, i32_t user_id, i32_t until_date)
{
    return restrictChatMember(std::to_string(chat_id), user_id, until_date);
}
bool Api::restrictChatMember(i32_t chat_id, i32_t user_id, 
        bool can_send_messages, bool can_send_media_messages, 
        bool can_send_other_messages, bool can_add_web_page_previews)
{
    return restrictChatMember(std::to_string(chat_id), user_id, 
            can_send_messages, can_send_media_messages,
            can_send_other_messages, can_add_web_page_previews);
}
bool Api::restrictChatMember(i32_t chat_id, i32_t user_id, i32_t until_date, 
        bool can_send_messages, bool can_send_media_messages, 
        bool can_send_other_messages, bool can_add_web_page_previews)
{
    return restrictChatMember(std::to_string(chat_id), user_id, until_date, 
            can_send_messages, can_send_media_messages,
            can_send_other_messages, can_add_web_page_previews);
}
bool Api::restrictChatMember(string chat_id, i32_t user_id)
{
    map args;
    args["chat_id"] = chat_id;
    args["user_id"] = user_id;

    json jres = json::parse(execute("restrictChatMember", args));
    return jres.at("ok").get<bool>();
}
bool Api::restrictChatMember(string chat_id, i32_t user_id, i32_t until_date)
{
    map args;
    args["chat_id"] = chat_id;
    args["user_id"] = user_id;
    args["until_date"] = until_date;

    json jres = json::parse(execute("restrictChatMember", args));
    return jres.at("ok").get<bool>();   
}
bool Api::restrictChatMember(string chat_id, i32_t user_id, 
        bool can_send_messages, bool can_send_media_messages, 
        bool can_send_other_messages, bool can_add_web_page_previews)
{
    map args;
    args["chat_id"] = chat_id;
    args["user_id"] = user_id;
    args["can_send_messages"] = string(can_send_messages ? "true" : "false");
    args["can_send_media_messages"] = string(can_send_media_messages ? "true" : "false");
    args["can_send_other_messages"] = string(can_send_other_messages ? "true" : "false");
    args["can_add_web_page_previews"] = string(can_add_web_page_previews ? "true" : "false");

    json jres = json::parse(execute("restrictChatMember", args));
    return jres.at("ok").get<bool>();
}
bool Api::restrictChatMember(string chat_id, i32_t user_id, i32_t until_date, 
        bool can_send_messages, bool can_send_media_messages, 
        bool can_send_other_messages, bool can_add_web_page_previews)
{
    map args;
    args["chat_id"] = chat_id;
    args["user_id"] = user_id;
    args["until_date"] = until_date;    
    args["can_send_messages"] = string(can_send_messages ? "true" : "false");
    args["can_send_media_messages"] = string(can_send_media_messages ? "true" : "false");
    args["can_send_other_messages"] = string(can_send_other_messages ? "true" : "false");
    args["can_add_web_page_previews"] = string(can_add_web_page_previews ? "true" : "false");

    json jres = json::parse(execute("restrictChatMember", args));
    return jres.at("ok").get<bool>();    
}
/*==================== END OF restrictChatMember ====================*/



/*=====   PRIVATE:   =====   PRIVATE:   =====   PRIVATE:   =====*/
/*=====   PRIVATE:   =====   PRIVATE:   =====   PRIVATE:   =====*/
/*=====   PRIVATE:   =====   PRIVATE:   =====   PRIVATE:   =====*/
string Api::execute(const char *method, map args)
{
    CURL *curl;
    CURLcode curlres;
    std::string res;
    std::string req = "https://api.telegram.org/bot" + token + "/" + method;

    for (auto it = args.begin(); it != args.end(); it++) 
    {
        req.append(it == args.begin() ? "?" : "&");
        req.append(it->first);
        req.append("=");
        req.append(it->second);
    }

    std::cout << req << std::endl;

    curl = curl_easy_init();
    if (curl) 
    {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0); //remove this to disable verbose output
        curl_easy_setopt(curl, CURLOPT_URL, req.c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // only for https
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); // only for https
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);

        if (curl_easy_perform(curl) != CURLE_OK)
            std::cerr << "curl_easy_perform() failed!" << std::endl;
    } 
    else 
    {
        std::cerr << "curl_easy_init() failed!" << std::endl;        
    }
    curl_easy_cleanup(curl);

    return res;
}

string Api::execute(const char *method, json args)
{
    CURL *curl;
    CURLcode curlres;
    std::string res;
    std::string req = "https://api.telegram.org/bot" + token + "/" + method;
    
    curl = curl_easy_init();
    if (curl) 
    {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L); // remove this to disable verbose output
        curl_easy_setopt(curl, CURLOPT_URL, req.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, args.dump().c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // only for https
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); // only for https
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);

        std::cout << req << std::endl;

        if (curl_easy_perform(curl) != CURLE_OK)
            std::cerr << "curl_easy_perform() failed!" << std::endl;
    } 
    else 
    {
        std::cerr << "curl_easy_init() failed!" << std::endl;        
    }
    curl_easy_cleanup(curl);

    return res;
}

string Api::executeSend(const char *method, map args, const char *fieldname, string filename)
{
    CURL *curl;
    CURLcode curlres;
    struct curl_httppost *formpost = NULL;
    struct curl_httppost *lastptr = NULL;
    std::string res;
    std::string req = "https://api.telegram.org/bot" + token + "/" + method;

    curl = curl_easy_init();
    if (curl)
    {
        curl_formadd(&formpost, &lastptr, 
            CURLFORM_COPYNAME, fieldname,
            CURLFORM_FILE, filename.c_str(),
            CURLFORM_END
        );

        for (auto it = args.begin(); it != args.end(); it++)
        {
            curl_formadd(&formpost, &lastptr, 
                CURLFORM_COPYNAME, it->first.c_str(),
                CURLFORM_COPYCONTENTS, it->second.c_str(),
                CURLFORM_END
            );
        }

        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L); // remove this to disable verbose output
        curl_easy_setopt(curl, CURLOPT_URL, req.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);

        if (curl_easy_perform(curl) != CURLE_OK)
            std::cerr << "curl_easy_perform() failed!" << std::endl;

        curl_formfree(formpost);
    } 
    else 
    {
        std::cerr << "curl_easy_init() failed!" << std::endl;
    }
    curl_easy_cleanup(curl);

    return res;
}


size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, string *s)
{
    size_t newLength = size*nmemb;
    size_t oldLength = s->size();
    try
    {
        s->resize(oldLength + newLength);
    }
    catch(std::bad_alloc &e)
    {
        // TODO: handle memory problem
        return 0;
    }

    std::copy((char*)contents, (char*)contents+newLength, s->begin()+oldLength);
    return size*nmemb;
}
