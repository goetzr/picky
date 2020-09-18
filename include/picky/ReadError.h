#pragma once

#include <stdexcept>
#include <string>

namespace picky {
  class ReadError : public std::runtime_error {
   public:
    ReadError(long offset, int num_bytes);

   private:
    static std::string BuildErrorMessage(long offset, int num_bytes);
  }
}