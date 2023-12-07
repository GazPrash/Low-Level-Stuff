#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void error_insight(char* message, FILE* stream){
  if (message == "usage"){
    fprintf(stream, "Usage : ./mini_excel.exe <your_data.csv>\n");
  } else if (message == "file_read"){
    fprintf(stream, "Incorrect file path provided");
  }
  
}

char* file_reader(const char * filepath, size_t* file_size){
  char * buffer = 0;
  FILE* file = fopen(filepath, "rb");
  // I know goto statements are illegal but bare with me here // we doin this 90s stylee
  if (file == NULL){
    goto cleanup;
  }
  if (fseek(file, 0, SEEK_END) < 0){
    goto cleanup;
  }
  long bfsize = ftell(file);
  buffer = malloc(sizeof(char) * bfsize);
  if (buffer == NULL){
    goto cleanup;
  }
  if (fseek(file, 0, SEEK_SET) < 0){
    goto cleanup;
  }
  size_t n = fread(buffer, 1, bfsize, file);
  if (ferror(file)){
    goto cleanup;
  }
  if (file_size){
    *file_size = n;
  }

  fclose(file);
  return buffer;
  
cleanup:
  if (file){
    fclose(file);
  }
  if (buffer){
    free(buffer);
  }
  return 0;
}

char* parse_content(char* content_buffer){
  char *row = strtok(content_buffer, "\n");
  while (row != NULL) {
    // Tokenize columns based on comma
    char *columnA = strtok(row, ",");
    char *columnB = strtok(NULL, ",");

    // Process the columns (in this example, just print them)
    printf("Column A: %s, Column B: %s\n", columnA, columnB);

    // Move to the next row
    row = strtok(NULL, "\n");
  }
  return row;
}

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    // perror("CSV file not included!");
    error_insight("usage", stderr);
    fprintf(stderr, "Error : No data file is provided!\n");
    exit(1);
  }

  const char *csv_path = argv[1];
  // puts(csv_path);
  size_t file_size = 0;
  char * content = file_reader(csv_path, &file_size);
  if (content == NULL){
    error_insight("file_read", stderr);
    exit(1);
  }
  char* rows = parse_content(content);
  puts(rows);

  // fwrite(content, 1, file_size, stdout);
  
  return 0;
}