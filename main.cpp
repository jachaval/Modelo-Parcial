#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <locale.h>
#include <ctime>
#include "rlutil.h"
using namespace std;
using namespace rlutil;
#include "menu.h"
#include "usuario.h"
#include "fecha.h"

int main() {

	setlocale(LC_ALL, "spanish");
	menu_principal();

	return 0;
}
