// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    29.05.2012 20:51:50 CEST
// File:    test_list.cpp

#include <iostream>

#define GCC

#include "list_class.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    list<int> map;
    map.push_back(4);
    map.push_back(5);
    map.push_back(6);
    map.push_back(7);

    //~ cout << map.back() << endl;
    //~ map.remove(6);
    //~ cout << map.back() << endl;
    //~ map.remove(6);
    //~ cout << map.back() << endl;
    //~ map.remove(4);
    //~ cout << map.back() << endl;
    //~ map.remove(5);
    map.print();
    
    for(int i = 0; i < map.size(); ++i)
    {
        cout << map[i] << endl;
    }
    
    
}
