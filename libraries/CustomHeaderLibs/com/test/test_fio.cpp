// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.08.2013 15:28:12 CEST
// File:    test_fio.cpp

#include <iostream>
#include "../../std_support.hpp"
#include "../fio.hpp"

com::fio_class f;

int main(int argc, char* argv[]) {
    
    std::cout << "bla" << std::endl;
    
    int a = 1;
    
    //~ f.open_write("test.txt");
    //~ f << a;
    
    f.open_read("test.txt");
    f >> a;
    
    
    std::cout << a << std::endl;
    
    f.close();
    
    return 0;
}
