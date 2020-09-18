#pragma once

#include "picky_export.h"
#include "endian.h"

#include <cstdint>
#include <cstdio>
#include <string>

namespace picky {

class PICKY_EXPORT BinaryFileReader {
 private:
	std::FILE* file_;
	Endian default_byte_order_;
 public:
  BinaryFileReader(std::FILE* file, Endian default_byte_order) :
		file_{ file },
		default_byte_order_{ default_byte_order } {}

	void Seek(long offset);

	void Read(std::int8_t  & data);
	void Read(std::int16_t & data) { Read(data, default_byte_order_); }
	void Read(std::int32_t & data) { Read(data, default_byte_order_); }
	void Read(std::int64_t & data) { Read(data, default_byte_order_); }
	void Read(std::uint8_t & data) { Read(data, default_byte_order_); }
	void Read(std::uint16_t& data) { Read(data, default_byte_order_); }
	void Read(std::uint32_t& data) { Read(data, default_byte_order_); }
	void Read(std::uint64_t& data) { Read(data, default_byte_order_); }

	void Read(std::int16_t & data, Endian byte_order);
	void Read(std::int32_t & data, Endian byte_order);
	void Read(std::int64_t & data, Endian byte_order);
	void Read(std::uint8_t & data, Endian byte_order);
	void Read(std::uint16_t& data, Endian byte_order);
	void Read(std::uint32_t& data, Endian byte_order);
	void Read(std::uint64_t& data, Endian byte_order);

	void Read(std::string& data, int len);
};

}