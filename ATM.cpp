#include <stdio.h>
#include <conio.h>
#include <malloc.h>       //To Use Dynamic Memory Allocation
#include <stdbool.h>      //To Use Bolean Data Type
#include <stdlib.h>       //To Include All Basic Header Files
#include <string.h>       //To Use The String Functions
#include <iostream>       //To Use C++ Functions
#include <windows.h>      //To Slow The Output Screen
#include <time.h>         //To Slow The Output Screen
#include <unistd.h>       // for sleep function
#include <ctype.h>        //prints cash design
using namespace std;      // To Use C++ Functions
FILE *globalFile_pointer; // Global file Poiner
FILE *temp;    //Extra Pointer
long int globalbalance;    //extra variable
int loop = 1;             // A True Variable To Always Continue The Programme
struct card               // Structure Of Card
{
    long long int Card_no;
    int card_pin;
    int card_exmonth;
    int card_exyear;
    long int card_balance = 1000;
    char name[50];
};
struct card *globalCard_data = (struct card *)malloc(sizeof(struct card)); // A Card Type global Variable To take The Users Data From Database To Programme
struct card *temp_data = (struct card *)malloc(sizeof(struct card)); // A Extra Card Type global Variable To take The Users Data From Database To Programme
int user_number() // Read The Number Of User From "users.txt"
{
    FILE *fp;
    fp = fopen("users.txt", "r");
    int a;
    fscanf(fp, "%d", &a);
    a++;
    int temp = a;
    return temp;
}
int count_number(long long int n) // Count Any Number
{
    int i = 0;
    while (n > 0)
    {
        n /= 10;
        i++;
    }
    return i;
}
bool count(int n) // Count the Length Of Card Pin Is Four Or Not While Password is Created by User
{
    int i = 0;
    while (n > 0)
    {
        n /= 10;
        i++;
    }
    if (i == 4)
    {
        return true;
    }
    else
    {
        return false;
    }
};
void Insert_data(int n, char name[50], long long int number, int pass, int ex_m, int ex_y, long int balance) // it Inserts The new Card Details Into the Database Called "data.txt"
{
    FILE *fp;
    fp = fopen("data.txt", "a");
    rewind(fp);
    fprintf(fp, "%d %s %lld %d %d %d %ld\n", n, name, number, pass, ex_m, ex_y, balance);
    fclose(fp);
}
int set_password() // when A Card Is Created It Generate The Card Password
{
    int user_pin, user_pin2;
    int yes = 1;
    while (yes < 4)
    {
        printf("\nCreat Password(4 Digit):");
        scanf("%d", &user_pin);
        printf("Confirm Password(4Digit):");
        scanf("%d", &user_pin2);
        if (user_pin == user_pin2 && count(user_pin))
        {
            return user_pin;
            yes = 4;
        }
        else
        {
            yes++;
            printf("\n...Password Not Matched Or Should Be Four Digit...\n");
        }
    }
    loop = 0;
    printf("\n....Time Out Try Again....\n");
    return 0;
}
long long int replaceLastFourDigits(long long int baseNumber, int sequence) // It Replace The Last Four Digit Of Card By Number Of Card or By The User Of Cards
{
    long long int newNumber = (baseNumber / 10000) * 10000 + sequence;
    return newNumber; 
}
long long int creaat_card_no() // when A Card Is Created It Generate The Card Number
{
    FILE *fp;
    int card_no[12];
    srand(time(0));
    for (int i = 0; i < 12; i++)
    {
        card_no[i] = (rand() % 10);
    }
    int a = user_number();
    long long int aa = 0;
    for (int i = 0; i < 12; i++)
    {
        aa += card_no[i];
        aa *= 10;
    }
    card_no[8] = 0;
    card_no[9] = 0;
    card_no[10] = 0;
    card_no[11] = 0;
    aa = replaceLastFourDigits(aa, a);
    return aa;
}
int set_month() // when A Card Is Created It Generate The Expiry Month Of Card
{
    int month;

    int yes = 1;
    while (yes < 4)
    {
        printf("Birth Month:");
        scanf("%d", &month);
        if (month >= 1 && month <= 12)
        {
            yes = 4;
            if (month <= 2)
            {

                return month;
            }
            else if (month == 11 || month == 12)
            {
                month -= (3 + month % 10);
                return month;
            }
            else
            {
                month -= 2;
                return month;
            }
        }
        else
        {
            yes++;
            printf("\n....Month should be between 1 to 12....\n");
        }
    }
    loop = 0;
    printf("\n....Time Out Try Again....\n");
    exit(1);
    return 0;
}
int set_year() // when A Card Is Created It Generate The Expiry year Of Card
{
    int year;
    int yes = 1;
    while (yes < 4)
    {
        printf("Birth Year:");
        scanf("%d", &year);
        if (count(year) && (year >= 1920 && year <= 2017))
        {

            year += 20;
            year = 2024 + 20;
            return year;
            yes = 4;
        }
        else
        {
            yes++;
            printf("\n....year should be between 1920 to 2017....\n");
        }
    }
    loop = 0;
    printf("\n....Time Out Try Again....\n");
    exit(1);
    return 0;
}
int last_digits(long long int n) // It Returns The Last Four Digit Of Card
{
    int last_digits = 0;
    for (int i = 0; i <= 3; i++)
    {
        int rem = n % 10;
        last_digits = last_digits * 10 + rem;
        n = n / 10;
    }
    return last_digits;
}
void generated() // When A New Card Genarets It Update The Number Of Users In "users.txt"
{
    FILE *fp;
    fp = fopen("users.txt", "r");
    int a;
    fscanf(fp, "%d", &a);
    a++;
    fclose(fp);
    fp = fopen("users.txt", "w");
    fprintf(fp, "%d", a);
    char de[10] = "Default 0";
    fprintf(fp, "\n%s", de);
    fclose(fp);
}
int get_cardPass_database(FILE *fp, struct card *data) // It Read The Card Pin From Database
{
    int st_no;
    int card_pass = 0;
    for (int i = 0; i < 4; i++)
    {
        st_no = (fgetc(fp) - '0');
        card_pass += st_no;
        card_pass *= 10;
    }
    card_pass /= 10;
    data->card_pin = card_pass;
    return 0;
}
int read_nameFrom_database(FILE *fp, struct card *data) // It Read The Name From Database
{
    char ch, name[50];
    int st_no = 0;
    int name_len = 0;
    fscanf(fp, "%d", &name_len);
    ch = fgetc(fp);
    for (int i = 0; i < name_len; i++)
    {
        name[i] = fgetc(fp);
    }
    name[name_len] = '\0';
    ch = fgetc(fp);
    strcpy(data->name, name);
    return name_len;
}
int getCardNo_database(FILE *fp, struct card *data) // It Read The Card No From Database
{
    int st_no;
    long long int card_no = 0;
    for (int i = 0; i <= 12; i++)
    {
        st_no = (fgetc(fp) - '0');
        // printf("%d\n",st_no);
        card_no += st_no;
        card_no *= 10;
    }
    card_no /= 10;

    data->Card_no = card_no;
    return 0;
}
int getcardExmonth_database(FILE *fp, struct card *data) // It Read The Card Expiry Month From Database
{
    data->card_exmonth = (fgetc(fp) - '0');
    return 0;
}
int get_cardExyear_database(FILE *fp, struct card *data) // It Read The Card Pin From Database
{
    int st_no;
    int Ex_year = 0;
    for (int i = 0; i < 4; i++)
    {
        st_no = (fgetc(fp) - '0');

        Ex_year += st_no;
        Ex_year *= 10;
    }
    Ex_year /= 10;
    data->card_exyear = Ex_year;
    return 0;
}
int getCardBalance_database(FILE *fp, struct card *data) // It Read The Card Balance From Database
{
    fscanf(fp, "%ld", &data->card_balance);
    return 0;
}
int Onestep_forward(FILE *fp) // take file pointer one step forward
{
    char ch;
    ch = fgetc(fp);
    return 0;
}
void data_address(int n, FILE *fp, struct card *data) // It Move The File Poiner To The Correct Location To Get The User Inputed Card details
{
    char buffer[100];
    int line = 1;
    if (n > 1)
    {

        while (fgets(buffer, sizeof(buffer), fp))
        {

            line++;
            if (line == n)
            {

                break;
            }
        }
    }
}
void cardGenerating() // Display A Generating Card Before Card Created Time Laps
{
    printf("\n");
    time_t start_time, current_time;
    double elapsed_time;
    const char *status[] = {"Generating Card.", "Generating Card..", "Generating Card...", "Generating Card....", "Generating Card....."};
    // Get the start time
    time(&start_time);
    int index = 0;
    do
    {
        // Get the current time
        time(&current_time);
        // Calculate the elapsed time
        elapsed_time = difftime(current_time, start_time);
        // Print the processing status with rotating dots
        printf("\r%s", status[index]);
        fflush(stdout); // Ensure the output is printed immediately
        // Update the index for the next status
        index = (index + 1) % 5;
        // Sleep for 1 second
        sleep(1);
    } while (elapsed_time < 15);
}
void processing()  //Display A Processing Timelaps
{
    printf("\n");
    time_t start_time, current_time;
    double elapsed_time;
    const char *status[] = {"Processing.", "Processing..", "Processing...", "Processing....", "Processing....."};
    // Get the start time
    time(&start_time);
    int index = 0;
    do
    {
        // Get the current time
        time(&current_time);
        // Calculate the elapsed time
        elapsed_time = difftime(current_time, start_time);
        // Print the processing status with rotating dots
        printf("\r%s", status[index]);
        fflush(stdout); // Ensure the output is printed immediately
        // Update the index for the next status
        index = (index + 1) % 5;
        // Sleep for 1 second
        sleep(1);
    } while (elapsed_time < 15);
}
void money_sending() //Display Money Sendong Timelaps
{
    printf("\n");
    time_t start_time, current_time;
    double elapsed_time;
    const char *status[] = {"Sending Money.", "Sending Money..", "Sending Money...", "Sending Money....", "Sending Money....."};
    // Get the start time
    time(&start_time);
    int index = 0;
    do
    {
        // Get the current time
        time(&current_time);
        // Calculate the elapsed time
        elapsed_time = difftime(current_time, start_time);
        // Print the processing status with rotating dots
        printf("\r%s", status[index]);
        fflush(stdout); // Ensure the output is printed immediately
        // Update the index for the next status
        index = (index + 1) % 5;
        // Sleep for 1 second
        sleep(1);
    } while (elapsed_time < 15);
}
int showCardDetails(struct card *temp, int len) // After Creating Card It Show The Details Of Card
{
    printf("\n\n\t...Card Details...");
    printf("\n-----------------------------------\n");
    printf("|  Name:%s               \n", temp->name);
    printf("|  Card No:%lld          \n", temp->Card_no);
    printf("|  Expiry Date:%d/%d             \n", temp->card_exmonth, temp->card_exyear);
    printf("|  Card Password:%d             \n", temp->card_pin);
    printf("|  Card Balance:%d             \n", temp->card_balance);
    printf("-----------------------------------\n");
    printf("....Take  Picture Of Ur Card Details....");
    Insert_data(len, temp->name, temp->Card_no, temp->card_pin, temp->card_exmonth, temp->card_exyear, temp->card_balance);
    printf("\n    .... Start Again To Use Card ....");
    exit(1);
}
int verify_cardNo(long long int c, FILE *fp, struct card *data) // check user given card number in databse
{
    if (c != data->Card_no)
    {
        printf("...Wrong Card Number...\n      Try Again");
        exit(1);
    }
    return 0;
}
int verify_pin(int c) // check user given card number in databse
{
    if (c != globalCard_data->card_pin)
    {
        printf("...Wrong Card Password...\n      Try Again");
        exit(1);
    }
    return 0;
}
int verify_cardExMonth(int c, FILE *fp, struct card *data) // check user given card number in databse
{
    if (c != data->card_exmonth)
    {
        printf("...Wrong Card Ex-Month...\n      Try Again");
        exit(1);
    }
    return 0;
}
int verify_cardExYear(int c, FILE *fp, struct card *data) // check user given card number in databse
{
    if (c != globalCard_data->card_exyear)
    {
        printf("...Wrong Card Ex-Year...\n      Try Again");
        exit(1);
    }
    return 0;
}
int Scan_data_of_user_card(int a,FILE *fp, struct card *data) // Perfrom All Operations To Creat A New Card
{
    rewind(globalFile_pointer);
    long long int temp_card;
    int temp_exmonth, temp_exyear;
    if (a)
    {
        printf("Receiver Card No:");
    }
    else
    {
        printf("Card NO:");
    }
    scanf("%lld", &temp_card);
  
        data_address(temp_card % 10000, fp, data);


         read_nameFrom_database(fp, data);
 
            
        getCardNo_database(fp, data);

   
        verify_cardNo(temp_card, fp, data);
  
    Onestep_forward(fp);
    get_cardPass_database(fp, data);
   
    Onestep_forward(fp);



        getcardExmonth_database(fp, data);
  
    printf("Ex Month:");
    scanf("%d", &temp_exmonth);
  
        verify_cardExMonth(temp_exmonth, fp, data);
 
    Onestep_forward(fp);
 
        get_cardExyear_database(fp, data);
  
    printf("Ex Yerar:");
    scanf("%d", &temp_exyear);
  
        verify_cardExYear(temp_exyear, fp, data);

    Onestep_forward(fp);
   getCardBalance_database(fp, data);
 
    rewind(globalFile_pointer);
    return 0;
}
void print_first_row(char digit) //print first row of cash
{
    switch (digit)
    {
    case '0':
        printf(" ###### ");
        break;
    case '1':
        printf("   ##   ");
        break;
    case '2':
        printf(" ###### ");
        break;
    case '3':
        printf(" ###### ");
        break;
    case '4':
        printf("#      #");
        break;
    case '5':
        printf(" ###### ");
        break;
    case '6':
        printf(" ###### ");
        break;
    case '7':
        printf(" ###### ");
        break; // Corrected for 7
    case '8':
        printf(" ###### ");
        break;
    case '9':
        printf(" ###### ");
        break;
    }
}
void print_second_row(char digit) //print second row of cash
{
    switch (digit)
    {
    case '0':
        printf("#      #");
        break;
    case '1':
        printf("  ###   ");
        break;
    case '2':
        printf("      # ");
        break;
    case '3':
        printf("      # ");
        break;
    case '4':
        printf("#      #");
        break;
    case '5':
        printf("#       ");
        break;
    case '6':
        printf("#       ");
        break;
    case '7':
        printf("     #  ");
        break;
    case '8':
        printf("#      #");
        break;
    case '9':
        printf("#      #");
        break;
    }
}
void print_third_row(char digit) //print third row of cash
{
    switch (digit)
    {
    case '0':
        printf("#      #");
        break;
    case '1':
        printf("   ##   ");
        break;
    case '2':
        printf(" ###### ");
        break;
    case '3':
        printf(" ###### ");
        break;
    case '4':
        printf(" ###### ");
        break;
    case '5':
        printf(" ###### ");
        break;
    case '6':
        printf(" ###### ");
        break;
    case '7':
        printf("    #   ");
        break; // Adjusted for proper 7
    case '8':
        printf(" ###### ");
        break;
    case '9':
        printf(" ###### ");
        break;
    }
}
void print_fourth_row(char digit) //print fourth row of cash
{
    switch (digit)
    {
    case '0':
        printf("#      #");
        break;
    case '1':
        printf("   ##   ");
        break;
    case '2':
        printf("#       ");
        break;
    case '3':
        printf("      # ");
        break;
    case '4':
        printf("      # ");
        break;
    case '5':
        printf("      # ");
        break;
    case '6':
        printf("#      #");
        break;
    case '7':
        printf("   #    ");
        break;
    case '8':
        printf("#      #");
        break;
    case '9':
        printf("      # ");
        break;
    }
}
void print_fifth_row(char digit) //print fifth row of cash
{
    switch (digit)
    {
    case '0':
        printf(" ###### ");
        break;
    case '1':
        printf("  ####  ");
        break;
    case '2':
        printf(" ###### ");
        break;
    case '3':
        printf(" ###### ");
        break;
    case '4':
        printf("      # ");
        break;
    case '5':
        printf(" ###### ");
        break;
    case '6':
        printf(" ###### ");
        break;
    case '7':
        printf("   #    ");
        break; // Adjusted for proper 7
    case '8':
        printf(" ###### ");
        break;
    case '9':
        printf(" ###### ");
        break;
    }
}
void print_digits(const char *digits) //printf total cash withdrawn by user
{
    int len = strlen(digits);
    int width = len * 8 + (len - 1); // 8 characters per digit and spaces between digits

    // Print the top border with cash-style frame
    printf("+");
    for (int i = 0; i < width; i++)
    { // +2 for the vertical borders
        printf("-");
    }
    printf("+\n");

    // Print the side borders with digits in between
    for (int row = 1; row <= 5; row++)
    {
        printf("|");
        for (int i = 0; i < len; i++)
        {
            switch (row)
            {
            case 1:
                print_first_row(digits[i]);
                break;
            case 2:
                print_second_row(digits[i]);
                break;
            case 3:
                print_third_row(digits[i]);
                break;
            case 4:
                print_fourth_row(digits[i]);
                break;
            case 5:
                print_fifth_row(digits[i]);
                break;
            }
            if (i < len - 1)
                printf(" "); // Space between digits
        }
        printf("|\n");
    }

    // Print the bottom border with cash-style frame
    printf("+");
    for (int i = 0; i < width; i++)
    { // +2 for the vertical borders
        printf("-");
    }
    printf("+\n");
}
int user_cash(const char input[100], int a) //printf total cash withdrawn by user
{

    for (int i = 0; i < strlen(input); i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Error: Invalid input. Please enter only digits between 0 and 9.\n");
            return 1; // Exit the program with an error code
        }
    }

    printf("\n");
    print_digits(input);

    return 0;
}
void update_balance_2o(int balance,FILE *fp, struct card *data) //update the balance in database after any operation
{ char ch;
    data_address(data->Card_no % 10000, fp, data);
    int a = read_nameFrom_database(fp, data);
    rewind(fp);
    data_address(data->Card_no % 10000, fp, data);
    int abc = count_number(a);
    if (abc == 2)
        fseek(fp, 2 + 1 + a + 1 + 12 + 1 + 4 + 1 + 1 + 1 + 4 + 1 + 1+11, SEEK_CUR);
    else
        fseek(fp, 2 + 1 + a + 1 + 12 + 1 + 4 + 1 + 1 + 1 + 4 + 1, SEEK_CUR);
    int s = count_number(balance);
    int e = count_number(data->card_balance);
    if(data->card_balance==0)
        fprintf(fp, "%d\n", balance);
   else
    fprintf(fp, "%d", balance);
    if (e > s)
    {
        for (int i = 0; i < e - s; i++)
        {
            fputc(' ', fp);
        }
    }}
