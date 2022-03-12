#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 32
#define FLAG_LEN 64
#define KEY_LEN 8


void tweet_tweet() {
  char buf[32];
  FILE *f = fopen("flag.txt","r");
  if (f == NULL) {
    printf("'flag.txt' missing in the current directory!\n");
    exit(0);
  }
  fgets(buf,32,f);
  puts(buf);
  fflush(stdout);
}

char global_birdy[KEY_LEN];

void carry_bird_into_mine(void){
  FILE *canary_file = fopen("birdy.txt","r");

  if (canary_file == NULL){
    printf("Looks like the bird has left the server. -- Please let an admin know on Discord!");
    printf("If you\'re running this locally, you\'ll need a birdy of your own!");
    exit(0);
  }
  fread(global_birdy, sizeof(char), KEY_LEN, canary_file);
  fclose(canary_file);
  return;
}

void name_it(void){
  char canary[KEY_LEN];
  char buf[BUF_SIZE];
  char user_len[BUF_SIZE];


  int count;
  int x = 0;
  memcpy(canary, global_birdy, KEY_LEN);
  printf("How many letters should its name have?\n> ");
  
  while(x < BUF_SIZE){
    read(0, user_len+x, 1);
    if (user_len[x]=='\n') break;
    x++;
  }
  sscanf(user_len, "%d", &count);
  
  printf("And what\'s the name? \n> ");
  read(0,buf,count);
  
  if (memcmp(canary, global_birdy, KEY_LEN)) {
    puts("*** Stack Smashing Detected *** : Are you messing with my canary?!");
    exit(-1);
  }

  printf("Ok... its name is %s\n",buf);
  fflush(stdout);
}

int main(int argc, char** argv){
  carry_bird_into_mine();
  puts("Working in a coal mine is dangerous stuff. \nGood thing I\'ve got my bird to protect me. ");
  puts("Let\'s give it a name.\n... ");
  name_it();
  return 0;
}
