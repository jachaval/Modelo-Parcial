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
#include "usuario.h"
#include "fecha.h"
#include "entrenamiento.h"

const char* FILE_ENTRENAMIENTOS = "entrenamientos.dat";

void cargar_entrenamientos(){
    //primero verifico el usuario
    int idusuario,pos;
    bool verificado, grabo;
    Entrenamiento regEntrena;

    cout << "    NUEVO ENTRENAMIENTO" << endl << endl;

    cout << "    ID Usuario     : ";
    cin >> idusuario;

    pos=buscar_usuario(idusuario);
    verificado=verificar_usuario(pos);
    //si existe cargo el resto de los datos sino salgo
    if(verificado){

        regEntrena=cargar_entrenamiento(idusuario);
        if(regEntrena.entrena.dia!=0){
            grabo= guardar_entrenamiento(regEntrena);
            if (grabo) {
                msj("El usuario se guardó correctamente.", APP_FORECOLOR, APP_OKCOLOR);
            }
            else {
                msj("El usuario no se guardó.", APP_FORECOLOR, APP_ERRORCOLOR);
            }
        }
        else{
            msj("La fecha no puede ser mayor a la actual", 15, 3);
        }
    }
    else{
        msj("No existe el usuario", 15, 3);
    }
}

Entrenamiento cargar_entrenamiento(int codigo_buscado) {
	Entrenamiento a, *aux;
	aux = &a;
    bool fechaverificada;
    bool aptomedico=verificar_apto(codigo_buscado);

    if(!aptomedico){
        msj("ATENCIÓN: Sin apto médico no podrá realizar la actividad de natación ni pesas", APP_FORECOLOR, APP_TITLEBACKCOLOR);
        cls();
        title("LARA®", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
        gotoxy(1, 3);
        cout << "    NUEVO ENTRENAMIENTO" << endl << endl;

        cout << "    ID Usuario     : "<<codigo_buscado<<endl;
    }

    aux->IDusuario=codigo_buscado;

	cout << "    Fecha de entrenamiento: (dd/mm/aaaa)";
	a.entrena=cargar_fecha();

	fechaverificada=verificar_fecha(a.entrena);

	if(fechaverificada){
        aux->actividad=cargar_actividad(aptomedico);

        aux->calorias=cargar_calorias();

        aux->tiempo=cargar_tiempo();

        aux->ID=cargar_ID();
        return a;
	}
	else{
        a.entrena.dia=0;
        return a;
	}
}

bool guardar_entrenamiento(Entrenamiento reg){
    bool grabo;
	FILE* f;
	f = fopen(FILE_ENTRENAMIENTOS, "ab");//crea el archivo o agrega registro al final
	if (f == NULL) {
		return false;
	}
	grabo = fwrite(&reg, sizeof(Entrenamiento), 1, f);
	fclose(f);
	return grabo;
}

int cargar_actividad(bool aptomedico){
    int actividad;

	if(aptomedico){
        cout << "    Ingresar actividad"<<endl;
        cout << "    1 = caminata"<<endl;
        cout << "    2 = correr"<<endl;
        cout << "    3 = bicicleta"<<endl;
        cout << "    4 = natación"<<endl;
        cout << "    5 = pesas"<<endl;
        cout << "    Ingrese número de actividad: ";
        cin >> actividad;

        while(actividad<1 || actividad>5){
            cout << "    >Ingrese número de actividad: ";
            cin >> actividad;
        }
        return actividad;
	}
	else{
        cout << "    Ingresar actividad"<<endl;
        cout << "    1 = caminata"<<endl;
        cout << "    2 = correr"<<endl;
        cout << "    3 = bicicleta"<<endl;
        cout << "    Ingrese número de actividad: ";
        cin >> actividad;
        while(actividad<1 || actividad>3){
            cout << "    >Ingrese número de actividad: ";
            cin >> actividad;
        }
        return actividad;
	}
    do{
        if(actividad>=1 && actividad<=5){
            if(actividad==4 || actividad==5){
                msj("No puede realizar la actividad n°4 o n°5 sin apto médico", 15, 3);
                return actividad;
            }
            else{
                return actividad;
            }
        }
        else{
            cout << "    >Ingrese número de actividad: ";
            cin >> actividad;
        }
    }while(actividad<1 || actividad>5);
}

float cargar_calorias() {
    int calorias;
	cout << "    Calorías :";
	cin >> calorias;
	while (calorias < 0) {
		cout << "    >Calorías  :";
		cin >> calorias;
	}
	return calorias;
}

int cargar_tiempo(){
    int tiempo;
	cout << "    Tiempo (min):";
	cin >> tiempo;
	while (tiempo < 0) {
		cout << "    >Tiempo  :";
		cin >> tiempo;
	}
	return tiempo;
}

bool verificar_usuario(int pos){
    bool verificado;
	if(pos >= 0) {
        verificado=true;
		return verificado;
	}
	else{
	    verificado=false;
        return verificado;
	}
	// Fin de la validación de código
}

bool verificar_apto(int codigo_buscado){ //busca en el archivo el registro solicitado y guarda la info del apto medico
    Usuario reg;
	FILE* f;
	f = fopen("usuarios.dat", "rb");
	int pos = 0;
	bool aptomedico;
	if (f == NULL) {
		return -1;
	}
	while (fread(&reg, sizeof(Usuario), 1, f)) {
		if (codigo_buscado == reg.ID) {
            aptomedico=reg.apto;
			fclose(f);
		}
    }
    fclose(f);
    return aptomedico;
}

void listar_entrenamiento() {
    cout << "    LISTA DE ENTRENAMIENTOS" << endl << endl;
	Entrenamiento reg;
	FILE* f;
	f = fopen(FILE_ENTRENAMIENTOS, "rb");
	if (f == NULL) {
		cout << "No se puede leer el archivo."<<endl;
		return;
	}
	cout << "    ID" << "   |IDUsuario" << " |Actividad" << " |Calorías" << " |Tiempo" << " |Fecha";
    cout << endl <<"    -----------------------------------------------------------------";
    cout<<endl;
	while (fread(&reg, sizeof(Entrenamiento), 1, f)) {
		mostrar_entrenamiento_tabla(reg);
	}
	fclose(f);
	anykey();
}

void mostrar_entrenamiento(Entrenamiento reg) {
	cout << "    ID                    : " << reg.ID << endl;
	cout << "    ID usuario            : " << reg.IDusuario << endl;
    cout << "    Fecha de entrenamiento: ";
	mostrar_fecha(reg.entrena);
    cout << "    Actividad             : ";
    mostrar_actividad(reg);
	cout << "    Calorías              : " << reg.calorias << endl;
    cout << "    Tiempo                : " << reg.tiempo << " minutos" <<endl;
}

int buscar_entrenamiento(int codigo_entrenamiento) {
	Entrenamiento reg;
	FILE* f;
	int pos = 0;
	f = fopen("entrenamientos.dat", "rb");
	if (f == NULL) {
		return -1;
	}
	while (fread(&reg, sizeof(Entrenamiento), 1, f)) {
		if (codigo_entrenamiento == reg.IDusuario) {
			fclose(f);
			return pos;
		}
		pos++;
	}
	fclose(f);
	return -1;
}

Entrenamiento leer_entrenamiento_x_idusuario(int pos) {
	Entrenamiento reg;
	FILE* p = fopen(FILE_ENTRENAMIENTOS, "rb");
	if (p == NULL) {
		reg.IDusuario = 0;
		return reg;
	}
	fseek(p, pos * sizeof(Entrenamiento), SEEK_SET);
	fread(&reg, sizeof(Entrenamiento), 1, p);
	fclose(p);
	return reg;
}

void listar_entrenamiento_x_id(){
	int codigo, pos;
    cout << "    ENTRENAMIENTO POR ID" << endl << endl;
	cout<<"    Ingrese el ID: ";
            cin>>codigo;
	pos = buscar_entrenamiento2(codigo);
	if (pos >= 0) {
        cout<<endl;
        cout<<"    ---------------------------"<<endl;
		mostrar_entrenamiento(leer_entrenamiento_x_id(pos));
	}
	else {
		msj("No existe el IDusuario ", 15, 3);
	}
}

int buscar_entrenamiento2(int codigo_entrenamiento) {
	Entrenamiento reg;
	FILE* f;
	int pos = 0;
	f = fopen("entrenamientos.dat", "rb");
	if (f == NULL) {
		return -1;
	}
	while (fread(&reg, sizeof(Entrenamiento), 1, f)) {
		if (codigo_entrenamiento == reg.ID) {
			fclose(f);
			return pos;
		}
		pos++;
	}
	fclose(f);
	return -1;
}

void cargar_entrenamientos2(){
    //primero verifico el usuario
    int idusuario,pos;
    bool verificado, grabo;
    Entrenamiento regEntrena;

    cout << "    NUEVO ARCHIVO ENTRENAMIENTO" << endl << endl;

    cout << "    ID Usuario     : ";
    cin >> idusuario;

    pos=buscar_usuario(idusuario);
    verificado=verificar_usuario(pos);
    //si existe cargo el resto de los datos sino salgo
    if(verificado){

        regEntrena=cargar_entrenamiento(idusuario);
        regEntrena.ID=1;
        if(regEntrena.entrena.dia!=0){
            grabo= guardar_entrenamiento2(regEntrena);
            if (grabo) {
                msj("El usuario se guardó correctamente.", APP_FORECOLOR, APP_OKCOLOR);
            }
            else {
                msj("El usuario no se guardó.", APP_FORECOLOR, APP_ERRORCOLOR);
            }
        }
        else{
            msj("La fecha no puede ser mayor a la actual", 15, 3);
        }
    }
    else{
        msj("No existe el usuario", 15, 3);
    }
}

bool guardar_entrenamiento2(Entrenamiento reg){
    bool grabo;
	FILE* f;
	f = fopen(FILE_ENTRENAMIENTOS, "wb");//crea el archivo y agrega el registro final
	if (f == NULL) {
		return false;
	}
	grabo = fwrite(&reg, sizeof(Entrenamiento), 1, f);
	fclose(f);
	return grabo;
}

void mostrar_actividad(Entrenamiento reg){
    switch (reg.actividad){
        case 1:
            cout<<"Caminata"<<endl;
        break;
        case 2:
            cout<<"Correr"<<endl;
        break;
        case 3:
            cout<<"Bicicleta"<<endl;
        break;
        case 4:
            cout<<"Natación"<<endl;
        break;
        case 5:
            cout<<"Pesas"<<endl;
        break;
    }
}

int cargar_ID(){
    int cantEntrenamientos;
    cantEntrenamientos=(cantidad_entrenamientos()+1);
    return cantEntrenamientos;
}

int cantidad_entrenamientos(){
    FILE *p = fopen(FILE_ENTRENAMIENTOS, "rb");
    if (p == NULL){
        return 1;
    }
    int bytes, cant;
    fseek(p, 0, SEEK_END); // SEEK_SET --> 0 , SEEK_CUR --> 1 , SEEK_END --> 2
    bytes = ftell(p);
    fclose(p);
    cant = bytes / sizeof(Entrenamiento);
    return cant;
}

void modificar_entrenamiento(){
    int codigo, pos;
    Entrenamiento reg;
    cout << "    MODIFICAR ENTRENAMIENTO" << endl<<endl;
    cout << "    ID: ";
    cin >> codigo;
    pos = buscar_entrenamiento(codigo);
    if (pos >= 0){
        cout << endl << "    Entrenamiento a modificar: " << endl;
        cout << "    --------------------------------" << endl;
        reg = leer_entrenamiento_x_id(pos);
        mostrar_entrenamiento(reg);
        cout << "    --------------------------------" << endl;
        cout << endl;

        reg.calorias=cargar_calorias();

        reg.tiempo=cargar_tiempo();

        if (guardar_entrenamiento3(reg, pos) == true){
            msj("Usuario guardado correctamente.", APP_FORECOLOR, APP_OKCOLOR);
            return ;
        }
        else{
            msj("El usuario no se guardó correctamente.", APP_FORECOLOR, APP_ERRORCOLOR);
            return ;

        }
    }
    else{
        msj("No existe el usuario", 15, 3);
        return ;
    }
}

Entrenamiento leer_entrenamiento_x_id(int pos) {
	Entrenamiento reg;
	FILE* p = fopen(FILE_ENTRENAMIENTOS, "rb");
	if (p == NULL) {
		reg.ID = 0;
		return reg;
	}
	fseek(p, pos * sizeof(Entrenamiento), SEEK_SET);
	fread(&reg, sizeof(Entrenamiento), 1, p);
	fclose(p);
	return reg;
}

bool guardar_entrenamiento3(Entrenamiento reg, int pos){
    bool grabo=true;
    FILE* p = fopen(FILE_ENTRENAMIENTOS, "rb+");

    if (p == NULL){
        return false;
    }
    fseek(p, pos * sizeof(Entrenamiento), SEEK_SET);
    grabo = fwrite(&reg, sizeof(Entrenamiento), 1, p);
    fclose(p);
    return grabo;
}

void ordenar_entrenamiento(Entrenamiento *vec, int tam){
    int i, j, posmax;
    Entrenamiento aux;
    ///Selection sort
    for(i=0; i<tam-1; i++){
        posmax = i;
        for(j=i+1; j<tam; j++){
            if (vec[j].IDusuario > vec[posmax].IDusuario){
                posmax = j;
            }
        }
        aux = vec[i];
        vec[i] = vec[posmax];
        vec[posmax] = aux;
    }
}

void listar_entrenamiento_x_idusuario(){
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
        p = fopen(FILE_ENTRENAMIENTOS, "rb");
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
            if(vec[i].IDusuario==codigo){
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

void mostrar_entrenamiento_tabla(Entrenamiento reg) {
    cout << left;
    cout << "    " <<setw(6)<< reg.ID;
    cout << setw(11) << reg.IDusuario;
    cout << setw(11);
    switch (reg.actividad){
        case 1:
            cout<<"Caminata";
        break;
        case 2:
            cout<<"Correr";
        break;
        case 3:
            cout<<"Bicicleta";
        break;
        case 4:
            cout<<"Natación";
        break;
        case 5:
            cout<<"Pesas";
        break;
    }
    cout << setw(10) << reg.calorias;
    cout << setw(8) << reg.tiempo;
    mostrar_fecha(reg.entrena);
}











































































































































