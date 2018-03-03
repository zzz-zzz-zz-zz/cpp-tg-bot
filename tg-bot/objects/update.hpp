#ifndef _TGBOT_OBJECTS_UPDATE
#define _TGBOT_OBJECTS_UPDATE

#include "_all.hpp"

#define _TGBOT_OPT_UPDATE_ANY 1
#define _TGBOT_OPT_UPDATE_UNIQ_PTR 0
#define _TGBOT_OPT_UPDATE_RAW_PTR 0

class Update
{
public:
    Update(string);
    Update(json);

    long int get_update_id() { return update_id; }

    Message get_message();
    Message get_edited_message();
    Message get_channel_post();
    Message get_edited_channel_post();
    InlineQuery get_inline_query();
    ChosenInlineResult get_chosen_inline_result();
    CallbackQuery get_callback_query();
    ShippingQuery get_shipping_query();
    PreCheckoutQuery get_pre_checkout_query();

#if _TGBOT_OPT_UPDATE_ANY
    bool has_message() { return upd_type == UpdateType::MESSAGE; }
    bool has_edited_message() { return upd_type == UpdateType::EDITED_MESSAGE; }
    bool has_channel_post() { return upd_type == UpdateType::CHANNEL_POST; }
    bool has_edited_channel_post() { return upd_type == UpdateType::EDITED_CHANNEL_POST; }
    bool has_inline_query() { return upd_type == UpdateType::INLINE_QUERY; }
    bool has_chosen_inline_result() { return upd_type == UpdateType::CHOSEN_INLINE_RESULT; }
    bool has_callback_query() { return upd_type == UpdateType::CALLBACK_QUERY; }
    bool has_shipping_query() { return upd_type == UpdateType::SHIPPING_QUERY; }
    bool has_pre_checkout_query() { return upd_type == UpdateType::PRE_CHECKOUT_QUERY; }
#elif _TGBOT_OPT_UPDATE_UNIQ_PTR
    bool has_message() { return message != nullptr; }
    bool has_edited_message() { return edited_message != nullptr; }
    bool has_channel_post() { return channel_post != nullptr; }
    bool has_edited_channel_post() { return edited_channel_post != nullptr; }
    bool has_inline_query() { return inline_query != nullptr; }
    bool has_chosen_inline_result() { return chosen_inline_result != nullptr; }
    bool has_callback_query() { return callback_query != nullptr; }
    bool has_shipping_query() { return shipping_query != nullptr; }
    bool has_pre_checkout_query() { return pre_checkout_query != nullptr; }
#endif

    ~Update();
private:
    long int update_id;

#if _TGBOT_OPT_UPDATE_ANY
    enum class UpdateType {
        NONE, MESSAGE, EDITED_MESSAGE, CHANNEL_POST, EDITED_CHANNEL_POST,
        INLINE_QUERY, CHOSEN_INLINE_RESULT, CALLBACK_QUERY,
        SHIPPING_QUERY, PRE_CHECKOUT_QUERY
    } upd_type;

    std::any upd; 
#elif _TGBOT_OPT_UPDATE_UNIQ_PTR
    unique_ptr<Message> message = nullptr;
    unique_ptr<Message> edited_message = nullptr;
    unique_ptr<Message> channel_post = nullptr;
    unique_ptr<Message> edited_channel_post = nullptr;
    unique_ptr<InlineQuery> inline_query = nullptr;
    unique_ptr<ChosenInlineResult> chosen_inline_result = nullptr;
    unique_ptr<CallbackQuery> callback_query = nullptr;
    unique_ptr<ShippingQuery> shipping_query = nullptr;
    unique_ptr<PreCheckoutQuery> pre_checkout_query = nullptr;
#endif

};


#endif