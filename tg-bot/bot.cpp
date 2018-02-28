#include "bot.hpp"

#include <unistd.h>


Bot::Bot(string token)
{
    api = new Api(token);
}

Bot::Bot(const char *token)
{
    api = new Api(string(token));
}

Bot::~Bot()
{
    delete api;
}

void Bot::start_polling()
{
    if (!update_flags) {
        throw std::invalid_argument("0 callbacks specified!");
    }
    
    std::cout << "Bot started polling...\n";

    if (update_flags == Api::UpdateFilters::ALL && cb_All != nullptr) {
        while (true)
        {
            list<Update> upds = api->getUpdates();

            for (Update &u : upds)
                cb_All(this, &u);
        }
    } else {
        throw std::invalid_argument("No case for not ALL filters!");          
    }
}

void Bot::start_polling(i32_t timeout_s)
{
    if (!update_flags) {
        throw std::invalid_argument("0 callbacks specified!");
    }
    
    std::cout << "Bot started polling...\n";

    if (update_flags == Api::UpdateFilters::ALL && cb_All != nullptr) {
        while (true)
        {
            list<Update> upds = api->getUpdates(timeout_s);

            for (Update &u : upds)
                cb_All(this, &u);
        }
    } else {
        throw std::invalid_argument("No case for not ALL filters!"); 
    }
}

void Bot::start_polling(i32_t poll_interval_ms, i32_t timeout_s)
{
    if (!update_flags) {
        throw std::invalid_argument("0 callbacks specified!");
    }
    
    std::cout << "Bot started polling each " << poll_interval_ms << " ms...\n";

    if (update_flags == Api::UpdateFilters::ALL && cb_All != nullptr) {
        while (true)
        {
            list<Update> upds = api->getUpdates(timeout_s);

            for (Update &u : upds)
                cb_All(this, &u);

            usleep(poll_interval_ms);
        }
    } else {
        throw std::invalid_argument("No case for not ALL filters!");
    }
}


bool Bot::has_updates()
{
    // return api->getUpdates(false).size() > 0;
    std::cout << "WARNING: Bot.has_updates() always false!!!\n";
    return false;
}

void Bot::on_update(i32_t update_filters, void (*callback)(Bot *b, Update *u))
{
    if (update_filters == Bot::UpdateFilters::ALL) {
        on_update(callback);
        return;
    }

    update_flags |= update_filters;                                          

    if (update_filters & Bot::UpdateFilters::MESSAGE)
        cb_Message = callback;

    if (update_filters & Bot::UpdateFilters::EDITED_MESSAGE)
        cb_Edited_message = callback;

    if (update_filters & Bot::UpdateFilters::CHANNEL_POST)
        cb_Channel_post = callback;

    if (update_filters & Bot::UpdateFilters::EDITED_CHANNEL_POST)
        cb_Edited_channel_post = callback;

    if (update_filters & Bot::UpdateFilters::INLINE_QUERY)
        cb_Inline_query = callback;

    if (update_filters & Bot::UpdateFilters::CHOSEN_INLINE_RESULT)
        cb_Chosen_inline_result = callback;

    if (update_filters & Bot::UpdateFilters::CALLBACK_QUERY)
        cb_Callback_query = callback;

    if (update_filters & Bot::UpdateFilters::SHIPPING_QUERY)
        cb_Shipping_query = callback;

    if (update_filters & Bot::UpdateFilters::PRE_CHECKOUT_QUERY)
        cb_Pre_checkout_query = callback;
}

void Bot::on_update(void (*callback)(Bot *b, Update *u))
{
    update_flags = Api::UpdateFilters::ALL;
    cb_All = callback;
}