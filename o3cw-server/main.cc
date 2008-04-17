// 
// File:   main.cc
// Author: alex
//
// Created on 5 Апрель 2008 г., 0:03
//

#include <stdlib.h>

#include "cdoc.h"
#include "libbonbon.h"
#include "cconnectionhandler.h"
//
// 
//
int main(int argc, char** argv)
{
    //Initialize BonBon - little threads library.
    bonbon::BonbonInit();
    
    /* Load main config */
    o3cw::CO3CWBase::LoadMainConfig("/etc/o3cw-server.cfg");
    
    /* Example of config usage */
//    o3cw::CConfig conf;
//    conf.Parse("<?xml><config><main><alex><p1>value1</p1><p2>value2</p2></alex></main>/config>");
//    std::string b1, b2;
//    conf.GetValue(b1,"p1","main:alex");
//    conf.GetValue(b2,"p2","main:alex");
//    printf("b1=[%s]\n", b1.c_str());
//    printf("b2=[%s]\n", b2.c_str());
    std::string b1;
    const o3cw::CConfig *main_conf=&(o3cw::CO3CWBase::GetMainConfig());
    main_conf->GetValue(b1,"default","net:timeout");
    printf("b1=[%s]\n", b1.c_str());
    
    
    //Run connections handler (echo-server)

    o3cw::CConnectionHandler connections_handler;

    
    return (EXIT_SUCCESS);
}
