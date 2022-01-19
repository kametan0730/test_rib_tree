#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "tree.h"

struct attribute{
    uint8_t origin;
    uint32_t next_hop;
    uint32_t med;
    uint32_t local_pref;
    // attribute* next; // TODO 複数の属性を持たせられるように
};

void print_address_binary(uint32_t addr){
    for(int i = 31; i >= 0; --i){
        if(CHECK_BIT(addr, i)){
            printf("1");
        }else{
            printf("0");
        }
    }
    printf("\n");
}

int main(){

    auto* root = (node<attribute>*) malloc(sizeof(node<attribute>));
    root->is_prefix = true;
    root->prefix = 0;
    root->prefix_len = 0;
    root->data = nullptr;
    root->parent = nullptr;
    root->node_0 = nullptr;
    root->node_1 = nullptr;

    add_prefix<attribute>(root, ntohl(inet_addr("1.2.3.64")), 28, attribute{
            .origin = 0,
            .next_hop = inet_addr("1.1.1.1"),
            .med = 0,
            .local_pref = 0
    }); // WAN

    add_prefix<attribute>(root, ntohl(inet_addr("1.2.3.80")), 28, attribute{
            .origin = 0,
            .next_hop = inet_addr("2.2.2.2"),
            .med = 0,
            .local_pref = 0
    });

    add_prefix<attribute>(root, ntohl(inet_addr("0.0.0.0")), 0, attribute{
            .origin = 0,
            .next_hop = inet_addr("3.3.3.3"),
            .med = 0,
            .local_pref = 0
    });


    auto a = search_prefix(root, ntohl(inet_addr("203.178.139.248")));
    std::cout << a->data->next_hop << std::endl;
/*


    add_prefix<attribute>(root, ntohl(inet_addr("10.20.0.0")), 16, attribute{
            .origin = 0,
            .next_hop = inet_addr("10.20.0.1"),
            .med = 0,
            .local_pref = 0
    });


    //add_prefix(root, inet_addr("10.0.0.0"), 8, inet_addr("10.0.0.1"));
    add_prefix<attribute>(root, ntohl(inet_addr("10.20.0.0")), 16, attribute{
            .origin = 0,
            .next_hop = inet_addr("10.20.0.1"),
            .med = 0,
            .local_pref = 0
    });
    add_prefix(root, ntohl(inet_addr("255.255.0.0")), 16, attribute{
            .origin = 0,
            .next_hop = inet_addr("1.1.1.1"),
            .med = 0,
            .local_pref = 0
    });

    add_prefix(root, ntohl(inet_addr("10.20.30.0")), 24, attribute{
            .origin = 0,
            .next_hop = inet_addr("10.20.30.1"),
            .med = 0,
            .local_pref = 0
    });

    add_prefix(root, ntohl(inet_addr("10.20.31.0")), 24, attribute{
            .origin = 0,
            .next_hop = inet_addr("10.20.31.1"),
            .med = 0,
            .local_pref = 0
    });
    add_prefix(root, ntohl(inet_addr("10.20.40.0")), 24, attribute{
            .origin = 0,
            .next_hop = inet_addr("10.20.0.1"),
            .med = 0,
            .local_pref = 0
    });

    node<attribute>* n1 = add_prefix(root, ntohl(inet_addr("1.0.0.0")), 4, attribute{
            .origin = 0,
            .next_hop = inet_addr("10.20.0.1"),
            .med = 0,
            .local_pref = 0
    });
    node<attribute>* n2 = add_prefix(root, ntohl(inet_addr("1.0.0.0")), 8, attribute{
            .origin = 0,
            .next_hop = inet_addr("10.20.0.1"),
            .med = 0,
            .local_pref = 0
    });

    //assert_tree(root);

    node<attribute>* res = search_prefix(root, ntohl(inet_addr("10.20.30.1")), 24, true);

    if(res == nullptr){
        printf("Result is null\n");
    }else{
        uint8_t prefix_len = res->prefix_len;
        printf("%d\n", prefix_len);
        printf("%s\n", inet_ntoa(in_addr{.s_addr = res->data->next_hop}));
    }

    delete_prefix(n1);

    */
    /*
    add_prefix(root, ntohl(inet_addr("103.247.181.0")), 24, inet_addr("103.247.181.1"));
    add_prefix(root, ntohl(inet_addr("103.247.181.224")), 28, inet_addr("103.247.181.224"));

    print_address_binary(ntohl(inet_addr("103.247.181.0")));
    print_address_binary(ntohl(inet_addr("103.247.181.224")));
    print_address_binary(ntohl(inet_addr("103.247.181.225")));
    printf("%d\n", ntohl(inet_addr("103.247.181.225")));
    //print_address_binary_2(inet_addr("103.247.181.225"));

    node* res2 = search_prefix(root, ntohl(inet_addr("103.247.181.224")));
    if(res2 == nullptr){
        printf("Result is null\n");
    }else{
        uint8_t prefix_len2 = res2->prefix_len;

        printf("%d\n", prefix_len2);
        printf("%s\n", inet_ntoa(in_addr{.s_addr = res2->next_hop}));

    }

    */
    // assert_tree(root);


    delete_prefix(root, true);


    //assert_tree(root);
    // TODO すべての出力をあってるかテストしたい

    return 0;
}
