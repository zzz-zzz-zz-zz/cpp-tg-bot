#ifndef _TGBOT_OBJECTS_UPDATE
#define _TGBOT_OBJECTS_UPDATE

#include "_all.hpp"


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

    bool has_message() { return message != nullptr; }
    bool has_edited_message() { return edited_message != nullptr; }
    bool has_channel_post() { return channel_post != nullptr; }
    bool has_edited_channel_post() { return edited_channel_post != nullptr; }
    bool has_inline_query() { return inline_query != nullptr; }
    bool has_chosen_inline_result() { return chosen_inline_result != nullptr; }
    bool has_callback_query() { return callback_query != nullptr; }
    bool has_shipping_query() { return shipping_query != nullptr; }
    bool has_pre_checkout_query() { return pre_checkout_query != nullptr; }

    // TODO: REMAKE WITH variant
    ~Update();
private:
    long int update_id;
    // Notice: ONLY ONE OF THIS WILL BE FILLED.
    // TODO: make in union/std::variant for efficiency
    Message *message = nullptr;
    Message *edited_message = nullptr;
    Message *channel_post = nullptr;
    Message *edited_channel_post = nullptr;
    InlineQuery *inline_query = nullptr;
    ChosenInlineResult *chosen_inline_result = nullptr;
    CallbackQuery *callback_query = nullptr;
    ShippingQuery *shipping_query = nullptr;
    PreCheckoutQuery *pre_checkout_query = nullptr;
};


#endif