#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

void logMessage(char* message) {
    FILE* outFile = fopen(OUTPUT_FILE, "a");
    if (outFile) {
        fprintf(outFile, "%s\n", message);
        fclose(outFile);
    }
}

int main() {
    FILE* inFile = fopen(INPUT_FILE, "r");
    if (!inFile) {
        logMessage("Error: Cannot open input file.");
        return 1;
    }
    
    FILE* outFile = fopen(OUTPUT_FILE, "w");
    if (!outFile) {
        fclose(inFile);
        logMessage("Error: Cannot open output file.");
        return 1;
    }
    fclose(outFile);

    char command[50];
    Vector* vector1 = NULL;
    Vector* vector2 = NULL;
    struct FieldInfo* type1;
    struct FieldInfo* type2;
    
    while (fscanf(inFile, "%s", command) != EOF) {
        if (strcmp(command, "CREATE1") == 0) {
            char typeStr[10];
            fscanf(inFile, "%s", typeStr);
            if (strcmp(typeStr, "INT") == 0) type1 = getIntegerFieldInfo();
            else if (strcmp(typeStr, "DOUBLE") == 0) type1 = getDoubleFieldInfo();
            else if (strcmp(typeStr, "FLOAT") == 0) type1 = getFloatFieldInfo();
            else {
                logMessage("Error: Invalid data type.");
                continue;
            }
            vector1 = createVector(type1);
            logMessage("Vector 1 created.");
        } 
        else if (strcmp(command, "CREATE2") == 0) {
            char typeStr[10];
            fscanf(inFile, "%s", typeStr);
            if (strcmp(typeStr, "INT") == 0) type2 = getIntegerFieldInfo();
            else if (strcmp(typeStr, "DOUBLE") == 0) type2 = getDoubleFieldInfo();
            else if (strcmp(typeStr, "FLOAT") == 0) type2 = getFloatFieldInfo();
            else {
                logMessage("Error: Invalid data type.");
                continue;
            }
            vector2 = createVector(type2);
            logMessage("Vector 2 created.");
        } 
        else if (strcmp(command, "ADD1") == 0) {
            if (!vector1) {
                logMessage("Error: Vector 1 not created.");
                continue;
            }
            
            char typeStr[10];
            fscanf(inFile, "%s", typeStr);
            struct FieldInfo* inputType;
            if (strcmp(typeStr, "INT") == 0) inputType = getIntegerFieldInfo();
            else if (strcmp(typeStr, "DOUBLE") == 0) inputType = getDoubleFieldInfo();
            else if (strcmp(typeStr, "FLOAT") == 0) inputType = getFloatFieldInfo();
            else {
                logMessage("Error: Invalid data type.");
                continue;
            }
            
            if (inputType != vector1->type) {
                logMessage("Error: Wrong data type for Vector 1.");
                continue;
            }
            
            if (vector1->type == getIntegerFieldInfo()) {
                int int_value;
                fscanf(inFile, "%d", &int_value);
                integer_t* value = integer(int_value);
                addElement(vector1, value);
            } else if (vector1->type == getDoubleFieldInfo()) {
                double double_value;
                fscanf(inFile, "%lf", &double_value);
                my_double_t* value = double_(double_value);
                addElement(vector1, value);
            } else if (vector1->type == getFloatFieldInfo()) {
                float float_value;
                fscanf(inFile, "%f", &float_value);
                my_float_t* value = float_(float_value);
                addElement(vector1, value);
            }
            logMessage("Element added to Vector 1.");
        } 
        else if (strcmp(command, "ADD2") == 0) {
            if (!vector2) {
                logMessage("Error: Vector 2 not created.");
                continue;
            }
            
            char typeStr[10];
            fscanf(inFile, "%s", typeStr);
            struct FieldInfo* inputType;
            if (strcmp(typeStr, "INT") == 0) inputType = getIntegerFieldInfo();
            else if (strcmp(typeStr, "DOUBLE") == 0) inputType = getDoubleFieldInfo();
            else if (strcmp(typeStr, "FLOAT") == 0) inputType = getFloatFieldInfo();
            else {
                logMessage("Error: Invalid data type.");
                continue;
            }
            
            if (inputType != vector2->type) {
                logMessage("Error: Wrong data type for Vector 2.");
                continue;
            }
            
            if (vector2->type == getIntegerFieldInfo()) {
                int int_value;
                fscanf(inFile, "%d", &int_value);
                integer_t* value = integer(int_value);
                addElement(vector2, value);
            } else if (vector2->type == getDoubleFieldInfo()) {
                double double_value;
                fscanf(inFile, "%lf", &double_value);
                my_double_t* value = double_(double_value);
                addElement(vector2, value);
            } else if (vector2->type == getFloatFieldInfo()) {
                float float_value;
                fscanf(inFile, "%f", &float_value);
                my_float_t* value = float_(float_value);
                addElement(vector2, value);
            }
            logMessage("Element added to Vector 2.");
        } 
        else if (strcmp(command, "REMOVE1") == 0){
            if (!vector1) {
                logMessage("Error: Vector 1 not created.");
                continue;
            }
            
            int index;
            fscanf(inFile, "%d", &index);
            if (index < 0 || index >= vector1->size_of_vector) {
                logMessage("Error: Invalid index.");
                continue;
            }
            
            removeElement(vector1, index);
            logMessage("Element removed from Vector 1.");
        }
        else if (strcmp(command, "REMOVE2") == 0){
            if (!vector2) {
                logMessage("Error: Vector 2 not created.");
                continue;
            }
            
            int index;
            fscanf(inFile, "%d", &index);
            if (index < 0 || index >= vector2->size_of_vector) {
                logMessage("Error: Invalid index.");
                continue;
            }
            
            removeElement(vector2, index);
            logMessage("Element removed from Vector 2.");
        }
        else if (strcmp(command, "ADD_VECTORS") == 0) {
            if (!vector1 || !vector2) {
                logMessage("Error: One or both vectors not created.");
                continue;
            }
            
            if (vector1->type != vector2->type) {
                logMessage("Error: Cannot add vectors of different types.");
                continue;
            }

            if (vector1->size_of_vector != vector2->size_of_vector) {
                logMessage("Error: Vectors must have the same size for addition.");
                continue;
            }
            
            Vector* result = addVectors(vector1, vector2);
            if (result) {
                logMessage("Vectors added successfully.");
                deleteVector(result);
            } else {
                logMessage("Error: Vector addition failed.");
            }
        } 
        else if (strcmp(command, "DELETE") == 0) {
            if (vector1) {
                deleteVector(vector1);
                vector1 = NULL;
                logMessage("Vector 1 deleted.");
            }
            if (vector2) {
                deleteVector(vector2);
                vector2 = NULL;
                logMessage("Vector 2 deleted.");
            }
        } 
        else if (strcmp(command, "SCALAR_PRODUCT") == 0) {
            if (!vector1 || !vector2) {
                logMessage("Error: One or both vectors not created.");
                continue;
            }
            if (vector1->type != vector2->type) {
                logMessage("Error: Cannot make scalar product of different types.");
                continue;
            }
            if (vector1->size_of_vector != vector2->size_of_vector) {
                logMessage("Error: Vectors must have the same size for scalar product.");
                continue;
            }
            scalarProduct(vector1, vector2);
            
            logMessage("Scalar product was made successfully.");
        } 
        else if (strcmp(command, "VECTOR_PRODUCT") == 0) {
            if (!vector1 || !vector2) {
                logMessage("Error: One or both vectors not created.");
                continue;
            }
            if (vector1->type != vector2->type) {
                logMessage("Error: Cannot make vector product of different types.");
                continue;
            }
            if (vector1->size_of_vector != vector2->size_of_vector) {
                logMessage("Error: Vectors must have the same size for vector product.");
                continue;
            }
            Vector* result = vectorProduct(vector1, vector2);
            if (result) {
                logMessage("Vector product was made successfully.");
                deleteVector(result);
            } else {
                logMessage("Error: Vector product compilation failed.");
            }
        } else {
            logMessage("Error: Unknown command.");
        }
    }
    
    
if (vector1) {
    deleteVector(vector1);
}
if (vector2) {
    deleteVector(vector2);
}
fclose(inFile);

Vector* vector3 = createVector(getFloatFieldInfo());

addElement(vector3, float_(1.5));

toString(vector3);
return 0;
}
