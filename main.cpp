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

//PROTOTIPOS DE LAS FUNCIONES
void dibujarConsola(int x1,int y1,int x2,int y2);
void gotoxy(int x,int y);
void CursorOn(bool visible, DWORD size);
void CursorOff();
void menu();
void limpiar();
void ingresarPalabra();
void traducirPalabra();
void traduccion(int op);
void cambio(char a[]);

int main()
{
    system("mode con: cols=80 lines=25");
	system("COLOR 80");
	CursorOff();
	dibujarConsola(0,0,78,24); //DIBUJA CUADRO GRANDE DE LOS BORDES
	dibujarConsola(1,1,77,3);  //DIBUJA CUADRO DEL TÍTULO
	gotoxy(16,2); cout << "               T R A D U C T O R";
	menu();
	getch();
    return 0;
}

//DESARROLLO DE LAS FUNCIONES/////

void menu(){
    char op;
    CursorOn(1,10);

    do{
        gotoxy(4,6); cout << "MENU";
        gotoxy(4,9); cout << "(1) Ingresar palabras";
		gotoxy(4,11); cout << "(2) Traducir palabras";
		gotoxy(4,13); cout << "(3) Cerrar";
		gotoxy(4,15); cout << "Ingrese opcion: ";
		cin >> op;

		if(op!='1' && op!=2 && op!='3'){
            gotoxy(4,22); cout << "Error al ingresar valores. Presione una tecla para volver a ingresar..";
			CursorOff();
			getch();
			gotoxy(4,22); cout << "                                                                       ";
			gotoxy(4,15); cout << "Ingrese opcion:               ";
			CursorOn(1,10);
		}
    }while(op!='1' && op!='2' && op!='3');
        if (op==1){
            ingresarPalabra();
        }

        if(op==2){
            traducirPalabra();
        }

        //if(op==3){
          //  exit(0);
        //}

}

//INGRESAR PALABRA
void ingresarPalabra(){
    cout << "test 1";
}

//TRADUCIR PALABRA
void traducirPalabra(){
    cout << "test 2";
}



//FUNCION GOTOXY. ESTA FUNCION NOS PERMITE POSICIONAR EN UNA DETERMINADA ZONA DE LA PANTALLA ALGUN MENSAJE. EJEMPLO: GOTOXY(4,8); cout << "HOLA").. INDICAMOS QUE EL MENSAJE "HOLA" APAREZCA EN LA COLUMNA NUMERO 4 Y FILA 8 DE LA PANTALLA
void gotoxy(int x,int y){
      HANDLE hcon;
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);
      COORD dwPos;
      dwPos.X = x;
      dwPos.Y= y;
      SetConsoleCursorPosition(hcon,dwPos);
}


void CursorOff(){
  CONSOLE_CURSOR_INFO cursor = {1, FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}


void CursorOn(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
	if(size == 0)
	{
		size = 20;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
	}
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

//DIBUJA CUADROS EN LA CONSOLA
void dibujarConsola(int x1,int y1,int x2,int y2){

    int i;
    for (i=x1;i<x2;i++){
		gotoxy(i,y1);cout << "Ä"; //linea horizontal superior
		gotoxy(i,y2);cout << "Ä"; //linea horizontal inferior
    }

    for (i=y1;i<y2;i++){
		gotoxy(x1,i);cout << "³"; //linea vertical izquierda
		gotoxy(x2,i);cout << "³"; //linea vertical derecha
    }

    gotoxy(x1,y1);cout << "Ú";
    gotoxy(x1,y2);cout << "À";
    gotoxy(x2,y1);cout << "¿";
    gotoxy(x2,y2);cout << "Ù";
}
