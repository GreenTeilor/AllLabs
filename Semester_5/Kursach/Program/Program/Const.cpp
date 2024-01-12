#include "Const.h"

void Const::loadImages()
{
    std::map<Type::Types, std::string> typesAndPaths = Type::getTypesAndPaths();
    for (std::map<Type::Types, std::string>::iterator it = typesAndPaths.begin(); it != typesAndPaths.end(); ++it) {
        std::string fullPath = "assets\\" + it->second + ".bmp";
        if (!(it->first == Type::Types::SMILE_HAPPY || it->first == Type::Types::SMILE_SHOCKED || it->first == Type::Types::SMILE_DEAD || it->first == Type::Types::SMILE_COOL 
            || it->first == Type::Types::DIGITS))
        {
            images.insert({ it->first, (HBITMAP)LoadImageA(NULL, fullPath.c_str(), IMAGE_BITMAP, Const::imgWidth, Const::imgHeight, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE) });
        }
        else if (it->first != Type::Types::DIGITS)
        {
            images.insert({ it->first, (HBITMAP)LoadImageA(NULL, fullPath.c_str(), IMAGE_BITMAP, Const::smileWidth, Const::smileHeight, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE) });
        }
        else
        {
            images.insert({ it->first, (HBITMAP)LoadImageA(NULL, fullPath.c_str(), IMAGE_BITMAP, Const::digitsWidth, Const::digitsHeight, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE) });
        }
    }
}