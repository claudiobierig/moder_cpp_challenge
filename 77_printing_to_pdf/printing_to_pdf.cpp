#include <iostream>
#include "hpdf.h"



void
error_handler (HPDF_STATUS   error_no,
                HPDF_STATUS   detail_no,
                void         *user_data)
{
    std::cout << error_no << detail_no << user_data << std::endl;
}

int main(){
    HPDF_Doc pdf;

    pdf = HPDF_New (error_handler, NULL);
    if (!pdf) {
        std::cout << "ERROR: cannot create pdf object.\n";
        return 1;
    }
/*
    if (setjmp(env)) {
        HPDF_Free (pdf);
        return 1;
    }*/
}