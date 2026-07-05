#pragma once
#include <string>
#include <fstream>
#include <exception>


class FileReaderBase
{
public:
    virtual char readChar() = 0;
    virtual bool openFile() = 0;
    virtual bool closeFile() = 0;
    virtual std::string readAll() = 0;
};




class StreamFileReader : public FileReaderBase
{

};


