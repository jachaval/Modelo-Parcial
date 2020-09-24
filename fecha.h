#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

struct Fecha {
	int dia, mes, anio;
};

void mostrar_fecha(Fecha);
Fecha cargar_fecha();
Fecha mostrar_fechaactual();
bool verificar_fecha(Fecha);
bool verificar_mayorDeEdad(Fecha,int);

#endif // FECHA_H_INCLUDED
