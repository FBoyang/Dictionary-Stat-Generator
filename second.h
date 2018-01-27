#ifndef first_h
#define first_h
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<limits.h>
#include<time.h>
struct node{

	int sIndex;
	int eIndex;
	int isWord;
	int prefix;
	int Occurrence;
	char* word;
	struct node *sibling;
	struct node *firstChild;
};

/*char* delims(){
*set the delims*

char *delim=malloc(sizeof(char)*80);
char temp[] = "\n,\t,\?,\a,\b,\f,\r,\v,1234567890`~!@#$%^&*()-_=+[{]}\"|';:></?'";
memcpy(delim,temp,strlen(temp)+1);
return delim;
}
*/


char* Word(FILE* Data){
	char* Word;
	char letter;
	int counter =0;
	int start;
	if(Data){
		letter = getc(Data);
		while(!isalpha(letter)){//find the first letter
			if((letter=getc(Data))==EOF){
				return NULL;
			}
		
		}
		while(isalpha(letter)){//find the range of word
			counter++;
			letter = getc(Data);
		}
		Word = (char*)malloc(sizeof(char)*counter+1);
		fseek(Data,-1*(counter+1),SEEK_CUR);
		for(start=0;start<counter;start++){
			Word[start]=tolower(getc(Data));
		}
		Word[start]= '\0';
		return Word;
	}

	else{
		return NULL;
	}
}


struct node* initialize(){
	struct node* Nnode = (struct node*)malloc(sizeof(struct node));
	/*Nnode->sIndex = 0;
	Nnode->eIndex=0;
	Nnode->isWord =0;
	Nnode->superWord =0;
	Nnode->Occurrence =0;
	Nnode->firstChild=NULL;	
	Nnode->sibling=NULL;
	Nnode->word = NULL;*/
	return Nnode;
}

/*char* toLowerCase(char* word){
	int count;
	for(count=0;count<strlen(word);count++){//transfer the taken to lowercase
			word[count]=tolower(word[count]);
	}
	return word;
}
*/			


