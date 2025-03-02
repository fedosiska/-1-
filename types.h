#pragma once

#include <stdlib.h>

struct FieldInfo {
    size_t element_size;
};

struct FieldInfo* getIntegerFieldInfo();
struct FieldInfo* getDoubleFieldInfo();

struct FieldInfo* getFloatFieldInfo();

void freeFieldInfo();

typedef struct Integer {
    int value;
} integer_t;

integer_t* integer(int value);

integer_t* intSum(integer_t* arg1, integer_t* arg2);

integer_t* intSub(integer_t* arg1, integer_t* arg2);

integer_t* intPoduct(integer_t* arg1, integer_t* arg2);

typedef struct MyDouble {
    double value;
} my_double_t;

my_double_t* double_(double value);

my_double_t* doubleSum(my_double_t* arg1, my_double_t* arg2);

my_double_t* doubleSub(my_double_t* arg1, my_double_t* arg2);

my_double_t* doubleProduct(my_double_t* arg1, my_double_t* arg2);

typedef struct MyFloat {
    float value;
} my_float_t;

my_float_t* float_(float value);

my_float_t* floatSum(my_float_t* arg1, my_float_t* arg2);

my_float_t* floatSub(my_float_t* arg1, my_float_t* arg2);

my_float_t* floatProduct(my_float_t* arg1, my_float_t* arg2);

void* sum(struct FieldInfo* type, void* arg1, void* arg2);

void* product(struct FieldInfo* type, void* arg1, void* arg2);
