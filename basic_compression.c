#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<assert.h>

typedef struct{
    char* key;
    int count;

} Storage;

typedef struct{
    Storage * store;
    int capacity;  // current capacity of storage
    int total_cap;  // overall total capacity

} DictCompressor;

DictCompressor* initializer(int dictlen){
    DictCompressor * new_compressor = (DictCompressor *) malloc(sizeof(DictCompressor));
    Storage * new_storage = (Storage*) malloc(sizeof(Storage) * dictlen);
    // Storage* temp = new_storage;

    for (int i = 0; i < dictlen; i++){
        new_storage[i].key = NULL;
        new_storage[i].count = 0;
    }
    
    new_compressor->store = new_storage;
    new_compressor->capacity = 0;
    new_compressor->total_cap = dictlen;

    return new_compressor;
}

int hashing_function(DictCompressor* dictobj, const char * word){
    unsigned long hash = 0;
    int c;
    while (c = *word++){
        hash += c;
    }
    return hash % dictobj->total_cap;
}

int getter(DictCompressor * dictobj, const char* word){
    if (dictobj->capacity == 0) return -1;

    int ret_ind = hashing_function(dictobj, word);
    if (ret_ind >= dictobj->total_cap) return -1;
    Storage rcvd_word = dictobj->store[ret_ind];
    // printf("\n h-%d", dictobj->store[ret_ind].count);
    if (strcmp(word, rcvd_word.key) == 0) return dictobj->store[ret_ind].count;
    return -1;
}

int setter(DictCompressor * dictobj, const char*stream){
    Storage* array = dictobj->store;
    int store_ind = hashing_function(dictobj, stream);
    // printf("%d  - %s\n", store_ind, stream);
    // check for existing keys
    // printf("%d - %d", (dictobj->store[store_ind].count), (store_ind));
    if (dictobj->store[store_ind].key && (strcmp(dictobj->store[store_ind].key, stream) != 0)){
        // puts("failed");
        printf("%s -- %s\n", dictobj->store[store_ind].key, stream);
        // puts("failed");
        return -1;
    }
    // puts("reached");
    char * target_key = (char *) malloc(sizeof(char) * (strlen(stream) + 1));  // to adjust the \0 char
    strcpy(target_key, stream);

    dictobj->store[store_ind].key = target_key;
    dictobj->store[store_ind].count++;
    dictobj->capacity++;
    return 0;
    // perror("Word couldnt be added.");
}

DictCompressor * extract_and_set(const char * filename, int bfsz){
    DictCompressor * compressor = initializer(1000);
    
    // reading the file
    FILE * fptr;
    fptr = fopen(filename, "r");
    // char r = 'r' & string r or char * r = "r\0"
    if (fptr == NULL){
        perror("Invalid Text File.");
    }
    // char * buffer = (char*) malloc(sizeof(char) * initial_buffer_len);
    char buffer[bfsz];
    int buf_ptr = 0;

    while (fscanf(fptr, "%20s", buffer) != EOF){
        // puts(buffer);
        if (setter(compressor, buffer) != 0){
            puts("Error while parsing words.");
        }
    }
    fclose(fptr);
    return compressor;
}

int compress(const char * filename, int bfsz){
    DictCompressor* dictobj = extract_and_set(filename, bfsz);
    const char * tword = "of";
    printf("%d", getter(dictobj, tword));

}

int tester(){

}

int main(){
    srand(time(NULL));
    compress("testfile.txt", 20);
    // DictCompressor * compressor = initializer(1000);
    // const char word1[] = "Boobby";
    // if (setter(compressor, word1) == -1){
    //     puts("Word Not added");
    //     return -1;
    // }
    // puts("Word added");
    // return 0;
}