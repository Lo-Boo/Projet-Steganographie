#include "pch.h"
#include "BitMap.h"

void BitMap::SavingImage(std::string newname)
{
	file.Save(newname);
}

unsigned int BitMap::GetPixel(BYTE* data, int offset, int size)
{
	if (offset < 0 || offset >= 8 || size <= 0 || size > 8 - offset)
		return 0;

	unsigned int mask = 0xFF;

	mask >>= (8 - size);
	mask <<= offset;
	unsigned int result = *data & mask;
	result >>= offset;
	return result;

}

void BitMap::SetImage(BYTE& red, BYTE& green, BYTE& blue, BYTE letters)
{
	unsigned int value_red = GetPixel(&letters, 0, 3);
	red &= 0b11111000;
	red |= value_red;

	unsigned int value_green = GetPixel(&letters, 3, 2);
	green &= 0b11111100;
	green |= value_green;

	unsigned int value_blue = GetPixel(&letters, 5, 3);
	blue &= 0b11111000;
	blue |= value_blue;
}

bool BitMap::ReadImage(std::string name)
{
	if (!file.Load(name))
		return false;

	buffers = file.GetBuffer();

	if (buffers == nullptr)
		return false;

	BITMAPFILEHEADER bfh;
	memcpy(&bfh, buffers, sizeof(BITMAPFILEHEADER));
	if (bfh.bfType != 0x4D42)
		return false;

	BITMAPINFOHEADER bih;
	memcpy(&bih, buffers + sizeof(bfh), sizeof(BITMAPINFOHEADER));
	if (bih.biBitCount != 24)
		return false;

	width = bih.biWidth;
	height = abs(bih.biHeight);
	bits = bih.biBitCount;
	shift = bfh.bfOffBits;

	if (width == 0 || height == 0)
		return false;

	stride = (width * bits + 31) / 32 * 4;
	return true;
}

bool BitMap::WriteImage(std::string text)
{
	if (buffers == nullptr)
		return false;

	bgr = buffers + shift;

	int i = 0;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = y * stride + x * 3;

			BYTE& blue = bgr[index];
			BYTE& green = bgr[index + 1];
			BYTE& red = bgr[index + 2];

			if (x == place_x && y == place_y && i <= text.size())
			{
				BYTE l = text[i];
				SetImage(red, green, blue, l);

				bgr[index] = blue;
				bgr[index + 1] = green;
				bgr[index + 2] = red;
				i++;
				place_x++;
			}
		}
	}
	return true;
}

BYTE BitMap::Decoded(BYTE red, BYTE green, BYTE blue)
{
	BYTE letters = 0;

	letters |= GetPixel(&red, 0, 3);
	letters |= GetPixel(&green, 0, 2) << 3;
	letters |= GetPixel(&blue, 0, 3) << 5;

	return letters;
}

void BitMap::WriteText()
{
	bgr = buffers + shift;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (x >= place_x && y >= place_y)
			{
				int index = y * stride + x * 3;

				BYTE& blue = bgr[index];
				BYTE& green = bgr[index + 1];
				BYTE& red = bgr[index + 2];

				hideLetters = Decoded(red, green, blue);
				if (hideLetters == '\0')
				{
					std::cout << "Le message est : " << secret;
					return;
				}
				secret += (char)hideLetters;
			}
		}
	}
}