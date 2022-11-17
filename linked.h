#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>

//Recorre la lista
#define iterate(stack)  for(node* aux = stack->lista; aux != NULL; aux = aux->next)
/*Para utilizar una funcion push con copia
    typedef struct{
        int ID;
        char *name;
    }Person;
    Person Juan = {.ID = 1,.name = "Juan"};
    int days = 27;
    Stack myStack = {0,NULL};
    { //Simple push
        copy(Person, Juan);
        push(&myStack, Copy_Juan);
    }
    { //n args push
        copy(Person, Juan);
        copy(int, days);
        pushArguments(&myStack, Copy_days, Copy_Juan);
    }
*/
//Caso de uso: -Para una funcion generadora de elementos
#define copy(T, val)    node* Copy_##val;{                              \
    T* aux_Ptr = malloc(sizeof(T));                                     \
    *aux_Ptr = val;                                                     \
    Copy_##val = wrap(aux_Ptr, sizeof(T));                              \
}                                                                   
#define dynamicCopy(T, val) T* Dynamic_##val = malloc(sizeof(T));   \
                            *Dynamic_##val = val;

#define popValueIndex(T, stack, index, var) {                       \
    node* aux = popStackNodeAtIndex(stack, index);                  \
    if(aux != NULL){                                                \
        var = *(T*)(aux->cont);                                     \
        free(aux->cont);                                            \
        free(aux);                                                  \
    }                                                               \
}

#define getValue(T, stack, index, var) {                            \
    node* aux = getStackNodeAtIndex(stack, index);                  \
    if(aux != NULL)var = *(T*)(aux->cont);                         \
}
#define changeValue(T, stack, index, newValue, typeSiz) {           \
    node* aux = getStackNodeAtIndex(stack, index);                  \
    if(aux != NULL){                                                \
        *(T*)(aux->cont) = newValue;                                \
        aux->typeSize = typeSiz;                                    \
    }                                                               \
}
//Convierte una lista de valores a una lista de nodos validos con memoria dinamica
#define transformList(T, originList, lenght) node* nodes_##originList[lenght];{\
    T* aux;                                                         \
    for(size_t i = 0; i<lenght; i++){                               \
        aux = malloc(sizeof(T));                                    \
        *aux = originList[i];                                       \
        nodes_##originList[i] = wrap(aux, sizeof(T));               \
    }                                                               \
}
#define removeStack(T, stack, index){                               \
    node *aux = popStackNodeAtIndex(stack,index);                   \
    free(aux->cont);                                                \
    free(aux);                                                      \
}

typedef struct node{
    size_t          typeSize;
    void*           cont;
    struct node*    next;
}node;
typedef struct{
    size_t size;
    node*   lista;
}Stack;

Stack* newStack();
node* wrap(void* const, const size_t);
void* unwrap(node* const);
//Busquedas
size_t search(const Stack* const, const void* const);
size_t searchValue(const Stack* const, const void* const, const size_t);

//More complex
size_t findByFunc(const Stack* const, int (*)(void*));
void forEach(const Stack* const , void(*)(void*));

//Adition functions based on pointers to elements
void pushNode(node** const, node* const);
void pushStack(Stack* const, node* const);
void pushArguments(Stack* const, ...);
void pushLista(Stack* const, node* const[], const size_t);

//Substraction  functions returning node pointers
node* popNode(node** const);
node* popNextNode(node** const);
node* popStackNode(Stack* const);
node* popStackNodeAtIndex(Stack* const, const size_t);
node* getStackNodeAtIndex(const Stack* const, const size_t);

void clearStack(Stack* const);
void destroyStack(Stack**);