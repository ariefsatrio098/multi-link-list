#pragma once
#include "init_big_data.h"
//normalNumber type definition
//parent
struct info_normal {
    int data;

    info_normal(int value) {
        this->data = value;
    }
};

struct elm_normal {
    info_normal* info;
    elm_normal* next;
    list_big* bigNum; //child
};
//end def

struct list_normal {
    elm_normal* first;
};