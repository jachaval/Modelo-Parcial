#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <locale.h>
#include <iomanip>
#include "rlutil.h"
using namespace std;
#include "interfaz.h"
using namespace rlutil;
#include "entrenamiento.h"
#include "reportes.h"


//1. listar todos los entrenamientos cuyo tiempo supere el tiempo promedio
//2. A partir de un ID de usuario que se ingrese por teclado listar Apellido, Nombres y
// cantidad de entrenamientos realizados en el año 2020


void reporte_1(){
    listar_entrenamiento_x_tiempo();
}

int buscar_promedio(){
    cout << "    LISTAR TODOS LOS USUARIOS" << endl << endl;
	Entrenamiento reg;
	int promedio, contador=0, tiempototal=0;
	FILE* f;
	f = fopen("entrenamientos.dat", "rb");
	if (f == NULL) {
		cout << "No se puede leer el archivo.";
		return -1;
	}
	while (fread(&reg, sizeof(Entrenamiento), 1, f)) {
        contador++;
        tiempototal+=reg.tiempo;
	}
	promedio=tiempototal/contador;
    cout<<endl;
	fclose(f);
	return promedio;
}

int buscar_entrenamiento_mayor_alpromedio(int promedio) {
	Entrenamiento reg;
	FILE* f;
	int pos = 0;
	f = fopen("entrenamientos.dat", "rb");
	if (f == NULL) {
		return -1;
	}
	while (fread(&reg, sizeof(Entrenamiento), 1, f)) {
		if (promedio < reg.tiempo) {
			fclose(f);
			return pos;
		}
		pos++;
	}
	fclose(f);
	return -1;
}

void listar_entrenamiento_x_tiempo(){
    cout << "    LISTA DE ENTRENAMIENTOS DE MAYORES AL TIEMPO PROMEDIO" << endl << endl;
	int codigo, pos, promedio;
	promedio=buscar_promedio();
	pos = buscar_entrenamiento_mayor_alpromedio(promedio);
	if (pos >= 0) {
        cout<<endl;
        cout<<"    ---------------------------"<<endl<<endl;
        int cant = cantidad_entrenamientos();
        if (cant == 0){
                msj("No existe el IDusuario 1 ", 15, 3);
            return;
        }

        Entrenamiento *vec;

        vec = (Entrenamiento *) malloc(cant * sizeof(Entrenamiento));
        if (vec == NULL){
                msj("No existe el IDusuario 2 ", 15, 3);
            return;
        }
        FILE *p;
        p = fopen("entrenamientos.dat", "rb");
        if (p == NULL){
            free(vec);
            msj("No existe el IDusuario 3", 15, 3);
            return;
        }
        fread(vec, sizeof(Entrenamiento), cant, p);
        fclose(p);

        //ordenar_entrenamiento(vec, cant);

        cout << "    ID" << "   |IDUsuario" << " |Actividad" << " |Calorías" << " |Tiempo" << " |Fecha";
        cout << endl <<"    -----------------------------------------------------------------";
        cout<<endl;
        int i;
        for(i=0; i<cant; i++){
            if(vec[i].tiempo>promedio){
                mostrar_entrenamiento_tabla(vec[i]);
            }
        }
        cout<<endl;
        free(vec);
	}
	else {
		msj("No existe el IDusuario ", 15, 3);
		return;
	}
}

void reporte_2(){
listar_entrenamiento_2020();
}

void listar_entrenamiento_2020(){
    cout << "    LISTA DE ENTRENAMIENTOS POR IDUSUARIO" << endl << endl;
	int codigo, pos;
	cout << "    Ingresar id a buscar: ";
	cin >> codigo;
	pos = buscar_entrenamiento(codigo);
	if (pos >= 0) {
        cout<<endl;
        cout<<"    ---------------------------"<<endl<<endl;
        int cant = cantidad_entrenamientos();
        if (cant == 0){
            return;
        }

        Entrenamiento *vec;

        vec = (Entrenamiento *) malloc(cant * sizeof(Entrenamiento));
        if (vec == NULL){
            return;
        }
        FILE *p;
        p = fopen("entrenamientos.dat", "rb");
        if (p == NULL){
            free(vec);
            return;
        }
        fread(vec, sizeof(Entrenamiento), cant, p);
        fclose(p);

        //ordenar_entrenamiento(vec, cant);

        cout << "    ID" << "   |IDUsuario" << " |Actividad" << " |Calorías" << " |Tiempo" << " |Fecha";
        cout << endl <<"    -----------------------------------------------------------------";
        cout<<endl;
        int i;
        for(i=0; i<cant; i++){
            if(vec[i].entrena.anio>=2020 && vec[i].IDusuario==codigo){
                pos = buscar_usuario(codigo);
                if (pos >= 0) {
                    cout<<endl;
                    cout<<"    ---------------------------"<<endl;
                    mostrar_usuario_reporte2(leer_usuario(pos));
                }
                else {
                    msj("No existe el usuario", 15, 3);
                }
               // mostrar_entrenamiento_tabla(vec[i]);
            }
        }
        cout<<endl;
        free(vec);
	}
	else {
		msj("No existen Entrenamientos del IDusuario ", 15, 3);
		return;
	}
}
void mostrar_usuario_reporte2(Usuario reg) {
	cout << "    ID                 : " << reg.ID << endl;
	cout << "    Nombres            : " << reg.nombres << endl;
	cout << "    Apellidos          : " << reg.apellidos << endl;
}
