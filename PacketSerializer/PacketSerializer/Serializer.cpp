#include "Serializer.h"
namespace Serialize {
	Serializer::Serializer(const UINT32& buffSize_)
	{
		m_Size = buffSize_;
		m_Buffer = new UCHAR[m_Size];
	}

	void Serializer::Set(UCHAR* buf, const UINT32 size)
	{
		m_Size = size;
		m_Buffer = new UCHAR[size];
		CopyMemory(m_Buffer, buf, size);
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
		WRITE(size);

		for (int i = 0; i < size; i++) {
			WRITE(in[i]);
		}
	}

	void Serializer::DeSerialize(std::string* out)
	{
		int size = 0;
		READ(&size);

		char* pTemp = new char[size + 1];
		for (int i = 0; i < size; i++) {
			READ(&pTemp[i]);
		}
		pTemp[size] = '\0';
		*out = pTemp;
		pTemp = nullptr;
	}

	Serializer& Serializer::operator<<(const UINT8& in)
	{
		WRITE(in);
		return *this;
		// TODO: 여기에 return 문을 삽입합니다.
	}

	Serializer& Serializer::operator<<(const UINT16& in)
	{
		WRITE(in);
		return *this;
	}

	Serializer& Serializer::operator<<(const UINT32& in)
	{
		WRITE(in);
		return *this;
	}

	Serializer& Serializer::operator<<(const UINT64& in)
	{
		WRITE(in);
		return *this;
	}

	Serializer& Serializer::operator<<(const INT8& in)
	{
		WRITE(in);
		return *this;
	}

	Serializer& Serializer::operator<<(const INT16& in)
	{
		WRITE(in);
		return *this;
	}

	Serializer& Serializer::operator<<(const INT32& in)
	{
		WRITE(in);
		return *this;
	}

	Serializer& Serializer::operator<<(const INT64& in)
	{
		WRITE(in);
		return *this;
	}

	Serializer& Serializer::operator<<(const FLOAT& in)
	{
		WRITE(in);
		return *this;
	}

	Serializer& Serializer::operator<<(const DOUBLE& in)
	{
		WRITE(in);
		return *this;
	}

	Serializer& Serializer::operator<<(const bool& in)
	{
		WRITE(in);
		return *this;
	}

	Serializer& Serializer::operator<<(const std::string& in)
	{
		Serialize(in);
		return *this;
	}

	Serializer& Serializer::operator>>(UINT8* out)
	{
		READ(out);
		return *this;
	}

	Serializer& Serializer::operator>>(UINT16* out)
	{
		READ(out);
		return *this;
	}

	Serializer& Serializer::operator>>(UINT32* out)
	{
		READ(out);
		return *this;
	}

	Serializer& Serializer::operator>>(UINT64* out)
	{
		READ(out);
		return *this;
	}

	Serializer& Serializer::operator>>(INT8* out)
	{
		READ(out);
		return *this;
	}

	Serializer& Serializer::operator>>(INT16* out)
	{
		READ(out);
		return *this;
	}

	Serializer& Serializer::operator>>(INT32* out)
	{
		READ(out);
		return *this;
	}

	Serializer& Serializer::operator>>(INT64* out)
	{
		READ(out);
		return *this;
	}

	Serializer& Serializer::operator>>(FLOAT* out)
	{
		READ(out);
		return *this;
	}

	Serializer& Serializer::operator>>(DOUBLE* out)
	{
		READ(out);
		return *this;
	}

	Serializer& Serializer::operator>>(bool* out)
	{
		READ(out);
		return *this;
	}

	Serializer& Serializer::operator>>(std::string* out)
	{
		DeSerialize(out);
		return *this;
	}
}