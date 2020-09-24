#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <locale.h>
#include <ctime>
using namespace std;
#include "interfaz.h"
#include "rlutil.h"
using namespace rlutil;
#include "menu.h"
#include "usuario.h"
#include "entrenamiento.h"
#include "fecha.h"
#include "reportes.h"

void menu_principal() {
    //initUI();

	int opcion,i;
	do{
	system("cls");
	title("LARA®", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
	//gotoxy(1, 3);

	for (i = 0; i < 24; i++) {
		gotoxy(i + 4, 3); printf("*");
		gotoxy(9, 4); printf("MENÚ PRINCIPAL ");
		gotoxy(i + 4, 5); printf("*");
		gotoxy(4, 4); printf("*");
		gotoxy(27, 4); printf("*");
	}

	gotoxy(1,6);
		//cout << "    MENÚ PRINCIPAL" << endl<<endl;
		cout << "    1. USUARIOS" << endl;
		cout << "    2. ENTRENAMIENTOS" << endl;
		cout << "    3. REPORTES " << endl;
		cout << "    4. CONFIGURACIÓN " << endl<<endl;
		cout << "    0. SALIR" << endl;
		cout << "    ------------------------------" << endl;

		cout <<"    Opcion-> ";
		cin >> opcion;


			switch (opcion) {
			case 1:
				menu_usuario();
				break;
			case 2:
			    menu_entrenamientos();
				break;
			case 3:
			    menu_reportes();
				break;
			case 4:
				break;
			case 0:	return;
				break;
			}
	} while (opcion != 0);

}

void menu_usuario() {
	int opcion ;
	bool grabo;
	do {
		system("cls");
		title("LARA®", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
		for (int i = 0; i < 23; i++) {
			gotoxy(i + 4, 3); printf("*");
			gotoxy(9, 4); printf("MENÚ USUARIOS ");
			gotoxy(i + 4, 5); printf("*");
			gotoxy(4, 4); printf("*");
			gotoxy(26, 4); printf("*");
		}

		gotoxy(1, 6);
		cout << "    1. NUEVO USUARIO" << endl;
		cout << "    2. MODIFICAR USUARIO" << endl;
		cout << "    3. LISTAR USUARIO POR ID " << endl;
		cout << "    4. LISTAR TODOS LOS USUARIOS " << endl;
		cout << "    5. ELIMINAR USUARIO" << endl;
		cout << "    6. NUEVO ARCHIVO USUARIO" << endl<<endl;
		cout << "    0. VOLVER AL MENÚ PRINCIPAL" << endl;
		cout << "    ------------------------------" << endl;

		cout << "    Opción-> ";
		cin >> opcion;

		switch (opcion) {
		case 1:
			rlutil::cls();
			title("LARA®", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
			gotoxy(1, 3);
			Usuario regUsuario;
			regUsuario=cargar_usuario();
			if(regUsuario.nacimiento.dia!=0){
                grabo = guardar_usuario(regUsuario);
                if (grabo) {
                    msj("El usuario se guardó correctamente.", APP_FORECOLOR, APP_OKCOLOR);
                }
                else {
                    msj("El usuario no se guardó.", APP_FORECOLOR, APP_ERRORCOLOR);
                }
            }
            else{
                msj("Debe ser mayor a 13 años para registrarse", 15, 3);
            }
			break;
		case 2:
		    rlutil::cls();
			title("LARA®", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
			gotoxy(1, 3);
			modificar_usuario();

			break;
		case 3:
			rlutil::cls();
			title("LARA®", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
			gotoxy(1, 3);
			listar_usuario_x_id();
			rlutil::anykey();
			break;
		case 4:
		    rlutil::cls();
			title("LARA®", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
			gotoxy(1, 3);
			listar_usuario();
			system("pause");
			break;
		case 5:
            rlutil::cls();
			title("LARA®", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
			gotoxy(1, 3);
			eliminar_usuario();
			break;
        case 6:
            rlutil::cls();
			title("LARA®", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
			gotoxy(1, 3);
			grabo = guardar_usuario2(cargar_usuario());
			if (grabo) {
				msj("El usuario se guardó correctamente.", APP_FORECOLOR, APP_OKCOLOR);
			}
			else {
				msj("El usuario no se guardó.", APP_FORECOLOR, APP_ERRORCOLOR);
			}
            break;
		case 0: return;
			break;
		}
	} while (opcion != 0);
}

void menu_entrenamientos(){
	int opcion,codigo ;
	bool grabo;
	do {
		system("cls");
		title("LARA®", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
		for (int i = 0; i < 29; i++) {
			gotoxy(i + 4, 3); printf("*");
			gotoxy(9, 4); printf("MENÚ ENTRENAMIENTOS ");
			gotoxy(i + 4, 5); printf("*");
			gotoxy(4, 4); printf("*");
			gotoxy(32, 4); printf("*");
		}

		gotoxy(1, 6);
		cout << "    1. NUEVO ENTRENAMIENTO" << endl;
		cout << "    2. MODIFICAR ENTRENAMIENTO" << endl;
		cout << "    3. LISTAR ENTRENAMIENTO POR ID " << endl;
		cout << "    4. LISTAR ENTRENAMIENTOPOR IDUSUARIO " << endl;
		cout << "    5. LISTAR TODOS LOS ENTRENAMIENTOS" << endl;
		cout << "    6. NUEVO ARCHIVO ENTRENAMIENTO" << endl;
		cout << "    0. VOLVER AL MENÚ PRINCIPAL" << endl<<endl;
		cout << "    ------------------------------" << endl;

		cout << "    Opción-> ";
		cin >> opcion;

		switch (opcion) {
		case 1:
			rlutil::cls();
			title("LARA®", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
			gotoxy(1, 3);
			cargar_entrenamientos();
            break;
		case 2:
		    rlutil::cls();
			title("LARA®", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
			gotoxy(1, 3);
            modificar_entrenamiento();
			break;
		case 3:
			rlutil::cls();
			title("LARA®", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
			gotoxy(1, 3);
            listar_entrenamiento_x_id();
            system ("pause");
			break;
		case 4:
			rlutil::cls();
			title("LARA®", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
			gotoxy(1, 3);
            listar_entrenamiento_x_idusuario();
            system ("pause");
			break;
		case 5:
			rlutil::cls();
			title("LARA®", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
			gotoxy(1, 3);
			listar_entrenamiento();
			system("pause");
			break;
        case 6:
            rlutil::cls();
			title("LARA®", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
			gotoxy(1, 3);
			cargar_entrenamientos2();
            break;
		case 0: return;
			break;
		}
	} while (opcion != 0);
}

void menu_reportes(){
	int opcion,codigo ;
	bool grabo;
	do {
		system("cls");
		title("LARA®", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
		for (int i = 0; i < 29; i++) {
			gotoxy(i + 4, 3); printf("*");
			gotoxy(9, 4); printf("MENÚ REPORTES ");
			gotoxy(i + 4, 5); printf("*");
			gotoxy(4, 4); printf("*");
			gotoxy(32, 4); printf("*");
		}

		gotoxy(1, 6);
		cout << "    1. REPORTE 1" << endl;
		cout << "    2. REPORTE 2" << endl;
		cout << "    0. VOLVER AL MENÚ PRINCIPAL" << endl<<endl;
		cout << "    ------------------------------" << endl;

		cout << "    Opción-> ";
		cin >> opcion;

		switch (opcion) {
		case 1:
			rlutil::cls();
			title("LARA®", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
			gotoxy(1, 3);
			reporte_1();
			anykey();

            break;
		case 2:
		    rlutil::cls();
			title("LARA®", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
			gotoxy(1, 3);
            reporte_2();
            anykey();
			break;
		case 0: return;
			break;
		}
	} while (opcion != 0);
}
