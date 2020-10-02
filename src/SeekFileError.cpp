#include "SeekFileError.h"

#include "fmt/core.h"

using namespace picky;
using namespace std;

string SeekFileError::BuildErrorMessage(long offset) {
  return fmt::format("Failed to seek to offset {}.", offset);
}