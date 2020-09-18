#include "SeekError.h"

#include "fmt/core.h"

using namespace std;

picky::SeekError::SeekError(long offset)
  : runtime_error{ BuildErrorMessage(offset) } {}
  
string picky::SeekError::BuildErrorMessage(long offset) {
  return fmt::format("Failed to seek to offset {}.", offset);
}