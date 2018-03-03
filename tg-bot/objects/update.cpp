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
            throw TelegramBadRequestException("Update::Update(json): \"result\" is not ok!");
    )

    update_id = j.at("update_id").get<int>();

    OMIT(
#ifdef _TGBOT_OPT_UPDATE_ANY
        upd = std::make_any<Message>(j.at("message").get<json>());
        upd_type = UpdateType::MESSAGE;
#elif _TGBOT_OPT_UPDATE_UNIQ_PTR
        message = std::make_unique<Message>(j.at("message").get<json>());
#endif
        return;
    )

    OMIT(
#ifdef _TGBOT_OPT_UPDATE_ANY
        upd = std::make_any<Message>(j.at("edited_message").get<json>());
        upd_type = UpdateType::EDITED_MESSAGE;
#elif _TGBOT_OPT_UPDATE_UNIQ_PTR
        edited_message = std::make_unique<Message>(j.at("edited_message").get<json>());
#endif
        return;
    )

    OMIT(
#ifdef _TGBOT_OPT_UPDATE_ANY
        upd = std::make_any<Message>(j.at("channel_post").get<json>());
        upd_type = UpdateType::CHANNEL_POST;
#elif _TGBOT_OPT_UPDATE_UNIQ_PTR
        channel_post = std::make_unique<Message>(j.at("channel_post").get<json>());
#endif
        return;
    )

    OMIT(
#ifdef _TGBOT_OPT_UPDATE_ANY
        upd = std::make_any<Message>(j.at("edited_channel_post").get<json>());
        upd_type = UpdateType::EDITED_CHANNEL_POST;
#elif _TGBOT_OPT_UPDATE_UNIQ_PTR
        edited_channel_post = std::make_unique<Message>(j.at("edited_channel_post").get<json>());
#endif
        return;
    )

    OMIT(
#ifdef _TGBOT_OPT_UPDATE_ANY
        upd = std::make_any<InlineQuery>(j.at("inline_query").get<json>());
        upd_type = UpdateType::INLINE_QUERY;
#elif _TGBOT_OPT_UPDATE_UNIQ_PTR
        inline_query = std::make_unique<InlineQuery>(j.at("inline_query").get<json>());
#endif
        return;
    )

    OMIT(
#ifdef _TGBOT_OPT_UPDATE_ANY
        upd = std::make_any<ChosenInlineResult>(j.at("chosen_inline_result").get<json>());
        upd_type = UpdateType::CHOSEN_INLINE_RESULT;
#elif _TGBOT_OPT_UPDATE_UNIQ_PTR
        chosen_inline_result = std::make_unique<ChosenInlineResult>(j.at("chosen_inline_result").get<json>());
#endif
        return;
    )

    OMIT(
#ifdef _TGBOT_OPT_UPDATE_ANY
        upd = std::make_any<CallbackQuery>(j.at("callback_query").get<json>());
        upd_type = UpdateType::CALLBACK_QUERY;
#elif _TGBOT_OPT_UPDATE_UNIQ_PTR
        callback_query = std::make_unique<CallbackQuery>(j.at("callback_query").get<json>());
#endif
        return;
    )

    OMIT(
#ifdef _TGBOT_OPT_UPDATE_ANY
        upd = std::make_any<ShippingQuery>(j.at("shipping_query").get<json>());
        upd_type = UpdateType::SHIPPING_QUERY;
#elif _TGBOT_OPT_UPDATE_UNIQ_PTR
        shipping_query = std::make_unique<ShippingQuery>(j.at("shipping_query").get<json>());
#endif
        return;
    )

    OMIT(
#ifdef _TGBOT_OPT_UPDATE_ANY
        upd = std::make_any<PreCheckoutQuery>(j.at("pre_checkout_query").get<json>());
        upd_type = UpdateType::PRE_CHECKOUT_QUERY;
#elif _TGBOT_OPT_UPDATE_UNIQ_PTR
        pre_checkout_query = std::make_unique<PreCheckoutQuery>(j.at("pre_checkout_query").get<json>());
#endif
        return;
    )
}

