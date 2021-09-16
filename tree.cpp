#include <cstdio>
#include <cstdlib>

#include "tree.h"

void print_address_binary(uint32_t addr){
    for(int i = 0; i < 32; ++i){
        if(N_BIT(addr, i)){
            printf("1");
        }else{
            printf("0");
        }
    }
    printf("\n");
}

void assert_tree(node* node){
    if(node->node_0 != nullptr){
        if(node->node_0->prefix_len != node->prefix_len + 1){
            printf("Invalid prefix length %d and %d\n", node->node_0->prefix_len, node->prefix_len);
        }else{
            printf("Assert OK\n");
        }
        assert_tree(node->node_0);
    }
    if(node->node_1 != nullptr){
        if(node->node_1->prefix_len != node->prefix_len + 1){
            printf("Invalid prefix length %d and %d\n", node->node_1->prefix_len, node->prefix_len);
        }else{
            printf("Assert OK\n");
        }
        assert_tree(node->node_1);
    }
}

void delete_prefix(node* prefix){
    prefix->is_prefix = false; // 削除対象のプレフィックスはプレフィックス扱いしない
    if(prefix->node_1 != nullptr and prefix->node_0 == nullptr){
        return delete_prefix(prefix->node_1);
    }
    if(prefix->node_0 != nullptr and prefix->node_1 == nullptr){
        return delete_prefix(prefix->node_0);
    }
    node* tmp;
    if(prefix->node_1 != nullptr and prefix->node_0 != nullptr){
        tmp = prefix->node_1;
        prefix->node_1 = nullptr;
        delete_prefix(prefix);
        return delete_prefix(tmp);
    }
    node* current = prefix;
    while(!current->is_prefix and current->parent != nullptr and (current->parent->node_0 == nullptr or current->parent->node_1 == nullptr)){
        printf("Release: %d\n", current->prefix_len);
        tmp = current->parent;
        if(current->parent->node_1 == current){
            current->parent->node_1 = nullptr;
        }else{
            current->parent->node_0 = nullptr;
        }
        free(current);
        current = tmp;
    }

}

uint8_t search_prefix(node* root, uint32_t address, node*& result, uint8_t max){
    node* current = root;
    node* next;
    node* match_node = root;
    uint8_t i = 0;
    while(i < max){
        if(current->is_prefix){
            match_node = current;
        }
        next = (N_BIT(address, i) ? current->node_1 : current->node_0);
        if(next == nullptr){
            result = match_node;
            return match_node->prefix_len;
        }
        i++;
        current = next;
    }
    result = match_node;
    return match_node->prefix_len;
}

node* add_prefix(node* root, uint32_t address, uint8_t prefix, uint32_t next_hop){
    node* current;
    uint8_t res_prefix = search_prefix(root, address, current, prefix-1);
    res_prefix++;
    node** growth_address_ptr;
    while(res_prefix < prefix){ // 枝を伸ばす
        printf("Create: %d\n", res_prefix);
        if(N_BIT(address, res_prefix-1)){
            growth_address_ptr = &current->node_1;
        }else{
            growth_address_ptr = &current->node_0;
        }
        if((*growth_address_ptr) != nullptr){
            current = *growth_address_ptr;
        }else{
            node* growth_node = (node*) malloc(sizeof(node));
            growth_node->is_prefix = false;
            growth_node->ip_address = current->ip_address;
            growth_node->prefix_len = res_prefix;
            growth_node->next_hop = 0;
            growth_node->parent = current;
            growth_node->node_0 = nullptr;
            growth_node->node_1 = nullptr;
            if(N_BIT(address, res_prefix - 1)){
                growth_node->ip_address |= (0x01 << (res_prefix));
                current->node_1 = growth_node;
            }else{
                current->node_0 = growth_node;
            }
            current = growth_node;
        }
        res_prefix++;
    }
    node* new_prefix = (node*) malloc(sizeof(node));
    new_prefix->is_prefix = true;
    new_prefix->ip_address = address;
    new_prefix->prefix_len = prefix;
    new_prefix->next_hop = next_hop;
    new_prefix->parent = current;
    new_prefix->node_0 = nullptr;
    new_prefix->node_1 = nullptr;
    if(N_BIT(address, prefix - 1)){
        current->node_1 = new_prefix;
    }else{
        current->node_0 = new_prefix;
    }
    return new_prefix;
}