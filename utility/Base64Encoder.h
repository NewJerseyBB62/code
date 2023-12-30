#ifndef _BASE_64_ENCODER_H
#define _BASE_64_ENCODER_H
#include <string>

using namespace std;

class Base64Encoder
{
public:
    Base64Encoder();
    string Encode(unsigned char const* bytes_to_encode, unsigned int in_len);
	string Decode(std::string const& s);
	void Decode(std::string const& s, char* bytes_decoded, int* out_len);
};

#endif
