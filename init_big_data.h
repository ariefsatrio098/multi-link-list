#pragma once
//bigNumber type definition
//child
struct info_big {
    int data;

    info_big(int value) {
        this->data = value;
    }
};

struct elm_big {
    info_big* info;
    elm_big* next;
};
//end def

struct list_big {
    elm_big* first;
};