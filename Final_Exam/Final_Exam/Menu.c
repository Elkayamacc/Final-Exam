/*-----------------------------------------------------------------------------------------------------------------
Name: Raz Elkayam                   Michael Davidov
id:   205634371						204332928
------------------------------------------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "doubly_list.h"


void menuLevel1(char* itemsPath, list* mylist) {
	int option = 0;
	printf("0 - Search item\n1 - Add item\n9 - Exit\n");
	if (!choise(&option, 1))
		menuLevel1(itemsPath, mylist);
	switch (option)
	{
	case 0:
	{
		searchItem(itemsPath, mylist);
		break;
	}
	case 1:
	{
		add_item(mylist, itemsPath);
		break;
	}
	case 9:
	{
		return 0;
	}
	default:{
		printf("wrong number.. lets try again");
		menuLevel1(itemsPath, mylist);
		break;
	}
	}
	menuLevel1(itemsPath, mylist);
}

int choise(int* option, int premision) {
	printf("Option: \n");
	scanf("%d", option);
	if (*option <= premision || *option == 9)
		return 1;
	printf("wrong choise of number\n");
	return 0;
}

void menuLevel2(char* itemsPath, list* mylist) {
	int numberOfItems = countLines(itemsPath)-2;
	int option = 0;
	printf("0 - Search item\n1 - Add item\n2 - Update item\n3 - Delete item\n9 - Exit\n");
	if (!choise(&option, 3))
		menuLevel2(itemsPath, mylist);
	switch (option)
	{
	case 0:
	{
		if (!searchItem(itemsPath, mylist))
			break;
		update_item(mylist, itemsPath);
		writeAllItems(mylist, numberOfItems, itemsPath);
		break;
	}
	case 1:
	{
		add_item(mylist, itemsPath);
		break;
	}
	case 2:
	{
		update_item(mylist, itemsPath);
		break;
	}
	case 3:
	{
		deleteItem(mylist, itemsPath);
		break;
	}
	case 9:
	{
		return 0;
	}
	default:
		printf("Wrong number..\n");
		break;
	}
	menuLevel2(itemsPath, mylist);
}

void menuLevel3(char* itemsPath, list* mylist, char* users_path, user* users_list) {
	int numberOfItems = countLines(itemsPath)-2;
	int option;
	printf("0 - Search item\n1 - Add item\n2 - Update item\n3 - Delete item\n4 - Print all users\n5 - Add_user\n6 - Update_user\n7 - Delete_user\n9 - Exit\nOption: ");
	scanf("%d", &option);
	switch (option)
	{
	case 0:
	{
		if (!searchItem(itemsPath, mylist))
			break;
		update_item(mylist, itemsPath);
		writeAllItems(mylist, numberOfItems, itemsPath);
		break;
	}
	case 1:
	{
		add_item(mylist , itemsPath);
		break;
	}
	case 2:
	{
		update_item(mylist,itemsPath);
		break;
	}
	case 3:
	{
		deleteItem(mylist, itemsPath);
		break;
	}
	case 4:
	{
		printUser(users_list, users_path);
		printf("\n");
		break;
	}
	case 5:
	{
		add_user(users_path, users_list);
		break;
	}
	case 6:
	{
		update_user(users_list, users_path);
		break;
	}
	case 7:
	{
		delete_user(users_list, users_path);
		break;
	}
	case 9:
	{
		return 0;
	}
	default:
	{
		printf("Not an option, lets try again\n");
			break;
	}
	}
	menuLevel3(itemsPath, mylist, users_path, users_list);
}

void scan_all_items(list* items_list, char* itemsPath) { // scan all the items into a list
	int numberOfItems = countLines(itemsPath)-2;
	FILE* items_file;
	char temp[6];
	char tempTitle[53];
	items_file = fopen(itemsPath, "a+");
	fgets(tempTitle , 53, items_file);
	for (int i = 0; i < numberOfItems; i++) {
		items items_temp;
		fscanf(items_file, "%3s%10s%13s%1d%5c%8d%4c%f", &temp, &items_temp.color ,&items_temp.category, &items_temp.is_damaged, &temp ,&items_temp.date,&temp , &items_temp.price);
		if (items_temp.date > 40000000)               // There is a bag white the scanf he dosent get spaces, so the 4 to identify the date.
			items_temp.date = items_temp.date - 40000000;
		items_temp.num = i;
		insertLast(items_list, allocItem(items_temp));
	}
	fclose(items_file);
}

int searchItem(char* itemsPath, list *mylist) { // search item options
	system("cls");
	LOGGER("Search Items");
	int search_option;
	printf("Please choose an option:\n1 - Search by 1 text field\n2 - Search by 2 text fields\n3 - Search by price (shows all the items with the price below that)\n4 - Search by number\n5 - Damaged or not\n6 - Search By Date(Shows all the items with the date below that)\nOption: ");
	scanf("%d", &search_option);
	int numberOfItems = countLines(itemsPath)-2;
	switch (search_option) {
	case 1:
	{
		if(!search_by_1_text_field(mylist, numberOfItems))
			return 0;
		return 1;
	}
	case 2:
	{
		if(!search_by_2_textfields(mylist, numberOfItems))
			return 0;
		return 1;
	}
	case 3:
	{
		if(!search_by_price(mylist, numberOfItems))
			return 0;
		return 1;
	}
	case 4:
	{
		if(!search_by_number(mylist, numberOfItems))
			return 0;
		return 1;
	}
	case 5:
	{
		if(!damagedOrNot(mylist, numberOfItems))
			return 0;
		return 1;
	}
	case 6:
	{
		if (!searchByDate(mylist, numberOfItems))
			return 0;
		return 1;
	}
	default:
	{
		printf("Not exist type of search, probably wrong number\n");
		return 0;
	}
	}
}

//search by 1 option ,color or category
int search_by_1_text_field(list* mylist, int numberOfItems) {
	LOGGER("Search by 1 textfield");
	printf("What text field would you wanna search? \n1.Color\n2.Category\n");
	int option;
	scanf("%d", &option);
	char text_field[10];
	if (option == 1){
		strcpy(&text_field, "color");
		if(!ChooseType(mylist, &text_field , numberOfItems ))
			return 0;
		return 1;
	}
	if (option == 2) {
		strcpy(&text_field, "category");
		if(!ChooseType(mylist, &text_field, numberOfItems))
			return 0;
		return 1;
	}
	else{
		printf("Not an option please try again\n");
		search_by_1_text_field( mylist, numberOfItems);
	}
}

//tag = category or color
int ChooseType(list* mylist, char* tag, int numberOfItems) { 
	printf("What %s do you want to seach?\n", tag); 
	char type[10];  //type of category or color
	scanf("%s", &type);
	if (!validate_textfield(numberOfItems, mylist, tag, &type))
		return 0;
	return 1;
}


//if color print
int validate_textfield(int numberOfItems ,list* mylist ,char* tag ,char* type) {
	system("cls");
	int counter = 0;
	node* link = mylist->head;
	if (strcompare(tag, "color"))   
	{
		for (int i = 0; i < numberOfItems; i++) {
			if (strcompare(link->value.color, type)) {
				printItem(link->value); counter++;
			}
			link = link->next;
		}
	}
	if (strcompare(tag, "category")) //if category print
	{
		for (int i = 0; i < numberOfItems; i++) {
			if (strcompare(link->value.category, type)) {
				printItem(link->value); counter++;
			}
			link = link->next;
		}
	}
	free(link);
	if (!counter){
		printf("No resault.. \n");
		return 0;
	}
	return 1;
}

//search by 2 text fields
int search_by_2_textfields(list* mylist, int numberOfItems) {
	LOGGER("Search by 2 textfields");
	int counter = 0;
	char color[10];
	char category[10];
	node* link = mylist->head;
	printf("what color do you want to search?\n");
	scanf("%s", &color);
	printf("what category do you want to search?\n");
	scanf("%s", &category);
	system("cls");
	for(int i = 0 ; i<numberOfItems; i++){					//if the color or the category mach, print
		if (strcompare(link->value.category, &category) || strcompare(link->value.color, &color)){
			printItem(link->value);
			counter++;
		}
		link = link->next;
	}
	free(link);
	if (!counter){
		printf("No resault..\n");
		return 0;
	}
	return 1;
}

int search_by_price( list* mylist, int numberOfItems) {
	LOGGER("Search by price");
	float price; 
	int counter = 0;
	node* link = mylist->head;
	printf("Please insert price (Shows all the items with the price below that)\nPrice: ");
	scanf("%f", &price);
	for (int i = 0; i < numberOfItems; i++) {				// if the price is small or equal print
		if (link->value.price <= price){
			printItem(link->value);
			counter++;
		}
		link = link->next;
	}
	if (!counter) {
		printf("No resault..\n");
		return 0;
	}
	return 1;
	free(link);
}

//search by number of index
int search_by_number(list* mylist, int numberOfItems) {
	LOGGER("Search by number");
	int number;
	int counter = 0;
	node* link = mylist->head;
	printf("Please insert number: \n");
	scanf("%d", &number);
	for (int i = 0; i < numberOfItems; i++) {
		if (link->value.num == number) {			// if the number small or equal print
			printItem(link->value);
			counter++;
		}
		link = link->next;
	}
	free(link);
	if (!counter) {
		printf("No resault..\n");
		return 0;
	}
	return 1;
}

int damagedOrNot(list* mylist, int numberOfItems) {
	LOGGER("Damaged or not");
	int option;
	int counter = 0;
	node* link = mylist->head;
	printf("Damaged? \n1.Yes    2.No  \nOption: "); 
	scanf("%d", &option);
	if (option != 1 && option != 2) {
		printf("Not an answer.. try again\n");
		damagedOrNot(mylist, numberOfItems);
	}
										
	for (int i = 0; i < numberOfItems; i++) {						//Check the bool if damaged or not
		if (option == 1 && link->value.is_damaged == 1) {
			printItem(link->value);
			counter++;
		}
		if (option == 2 && link->value.is_damaged == 2) {
			printItem(link->value);
			counter++;
		}
		link = link->next;
	}
	free(link);
	if (!counter) {
		printf("No resault..\n");
		return 0;
	}
	return 1;
}

int searchByDate(list* mylist, int numberOfItems) { 
	LOGGER("Search by date");
	int day,month,year;
	validateDate(&day, &month, &year);
	if(!compareList(mylist, day, month, year , numberOfItems))
		return 0;
	return 1;
}


//Check if there is no more then 31 days 12 month and 2020 years
int validateDate(int* day, int* month, int* year){  
	if (!scanDate(day, "day")) {
		printf("There is no such day.. try again\n");
		validateDate(day, month, year);
	}
	if (!scanDate(month, "month")) {
		printf("There is no such month.. try again\n");
		validateDate(day, month, year);
	}
	if (!scanDate(year, "year")) {
		printf("There is no such year.. again\n");
		validateDate(day, month, year);
	}
}

//Scan and validate the day\month\year and them to value
int scanDate(int *value ,char *type) {    
	printf("Please insert the %s of the date\n", type);
	scanf("%4d", value);
	if (strcompare(type, "year") && *value <= 2020) {
		return 1;
	}
	if(strcompare(type, "month") && *value <= 12){
		return 1;
	}
	if (strcompare(type, "day") && *value <= 31) {
		return 1;
	}
	return 0;
}

//If the date is lower then the input date print
int compareList(list* mylist, int day, int month, int year, int numberOfItems) { 
	int list_day, list_month, list_year;
	int counter = 0;
	node* link = mylist->head;
	for (int i = 0; i < numberOfItems; i++)
	{	
		splitDate(link->value.date, &list_day, &list_month, &list_year);
		if (cheackDate(day, month, year, list_day, list_month, list_year)) {
			printItem(link->value);
			counter++;
		}
		link = link->next;
	}
	free(link);
	if (!counter) {
		printf("No resault... \n");
		return 0;
	}
	return 1;
}


// check if the date is lower then the input date   
// 1 - yes  2 - equal  3 - no 
int cheackDate(int day, int month, int year,int list_day,int list_month,int list_year) { 
	if (year > list_year) {
		return 1;
	}
	if (year == list_year)
	{
		if (month > list_month)
			return 1;
		if (month == list_month)
		{
			if (day > list_day)
				return 1;
			if (day == list_day)
				return 2;
		}
	}
	return 0;
}

void splitDate(int date, int* day, int* month, int* year) { //Split the date string into day, month ,year
	*day = date / 1000000;
	*month = date / 10000 - (*day) * 100;
	*year = date - (date / 10000) * 10000;
}

void printItem(items value) {  //Print the item
	char isdamaged[4];
	if (value.is_damaged == 1)
		strcpy(isdamaged, "yes");
	else
		strcpy(isdamaged, "no ");
	int day, month, year;
	splitDate(value.date, &day, &month, &year);
	printf("Num: %d , Color: %s , Category: %s , Price: %f , Is_damaged? %s , Date: %d.%d.%d\n\n", value.num , value.color, value.category, value.price, isdamaged, day, month, year);
}


void add_item(list* mylist, char* itemsPath) {
	system("cls");
	LOGGER("Add Item");
	scanToList(mylist);
	int numberOfitems = countLines(itemsPath)-1;
	writeAllItems(mylist , numberOfitems, itemsPath);
}

void scanToList(list* mylist) {   //scan items to list
	items tempItem;
	printf("Please insert color: \n");
	scanf("%10s", &tempItem.color);
	printf("Please insert category: \n");
	scanf("%10s", &tempItem.category);
	printf("Please insert price: \n");
	scanf("%f", &tempItem.price);
	scanBool(&tempItem);
	stickDate(&tempItem);
	tempItem.num = length(mylist);
	insertLast(mylist, allocItem(tempItem));
}

int scanBool(items* tempItem) { //Scan if damaged or not
	int option;
	printf("Is the item damaged? (scratch or with holes)\n1.Yes    2.No\nOption: ");
	scanf("%d", &option);
	if (option == 2 || option == 1) {
		tempItem->is_damaged = option;
		return 1;
	}
	else {
		printf("Wrong number.. try again\n");
		scanBool(tempItem);
	}
}

//stick the date to one int
void stickDate(items* tempItem) {
	int date , day, month, year;
	validateDate(&day, &month, &year);
	date = day * 1000000 + month * 10000 + year;
	tempItem->date = date;
}

//write all the items into a file
void writeAllItems(list* itemsList, int numberOfItems, char* itemsPath) {
	LOGGER("Write all items to the file");
	FILE* itemsFile;
	itemsFile = fopen(itemsPath, "w");
	char tempTitle[] = "N  Color     Category    Bool    Date        Float\n\n";
	node* link= itemsList->head;
	int temp_date;
	fputs(tempTitle, itemsFile);
	for (int i = 0; i < numberOfItems; i++) {
		if (link->value.date < 10000000)
			temp_date = link->value.date + 40000000;
		else
			temp_date = link->value.date;
		fprintf(itemsFile, "%-3d%-10s%-13s%-6d%-12d%f\n", link->value.num, link->value.color, link->value.category, link->value.is_damaged, temp_date, link->value.price);
		link = link->next;
	}
	fclose(itemsFile);
	free(link);
}


void update_item(list* itemsList , char* itemsPath) {
	LOGGER("Update item");
	int index;
	int option;
	int numberOfitems = countLines(itemsPath)-2;
	printf("What would you like to update?\n1.Color\n2.Category\n3.Is_damaged\n4.Date\n5.Price\n8.back\nOption: ");
	scanf("%d", &option);
	if (option < 6 && option != 0) {
		printf("Please enter the index of the item that you want to update: ");
		scanf("%d", &index);
	}

	system("cls");
	switch (option)
	{
	case 1:
	{
		updateTextField(itemsList, index, "color");
		break;
	}
	case 2:
	{
		updateTextField(itemsList, index, "category");
		break;
	}
	case 3:
	{
		updateIsDamaged(itemsList, index);
		break;
	}
	case 4:
	{
		updateDate(itemsList, index);
		break;
	}
	case 5:
	{
		updatePrice(itemsList, index);
		break;
	}
	case 8:
	{
		break;
	}
	default:{
		LOGGER("Exit error: Not an option of choose");
		printf("Not an option..\n");
		break;
	}
	}
	writeAllItems(itemsList, numberOfitems, itemsPath);
}

void updateTextField(list* itemsList , int index, char* type) {
	LOGGER("Update textfield");
	char textfield[10];
	printf("What %s would u like to update to?\n", type);
	scanf("%s", &textfield);
	if(strcompare(type, "color")){
		strcpy(getLinkByIndex(itemsList, index)->value.color, &textfield);
	}
	if (strcompare(type, "category"))
		strcpy(getLinkByIndex(itemsList, index)->value.category, &textfield);
}

int updateIsDamaged(list* itemsList, int index) {
	LOGGER("Update is_Damaged");
	int option;
	printf("Is damaged?\n1.Yes   2.No\n");
	scanf("%d", &option);
	if (option != 1 && option != 2) {
		printf("Wrong answer try again..\n");
		updateIsDamaged(itemsList, index);
	}
	getLinkByIndex(itemsList, index)->value.is_damaged = option;
}

void updateDate(list* itemsList, int index){
	stickDate(&getLinkByIndex(itemsList, index)->value);
}

void updatePrice(list* itemsList, int index) {
	float price;
	printf("Please enter a price you would update:    ");
	scanf("%f", &price);
	getLinkByIndex(itemsList, index)->value.price = price;
}

void deleteItem(list* mylist,char* itemsPath) {
	system("cls");
	printf("Please insert number of index to delete: ");
	int numberOfItems = countLines(itemsPath)-2;
	int index;
	scanf("%d", &index);
	node* link = mylist->head;
	if (!deleteLink(mylist, getLinkByIndex(mylist, index)))
		printf("Item is not exist");
	for (int i = 0; i < numberOfItems - 1; i++) {
		link->value.num = i;
		link = link->next;
	}
	free(link);
	writeAllItems(mylist,numberOfItems-1 , itemsPath);
}

void simulator(int numberOfItems,char* itemsPath) {
	list tempList;
	initList(&tempList);
	char* categoryArray[] = { {"shirt"},{"pants"},{"underwear"},{"socks"},{"sheet"},{"jacket"} };
	char* colorArray[] = { {"yellow"},{"green"},{"white"},{"black"},{"pink"} };
	float priceArray[] = { {13.33},{23},{4.5},{3.33},{20},{25.99} };
	items tempItem;
	int a , b;
	for(int i = 0; i < numberOfItems; i++) {
		a = rand() % 5;
		b = rand() % 30 + 1;
		if (b < 10)
			b = b + 40;
		tempItem.num = i;
		strcpy(tempItem.color , colorArray[rand() % 4]);
		strcpy(tempItem.category, categoryArray[a]);
		tempItem.date = (b)*1000000 + (rand() % 11 + 1) * 10000 + (rand() % 10 + 2010);;
		tempItem.is_damaged = rand() % 2 + 1;
		tempItem.price = priceArray[a];
		insertLast(&tempList, allocItem(tempItem));
	}
	writeAllItems(&tempList, numberOfItems, itemsPath);
}