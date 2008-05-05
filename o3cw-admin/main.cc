// 
// File:   main.cc
// Author: alex
//
// Created on 21 Апрель 2008 г., 21:19
//

#include <string>
#include <stdlib.h>
#include <iostream>
#include "clistener.h"
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
    adm::CListener listner(&client);
    
    std::cout << "O3CW administrator tool" << std::endl;
    std::cout << "Use `\\q` to exit" << std::endl;
    std::cout << "Use `\\help` to get help" << std::endl;
    std::cout << "Type command and press enter" << std::endl;
    std::cout << "Press enter twice at and of input to execute command sequence." << std::endl;

    o3cw::CClient clnt;
    o3cw::CCommand cmd(clnt);
    std::string buff;
    bool work=true;
    while (work)
    {
        bool execute=true;
        buff.erase();
        std::cout << ">";
        std::getline(std::cin, buff);
        size_t body_size=buff.length();
        if (buff.length()>0)
        {
            if (buff[0]!='\\')
            {
                execute=false;
                cmd.Push(buff);
            }
            else
            {
                cmd.Clear();
                if (buff=="\\shutdown")
                {
                    cmd.Push("server");
                    cmd.Push("exit");
                }
                else if (buff.find("\\login")==0)
                {
                    int name_begins=strlen("\\login");
                    size_t l=buff.length();
                    while (l>name_begins && buff[name_begins]==' ')
                        name_begins++;
                    
                    std::string login=(buff.c_str()+name_begins);
                    if (login=="")
                    {
                        std::cout << "Usage: \\login username" << std::endl;
                         execute=false;
                    }
                    else
                    {
                        cmd.Push("user");
                        cmd.Push("open");
                        cmd.Push(login);
                    }
                }
                else if (buff=="\\docs")
                {
                    cmd.Push("doc");
                    cmd.Push("list");
                }
                else if (buff=="\\help" || buff=="\\?" )
                {
                    std::cout << "Supported commands:" << std::endl;
                    std::cout << "\\get filename - get file from server" << std::endl;
                    std::cout << "\\help - get this message" << std::endl;
                    std::cout << "\\shutdown - shutdown o3cw server" << std::endl;
                    std::cout << "\\login (user) - login as user" << std::endl;
                    std::cout << "\\docs - print list of all aviable docs" << std::endl;
                    std::cout << "\\open (doc) - open doc with specified doc_id" << std::endl;
                    std::cout << "\\get (doc_id) - get content of an opened doc" << std::endl;
                    std::cout << "\\q - exit" << std::endl;
                }
                else if (buff=="\\q")
                {
                    work=false;
                }
            }
        }
        
        if (execute)
        {
            std::cout << " * Executing" << std::endl;
            std::string send_buff;
            cmd.Compile(send_buff);
            if (client.SendBody(send_buff)<=0)
                std::cout << " * Connection lost" << std::endl;
            cmd.Clear();
        }
    }
    listner.Kill();
    return (EXIT_SUCCESS);
}

