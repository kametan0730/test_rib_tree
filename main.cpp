#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "tree.h"

int main(){
    print_address_binary(inet_addr("10.20.30.0"));
    print_address_binary(inet_addr("10.20.40.0"));

    node* root = (node*) malloc(sizeof(node));
    root->is_prefix = true;
    root->prefix = 0;
    root->prefix_len = 0;
    root->next_hop = 0;
    root->parent = nullptr;
    root->node_0 = nullptr;
    root->node_1 = nullptr;

    //add_prefix(root, inet_addr("10.0.0.0"), 8, inet_addr("10.0.0.1"));
    add_prefix(root, inet_addr("10.20.0.0"), 16, inet_addr("10.20.0.1"));
    add_prefix(root, inet_addr("10.20.30.0"), 24, inet_addr("10.20.30.1"));
    add_prefix(root, inet_addr("10.20.31.0"), 24, inet_addr("10.20.31.1"));
    add_prefix(root, inet_addr("10.20.40.0"), 24, inet_addr("10.20.40.1"));

    node* n1 = add_prefix(root, inet_addr("1.0.0.0"), 4, inet_addr("10.0.0.1"));
    node* n2 = add_prefix(root, inet_addr("1.0.0.0"), 8, inet_addr("10.0.0.1"));

    // assert_tree(root);

    node* res = search_prefix(root, inet_addr("10.20.30.1"));
    uint8_t prefix_len = res->prefix_len;

    printf("%d\n", prefix_len);
    in_addr addr{
        .s_addr = res->next_hop
    };
    printf("%s\n", inet_ntoa(addr));

    delete_prefix(n1);

    delete_prefix(root, true);

    //assert_tree(root);
    // TODO すべての出力をあってるかテストしたい

    return 0;
}
