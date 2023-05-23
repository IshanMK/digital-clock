/*
 * E / 18 / 173
 * Kasthuripitiya K.A.I.M.
 * Digital Clock
 * Date - 04 / 09 / 21
 * */

#include <stdio.h>
#include <unistd.h> //for sleep function
#include <time.h>
#include <string.h>
#include <stdlib.h> //to clear the console
#include <signal.h>
//Background Colors

#define BGBLACK() printf("\x1b[40m")
#define BGRED() printf("\x1b[41m")
#define BGGREEN() printf("\x1b[42m")
#define BGYELLOW() printf("\x1b[43m")
#define BGBLUE() printf("\x1b[44m")
#define BGMAGENTA() printf("\x1b[45m")
#define BGCYAN() printf("\x1b[46m")
#define BGWHITE() printf("\x1b[47m")

//foreground colors

#define FGBLACK() printf("\x1b[30m")
#define FGRED() printf("\x1b[31m")
#define FGGREEN() printf("\x1b[32m")
#define FGYELLOW() printf("\x1b[33m")
#define FGBLUE() printf("\x1b[34m")
#define FGMAGENTA() printf("\x1b[35m")
#define FGCYAN() printf("\x1b[36m")
#define FGWHITE() printf("\x1b[37m")

//RESET ALL
#define RESET() printf("\x1b[0m")

#define CLEAR()   printf("\x1b[H\x1b[J")
#define NOBLINK() printf("\x1b[25m")
#define HIDECURSOR() printf("\x1b[?25l")
#define SHOWCURSOR() printf("\x1b[?25h")

