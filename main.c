#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NOMBRE_ARCHIVO "registroJugador.dat"


///////////////////// ESTRUCTURAS ////////////////////////////////
typedef struct
{
    int idRegistro;
    int nroJugador;
    char nombreJugador[30];
    char apellidoJugador[30];
    int clase; // año de nacimiento
    char puestoJugador[30]; /**Delantero - Medio - Defensor - Arquero*/
    char nombreEquipo[30];
    int puntosGanados;
} stRegistroJugador;


typedef struct
{
    int nroJugador;
    char nombreJugador[30];
    char apellidoJugador[30];
    int clase;
    char puestoJugador[30];
} stJugador;


typedef struct
{
    int idEquipo;
    char nombreEquipo[30];
    int puntosGanados;
} stEquipo;

typedef struct nodoArbolJugador
{
    stJugador jugador;
    struct nodoArbolJugador * der;
    struct nodoArbolJugador * izq;
} nodoArbolJugador;

typedef struct arregloEquipo
{
    stEquipo equipo;
    nodoArbolJugador * arbolJugadores;
} arregloEquipo;



////////////////////// PROTOTIPADOS ////////////////////////////

// FUNCIONES PUNTO 1

nodoArbolJugador * insertarNodo(nodoArbolJugador * arbol,stJugador jugador);
nodoArbolJugador * crearNodoArbol(stJugador jugador);
nodoArbolJugador * inicArborl();

// FUNCIONES PUNTO 2

int buscarPosArregloEquipos(arregloEquipo arrEquipo[],int validos, char nombreEquipo[]);
int agregarEquipo(arregloEquipo arrEquipo[], int validos, char nombreEquipo[]);
int altaJugadores(arregloEquipo arrEquipo[], stJugador jugador, char nombreEquipo[],int validos);

// FUNCIONES PUNTO 3

int pasarArchivoToADA(arregloEquipo arrEquipo[],int dimension,char nombreArchivo[]);

// FUNCIONES PUNTO 4

void mostrarUnJugador(stJugador jugador);
void mostrarArbolJugadores(nodoArbolJugador * arbol);
void mostrarUnEquipo(stEquipo equipo);
void mostrarADA(arregloEquipo arrEquipo[],int validos);

// FUNCIONES PUNTO 5

int buscarJugadorArbol(nodoArbolJugador * arbol, stJugador jugador);
int buscarJugadorPorNombre(nodoArbolJugador * arbol, stJugador jugador);
int buscarJugadorPorApellido(nodoArbolJugador * arbol, stJugador jugador);
int buscarJugadorPorNro(nodoArbolJugador * arbol, stJugador jugador);
int buscarEquipoArreglo(arregloEquipo arrEquipo[],int validos, char nombreEquipo[],stJugador jugador);




//////////////////////// MAIN ///////////////////////////////

// 6. Desarrolle un main() e invoque únicamente a las funciones que compilen
//      correctamente. La resolución de este es obligatoria y sumara puntos extras en caso
//      de necesitarlos.

int main()
{
    arregloEquipo arrEquipo[100];
    int validos = pasarArchivoToADA(arrEquipo,100,NOMBRE_ARCHIVO);
    mostrarADA(arrEquipo,validos);
    stJugador jugador;
    char nombreEquipo[20];
    printf("\n\nIngrese el nombre del jugador buscado: ");
    fflush(stdin);
    gets(jugador.nombreJugador);
    printf("\n\nIngrese el apellido del jugador buscado: ");
    fflush(stdin);
    gets(jugador.apellidoJugador);
    printf("\n\nIngrese el numero del jugador buscado: ");
    scanf("%d",&jugador.nroJugador);
    printf("\n\nIngrese el equipo del jugador buscado: ");
    fflush(stdin);
    gets(nombreEquipo);

    int flag = buscarEquipoArreglo(arrEquipo,validos,nombreEquipo,jugador);

    if(flag != -1){
        printf("\n\nJUGADOR ENCONTRADO!!");
        printf("\n\nSu numero es: %d",flag);
    }else{
        printf("\n\nJugador No encontrado :(");
    }

    return 0;
}



////////////////////////// FUNCIONES ///////////////////////////////////


