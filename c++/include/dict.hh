#ifndef DICT_HEADER
#define DICT_HEADER
#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <filesystem>
	class Cache
{
public:
	std::unordered_map<std::string, std::string> vals;
	// add a value to the map
	void add_cache(std::string code, std::string encoded);
	//find if a value exists
	std::string find(std::string code);
	//override default operator for <<
	friend std::ostream &operator<<(std::ostream &os, const Cache &ch)
	{
		for (auto i : ch.vals)
		{
			os << "\"" << i.first << "\">\"" << i.second << "\""
			   << "\n";
		}
		return os;
	}
	//persist cache
	void save();
	//load cache
	void load();
};


class Atbash
{
public:
	Cache cache;
	//enocdes a string with atbash
	std::string encode(std::string val);
	//same as encode
	std::string decode(std::string val);
};

#endif