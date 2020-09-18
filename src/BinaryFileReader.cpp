#include "BinaryFileReader.h"
#include "ReadError.h"
#include "SeekError.h"

using namespace std;

template<picky::Endian DefaultByteOrder>
void picky::BinaryFileReader<DefaultByteOrder>::Seek(long offset) {
  if (fseek(file_, offset, SEEK_SET) != 0) {
    throw picky::SeekError(offset);
  }
  offset_ = offset;
}

template<picky::Endian DefaultByteOrder>
void picky::BinaryFileReader<DefaultByteOrder>::Read(int8_t& data) {
  if (fread(&data, 1, 1, file_) != 1) {
    throw picky::ReadError(offset_, 1);
  }
  ++offset_;
}

template<picky::Endian DefaultByteOrder>
void picky::BinaryFileReader<DefaultByteOrder>::Read(int16_t& data, Endian byte_order) {
  constexpr auto size = 2;
  if (fread(&data, 1, size, file_) != size) {
    throw picky::ReadError(offset_, size);
  }
  if (DefaultByteOrder != HostByteOrder) {
    data = SwapByteOrder(data);
  }
  offset_ += size;
}

template<picky::Endian DefaultByteOrder>
void picky::BinaryFileReader<DefaultByteOrder>::Read(int32_t& data, Endian byte_order) {
  constexpr auto size = 4;
  if (fread(&data, 1, size, file_) != size) {
    throw picky::ReadError(offset_, size);
  }
  if (DefaultByteOrder != HostByteOrder) {
    data = SwapByteOrder(data);
  }
  offset_ += size;
}

template<picky::Endian DefaultByteOrder>
void picky::BinaryFileReader<DefaultByteOrder>::Read(int64_t& data, Endian byte_order) {
  constexpr auto size = 8;
  if (fread(&data, 1, size, file_) != size) {
    throw picky::ReadError(offset_, size);
  }
  if (DefaultByteOrder != HostByteOrder) {
    data = SwapByteOrder(data);
  }
  offset_ += size;
}

template<picky::Endian DefaultByteOrder>
void picky::BinaryFileReader<DefaultByteOrder>::Read(uint8_t& data, Endian byte_order) {
  if (fread(&data, 1, 1, file_) != 1) {
    throw picky::ReadError(offset_, 1);
  }
  ++offset_;
}

template<picky::Endian DefaultByteOrder>
void picky::BinaryFileReader<DefaultByteOrder>::Read(uint16_t& data, Endian byte_order) {
  constexpr auto size = 2;
  if (fread(&data, 1, size, file_) != size) {
    throw picky::ReadError(offset_, size);
  }
  if (DefaultByteOrder != HostByteOrder) {
    data = SwapByteOrder(data);
  }
  offset_ += size;
}

template<picky::Endian DefaultByteOrder>
void picky::BinaryFileReader<DefaultByteOrder>::Read(uint32_t& data, Endian byte_order) {
  constexpr auto size = 4;
  if (fread(&data, 1, size, file_) != size) {
    throw picky::ReadError(offset_, size);
  }
  if (DefaultByteOrder != HostByteOrder) {
    data = SwapByteOrder(data);
  }
  offset_ += size;
}

template<picky::Endian DefaultByteOrder>
void picky::BinaryFileReader<DefaultByteOrder>::Read(uint64_t& data, Endian byte_order) {
  constexpr auto size = 8;
  if (fread(&data, 1, size, file_) != size) {
    throw picky::ReadError(offset_, size);
  }
  if (DefaultByteOrder != HostByteOrder) {
    data = SwapByteOrder(data);
  }
  offset_ += size;
}

template class picky::BinaryFileReader<picky::Endian::LITTLE>;
template class picky::BinaryFileReader<picky::Endian::BIG>;