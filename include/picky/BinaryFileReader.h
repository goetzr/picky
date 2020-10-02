#pragma once

#include "picky_export.h"
#include "ByteOrder.h"

#include <cstdint>
#include <cstdio>
#include <string>

namespace picky {

template<ByteOrder FileByteOrder>
class PICKY_EXPORT BinaryFileReader {
 private:
	std::FILE* file_;
	mutable long size_;
	mutable long offset_;

 public:
  BinaryFileReader(std::string const& file_path);
	~BinaryFileReader() { fclose(file_); }

	// Disable copy operations.
	BinaryFileReader(BinaryFileReader const&) = delete;
	BinaryFileReader& operator=(BinaryFileReader const&) = delete;

	// Enable move operations.
	BinaryFileReader(BinaryFileReader&& rhs);
	BinaryFileReader& operator=(BinaryFileReader&& rhs);

	long GetSize() const { return size_; }
	long GetOffset() const { return offset_; 
	}
	void Seek(long offset) const;

	// Use FileByteOrder.
	void Read(std::int8_t  & data) const;
	void Read(std::int16_t & data) const;
	void Read(std::int32_t & data) const;
	void Read(std::int64_t & data) const;
	void Read(std::uint8_t & data) const;
	void Read(std::uint16_t& data) const;
	void Read(std::uint32_t& data) const;
	void Read(std::uint64_t& data) const;

	// Use specified byte order.
	void Read(std::int16_t & data, ByteOrder byte_order) const;
	void Read(std::int32_t & data, ByteOrder byte_order) const;
	void Read(std::int64_t & data, ByteOrder byte_order) const;
	void Read(std::uint16_t& data, ByteOrder byte_order) const;
	void Read(std::uint32_t& data, ByteOrder byte_order) const;
	void Read(std::uint64_t& data, ByteOrder byte_order) const;

	void Read(std::string& data) const;
	void Read(std::string& data, int len) const;
};

}