/*-----------------------------------------------------------------------------------------------------------------
Name: Raz Elkayam                   Michael Davidov
id:   205634371						204332928
-----------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <ctype.h>
#define MAX_TRIES 3
#define MAX_USERS 4

void LOGGER(char* action);
//------------------------------------------------Tools Functions-------------------------------------------
int countLines(char* filename);  // count the number of lines in the text
int strcompare(char* str1, char* str2); // Compare between to strings (ignores if Lower or Upper) if 1 -same  0- different
void splitDate(int value, int* day, int* month, int* year); // take a value of date (int) and split it to day, month and year

/* simulator: 
        Simulates number of items to write to a file (Choose randomly fields to add)
		numberOfItems = number of items to insert to the file        itemsPath = path
*/
void simulator(int numberOfItems, char* itemsPath);
//----------------------------------------------- users functions-------------------------------------------

typedef struct user
{
	char username[15];
	char password[15];
	int level;
	char fullname[20];
}user;

void scan_all_users(char* path, user users_list[]); //Push all the users into array of users
int add_user(char* path, user* users_list);
void insert_details(user* users_list, int lines);
void insert_username(char* username, int lines);
int check_if_username_exist(char* username, user* users_list, int lines);
int delete_user(user* users_list, char* path);
void write_all_users(char* path, user users_list[], int num_of_users);
int update_user(user* users_list, char* path);
void Choose_what_to_update(user* users_list, int user_number, int number_of_users);
int username_to_update(char* username, user* users_list, int lines); //check what username to update
void read_users(char* username, char* password);
void printUser(user* usersList, char* usersPath);


//------------------------------------------- Items Functions: -----------------------------------------------
typedef struct items {
	int num;
	char color[10];
	char category[10];
	float price;
	int is_damaged;
	int date;
}items;

typedef items list_type;

typedef struct node
{
	list_type value;
	struct node* next;
	struct node* prev;
}node;

typedef struct list
{
	node* head;
	node* tail;
}list;


void scan_all_items(list* items_list, char* items_path);

void menuLevel1(char* items_path, list* mylist);

void menuLevel2(char* items_path, list* mylist);

void menuLevel3(char* items_path, list* mylist, char* users_path, user* users_list);

int searchItem(char* items_path, list* mylist);  

int search_by_1_text_field(list* mylist, int number_of_items); //Search by one textfield color or category

int ChooseType(list* mylist, char* tag, int number_of_items); //Choose if color or category

int validate_textfield(int numberOfItems, list* mylist, char* tag, char* type); // Check what color/category and print

int search_by_2_textfields(list* templist, int number_of_items); // Search by 2 text fields (if appears in one print)

int search_by_price(list* templist, int number_of_items); // Show all the items that smaller or equal to the price

int search_by_number(list* templist, int number_of_items); // Show all the items that smaller or equal to the number

int damagedOrNot(list* templist, int number_of_items); // Search by the field damaged item or not

int searchByDate(list* templist, int number_of_items); // Search by date 

int scanDate(int* value, char* type);  // Scan date from the user 

int compareList(list* templist, int day, int month, int year, int number_of_items); //Cheack if the date is smaller the the input

void printItem(items value); // Print the item with all the categorys

int user_login(char* items_path, list* mylist, char* users_path, user* users_list); 

int validate_user(char* username, char* password, char* items_path, list* mylist, char* users_path, user* users_list);
//Validate user and show the menu to choose

void add_item(list* mylist, char* itemsPath);

void writeAllItems(list* itemsList, int numberOfItems, char* itemsPath);// Write all the items into a file

void scanToList(list* mylist); // scan item to the list

int scanBool(items* tempItem); // scan if the item is damaged and validate the option

void stickDate(items* tempItem); // scan the date from the user

void update_item(list* itemsList, char* itemsPath);

void updateTextField(list* itemsList, int index, char* type);

int updateIsDamaged(list* itemsList, int index); // update if the item is damaged or not

void updateDate(list* itemsList, int index);

void updatePrice(list * itemsList, int index);

void deleteItem(list* mylist, char* itemsPath); // Delete item

//----------------------------------------------doubly Functions-----------------------------------------------

void initList(list* lst);

int isEmpty(list* lst);

int length(list* lst);

node* allocItem(list_type value);

node* getLinkByIndex(list* lst, int idx);

int insertFirst(list* lst, node* item);


int insertLast(list* lst, node* item);

int deleteLink(list* lst, node* link);

int deleteLast(list* lst);

int deleteFirst(list* lst);
