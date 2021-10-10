#include "include/dict.hh"

std::string Atbash::encode(std::string val)
{
    std::string encoded(cache.find(val));
    if (encoded.empty())
    {
        encoded.clear();
        encoded.resize(val.size());
    }
    else
    {
        return encoded;
    }

    for (auto i : val)
    {
        if (i >= 'a' && i <= 'z')
        {
            encoded += (char)(abs(i - 'a' - 25) + 'a');
        }
        else if (i >= 'A' && i <= 'Z')
        {
            encoded += (char)(abs(i - 'A' - 25) + 'A');
        }
        else
        {
            encoded += i;
        }
    }
    this->cache.add_cache(val, encoded);
    return encoded;
}

std::string Atbash::decode(std::string val)
{
    return this->encode(val);
}