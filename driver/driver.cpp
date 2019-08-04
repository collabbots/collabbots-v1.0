#include <iostream>
#include <stdio.h>
#include <string>

int main()
{
    FILE *file;
    //Opening device file

    std::string instrct;

    while (true)
    {
        file = fopen("/dev/ttyACM0", "w");
        std::cout << ">>" << std::endl;
        std::cin >> instrct;
        fprintf(file, "%s", instrct.c_str()); //Writing to the file
        fclose(file);
    }

    return 0;
}