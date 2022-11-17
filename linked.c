#include "linked.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define iterate(stack)  for(node* aux = stack->lista; aux != NULL; aux = aux->next)
Stack* newStack(){
    Stack* created = malloc(sizeof(Stack));
    *created = (Stack){.size = 0, .lista = NULL};
    return created;
}
//Encapsula el valor mandado dentro de un nodo
node* wrap(void* const val, const size_t typeSize){
    node* newNode = malloc(sizeof(node));
    *newNode = (node){
        .typeSize = typeSize,
        .cont = val,
        .next = NULL
    };
    return newNode;
}
void* unwrap(node* const Node){
    void* aux = Node->cont;
    free(Node);
    return aux;
}
//Retorna el indice en el cual se encuentra un puntero que apunta a la misma direccion de memoria del valor
size_t search(const Stack* const stack, const void* const valor){
    unsigned int index = 0;
    iterate(stack){
        if (aux->cont == valor) return index;
        index++;
    }
    return stack->size + 1;
}
//A diferencia del search simple este hace una revision de bytes en lugar de direccion de memoria
size_t searchValue(const Stack* const stack, const void* const valor, const size_t typeLen){
    const char* buscado = valor;
    char* actualValue;
    uint8_t found = 0;
    size_t index = 0;
    iterate(stack){
        if(aux->typeSize < typeLen || aux->typeSize > typeLen)continue; //Chequeo para evitar acceso a memoria que no nos pertenece
        actualValue = aux->cont;
        found = 1;
        for (uint8_t i = 0; i < typeLen; i++){
            if(buscado[i] != actualValue[i]){
               found = 0;
               break; 
            }
        }
        if(found)return index;
        index++;
    }
    return stack->size + 1;
}
//Retorna el indice de la lista en el que se cumpla que el valor en el indice pasado a la funcion retorne True
size_t findByFunc(const Stack* const stack, int (*func)(void*)){
    size_t indice = 0;
    iterate(stack){
        if(func(aux->cont))return indice;
        indice++;
    }
    return stack->size + 1;
}
//Pasa cada valor en el stack a la funcion obtenida
void forEach(const Stack* const stack, void (*func)(void*)){
    iterate(stack)func(aux->cont);
}
void pushNode(node** const origin, node* const contenido){
    contenido->next = (*origin);
    *origin = contenido;
}
void pushStack(Stack* const stack, node* const contenido){
    pushNode(&(stack->lista), contenido);
    stack->size++;
}
//Agrega los nodos recibidos como argumentos hasta encontrar NULL
void pushArguments(Stack* const stack, ...){
    va_list ap;
    va_start(ap, stack);
    for(node* aux = va_arg(ap, node*); aux != NULL; aux = va_arg(ap, node*))pushStack(stack, aux);
    va_end(ap);
}
//Agrega los valores en el orden en que se encuentra en la lista
//Hint: El tamaño de una lista se puede sacar con (sizeof(Lista) / sizeof(typeOfLista)) solo si se aplica donde se creo no cuando es pasada a una funcion
void pushLista(Stack* const stack, node* const valores[], const size_t sizeOfList){
    if(sizeOfList == 0)return;
    for(size_t i = 0; i < sizeOfList; i++)pushStack(stack, valores[i]);
}
node* popNode(node** const origin){
    node* aux = *origin;
    *origin = (*origin)->next;
    aux->next = NULL;
    return aux;
}
node* popNextNode(node** const origin){
    node* aux = (*origin)->next;
    (*origin)->next = (*origin)->next->next;
    aux->next = NULL;
    return aux;
}
//Extra el ultimo contenido del ultimo nodo añadido al stack
//Recordatorio: Liberar la memoria del puntero retornado
node* popStackNode(Stack* const stack){
    if(stack->lista == NULL)return NULL;
    stack->size-=1;
    return popNode(&(stack->lista));
}
//Extrae el contenido del nodo en el index
//Recordatorio: Liberar la memoria del puntero retornado
node* popStackNodeAtIndex(Stack* const stack, const size_t index){
    if(index > stack->size)return NULL;
    if(index < 1)return popStackNode(stack);
    size_t i = 1;
    iterate(stack){
        if(i == index){
            stack->size-=1;
            return popNextNode(&(aux));
        }
        i++;
    }
    return NULL;
}
//Retorna el contenido del nodo en el index sin eliminarlo
//No liberar el puntero enviado
node* getStackNodeAtIndex(const Stack* const stack, const size_t index){
    if(index > stack->size)return NULL;
    unsigned int i = 0;
    iterate(stack){
        if(i == index)return aux;
        i++;
    }
    return NULL;
}
//Elimina todos los elementos del stack
void clearStack(Stack* const stack){
    node* temp;
    for(node* aux = stack->lista;aux != NULL;aux = temp){
        temp = aux->next;
        free(aux->cont);
        free(aux);
    }
    stack->size = 0;
}
void destroyStack(Stack** stack){
    clearStack(*stack);
    free(*stack);
    *stack = NULL;
}