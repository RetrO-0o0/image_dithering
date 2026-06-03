#include <iostream>
#include <limits>
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
                        "3. 8x8 Bayer\n" << 
                        "0. Exit\n";
            std::cin >> option;

            if ((option < 0) || (option > 3))
                throw(std::out_of_range("Choose a number between 1, 2, 3!\n"));
            else if (!option)
                return 0;

            break;
        }
        catch(const std::exception& e)
        {
            system("cls");
            std::cerr << e.what() << '\n';
        }
    }

    std::string path {};
    std::cout << "Enter a path to your picture: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();
    std::getline(std::cin, path);

    switch (option)
    {
    case 0:
        return 0;

    case 1:
        if (!static_cast<bool>(bayer2x2(path)))
            std::cout << "Dithering Successful!\n";
        else
            std::cout << "Oh we fucked up!\n";
        break;
    
    case 2:
        if (!static_cast<bool>(bayer4x4(path)))
            std::cout << "Dithering Successful!\n";
        else
            std::cout << "Oh we fucked up!\n";
        break;

    case 3:
        if (!static_cast<bool>(bayer8x8(path)))
            std::cout << "Dithering Successful!\n";
        else
            std::cout << "Oh we fucked up!\n";
        break;
        
    default:
        break;
    }

    return 0;
}