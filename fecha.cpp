#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <locale.h>
#include <ctime>
using namespace std;
#include "fecha.h"

void mostrar_fecha(Fecha reg) {
	cout << reg.dia << "/" << reg.mes << "/" << reg.anio << endl;
}

Fecha cargar_fecha() {
	Fecha aux;
	// para saber el año actual recurro a las siguientes lineas y al final si el año ingresado es mayor al del sistema vuelve a pedir el año
	time_t tiempo;
    char cad[80];
    struct tm *tmPtr;
    tiempo = time(NULL);
    tmPtr = localtime(&tiempo);

	cout << endl;
	cout << "    Día: ";
	cin >> aux.dia;
	while (aux.dia < 1 || aux.dia > 31) {
		cout << "    >Día: ";
		cin >> aux.dia;
	}
	cout << "    Mes: ";
	cin >> aux.mes;
	while (aux.mes < 1 || aux.mes > 12) {
		cout << "    >Mes: ";
		cin >> aux.mes;
	}
	cout << "    Año: ";
	cin >> aux.anio;
	while (aux.anio >(1900+tmPtr->tm_year)) {
		cout << "    >Año: ";
		cin >> aux.anio;
	}
	return aux;
}

Fecha mostrar_fechaactual(){//nombre incorrecto ya que al final no muestra la fecha pero bueno, habria que cambiarlo :D
    time_t tiempo;
    char cad[80];
    struct tm *tmPtr;
    Fecha fechaac;
    tiempo = time(NULL);
    tmPtr = localtime(&tiempo);

    //printf("FECHA ACTUAL \n%d/%d/%d %d:%d:%d", tmPtr->tm_mday, tmPtr->tm_mon+1, 1900+tmPtr->tm_year, tmPtr->tm_hour, tmPtr->tm_min, tmPtr->tm_sec);
    //strftime(cad, 80, "%A %d de %B de %Y", tmPtr);
    //printf("\n\n%s", cad);
    fechaac.dia=tmPtr->tm_mday;
    fechaac.mes=tmPtr->tm_mon+1;
    fechaac.anio=1900+tmPtr->tm_year;
return fechaac;
}

bool verificar_fecha(Fecha fech){
    Fecha fechaact;
    fechaact=mostrar_fechaactual();
    if(fech.anio<fechaact.anio){
        return true;
    }
    else{
        if(fech.anio==fechaact.anio){
            if(fech.mes<fechaact.mes){
                return true;
            }
            else{
                if(fech.mes==fechaact.mes){
                    if(fech.dia<=fechaact.dia){
                        return true;
                    }
                    else{
                        return false;
                    }
                }
                else{
                    return false;
                }
            }
            return false;
        }
        else{
            return false;
        }
    }
}

bool verificar_mayorDeEdad(Fecha fecha, int edadMinima){
    int edad;
    time_t tiempo;
    char cad[80];
    struct tm *tmPtr;
    Fecha fechaac;
    tiempo = time(NULL);
    tmPtr = localtime(&tiempo);
    fechaac.dia=tmPtr->tm_mday;
    fechaac.mes=tmPtr->tm_mon+1;
    fechaac.anio=1900+tmPtr->tm_year;

    edad=fechaac.anio-fecha.anio;
    if(fecha.mes>=fechaac.mes){
         if(fecha.mes==fechaac.mes) {
              if(fecha.dia>fechaac.dia){
                edad=edad-1;
              }
         }
         else {
            edad=edad-1;
         }
    }
    if(edad<edadMinima){
        return false;
    }
    else{
        return true;
    }
}



















