#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int TareaID;         //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion;        // entre 10 – 100
} Tarea;

void CargarTareas(Tarea** tareas, int cantidad);
void ListarTareas(Tarea** tareas, Tarea** tareasRealizadas, int cantidad);
void MostrarTareas(Tarea** tareas, int cantidad);
Tarea BuscarTarea(Tarea** tareas, Tarea** tareasRealizadas, int cantidad);

int main()
{
    int cantidad_tareas;
    Tarea** tareas;
    Tarea** tareasRealizadas;

    printf("Ingrese cantidad de tareas a cargar: ");
    scanf("%d", &cantidad_tareas);

    tareas = (Tarea**) malloc(cantidad_tareas * sizeof(Tarea*));
    tareasRealizadas = (Tarea**) malloc(cantidad_tareas * sizeof(Tarea*));

    CargarTareas(tareas, cantidad_tareas);
    system("cls");
    ListarTareas(tareas, tareasRealizadas, cantidad_tareas);
    system("cls");

    printf("Tareas Realizadas: \n");
    MostrarTareas(tareasRealizadas, cantidad_tareas);

    printf("\nTarea Pendientes: \n");
    MostrarTareas(tareas, cantidad_tareas);

    Tarea aux;
    aux = BuscarTarea(tareas, tareasRealizadas, cantidad_tareas);
    printf("ID: %d\n", aux.TareaID);
    printf("Nombre: %s\n", aux.Descripcion);
    printf("Duracion: %d\n\n", aux.Duracion);
    
    getchar();
    system("PAUSE");
    return 0;
}

void CargarTareas(Tarea** tareas, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        tareas[i] = (Tarea *) malloc(sizeof(Tarea));
        char descrip[30];
        tareas[i]->TareaID = i+1;

        printf("Ingrese la descripcion de la tarea: ");
        scanf("%s", descrip);
        tareas[i]->Descripcion = (char*) malloc(strlen(descrip) * sizeof(char));
        strcpy(tareas[i]->Descripcion, descrip);

        tareas[i]->Duracion = rand() % 100 + 1;
    }
}

void ListarTareas(Tarea** tareas, Tarea** tareasRealizadas, int cantidad)
{
    char resp;
    int cont = 0;

    printf("TAREAS: \n");
    for (int i = 0; i < cantidad; i++)
    {
        printf("ID: %d\n", tareas[i]->TareaID);
        printf("Nombre: %s\n", tareas[i]->Descripcion);
        printf("Duracion: %d\n\n", tareas[i]->Duracion);

        fflush(stdin);
        printf("La tarea fue realizada? (S o N) ");
        scanf("%c", &resp);

        if(tolower(resp) == 's')
        {
            tareasRealizadas[cont] = tareas[i];
            tareas[i] = NULL;
        }
        else
        {
            tareasRealizadas[cont] = NULL;
        }
        cont++;
    }
}

void MostrarTareas(Tarea** tareas, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        if(tareas[i])
        {
            printf("ID: %d\n", tareas[i]->TareaID);
            printf("Nombre: %s\n", tareas[i]->Descripcion);
            printf("Duracion: %d\n\n", tareas[i]->Duracion);
        }
    }
}

Tarea BuscarTarea(Tarea** tareas, Tarea** tareasRealizadas, int cantidad)
{
    int id;

    printf("Ingrese el ID de la tarea a buscar: ");
    scanf("%d", &id);

    for (int i = 0; i < cantidad; i++)
    {
        if(tareas[i] && tareas[i]->TareaID == id)
        {
            return *tareas[i];
        }
        if(tareasRealizadas[i] &&  tareasRealizadas[i]->TareaID == id)
        {
            return *tareasRealizadas[i];
        }
    }

    Tarea nula;
    nula.TareaID = 0;
    return nula;
}