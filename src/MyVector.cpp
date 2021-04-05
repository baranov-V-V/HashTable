#include "Vector.h"

void VectorDump(Vector* vector, FILE* fp) {
    assert(vector);
    assert(fp);

    fprintf(fp, "adress of vector: [%p]\n", vector);
    fprintf(fp, "{\n    size = %ld\n    capacity = %ld\n", vector->size, vector->capacity);
    fprintf(fp, "    data adress: [%p]\n", vector->data);

    fprintf(fp, "   {\n");
    for (size_t i = 0; i < vector->size; i++) {
        fprintf(fp, "       *[%ld] = %d\n", i, vector->data[i]);
    }
    fprintf(fp, "   }\n}\n");

}

size_t VectorSize(Vector* vector) {
    assert(vector);
    return vector->size;
}

size_t VectorCapacity(Vector* vector) {
    assert(vector);
    return vector->capacity;
}

Error_t VectorIncrease(Vector* vector) {
    assert(vector);

    size_t old_capacity = vector->capacity;

    if (vector->capacity == 0) {
        vector->capacity = 1;
    }
    else if (vector->size == vector->capacity) {
        vector->capacity = vector->capacity * REALLOC_VALUE;
    }
    else {
        return INCREASE_ERROR;
    }

    vector->data = (Type_t*) realloc(vector->data, sizeof(Type_t) * vector->capacity);
    assert(vector->data);

    return SUCCESS;
}

Error_t VectorDecrease(struct Vector* vector) {
    assert(vector != NULL);

    if (vector->size > 0 && (float) vector->capacity / (float) vector->size >= (float) DECREASE_LEVEL) {
        vector->capacity = (int) vector->capacity / REALLOC_VALUE;

        vector->data = (Type_t*) realloc(vector->data, sizeof(Type_t) * vector->capacity);
        assert(vector->data);
    }

    return SUCCESS;
}

Vector* ConstructVector(int start_capacity) {
    assert(start_capacity >= 0);

    Vector* new_vector = (Vector*) calloc(1, sizeof(Vector));

    new_vector->size = 0;
    new_vector->capacity = start_capacity;

    new_vector->data = (Type_t*) calloc(start_capacity, sizeof(Type_t));

    return new_vector;
}

Error_t PushBack(struct Vector* vector, Type_t value) {
    assert(vector);

    if (vector->size == vector->capacity) {
        VectorIncrease(vector);
    }

    vector->data[vector->size++] = value;

    return SUCCESS;
}

Type_t LastElem(struct Vector* vector) {
    assert(vector);

    if (vector->size > 0) {
        return vector->data[vector->size - 1];
    }
}

Error_t PopBack(struct Vector* vector) {
    assert(vector);

    if (vector->size > 0) {
        vector->size--;
    }
    else {
        return POP_ERROR;
    }

    VectorDecrease(vector);

    return SUCCESS;
}

Error_t DestroyVector(struct Vector* vector) {
    assert(vector != NULL);

    vector->size = -1;
    vector->capacity = -1;

    free(vector->data);

    return SUCCESS;
}

Type_t GetElem(Vector* vector, int pos) {
    assert(vector);
    return vector->data[pos];
};

Error_t Insert(Vector* vector, Type_t value, int pos) {
    assert(vector);

    if (pos > vector->size - 1) {
        return INSERT_ERROR;
    } else {
        vector->data[pos] = value;
    }

    return SUCCESS;
};

Error_t Erase(Vector* vector, int pos) {
    assert(vector);
    assert(pos >= 0);

    if (pos > vector->size - 1) {
        return ERASE_ERROR;
    }

    for (size_t i = pos; i < vector->size - 1; ++i) {
        vector->data[i] = vector->data[i + 1];
    }

    vector->size--;

    VectorDecrease(vector);

    return SUCCESS;
}


