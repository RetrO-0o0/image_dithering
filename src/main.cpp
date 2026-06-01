#include <iostream>
#include "bayer2x2.hpp"
#include "bayer4x4.hpp"
#include "bayer8x8.hpp"

int main()
{
    int option {};
    while (true)
    {
        try
        {
            std::cout << "Enter your choice of dithering algorithm:\n" << 
                        "1. 2x2 Bayer\n" <<
                        "2. 4x4 Bayer\n" <<
                        "3. 8x8 Bayer\n";
            std::cin >> option;

            if (0 < option < 4)
            {
                system("cls");
                break;
            }
            else
            {
                system("cls");
                throw("Choose a number between 1, 2, 3!\n");
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::string path {};
    std::cout << "Enter a path to your picture: ";
    std::getline(std::cin, path);
    
    

    switch (option)
    {
    case 1:
        if (!bayer2x2(path))
            std::cout << "Dithering Successful!\n";
        else
            std::cout << "Oh we fucked up!\n";
        break;
    
    case 2:
        if (!bayer4x4(path))
            std::cout << "Dithering Successful!\n";
        else
            std::cout << "Oh we fucked up!\n";
        break;

    case 3:
        if (!bayer8x8(path))
            std::cout << "Dithering Successful!\n";
        else
            std::cout << "Oh we fucked up!\n";
        break;
        
    default:
        break;
    }

    return 0;
}