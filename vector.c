#include <math.h>
#include <string.h>
#include "vector.h"


Vector* createVector(DataType type){
    Vector* vector = (Vector*)malloc(sizeof(Vector));
    vector->size_of_vector=0;
    vector->type=type;
    switch (type)
    {
    case INT:
        vector->element_size = sizeof(int);
        break;
    case DOUBLE:
        vector->element_size = sizeof(double);
        break;
    case FLOAT:
        vector->element_size = sizeof(float);
        break;
    }

    vector->data = malloc(vector->element_size);
    return vector;
}

void addElement(Vector* vector, void* element, DataType type){
    if (vector->type != type){
        printf("Error while adding element: element has wrong type");
        exit(1);
    }
    void* new_data = realloc(vector->data, vector->element_size * (vector->size_of_vector + 1));
    if(new_data == NULL){
        printf("Error: reallocating memory\n");
        exit(1);
    }
    
    vector->data = new_data;
    memcpy((char*)vector->data + vector->element_size * vector->size_of_vector, element, vector->element_size);
    vector->size_of_vector++;
}

void removeElement(Vector* vector, size_t index) {
    if (index >= vector->size_of_vector) {
        printf("Error while removing element: index out of range\n");
        exit(1);
    }
    for (size_t i = index; i < vector->size_of_vector - 1; i++) {
        memcpy((char*)vector->data + vector->element_size * i, (char*)vector->data + vector->element_size * (i + 1), vector->element_size);
    }
    vector->size_of_vector--;

    void* new_data = realloc(vector->data, vector->element_size * vector->size_of_vector);
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
    return vector->data + vector->element_size * index;
}

void deleteVector(Vector* vector){
    free(vector->data);
    free(vector);
    printf("Vector deleted\n");
}

void printVector(Vector* vector){
    printf("Your vector ");
    for(size_t i = 0; i < vector->size_of_vector; i++){
        switch (vector->type)
        {
        case INT:
            printf("%d ", *(int*)getElement(vector, i));
            break;
        case DOUBLE:
            printf("%f ", *(double*)getElement(vector, i));
            break;
        case FLOAT:
            printf("%f ", *(float*)getElement(vector, i));
            break;
        }
    }
    printf("\n");
}

