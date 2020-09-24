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

const char* FILE_USUARIOS = "usuarios.dat";

Usuario cargar_usuario() {
	Usuario a, * aux;
	aux = &a;
	int ID;
	int edadMinima=13;
	bool edadVerificada;

	cout << "    NUEVO USUARIO" << endl << endl;
	cout << "    ID        : ";
	cin >> ID;

	// Validamos el código que no se repita en la lista
	while (buscar_usuario(ID) >= 0) {
		cout << "    >ID        : ";
		cin >> ID;
	}
	// Fin de la validación de código
	aux->ID = ID;

	cout << "    Nombres   : ";
	cin.ignore();
	cin.getline(aux->nombres, 50);
	while (aux->nombres[0] == '\0'|| aux->nombres[0] == ' ') {
		cout << "    >Nombres   : ";
		cin.getline(aux->nombres, 50);
	}

	cout << "    Apellidos : ";
	cin.getline(aux->apellidos, 50);
	while (aux->apellidos[0] == '\0'|| aux->apellidos[0] == ' ') {
		cout << "    >Apellidos : ";
		cin.getline(aux->apellidos, 50);
	}

	cout << "    Fecha de nacimiento: (dd/mm/aaaa)";
	aux->nacimiento=cargar_fecha();
    edadVerificada=verificar_mayorDeEdad(a.nacimiento,edadMinima);

    if(edadVerificada){
        aux->altura = cargar_altura();

        aux->peso = cargar_peso();

        cout << "    Perfil de actividad (A/B/C):";
        cin >> aux->perfil;
        while (aux->perfil != 'A' && aux->perfil != 'a' && aux->perfil != 'B' && aux->perfil != 'b' && aux->perfil != 'C' && aux->perfil != 'c') {
            cout << "    >Perfil de actividad: ";
            cin >> aux->perfil;
        }

        aux->apto=cargar_apto();

        aux->estado = true;
        return a;
    }
    else{
        a.nacimiento.dia=0;
        return a;
    }
}

int buscar_usuario(int codigo_buscado) {
	Usuario reg;
	FILE* f;
	int pos = 0;
	f = fopen("usuarios.dat", "rb");
	if (f == NULL) {
		return -1;
	}
	while (fread(&reg, sizeof(Usuario), 1, f)) {
		if (codigo_buscado == reg.ID) {
			fclose(f);
			return pos;
		}
		pos++;
	}
	fclose(f);
	return -1;
}

bool guardar_usuario(Usuario reg) {
	bool grabo;
	FILE* f;
	f = fopen("usuarios.dat", "ab");//crea el archivo y agrega registro al final
	if (f == NULL) {
		return false;
	}
	grabo = fwrite(&reg, sizeof(Usuario), 1, f);
	fclose(f);
	return grabo;
}

bool guardar_usuario2(Usuario reg) {
	bool grabo;
	FILE* f;
	f = fopen("usuarios.dat", "wb");//crea el archivo o lo reescribi
	if (f == NULL) {
		return false;
	}
	grabo = fwrite(&reg, sizeof(Usuario), 1, f);
	fclose(f);
	return grabo;
}

void listar_usuario() {
    cout << "    LISTAR TODOS LOS USUARIOS" << endl << endl;
	Usuario reg;
	FILE* f;
	f = fopen("usuarios.dat", "rb");
	if (f == NULL) {
		cout << "No se puede leer el archivo.";
		return;
	}
	cout << "    ID" << "   |Apellidos" << "      |Nombres" << "        |Altura" << " |Peso" << " |Actividad" << " |Apto médico" << " |Fecha de nacimiento";
    cout << endl <<"    ------------------------------------------------------------------------------------------------";
    cout<<endl;
	while (fread(&reg, sizeof(Usuario), 1, f)) {
		//mostrar_usuario(reg);
		mostrar_usuario_tabla(reg);

	}
    cout<<endl;
	fclose(f);
}

void mostrar_usuario(Usuario reg) {
	cout << "    ID                 : " << reg.ID << endl;
	cout << "    Nombres            : " << reg.nombres << endl;
	cout << "    Apellidos          : " << reg.apellidos << endl;
    cout << "    Nacimiento         : ";
	mostrar_fecha(reg.nacimiento);
	cout << "    Altura             : " << reg.altura << " cm" << endl;
	cout << "    Peso               : " << reg.peso << " kg" << endl;
	mostrar_perfil_actividad(reg);
	if(reg.apto==1){
    cout << setw(13) << "Si";
    }
    else{
        cout << setw(13) << "No";
    }
	cout << "    Estado             : " << reg.estado << endl;
}

float cargar_altura() {
	float altura;
	cout << "    Altura(cm):";
	cin >> altura;
	while (altura < 0) {
		cout << "    >Altura(cm):";
		cin >> altura;
	}
	return altura;
}

float cargar_peso() {
	float peso;
	cout << "    Peso  (kg):";
	cin >> peso;
	while (peso < 0) {
		cout << "    >Peso  (kg):";
		cin >> peso;
	}
	return peso;
}

