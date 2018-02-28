#include "audio.hpp"


Audio::Audio(string jstr) : Audio::Audio(json::parse(jstr))
{
}

Audio::Audio(json j)
{
    std::cout << "TODO: Audio::Audio(json). JSON: " << j.dump(2) << std::endl;
}