// 1. Desarrolle las funciones necesarias para la Gestión de Carga de datos del Árbol
//(Crear los nodos, agregarlos al árbol y mostrar nodos del árbol) (15 puntos)

nodoArbolJugador * inicArborl()
{
    return NULL;
}

nodoArbolJugador * crearNodoArbol(stJugador jugador)
{
    nodoArbolJugador * aux = (nodoArbolJugador*) malloc(sizeof(nodoArbolJugador));
    aux->jugador = jugador;
    aux->der = NULL;
    aux->izq = NULL;

    return aux;
}


nodoArbolJugador * insertarNodo(nodoArbolJugador * arbol,stJugador jugador)
{
    if(arbol == NULL)
    {
        arbol = crearNodoArbol(jugador);
    }
    else
    {
        if(jugador.clase > arbol->jugador.clase)
        {
            arbol->der = insertarNodo(arbol->der, jugador);
        }
        else
        {
            arbol->izq = insertarNodo(arbol->der,jugador);
        }
    }
    return arbol;
}

// 2. Desarrolle las funciones necesarias para la Gestión del Arreglo de Arboles.
//        a. Buscar la Posición del Árbol de Jugadores en el Arreglo de acuerdo con el
//            nombre del Equipo.



int buscarPosArregloEquipos(arregloEquipo arrEquipo[],int validos, char nombreEquipo[])
{
    int pos = -1;
    int index = 0;
    while(index < validos)
    {
        if(strcmp(arrEquipo[index].equipo.nombreEquipo,nombreEquipo) == 0)
        {
            pos = index;
        }
        index++;
    }
    return pos;
}

//        b. Agregar un Equipo Nuevo.

int agregarEquipo(arregloEquipo arrEquipo[], int validos, char nombreEquipo[])
{
    srand(time(NULL));
    strcpy(arrEquipo[validos].equipo.nombreEquipo,nombreEquipo);
    arrEquipo[validos].equipo.idEquipo = rand()%1000;
    arrEquipo[validos].arbolJugadores = inicArborl();
    validos++;
    return validos;
}

//        c. Dar de alta los jugadores de acuerdo al Equipo.

int altaJugadores(arregloEquipo arrEquipo[], stJugador jugador, char nombreEquipo[],int validos)
{
    int pos = buscarPosArregloEquipos(arrEquipo,validos,nombreEquipo);
    if(pos == -1)
    {
        validos = agregarEquipo(arrEquipo,validos,nombreEquipo);
        pos = validos - 1;
    }
    arrEquipo[pos].arbolJugadores = insertarNodo(arrEquipo[pos].arbolJugadores,jugador);
    return validos;
}

// 3. Hacer una función que lea el archivo e integre todas las funciones del punto 1 y 2,
// y cargue los 100 jugadores y sus equipos.


int pasarArchivoToADA(arregloEquipo arrEquipo[],int dimension, char nombreArchivo[])
{
    FILE * archi = fopen(nombreArchivo,"rb");
    stRegistroJugador regJugador;
    stJugador jugador;
    int validos = 0;
    if(archi)
    {
        while(fread(&regJugador,sizeof(stRegistroJugador),1,archi)> 0 && validos < dimension)
        {
            jugador.nroJugador = regJugador.nroJugador;
            jugador.clase = regJugador.clase;
            strcpy(jugador.nombreJugador,regJugador.nombreJugador);
            strcpy(jugador.apellidoJugador,regJugador.apellidoJugador);
            strcpy(jugador.puestoJugador,regJugador.puestoJugador);
            validos = altaJugadores(arrEquipo,jugador,regJugador.nombreEquipo,validos);
        }
        fclose(archi);
    }
    else
    {
        printf("\n\nERROR\n\n");
    }
    return validos;
}


// 4. Realizar una función que muestre todos los jugadores organizados por equipo. Modularizar.

void mostrarUnJugador(stJugador jugador)
{
    printf("\n\t%d",jugador.nroJugador);
    printf("\n\t%s",jugador.nombreJugador);
    printf("\n\t%s",jugador.apellidoJugador);
    printf("\n\t%s",jugador.puestoJugador);
    printf("\n\t%d",jugador.clase);
}

