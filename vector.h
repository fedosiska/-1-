#pragma once
#include "types.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct Vector_Nd{
    struct FieldInfo* type;
    void* data;
    size_t size_of_vector;
} Vector;

Vector* createVector(struct FieldInfo* type);

void addElement(Vector* vector, void* element, struct FieldInfo* type);

void removeElement(Vector* vector, size_t index);

void* getElement(Vector* vector, size_t index);

void printVector(Vector* vector);

void printElement(Vector* vector, size_t index);

void deleteVector(Vector* vector);

Vector* addVectors(Vector* vector1, Vector* vector2);

void scalarProduct(Vector* vector1, Vector* vector2);

Vector* multiplyVector(Vector* vector1, void* value, struct FieldInfo* type);

Vector* vectorProduct(Vector* vector1, Vector* vector2);

void distVector(Vector* vector);
