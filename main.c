#include "vector.c"

int main(void){
    int a = 1;
    int b = 2;
    int c = 5;
    int d = 4;
    Vector* v1 = createVector(INT);
    addElement(v1,&a, INT);
    addElement(v1,&b, INT);
    Vector* v2 = createVector(INT);
    addElement(v2,&c, INT);
    addElement(v2,&d, INT);
    Vector* sum = addVectors(v1,v2);
    printVector(sum);
    scalarProduct(sum,v1);
    distVector(sum);
}