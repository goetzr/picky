#pragma once

#include <stdexcept>
#include <string>

namespace picky {
  class SeekError : public std::runtime_error {
   public:
    SeekError(long offset);

   private:
    static std::string BuildErrorMessage(long offset);
  };
}