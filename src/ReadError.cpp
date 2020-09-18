#include "ReadError.h"

#include "fmt/core.h"

using namespace std;

string picky::ReadError::BuildErrorMessage(long offset, int num_bytes) {
  // TODO: Fix formatting.
  return fmt::format("Failed to read %d bytes at offset 0x%08x.")
}

picky::ReadError::ReadError(long offset, int num_bytes)
  : runtime_error() {

}