#include "pch.h"
#include "File.h"

bool File::Load(std::string name)
{
    filename = name.c_str(); // convertit un string en n'importe quel type de variable 

    if (fopen_s(&stream, filename, "rb") != 0)
        return false;

    fseek(stream, 0, SEEK_END);
    size = ftell(stream);
    fseek(stream, 0, SEEK_SET);

    buffer = new BYTE[size];
    // lire l'image/dossier
    if (fread(buffer, 1, size, stream) != size)
    {
        delete[] buffer;
        buffer = nullptr;
        size = 0;
        return false;
    }

    if (size == 0)
        return false;

    fclose(stream);
    stream = nullptr;
    return true;
}

bool File::Save(std::string newname)
{
    if (buffer == nullptr)
        return false;

    newfilename = newname.c_str();

    if (fopen_s(&stream, newfilename, "wb") != 0)
        return false;

    fwrite(buffer, 1, size, stream);

    fclose(stream);
    stream = nullptr;
    return true;
}

