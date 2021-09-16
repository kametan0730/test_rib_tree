#ifndef TEST_RIB_TREE_TREE_H
#define TEST_RIB_TREE_TREE_H

#include <cstdint>

#define N_BIT(A, N) ((A >> (N)) & 0b01)

struct node{
    bool is_prefix;
    uint32_t ip_address;
    uint8_t prefix_len;
    uint32_t next_hop;
    node* parent;
    node* node_0;
    node* node_1;
};

void print_address_binary(uint32_t addr);
void assert_tree(node* node);

void delete_prefix(node* prefix);
uint8_t search_prefix(node* root, uint32_t address, node*& result, uint8_t max = 32);
node* add_prefix(node* root, uint32_t address, uint8_t prefix, uint32_t next_hop);

#endif //TEST_RIB_TREE_TREE_H
