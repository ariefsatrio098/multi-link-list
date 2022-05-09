#include <iostream>
//include header inisialisasi data "normal", yang didalam headernya 
//sekalian mengimport(include) header inisialisai data "big"(child)
#include "init_normal_data.h"

using namespace std;

//procedure (fungsi)
//
//init procedure
void inputDataNormal(list_normal* list, int val);
void inputDataBig(list_big* list, int val, elm_big* insertedElm);
void print(list_big* big, list_normal* normal);
elm_normal* searchDataNormal(list_normal* list, int key);
elm_big* searchDataBig(list_big* list, int key);
void addRelation(list_normal* listn, list_big* listb, int keyNormal, int keyBig);
void delRelation(list_normal* listn, int keyNormal, int keyBig);
void delDataBig(list_big* list, int keyBig);
void delDataNormal(list_normal *list, int keyNormal);
//end of init 

//memasukkan data (node) kedalam list
//normal
void inputDataNormal(list_normal* list, int val) {
    elm_normal* elm = new elm_normal();
    info_normal* n = new info_normal(val);
    elm->info = n;
    if (list->first == NULL) {
        list->first = elm;
    }
    else {
        elm->next = list->first;
        list->first = elm;
    }
}

//big
void inputDataBig(list_big* list, int val = NULL, elm_big* insertedElm = NULL) {
    if (val != NULL) {
        elm_big* elm = new elm_big();
        info_big* n = new info_big(val);
        elm->info = n;
        if (list->first == NULL) {
            list->first = elm;
        }
        else {
            elm->next = list->first;
            list->first = elm;
        }
    }
    else if (insertedElm != NULL) {
        if (list->first == NULL) {
            list->first = insertedElm;
        }
        else {
            insertedElm->next = list->first;
            list->first = insertedElm;
        }
    }
}

//print data
void print(list_big* big = NULL, list_normal* normal = NULL ){
    if (normal != NULL) {
        elm_normal* tempNormal = normal->first;
        cout << "list normal:" << endl;
        while (tempNormal != NULL) {
            cout << tempNormal->info->data << "\t";
            cout << "\tchild:";
            if (tempNormal->bigNum != NULL) {
                elm_big* tempNormal_child = tempNormal->bigNum->first;
                while (tempNormal_child != NULL) {
                    cout << "\t" << tempNormal_child->info->data;
                    tempNormal_child = tempNormal_child->next;
                } 
            }
            cout << endl;
            tempNormal = tempNormal->next;
        }
        cout << endl;
    }
    
    if (big != NULL) {
        elm_big* tempBig = big->first;
        cout << "list big:" << endl;
        while (tempBig != NULL) {
            cout << tempBig->info->data << "\t" << endl;
            tempBig = tempBig->next;
        }
        cout << endl;
    }
}

//mencari node dari valuenya dalam suatu list
//normal
elm_normal* searchDataNormal(list_normal* list, int key) {
    elm_normal* tempNormal = list->first;
    while (tempNormal != NULL) {
        if (key == tempNormal->info->data) {
            return tempNormal;
        }
        tempNormal = tempNormal->next;
    }
    return NULL;
}

//big
elm_big* searchDataBig(list_big* list, int key) {
    elm_big* tempBig = list->first;
    while (tempBig != NULL) {
        if (key == tempBig->info->data) {
            return tempBig;
        }
        tempBig = tempBig->next;
    }
    return NULL;
}

//menambah relasi kelist parrent dan membuat sebuah list baru sebagai child yang datanya 
//didapat dari list sebelumnya (child awal)
void addRelation(list_normal* listn, list_big* listb, int keyNormal, int keyBig) {
    //declare
    elm_normal* p;
    elm_big* q, *r;
    list_big* newList;

    //algorithm
    p = searchDataNormal(listn, keyNormal);
    q = searchDataBig(listb, keyBig);
    if (p != NULL && q != NULL) {
        r = new elm_big();
        r->info = q->info;
        if (p->bigNum == NULL) {
            newList= new list_big();
        }
        else {
            newList = p->bigNum;
        }
        p->bigNum = newList;
        inputDataBig(newList, 0, r);
    }
}

//menghapus relasi dan data dalam list yang di hubungkan pada parrent
void delRelation(list_normal* listn, int keyNormal, int keyBig) {
    //declare
    elm_normal* p;
    list_big* childList;

    //algorithm
    p = searchDataNormal(listn, keyNormal);
    if (p != NULL && p->bigNum != NULL) {
        childList = p->bigNum;
        delDataBig(childList, keyBig);
    }
}

//menghapus node dari list parrent 
//normal 
void delDataNormal(list_normal* list, int keyNormal) {
    elm_normal* target = NULL, * prev = NULL, * tempNormal = list->first;
    bool got = true;
    //algorithm jika data yang dicari ada pada posisi awal
    if (tempNormal->info->data == keyNormal) {
        list->first = tempNormal->next;
        tempNormal->next = NULL;
        return;
    }
    else {
        while (tempNormal != NULL) {
            if (!got) {
                keyNormal == tempNormal->next->info->data;
            }
            if (!got) {
                prev = tempNormal;
                got = true;
            }
            if (keyNormal == tempNormal->info->data) {
                target = tempNormal;
            }
            tempNormal = tempNormal->next;
        }
        if (target != NULL && prev != NULL) {
            prev->next = target->next;
            target->next = NULL;
        }
    }
}

//menghapus data dari list child (awal)
//big
void delDataBig(list_big* list, int keyBig) {
    elm_big* target = NULL, *prev = NULL, *tempBig = list->first;
    bool got = false;
    //algorithm jika data yang dicari ada pada posisi awal
    if (tempBig->info->data == keyBig) {
        list->first = tempBig->next;
        tempBig->next = NULL;
        return;
    }
    else {
        while (tempBig != NULL) {
            if (!got) {
                keyBig == tempBig->next->info->data;
            }
            if (!got) {
                prev = tempBig;
                got = true;
            }
            if (keyBig == tempBig->info->data) {
                target = tempBig;
            }
            tempBig = tempBig->next;
        }
        if (target != NULL && prev != NULL) {
            prev->next = target->next;
            target->next = NULL;
        }
    }
}


int main() {
    list_normal* lNormal = new list_normal();
    list_big* lBig = new list_big();
    inputDataNormal(lNormal, 1);
    print(lBig, lNormal);
    inputDataBig(lBig, 2000);
    print(lBig, lNormal);
    inputDataNormal(lNormal, 10);
    print(lBig, lNormal);
    inputDataBig(lBig, 1000);
    print(lBig, lNormal);
    inputDataNormal(lNormal, 4);
    print(lBig, lNormal);
    addRelation(lNormal, lBig, 4, 2000);
    print(lBig, lNormal);
    addRelation(lNormal, lBig, 10, 2000);
    print(lBig, lNormal);
    addRelation(lNormal, lBig, 10, 1000);
    print(lBig, lNormal);
    delRelation(lNormal, 10, 2000);
    print(lBig, lNormal);
    delRelation(lNormal, 4, 2000);
    print(lBig, lNormal);
}