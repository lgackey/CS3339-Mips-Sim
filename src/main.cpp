#include <iostream>
#include "memory/Memory.h"


int main() {

    Memory mem;
    mem.SW(0, 1268576575);
    int temp = mem.LW(0);

    std::cout << "\nMemory Tests:\n";
    mem.print(); // debug print memory contents

    std::cout << temp;
    return 0;
}