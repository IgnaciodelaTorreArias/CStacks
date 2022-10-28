#include <stdlib.h>
#include <stddef.h>
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
#define copy(T, val)    void* Copy_##val = malloc(sizeof(val));\
                        *((T*)Copy_##val) = val;
#define popV(T, stack, var) {                           \
    void* aux = popP(stack);                            \
    if(aux == NULL){                                    \
        printf("Theres is no data left on the stack");  \
    }else{                                              \
        var = *((T*)aux);                               \
        free(aux);                                      \
    }                                                   \
}
#define popVI(T, stack, var, index) {                   \
    void* aux = popPI(stack, index);                    \
    if(aux == NULL){                                    \
        printf("Theres is no data left on the stack");  \
    }else{                                              \
        var = *((T*)aux);                               \
        free(aux);                                      \
    }                                                   \
}
#define getV(T, stack, var, index) {                    \
    void* aux = getP(stack, index);                     \
    if(aux == NULL){                                    \
        printf("Index Error");                          \
    }else{                                              \
        var = *((T*)aux);                               \
    }                                                   \
}
#define changeVI(T, stack, newValue, index) {           \
    T* aux = getP(stack, index);                        \
    *aux = newValue;                                    \
}
#define transformList(T, originList, lenght) void* void_##originList[lenght];\
{                                                       \
    for(size_t i = 0; i<lenght; i++){                   \
        void_##originList[i] = malloc(sizeof(T));       \
        *(T*)void_##originList[i] = originList[i];      \
    }                                                   \
}

typedef struct node{
    void*           cont;
    struct node*    next;
}node;
typedef struct{
    size_t  size;
    node*   lista;
}Stack;

Stack* newStack();
static node* wrap(void* const);
//Busquedas
size_t search(Stack* const, void* const);
size_t searchValue(Stack* const, void* const, const size_t);

//More complex
size_t findByFunc(Stack* const stack, int (*func)(void*));
void map(Stack* const stack, void* (*func)(void*));
void forEach(Stack* const stack, void(*func)(void*));

//Adition functions based on pointers to elements
void push(Stack* const, void* const);
void pushArguments(Stack* const, ...);
void pushLista(Stack* const, void* const[], const size_t);

//Substraction  functions returning pointers
void* popP(Stack* const);
void* popPI(Stack* const, const size_t);
void* getP(Stack*, const size_t);

void clean(Stack* const stack);
void destroy(Stack** const stack);