//function prototypes
void gotoxy(int , int) ;
void zero(int , int) ;
void one(int , int) ;
void two(int , int) ;
void three(int , int) ;
void four(int , int) ;
void five(int , int) ;
void six(int , int) ;
void seven(int , int) ;
void eight(int , int) ;
void nine(int , int) ;
void colon(int , int) ;
void calldigit(int , int , int) ;
void printdigit(int digit_arr[5][6] , int x , int y) ;
void bgcolors(char []) ;
void fgcolors(char []) ;
void timeandDate(char str[]) ;
void other_option() ;
void h_option() ;
void invalidcolor(char []) ;
void simple(char []) ;
void inthandler(int) ;
//golbal arrays
int digit_arr[5][6] ;
int counter = 0 ;
char str[256] ;
char colorcheck[256] ;
char colorarray[256] ;
//main function
int main(int argc , char** argv){
	
	signal(SIGINT , inthandler) ;
	//define a color array
	char colors[][8] = {"red" , "green" , "yellow" , "blue" , "magenta" , "cyan" , "black" , "white"} ;
	
	//if the no of argumenst > 1
	if(argc > 1){

		for(int index = argc - 1 ; index >= 0 ; index--){
			//check the beginning of the arguments for "-c"
			if(strncmp(argv[index] , "-c" , 2) == 0){
				int c_location = index ; //find the c location
				//check the other arguments for "-h"
				for(int counter = argc - 1  ; counter >= 0 ; counter--){
					if(strncmp(argv[counter] , "-h" , 2) == 0){
						int h_location = counter ; //find the location of the h
						if(c_location < h_location){
							invalidcolor(argv[counter]) ; //if "-h" is after "-c"
							return 0 ;
						}
						else{
							h_option() ;
							return 0 ;
						}
					}
				}
				//check for other commands
				//check the other arguments also for "--"
				for(int counter = argc - 1 ; counter >= 0 ; counter--){
					if(strncmp(argv[counter] , "--" , 2) == 0){
						//if the position of "--" is before "-c"
						if(strlen(argv[counter]) == 2){ //if the sting length is also 2
							if(counter < index){
								strcpy(str , "white") ; //deafult clock will be loaded
								timeandDate(str) ;
							}
						}
						else if(strlen(argv[counter]) != 2){
							other_option() ; //if the string lenght > 2 , it will dispaly this message
							return 0 ;
						}
					}
				}
				//if the string length is 2
				if(strlen(argv[index]) == 2){
					
					//check whether if this is the last argument
					if(index == argc - 1){
						other_option() ;
						return 0 ;
					}
					//check the next argument is a valid color or not
					//copy the next argument to str
					strcpy(str , argv[index + 1]) ;
					
					//convert the whole string to simple
					simple(str) ;

					//check whether the string is a valid color
					int unmatch = 0 ; //for unmatching colors
					for(int i = 0 ; i < 8 ; i++){
						//int unmatch = 0 ; //for unmatching colors
						if(strcmp(colors[i] , str) == 0){
							strcpy(str , colors[i]) ;
							timeandDate(str) ;
							
						}
						else{
							unmatch++ ;
						}
						if(unmatch / 8 == 1){
							invalidcolor(str) ;
							return 0 ;
						}
					}	
				

				}
				//if the string length is greater than 2
				else if(strlen(argv[index]) > 2){
					
					//copy the current argument to str
					strcpy(str , argv[index]) ;

					//saving a new array starting from str[2]
					for(int i = 0 ; i < strlen(str) - 2 ; i++){
						colorarray[i] = str[i + 2] ;
					}
					colorarray[strlen(str)] = '\0' ;
					
					//convert the colorarray to simple
					simple(colorarray) ;

					//check whether the string is a valid color
					int unmatch = 0 ; //for unmatching colors
					for(int i = 0 ; i < 8 ; i++){
						if(strcmp(colors[i] , colorarray) == 0){
							strcpy(str , colors[i]) ;
							timeandDate(str) ;
						}
						else{
							unmatch++ ;
						}
						if(unmatch / 8 == 1){
							//if non of the colors are matched
							invalidcolor(colorarray) ;
							return 0 ;
						}
					}
				}	

			}
		}
		//if "-c" not found 
		//if it finds "-h"
		for(int index = argc - 1 ; index >= 0 ; index--){
			if(strncmp(argv[index] , "-h" , 2) == 0){
				h_option() ;
				return 0 ;
			}
		}
		
		//if the string contains "--"
		for(int index = argc - 1 ; index >= 0 ; index--){
			if(strncmp(argv[index] , "--" , 2) == 0){ //if the elements "--"
				//check for the string length
				if(strlen(argv[index]) == 2){
					strcpy(str , "white") ;
					timeandDate(str) ;
				}
				else if(strlen(argv[index]) != 2){
					other_option() ;
					return 0 ;
				}
			}
		}
		//if it contains only 1 hyphen
		for(int index = argc - 1 ; index >= 0 ; index--){
			if(strcmp(argv[index] , "-") == 0){
				strcpy(str , "white") ;
				timeandDate(str) ;
			}
		}
		//if there are no hyphens available the
		int nohyphens = 0 ; //args without hyphens 
		for(int index = argc - 1 ; index >= 0 ; index--){
			if(strncmp(argv[index] , "-" , 1) == 0){
				//if the next element is not a '-' / 'c' / 'h'
				//copyh the string to str
				strcpy(str , argv[index]) ;
				if((str[1] != '-') || (str[1] != 'h') || (str[1] != 'c')){
					other_option() ;
					return 0 ;
				}
			}
			else if(strncmp(argv[index] , "-" , 1) != 0){
				nohyphens++ ;
			}
			//if there are no argumenst without flags , then default clock will be loaded
			if(nohyphens / argc == 1){
				strcpy(str , "white") ;
				timeandDate(str) ;
			}
		} 
	}
	//if the no of arguments == 1
	else if(argc == 1){
		strcpy(str , "white") ;
		timeandDate(str) ;
	}
	return 0 ;
}

//================functions=====================
//convert to simple
void simple(char str[]){
	for(int i = 0 ; i < strlen(str) ; i++){
		if('A' <=str[i] && str[i] <= 'Z'){
			str[i] = str[i] + ('a' - 'A') ;
		}
	}
}
//function to print '0'
void zero(int x , int y){
	int digit_arr[5][6] = {
		{1,1,1,1,1,1} ,
		{1,1,0,0,1,1} ,
		{1,1,0,0,1,1} ,
		{1,1,0,0,1,1} ,
		{1,1,1,1,1,1}

	} ;
	printdigit(digit_arr , x , y) ;
}

//function to print 1
void one(int x, int y){
	int digit_arr[5][6] = {
		{0,0,0,0,1,1} ,
		{0,0,0,0,1,1} ,
		{0,0,0,0,1,1} ,
		{0,0,0,0,1,1} ,
		{0,0,0,0,1,1}

	} ;
	printdigit(digit_arr , x , y) ;

}

//function to print 2
void two(int x , int y){
	int digit_arr[5][6] = {
		{1,1,1,1,1,1} ,
		{0,0,0,0,1,1} ,
		{1,1,1,1,1,1} ,
		{1,1,0,0,0,0} ,
		{1,1,1,1,1,1}
	} ;
	printdigit(digit_arr , x , y) ;
}

