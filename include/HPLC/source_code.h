#pragma once

using Program = std::string;
using FileName = std::string;

struct SourceCode
{
    FileName name {""};
    Program contents{""};
};