void update_balance(int balance, FILE *fp, struct card *data) // update the balance in database after withdraw
{
    char ch;
    data_address(data->Card_no % 10000, fp, data);
    int a = read_nameFrom_database(fp, data);
    rewind(fp);
    data_address(data->Card_no % 10000, fp, data);
    int abc = count_number(a);
    if (abc == 2)
        fseek(fp, 2 + 1 + a + 1 + 12 + 1 + 4 + 1 + 1 + 1 + 4 + 1 + 1, SEEK_CUR);
    else
        fseek(fp, 2 + 1 + a + 1 + 12 + 1 + 4 + 1 + 1 + 1 + 4 + 1, SEEK_CUR);
    int s = count_number(balance);
    int e = count_number(data->card_balance);
      if(data->card_balance==0)
        fprintf(fp, "%d\n", balance);
        else
    fprintf(fp, "%d", balance);
    if (e > s)
    {
        for (int i = 0; i < e - s; i++)
        {
            fputc(' ', fp);
        }
    }
}
int withdraw_background(int choice, int a, FILE *fp, struct card *data)  //perform background operations while cash withdrawn
{
    switch (choice)
    {
    case 1:
        if (data->card_balance < 100 + 150)
        {
            printf(".....Insufficient Balance.....");
            exit(1);
        }
        if (a)
            {user_cash("100", 0);
        printf("TAKE IT");}
        // else
        //     update_balance_2o(temp_data->card_balance + 100, temp, temp_data);
        globalbalance=100+temp_data->card_balance;
        return 100;
        break;
    case 2:
        if (data->card_balance < 200 + 150)
        {
            printf(".....Insufficient Balance.....");
            exit(1);
        }
        if (a)
{            user_cash("200", 0);
        printf("TAKE IT");}
        // else
          //  update_balance(temp_data->card_balance + 200, temp, temp_data);
globalbalance=200+temp_data->card_balance;
        return 200;
        break;
    case 3:
        if (data->card_balance < 500 + 150)
        {
            printf(".....Insufficient Balance.....");
            exit(1);
        }
        if (a)
           { user_cash("500", 0);
        printf("TAKE IT");}
        // else
          //  update_balance(temp_data->card_balance + 500, temp, temp_data);
globalbalance=500+temp_data->card_balance;
        return 500;
        break;
    case 4:
        if (data->card_balance < 1000 + 150)
        {
            printf(".....Insufficient Balance.....");
            exit(1);
        }
        if (a)
          {  user_cash("1000", 0);
        printf("TAKE IT");}
       // else
          //  update_balance(temp_data->card_balance + 1000, temp, temp_data);
globalbalance=1000+temp_data->card_balance;
        return 1000;
        break;
    case 5:
        if (data->card_balance < 5000 + 150)
        {
            printf(".....Insufficient Balance.....");
            exit(1);
        }
        if (a)
            {user_cash("5000", 0);
        printf("TAKE IT");}
       // else
          //  update_balance(temp_data->card_balance + 5000, temp, temp_data);
globalbalance=5000+temp_data->card_balance;
        return 5000;
        break;
    case 6:
        int num;
        char input[10];
        printf("Enter Amount: ");
        scanf("%d", &num);
        sprintf(input, "%d", num);
        if (data->card_balance < num + 150)
        {
            printf("....Insufficient Balance");
            exit(1);
        }
        if (a)
            {user_cash(input, 1);
        printf("TAKE IT");}
        // else
        //     update_balance(temp_data->card_balance + num, temp, temp_data);
globalbalance=num+temp_data->card_balance;
        return num;
        break;
    default:
        printf("....Input Error....");
        exit(1);
        break;
    }
}
int deposit_background(int choice, FILE *fp, struct card *data)   //perform background operations while cash deposit
{
    switch (choice)
    {
    case 1:
        return 100;
        break;
    case 2:
        return 200;
        break;
    case 3:
        return 500;
        break;
    case 4:
        return 1000;
        break;
    case 5:
        return 5000;
        break;
    case 6:
        int num;
        char input[10];
        printf("Enter Amount: ");
        scanf("%d", &num);
        if (num > 100000)
        {
            printf("Minimun Deposit Amount 1Lakh");
            exit(1);
        }
        return num;
        break;
    default:
        printf("....Input Error....");
        exit(1);
        break;
    }
}
void update_pin(int pin) //update the card  password after any changes in pin 
{
    char ch;
    data_address(globalCard_data->Card_no % 10000, globalFile_pointer, globalCard_data);
    int a = read_nameFrom_database(globalFile_pointer, globalCard_data);
    rewind(globalFile_pointer);
    data_address(globalCard_data->Card_no % 10000, globalFile_pointer, globalCard_data);
    int abc = count_number(a);
    if (abc == 2)
        fseek(globalFile_pointer, 2 + 1 + a + 1 + 12 + 1 + 1, SEEK_CUR);
    else
        fseek(globalFile_pointer, 2 + 1 + a + 1 + 12 + 1 + 1, SEEK_CUR);
    fprintf(globalFile_pointer, "%d", pin);
}
int change_pin()   //update the card  password after any changes in pin
{
    int user_pin, user_pin2;
    int yes = 1;
    while (yes < 4)
    {
        // printf("\n....Enter 4 Digit Pin....\n");
        printf("\nNew Pin(4 Digit):");
        scanf("%d", &user_pin);
        printf("Confirm Pin(4Digit):");
        scanf("%d", &user_pin2);
        if (user_pin == user_pin2 && count(user_pin))
        {
            return user_pin;
            //   temp->data.card_pin = user_pin;
            yes = 4;
        }
        else
        {
            yes++;
            printf("\n...Password Not Matched Or Should Be Four Digit...\n");
        }
    }
    loop = 0;
    printf("\n....Time Out Try Again....\n");
    return 0;
}
int cash_withdraw(int a, FILE *fp, struct card *data) // help to withdraw cash
{
    printf("\n.....Select Amount.....");
    printf("\n-----------------------");
    printf("\n|  1:100     2:200    |");
    printf("\n|  3:500     4:1000   |");
    printf("\n|  5:5000    6:Other  |");
    printf("\n-----------------------");
    printf("\nEnter:");
    int choice;
    scanf("%d", &choice);
    if(a)
    processing();
    int balance = withdraw_background(choice, a, globalFile_pointer, globalCard_data);
    balance = data->card_balance - balance;
    return balance;
}
int cash_deposit(FILE *fp, struct card *data) // help to withdraw cash
{
    printf("\n.....Select Amount.....");
    printf("\n-----------------------");
    printf("\n|  1:100     2:200    |");
    printf("\n|  3:500     4:1000   |");
    printf("\n|  5:5000    6:Other  |");
    printf("\n-----------------------");
    printf("\nEnter:");
    int choice;
    scanf("%d", &choice);
    processing();
    int balance = deposit_background(choice, globalFile_pointer, globalCard_data);
    balance = data->card_balance + balance;
    return balance;
}
int send_money() //help to send mone =y to any card to any card of k,s atm
{
    temp = fopen("data.txt", "r+");
    Scan_data_of_user_card(1,temp,temp_data);
    int balance = cash_withdraw(0, globalFile_pointer, globalCard_data);
    update_balance(balance, globalFile_pointer, globalCard_data);
    rewind(globalFile_pointer);
    update_balance(globalbalance,globalFile_pointer,temp_data);
    fclose(temp);
}
void Atm_operations() // All Atm Operations Called By Here
{
    printf("\n---------------------------------------");
    printf("\n|  1:Cash Withdraw     2:Cash Deposit |");
    printf("\n|  3:Check Balance     4:Change Pin   |");
    printf("\n|  5:Forget Pin        6:Send Money   |");
    printf("\n---------------------------------------");
    printf("\nEnter_");
    int choice, pin, balance;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("Enter Pin:");
        scanf("%d", &pin);
        verify_pin(pin);
        balance = cash_withdraw(1, globalFile_pointer, globalCard_data);
        update_balance(balance, globalFile_pointer, globalCard_data);
        printf("\n....THANK YOU SIR...\n...Have A Good Day...");

        break;
    case 2:
        printf("Enter Pin:");
        scanf("%d", &pin);
        verify_pin(pin);

        balance = cash_deposit(globalFile_pointer, globalCard_data);
        update_balance(balance, globalFile_pointer, globalCard_data);
        printf("\nCurrent Balance:%d", balance);
        printf("\n....THANK YOU SIR...\n...Have A Good Day...");

        break;
    case 3:
        printf("Enter Pin:");
        scanf("%d", &pin);
        verify_pin(pin);
        processing();
        printf("\nCurrent Balance:%d", globalCard_data->card_balance);
        printf("\n....THANK YOU SIR...\n...Have A Good Day...");

        break;
    case 4:
        printf("Enter Old Pin:");
        scanf("%d", &pin);
        verify_pin(pin);
        processing();
        pin = change_pin();
        update_pin(pin);
        printf("\n....THANK YOU SIR...\n...Have A Good Day...");

        break;
    case 5:
        printf("Enter Data From The Card Accurately");
        char name[50];
        printf("\nEnter Name:");
        gets(name);
        gets(name);
        if (!strcmp(name, globalCard_data->name))
        {
            printf("Enter Ex Month:");
            int ex_m;
            scanf("%d", &ex_m);
            if (ex_m == globalCard_data->card_exmonth)
            {
                printf("Enter Ex Year:");
                int ex_y;
                scanf("%d", &ex_y);
                if (ex_y == globalCard_data->card_exyear)
                {
                    processing();
                    printf("\n......Details Verified......");
                    pin = change_pin();
                    update_pin(pin);
                    printf("...Pin Changed Successfully...");
                    printf("\n....THANK YOU SIR...\n...Have A Good Day...");
                }
                else
                {
                    printf("...Incorrect Ex Year...");
                }
            }
            else
            {
                printf("...Incorrect Ex Month...");
            }
        }
        else
        {
            printf("...Incorrect Name...");
        }

        break;
    case 6:
        // printf("........Out Of Service........");
        // exit(1);
        printf("Enter Pin:");
        scanf("%d", &pin);
        verify_pin(pin);
        send_money();
        money_sending();
        printf("\n....Transaction Completed....");
        break;
    default:
        printf("....Input Error....");
        exit(1);
        break;
    }
    exit(1);
}
// Main Function
int main()
{

    printf("\n\n");
    while (loop)
    {
        int key;
        printf("\n_________________________________");
        printf("\n_________________________________");
        printf("\n...Are You Have K's ATM Card...\n");
        printf("   ....Enter 1:Yes 2:no....\n");
        printf("INPUT_");
        scanf("%d", &key);
        // Check User Have Atm Card Or Not
        if (key == 1 || key == 2)
        {
            // When User Have No Card
            if (key == 2)
            {
                int key;
                printf("....1:Creat Card 2:Leave K's ATM....");
                printf("\nINPUT_");
                scanf("%d", &key);
                // User Want To Creating A New Card Or Leave Atm
                if (key == 1 || key == 2)
                {
                    // Leave Atm
                    if (key == 2)
                    {
                        printf("....THANK YOU SIR...\n...Have A Good Day...");
                        loop = 0;
                    }
                    // Creating Card
                    else
                    {
                        struct card *temp = (struct card *)malloc(sizeof(struct card));

                        char name[20];
                        gets(name);
                        printf("Full name: ");
                        char name2[50];
                        gets(name2);
                        strcpy(temp->name, strupr(name2));
                        temp->card_exmonth = set_month();
                        temp->card_exyear = set_year();
                        temp->Card_no = creaat_card_no();
                        int len = strlen(temp->name);
                        cardGenerating();
                        printf("\n\n\n\n\n...Card Generated Sucessfully...\n\n\n\n\n\n\n\n");
                        printf("\nCard No:xxxxxxxxxxx%d", temp->Card_no % 10000);
                        temp->card_pin = set_password();
                        generated();
                        showCardDetails(temp, len);
                    }
                }
                // Input error
                else
                {
                    printf("----------------------------\n");
                    printf("(+ _ +)..Only 1 & 2..(+ _ +)");
                    printf("\n----------------------------");
                }
            }
            // When User Have A Card
            else
            {
                globalFile_pointer = fopen("data.txt", "r+");
                Scan_data_of_user_card(0,globalFile_pointer,globalCard_data);
                //  rewind(globalFile_pointer);
                Atm_operations();
                fclose(globalFile_pointer);
                printf("....THANK YOU SIR...\n...Have A Good Day...");
                exit(1);
            }
        }
        // Input error
        else
        {
            printf("----------------------------\n");
            printf("(+ _ +)..Only 1 & 2..(+ _ +)");
            printf("\n----------------------------");
        }
    }

    return 0;
}
