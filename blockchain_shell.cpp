#include "blockchain_utils.h"
#include <iostream>
using namespace std;

void printMenu() {
    cout << "\nChoose an option:\n";
    cout << "1. Print DB\n";
    cout << "2. Print block by hash\n";
    cout << "3. Print block by height\n";
    cout << "4. Export data to CSV\n";
    cout << "5. Refresh data\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    while (true) {
        printMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number between 0 and 5.\n";
            continue;
        }

        // Load DB for all relevant actions
        vector<Block> blocks = load_database("blockchain_data.txt");
        if (blocks.empty()) {
            cout << "No blocks found or error loading database.\n";
            continue;
        }

        switch (choice) {
            case 1:
                print_blocks(blocks);
                break;

            case 2: {
                string hash;
                cout << "Enter block hash: ";
                cin >> hash;
                find_block_by_hash(blocks, hash);
                break;
            }

            case 3: {
                string height;
                cout << "Enter block height: ";
                cin >> height;
                find_block_by_height(blocks, height);
                break;
            }

            case 4:
                export_to_csv(blocks, "blocks.csv");
                cout << "Export completed successfully to blocks.csv :)" << endl;
                break;

            case 5: {
                int num_blocks;
                cout << "Enter number of blocks to reload: ";
                cin >> num_blocks;
                reload_database(num_blocks);
                break;
            }

            default:
                cout << "Invalid choice. Please enter a number between 0 and 5.\n";
                break;
        }
    }

    return 0;
}
