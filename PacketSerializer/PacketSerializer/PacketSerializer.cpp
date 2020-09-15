#include <iostream>
#include "Packet.h"
using namespace Serialize;
int main() {
	Packet pk(1500, PACKET_ID::NONE, 0, IO_DIR::SERV_TO_CLI);
	std::vector<int> v;
	for (int i = 0; i < 10; i++) {
		v.push_back(i);
	}
	pk << v;
	PacketHeader pkHeader;
	std::vector<int> c;
	pk >> &pkHeader.pkID;
	std::cout << (int)pkHeader.pkID << std::endl;
	pk >> &pkHeader.sessionIdx;
	pk >> &pkHeader.ioDir;
	pk >> &c;
	for (int i = 0; i < c.size(); i++) {
		std::cout << c[i] << std::endl;
	}
	return 0;
}