//function to print 3
void three(int x , int y){
	int digit_arr[5][6] = {
		{1,1,1,1,1,1} ,
		{0,0,0,0,1,1} ,
		{1,1,1,1,1,1} ,
		{0,0,0,0,1,1} ,
		{1,1,1,1,1,1}
	} ;
	printdigit(digit_arr , x , y) ;
}

//function to print 4
void four(int x , int y){
	int digit_arr[5][6] = {
		{1,1,0,0,1,1} ,
		{1,1,0,0,1,1} ,
		{1,1,1,1,1,1} ,
		{0,0,0,0,1,1} ,
		{0,0,0,0,1,1}
	} ;
	printdigit(digit_arr , x , y) ;
}

//function to print 5
void five(int x , int y){
	int digit_arr[5][6] = {
		{1,1,1,1,1,1} ,
		{1,1,0,0,0,0} ,
		{1,1,1,1,1,1} ,
		{0,0,0,0,1,1} ,
		{1,1,1,1,1,1}
	} ;
	printdigit(digit_arr , x , y) ;
}

//function to print 6
void six(int x , int y){
	int digit_arr[5][6] = {
		{1,1,1,1,1,1} ,
		{1,1,0,0,0,0} ,
		{1,1,1,1,1,1} ,
		{1,1,0,0,1,1} ,
		{1,1,1,1,1,1}
	} ;
	printdigit(digit_arr , x, y) ;
}

//function to print 7
void seven(int x, int y){
	int digit_arr[5][6] = {
		{1,1,1,1,1,1} ,
		{0,0,0,0,1,1} ,
		{0,0,0,0,1,1} ,
		{0,0,0,0,1,1} ,
		{0,0,0,0,1,1}
	} ;
	printdigit(digit_arr , x, y) ;
}

//function to print 8
void eight(int x , int y){
	int digit_arr[5][6] = {
		{1,1,1,1,1,1} ,
		{1,1,0,0,1,1} ,
		{1,1,1,1,1,1} ,
		{1,1,0,0,1,1} ,
		{1,1,1,1,1,1}

	} ;
	printdigit(digit_arr , x , y) ;
}

//function to print 9
void nine(int x , int y){
	int digit_arr[5][6] = {
		{1,1,1,1,1,1} ,
		{1,1,0,0,1,1} ,
		{1,1,1,1,1,1} ,
		{0,0,0,0,1,1} ,
		{1,1,1,1,1,1}
	} ;
	printdigit(digit_arr , x , y) ;
}

//function to print colon
void colon(int x , int y){
	int digit_arr[5][6] = {
		{0,0,0,0,0,0} ,
		{0,0,1,1,0,0} ,
		{0,0,0,0,0,0} ,
		{0,0,1,1,0,0} ,
		{0,0,0,0,0,0}
	} ;
	printdigit(digit_arr , x, y) ;
}

//print a specifc digit at a specific position
void calldigit(int digit , int x , int y){
	if(digit == 0){
		//digit zero will be printed at (x , y) position of the console
		zero(x , y) ;
	}
	else if(digit == 1){
		//digit one will be printed at (x , y) position of the console
		one(x , y) ;
	}
	else if(digit == 2){
		//digit two will be printed at (x , y) position of the console
		two(x , y) ;
	}
	else if(digit == 3){
		//digit three will be printed at (x , y) position of the console
		three(x , y) ;
	}
	else if(digit == 4){
		//digit four will be printed at (x , y) position of the console
		four(x , y) ;
	}
	else if(digit == 5){
		//digit five will be printed at (x , y) position of the console
		five(x , y) ;
	}
	else if(digit == 6){
		//digit six will be printed at (x , y) position of the console
		six(x , y) ;
	}
	else if(digit == 7){
		//digit seven will be printed at (x , y) position of the console
		seven(x , y) ;
	}
	else if(digit == 8){
		//digit eight will be printed at (x , y) position of the console
		eight(x , y) ;
	}
	else if(digit == 9){
		//digit nine will be printed at (x , y) position of the console
		nine(x , y) ;
	}
}

//print the specific digit
void printdigit(int digit_arr[5][6] , int x , int y){
	for(int row_counter = 0 ; row_counter < 5 ; row_counter++){
		for(int col_counter = 0 ; col_counter < 6 ; col_counter++){
			gotoxy(x,y) ;
			if(digit_arr[row_counter][col_counter] == 1){
				bgcolors(str) ; //background color set
				printf(" ") ; //this psace will be highlighted with the background color
				RESET() ; //background color reset
			}
			else{
				printf(" ") ;//printing  a space
			}
			x++ ; //x coordinate in increasing
		}
		y++ ; //y coordinate also increasing
		x = x - 6 ; // after each loop x coordinate will be increased by 6 , so , it need to reset
		printf("\n") ; //after each loop a new line will be added
	}
}

