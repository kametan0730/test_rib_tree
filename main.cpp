#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "tree.h"

int main(){
    print_address_binary(inet_addr("10.20.30.0"));
    print_address_binary(inet_addr("10.20.40.0"));

    node root{
            .is_prefix = true,
            .ip_address = 0,
            .prefix_len = 0,
            .next_hop = 0,
            .parent = nullptr,
            .node_0 = nullptr,
            .node_1 = nullptr,
    };

    add_prefix(&root, inet_addr("10.0.0.0"), 8, inet_addr("10.0.0.1"));
    add_prefix(&root, inet_addr("10.20.0.0"), 16, inet_addr("10.20.0.1"));
    add_prefix(&root, inet_addr("10.20.30.0"), 24, inet_addr("10.20.30.1"));
    add_prefix(&root, inet_addr("10.20.31.0"), 24, inet_addr("10.20.30.1"));
    add_prefix(&root, inet_addr("10.20.40.0"), 24, inet_addr("10.20.40.1"));

    node* res;
    uint8_t prefix = search_prefix(&root, inet_addr("10.20.30.1"), res);

    printf("%d\n", prefix);
    in_addr addr{
        .s_addr = res->next_hop
    };
    printf("%s\n", inet_ntoa(addr));
    return 0;
}
