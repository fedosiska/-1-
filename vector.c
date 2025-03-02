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

void addElement(Vector* vector, void* element, struct FieldInfo* type){
    if (vector->type != type){
        printf("Error while adding element: element has wrong type");
        exit(1);
    }
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
    return vector->data + vector->type->element_size * index;
}

void deleteVector(Vector* vector){
    free(vector->data);
    free(vector);
    printf("Vector deleted\n");
}

void printVector(Vector* vector){
    printf("Your vector ");
    for(size_t i = 0; i < vector->size_of_vector; i++){
        if (vector->type == getIntegerFieldInfo()){
            printf("%d ", *(integer_t*)getElement(vector, i));
        }
        else if (vector->type == getDoubleFieldInfo()){
            printf("%f ", *(my_double_t*)getElement(vector, i));
        }
        else if (vector->type == getFloatFieldInfo()){
            printf("%f ", *(my_float_t*)getElement(vector, i));
        }

    printf("\n");
    }
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
        addElement(result, newElement, vector1->type);
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
    double scalarresult = 0.0;
    for(size_t i =0; i<vector1->size_of_vector;i++){
        scalarresult += *(double*)product(vector1->type, getElement(vector1, i), getElement(vector2,i));
    }
    printf("Scalar product: %.2f\n", scalarresult);
}

Vector* multiplyVector(Vector* vector, void* value, struct FieldInfo* type){
    if(vector->type!= type){
        printf("Error in multiplyVector: Vector and value have different datatypes\n");
        exit(1);
    }
    Vector* result = createVector(vector->type);
    for(int i = 0; i < vector->size_of_vector; i++){
        if(vector->type == getIntegerFieldInfo()){
            int multiplied_value_int = *(int*)getElement(vector, i) * *(int*)value;
            addElement(result, &multiplied_value_int, getIntegerFieldInfo());
        }
        else if(vector->type == getDoubleFieldInfo()){
            double multiplied_value_double = *(double*)getElement(vector, i) * *(double*)value;
            addElement(result, &multiplied_value_double, getDoubleFieldInfo());
        }
        else if(vector->type == getFloatFieldInfo()){
            float multiplied_value = *(float*)getElement(vector, i) * *(float*)value;
            addElement(result, &multiplied_value, getFloatFieldInfo());
        }
    }
    return result;
}

void distVector(Vector* vector){
    double dst_result = 0;
    for(int i = 0; i < vector->size_of_vector; i++){
        if(vector->type== getIntegerFieldInfo()){
            dst_result += pow(*(int*)getElement(vector, i), 2);
        }
        else if(vector->type == getDoubleFieldInfo()){
            dst_result += pow(*(double*)getElement(vector, i), 2);
        }
        else if(vector->type == getFloatFieldInfo()){
            dst_result += pow(*(float*)getElement(vector, i), 2);
        }
    }
    double length = sqrt(dst_result);
    printf("Length: %.2f\n", length);
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
    addElement(result, coord_x, vector1->type);
    addElement(result, coord_y, vector1->type);
    addElement(result, coord_z, vector1->type);
    free(coord_x);
    free(coord_y);
    free(coord_z);
    return result;
}
