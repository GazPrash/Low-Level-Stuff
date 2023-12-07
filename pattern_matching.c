#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>


bool match(const char * pattern, const char * text){

  while (*pattern != '\0' && *text != '\0'){
    switch (*pattern)
    {
    case '?'/* constant-expression */:
    {
      pattern++;
      text++;

    } break;
    case '*':
    {
      if (match(pattern+1, text)) return true;
      text++;
    } break;
    case '[':
    {
      // [abc]at   --   cat
      bool found_match = false;
      pattern++;
      if (*(pattern + 1) == '-'){
        if (*text >= *pattern && *text <= *(pattern+2)){
          pattern += 4;
          text++;
          break;
        }
      }
      while (*pattern != ']'){
        if (*pattern == '\0'){
          printf("Syntax Error!");
          return false;
        }
        if (*pattern == *text){
          found_match = true;
        }
        pattern++;
      }

      if (found_match){
        pattern++;
        text++;
      } else return false;
    } break;

    default:
      if (*pattern == *text){
        pattern++;
        text++;
      } else return false;
    }
  }
  if (*text == '\0'){
    while (*pattern == '*') pattern++;
    return (*pattern == '\0');
  }
  return false;
  // return (*pattern == '\0' && *text == '\0');
  // assert(0 && "TODO : Implement");
}

void compile_result(){

}

int main(){

  printf("%s\n", match("?at", "Cat") ? "true" : "false");
  printf("%s\n", match("??at", "Gyat") ? "true" : "false");
  printf("%s\n", match("?at", "at") ? "true" : "false");
  printf("%s\n", match("main.***", "main.cpp") ? "true" : "false");

  printf("%s\n", match("*at", "Cat") ? "true" : "false");
  printf("%s\n", match("*at", "Gyat") ? "true" : "false");
  printf("%s\n", match("*.js", "React.js") ? "true" : "false");
  printf("%s\n", match("main.*", "main.cxx") ? "true" : "false");
  printf("%s\n", match("*.*", "package.hpp") ? "true" : "false");

  printf("%s\n", match("main.[ch]", "main.c") ? "true" : "false");
  printf("%s\n", match("main.[ch]", "main.py") ? "true" : "false");
  printf("%s\n", match("main.[ch]pp", "main.hpp") ? "true" : "false");


  printf("%s\n", match("main.[c-h]pp", "main.hpp") ? "true" : "false");

  return 0;
}