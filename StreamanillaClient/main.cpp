//
//  main.cpp
//  StreamanillaClient
//
//  Created by Dmitry Chaban on 12/17/16.
//  Copyright © 2016 dmi3coder. All rights reserved.
//

#include <iostream>
#include "mongoose.h"
using namespace std;

static const char *s_http_port = "1234";
static struct mg_serve_http_opts s_http_server_opts;
static bool connected = 0;

static void client_handler(struct mg_connection *conn, int ev, void *p) {
    cout<< "this is it!";

    if (ev == MG_EV_CONNECT) {
        if (conn->flags & MG_F_CLOSE_IMMEDIATELY) {
            printf("%s\n", "Error connecting to server!");
            exit(EXIT_FAILURE);
        }
        connected = 1;
        printf("%s\n", "Connected to server. Type a message and press enter.");
    } else if(ev == MG_EV_RECV){
        printf("we have a party lol!");
    } else if(ev == MG_EV_ACCEPT){
        mg_send(conn, NULL, 0);
    }
//    else if (ev == MG_EV_RECV) {
//        if (conn->flags & MG_F_USER_1) {
//            // Received data from the stdin, forward it to the server
//            struct mg_connection *c = (struct mg_connection *) conn->user_data;
//            mg_send(c, io->buf, io->len);
//            mbuf_remove(io, io->len);
//        } else {
//            // Received data from server connection, print it
//            fwrite(io->buf, io->len, 1, stdout);
//            mbuf_remove(io, io->len);
//        }
//    } else if (ev == MG_EV_CLOSE) {
//        // Connection has closed, most probably cause server has stopped
//        exit(EXIT_SUCCESS);
//    }
}

int main(int argc, const char * argv[]) {
    cout << "Hello, there! :>)";
    struct mg_mgr mgr;
    struct mg_connection *nc;
    
    mg_mgr_init(&mgr, NULL);
    nc = mg_connect(&mgr, "1234", client_handler);
    if(nc != NULL){
        mg_send(nc, NULL, 0);
        for(;;){
            mg_mgr_poll(&mgr, 1000);
        }
        return 1;
    }
    
    
    

    return 0;
}