void printElement(Vector* vector, size_t index){
    if(index >= vector->size_of_vector){
        printf("Error in printing: index out of range\n");
        exit(1);
    }
    switch (vector->type)
    {
    case INT:
        printf("Element is %d\n", *(int*)getElement(vector, index));
        break;
    case DOUBLE:
        printf("Element is %f\n", *(double*)getElement(vector, index));
        break;
    case FLOAT:
        printf("Element is %f\n", *(float*)getElement(vector, index));
        break;
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
    switch(vector1->type){
        case INT:
            Vector* result_int = createVector(INT);
            for(int i = 0; i < vector1->size_of_vector; i++){
                int sum_int = *(int*)getElement(vector1, i) + *(int*)getElement(vector2, i);
                addElement(result_int, &sum_int, INT);
            }
            return result_int;
            break;
        case DOUBLE:
            Vector* result_double = createVector(DOUBLE);
            for(int i = 0; i < vector1->size_of_vector; i++){
                double sum_double = *(double*)getElement(vector1, i) + *(double*)getElement(vector2, i);
                addElement(result_double, &sum_double, DOUBLE);
            }
            return result_double;
            break;
        case FLOAT:
            Vector* result_float = createVector(FLOAT);
            for(int i = 0; i < vector1->size_of_vector; i++){
                float sum_float = *(float*)getElement(vector1, i) + *(float*)getElement(vector2, i);
                addElement(result_float, &sum_float, FLOAT);
            }
            return result_float;
            break;
    }
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
    switch(vector1->type){
        case INT:
            int scalar_product_int = 0;
            for(int i = 0; i < vector1->size_of_vector; i++){
                scalar_product_int += *(int*)getElement(vector1, i) * *(int*)getElement(vector2, i);
            }
            printf("Scalar product: %d\n", scalar_product_int);
            break;
        case DOUBLE:
            double scalar_product_double = 0;
            for(int i = 0; i < vector1->size_of_vector; i++){
                scalar_product_double += *(double*)getElement(vector1, i) * *(double*)getElement(vector2, i);
            }
            printf("Scalar product: %f\n", scalar_product_double);
            break;
        case FLOAT:
            float scalar_product_float = 0;
            for(int i = 0; i < vector1->size_of_vector; i++){
                scalar_product_float += *(float*)getElement(vector1, i) * *(float*)getElement(vector2, i);
            }
            printf("Scalar product: %f\n", scalar_product_float);
            break;
    }
}

Vector* multiplyVector(Vector* vector, void* value, DataType type){
    if(vector->type!= type){
        printf("Error in multiplyVector: Vector and value have different datatypes\n");
        exit(1);
    }
    Vector* result = createVector(vector->type);
    for(int i = 0; i < vector->size_of_vector; i++){
        switch(vector->type){
            case INT:
                int multiplied_value_int = *(int*)getElement(vector, i) * *(int*)value;
                addElement(result, &multiplied_value_int, INT);
                break;
            case DOUBLE:
                double multiplied_value_double = *(double*)getElement(vector, i) * *(double*)value;
                addElement(result, &multiplied_value_double, DOUBLE);
                break;
            case FLOAT:
                float multiplied_value = *(float*)getElement(vector, i) * *(float*)value;
                addElement(result, &multiplied_value, FLOAT);
                break;
        }
    }
    return result;
}

void distVector(Vector* vector){
    double dst_result = 0;
    for(int i = 0; i < vector->size_of_vector; i++){
        switch(vector->type){
            case INT:
                dst_result += pow(*(int*)getElement(vector, i), 2);
                break;
            case DOUBLE:
                dst_result += pow(*(double*)getElement(vector, i), 2);
                break;
            case FLOAT:
                dst_result += pow(*(float*)getElement(vector, i), 2);
                break;
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
    switch (vector1->type){
        case INT:
            int coord_x_int = *(int*)getElement(vector1, 1) * *(int*)getElement(vector2, 2) - *(int*)getElement(vector1, 2) * *(int*)getElement(vector2, 1);
            int coord_y_int = *(int*)getElement(vector1, 2) * *(int*)getElement(vector2, 0) - *(int*)getElement(vector1, 0) * *(int*)getElement(vector2, 2);
            int coord_z_int = *(int*)getElement(vector1, 0) * *(int*)getElement(vector2, 1) - *(int*)getElement(vector1, 1) * *(int*)getElement(vector2, 0);
            addElement(result, &coord_x_int, INT);
            addElement(result, &coord_y_int, INT);
            addElement(result, &coord_z_int, INT);
            break;
        case DOUBLE:
            double coord_x_double = *(double*)getElement(vector1, 1) * *(double*)getElement(vector2, 2) - *(double*)getElement(vector1, 2) * *(double*)getElement(vector2, 1);
            double coord_y_double = *(double*)getElement(vector1, 2) * *(double*)getElement(vector2, 0) - *(double*)getElement(vector1, 0) * *(double*)getElement(vector2, 2);
            double coord_z_double = *(double*)getElement(vector1, 0) * *(double*)getElement(vector2, 1) - *(double*)getElement(vector1, 1) * *(double*)getElement(vector2, 0);
            addElement(result, &coord_x_double, DOUBLE);
            addElement(result, &coord_y_double, DOUBLE);
            addElement(result, &coord_z_double, DOUBLE);
            break;
        case FLOAT:
            float coord_x_float = *(float*)getElement(vector1, 1) * *(float*)getElement(vector2, 2) - *(float*)getElement(vector1, 2) * *(float*)getElement(vector2, 1);
            float coord_y_float = *(float*)getElement(vector1, 2) * *(float*)getElement(vector2, 0) - *(float*)getElement(vector1, 0) * *(float*)getElement(vector2, 2);
            float coord_z_float = *(float*)getElement(vector1, 0) * *(float*)getElement(vector2, 1) - *(float*)getElement(vector1, 1) * *(float*)getElement(vector2, 0);
            addElement(result, &coord_x_float, FLOAT);
            addElement(result, &coord_y_float, FLOAT);
            addElement(result, &coord_z_float, FLOAT);
            break;
    }
    return result;
}
