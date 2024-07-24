
/*
	1 - get the len of a string 
	2 - find a string on a string 
	3 - finding an exact string match
	4 - concatenate 2 strings
	5 - convert integer to string 
	6 - convert string to unsigned integer
*/
// get lenght of string
int str_len(char str[]);

// find string 1(str1) in string 2(str2)
int find_str(char str1[], char str2[]);

// check str1 == str2
int find_strL(char str1[], char str2[]);

// add two string 2 to string 1
void Concatstr(char str1[], char str2[]);

// convert number to char
void int_cvt_char(int num, char str[]);

// return number from converting string 
int char_cvt_int(char str[]);

// clear string 
void str_empty(char str[]);
