#pragma once
#include <cstdint>

class FileWriterBase
{
public:
  virtual bool writeUInt32(std::uint32_t value) = 0;
};