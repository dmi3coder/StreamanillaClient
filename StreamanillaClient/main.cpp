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

static bool connected = 0;

static void client_handler(struct mg_connection *conn, int ev, void *p) {
    struct mbuf *io = &conn->send_mbuf;
    static int a  = 1;
    switch (ev) {
        case MG_EV_CONNECT:
            
            if (conn->flags & MG_F_CLOSE_IMMEDIATELY) {
                printf("%s\n", "Error connecting to server!");
                exit(EXIT_FAILURE);
            }else{
                string *data = new string("my location is woodward, usa");
                mg_send(conn, data->c_str(), data->length());
                delete data;
                printf("%s\n", "Connected to server. Type a message and press enter.");
                
            }
            break;
        case MG_EV_SEND:
            break;
        case MG_EV_RECV:
        {
            string receivedString = io->buf;
            cout << receivedString;
        }
            cout << "MG_EV_RECV dude,for real! "<< a++ << endl;
            break;
        case MG_EV_ACCEPT:
            break;
        case MG_EV_POLL:
            mg_send(conn, &(conn->recv_mbuf), (int)conn->recv_mbuf.len);
            mbuf_remove(&conn->recv_mbuf, (int)conn->recv_mbuf.len);
        default:
            break;
    }
}

int main(int argc, const char * argv[]) {
    cout << "Hello, there! :>)\n";
    struct mg_mgr mgr;
    struct mg_connection *nc;
    
    mg_mgr_init(&mgr, NULL);
    nc = mg_connect(&mgr, "tcp://192.168.0.100:1234", client_handler);
    if(nc != NULL){
        for(;;){
            mg_mgr_poll(&mgr, 1000);
        }
        return 1;
    }
    
    
    

    return 0;
}
