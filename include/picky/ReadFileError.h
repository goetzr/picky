#pragma once

#include <stdexcept>
#include <string>

namespace picky {
  class ReadFileError : public std::runtime_error {
   public:
    ReadFileError(long offset, int num_bytes);

   private:
    static std::string BuildErrorMessage(long offset, int num_bytes);
  };

  inline ReadFileError::ReadFileError(long offset, int num_bytes)
    : std::runtime_error{ BuildErrorMessage(offset, num_bytes) } {}
}