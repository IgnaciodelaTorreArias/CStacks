#include "linked.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

#define iterate(stack)  for(node* aux = stack->lista; aux != NULL; aux = aux->next)
Stack* newStack(){
    Stack* stack = malloc(sizeof(Stack));
    *stack = (Stack){.size = 0, .lista = NULL};
    return stack;
}
//Encapsula el valor mandado dentro de un nodo
static node* wrap(void* const val){
    node* newNode = malloc(sizeof(node));
    *newNode = (node){
        .cont = val,
        .next = NULL
    };
    return newNode;
}
//Retorna el indice en el cual se encuentra un puntero que apunta a la misma direccion de memoria del valor
size_t search(Stack* const stack, void* const valor){
    unsigned int index;
    iterate(stack){
        if (aux->cont == valor) return index;
        index++;
    }
    return stack->size+1;
}
//A diferencia del search simple este hace una revision de bytes en lugar de direccion de memoria
size_t searchValue(Stack* const stack, void* const valor, const size_t typeLen){
    char* buscado = valor;
    char* actualValue;
    unsigned char found = 0;
    size_t index = 0;
    iterate(stack){
        actualValue = aux->cont;
        found = 1;
        for (unsigned char i = 0; i < typeLen; i++){
            if(buscado[i] != actualValue[i]){ //Dangerous for a stack with contents of diferent types
               found = 0;
               break; 
            }
        }
        if(found)return index;
        index++;
    }
    return stack->size+1;
}
//Retorna el indice de la lista en el que se cumpla que el valor en el indice pasado a la funcion retorne True
size_t findByFunc(Stack* const stack, int (*func)(void*)){
    size_t indice = 0;
    iterate(stack){
        if(func(aux->cont))return indice;
        indice++;
    }
    return stack->size+1;
}
//Cambia el contenido de cada nodo al resultado de enviar su contenido a la funcion obtenida
void map(Stack* const stack, void* (*func)(void*)){
    iterate(stack)aux->cont = func(aux->cont);
}
//Pasa cada valor en el stack a la funcion obtenida
void forEach(Stack* const stack, void(*func)(void*)){
    iterate(stack)func(aux->cont);
}
//Encapsula el nuevo elemento en un nodo y lo añade al stack
void push(Stack* const stack, void* const contenido){
    node* newNode = wrap(contenido);
    newNode->next = stack->lista;
    stack->lista = newNode;
    stack->size++;
}
//Agrega los argumentosrecividos hasta encontrar un puntero a NULL
void pushArguments(Stack* const stack, ...){
    va_list ap;
    va_start(ap, stack);
    for(void* aux = va_arg(ap, void*); aux != NULL; aux = va_arg(ap, void*))push(stack, aux);
    va_end(ap);
}
//Agrega los valores en el orden en que se encuentra en la lista
//Hint: El tamaño de una lista se puede sacar con (sizeof(Lista) / sizeof(typeOfLista)) solo si se aplica donde se creo no cuando es pasada a una funcion
void pushLista(Stack* const stack, void* const valores[], const size_t sizeOfValores){
    if(sizeOfValores == 0)return;
    for(size_t i = 0; i < sizeOfValores; i++)push(stack, valores[i]);
}
//Extra el ultimo contenido del ultimo nodo añadido al stack
//Recordatorio: Liberar la memoria del puntero retornado
void* popP(Stack* const stack){
    if(stack->lista == NULL)return NULL;
    void* contenido = stack->lista->cont;
    node* temp = stack->lista->next;
    free(stack->lista);
    stack->lista = temp;
    stack->size--;
    return contenido;
}
//Extrae el contenido del nodo en el index
//Recordatorio: Liberar la memoria del puntero retornado
void* popPI(Stack* const stack, const size_t index){
    if(index > stack->size)return NULL;
    if(index < 1)return popP(stack);
    size_t i = 1;
    void* contenido;
    iterate(stack){
        if(i == index){
            contenido = aux->next->cont;
            node* temp = aux->next->next;
            free(aux->next);
            aux->next = temp;
            stack->size--;
            return contenido;
        }
        i++;
    }
    stack->size--;
    return contenido;
}
//Retorna el contenido del nodo en el index sin eliminarlo
//No liberar el puntero enviado
void* getP(Stack* stack, const size_t index){
    if(index > stack->size)return NULL;
    size_t i = 0;
    void* contenido;
    iterate(stack){
        if(i == index)contenido = aux->cont;
        i++;
    }
    return contenido;
}
//Elimina todos los elementos del stack
void clean(Stack* const stack){
    node* temp;
    for(node* aux = stack->lista;aux != NULL;aux = temp){
        temp = aux->next;
        free(aux->cont);
        free(aux);
    }
    stack->size = 0;
}
void destroy(Stack** const stack){
    clean(*stack);
    free(*stack);
    *stack = NULL;
}