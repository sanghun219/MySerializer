#include "Packet.h"
using namespace Serialize;
Serializer& Serialize::operator<<(Serializer& left, const PACKET_ID& pkID)
{
	left << static_cast<UINT32>(pkID);
	return left;
	// TODO: 여기에 return 문을 삽입합니다.
}

Serializer& Serialize::operator<<(Serializer& left, const IO_DIR& ioDir)
{
	left << static_cast<UINT32>(ioDir);
	return left;
	// TODO: 여기에 return 문을 삽입합니다.
}

Serializer& Serialize::operator>>(Serializer& left, PACKET_ID* pkID)
{
	UINT32 tempID = 0;
	left >> &tempID;
	*pkID = static_cast<PACKET_ID>(tempID);
	return left;
	// TODO: 여기에 return 문을 삽입합니다.
}

Serializer& Serialize::operator>>(Serializer& left, IO_DIR* ioDir)
{
	UINT32 tempID = 0;
	left >> &tempID;
	*ioDir = static_cast<IO_DIR>(tempID);
	return left;
	// TODO: 여기에 return 문을 삽입합니다.
}

Packet::Packet(const UCHAR* pData, const PACKET_ID& pkID,
	const UINT32& sessionIdx, const IO_DIR& ioDir) : Serializer(*pData) {
	m_PKheader.pkID = pkID;
	m_PKheader.sessionIdx = sessionIdx;
	m_PKheader.ioDir = ioDir;
	*this << pkID;
	*this << sessionIdx;
	*this << ioDir;
}

Packet::Packet(const UINT32& size, const PACKET_ID& pkID,
	const UINT32& sessionIdx, const IO_DIR& ioDir) : Serializer(size) {
	m_PKheader.pkID = pkID;
	m_PKheader.sessionIdx = sessionIdx;
	m_PKheader.ioDir = ioDir;
	*this << pkID;
	*this << sessionIdx;
	*this << ioDir;
}