#include "BinaryFileReader.h"
#include "OpenFileError.h"
#include "ReadFileError.h"
#include "SeekFileError.h"
#include "HostByteOrder.h"

using namespace picky;
using namespace std;

template<typename T>
inline int ReadFromFile(FILE* file, T& data, long offset) {
  size_t const size = sizeof(T);
  if (fread(&data, 1, size, file) != size) {
    throw ReadFileError(offset, size);
  }
  return size;
}

FILE* OpenFile(string const& file_path) {
  auto f = fopen(file_path.c_str(), "rb");
  if (f == nullptr) {
    throw OpenFileError(file_path);
  }
  return f;
}

long GetFileSize(FILE* file) {
  auto res1 = fseek(file, 0, SEEK_END);
  auto size = ftell(file);
  auto res2 = fseek(file, 0, SEEK_SET);
  if (res1 != 0 || res2 != 0) {
    throw SeekFileError("Failed to seek the file to determine its size.");
  }
  return size;
}

template<ByteOrder FileByteOrder>
BinaryFileReader<FileByteOrder>::BinaryFileReader(string const& file_path) :
		file_{ OpenFile(file_path) },
		size_{ GetFileSize(file_) },
		offset_{ 0L } {}

template<ByteOrder FileByteOrder>
BinaryFileReader<FileByteOrder>::BinaryFileReader(BinaryFileReader&& rhs) :
  file_ { rhs.file_ },
  size_ { rhs.size_ },
  offset_ { rhs.offset_ } {
    rhs.file_ = nullptr;
    rhs.size_ = 0;
    rhs.offset_ = 0;
  }
  
template<ByteOrder FileByteOrder>
BinaryFileReader<FileByteOrder>& BinaryFileReader<FileByteOrder>::operator=(BinaryFileReader&& rhs) {
  file_ = rhs.file_;
  size_ = rhs.size_;
  offset_ = rhs.offset_;
  rhs.file_ = nullptr;
  rhs.size_ = 0;
  rhs.offset_ = 0;

  return *this;
}

template<ByteOrder FileByteOrder>
void BinaryFileReader<FileByteOrder>::Seek(long offset) const {
  if (offset >= size_ || fseek(file_, offset, SEEK_SET) != 0) {
    throw SeekFileError(offset);
  }
  offset_ = offset;
}

template<ByteOrder FileByteOrder>
void BinaryFileReader<FileByteOrder>::Read(int8_t& data) const {
  offset_ += ReadFromFile(file_, data, offset_);
}

template<ByteOrder FileByteOrder>
void BinaryFileReader<FileByteOrder>::Read(int16_t & data) const {
  offset_ += ReadFromFile(file_, data, offset_);

  if constexpr (FileByteOrder != HostByteOrder)
    data = SwapByteOrder(data);
}

template<ByteOrder FileByteOrder>
void BinaryFileReader<FileByteOrder>::Read(int32_t & data) const {
  offset_ += ReadFromFile(file_, data, offset_);

  if constexpr (FileByteOrder != HostByteOrder)
    data = SwapByteOrder(data);
}

template<ByteOrder FileByteOrder>
void BinaryFileReader<FileByteOrder>::Read(int64_t & data) const {
  offset_ += ReadFromFile(file_, data, offset_);

  if constexpr (FileByteOrder != HostByteOrder)
    data = SwapByteOrder(data);
}

template<ByteOrder FileByteOrder>
void BinaryFileReader<FileByteOrder>::Read(uint8_t& data) const {
  offset_ += ReadFromFile(file_, data, offset_);
}

template<ByteOrder FileByteOrder>
void BinaryFileReader<FileByteOrder>::Read(uint16_t & data) const {
  offset_ += ReadFromFile(file_, data, offset_);

  if constexpr (FileByteOrder != HostByteOrder)
    data = SwapByteOrder(data);
}

template<ByteOrder FileByteOrder>
void BinaryFileReader<FileByteOrder>::Read(uint32_t & data) const {
  offset_ += ReadFromFile(file_, data, offset_);

  if constexpr (FileByteOrder != HostByteOrder)
    data = SwapByteOrder(data);
}

template<ByteOrder FileByteOrder>
void BinaryFileReader<FileByteOrder>::Read(uint64_t & data) const {
  offset_ += ReadFromFile(file_, data, offset_);

  if constexpr (FileByteOrder != HostByteOrder)
    data = SwapByteOrder(data);
}

template<ByteOrder FileByteOrder>
void BinaryFileReader<FileByteOrder>::Read(int16_t& data, ByteOrder byte_order) const {
  offset_ += ReadFromFile(file_, data, offset_);

  if (byte_order != HostByteOrder)
    data = SwapByteOrder(data);
}

template<ByteOrder FileByteOrder>
void BinaryFileReader<FileByteOrder>::Read(int32_t& data, ByteOrder byte_order) const {
  offset_ += ReadFromFile(file_, data, offset_);

  if (byte_order != HostByteOrder)
    data = SwapByteOrder(data);
}

template<ByteOrder FileByteOrder>
void BinaryFileReader<FileByteOrder>::Read(int64_t& data, ByteOrder byte_order) const {
  offset_ += ReadFromFile(file_, data, offset_);

  if (byte_order != HostByteOrder)
    data = SwapByteOrder(data);
}

template<ByteOrder FileByteOrder>
void BinaryFileReader<FileByteOrder>::Read(uint16_t& data, ByteOrder byte_order) const {
  offset_ += ReadFromFile(file_, data, offset_);

  if (byte_order != HostByteOrder)
    data = SwapByteOrder(data);
}

template<ByteOrder FileByteOrder>
void BinaryFileReader<FileByteOrder>::Read(uint32_t& data, ByteOrder byte_order) const {
  offset_ += ReadFromFile(file_, data, offset_);

  if (byte_order != HostByteOrder)
    data = SwapByteOrder(data);
}

template<ByteOrder FileByteOrder>
void BinaryFileReader<FileByteOrder>::Read(uint64_t& data, ByteOrder byte_order) const {
  offset_ += ReadFromFile(file_, data, offset_);

  if (byte_order != HostByteOrder)
    data = SwapByteOrder(data);
}

template<ByteOrder FileByteOrder>
void BinaryFileReader<FileByteOrder>::Read(string& data) const {
  char c;
  while (true) {
    if (fread(&c, 1, 1, file_) != 1) {
      throw ReadFileError(offset_, 1);
    }
    ++offset_;
    if (c == '\0') {
      break;
    }
    data += c;
  }
}

template<ByteOrder FileByteOrder>
void BinaryFileReader<FileByteOrder>::Read(string& data, int len) const {
  data.reserve(len);
  data.assign(len, '\0');
  if (fread(data.data(), 1, len, file_) != len) {
    throw ReadFileError(offset_, len);
  }
  offset_ += len;
}

template class BinaryFileReader<ByteOrder::LITTLE>;
template class BinaryFileReader<ByteOrder::BIG>;