#ifndef ENTRENAMIENTO_H_INCLUDED
#define ENTRENAMIENTO_H_INCLUDED

#include "fecha.h"

struct Entrenamiento{
    int ID;
    int IDusuario;
    Fecha entrena;//no ser mayor a la fecha actual, tenemos que usar la fecha del sistema
    int actividad; //entre 1 y 5. 1=caminata/2=correr/3=bicicleta
    // solo con apto 4=natacion/5=pesas
    float calorias;
    int tiempo; //minutos
};

void cargar_entrenamientos();
Entrenamiento cargar_entrenamiento(int);
bool guardar_entrenamiento(Entrenamiento);
void listar_entrenamiento_x_idusuario();
bool verificar_usuario(int);
void listar_entrenamiento_x_id();
bool verificar_apto(int codigo_buscado);
void listar_entrenamiento();
void mostrar_entrenamiento(Entrenamiento);
int buscar_entrenamiento(int codigo_entrenamiento);
Entrenamiento leer_entrenamiento_x_idusuario(int pos);
int buscar_entrenamiento2(int codigo_entrenamiento);
int cargar_actividad(bool);
int cargar_tiempo();
float cargar_calorias();
void cargar_entrenamientos2();
bool guardar_entrenamiento2(Entrenamiento reg);
void mostrar_actividad(Entrenamiento);
int cantidad_entrenamientos();
int cargar_ID();
void modificar_entrenamiento();
Entrenamiento leer_entrenamiento_x_id(int pos);
bool guardar_entrenamiento3(Entrenamiento reg, int pos);
void ordenar_entrenamiento(Entrenamiento *vec, int tam);
void mostrar_entrenamiento_tabla(Entrenamiento reg);

#endif // ENTRENAMIENTO_H_INCLUDED
