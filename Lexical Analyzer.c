#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int isKeyword(char buffer[]){
	char keywords[32][10] = {"auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while"};
	int i, flag = 0;

	for(i = 0; i < 32; ++i){
		if(strcmp(keywords[i], buffer) == 0){
			flag = 1;
			break;
		}
	}

	return flag;
}

int main(){
	char ch, buffer[15], operators[] = "+-*/%=><";
	FILE *fp;
	int i,j=0;

	fp = fopen("test.txt","r");

	if(fp == NULL){
		printf("error while opening the file\n");
		exit(0);
	}

	while((ch = fgetc(fp)) != EOF){
   		for(i = 0; i < 8; ++i){
   			if(ch == operators[i])
   				printf("%c is operator\n", ch);
   		}

   		if(isalnum(ch)){
   			buffer[j++] = ch;
   		}


   		else if((ch == ' ' || ch == '\n') && (j != 0)){
   				buffer[j] = '\0';
   				j = 0;

   				if(isKeyword(buffer) == 1)
   					printf("%s is keyword\n", buffer);
   				else{
                    int checked_constant = 1, c = 0;
                    while(buffer[c] != '\0'){
                        if(buffer[c] >= '0' && buffer[c] <= '9'){
                            checked_constant = 1;
                        }
                        else{
                            checked_constant = 0;
                            break;
                        }
                        c++;
                    }
                    if(checked_constant == 1){
                        printf("%s is constant\n", buffer);
                    }
                    if(checked_constant == 0){
                        printf("%s is indentifier\n", buffer);
                    }
   				}
   		}
   		else if(!isalnum(ch) && !(ch == ' ' || ch == '\n' || ch == '\t')){
            printf("%c is special symbol\n", ch);
   		}
	}

	fclose(fp);

	return 0;
}
