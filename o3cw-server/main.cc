// 
// File:   main.cc
// Author: alex
//
// Created on 5 Апрель 2008 г., 0:03
//

#include <stdlib.h>

#include "co3cwserver.h"
//
// 
//
int main(int argc, char** argv)
{

    /* Initialize BonBon - little threads library. */
    bonbon::BonbonInit();

    /* One O3CW Server application must be created */
    o3cwapp::CO3CWServer server;
    server.LoadConfig("/etc/o3cw-server.cfg");
    server.Run();
    server.Shutdown();
    
    return (EXIT_SUCCESS);
}
