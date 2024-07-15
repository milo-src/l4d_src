#include "vector_management.h"

// Function for calling vector constructor
void VectorConstructorIterator(void* param_1, uint param_2, int param_3, _func_void_ptr_void_ptr* param_4) {
    void* pvVar1;

    if (param_2 != 0) {
        pvVar1 = param_1;
        do {
            (*param_4)(pvVar1, param_3);
            pvVar1 = (void *)((int)pvVar1 + param_3);
            param_2 = param_2 - 1;
        } while (param_2 != 0);
    }
}
