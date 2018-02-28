#include "inlinequery.hpp"

InlineQuery::InlineQuery(string jstr) : InlineQuery::InlineQuery(json::parse(jstr))
{
}

InlineQuery::InlineQuery(json j)
{
    std::cout << "TODO: InlineQuery::InlineQuery(json). JSON: " << j.dump(2) << std::endl;
}