#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int TareaID;         //Numerado en ciclo iterativo
    char *Descripcion;   //
    int Duracion;        // entre 10 – 100
} Tarea;

typedef struct nodo{
    Tarea T;
    nodo* Siguiente;
} TNodo;

TNodo* CrearListaVacia();
void CrearNodo(TNodo** Start, Tarea** T);
void InsertarNodo(TNodo** tareas, TNodo** que);
void EliminarNodo(TNodo** tareas, int id);

void CargarTareas(TNodo** tareas, int cantidad);
void ListarTareas(TNodo** tareasPendientes, TNodo** tareasRealizadas);
void MostrarTareas(TNodo** tareas);
TNodo BuscarTarea(TNodo** tareasPendientes, TNodo** tareasRealizadas);
TNodo BuscarPorPalabra(TNodo** tareasPendientes, TNodo** tareasRealizadas);

int main()
{
    int cantidad_tareas;

    TNodo* TareasPendientes = CrearListaVacia();
    TNodo* TareasRealizadas = CrearListaVacia();

    printf("Ingrese cantidad de tareas a cargar: ");
    scanf("%d", &cantidad_tareas);
    fflush(stdin);

    CargarTareas(&TareasPendientes, cantidad_tareas);
    system("cls");
   
    ListarTareas(&TareasPendientes, &TareasRealizadas);
    system("cls");

    printf("/////////////////////////////////////////////////////\n");
    printf("Tareas Realizadas: \n");
    MostrarTareas(&TareasRealizadas);
    printf("/////////////////////////////////////////////////////\n");
    printf("Tarea Pendientes: \n");
    MostrarTareas(&TareasPendientes);

    //Busqueda por ID y por Palabra
    printf("\n/////////////////////////////////////////////////////\n");
    TNodo aux;
    aux = BuscarTarea(&TareasPendientes, &TareasRealizadas);
    printf("ID: %d\n", aux.T.TareaID);
    printf("Descripcion: %s\n", aux.T.Descripcion);
    printf("Duracion: %d\n\n", aux.T.Duracion);
    
    TNodo aux2;
    aux2 = BuscarPorPalabra(&TareasPendientes, &TareasRealizadas);
    printf("ID: %d\n", aux2.T.TareaID);
    printf("Nombre: %s\n", aux2.T.Descripcion);
    printf("Duracion: %d\n\n", aux2.T.Duracion);

    system("PAUSE");
    return 0;
}

TNodo* CrearListaVacia()
{
    return NULL;
}

void CrearNodo(TNodo** Start, Tarea** T)
{
    TNodo* Nodo = (TNodo*) malloc(sizeof(TNodo));

    //Declaramos la tarea creada en el nodo
    Nodo->T = **T;
    Nodo->Siguiente = *Start;
    *Start = Nodo;
}

void EliminarNodo(TNodo** tareas, int id)
{
    TNodo* aux = *tareas;
    TNodo* auxAnterior = *tareas;
    //while (aux && (aux->T.TareaID != id) )
    while (aux && (aux->T.TareaID != id) )
    {
        auxAnterior = aux;
        aux = aux->Siguiente;
        printf("a\n");
    }
    
    if(aux)
    {
        aux->T.TareaID = 0;
        auxAnterior->Siguiente = aux->Siguiente;
        //free(aux);
    }
}

void CargarTareas(TNodo** tareas, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        //Creamos la tarea
        Tarea* T;
        T = (Tarea *) malloc(sizeof(Tarea));
        char descrip[30];
        T->TareaID = i+1;

        printf("Ingrese la descripcion de la tarea: ");
        gets(descrip);
        T->Descripcion = (char*) malloc(strlen(descrip) * sizeof(char));
        strcpy(T->Descripcion, descrip);

        T->Duracion = rand() % 100 + 1;

        CrearNodo(tareas, &T);
    }
}

void ListarTareas(TNodo** tareasPendientes, TNodo** tareasRealizadas)
{
    char resp;
    TNodo* aux = *tareasPendientes;
    
    printf("TAREAS: \n");
    while (aux != NULL)
    {
        printf("ID: %d\n", aux->T.TareaID);
        printf("Descripcion: %s\n", aux->T.Descripcion);
        printf("Duracion: %d\n\n", aux->T.Duracion);

        printf("La tarea fue realizada? (S o N) ");
        scanf("%c", &resp);
        fflush(stdin);

        if(tolower(resp) == 's')
        {
            Tarea* T;
            T = (Tarea *) malloc(sizeof(Tarea));
            *T = aux->T;
            
            CrearNodo(tareasRealizadas, &T);
            EliminarNodo(tareasPendientes, aux->T.TareaID);
        }
        aux = aux->Siguiente;
    }
}

void MostrarTareas(TNodo** tareas)
{
    TNodo* aux = *tareas;
    while(aux && aux->T.TareaID != 0)
    {
        printf("ID: %d\n", aux->T.TareaID);
        printf("Descripcion: %s\n", aux->T.Descripcion);
        printf("Duracion: %d\n\n", aux->T.Duracion);

        aux = aux->Siguiente;
    }
}

TNodo BuscarTarea(TNodo** tareasPendientes, TNodo** tareasRealizadas)
{
    int id;
    TNodo* aux = *tareasPendientes;
    TNodo* auxRealizadas = *tareasRealizadas;

    printf("Ingrese el ID de la tarea a buscar: ");
    scanf("%d", &id);
    fflush(stdin);

    while (aux && aux->T.TareaID != id)
    {
        aux = aux->Siguiente;
    }
    if(aux)
    {
        return *aux;
    }

    while (auxRealizadas && auxRealizadas->T.TareaID != id)
    {
        auxRealizadas = auxRealizadas->Siguiente;
    }
    if(auxRealizadas)
    {
        return *auxRealizadas;
    }

    TNodo nula;
    nula.T.TareaID = 0;
    nula.T.Descripcion = "0";
    nula.T.Duracion= 0;
    return nula;
}

TNodo BuscarPorPalabra(TNodo** tareasPendientes, TNodo** tareasRealizadas)
{
    char palabra[20];
    TNodo* aux = *tareasPendientes;
    TNodo* auxRealizadas = *tareasRealizadas;

    printf("Ingrese la palabra a buscar: ");
    gets(palabra);

    while (aux && (strstr(aux->T.Descripcion, palabra) == NULL) )
    {
        aux = aux->Siguiente;
    }
    if(aux)
    {
        return *aux;
    }

    while (auxRealizadas && (strstr(auxRealizadas->T.Descripcion, palabra) == NULL) )
    {
        auxRealizadas = auxRealizadas->Siguiente;
    }
    if(auxRealizadas)
    {
        return *auxRealizadas;
    }

    TNodo nula;
    nula.T.TareaID = 0;
    nula.T.Descripcion = "0";
    nula.T.Duracion= 0;
    return nula;
}