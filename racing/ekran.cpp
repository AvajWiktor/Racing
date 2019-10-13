#include "ekran.h"

cWindow::cWindow(){
    setPosition(400,100);
}


int cWindow :: get_start(){

    return start_;

}


void cWindow::set_start(int start){
    start_=start;
}
