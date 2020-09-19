#include "BinaryFileReader.h"
#include "ReadError.h"
#include "SeekError.h"

using namespace std;

template<picky::Endian DefaultByteOrder>
picky::BinaryFileReader<DefaultByteOrder>::BinaryFileReader(std::FILE* file) :
		file_{ file },
		size_{ 0L },
		offset_{ 0L } {
			auto seek1 = fseek(file, 0, SEEK_END);
			size_ = ftell(file);
			auto seek2 = fseek(file, 0, SEEK_SET);
			if (seek1 != 0 || seek2 != 0) {
				throw SeekError("Failed to seek the file to determine its size.");
			}
		}

template<picky::Endian DefaultByteOrder>
void picky::BinaryFileReader<DefaultByteOrder>::Seek(long offset) {
  if (offset >= size_ || fseek(file_, offset, SEEK_SET) != 0) {
    throw picky::SeekError(offset);
  }
  offset_ = offset;
}

template<picky::Endian DefaultByteOrder>
void picky::BinaryFileReader<DefaultByteOrder>::Read(int8_t& data) {
  auto const size = 1;
  if (fread(&data, 1, size, file_) != size) {
    throw picky::ReadError(offset_, size);
  }
  ++offset_;
}

template<picky::Endian DefaultByteOrder>
void picky::BinaryFileReader<DefaultByteOrder>::Read(int16_t& data, Endian byte_order) {
  auto const size = 2;
  if (fread(&data, 1, size, file_) != size) {
    throw picky::ReadError(offset_, size);
  }
  if (byte_order != HostByteOrder) {
    data = SwapByteOrder(data);
  }
  offset_ += size;
}

template<picky::Endian DefaultByteOrder>
void picky::BinaryFileReader<DefaultByteOrder>::Read(int32_t& data, Endian byte_order) {
  auto const size = 4;
  if (fread(&data, 1, size, file_) != size) {
    throw picky::ReadError(offset_, size);
  }
  if (byte_order != HostByteOrder) {
    data = SwapByteOrder(data);
  }
  offset_ += size;
}

template<picky::Endian DefaultByteOrder>
void picky::BinaryFileReader<DefaultByteOrder>::Read(int64_t& data, Endian byte_order) {
  auto const size = 8;
  if (fread(&data, 1, size, file_) != size) {
    throw picky::ReadError(offset_, size);
  }
  if (byte_order != HostByteOrder) {
    data = SwapByteOrder(data);
  }
  offset_ += size;
}

template<picky::Endian DefaultByteOrder>
void picky::BinaryFileReader<DefaultByteOrder>::Read(uint8_t& data, Endian byte_order) {
  auto const size = 1;
  if (fread(&data, 1, size, file_) != size) {
    throw picky::ReadError(offset_, size);
  }
  ++offset_;
}

template<picky::Endian DefaultByteOrder>
void picky::BinaryFileReader<DefaultByteOrder>::Read(uint16_t& data, Endian byte_order) {
  auto const size = 2;
  if (fread(&data, 1, size, file_) != size) {
    throw picky::ReadError(offset_, size);
  }
  if (byte_order != HostByteOrder) {
    data = SwapByteOrder(data);
  }
  offset_ += size;
}

template<picky::Endian DefaultByteOrder>
void picky::BinaryFileReader<DefaultByteOrder>::Read(uint32_t& data, Endian byte_order) {
  auto const size = 4;
  if (fread(&data, 1, size, file_) != size) {
    throw picky::ReadError(offset_, size);
  }
  if (byte_order != HostByteOrder) {
    data = SwapByteOrder(data);
  }
  offset_ += size;
}

template<picky::Endian DefaultByteOrder>
void picky::BinaryFileReader<DefaultByteOrder>::Read(uint64_t& data, Endian byte_order) {
  auto const size = 8;
  if (fread(&data, 1, size, file_) != size) {
    throw picky::ReadError(offset_, size);
  }
  if (byte_order != HostByteOrder) {
    data = SwapByteOrder(data);
  }
  offset_ += size;
}

template class picky::BinaryFileReader<picky::Endian::LITTLE>;
template class picky::BinaryFileReader<picky::Endian::BIG>;