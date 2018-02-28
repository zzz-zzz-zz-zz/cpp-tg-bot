#ifndef __TGBOT_OBJECTS_INCLUDES
#define __TGBOT_OBJECTS_INCLUDES

/**
 * Gathering of 3rd party includes
 **/

#include <stdlib.h>
#include <cstdint>
#include <variant>
#include <sstream>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <map>
#include <list>
#include <optional>
#include <exception>
using std::string;
using json = nlohmann::json;
using map = std::map<string, string>;
using std::list;
using std::optional;
using std::nullopt;
using std::exception;

typedef int_fast32_t i32_t;
typedef uint_fast32_t ui32_t;


#endif // __TGBOT_OBJECTS_INCLUDES