#include "precheckoutquery.hpp"


PreCheckoutQuery::PreCheckoutQuery(string jstr) 
        : PreCheckoutQuery::PreCheckoutQuery(json::parse(jstr))
{
}


PreCheckoutQuery::PreCheckoutQuery(json j)
{
    std::cout << "TODO: PreCheckoutQuery::PreCheckoutQuery(json). JSON: " << j.dump(2) << std::endl;
}