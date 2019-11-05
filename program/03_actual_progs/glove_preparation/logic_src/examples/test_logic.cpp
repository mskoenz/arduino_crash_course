// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    14.06.2013 22:35:09 EDT
// File:    std_uart_example.cpp

#include <iostream>
#include <logic.hpp>

int main(int argc, char* argv[]) {
    
    char c;
    
    std::cout << "enter char: " << std::endl;
    std::cin >> c;
    
    logic.read_all_gest();
    
    logic.key_meta[0].key = "key a";
    logic.key_meta[0].name = "Faust";
    
    logic.write_archive("test.hex");
    return 0;
}
