#include "include/dict.hh"

void Cache::add_cache(std::string code, std::string encoded)
{
    this->vals.emplace(code, encoded);
}

std::string Cache::find(std::string code)
{
    auto find_at = this->vals.find(code);
    if (find_at == this->vals.end())
    {
        return "";
    }
    return find_at->second;
}

void Cache::save()
{
    std::ofstream out("cache.atbash");
    out << *this;
    out.close();
}

void Cache::load()
{
    std::ifstream in("cache.atbash");
    if (!in)
    {
        std::fstream file;
        file.open("cache.atbash", std::ios::out);
        file.close();
    }
    namespace fs = std::filesystem;
    fs::path h = "cache.atbash";
    std::size_t length = fs::file_size(h);
    if (length == 0)
    {
        in.close();
        return;
    }
    in.seekg(0, in.beg);

    char *buffer = new char[length];
    in.read(buffer, length);
    bool flag = 0, flag2 = 0;

    std::string added1;
    std::string added2;
    for (std::size_t i = 0; i < length; i++)
    {
        if (buffer[i] == '\"' && added1.empty())
        {
            flag = 1;
            flag2 = 0;
        }
        else if (buffer[i] == '\"' && !added1.empty() && added2.empty() && flag != 0 && flag != 0)
        {
            flag = 0;
            flag2 = 0;
        }
        else if (buffer[i] == '\"' && !added1.empty() && !added2.empty())
        {
            flag = 0;
            flag2 = 0;
        }
        else if (buffer[i] == '\"' && !added1.empty() && added2.empty())
        {
            flag = 0;
            flag2 = 1;
        }
        else if (flag == 1 && flag2 == 0)
        {
            added1 += buffer[i];
        }
        else if (flag == 0 && flag2 == 1)
        {
            added2 += buffer[i];
        }
        else if (buffer[i] == '\n')
        {
            //this->vals.insert(added1,added2);
            if (added2[0] == '\000')
            {
                std::size_t sizer = added2.size();
                std::string added;
                for (int i = sizer / 2; i < sizer; i++)
                {
                    added += added2[i];
                }
                this->add_cache(added1, added);
            }
            else
            {
                this->add_cache(added1, added2);
            }

            added1.clear();
            added2.clear();
        }
    }

    in.close();
    delete[] buffer;
}