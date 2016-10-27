// Proyecto pensamiento.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#define MAX_NOMBRE 50
#define MAX_CAPACIDAD 10
#define MAX_CLIENTES 100

struct Cliente
{
	char nombre[MAX_NOMBRE];
	long cedula;
	char filaUsuario;
	int columnaUsuario;
};

int menu();
void  mostrarTeatro(char[MAX_CAPACIDAD][MAX_CAPACIDAD]);
void reservarSilla(char, int, char[MAX_CAPACIDAD][MAX_CAPACIDAD], Cliente[MAX_CLIENTES]);
void comprarBoleta(char, int, char[MAX_CAPACIDAD][MAX_CAPACIDAD], Cliente[MAX_CLIENTES]);
void cancelarCompraOReserva(char, int, char[MAX_CAPACIDAD][MAX_CAPACIDAD], Cliente[MAX_CLIENTES]);
void consultarListaClientes(Cliente[MAX_CLIENTES]);
bool verificarSillaLibre(char, int, char[MAX_CAPACIDAD][MAX_CAPACIDAD]);
bool verificarSillaReservada(char, int, char[MAX_CAPACIDAD][MAX_CAPACIDAD]);
bool verificarSillaComprada(char, int, char[MAX_CAPACIDAD][MAX_CAPACIDAD]);
bool buscarCedula(int, Cliente[MAX_CLIENTES]);
int convertirFila(char);

using namespace std;

char fila;
int columna;
int contador = 0;
char continuar;

int main()
{
	char teatroNacional[MAX_CAPACIDAD][MAX_CAPACIDAD];
	int opcion;
	Cliente usuarios[MAX_CLIENTES];

	for (int i = 0; i < MAX_CAPACIDAD; i++)
	{
		for (int j = 0; j < MAX_CAPACIDAD; j++)
		{
			teatroNacional[i][j] = 'l';
		}
	}


	do
	{
		opcion = menu();
		switch (opcion)
		{
		case 1:
			mostrarTeatro(teatroNacional);
			break;
		case 2:
			reservarSilla(fila, columna, teatroNacional, usuarios);
			break;
		case 3:
			comprarBoleta(fila, columna, teatroNacional, usuarios);
			break;
		case 4:
			cancelarCompraOReserva(fila, columna, teatroNacional, usuarios);
			break;
		case 5:
			consultarListaClientes(usuarios);
			break;
		default:
			cout << "...";
			break;
		}
		cout << endl;
		cout << "Desea continuar (s/n): ";
		cin >> continuar;
		system("cls");
	} while (continuar == 's' || continuar == 'S');


	return 0;
}

int menu()
{
	int op;
	do
	{
		cout << " _____________________________________________" << endl;
		cout << "|        Bienvenido al Teatro Nacional        |" << endl;
		cout << "|_____________________________________________|" << endl;
		cout << "|1.Mostrar Teatro			      |" << endl;
		cout << "|2.Reservar Silla			      |" << endl;
		cout << "|3.Comprar Boleta			      |" << endl;
		cout << "|4.Cancelar Compra o Reserva                  |" << endl;
		cout << "|5.Consultar lista de clientes   	      |" << endl;
		cout << "|_____________________________________________|" << endl;
		cout << endl;
		cin >> op;
	} while (op <= 0 || op >= 6);
	return op;
}

void mostrarTeatro(char teatro[MAX_CAPACIDAD][MAX_CAPACIDAD])
{
	int contador = 0;
	cout << "  1 2 3 4 5 6 7 8 9 10 " << endl;
	for (int i = 0; i < MAX_CAPACIDAD; i++)
	{
		cout << char(65 + contador) << " ";
		contador++;

		for (int j = 0; j < MAX_CAPACIDAD; j++)
		{
			cout << teatro[i][j] << " ";

		}
		cout << endl;
	}
}

void reservarSilla(char fila, int columna, char teatroNacional[][MAX_CAPACIDAD], Cliente usuarios[MAX_CLIENTES])
{
	cout << "Digite su nombre: ";
	cin >> usuarios[contador].nombre;

	do
	{
		cout << "Digite su cedula: ";
		cin >> usuarios[contador].cedula;
	} while (buscarCedula(usuarios[contador].cedula, usuarios) == true);

	cout << "Digite la fila donde desea reservar la silla (a-j): ";
	cin >> usuarios[contador].filaUsuario;
	cout << "Digite la columna donde desea reservar la silla (1-10): ";
	cin >> usuarios[contador].columnaUsuario;
	if (verificarSillaLibre(usuarios[contador].filaUsuario, usuarios[contador].columnaUsuario, teatroNacional) == true)
	{
		int filaNumero;
		filaNumero = convertirFila(usuarios[contador].filaUsuario);
		teatroNacional[filaNumero][(usuarios[contador].columnaUsuario) - 1] = 'r';
		cout << "Apreciad@ " << usuarios[contador].nombre << " su silla ya qued" << char(162) << " reservada" << endl;
		mostrarTeatro(teatroNacional);
	}
	else
	{
		cout << "La silla ya est" << char(160) << " reservada o comprada" << endl;
	}
	contador++;
}

