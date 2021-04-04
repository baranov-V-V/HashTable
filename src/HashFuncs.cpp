#include "Hash.h"
#include "Vector.h"

void GetText(char* file_name, Text* text) {
    assert(file_name);
    assert(text);

    struct stat info = {};
    stat(file_name, &info);
    size_t file_length = info.st_size;

    FILE* fp = fopen(file_name, "r");
    assert(fp);

    text->text = (char*) calloc(file_length + 1, sizeof(char));
    assert(text->text);

    int obj_read = fread(text->text, sizeof(char), file_length + 1, fp);

    text->text[obj_read - 1] = '\0';
    text->length = obj_read;

    fclose(fp);
}

size_t GetLinesCount(Text* text) {
    assert(text);

    size_t lines_count = 0;

    for (int i = 0; text->text[i] != '\0'; i++) {
        if (text->text[i] == '\n') {
            lines_count++;
        }
    }

    //printf("lines: %d", lines_count + 1);
    return lines_count + 1;
}

void ParceText(Text* text) {
    assert(text);

    int curr_ident = 0;
    char* line_pointer = text->text;

    for(int i = 0; i < text->lines_count; ++i) {
        while(*(line_pointer + curr_ident) != '\n' && *(line_pointer + curr_ident) != '\0') {
            curr_ident++;
        }
        *(line_pointer + curr_ident) = '\0';

        char* sep_symb = strchr(line_pointer, ':');
        assert(sep_symb);

        *sep_symb = '\0';

        text->dict[i].key = line_pointer;
        text->dict[i].value = sep_symb + 2;

        line_pointer = line_pointer + curr_ident + 1;
        curr_ident = 0;
    }
}

void DumpText(Text* text) {
    assert(text);

    printf("Main text:\n%s\nEnd of main text\n", text->text);
    printf("len: %ld, lines_count: %ld\n", text->length, text->lines_count);

    printf("Parced nodes:\n");
    for (int i = 0; i < text->lines_count; ++i) {
        printf("[%d] key: <%s> value: <%s>\n", i, text->dict[i].key, text->dict[i].value);
    }
}

void DumpBucketSizes(HashTable* table, char* file_name) {
    assert(table);
    assert(file_name);

    FILE* fp = fopen(file_name, "w");
    assert(fp);

    char* buff = (char*) calloc(MAX_INT_LEN * table->size * 2, sizeof(char));
    assert(buff);

    char* buff_start = buff;

    buff += sprintf(buff, "BucketId,BucketSize\n");

    for (int i = 0; i < table->size; ++i) {
        buff += sprintf(buff, "%d,%ld\n", i, VectorSize(table->data + i));
    }

    fwrite(buff_start, buff - buff_start, sizeof(char), fp);

    //printf("<%s>", buff_start);

    fclose(fp);
}

void DumpBucketGraph(HashTable* table, char* file_name) {
    assert(table);
    assert(file_name);

    FILE* fp = fopen(file_name, "w");
    assert(fp);

    char* buff = (char*) calloc(MAX_INT_LEN * table->size * 2, sizeof(char));
    assert(buff);

    char* buff_start = buff;

    for (int i = 0; i < table->size; ++i) {
        buff += sprintf(buff, "%d ", i);
    }

    buff += sprintf(buff, "\n");

    for (int i = 0; i < table->size; ++i) {
        buff += sprintf(buff, "%ld ", VectorSize(table->data + i));
    }

    fwrite(buff_start, buff - buff_start, sizeof(char), fp);

    //printf("<%s>", buff_start);

    fclose(fp);
}

HashTable* ConstructFromFile(char* file_name, uint64_t (*HashFunc)(char* key)) {
    HashTable* table = ConstructTable(initial_size, HashFunc);

    Text text = {};
    GetText(file_name, &text);

    text.lines_count = GetLinesCount(&text);
    text.dict = (Node*) calloc(text.lines_count, sizeof(Node));
    assert(text.dict);

    ParceText(&text);

    //DumpText(&text);

    //printf("done1\n");
    for (int i = 0; i < text.lines_count; ++i) {
      //  printf("done[%d]\n", i);
        Insert(table, text.dict[i]);
    }
    //printf("done2\n");

    //DumpTable(table);

    return table;
}
