#pragma once
#include "Define.h"
#include <assert.h>

// TODO : NameSpace로 작성된 이유는 구조체나 클래스를 적재하는 경우 해당 클래스에서 namespace 함수 작성을 권하기 때문
// 여긴 아주 기본적인 원시자료형 + STL에 대한 데이터만을 직렬화한다.
namespace Serialize {
	class Serializer
	{
	public:
		// 기본적으로는 버퍼 사이즈를 지정해주어야 함
		Serializer(const UINT32& buffSize_);
		// 버퍼 전체를 복사하려할 때
		void Set(UCHAR* buf, const UINT32 size);
		Serializer(const Serializer& copy)
		{
			this->Set(copy.m_Buffer, copy.m_Size);
		}
		void operator =(const Serializer& copy) {
			this->Set(copy.m_Buffer, copy.m_Size);
		}

		UINT32 GetBufferSize()const { return m_Size; }
		UINT32 GetReadDataSize()const { return m_ReadPtr; }
		UINT32 GetWriteDataSize()const { return m_WritePtr; }
		const UCHAR* GetBuffer() { return m_Buffer; }
	public:
		// string , vector .. 더 필요한 STL들은 알아서 집어넣길
		void Serialize(const std::string& in);
		template<typename T>
		void Serialize(const std::vector<T>& in);
		template<typename T>
		void Serialize(const T& in);
		template<typename T>
		void DeSerialize(T* out);
		template<typename T>
		void DeSerialize(std::vector<T>* out);
		void DeSerialize(std::string* out);
	public:
		// operator 사용할 것인가?
		Serializer& operator << (const UINT8& in);
		Serializer& operator << (const UINT16& in);
		Serializer& operator << (const UINT32& in);
		Serializer& operator << (const UINT64& in);
		Serializer& operator << (const INT8& in);
		Serializer& operator << (const INT16& in);
		Serializer& operator << (const INT32& in);
		Serializer& operator << (const INT64& in);
		Serializer& operator << (const FLOAT& in);
		Serializer& operator << (const DOUBLE& in);
		Serializer& operator << (const bool& in);
		template <typename T>
		Serializer& operator << (const std::vector<T>& in);
		Serializer& operator << (const std::string& in);

		Serializer& operator >> (UINT8* out);
		Serializer& operator >> (UINT16* out);
		Serializer& operator >> (UINT32* out);
		Serializer& operator >> (UINT64* out);
		Serializer& operator >> (INT8* out);
		Serializer& operator >> (INT16* out);
		Serializer& operator >> (INT32* out);
		Serializer& operator >> (INT64* out);
		Serializer& operator >> (FLOAT* out);
		Serializer& operator >> (DOUBLE* out);
		Serializer& operator >> (bool* out);
		template <typename T>
		Serializer& operator >> (std::vector<T>* out);
		Serializer& operator >> (std::string* out);
	private:
		// 버퍼가 가득찼을 때 false 반환 ( 경우에 따라서 버퍼 크기를 2배로하고 복사하는 기법써도 됨)
		BOOL CheckWriteBoundary(UINT32 offsetSize_);
		BOOL CheckReadBoundary(UINT32 offsetSize_);
		// 메모리 단일 복사 과정 .. 매크로가 더 편했을듯 하지만 Effective c++ 조언따라 되도록 안쓰기로함
		template <typename T>
		void WRITE(const T& data);
		template <typename T>
		void READ(T* pData);
	private:
		UINT32 m_Size = 0;
		UINT32 m_ReadPtr = 0;
		UINT32 m_WritePtr = 0;
		UCHAR* m_Buffer = nullptr;
	};

	template<typename T>
	inline void Serializer::Serialize(const std::vector<T>& in)
	{
		size_t size = in.size();
		WRITE(size);
		for (int i = 0; i < size; i++) {
			WRITE(in[i]);
		}
	}

	template<typename T>
	inline void Serializer::Serialize(const T& in)
	{
		WRITE(in);
	}

	template<typename T>
	inline void Serializer::DeSerialize(T* out)
	{
		READ(out);
	}

	template<typename T>
	inline void Serializer::DeSerialize(std::vector<T>* out)
	{
		int size = 0;
		READ(&size);

		for (int i = 0; i < size; i++) {
			T data;
			READ(&data);
			out->push_back(data);
		}
	}

	template<typename T>
	inline Serializer& Serializer::operator<<(const std::vector<T>& in)
	{
		Serialize(in);
		return *this;
	}

	template<typename T>
	inline Serializer& Serializer::operator>>(std::vector<T>* out)
	{
		DeSerialize(out);
		return *this;
	}

	template<typename T>
	inline void Serializer::WRITE(const T& data)
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
	inline void Serializer::READ(T* pData)
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
}