void comprarBoleta(char fila, int columna, char teatroNacional[][MAX_CAPACIDAD], Cliente usuarios[MAX_CLIENTES])
{

	cout << "Digite su nombre: ";
	cin >> usuarios[contador].nombre;
	do
	{
		cout << "Digite su cedula: ";
		cin >> usuarios[contador].cedula;
	} while (buscarCedula(usuarios[contador].cedula, usuarios) == true);
	cout << "Digite la fila donde desea reservar la silla (a-j): ";
	cin >> usuarios[contador].filaUsuario;
	cout << "Digite la columna donde desea reservar la silla (1-10): ";
	cin >> usuarios[contador].columnaUsuario;

	if (verificarSillaLibre(usuarios[contador].filaUsuario, usuarios[contador].columnaUsuario, teatroNacional) == true)
	{
		if (verificarSillaReservada(usuarios[contador].filaUsuario, usuarios[contador].columnaUsuario, teatroNacional) == false)
		{
			int filaNumero;
			filaNumero = convertirFila(usuarios[contador].filaUsuario);
			teatroNacional[filaNumero][(usuarios[contador].columnaUsuario) - 1] = 'c';
			cout << "Apreciad@ " << usuarios[contador].nombre << " su silla ya qued" << char(162) << " comprada" << endl;
			mostrarTeatro(teatroNacional);
		}
		else
		{
			cout << "La silla ya est" << char(160) << " reservada" << endl;
		}
	}
	else
	{
		cout << "La silla ya est" << char(160) << " comprada y/o reservada" << endl;
	}
	contador++;
}

void cancelarCompraOReserva(char fila, int columna, char teatroNacional[][MAX_CAPACIDAD], Cliente usuarios[MAX_CLIENTES])
{
	int aux;
	int posicion;
	cout << "Ingrese cedula " << endl;
	cin >> aux;
	for (int i = 0; i<contador; i++)
	{
		if (aux == usuarios[i].cedula)
		{
			cout << "Bienvenid@ " << aux << endl;
			int filaNumero;
			filaNumero = convertirFila(usuarios[i].filaUsuario);
			teatroNacional[filaNumero][(usuarios[i].columnaUsuario) - 1] = 'l';
			mostrarTeatro(teatroNacional);
			posicion = i;
		}
	}
	for (int j = posicion; j <= contador - 1; j++)
	{
		usuarios[j] = usuarios[j + 1];
	}
}

void consultarListaClientes(Cliente usuarios[MAX_CLIENTES])
{
	for (int i = 0; i<contador; i++)
	{
		cout << "Nombre: " << usuarios[i].nombre << endl;
		cout << "Cedula: " << usuarios[i].cedula << endl;
		cout << "Silla: " << usuarios[i].filaUsuario << "-" << usuarios[i].columnaUsuario << endl;
	}
}

bool verificarSillaLibre(char fila, int columna, char matrizAuxiliar[MAX_CAPACIDAD][MAX_CAPACIDAD])
{
	bool flag;
	int filaNumero;
	filaNumero = convertirFila(fila);

	if (matrizAuxiliar[filaNumero][columna - 1] == 'l')
	{
		flag = true;
	}
	else
	{
		flag = false;
	}
	return flag;
}

bool verificarSillaReservada(char fila, int columna, char matrizAuxiliar[MAX_CAPACIDAD][MAX_CAPACIDAD])
{
	bool flag;
	int filaNumero;
	filaNumero = convertirFila(fila);

	if (matrizAuxiliar[filaNumero][columna - 1] == 'r')
	{
		flag = true;
	}
	else
	{
		flag = false;
	}
	return flag;
}

bool verifivarSillaComprada(char fila, int columna, char matrizAuxiliar[MAX_CAPACIDAD][MAX_CAPACIDAD])
{
	bool flag;
	int filaNumero;
	filaNumero = convertirFila(fila);

	if (matrizAuxiliar[filaNumero][columna - 1] == 'c')
	{
		flag = true;
	}
	else
	{
		flag = false;
	}
	return flag;
}

int convertirFila(char fila)
{
	int numero;
	switch (fila)
	{
	case 'a':
	case 'A':
		numero = 0;
		break;
	case 'b':
	case 'B':
		numero = 1;
		break;
	case 'c':
	case 'C':
		numero = 2;
		break;
	case 'd':
	case 'D':
		numero = 3;
		break;
	case 'e':
	case 'E':
		numero = 4;
		break;
	case 'f':
	case 'F':
		numero = 5;
		break;
	case 'g':
	case 'G':
		numero = 6;
		break;
	case 'h':
	case 'H':
		numero = 7;
		break;
	case 'i':
	case 'I':
		numero = 8;
		break;
	case 'j':
	case 'J':
		numero = 9;
		break;
	default:
		break;
	}
	return numero;
}

bool buscarCedula(int cedula, Cliente usuarios[MAX_CLIENTES])
{
	bool flag = false;

	for (int i = 0; i < contador; i++)
	{
		if (cedula == usuarios[i].cedula)
		{
			flag = true;
		}
	}

	return flag;
}