//goto specific position
void gotoxy(int x , int y){
	//goto x , y coordinate on the console
	printf("%c[%d;%df", 0x1B, y, x);
}

//set background colors
void bgcolors(char str[]){
	if(strcmp(str , "black") == 0){
		BGBLACK() ; //set background black
	}
	else if(strcmp(str , "red") == 0){
		BGRED() ; //set background red
	}
	else if(strcmp(str , "green") == 0){
		BGGREEN() ; //set background green
	}
	else if(strcmp(str , "yellow") == 0){
		BGYELLOW() ; //set background yellow
	}
	else if(strcmp(str , "blue") == 0){
		BGBLUE() ; //set background blue
	}
	else if(strcmp(str , "magenta") == 0){
		BGMAGENTA() ; //set background magenta
	}
	else if(strcmp(str , "cyan") == 0){
		BGCYAN() ; //set background cyan
	}
	else if(strcmp(str , "white") == 0){
		BGWHITE() ; //set background white
	}
}

//set foreground colors
void fgcolors(char str[]){
	if(strcmp(str , "black") == 0){
		FGBLACK() ; //set foregound black
	}
	else if(strcmp(str , "red") == 0){
		FGRED() ; //set foreground red
	}
	else if(strcmp(str , "green") == 0){
		FGGREEN() ; //set foregorund green
	}
	else if(strcmp(str , "yellow") == 0){
		FGYELLOW() ; //set foreground yellow
	}
	else if(strcmp(str , "blue") == 0){
		FGBLUE() ; //set foreground blue
	}
	else if(strcmp(str , "magenta") == 0){
		FGMAGENTA() ; //set foreground magenta
	}
	else if(strcmp(str , "cyan") == 0){
		FGCYAN() ; //set foreground cyan
	}
	else if(strcmp(str , "white") == 0){
		FGWHITE() ; //set foreground white
	}
}
//time and date function
void timeandDate(char str[]){

    	while(1){
		//system("xterm") ;
    	    	time_t T = time(NULL) ;
		struct tm tm = *localtime(&T) ;

		HIDECURSOR() ;
		
		//clear the console
		//for unix based systems  , system("clear") will be used
		//for windows systems , system("cls") will be used
		system("clear") ; 
		//print the date
		gotoxy(23,8) ; //goto 23,8 position
		fgcolors(str) ;//set the foreground color
		printf("%02d-%02d-%02d\n" , tm.tm_year + 1900 , tm.tm_mon + 1 , tm.tm_mday) ;

		RESET() ; //reset to default color

		//digits of hours
		calldigit(tm.tm_hour / 10 , 2 ,2) ; //first digit of the 'hours'
		calldigit(tm.tm_hour % 10 , 9 ,2) ; //second digit of the 'hours'

		//print the colon
		colon(15,2) ;

		//digits of minutes
		calldigit(tm.tm_min / 10 , 21 , 2) ; //first digit of the 'minutes'
		calldigit(tm.tm_min % 10 , 28 , 2) ; //second digit of the 'minutes'

		//print the colon
		colon(34,2) ;

		//digits of seconds
		calldigit(tm.tm_sec / 10 , 40, 2) ; //first digit of the 'seconds'
		calldigit(tm.tm_sec % 10 , 47 , 2) ; //second digit of the 'seconds'

		gotoxy(0,9) ; //Goto this position to avoid overwritten
		printf("\n") ;
		sleep(1) ; //wait a second
		system("clear") ; //clear console
        }
}


//print error messages
void other_option(){
	printf("Invalid use of arguments.\n"
		"usage : clock -h                quick help on cmd\n"
		"usage : clock -c <color>        print clock with a color\n") ;
}

void h_option(){
	printf("usage : clock -h                quick help on cmd\n"
		"usage : clock -c <color>        print clock with a color\n"
		"<color-black|red|green|yellow|blue|magenta|cyan|white>  supported colors\n") ;
}

void invalidcolor(char str[]){
	printf("%s :This is not a valid color, Please enter one of these colours: black, red, green, yellow, blue, magenta, cyan, white\n" , str) ;
}

void inthandler(int dummy){
	SHOWCURSOR() ;
	system("clear") ;
	exit(1) ;
}
