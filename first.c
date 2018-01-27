#include<stdio.h>
#include<stdlib.h>
#include"first.h"
#include<time.h>


int main(int argc, char** argv){
	
	if(argc!=2){
		printf("invalid input\n");
		return 0;
	}

	else{
		FILE *fPtr;
		fPtr = fopen(argv[1],"r");
		
		if(fPtr==NULL){
			printf("invalid input\n");
			return 0;
		}

		else{
			char dict[15];
			char data[15];
			int count=0;
			FILE *diction;
			FILE *Data;
			//char* delim =delims();	
			while(!feof(fPtr)){
				fscanf(fPtr,"%s %s\n", dict,  data);
				//strcat(dict,".txt\0");
				//strcat(data,".txt\0");
				diction = fopen(dict,"r");
				Data = fopen(data,"r");
				readDict(diction);

				count++;
				/*char* delimer = delims();
				int size;
				fseek(Data,0,SEEK_END);
				size = ftell(Data);
				fseek(Data,0,SEEK_SET);
				char string[size+1];
				fread(string,size+1,1,Data);
		*/
				//char* tokens=strtok(string,delimer);
				char* tokens = Word(Data);
				//count++;
				line_counter = count;
				//clock_t begin = clock();
				while(tokens!=NULL){
				//	tokens = toLowerCase(tokens);
					matchStr(tokens);
					tokens=Word(Data);
					//tokens = strtok(NULL,delim);
				}

				printResult();
				Mfree(Trie->firstChild);
				//clock_t end = clock();
				//double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
				//printf("traverse the data and match word takes%f\n",time_spent);
				fclose(Data);
				fclose(diction);
			}
	return 0;
		}
	}return 0;

}
				
