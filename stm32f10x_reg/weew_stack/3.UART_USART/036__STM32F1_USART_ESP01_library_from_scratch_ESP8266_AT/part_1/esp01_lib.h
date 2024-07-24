#define Network "thaothom"
#define Password ""

// int esp
void esp_init(char UART3_msg[],unsigned short uart_3_mgr[],char UART2_msg[],unsigned short uart_2_mgr[]);


// setup esp_menu 

void esp_setup(char USART_3_msg[],char USART_2_msg[],unsigned short uart_3_mgr[],unsigned short uart_2_mgr[]);



// setup menu display function
void esp_menu(void); 


// send manual command to esp
void esp_man_mode(char USART_3_msg[],char USART_2_msg[],unsigned short uart_3_mgr[],unsigned short uart_2_mgr[]);

// core esp01 function
int esp_core_cmd(char cmd[], char check_str[], short show, unsigned short int_time, char ESP_STR[], unsigned short ESP_mgr[] );

/*
	
*/


// master esp01 function
int esp_master_cmd(char cmd[], char check_str[], short show, unsigned short int_time, char ESP_STR[], unsigned short ESP_mgr[],unsigned short show_msg, char success[], char fail[]);

/*	
	esp_master_cmd("AT\r\n","OK",0,0,UART3_msg,uart_3_mgr,1,"ESP01 is dectected","Detection failed");
	esp_master_cmd("AT+RESTORE\r\n","Ready",1,10,UART3_msg,uart_3_mgr,1,"RESTORE is succesful","RESTORE failed");
	esp_master_cmd("AT+CUMODE=1\r\n","OK",0,0,UART3_msg,uart_3_mgr,1,"STATION MODE","STATION MODE FAILS");
	esp_master_cmd("AT+CWLAP\r\n","OK",1,50,UART3_msg,uart_3_mgr,1,"NetWork listed: ","scan failed");
	esp_master_cmd("AT+LICPSTATUS\r\n","STATUS: 2",1,0,UART3_msg,uart_3_mgr,1,"Connected to AP","Not connected to AP");
	esp_master_cmd("AT+CIPMUX=1\r\n","OK",1,0,UART3_msg,uart_3_mgr,1,"Multi connection enable","Muti connection fail");
	esp_master_cmd("AT+CIPSERVER=1,80\r\n","OK",1,0,UART3_msg,uart_3_mgr,1,"HTTP enable","HTTP failed");
	esp_master_cmd("AT+CIFSR\r\n","OK",1,0,UART3_msg,uart_3_mgr,1,"","");
*/

// automatic connettion using saved networ and password
int esp_net_auto_connect(char ESP_STR[], unsigned short ESP_mgr[],char network[],char password[]);

// input network and pass 
int esp_net_manual_connect(char ESP_STR[], unsigned short ESP_mgr[],char USER_STR[],unsigned short USER_mgr[]);



