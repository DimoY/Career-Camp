#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <filesystem>
#include "include/dict.hh"

int main(int argc, char const *argv[])
{
	Atbash *x = new Atbash;
	if (argc > 1)
	{
		x->cache.load();
		if (std::string(argv[1]) == "encode" && argc > 2)
		{
			std::cout << x->encode(argv[2]) << std::endl;
		}
		else if (std::string(argv[1]) == "decode" && argc > 2)
		{
			std::cout << x->encode(argv[2]) << std::endl;
		}
		else if (std::string(argv[1]) == "--help")
		{
			std::cout << "Usage: atbash [encode/decode] <text to encode/decode>\n\nEncodes a string with the encoding Atbash\n\n encode - encodes a line passed as a command line argument\n decode - decodes text passed as a command line argument\n --help - prints a help message\n cache - prints the cache file\n clear - clears the cache file" << std::endl;
		}
		else if (std::string(argv[1]) == "cache")
		{
			std::cout << "Cache is:\n"
					  << std::endl;
			std::cout << x->cache << std::endl;
		}
		else if (std::string(argv[1]) == "clear")
		{
			x->cache.vals.clear();
			x->cache.save();
			std::cout << "Everything is cleared" << std::endl;
		}
	}

	x->cache.save();
	delete x;
}