void mostrarArbolJugadores(nodoArbolJugador * arbol)
{
    if(arbol)
    {
        mostrarUnJugador(arbol->jugador);
        mostrarArbolJugadores(arbol->der);
        mostrarArbolJugadores(arbol->izq);
    }
}

void mostrarUnEquipo(stEquipo equipo)
{
    printf("\n---------------------");
    printf("\n%d",equipo.idEquipo);
    printf("\n%s",equipo.nombreEquipo);
    printf("\n%d",equipo.puntosGanados);
}

void mostrarADA(arregloEquipo arrEquipo[],int validos)
{
    int index;
    for(index = 0; index < validos; index++)
    {
        mostrarUnEquipo(arrEquipo[index].equipo);
        mostrarArbolJugadores(arrEquipo[index].arbolJugadores);
    }
}


//5. Codifique las funciones que necesita para resolver la tarea de buscar el número de
//  un jugador conociendo su equipo, su nombre y apellido. Para desarrollar las
//  funciones, piense qué responsabilidad tiene cada TDA trabajado.

int buscarJugadorArbol(nodoArbolJugador * arbol, stJugador jugador)
{
    int flag = buscarJugadorPorNombre(arbol,jugador);
    if(arbol != NULL)
    {
        if(flag != -1)
        {
            flag = buscarJugadorPorApellido(arbol,jugador);
            if(flag != -1)
            {
                flag = buscarJugadorPorNro(arbol,jugador);
            }
            else
            {
                flag = buscarJugadorArbol(arbol->der,jugador);
                if(flag == -1)
                {
                    flag = buscarJugadorArbol(arbol ->izq,jugador);
                }
            }
        }
        else
        {
            flag = buscarJugadorArbol(arbol->der,jugador);
            if(flag == -1)
            {
                flag = buscarJugadorArbol(arbol ->izq,jugador);
            }
        }
    }

    return flag;
}

int buscarJugadorPorNombre(nodoArbolJugador * arbol, stJugador jugador)
{
    int flag = -1;
    if(arbol)
    {
        if(strcmp(arbol->jugador.nombreJugador,jugador.nombreJugador) == 0)
        {
            flag = jugador.nroJugador;
        }
        else
        {
            if(strcmp(arbol->jugador.nombreJugador,jugador.nombreJugador) < 0)
            {
                flag = buscarJugadorPorNombre(arbol->der,jugador);
            }
            else
            {
                flag = buscarJugadorPorNombre(arbol->izq,jugador);
            }
        }
    }
    return flag;
}

int buscarJugadorPorApellido(nodoArbolJugador * arbol, stJugador jugador)
{
    int flag = -1;
    if(arbol)
    {
        if(strcmp(arbol->jugador.apellidoJugador,jugador.apellidoJugador) == 0)
        {
            flag = 1;
        }
        else
        {
            if(strcmp(arbol->jugador.apellidoJugador,jugador.apellidoJugador) < 0)
            {
                flag = buscarJugadorPorNombre(arbol->der,jugador);
            }
            else
            {
                flag = buscarJugadorPorNombre(arbol->izq,jugador);
            }
        }
    }
    return flag;
}



int buscarJugadorPorNro(nodoArbolJugador * arbol, stJugador jugador)
{
    int flag = -1;
    if(arbol)
    {
        if(arbol->jugador.nroJugador == jugador.nroJugador)
        {
            flag = 1;
        }
        else
        {
            if(arbol->jugador.nroJugador < jugador.nroJugador)
            {
                buscarJugadorPorNombre(arbol->der,jugador);
            }
            else
            {
                buscarJugadorPorNombre(arbol->izq,jugador);
            }
        }
    }
    return flag;
}


int buscarEquipoArreglo(arregloEquipo arrEquipo[],int validos, char nombreEquipo[],stJugador jugador){
    int index = 0;
    int flag = -1;
    while(index < validos && flag == -1){
        if(strcmp(arrEquipo[index].equipo.nombreEquipo,nombreEquipo) == 0){
            flag = buscarJugadorArbol(arrEquipo[index].arbolJugadores,jugador);
        }
        index++;
    }
    return flag;
}





