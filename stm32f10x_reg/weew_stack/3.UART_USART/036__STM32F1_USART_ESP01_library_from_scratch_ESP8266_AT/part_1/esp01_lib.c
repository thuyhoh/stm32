#include "uart_driver.h"
#include "help_func.h"
#include "esp01_lib.h"

// init function 
void esp_init(char UART3_msg[],unsigned short uart_3_mgr[],char UART2_msg[],unsigned short uart_2_mgr[])
{
	if(esp_master_cmd("AT\r\n","OK",0,0,UART3_msg,uart_3_mgr,1,"ESP01 is dectected","Detection failed"))
	{
		if(esp_master_cmd("AT+LICPSTATUS\r\n","STATUS: 2",1,0,UART3_msg,uart_3_mgr,1,"Connected to AP","Not connected to AP") == 0)
		{
			esp_net_auto_connect(UART3_msg,uart_3_mgr,Network,Password);
		}
		
			esp_menu();
	}else
	{
		UART_SEND(2,"\nSeclect the next step: \nD: Detect the ESP01\n");
	}
}

// menu setup function

/*
	\nthe ESP is Detected
	\nConnected to AP
	\nSelect the next step:
	\nM: Manual input ESP
	\nR: Reset
	\nL: List Networks
	\nP: Get IP address
	\nA: Automatic connetion using ssaved Network and password
	\nI: Input Network and Pass
	\nC: Check Network Connection
*/

void esp_setup(char USART_3_msg[],char USART_2_msg[],unsigned short uart_3_mgr[],unsigned short uart_2_mgr[])
{
	if(find_strL("D",USART_2_msg))
	{
		if(esp_master_cmd("AT\r\n","OK",0, 0, USART_3_msg, uart_3_mgr,1,"\nThe ESP is Detected\n","\nDetection failed\n"))
		{
		esp_menu();
		}
		else{UART_SEND(2,"\nSelect the next step: \nD: Detect the ESP01\n");}
	}
	else if(esp_master_cmd("AT\r\n","OK",0, 0, USART_3_msg, uart_3_mgr,0,"",""))
	{
		if(find_strL("M",USART_2_msg))
		{
			str_empty(USART_2_msg);
			uart_2_mgr[1] = 0;
			esp_man_mode(USART_3_msg,USART_2_msg,uart_3_mgr,uart_2_mgr);
		}
		else if(find_strL("R",USART_2_msg))
		{
			esp_master_cmd("AT+RESTORE\r\n","ready",0, 200, USART_3_msg, uart_3_mgr,1,"\nRestore succesful\n","\nRestore failed\n");
			esp_master_cmd("AT+CWMODE=1\r\n","OK",0, 0, USART_3_msg, uart_3_mgr,0,"","");
		}
		else if(find_strL("L",USART_2_msg))
		{
			esp_master_cmd("AT+CWLAP\r\n","OK",1,500, USART_3_msg, uart_3_mgr,1,"\nNetwork listed\n","\nscan failed\n");
		}
		else if(find_strL("A",USART_2_msg))
		{
			esp_net_auto_connect(USART_3_msg, uart_3_mgr, Network,Password);
		}
		else if(find_strL("I",USART_2_msg))
		{
			str_empty(USART_2_msg);
			uart_2_mgr[1] = 0;
			esp_net_manual_connect(USART_3_msg, uart_3_mgr, USART_2_msg,uart_2_mgr);
		}
		else if(find_strL("P",USART_2_msg))
		{
			esp_master_cmd("AT+CIFSR\r\n","OK",1,0, USART_3_msg, uart_3_mgr,0,"\n","\n");
		}
		else if(find_strL("C",USART_2_msg))
		{
			esp_master_cmd("AT+CIPSTATUS\r\n","STATUS:2",0,0, USART_3_msg, uart_3_mgr,1,"\nConnected to AP\n","\nNot connected\n");
		}
		else
		{
			UART_SEND(2,"\nThe input : \n");
			UART_SEND(2,USART_2_msg);
			UART_SEND(2,"\nis not an option in the Menu\n");
		}
		esp_menu();	
	}
	else
		{
			UART_SEND(2,"\nThe input : \n");
			UART_SEND(2,USART_2_msg);
			UART_SEND(2,"\nis not an option in the Menu\n");
		}
		uart_2_mgr[1] = 0;
		str_empty(USART_2_msg);
}


// menu display function

void esp_menu(void)
{
	UART_SEND(2,"\nthe ESP is Detected\nConnected to AP\nSelect the next step:\nM: Manual input ESP\nR: ResetnL: List Networks\nP: Get IP address\nA: Automatic connetion using ssaved Network and password\nI: Input Network and Pass\nC: Check Network Connection");
}



