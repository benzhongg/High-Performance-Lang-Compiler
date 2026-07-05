#pragma once

template <typename OT, typename IT> class FileWriterBase
{
public:
  virtual std::vector<OT> write(std::vector<IT> inputVector) = 0;
};