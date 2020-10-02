#pragma once

#include <stdexcept>
#include <string>

namespace picky {
  class SeekFileError : public std::runtime_error {
   public:
    SeekFileError(std::string const& msg);
    SeekFileError(long offset);

   private:
    static std::string BuildErrorMessage(long offset);
  };

  inline SeekFileError::SeekFileError(std::string const& msg)
    : std::runtime_error(msg) {}

  inline SeekFileError::SeekFileError(long offset)
    : std::runtime_error{ BuildErrorMessage(offset) } {}
}