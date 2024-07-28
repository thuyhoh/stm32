#include "string.h"
#include "stdint.h"
void str_emp(char* str){
	int i = 0;
	while(*(str + i) != '\0'){
		*(str + i) = '\0';
		i++;
	}
}

int str_len(char* str){
	int i = 0;
	while(str[i] != '\0'){
		i++;
	}
	return i;
}

int find_str(char* str_src,char *str_dest){
	int len_src = str_len(str_src), len_dest = str_len(str_dest);
	if(len_src > len_dest) return 0;
	int i;
	for(i = 0; i< (len_dest - len_src); i++){
		int j, count = 0;	
		for(j = 0; j < len_src; j++){
			if(str_dest[i+j] == str_src[j]){
				count++;
			}
			else{
				break;
			}
		}
		if(count == len_src - 1){
			return 1;
		}
	}
	return 0;
}

int same_str(char* str_src, char* str_dest){
	if((str_len(str_src) == str_len(str_dest)) && find_str(str_src,str_dest)) return 1;
	return 0;
}

void int_cvt_char(int nums, char* str_dest){
	char str_tmp[100];
	int cnt = 0;
	int div = 10;
	int j = 0;
	while(nums >= div){
		str_tmp[cnt] = nums % div + 0x30;
		nums /= 10;
		cnt++;
	}
	str_tmp[cnt] = nums + 0x30;
	for(j = cnt; j > 0; j--){
		str_dest[cnt - j] = str_tmp[j];
	}
}

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

