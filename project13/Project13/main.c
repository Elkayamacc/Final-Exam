#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "doubly_list.h"

#define path "C:\\Users\\lab508\\Desktop\\final\\users.txt"
#define itemsPath "C:\\Users\\lab508\\Desktop\\final\\items.txt"
#define loggerPath "C:\\Users\\lab508\\Desktop\\final\\log.txt"


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
	fprintf(fp, "LOG: occurred at :[%s] Details: %s\n", tm, action);
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
	//		simulator(60, itemsPath); //Creates items - items simulator
	user_login(&itemsPath, &my_items_list, &path, users_list);

}

