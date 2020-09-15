#pragma once
#include "Define.h"
#include <assert.h>

// TODO : NameSpace�� �ۼ��� ������ ����ü�� Ŭ������ �����ϴ� ��� �ش� Ŭ�������� namespace �Լ� �ۼ��� ���ϱ� ����
// ���� ���� �⺻���� �����ڷ��� + STL�� ���� �����͸��� ����ȭ�Ѵ�.
namespace Serialize {
	class Serializer
	{
	public:
		// �⺻�����δ� ���� ����� �������־�� ��
		Serializer(const UINT32& buffSize_);
		// ���� ��ü�� �����Ϸ��� ��
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
		// string , vector .. �� �ʿ��� STL���� �˾Ƽ� ����ֱ�
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
		// operator ����� ���ΰ�?
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
		// ���۰� ����á�� �� false ��ȯ ( ��쿡 ���� ���� ũ�⸦ 2����ϰ� �����ϴ� ����ᵵ ��)
		BOOL CheckWriteBoundary(UINT32 offsetSize_);
		BOOL CheckReadBoundary(UINT32 offsetSize_);
		// �޸� ���� ���� ���� .. ��ũ�ΰ� �� �������� ������ Effective c++ ������� �ǵ��� �Ⱦ������
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
