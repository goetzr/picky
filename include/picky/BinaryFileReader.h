#pragma once

#include "picky_export.h"
#include "endian.h"

#include <cstdint>
#include <cstdio>
#include <string>

namespace picky {

template<picky::Endian DefaultByteOrder>
class PICKY_EXPORT BinaryFileReader {
 private:
	std::FILE* file_;
	long offset_;

 public:
  BinaryFileReader(std::FILE* file) :
		file_{ file },
		offset_{ 0L } {}

	void Seek(long offset);

	void Read(std::int8_t  & data);
	void Read(std::int16_t & data) { Read(data, DefaultByteOrder); }
	void Read(std::int32_t & data) { Read(data, DefaultByteOrder); }
	void Read(std::int64_t & data) { Read(data, DefaultByteOrder); }
	void Read(std::uint8_t & data) { Read(data, DefaultByteOrder); }
	void Read(std::uint16_t& data) { Read(data, DefaultByteOrder); }
	void Read(std::uint32_t& data) { Read(data, DefaultByteOrder); }
	void Read(std::uint64_t& data) { Read(data, DefaultByteOrder); }

	void Read(std::int16_t & data, Endian byte_order);
	void Read(std::int32_t & data, Endian byte_order);
	void Read(std::int64_t & data, Endian byte_order);
	void Read(std::uint8_t & data, Endian byte_order);
	void Read(std::uint16_t& data, Endian byte_order);
	void Read(std::uint32_t& data, Endian byte_order);
	void Read(std::uint64_t& data, Endian byte_order);

	//void Read(std::string& data, int len);
};

}