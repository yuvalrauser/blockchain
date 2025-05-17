#include "blockchain_utils.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage:\n";
        cout << "  " << argv[0] << " --hash <value>\n";
        cout << "  " << argv[0] << " --height <value>\n";
        return 1;
    }

    string option = argv[1];
    string value = argv[2];

    vector<Block> blocks = load_database("blockchain_data.txt");
    if (blocks.empty()) {
        cout << "No blocks found or error loading database." << endl;
        return 1;
    }

    if (option == "--hash") {
        find_block_by_hash(blocks, value);
    } else if (option == "--height") {
        find_block_by_height(blocks, value);
    } else {
        cout << "Invalid option. Use --hash or --height.\n";
        return 1;
    }

    return 0;
}
