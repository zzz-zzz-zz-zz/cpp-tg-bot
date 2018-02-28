#include "update.hpp"

/**
 * Create Update from string containing json presentation of object
 **/
Update::Update(string jstr) : Update::Update(json::parse(jstr))
{
}

/**
 * Create Update from json object 
 **/
Update::Update(json j)
{
    OMIT(
        if (j.at("ok").get<bool>())
            j = j["result"];
        else
            throw std::invalid_argument("\"result\" is not ok!");
    )

    update_id = j.at("update_id").get<int>();

    OMIT(
        message = new Message(j.at("message").get<json>());
        return;
    )

    OMIT(
        edited_message = new Message(j.at("edited_message").get<json>());
        return;
    )

    OMIT(
        channel_post = new Message(j.at("channel_post").get<json>());
        return;
    )

    OMIT(
        edited_channel_post = new Message(j.at("edited_channel_post").get<json>());
        return;
    )

    OMIT(
        inline_query = new InlineQuery(j.at("inline_query").get<json>());
        return;
    )

    OMIT(
        chosen_inline_result = new ChosenInlineResult(j.at("chosen_inline_result").get<json>());
        return;
    )

    OMIT(
        callback_query = new CallbackQuery(j.at("callback_query").get<json>());
        return;
    )

    OMIT(
        shipping_query = new ShippingQuery(j.at("shipping_query").get<json>());
        return;
    )

    OMIT(
        pre_checkout_query = new PreCheckoutQuery(j.at("pre_checkout_query").get<json>());
        return;
    )
}

Message Update::get_message() 
{
    if (message == nullptr)
        throw std::invalid_argument("Update::get_message() - message is empty!");

    return *message;
}

Message Update::get_edited_message() 
{
    if (edited_message == nullptr)
        throw std::invalid_argument("Update::get_edited_message() - edited_message is empty!");

    return *edited_message;
}

Message Update::get_channel_post() 
{
    if (channel_post == nullptr)
        throw std::invalid_argument("Update::get_channel_post() - channel_post is empty!");

    return *channel_post;
}

Message Update::get_edited_channel_post() 
{
    if (edited_channel_post == nullptr)
        throw std::invalid_argument("Update::get_edited_channel_post() - edited_channel_post is empty!");

    return *edited_channel_post;
}

InlineQuery Update::get_inline_query() 
{
    if (inline_query == nullptr)
        throw std::invalid_argument("Update::get_inline_query() - inline_query is empty!");

    return *inline_query;
}

ChosenInlineResult Update::get_chosen_inline_result() 
{
    if (chosen_inline_result == nullptr)
        throw std::invalid_argument("Update::get_chosen_inline_result() - chosen_inline_result is empty!");

    return *chosen_inline_result;
}

CallbackQuery Update::get_callback_query() 
{
    if (callback_query == nullptr)
        throw std::invalid_argument("Update::get_callback_query() - callback_query is empty!");

    return *callback_query;
}

ShippingQuery Update::get_shipping_query()
{
    if (shipping_query == nullptr)
        throw std::invalid_argument("Update::get_shipping_query() - shipping_query is empty!");

    return *shipping_query;
}

PreCheckoutQuery Update::get_pre_checkout_query()
{
    if (pre_checkout_query == nullptr)
        throw std::invalid_argument("Update::get_pre_checkout_query() - pre_checkout_query is empty!");
        
    return *pre_checkout_query;
}

// TODO: REMAKE WITH variant
Update::~Update()
{
    // Make OK destructor bcz of MEMORY LEAKS
    return;
    // CODE BELOW NEVER EXECUTES!!!!!!!!!!!!

    if (message != nullptr) {
        delete message;
        return;
    }
    if (edited_message != nullptr) {
        delete edited_message;
        return;
    };
    if (channel_post != nullptr) {
        delete channel_post;
        return;
    }
    if (edited_channel_post != nullptr) {
        delete edited_channel_post;
        return;
    }
    if (inline_query != nullptr) {
        delete inline_query;
        return;
    }
    if (chosen_inline_result != nullptr) {
        delete chosen_inline_result;
        return;
    }
    if (callback_query != nullptr) {
        delete callback_query;
        return;
    }
    if (shipping_query != nullptr) {
        delete shipping_query;
        return;
    }
    if (pre_checkout_query != nullptr) {
        delete pre_checkout_query;
        return;
    }
}