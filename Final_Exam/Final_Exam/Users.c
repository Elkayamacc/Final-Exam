/*-----------------------------------------------------------------------------------------------------------------
Name: Raz Elkayam                   Michael Davidov
id:   205634371						204332928
------------------------------------------------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "doubly_list.h"


//Count number of lines in the file
int countLines(char* filename)
{
	FILE* f = fopen(filename, "r");
	int c;
	int count = 0;
	if (!f)
		return -1;
	while ((c = fgetc(f)) != EOF)
		if (c == '\n')
			count++;
	fclose(f);
	return count;
}

// Compare between 2 strings if same return 1 if not return 0 
int strcompare(char* str1, char* str2) {
	int len_str1 = strlen(str1);
	int len_str2 = strlen(str2);
	if (len_str1 != len_str2)
		return 0;
	int tmp = 0;
	for (int i = 0; i < len_str1; i++) {
		tmp = tmp + (toupper(str1[i]) ^ toupper(str2[i]));
	}
	if (tmp == 0)
		return 1;
	else
		return 0;
}

//Push all the users in the file into array
void scan_all_users(char* path , user users_list[]){
	FILE* users;
	int NumberOfItems = countLines(path);
	users = fopen(path, "r");
	char tempTitle[52];
	fgets(tempTitle, 52,users );
	for (int i = 0; i < NumberOfItems; i++) {
			fscanf(users, "%15s%15s%20s%1d", &users_list[i].username, &users_list[i].password, &users_list[i].fullname ,& users_list[i].level );
	}
	fclose(users);
}


//Add user 
int add_user(char* path, user* users_list){
	system("cls");
	if (countLines(path) > MAX_USERS){
		printf("Cannot add more users (MAX LIMIT)\n");
		return 0;
	}
	FILE* users;
	users = fopen(path, "a+");
	int line_of_user = countLines(path)-1;
	insert_details(users_list, line_of_user);
	int num_of_users = line_of_user + 1;
	write_all_users(path, users_list ,num_of_users);
	fclose(users);
}

//Write the users to a file
void write_all_users(char* path, user users_list[], int num_of_users) {
	FILE* users;
	users = fopen(path, "w");
	char str[] = "UserName       Password       Full_Name           L\n";
	fputs(str, users);
	for (int i = 0; i <= num_of_users; i++) {
		if (num_of_users > i) {
			fprintf(users, "%-15s%-15s%-20s%-1d\n", users_list[i].username, users_list[i].password, users_list[i].fullname, users_list[i].level);
		}
	}
	fclose(users);
}

//Insert users details
void insert_details(user* users_list, int lines) {
	char username[15];
	insert_username(&username, lines);
	check_if_username_exist(&username, users_list, lines);
	strcpy(users_list[lines].username, username);
	printf("Please insert new password: (1-15 characters)\n");
	scanf("%s", &users_list[lines].password);
	printf("Please insert new Level (between 1-3):\n");
	scanf("%d", &users_list[lines].level);
	printf("Please insert new fullname: (1-20 characters no space)\n");
	scanf("%s", &users_list[lines].fullname);
}

void insert_username(char* username, int lines) {
	printf("Please, insert new username: (1-15 characters) \n");
	scanf("%s", username);
}

//Check if this user is already used
int check_if_username_exist(char* username, user* users_list, int lines) {
	int tmp = 0;
	for (int i = 0; i < lines; i++) {
		if (strcompare(username,users_list[i].username)!=0){
			tmp = tmp + 1;
		}
	}
	if (tmp == 0)
		return 1;
printf("The username is already exist, insert another username: \n");
scanf("%s", username);
check_if_username_exist(username, users_list, lines);
}

//delete user
int delete_user(user* users_list, char* path) {
	system("cls");
	char username[15];
	int j = 0, i = 0;
	printf("please insert username to delete:\n");
	scanf("%s", &username);
	int numberOfUsers = countLines(path)-1;
	if (countLines(path) == 2) {
		printf("Only 1 user... cannot delete\n");
		return 0;
	}
	for (i; i < numberOfUsers; i++) {
		if (!strcompare(username, users_list[i].username)) {
			users_list[j] = users_list[i];
			j++;
		}
	}
	write_all_users(path, users_list, j);
}


//Update user
int update_user(user* users_list, char* path) {
	system("cls");
	int number_of_users = countLines(path)-1;
	char username[15];
	printf("please insert username to update:");
	scanf("%s", &username);
	for (int i = 0; i < MAX_USERS; i++) {
		if (strcompare(username, users_list[i].username)) { //check if equal
			Choose_what_to_update(users_list, i , number_of_users);
			write_all_users(path, users_list, number_of_users);
			return 1;
		}
	}
	printf("This user name is not exist.. Please try again\n");
	update_user(users_list, path);
	return 0;
}

void Choose_what_to_update(user* users_list,int user_number, int number_of_users) {
	printf("Please Choose what to update:\n1.Username     2.Password     \n3.Level:       4.Fullname\nOption: ");
	int option;
	scanf("%d", &option);
	switch (option)
	{
	case 1: //username
	{
		printf("Please insert new username: \n");
		char username[15];
		scanf("%s", &username);
		if (username_to_update(username, users_list, number_of_users)) //Check if the username is exist
			strcpy(users_list[user_number].username, &username);
		printf("%s", users_list[user_number].username);
		break;
	}
	case 2: //password
	{
		printf("Please insert new password: \n");
		scanf("%s", users_list[user_number].password);
		break;
	}
	case 3: //level
	{
		printf("Please insert level: \n");
		int level;
		scanf("%d", &level);
		if (level <= 3)
			users_list[user_number].level = level;
		else
			printf("Wrong number of level");
		break;
	}
	case 4: //fullname
	{
		printf("Please insert fullname: ");
		scanf("%s", users_list[user_number].fullname);
		break;
	}
	default:
	{
		printf("Wrong number.. please try again\n");
		Choose_what_to_update(users_list, user_number , number_of_users);
		break;
	}
	}

}

int username_to_update(char* username, user* users_list, int lines) {
	int tmp = 0;
	for (int i = 0; i < lines; i++) {
		if (strcompare(username, users_list[i].username) != 0) {
			tmp = tmp + 1;
		}
	}
	if (tmp == 0)
		return 1;
	else {
		printf("User didnt found..");
		return 0;
	}
}

int user_login(char* items_path, list* mylist, char* users_path, user* users_list) {
	char username[15];
	char password[15];
	for (int i = 0; i < MAX_TRIES; i++) {
		read_users(&username, &password);
		if (validate_user(&username, &password, items_path , mylist, users_path, users_list)){
			return 1;
	}
		else
			printf("Wrong username or password \n");
	}
	printf("You have been wrong 3 times...");
	return 0;
}

//read the user
void read_users(char* username, char* password) {
	printf("Please insert username:\n");
	scanf("%s", username);

	printf("Please insert password:\n");
	scanf("%s", password);
}


int validate_user(char* username, char* password, char* items_path, list* mylist, char* users_path, user* users_list) {
	for (int i = 0; i < MAX_USERS; i++) {
		if (strcompare(username, users_list[i].username) == 1 && strcompare(password, users_list[i].password) == 1) { //check if equal
			if (users_list[i].level == 1){
				menuLevel1(items_path, mylist);
				return 1;
			}
			if (users_list[i].level == 2){
				menuLevel2(items_path, mylist);
				return 1;
			}
			if(users_list[i].level == 3){
				menuLevel3(items_path, mylist, users_path, users_list);
				return 1;
			}
		}
	}
	return 0;
}

void printUser(user* usersList, char* usersPath) {
	system("cls");
	int numberOfUsers = countLines(usersPath)-1;
	for (int i = 0; i < numberOfUsers; i++) {
		printf("Username: %s\n", usersList[i].username);
	}
}

