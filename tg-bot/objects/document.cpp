#include "document.hpp"


Document::Document(string jstr) : Document(json::parse(jstr))
{ }

Document::Document(json j)
{
    std::cout << "Document(json): " << j.dump(2) << std::endl;
}