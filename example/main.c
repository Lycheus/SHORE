#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct
{
  char fixed_str[6];
  char str[39];
}struct_temp;

const char* init_search(const char *string, int num, const char *string2, char* string3)
{
  //printf("init_search start\n");
  printf("%c\n", (unsigned char)string[4]);
  printf("%c\n", (unsigned char)string2[num]);
  printf("%c\n", (unsigned char)string3[num+1]);

  return &string2[num];
}

const char* arg8_foo(char** string0, int i0, char* string1, int i1, char* string2, int i2, char* string3, int i3, char* string4, int i4, char* string5, int i5, char* string6, int i6, char* string7, int i7)
 //void arg8_foo(char** string0, int i0, char* string1, int i1, char* string2, int i2, char* string3, int i3, char* string4, int i4, char* string5, int i5, char* string6, int i6)
//void arg8_foo(char** string0, int i0)
{
  //printf("arg8_foo start\n");
  printf("%s\n", string0[i0]); //abcdefg123
  printf("%c\n", string1[i1]); //m  //m
  printf("%c\n", string2[i2]); //y  //y
  printf("%c\n", string3[i3]); //o  //d
  printf("%c\n", string4[i4]); //e  //e
  printf("%c\n", string5[i5]); //q  //q
  printf("%c\n", string6[i6]); //g  //w
  printf("%c\n", string7[i7]); //w
  //add one nested struct return
  return string0[1];
  //return;
}


int main(int argc, char* argv[])  // ./main helloworld 5
{
  printf("main start\n");

  int temp = atoi(argv[2]); //w
  printf("%c\n", argv[1][temp]);

  printf("%d\n", temp);  //5
  printf("%s\n", argv[1]); //helloworld
  
  const char* return_str;
  //char* find_strings[] = {"abcdefg123", "lmnopqrst456", "wxyz789", "amontafish", NULL};
  char* find_strings[] = {"abcdefg123", "lmnopqrst456", "wxyz789", NULL};
  char* alphabet = "abcdefghijklmnopqrstuvwxyz";
  char* dyn_ptr = malloc(sizeof(char)*11);
  memcpy(dyn_ptr, find_strings[1], 9);
  memcpy(struct_temp.str, alphabet, strlen(alphabet)+1);

  return_str = arg8_foo(find_strings, 0, find_strings[1], 1, find_strings[2], 2, find_strings[1], 3, alphabet, 4, dyn_ptr, 5, struct_temp.str, 6, argv[1], atoi(argv[2]));
  //arg8_foo(find_strings, 0, find_strings[1], 1, find_strings[2], 2, struct_temp.str, 3, alphabet, 4, dyn_ptr, 5, argv[1], atoi(argv[2])); // helloworld 5
  //arg8_foo(find_strings, 0, find_strings[1], 1, find_strings[2], 2, struct_temp.str, 3, alphabet, 4, dyn_ptr, 5, argv[1], atoi(argv[2])); // helloworld 5
  printf("SUCCEED!: %s\n", return_str); //lmnopqrst456
  

  printf("main: __ctype_b_loc() = %p\n", __ctype_b_loc());
  
  int loc;
  char A = 'A';
  printf("isupper\n");
  loc = isupper(A);
  

  printf("dyn_ptr = %p\n", dyn_ptr);


  printf("kenny: copy struct\n");
  memcpy(struct_temp.str, alphabet, strlen(alphabet)+1);
  printf("kenny: copy dyn_ptr\n");
  memcpy(dyn_ptr, find_strings[1], 9);

  printf("alphabet: %c\n", struct_temp.str[19]);
  printf("dyn_ptr: %s\n", dyn_ptr);


  char* src_ptr[5];
  char* dst_ptr[5];
  for(int i = 0; i < 5; i++){
    src_ptr[i] = malloc(sizeof(char)*117);
    strcpy(src_ptr[i], "hello world\n");
  }

  memcpy(dst_ptr, src_ptr, sizeof(char*)*5);
  printf("%s\n", dst_ptr[1]);
  printf("%s\n", dst_ptr[3]);
  
  // large long long value passed to and return from functions
  // function with more than 8 args
  // realloc, calloc, strncpy wrapper test
  // ctype_b_loc (related to sjeng) fopen fgets wrapper test
  // csrw offset adjust
  // spilling test code in another function using __asm_inline
  
  const char* ret_ptr = init_search(find_strings[1], 2, find_strings[0], dyn_ptr);

  strcpy(dyn_ptr, find_strings[0]);
  
  printf("%c\n", (unsigned char)ret_ptr[2]); //e
  printf("%s\n", argv[1]); //helloworld
  printf("%s\n", dyn_ptr); //abcdefg123
  printf("%c\n", dyn_ptr[atoi(argv[2])]); //f

  char* clone_ptr = dyn_ptr;

  printf("clone_ptr:%s\n", clone_ptr);
  free(dyn_ptr);
  //printf("clone_ptr2:%s\n", clone_ptr); 
  //printf("clone_ptr2:%c\n", clone_ptr[1]); //test temporal safety
  
  return 0;
}
