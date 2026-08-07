#pragma once
#include <exception>
#include <fstream>
#include <string>
#include "HPLC/source_code.h"

class FileReaderBase
{
public:
  virtual char        readChar()  = 0;
  virtual bool        openFile(FileName input_file)  = 0;
  virtual bool        closeFile() = 0;
  virtual SourceCode readAll()   = 0;
};

class StreamFileReader : public FileReaderBase
{

private:
  std::ifstream m_fileStream {};
  FileName m_fileName {""};

public:
  StreamFileReader() = default;

  char readChar() override
  {
    if (char result = m_fileStream.get())
    {
      return result;
    }
    else
    {
      return '\0';
    }
  }

  bool openFile(FileName file) override
  {
    m_fileStream.open(file);
    m_fileName = file;

    if (!m_fileStream.is_open()) 
    { 
      return false;
    }
    
    return true;
  }

  bool closeFile() override
  {
    m_fileStream.close();
    
    if (m_fileStream.is_open()) 
    { 
      return false;
    }
    
    return true;
  }

  SourceCode readAll() override
  {
    std::string program_string{};
    std::string line{};
    while(m_fileStream)
    {
      std::getline(m_fileStream, line);
      program_string.append(line);
      program_string.push_back('\n');
    }
    return SourceCode{m_fileName, program_string};
  }
};
