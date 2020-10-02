#include "OpenFileError.h"

#include "fmt/core.h"

using namespace picky;
using namespace std;

string OpenFileError::BuildErrorMessage(string const& file_path) {
  return fmt::format("Failed to open the file at {}.", file_path);
}