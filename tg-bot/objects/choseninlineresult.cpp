#include "choseninlineresult.hpp"


ChosenInlineResult::ChosenInlineResult(string jstr) 
        : ChosenInlineResult::ChosenInlineResult(json::parse(jstr))
{
}

ChosenInlineResult::ChosenInlineResult(json j)
{
    std::cout << "TODO: ChosenInlineResult::ChosenInlineResult(json). JSON: " 
              << j.dump(2) << std::endl;
}