#pragma once
#include "Define.h"
#include <assert.h>
class Serializer
{
public:
	Serializer(const UINT32& buffSize_);
	void Serialize(const std::string& in);
	void DeSerialize(std::string* out);
private:
	BOOL CheckWriteBoundary(UINT32 offsetSize_);
	BOOL CheckReadBoundary(UINT32 offsetSize_);
	template <typename T>
	void CommonWriteMemory(const T& data);
	template <typename T>
	void CommonReadMemory(T* pData);
private:
	UINT32 m_Size = 0;
	UINT32 m_ReadPtr = 0;
	UINT32 m_WritePtr = 0;
	UCHAR* m_Buffer = nullptr;
};

template<typename T>
inline void Serializer::CommonWriteMemory(const T& data)
{
	int dataSize = sizeof(T);
	if (CheckWriteBoundary(dataSize)) {
		memcpy_s((void* const)(m_Buffer + m_WritePtr), sizeof(m_Buffer), (const void*)(&data),
			dataSize);
		m_WritePtr += dataSize;
	}
	else {
		assert(FALSE);
	}
}

template<typename T>
inline void Serializer::CommonReadMemory(T* pData)
{
	int dataSize = sizeof(T);
	if (CheckReadBoundary(dataSize)) {
		memcpy_s((void* const)(pData), dataSize, (const void* const)(m_Buffer + m_ReadPtr), dataSize);
		m_ReadPtr += dataSize;
	}
	else {
		assert(FALSE);
	}
}
