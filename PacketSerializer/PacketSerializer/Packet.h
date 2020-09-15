#pragma once
#include "Serializer.h"
enum class PACKET_ID {
	NONE,
};
enum class IO_DIR {
	CLI_TO_SERV,
	SERV_TO_CLI,
};

struct PacketHeader {
	PACKET_ID pkID;
	UINT32 sessionIdx;
	IO_DIR ioDir;
};
const UINT16 pckHeaderSize = sizeof(PacketHeader);

class Packet : public Serialize::Serializer
{
public:
	Packet() = default;
	Packet(const UCHAR* pData, const PACKET_ID& pkID, const UINT32& sessionIdx, const IO_DIR& ioDir);
	Packet(const UINT32& size, const PACKET_ID& pkID, const UINT32& sessionIdx, const IO_DIR& ioDir);

private:
	PacketHeader m_PKheader;
};

namespace Serialize {
	Serializer& operator << (Serializer& left, const PACKET_ID& pkID);
	Serializer& operator << (Serializer& left, const IO_DIR& ioDir);
	Serializer& operator >> (Serializer& left, PACKET_ID* pkID);
	Serializer& operator >> (Serializer& left, IO_DIR* ioDir);
}