#include "HPLC/file_handling/file_reader.h"
#include <gtest/gtest.h>

TEST(FileReaderModule, OpenFile) 
{ 
    FileReaderBase* file_reader(new StreamFileReader()); 
    if(!file_reader->openFile("data/simple_example_1.hplc"))
    {
        FAIL();
    }
    SourceCode source_code = file_reader->readAll();
    SUCCEED();
}