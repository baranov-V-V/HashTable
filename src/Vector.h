#pragma once

#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

#include "Hash.h"

const int REALLOC_VALUE = 2;
const int INCREASE_LEVEL = 2;
const int DECREASE_LEVEL = 4;

/*!
Error codes
!*/
enum Error_t {
    SUCCESS        = 0,
    LENGTH_ERROR   = 1,
    PUSH_ERROR     = 2,
    TOP_ERROR      = 3,
    INCREASE_ERROR = 4,
    DECREASE_ERROR = 5,
    POP_ERROR      = 6,
    INSERT_ERROR   = 7,
    ERASE_ERROR    = 8
};

Vector* ConstructVector(int start_size);
size_t VectorSize(Vector* vector);
size_t VectorCapacity(Vector* vector);
Error_t VectorIncrease(Vector* vector);
Error_t VectorDecrease(Vector* vector);
Error_t PushBack(Vector* vector, Type_t value);
Type_t LastElem(Vector* vector);
Error_t PopBack(Vector* vector);
Error_t DestroyVector(Vector* vector);
Type_t GetElem(Vector* vector, int pos);
Error_t Insert(Vector* vector, Type_t value, int pos);
Error_t Erase(Vector* vector, int pos);