struct node *Trie;
void readDict(FILE *dict_file){// Read the dictionary and arrange the words in a Trie
	//Trie ={0,0,0,0,0,NULL,NULL,NULL};

	Trie =initialize();

	/*int size;
	fseek(dict_file,0,SEEK_END);
	size = ftell(dict_file);
	fseek(dict_file,0,SEEK_SET);
	char content[size+1];
	fread(content,size+1,1,dict_file);

	char* delim=delims();
	char* tokens=strtok(content,delim);
	*/
	char* tokens= Word(dict_file);
	
/*	for(count=0;count<strlen(tokens);count++){//transfer the token to lowercase
		tokens[count]=tolower(tokens[count]);
	}*/	

	struct node*ptr = Trie->firstChild;
	int Index=0;
	while(tokens!=NULL){
	//clock_t begin =clock();
	//printf("%s\n", tokens);	
	if(Trie->firstChild==NULL){//if Trie is empty, add the new word as Trie's firstChild
		struct node* firstChild = (struct node*)malloc(sizeof(struct node));
		//firstChild = {0,strlen(tokens),1,0,0,tokens,NULL,NULL};
		firstChild->eIndex=strlen(tokens)-1;
		firstChild->isWord=1;
		firstChild->word = (char*)malloc(sizeof(char)*(strlen(tokens)+10));
		memcpy(firstChild->word,tokens,strlen(tokens)+1);
		//(firstChild->word) = tokens;
		//strncpy(firstChild->word,tokens,strlen(tokens));
		Trie->firstChild = firstChild;
		ptr=Trie->firstChild;
		}
	else{//check the character with ptr one by onei
		
		while(ptr!=NULL){
			
			for(Index=ptr->sIndex;Index<strlen(tokens)&&Index<ptr->eIndex+1;Index++){
				if(tokens[Index]!=ptr->word[Index]){
					if(Index==ptr->sIndex){//indicate the first characters are different, so go to sibling and check
						
						//if(ptr->sibling!=NULL)//ptr has sibling
							
							while(tokens[Index]>ptr->word[Index]){//no need to change alphabetical order
								if(ptr->sibling!=NULL){
								ptr=ptr->sibling;}
								else{
									break;
								}
							}
							if(tokens[Index]>ptr->word[Index]){//sibling is NULL
							struct node* NewSibling = initialize();
							NewSibling->eIndex = strlen(tokens)-1;
							NewSibling->isWord = 1;
							NewSibling->word = realloc(NewSibling->word,strlen(tokens)+10);
							memcpy(NewSibling->word,tokens,strlen(tokens)+1);
							ptr->sibling = NewSibling;
							ptr = NULL;
							break;
							}
							else if(tokens[Index]<ptr->word[Index]){//new sibling should be in the front
								struct node* NewSibling1 =(struct node*)malloc(sizeof(struct node));
								NewSibling1->word = realloc(NewSibling1->word,strlen(ptr->word)+10);//
								memcpy(NewSibling1->word,ptr->word,strlen(ptr->word)+1);
								NewSibling1->isWord = ptr->isWord;
								NewSibling1->sIndex = ptr->sIndex;
								NewSibling1->eIndex = ptr->eIndex;
								NewSibling1->sibling = ptr->sibling;
								NewSibling1->firstChild = ptr->firstChild;
								ptr->isWord=1;
								ptr->firstChild=NULL;
								ptr->sIndex = Index;
								ptr->eIndex = strlen(tokens)-1;
								ptr->word=realloc(ptr->word,strlen(tokens)+1);
								memcpy(ptr->word,tokens,strlen(tokens)+1);
								ptr->sibling = NewSibling1;
								ptr = NULL;
								break;
							}

							
							else{//first letter equal
								/*if(== ){
								struct node* NewC = (struct node*)malloc(sizeof(struct node));
								NewC->isWord = ptr->isWord;
								NewC->firstChild = ptr->firstChild;
								NewC->sIndex = Index+1;
								NewC->eIndex = ptr->eIndex;
								NewC->word = (char*)malloc(sizeof(char)*(strlen(ptr->word)+10));	
								memcpy(NewC->word,ptr->word,ptr->eIndex+1);

								ptr->isWord = 1;
								ptr->word = realloc(ptr->word,Index+10);
								memcpy(ptr->word,tokens,strlen(tokens)+1);
								ptr->eIndex = Index;
								ptr->firstChild = NewC;
								break;}*/
									Index=-1;
									continue;
								
							}	
						}
					
					else{//the different character exist in between 
						struct node *NewChild1=(struct node*)malloc(sizeof(struct node));
						

						struct node *NewChild2 =(struct node*)malloc(sizeof(struct node));
						

						//NewChild1=						
						NewChild1->sIndex = Index;
						NewChild1->eIndex=strlen(tokens)-1;
						NewChild1->isWord=1;
						NewChild1->word=(char*)malloc(sizeof(char)*(strlen(tokens)+10));
						memcpy(NewChild1->word,tokens,strlen(tokens)+1);
						
						NewChild2->sIndex=Index;
						NewChild2->eIndex=ptr->eIndex;
						NewChild2->isWord = ptr->isWord;
						NewChild2->word = (char*)malloc(sizeof(char)*(ptr->eIndex+10));
						memcpy(NewChild2->word,ptr->word,ptr->eIndex+1);
						ptr->isWord = 0;
							
						ptr->eIndex=Index-1;
						//NewChild 2 is the original word 
						char* substring =(char*)malloc(sizeof(char)*(ptr->eIndex+10));
						memcpy(substring,tokens,Index+1);
						ptr->word = (char*)malloc(sizeof(char)*Index +1);
											//update the word data in ptr, cut off the rest of the different string
						strncpy(ptr->word,substring,Index);
						/*decide which of the two children should be the firsChild based on the alphabetical order*/
						if((NewChild1->word)[Index]<NewChild2->word[Index]){//NewChild1 should be the firstChild
							struct node* temp = ptr->firstChild;
							ptr->firstChild=NewChild1;
							NewChild1->sibling = NewChild2;
							NewChild2->firstChild = temp;
						}
					
						else{//NewChild2 should be the firstChild
							struct node* temp2= ptr->firstChild;
							ptr->firstChild=NewChild2;
							NewChild2->firstChild = temp2;
							NewChild2->sibling = NewChild1;
						}	
		/*condition 1:token and ptr->word are the same
 * 		  condition 2:token is the superword of ptr->word
 * 		  condition 3:token is the prefix of ptr->word
 * 		  */
					}
				}
			

	
		}
	
	if(ptr!=NULL){
	  if(Index>=strlen(tokens)||Index>=ptr->eIndex+1){	
		if(strlen(tokens)>ptr->eIndex+1){//condition2
			if(ptr->firstChild!=NULL){
			
				ptr=ptr->firstChild;
				continue;
			}
			else{//if the string length exceed the existing one
				struct node *NewChild3 = (struct node*)malloc(sizeof(struct node));
				//NewChild3={(ptr->eIndex)+1,strlen(tokens),1,0,0,tokens,NULL,NULL};
				NewChild3->sIndex=ptr->eIndex+1;
				NewChild3->eIndex = strlen(tokens)-1;
				NewChild3->isWord=1;
				//NewChild3->superWord=0;
				//NewChild3->Occurrence = 0;
				NewChild3->word =(char*)malloc(sizeof(char)*(strlen(tokens)+10));
			
				memcpy(NewChild3->word,tokens,strlen(tokens)+1);
				//NewChild3->firstChild=NULL;
				//NewChild3->sibling=NULL;

					
				ptr->firstChild = NewChild3;
				break;

			
			}
		
		}
		else if(strlen(tokens)<ptr->eIndex+1){//condition3. Again, need to spit the word up
			struct node* temp3= ptr->firstChild;
			//ptr->isWord=1;
			struct node* NewChild4 = (struct node*)malloc(sizeof(struct node));
			//NewChild4 = {strlen(tokens),ptr->endIndex,ptr->isWord,0,0,ptr->word,NULL,NULL};
			NewChild4->sIndex = strlen(tokens);
			NewChild4->eIndex = ptr->eIndex;
			NewChild4->isWord = ptr->isWord;
			ptr->isWord=1;
			NewChild4->word = malloc(sizeof(char)*(NewChild4->eIndex+10));
			memcpy(NewChild4->word,ptr->word,NewChild4->eIndex+1);
			ptr->eIndex = strlen(tokens)-1;
			ptr->word = malloc(sizeof(char)*strlen(tokens)+10);
			NewChild4->firstChild = temp3;
			memcpy(ptr->word,tokens,strlen(tokens)+1);
			ptr->firstChild = NewChild4;
		}
		else{//two words are the same
			ptr->isWord = 1;
			break;
		}
	}

		}	
	}
	
	
	
	}
	ptr = Trie->firstChild;	
	//tokens=strtok(NULL,delim);
	tokens=Word(dict_file);
//	clock_t end =clock();
//	double time = (double)(end-begin)/CLOCKS_PER_SEC;
//	printf("this turn takes: %g\n",time);
	}
	return;
}

