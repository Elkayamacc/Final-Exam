/*-----------------------------------------------------------------------------------------------------------------
Name: Raz Elkayam                   Michael Davidov
id:   205634371						204332928

													 Notes:
-Try not to insert full name with spaces
- in the items file if the day of the date start in the number 4, its instead of space , its an identify 
-------------------------------------------------------------------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "doubly_list.h"

#define path "D:\\Final_exam\\users.txt"
#define itemsPath "D:\\Final_exam\\items.txt"
#define loggerPath "D:\\Final_exam\\log.txt"


char* print_tm()
{
	time_t mytime = time(NULL);
	char* time_str = ctime(&mytime);
	time_str[strlen(time_str) - 1] = '\0';
	return time_str;
}

void LOGGER(char* action)

{
	char* tm = print_tm();
	FILE* fp = fopen(loggerPath, "a+");
	fprintf(fp, "LOG: occurred at :[%s] Details: %s\n", tm , action );
	fclose(fp);
}

void main() {

	//Check if there is a user file, if not create with the default user
	FILE* users;
	user users_list[MAX_USERS];
	users = fopen(path, "a+");
	if (countLines(path) == 0) {
		fprintf(users, "UserName       Password       Full_Name           L\nadmin          admin          System_Manager      3\n");
		fclose(users);  
	}

	scan_all_users(&path, users_list);
	list my_items_list;
	initList(&my_items_list);
	scan_all_items(&my_items_list, &itemsPath);
//	simulator(60, itemsPath); //Creates items - items simulator
	user_login(&itemsPath,&my_items_list, &path, users_list);

}

