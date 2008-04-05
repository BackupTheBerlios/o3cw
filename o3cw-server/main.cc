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
    
    return (EXIT_SUCCESS);
}

