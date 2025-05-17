#include "blockchain_utils.h"
#include <iostream>
using namespace std;

int main() {
    vector<Block> blocks = load_database("blockchain_data.txt");
    if (blocks.empty()) {
        cout << "No blocks found or error loading database." << endl;
        return 1;
    }

    print_blocks(blocks);

    return 0;
}
