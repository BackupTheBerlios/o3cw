#include "bonbon.h"
int bonbon::BonbonInit()
{
    if (bonbon::CLock::CLockInit()!=0)
        return -1;
    return 0;
}
