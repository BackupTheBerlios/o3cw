// 
// File:   main.cc
// Author: alex
//
// Created on 5 Апрель 2008 г., 0:03
//

#include <stdlib.h>

#include "cdoc.h"
#include "extra/libbonbon/bonbon.h"
//
// 
//
int main(int argc, char** argv)
{
    //Initialize BonBon - little threads library.
    bonbon::BonbonInit();
    o3cw::CDoc my_doc;
    printf("creating new docs\n");
    for (int a=0; a<20; a++)
    {
        o3cw::CDoc my_doc1;
        o3cw::CDoc my_doc2;
        printf("my doc id=[%u]\n", my_doc1.GetId());
    }
    return (EXIT_SUCCESS);
}