// send manual command to esp

void esp_man_mode(char USART_3_msg[],char USART_2_msg[],unsigned short uart_3_mgr[],unsigned short uart_2_mgr[])
{
	int keep = 1;
	UART_SEND(2,"\nStarting the manual input mode\n");
	UART_SEND(2,"\nQ: Quit manual mode\n");
	
	while(keep)
	{
		if(uart_2_mgr[1] == 1)
		{	
			if(find_strL("Q",USART_2_msg))
			{
				keep = 0;
			}
			else
			{
				Concatstr(USART_2_msg,"\r\n");
				UART_SEND(3,USART_2_msg);
				uart_2_mgr[1] = 0;
				str_empty(USART_2_msg);
			}
			
		}
		
		if(uart_3_mgr[1] == 1)
		{
			UART_SEND(2,USART_3_msg);
			uart_3_mgr[1] = 0;
			uart_3_mgr[5] = 10;
			str_empty(USART_3_msg);
		}
		
		
	}
	UART_SEND(2,"\nStotping the manual input mode\n");
}

// core esp01 function

int esp_core_cmd(char cmd[], char check_str[], short show, unsigned short int_time, char ESP_STR[], unsigned short ESP_mgr[] ){
	unsigned short result = 0;
	if(int_time){
		ESP_mgr[5] = int_time;
	}
	UART_MSG(3,cmd,ESP_mgr);
	if(show)
	{
		UART_SEND(2,ESP_STR);
	}
	
	if(find_str(check_str,ESP_STR)){
		result = 1;
	}
	str_empty(ESP_STR);
	return result;
}

// master esp01 function
int esp_master_cmd(char cmd[], char check_str[], short show, unsigned short int_time, char ESP_STR[], unsigned short ESP_mgr[],unsigned short show_msg, char success[], char fail[])
{
	int result = 0;
	if(esp_core_cmd(cmd,check_str,int_time,show,ESP_STR,ESP_mgr))
	{	
		if(show_msg)
		{
			UART_SEND(2,success);
			result = 1;
		}	
	}else
	{
		if(show_msg)
		{			
			UART_SEND(2,fail);
		}
	}
	return result;
}
// automatic connettion using saved networ and password

int esp_net_auto_connect(char ESP_STR[], unsigned short ESP_mgr[],char network[],char password[])
{
	char ESP_cmd[120] = "AT+CWJAP=\"";
	int result = 0;
	int connect = 0;
	Concatstr(ESP_cmd,network);
	Concatstr(ESP_cmd,"\",\"");
	Concatstr(ESP_cmd,password);
	Concatstr(ESP_cmd,"\"\r\n");
	connect += esp_master_cmd(ESP_cmd,"Connected",0,500,ESP_STR,ESP_mgr,1,"Connect Network","Not Connected");
	connect += 	esp_master_cmd("AT+CIPMUX=1\r\n","OK",1,0,ESP_STR,ESP_mgr,1,"","");
	connect += 	esp_master_cmd("AT+CIPSERVER=1,80\r\n","OK",1,0,ESP_STR,ESP_mgr,1,"","");
	result = (connect == 3)? 1:0;
	return result;
}

// input network and pass
int esp_net_manual_connect(char ESP_STR[], unsigned short ESP_mgr[],char USER_STR[],unsigned short USER_mgr[])
{
	char ESP_cmd[120] = "AT+CWJAP=\"";
	int result = 0;
	int connect = 0;
	UART_MSG(2,"\nInput the Network name: \n",USER_mgr);
	Concatstr(ESP_cmd,USER_STR);
	str_empty(USER_STR);
	Concatstr(ESP_cmd,"\",\"");
	
	UART_MSG(2,"\nInput the Network Password: \n",USER_mgr);
	Concatstr(ESP_cmd,USER_STR);
	str_empty(USER_STR);
	Concatstr(ESP_cmd,"\"\r\n");
	connect += esp_master_cmd(ESP_cmd,"Connected",1,500,ESP_STR,ESP_mgr,1,"Connect Network","Not Connected");
	connect += 	esp_master_cmd("AT+CIPMUX=1\r\n","OK",1,0,ESP_STR,ESP_mgr,1,"","");
	connect += 	esp_master_cmd("AT+CIPSERVER=1,80\r\n","OK",1,0,ESP_STR,ESP_mgr,1,"","");
	result = (connect == 3)? 1:0;
	return result;
}

