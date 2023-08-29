#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<windows.h>
#include <string.h>
#include <iostream>

using namespace std;
HANDLE console = GetStdHandle (STD_OUTPUT_HANDLE);


//ESTRUCTURA DE LAS DOS VARAIBLES
typedef struct traductor{
    char ing[30];
    char esp[30];
};


int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