void update(struct node** ptr){//update all the child and sibling from this node
	if(*ptr==NULL){
		return ;
	}
	else{
		if((*ptr)->isWord==1){
		(*ptr)->prefix++;
		}
		//printf("%s prefix is %d\n",(*ptr)->word, (*ptr)->prefix);
		update(&((*ptr)->firstChild));
		update(&((*ptr)->sibling));
		}
		
	}
	

void matchStr(char* str){
	//printf("token is %s\n", str);
	if(Trie->firstChild==NULL){
		return;
	}
	else{
		struct node* ptr = Trie->firstChild;
		int count;
		for(count=ptr->sIndex;count<=(ptr->eIndex+1)&&count<strlen(str);count++){
		if(count==(ptr->eIndex+1)&&count<strlen(str)){
			ptr=ptr->firstChild;
			if(ptr){
				count = ptr->sIndex-1;
				continue;
			}
			else{
				return;
			}
		}

		else if(ptr->word[count]==str[count]){
				continue;
			}	

			else if(ptr->word[count]<str[count]){//not fully match
			
					ptr = ptr->sibling;
					if(ptr){
					count=ptr->sIndex-1;
					continue;	
					}
					else{//no match
						return;
					}
				}
			
			else{//the sibling is not possible to match
					return;
				}
		
			
		}
			
	
		if(ptr->eIndex+1==strlen(str)){

			if(ptr->isWord ==1){
			ptr->Occurrence++;
			}
			update(&(ptr->firstChild));
			return;
		}
		if(ptr->eIndex+1>strlen(str))  {
			if(ptr->isWord==1){
			ptr->prefix++;
			//printf("%s prefix is %d\n",ptr->word,ptr->prefix);
			}
			update(&(ptr->firstChild));
			return;
				
		}

			
			
		
			return;
		
		
				
	}
}

void traverse(FILE *file_name, struct node* Node){
	
	
	if(Node==NULL){
		return;
	}
	else{
		struct node* ptr;
		ptr= Node;
				if(ptr->isWord==1){
				fprintf(file_name,"%s %d %d\n",ptr->word,ptr->Occurrence, ptr->prefix);
			
				traverse(file_name,ptr->firstChild);
				traverse(file_name,ptr->sibling);
			}
			else{
				traverse(file_name,ptr->firstChild);
				traverse(file_name,ptr->sibling);
			}
		}
} 	

void Mfree(struct node*Node){
	if(Node==NULL){
		return;
	}

	else{
		Mfree(Node->firstChild);
		Mfree(Node->sibling);
		free(Node);
	}
}
int line_counter;

void printResult(){//open the nth output file and write content 
	FILE *out_file;
	char file_name[10];
	
	sprintf(file_name,"out%d.txt",line_counter);
	out_file = fopen(file_name,"w");
	if(out_file==NULL){
		printf("error\n");
		return;
	}

	traverse(out_file,Trie->firstChild);
	fclose(out_file);
	
}

#endif
