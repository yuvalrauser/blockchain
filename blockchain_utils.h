#ifndef BLOCKCHAIN_UTILS_H
#define BLOCKCHAIN_UTILS_H

#include <string>
#include <vector>
using namespace std;

struct Block {
    string hash;
    string height;
    string total;
    string time;
    string received_time;
    string relayed_by;
    string prev_block;
};

vector<Block> load_database(const string& filename);
void print_blocks(const vector<Block>& blocks);
void find_block_by_hash(const vector<Block>& blocks, const string& hash);
void find_block_by_height(const vector<Block>& blocks, const string& height);
void export_to_csv(const vector<Block>& blocks, const string& filename);
void reload_database(int num_blocks);
void print_block(const Block& block);

#endif
