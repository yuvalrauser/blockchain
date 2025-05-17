#include "blockchain_utils.h"
#include <iostream>
#include <cstdlib>  
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <number of blocks>" << endl;
        return 1;
    }

    int num_blocks = atoi(argv[1]);  

    if (num_blocks <= 0) {
        cout << "Invalid number of blocks. Please enter a positive integer." << endl;
        return 1;
    }

    reload_database(num_blocks);

    return 0;
}
