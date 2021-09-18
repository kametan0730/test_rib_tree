#ifndef TEST_RIB_TREE_TREE_H
#define TEST_RIB_TREE_TREE_H

#include <cstdint>
#include <netinet/in.h>

/*
struct entry{
    uint32_t next_hop;
    entry* next_entry;
};
*/

struct node{
    bool is_prefix;
    uint32_t prefix;
    uint8_t prefix_len;
    uint32_t next_hop;
    node* parent;
    node* node_0;
    node* node_1;
};

bool check_bit(uint32_t addr, uint8_t n);
void print_address_binary(uint32_t addr);
void print_address_binary_2(uint32_t addr);
void assert_tree(node* node);

// entry* add_entry_to_prefix();

void delete_prefix(node* prefix, bool is_delete_child_prefix = false);
node* search_prefix(node* root, uint32_t address, uint8_t max_prefix_len = 32, bool is_prefix_strict = false);
node* add_prefix(node* root, uint32_t prefix, uint8_t prefix_len, uint32_t next_hop);

#endif //TEST_RIB_TREE_TREE_H
