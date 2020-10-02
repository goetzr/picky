#pragma once

#include <stdexcept>
#include <string>

namespace picky {
  class OpenFileError : public std::runtime_error {
   public:
    OpenFileError(std::string const& file_path);

   private:
    static std::string BuildErrorMessage(std::string const& file_path);
  };

  inline OpenFileError::OpenFileError(std::string const& file_path)
    : std::runtime_error{ BuildErrorMessage(file_path) } {}
}