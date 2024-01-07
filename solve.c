#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
  int N=1000;
  int M=10000;
  
  int** data;
  data=(int**)malloc(sizeof(int*)*N);
  for(int i=0; i<N; i++){
    data[i]=(int*)malloc(sizeof(int)*M);
  }
  
  FILE *dataFile=fopen(argv[1], "r");
  if(dataFile==NULL){
    printf("can't open datafile\n");
    return -1;
  }
  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      data[i][j]=(int)fgetc(dataFile)-48;
    }
    int z=fgetc(dataFile);
  }
  fclose(dataFile);
  
  int P=50000;
  
  int* s;
  int* l;
  s=(int*)malloc(sizeof(int)*P);
  l=(int*)malloc(sizeof(int)*P);
  
  FILE *rangeFile=fopen(argv[2], "r");
  if(rangeFile==NULL){
    printf("can't open rangefile\n");
    return -1;
  }
  int p=0;
  for(; fscanf(rangeFile, "%d, %d\n",&s[p], &l[p]) != EOF;){
    p++;
  }
  fclose(rangeFile);

  int k=0;
  int* count;
  count=calloc(p, sizeof(int));

  while(k!=p){
    int i=1;
    while(i!=N){
      int j=0;
      for(j=l[k]; j<l[k]+s[k]; j++){
	if(data[0][j]!=data[i][j]){
	  break;
	}
      }
      if(j==l[k]+s[k]){
	count[k]++;
      }
      i++;
    }
    k++;
  }

  FILE *answerFile=fopen(argv[3], "w");
  if(answerFile==NULL){
    printf("can't open answerfile\n");
    return -1;
  }
  for(int i=0; i<p; i++){
    fprintf(answerFile, "%d, %d, %d\n",s[i], l[i], count[i]);
  }
  fclose(answerFile);

  return 0;
}
