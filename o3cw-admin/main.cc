// 
// File:   main.cc
// Author: alex
//
// Created on 21 Апрель 2008 г., 21:19
//

#include <string>
#include <stdlib.h>
#include <iostream>
#include "../o3cw-core/o3cw.h"
//
// 
//
int main(int argc, char** argv)
{
    bonbon::BonbonInit();
    std::cout << "Connecting to 127.0.0.1:25005...";
    std::cout.flush();
    o3cw::CClient client;
    if (client.Connect("127.0.0.1", 25005)==0)
        std::cout << "OK" << std::endl;
    else
    {
        std::cout << "failed." << std::endl;
        exit(-1);
    }
    std::cout << "O3CW administrator tool" << std::endl;
    std::cout << "Use `\\q` for exit" << std::endl;
    std::cout << "Type command and press enter" << std::endl;
    std::cout << "Press enter twice at and of input to execute command sequence." << std::endl;

    
    //o3cw::CCommand cmd;
    std::string cmd;
    
    std::string buff("-");
    while (buff!="\\q")
    {
        std::cout << ">";
        std::getline(std::cin, buff);
        size_t body_size=buff.length();
        if (buff.length()>0)
        {
            char tmp[4];
            memcpy(tmp, &body_size, 4);
            cmd.append(tmp,4);
            cmd.append(buff, 0, body_size);
        }
        else
        {
            std::cout << " * Executing" << std::endl;
            char head[1024];
            snprintf(head,1024, "HEAD\nlength=%u\n\n",cmd.length());
            std::string to_send(head);
            to_send.append(cmd);
            if (client.Send(to_send)<=0)
                std::cout << " * Connection lost" << std::endl;

            cmd.erase();
            
        }
    }
    std::cout.flush();
    return (EXIT_SUCCESS);
}

