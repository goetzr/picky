#include "BinaryFileReader.h"

using namespace std;

picky::BinaryFileReader::BinaryFileReader(char const * path) {
  
}

void picky::BinaryFileReader::Read(int8_t& data) {
  if (fread(&data, 1, 1, file_) != 1) {

  }
}

void picky::BinaryFileReader::Read(int16_t& data, Endian byte_order);
void picky::BinaryFileReader::Read(int32_t& data, Endian byte_order);
void picky::BinaryFileReader::Read(int64_t& data, Endian byte_order);
void picky::BinaryFileReader::Read(uint8_t& data, Endian byte_order);
void picky::BinaryFileReader::Read(uint16_t& data, Endian byte_order);
void picky::BinaryFileReader::Read(uint32_t& data, Endian byte_order);
void picky::BinaryFileReader::Read(uint64_t& data, Endian byte_order);