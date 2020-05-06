#include<stdio.h>
#include<utmp.h>
#include<fcntl.h>
#include<stdlib.h>


const char* ut_path = "/var/run/utmp";

typedef struct u_chain {
    struct utmp* data;
    struct u_chain* next;
}u_chain;

typedef struct u_chain_h {
    u_chain* header;
    u_chain* end;
    int len;
}u_chain_ll;

void append(u_chain_ll* uh, u_chain* u){
    if (uh->header == NULL) {
        uh->header = u;
        uh->end = u;
        uh->len++;
        return;
    }
    uh->end->next = u;
    uh->end = u;
    uh->len++;
    return;
}

void print_u_chains(u_chain_ll* uh){
    if (uh->header == NULL) { 
        printf("nil u_chain_ll\n");
        return;
    }
    struct u_chain *tmp = uh->header;
    while (tmp != NULL){
        printf("%s %d %d(%s)\n", uh->header->data->ut_user, uh->header->data->ut_session, uh->header->data->ut_time, uh->header->data->ut_host);
        tmp = tmp->next;
    }
}

int main(int argc, char* argv[]){
    // open()
    // read()
    // defer close()
    // parse buf to struct
    // printf(struct)
    int fd = open(ut_path, O_RDONLY);
    if (fd <= 0) {
        perror(UTMP_FILE);
        exit(1);
    }
    /*长度未知，没办法直接得到数组长度，但是需要一个内存结构来储存读出来的内容*/
    /*毫无疑问，链表是最适合数据结构了。拓展性好，不需要随机访问， 不需要提前定义长度*/
    /*struct utmp** us = malloc(sizeof(&u));*/
    u_chain_ll ucll = {header: NULL, end: NULL, len: 0};
    /*struct u_chain h;*/
    /*ucll.header = &h;*/

    int size_u = sizeof(struct utmp);
    while(1) {
        struct utmp* us = malloc(size_u);
        u_chain uc = {data: us, next: NULL};

        if ((read(fd, us, size_u)) != size_u){
            break;
        }

        append(&ucll, &uc);
    }
    print_u_chains(&ucll);
    return 0;
}