Message Update::get_message() 
{
#if _TGBOT_OPT_UPDATE_ANY
    try
    {
        return std::any_cast<Message>(upd);
    }
    catch (const std::bad_any_cast &e)
    {
        std::cout << "Update::get_message(): " << e.what() << std::endl;
    }
#elif _TGBOT_OPT_UPDATE_UNIQ_PTR
    if (!message)
        throw TelegramNullObjectException("Update::get_message() - message is empty!");
    return *message;
#endif
}

Message Update::get_edited_message() 
{
#if _TGBOT_OPT_UPDATE_ANY
    return get_message();
#elif _TGBOT_OPT_UPDATE_UNIQ_PTR
    if (!edited_message)
        throw TelegramNullObjectException("Update::get_edited_message() - edited_message is empty!");
    return *edited_message;
#endif
}

Message Update::get_channel_post() 
{
#ifdef _TGBOT_OPT_UPDATE_ANY
    return get_message();
#elif _TGBOT_OPT_UPDATE_UNIQ_PTR
    if (!channel_post)
        throw TelegramNullObjectException("Update::get_channel_post() - channel_post is empty!");
    return *channel_post;
#endif
}

Message Update::get_edited_channel_post() 
{
#if _TGBOT_OPT_UPDATE_ANY
    return get_message();    
#elif _TGBOT_OPT_UPDATE_UNIQ_PTR
    if (!edited_channel_post)
        throw TelegramNullObjectException("Update::get_edited_channel_post() - edited_channel_post is empty!");
    return *edited_channel_post;
#endif
}

InlineQuery Update::get_inline_query() 
{
#ifdef _TGBOT_OPT_UPDATE_ANY
    try
    {
        return std::any_cast<InlineQuery>(upd);
    }
    catch (const std::bad_any_cast &e)
    {
        std::cout << "Update::get_inline_query(): " << e.what() << std::endl;
    }
#elif _TGBOT_OPT_UPDATE_UNIQ_PTR
    if (!inline_query)
        throw TelegramNullObjectException("Update::get_inline_query() - inline_query is empty!");
    return *inline_query;
#endif
}

ChosenInlineResult Update::get_chosen_inline_result() 
{
#ifdef _TGBOT_OPT_UPDATE_ANY
    try
    {
        return std::any_cast<ChosenInlineResult>(upd);
    }
    catch (const std::bad_any_cast &e)
    {
        std::cout << "Update::get_chosen_inline_result(): " << e.what() << std::endl;
    }
#elif _TGBOT_OPT_UPDATE_UNIQ_PTR
    if (!chosen_inline_result)
        throw TelegramNullObjectException("Update::get_chosen_inline_result() - chosen_inline_result is empty!");
    return *chosen_inline_result;
#endif
}

CallbackQuery Update::get_callback_query() 
{
#ifdef _TGBOT_OPT_UPDATE_ANY
    try
    {
        return std::any_cast<CallbackQuery>(upd);
    }
    catch (const std::bad_any_cast &e)
    {
        std::cout << "Update::get_callback_query(): " << e.what() << std::endl;
    }
#elif _TGBOT_OPT_UPDATE_UNIQ_PTR
    if (!callback_query)
        throw TelegramNullObjectException("Update::get_callback_query() - callback_query is empty!");
    return *callback_query;
#endif
}

ShippingQuery Update::get_shipping_query()
{
#ifdef _TGBOT_OPT_UPDATE_ANY
    try
    {
        return std::any_cast<ShippingQuery>(upd);
    }
    catch (const std::bad_any_cast &e)
    {
        std::cout << "Update::get_shipping_query(): " << e.what() << std::endl;
    }
#elif _TGBOT_OPT_UPDATE_UNIQ_PTR
    if (!shipping_query)
        throw TelegramNullObjectException("Update::get_shipping_query() - shipping_query is empty!");
    return *shipping_query;
#endif
}

PreCheckoutQuery Update::get_pre_checkout_query()
{
#ifdef _TGBOT_OPT_UPDATE_ANY
    try
    {
        return std::any_cast<PreCheckoutQuery>(upd);
    }
    catch (const std::bad_any_cast &e)
    {
        std::cout << "Update::get_pre_checkout_query(): " << e.what() << std::endl;
    }
#elif _TGBOT_OPT_UPDATE_UNIQ_PTR
    if (!pre_checkout_query)
        throw TelegramNullObjectException("Update::get_pre_checkout_query() - pre_checkout_query is empty!");   
    return *pre_checkout_query;
#endif
}

Update::~Update()
{

}