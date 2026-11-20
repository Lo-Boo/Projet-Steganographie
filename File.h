#pragma once

class File
{
protected:
    FILE* stream = nullptr;

    const char* filename;
    const char* newfilename;

    BYTE* buffer = nullptr;
    long size = 0;

public:
    bool Save(std::string newname);
    bool Load(std::string name);

    BYTE* GetBuffer()
    {
        return buffer;
    }

    // suprime les BYTE
    File()
    {
    }
    ~File()
    {
        delete[] buffer;
    }
};