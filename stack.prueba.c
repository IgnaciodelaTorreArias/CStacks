#include <stdio.h>
#include <stdlib.h>
#include "linked.h"

static inline void printDataAsNumber(void* const value){
    printf("%i->", *(int*)value);
}
static inline void printStack(Stack* const stack){
    forEach(stack, printDataAsNumber);
    printf("\n");
}
int main(){ 
    Stack* data = newStack();
    int getVar;
    for(int i = 0; i<5; i++){
        copy(int, i)
        push(data, Copy_i);
    }
    {
        int a=33, b=66, c=99;
        copy(int, a) //Genera una variable copy que usamos para mandar al stack
        copy(int, b)
        copy(int, c)
        pushArguments(data, Copy_a, Copy_b, Copy_c, NULL);
    }
    {
        int list[] = {1115, 5111, 1515};
        size_t len = sizeof(list) / sizeof(int);
        transformList(int, list, len)
        pushLista(data, void_list, len);
    }
    printStack(data);
    
    popV(int,data, getVar)
    printf("Recover data is: %i\n", getVar);
    printStack(data);

    popVI(int,data, getVar,1)
    printf("Recover data is: %i\n", getVar);
    printStack(data);
    
    getV(int, data, getVar, 1)
    printf("Recover data is: %i\n", getVar);
    printStack(data);

    changeVI(int, data, 101, 1)//Cambia el 99 por 101
    printStack(data);

    destroy(&data);
    return 0;
}