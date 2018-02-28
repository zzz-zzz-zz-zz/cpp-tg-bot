#ifndef __TGBOT_BOT
#define __TGBOT_BOT

#include "objects/_all.hpp"
#include "api.hpp"


class Bot
{
public:
    Bot(string);
    Bot(const char *);
    ~Bot();

    bool has_updates();

    void on_update(i32_t update_filters, void (*callback)(Bot*, Update*));
    void on_update(void (*callback)(Bot*, Update*));
    void start_polling(i32_t poll_interval_ms, i32_t timeout_s);
    void start_polling(i32_t poll_interval_ms);
    void start_polling();

    Api *api;

    enum UpdateFilters {
        NONE                  =   0b000000000,
        MESSAGE               =   0b000000001,
        EDITED_MESSAGE        =   0b000000010,
        CHANNEL_POST          =   0b000000100,
        EDITED_CHANNEL_POST   =   0b000001000,
        INLINE_QUERY          =   0b000010000,
        CHOSEN_INLINE_RESULT  =   0b000100000,
        CALLBACK_QUERY        =   0b001000000,
        SHIPPING_QUERY        =   0b010000000,
        PRE_CHECKOUT_QUERY    =   0b100000000,
        ALL                   =   0b111111111,
    };
private:
    void (*cb_Message)(Bot*, Update*) = nullptr;
    void (*cb_Edited_message)(Bot*, Update*) = nullptr;
    void (*cb_Channel_post)(Bot*, Update*) = nullptr;
    void (*cb_Edited_channel_post)(Bot*, Update*) = nullptr;
    void (*cb_Inline_query)(Bot*, Update*) = nullptr;
    void (*cb_Chosen_inline_result)(Bot*, Update*) = nullptr;
    void (*cb_Callback_query)(Bot*, Update*) = nullptr;
    void (*cb_Shipping_query)(Bot*, Update*) = nullptr;
    void (*cb_Pre_checkout_query)(Bot*, Update*) = nullptr;

    void (*cb_All)(Bot*, Update*) = nullptr;

    i32_t update_flags = UpdateFilters::NONE;
};


#endif // __TGBOT_BOT