#include <iostream>
#include "Serializer.h"

int main() {
	Serializer s(PACKET_SIZE);
	std::string k = "abc";
	std::string b;
	s.Serialize(k);
	s.DeSerialize(&b);

	std::cout << b << std::endl;

	return 0;
}