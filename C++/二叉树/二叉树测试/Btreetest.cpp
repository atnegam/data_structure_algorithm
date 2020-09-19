#include "../../global.h"
#include "../Btree.h"
using namespace std;
int main(){
    BTree bt=NULL;
    for(int i=0; i<100; i++){
        Insert(bt,i);
    }
    Delete(bt,63);
    traver(bt);
}