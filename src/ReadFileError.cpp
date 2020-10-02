#include "ReadFileError.h"

#include "fmt/core.h"

using namespace picky;
using namespace std;

string ReadFileError::BuildErrorMessage(long offset, int num_bytes) {
  return fmt::format("Failed to read {} bytes at offset {#08x}.", num_bytes, offset);
}