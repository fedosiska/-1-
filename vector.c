#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "types.h"


Vector* createVector(struct FieldInfo* type){
    Vector* vector = (Vector*)malloc(sizeof(Vector));
    vector->size_of_vector=0;
    vector->type=type;
    vector->data = malloc(vector->type->element_size);
    return vector;
}

void addElement(Vector* vector, void* element){
    void* new_data = realloc(vector->data, vector->type->element_size * (vector->size_of_vector + 1));
    if(new_data == NULL){
        printf("Error: reallocating memory\n");
        exit(1);
    }
    
    vector->data = new_data;
    memcpy((char*)vector->data + vector->type->element_size * vector->size_of_vector, element, vector->type->element_size);
    vector->size_of_vector++;
}

void removeElement(Vector* vector, size_t index) {
    if (index >= vector->size_of_vector) {
        printf("Error while removing element: index out of range\n");
        exit(1);
    }
    for (size_t i = index; i < vector->size_of_vector - 1; i++) {
        memcpy((char*)vector->data + vector->type->element_size * i, (char*)vector->data + vector->type->element_size * (i + 1), vector->type->element_size);
    }
    vector->size_of_vector--;

    void* new_data = realloc(vector->data, vector->type->element_size * vector->size_of_vector);
    if (new_data == NULL && vector->size_of_vector > 0) {
        printf("Error reallocating memory\n");
        exit(1);
    }
    vector->data = new_data;
}
void* getElement(Vector* vector, size_t index){
    if(index >= vector->size_of_vector){
        printf("Error while getting element: index out of range\n");
        exit(1);
    }
    return (char*)vector->data + vector->type->element_size * index;
}

void deleteVector(Vector* vector){
    if (!vector->data){
        printf("Error: Vector cannot be deleted\n");
        exit(1);
    }
    free(vector->data);
    free(vector);
    printf("Vector deleted\n");
}

void toString(Vector* vector){
    printf("Your vector: [");
    for (size_t i = 0; i < vector->size_of_vector; i++) {
        vector->type->toString(getElement(vector, i));
        if(i!= vector->size_of_vector-1) printf(", ");
    }
    printf("]\n");
}

Vector* addVectors(Vector* vector1, Vector* vector2){
    if(vector1->type != vector2->type){
        printf("Error in adding Vectors: Vectors have different datatypes\n");
        exit(1);
    }
    if(vector1->size_of_vector != vector2->size_of_vector){
        printf("Error in adding Vectors: Vectors have different sizes\n");
        exit(1);
    }
    Vector* result = createVector(vector1->type);
    for(size_t i = 0; i < vector1->size_of_vector; i++){
        void* newElement;
        newElement = sum(vector1->type, getElement(vector1, i), getElement(vector2, i));
        addElement(result, newElement);
        free(newElement);
    }
    return result;
}

void scalarProduct(Vector* vector1, Vector* vector2){
    if(vector1->type != vector2->type){
        printf("Error in scalarProduct: Vectors have different datatypes\n");
        exit(1);
    }
    if(vector1->size_of_vector!= vector2->size_of_vector){
        printf("Error in scalarProduct: Vectors have different sizes\n");
        exit(1);
    }
    void* scalarresult = Zero(vector1->type);
    for(size_t i =0; i<vector1->size_of_vector;++i){
        scalarresult = sum(vector1->type, product(vector1->type, getElement(vector1, i), getElement(vector2,i)), scalarresult);
    }
    printf("Scalar product result: ");
    vector1->type->toString(scalarresult);
    free(scalarresult);
}

Vector* multiplyVector(Vector* vector, void* value, struct FieldInfo* type){
    if(vector->type!= type){
        printf("Error in multiplyVector: Vector and value have different datatypes\n");
        exit(1);
    }
    Vector* result = createVector(vector->type);
    for (size_t i = 0; i < vector->size_of_vector; i++) {
        void* multiplied_value = product(vector->type, getElement(vector, i), value);
        addElement(result, multiplied_value);
        free(multiplied_value);
    }
    return result;
}

Vector* vectorProduct(Vector* vector1, Vector* vector2){
    if(vector1->type!= vector2->type){
        printf("Error in vectorProduct: Vectors have different datatypes\n");
        exit(1);
    }
    if(vector1->size_of_vector!= 3 || vector2->size_of_vector!= 3){
        printf("Error in vectorProduct: Vectors must have 3 elements\n");
        exit(1);
    }
    Vector* result = createVector(vector1->type);
    void* coord_x;
    void* coord_y;
    void* coord_z;
    coord_x = sub(vector1->type, product(vector1->type,getElement(vector1, 1),getElement(vector2, 2)), product(vector2->type, getElement(vector1,2), getElement(vector2,1)));
    coord_y = sub(vector1->type, product(vector1->type,getElement(vector1,2), getElement(vector2,0)), product(vector2->type, getElement(vector1,0), getElement(vector2,2)));
    coord_z = sub(vector1->type, product(vector1->type,getElement(vector1,0), getElement(vector2,1)), product(vector2->type, getElement(vector1,1), getElement(vector2,0)));
    addElement(result, coord_x);
    addElement(result, coord_y);
    addElement(result, coord_z);
    free(coord_x);
    free(coord_y);
    free(coord_z);
    return result;
}
