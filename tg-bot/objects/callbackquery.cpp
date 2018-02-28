#include "callbackquery.hpp"

CallbackQuery::CallbackQuery(string jstr) : CallbackQuery::CallbackQuery(json::parse(jstr))
{
}

CallbackQuery::CallbackQuery(json j)
{
    std::cout << "TODO: CallbackQuery::CallbackQuery(json). JSON: " << j.dump(2) << std::endl;
}