#include "../RB.h"



int main(){
    RBTree rb=NULL;
    RB_Insert(rb,9);
    RB_Insert(rb,8);
    RB_Insert(rb,6);
    RB_Insert(rb,2);
    RB_Insert(rb,3);
    RB_Insert(rb,1);
    RB_Delete(rb,2);
    //lev_trave(rb);
    //pre_trave(rb);
    mid_trave(rb);
}

//8 5 15 6 18 3 12