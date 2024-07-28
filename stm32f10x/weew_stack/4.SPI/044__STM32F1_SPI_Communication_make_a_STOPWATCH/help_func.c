#include "help_func.h"


/* get the len of a string */ 

int str_len(char str[]){
	int len = 0;
	while(str[++len] != '\0');
	return (len - 1);
}

/* find a string on a string */
int find_str(char str1[], char str2[]){
	int match = 0;
	/*
	1 - first loop going through all the chars of str2
	2 - nested loop inside the first to go through the str1
	*/
	int strlen = str_len(str1);
	int i = 0;
	int j = 0;
	int test = 0;
	while((str2[i+strlen - 1] != '\0' | str2[i+strlen]!= '\0') & (match == 0)){
		for(j = 0; j <= strlen;j++){
			if(str1[j] == str2[i+j]){
				test++;
				if(test == strlen + 1){
					match = 1;
				}
			}
		}
		test = 0;
		i++;
	}
	
	
	return match;
}

int find_strL(char str1[], char str2[]){
	int result = 0;
	if((str_len(str1) == str_len(str2)) && find_str(str1,str2)){
		return 1;
	}
	return result;
}


// add 2 string in str1 
void Concatstr(char str1[], char str2[]){
	int i = 0;
	int j = 0;
	while(str2[i] != '\0'){
		i++;
	}
	while(str1[j] != '\0'){
		str1[i+j] = str2[j];
		j++;
	}
}


// convert int to char
void int_cvt_char(int num, char str[]){
	char lstr[30];
	int cnt = 0;
	int div = 10;
	int j = 0;
	while(num >= div){
		lstr[cnt] = num % div + 0x30;
		num /= 10;
		cnt++;
	}
	lstr[cnt] = num +0x30;
	for(j = cnt ; j>= 0; j--){
		str[cnt -j] = lstr[j];
	}
}

// convert char to int
int char_cvt_int(char str[]){
	int result = 0;
	int stop = 0;
	int strlen = str_len(str);
	int i = 0;
	char check[1];
	for(i = 0; i <= strlen;i++){
		check[0] = str[i];
		if(find_str(check,"123456789") == 0){
			stop = 1;
			break;
		}
	}
	if(stop == 0){
		for(i = 0;  i< str_len(str);i++){
			result = result*10+ (str[i] - 0x30);
		}
	}
	
	return result;
}

/* clear string*/

void str_empty(char str[]){
	int i = 0;
	while(str[i] != '\n'){
		str[i] = '\0';
		i++;
	}
}
