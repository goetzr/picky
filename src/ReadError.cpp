#include "ReadError.h"

#include "fmt/core.h"

using namespace std;

picky::ReadError::ReadError(long offset, int num_bytes)
  : runtime_error{ BuildErrorMessage(offset, num_bytes) } {}

string picky::ReadError::BuildErrorMessage(long offset, int num_bytes) {
  return fmt::format("Failed to read {} bytes at offset {#08x}.", num_bytes, offset);
}