void listar_usuario_x_id() {
	int codigo, pos;
	cout<<"    LISTAR USUARIO POR ID" << endl<<endl;
	cout << "    Ingresar código a buscar: ";
	cin >> codigo;
	pos = buscar_usuario(codigo);
	if (pos >= 0) {
        cout<<endl;
        cout<<"    ---------------------------"<<endl;
		mostrar_usuario(leer_usuario(pos));
	}
	else {
		msj("No existe el usuario", 15, 3);
	}
}

Usuario leer_usuario(int pos) {
	Usuario reg;
	FILE* p = fopen(FILE_USUARIOS, "rb");
	if (p == NULL) {
		reg.ID = 0;
		return reg;
	}
	fseek(p, pos * sizeof(Usuario), SEEK_SET);
	fread(&reg, sizeof(Usuario), 1, p);
	fclose(p);
	return reg;
}

int cargar_apto() {
	char opc;
	cout << "    Apto médico    (S/N): ";
	cin >> opc;
	switch (opc){
	case 's':
	case 'S':
		return 1;
		break;
	case 'n':
	case 'N':
		return 0;
		break;
	default:
	    cout << " ";
        cargar_apto();
        break;
	}
}

void mostrar_perfil_actividad(Usuario reg) {
	switch (reg.perfil){
	case 'a':
	case 'A': cout << "    Perfil de actividad: " << 'A' << endl;
		break;
	case 'b':
	case 'B': cout << "    Perfil de actividad: " << 'B' << endl;
		break;
	case 'c':
	case 'C': cout << "    Perfil de actividad: " << 'C' << endl;
		break;
	}
}

bool guardar_usuario3(Usuario reg, int pos){
    bool grabo=true;
    FILE* p = fopen(FILE_USUARIOS, "rb+");

    if (p == NULL){
        return false;
    }
    fseek(p, pos * sizeof(Usuario), SEEK_SET);
    grabo = fwrite(&reg, sizeof(Usuario), 1, p);
    fclose(p);
    return grabo;
}

void modificar_usuario(){
    int codigo, pos;
    Usuario reg;
    cout << "    MODIFICAR USUARIO" << endl<<endl;
    cout << "    ID: ";
    cin >> codigo;
    pos = buscar_usuario(codigo);
    if (pos >= 0){
        cout << endl << "    Usuario a modificar: " << endl;
        cout << "    --------------------------------" << endl;
        reg = leer_usuario(pos);
        mostrar_usuario(reg);
        cout << "    --------------------------------" << endl;
        cout << endl;

        reg.peso=cargar_peso();

        cout << "    Perfil de actividad: ";
        cin >> reg.perfil;
        while (reg.perfil != 'A' && reg.perfil != 'a' && reg.perfil != 'B' && reg.perfil != 'b' && reg.perfil != 'C' && reg.perfil != 'c') {
            cout << "    >Perfil de actividad: ";
            cin >> reg.perfil;
        }

        reg.apto=cargar_apto();

        if (guardar_usuario3(reg, pos) == true){
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

void eliminar_usuario(){
    char opc;
    int codigo, pos;
    cout << "    ELIMINAR USUARIO" << endl<<endl;
    cout << "    Código: ";
    cin >> codigo;
    pos = buscar_usuario(codigo);
    if (pos >= 0){
        cout << endl << "    Usuario a eliminar: " << endl;
        cout << "    --------------------------------" << endl;
        Usuario reg = leer_usuario(pos);
        mostrar_usuario(reg);
        cout << "    --------------------------------" << endl;
        cout << endl;

        do{
        cout << "    ¿ESTÁ SEGURO DE ELIMINAR USUARIO? (S/N): ";
        cin >> opc;
            if (opc=='s'||opc=='S'){
                reg.estado=false;
                if (guardar_usuario3(reg, pos) == true){
                    msj("Usuario eliminado correctamente.", APP_FORECOLOR, APP_OKCOLOR);
                    return ;
                }
                else{
                    msj("El usuario no se guardó correctamente.", APP_FORECOLOR, APP_ERRORCOLOR);
                    return ;

                }
            }
            if(opc=='n'||opc=='N'){
                msj("No se han generado cambios", 15, 3);
                return ;
            }
        }while(opc!='s'||opc!='S'||opc=='n'||opc=='N');
    }
    else{
        msj("El usuario no existe", 15, 3);
    }
}

void mostrar_usuario_tabla(Usuario reg){
    cout << left;
    cout << "    " <<setw(6)<< reg.ID;
    cout << setw(16) << reg.apellidos;
    cout << setw(16) << reg.nombres;
    cout << setw(8) << reg.altura;
    cout << setw(6) << reg.peso;
    cout << setw(11);
    switch (reg.perfil){
	case 'a':
	case 'A': cout << 'A';
		break;
	case 'b':
	case 'B': cout << 'B';
		break;
	case 'c':
	case 'C': cout << 'C';
		break;
	}
    if(reg.apto==1){
    cout << setw(13) << "Si";
    }
    else{
        cout << setw(13) << "No";
    }
    mostrar_fecha(reg.nacimiento);
}



























































































