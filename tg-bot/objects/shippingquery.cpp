#include "shippingquery.hpp"


ShippingQuery::ShippingQuery(string jstr) : ShippingQuery::ShippingQuery(json::parse(jstr))
{
}

ShippingQuery::ShippingQuery(json j)
{
    std::cout << "TODO: ShippingQuery::ShippingQuery(json). JSON: " << j.dump(2) << std::endl;
}