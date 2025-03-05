#include "types.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct FieldInfo* INT_FIELD_INFO = NULL;
struct FieldInfo* DOULE_FIELD_INFO = NULL;
struct FieldInfo* FLOAT_FIELD_INFO = NULL;

struct FieldInfo* getIntegerFieldInfo(){
    if (INT_FIELD_INFO == NULL) {
        INT_FIELD_INFO = malloc(sizeof(struct FieldInfo));
        INT_FIELD_INFO->element_size = sizeof(struct Integer);
    }
    return INT_FIELD_INFO;
}

struct FieldInfo* getDoubleFieldInfo(){
    if (DOULE_FIELD_INFO == NULL) {
        DOULE_FIELD_INFO = malloc(sizeof(struct FieldInfo));
        DOULE_FIELD_INFO->element_size = sizeof(struct MyDouble);
    }
    return DOULE_FIELD_INFO;
}

struct FieldInfo* getFloatFieldInfo(){
    if (FLOAT_FIELD_INFO == NULL) {
        FLOAT_FIELD_INFO = malloc(sizeof(struct FieldInfo));
        FLOAT_FIELD_INFO->element_size = sizeof(struct MyFloat);
    }
    return FLOAT_FIELD_INFO;
}

integer_t* integer(int value){
    integer_t* assign = malloc(sizeof(integer_t));
    if (!assign)
    {
        printf("Error: reallocating memory\n");
        exit(1);
    }
    assign->value = value;
    return assign;
}

integer_t* intSum(integer_t* arg1, integer_t* arg2){
    integer_t* isum = malloc(sizeof(integer_t));
    if (!isum){
        printf("Error: reallocating memory\n");
        exit(1);
    }
    isum->value = arg1->value + arg2->value;
    return isum;
}

integer_t* intSub(integer_t* a, integer_t* b)
{
    integer_t* isub = malloc(sizeof(integer_t));
    if (!isub){
        printf("Error: reallocating memory\n");
        exit(1);
    }
    isub->value = a->value - b->value;
    return isub;
}

integer_t* intPoduct(integer_t* arg1, integer_t* arg2){
    integer_t* iprod = malloc(sizeof(integer_t));
    if (!iprod){
        printf("Error: reallocating memory\n");
        exit(1);
    }
    iprod->value = arg1->value * arg2->value;
    return iprod;
}

my_double_t* double_(double value){
    my_double_t* assign = malloc(sizeof(my_double_t));
    if (!assign){
        printf("Error: reallocating memory\n");
        exit(1);
    }
    assign->value = value;
    return assign;
}

my_double_t *doubleSum(my_double_t *arg1, my_double_t *arg2){
    my_double_t* dsum = malloc(sizeof(my_double_t));
    if (!dsum){
        printf("Error: reallocating memory\n");
        exit(1);
    }
    dsum->value = arg1->value + arg2->value;
    return dsum;
}

my_double_t* doubleSub(my_double_t* a, my_double_t* b){
    my_double_t* dsub = malloc(sizeof(my_double_t));
    if (!dsub){
        printf("Error: reallocating memory\n");
        exit(1);
    }
    dsub->value = a->value - b->value;
    return dsub;
}

my_double_t* doublePoduct(my_double_t* arg1, my_double_t* arg2){
    my_double_t* dprod = malloc(sizeof(my_double_t));
    if (!dprod){
        printf("Error: reallocating memory\n");
        exit(1);
    }
    dprod->value = arg1->value * arg2->value;
    return dprod;
}

my_float_t* float_(float value){
    my_float_t* assign = malloc(sizeof(my_float_t));
    if (!assign){
        printf("Error: reallocating memory\n");
        exit(1);
    }
    assign->value = value;
    return assign;
}

my_float_t* floatSum(my_float_t* arg1, my_float_t* arg2){
    my_float_t* fsum = malloc(sizeof(my_float_t));
    if (!fsum){
        printf("Error: reallocating memory\n");
        exit(1);
    }
    fsum->value = arg1->value + arg2->value;
    return fsum;
}

my_float_t* floatSub(my_float_t* a, my_float_t* b){
    my_float_t* fsub = malloc(sizeof(my_float_t));
    if (!fsub){
        printf("Error: reallocating memory\n");
        exit(1);
    }
    fsub->value = a->value - b->value;
    return fsub;
}

my_float_t* floatPoduct(my_float_t* arg1, my_float_t* arg2){
    my_float_t* fprod = malloc(sizeof(my_float_t));
    if (!fprod){
        printf("Error: reallocating memory\n");
        exit(1);
    }
    fprod->value = arg1->value * arg2->value;
    return fprod;
}


void freeFieldInfo(struct FieldInfo* fieldInfo){
    if (fieldInfo){ 
        free(fieldInfo);
    }
}

void* Zero(struct FieldInfo* type){
    void* z = malloc(sizeof(type->element_size));
    if (!z){
        printf("Error: reallocating memory\n");
        exit(1);
    }
    for (size_t i = 0 ; i < type->element_size; i++)
    {
        *((char *) z + i) = 0;
    }
    return z;
}
void* sum(struct FieldInfo* type, void* arg1, void* arg2){
    void* new;
    if (type == getIntegerFieldInfo()) {
        new = (void*)(intSum)((integer_t*)arg1, (integer_t*)arg2);
    } else if (type == getDoubleFieldInfo()) {
        new = (void*)(doubleSum((my_double_t*)arg1, (my_double_t*)arg2));
    } else if (type == getFloatFieldInfo()) {
        new = (void*)(floatSum((my_float_t*)arg1, (my_float_t*)arg2));
    }
    return new;
}

void* sub(struct FieldInfo* type, void* arg1, void* arg2){
    void* new;
    if (type == getIntegerFieldInfo()) {
        new = (void*)(intSub)((integer_t*)arg1, (integer_t*)arg2);
    } else if (type == getDoubleFieldInfo()) {
        new = (void*)(doubleSub((my_double_t*)arg1, (my_double_t*)arg2));
    } else if (type == getFloatFieldInfo()) {
        new = (void*)(floatSub((my_float_t*)arg1, (my_float_t*)arg2));
    }
    return new;
 
}

void* product(struct FieldInfo* type, void* arg1, void* arg2){
    void* new;
    if (type == getIntegerFieldInfo()) {
        new = (void*)(intPoduct)((integer_t*)arg1, (integer_t*)arg2);
    } else if (type == getDoubleFieldInfo()) {
        new = (void*)(doublePoduct((my_double_t*)arg1, (my_double_t*)arg2));
    } else if (type == getFloatFieldInfo()) {
        new = (void*)(floatPoduct((my_float_t*)arg1, (my_float_t*)arg2));
    }
    return new;
}
