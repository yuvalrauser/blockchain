#include "blockchain_utils.h"
#include <fstream>
#include <iostream>
#include <cstdlib> 
using namespace std;

vector<Block> load_database(const string& filename) {
    vector<Block> blocks;
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file " << filename << endl;
        return blocks;
    }

    string line;
    Block currentBlock;
    int field_count = 0; 

    while (getline(file, line)) {
        if (line.find("hash: ") == 0) {
            currentBlock.hash = line.substr(6);
            field_count++;
        } else if (line.find("height: ") == 0) {
            currentBlock.height = line.substr(9);
            field_count++;
        } else if (line.find("total: ") == 0) {
            currentBlock.total = line.substr(7);
            field_count++;
        } else if (line.find("time: ") == 0) {
            currentBlock.time = line.substr(6);
            field_count++;
        } else if (line.find("received_time: ") == 0) {
            currentBlock.received_time = line.substr(15);
            field_count++;
        } else if (line.find("relayed_by: ") == 0) {
            currentBlock.relayed_by = line.substr(12);
            field_count++;
        } else if (line.find("prev_block: ") == 0) {
            currentBlock.prev_block = line.substr(12);
            field_count++;
        } else if (line == "|" || line == "V " || line.empty()) {
            continue; 
        }

        if (field_count == 7) {
            blocks.push_back(currentBlock);
            currentBlock = Block(); 
            field_count = 0;
        }
    }

    file.close();
    return blocks;
}

void print_block(const Block& block) {
    cout << "hash: " << block.hash << endl;
    cout << "height: " << block.height << endl;
    cout << "total: " << block.total << endl;
    cout << "time: " << block.time << endl;
    cout << "received_time: " << block.received_time << endl;
    cout << "relayed_by: " << block.relayed_by << endl;
    cout << "prev_block: " << block.prev_block << endl;
}

void print_blocks(const vector<Block>& blocks) {
    for (size_t i = 0; i < blocks.size(); i++) {
        print_block(blocks[i]);

        if (i < blocks.size() - 1) {
            cout << "                              |" << endl;
            cout << "                              |" << endl;
            cout << "                              |" << endl;
            cout << "                              V" << endl;
        }
    }
}

void find_block_by_hash(const vector<Block>& blocks, const string& hash) {
    for (size_t i = 0; i < blocks.size(); i++) {
        if (blocks[i].hash == hash) {
            print_block(blocks[i]);
            return; 
        }
    }
    cout << "Block not found for given hash." << endl;
}

void find_block_by_height(const vector<Block>& blocks, const string& height) {
    for (size_t i = 0; i < blocks.size(); i++) {
        if (blocks[i].height == height) {
            print_block(blocks[i]);
            return;
        }
    }
    cout << "Block not found for given height." << endl;
}

void export_to_csv(const vector<Block>& blocks, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    file << "hash_value,height,total,time,received_time,relayed_by,prev_block\n";

    for (const Block& block : blocks) {
        file << block.hash << ","
             << block.height << ","
             << block.total << ","
             << block.time << ","
             << block.received_time << ","
             << block.relayed_by << ","
             << block.prev_block << "\n";
    }

    file.close();
}

void reload_database(int num_blocks) {
    string command = "./get_blocks.sh " + to_string(num_blocks);
    int result = system(command.c_str());
    if (result != 0) {
        cerr << "Error: Failed to reload database." << endl;
    }
}
