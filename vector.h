#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    INT,
    DOUBLE,
    FLOAT
} DataType;

typedef struct Vector_Nd{
    DataType type;
    void* data;
    size_t size_of_vector;
    size_t element_size;
} Vector;

Vector* createVector(DataType type);

void addElement(Vector* vector, void* element, DataType type);

void removeElement(Vector* vector, size_t index);

void* getElement(Vector* vector, size_t index);

void printVector(Vector* vector);

void printElement(Vector* vector, size_t index);

void deleteVector(Vector* vector);

Vector* addVectors(Vector* vector1, Vector* vector2);

void scalarProduct(Vector* vector1, Vector* vector2);

Vector* multiplyVector(Vector* vector1, void* value, DataType type);

Vector* vectorProduct(Vector* vector1, Vector* vector2);

void distVector(Vector* vector);
