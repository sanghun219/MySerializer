#include "Serializer.h"
Serializer::Serializer(const UINT32& buffSize_)
{
	m_Size = buffSize_;
	m_Buffer = new UCHAR[m_Size];
}

BOOL Serializer::CheckWriteBoundary(UINT32 offsetSize_)
{
	if (m_WritePtr + offsetSize_ >= m_Size) {
		return FALSE;
	}
	return TRUE;
}

BOOL Serializer::CheckReadBoundary(UINT32 offsetSize_)
{
	if (m_ReadPtr + offsetSize_ >= m_Size) {
		return FALSE;
	}
	return TRUE;
}

void Serializer::Serialize(const std::string& in)
{
	int size = in.size();
	CommonWriteMemory(size);

	for (int i = 0; i < size; i++) {
		CommonWriteMemory(in[i]);
	}
}

void Serializer::DeSerialize(std::string* out)
{
	int size = 0;
	CommonReadMemory(&size);

	char* pTemp = new char[size + 1];
	for (int i = 0; i < size; i++) {
		CommonReadMemory(&pTemp[i]);
	}
	pTemp[size] = '\0';
	*out = pTemp;
	pTemp = nullptr;
}