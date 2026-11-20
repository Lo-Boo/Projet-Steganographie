#pragma once
#include "File.h"

class BitMap
{
protected:
    File file;

    BYTE hideLetters;
    std::string secret = "";
    int width = 0;
    int height = 0;
    int bits = 0;
    int stride = 0;
    int shift = 0;

    BYTE* buffers = nullptr;
    BYTE* bgr = nullptr;
    BYTE red;
    BYTE green;
    BYTE blue;

    int place_x = 198;
    int place_y = 82;

public:
    bool ReadImage(std::string name);
	bool WriteImage(std::string text);
    void SavingImage(std::string newname);
    void WriteText();

    BYTE Decoded(BYTE red, BYTE green, BYTE blue);

	unsigned int GetPixel(BYTE* data, int offset, int size);
    void SetImage(BYTE& red, BYTE& green, BYTE& blue, BYTE letter);

    BitMap()
    {
    }
    ~BitMap() = default;
};

