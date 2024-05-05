#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct Tarea{
    int TareaID;
    char * Descripcion;
    int Duracion;
}Tarea;

typedef struct Nodo{
    Tarea T;
    struct Nodo * siguiente;
}Nodo;

Nodo * crearListaVacia();
Nodo * crearNodo(int id);
void cargarPendientes(Nodo **P, int * id);
Nodo * quitar_pendiente(Nodo **P, int id_quitar);
void transferirARealizada(Nodo **R, Nodo *quitado);
void mostrarLista(Nodo *L);
Nodo * buscarPorId(Nodo *L, int id_buscar);
Nodo * buscarPorPalabra(Nodo *L, char * palabra);
void listarNodo(Nodo *L);

int main(){
    srand(time(NULL));
    int id=1000, id_quitar, id_buscar;
    int opcion;
    char * palabra = (char *)malloc(sizeof(char) * 20);

    Nodo * pendientes = crearListaVacia();
    Nodo * realizadas = crearListaVacia();

    do
    {
        printf("\n------MENU------");
        printf("\n1- Cargar tarea pendiente");
        printf("\n2- Transferir pendiente a realizada");
        printf("\n3- Listar pendientes");
        printf("\n4- Listar realizadas");
        printf("\n5- Buscar tarea por ID");
        printf("\n6- Buscar por palabra clave");
        printf("\nOpcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
            case 1: cargarPendientes(&pendientes, &id);
                break;
            case 2: printf("\nTarea a quitar: ");
                    scanf("%d", &id_quitar);
                    Nodo * nodo_quitado = quitar_pendiente(&pendientes, id_quitar);
                    if (nodo_quitado){
                        transferirARealizada(&realizadas, nodo_quitado);
                    } else {
                        printf("\nNo se encontro la tarea");
                    }
                    
                break;
            case 3: mostrarLista(pendientes);
                break;
            case 4: mostrarLista(realizadas);
                break;
            case 5: printf("\nTarea a buscar: ");
                    scanf("%d", &id_buscar);
                    Nodo * encontrado1 = buscarPorId(pendientes, id_buscar);
                    if (encontrado1){
                        listarNodo(encontrado1);
                        printf("\nTarea ubicada en pendientes");

                    } else {
                        Nodo * encontrado2 = buscarPorId(realizadas, id_buscar);
                        if(encontrado2){
                            listarNodo(encontrado2);
                            printf("\nTarea ubicada en realizadas");
                        } else {
                            printf("\nTarea no encontrada");
                        }
                    }
                break;
            case 6: printf("\nPalabra a buscar: ");
                    fflush(stdin);
                    gets(palabra);
                    palabra = (char *)realloc(palabra, sizeof(char) * (strlen(palabra) + 1));
                    Nodo * encontrado3 = buscarPorPalabra(pendientes, palabra);
                    if (encontrado3){
                        listarNodo(encontrado3);
                        printf("\nTarea ubicada en pendientes");

                    } else {
                        Nodo * encontrado4 = buscarPorPalabra(realizadas, palabra);
                        if(encontrado4){
                            listarNodo(encontrado4);
                            printf("\nTarea ubicada en realizadas");
                        } else {
                            printf("\nTarea no encontrada");
                        }
                    }
        }
    } while (opcion != 0);
    
}

Nodo * crearListaVacia()
{
    return NULL;
}

Nodo *crearNodo(int id)
{
    Nodo * nuevo = (Nodo *)malloc(sizeof(Nodo));
    
    nuevo->T.TareaID = id;
    nuevo->T.Duracion = rand() % 91 + 10;
    
    char * buff = (char *)malloc(sizeof(char) * 50);
    printf("\nDescripcion: ");
    fflush(stdin);
    gets(buff);
    nuevo->T.Descripcion = (char *)malloc(sizeof(char) * (strlen(buff) + 1));
    strcpy(nuevo->T.Descripcion, buff);
    free(buff);

    nuevo->siguiente = NULL;
}

void cargarPendientes(Nodo **P, int *id)
{
    Nodo * nuevo = crearNodo(*id);
    (*id)++;
    nuevo->siguiente = *P;
    *P = nuevo;
}

Nodo *quitar_pendiente(Nodo **P, int id_quitar)
{
    Nodo * actual = *P;
    Nodo * anterior = NULL;
    while (actual && id_quitar != actual->T.TareaID)
    {
        anterior = actual;
        actual = actual->siguiente;
    }
    
    if(anterior == NULL){ //si el id encontrado es el primer nodo
        *P = actual->siguiente;
    } else { //si lo encontro pero no es el primero
        anterior->siguiente = actual->siguiente;
    }
    
    return actual;

}

void transferirARealizada(Nodo **R, Nodo *quitado)
{
    quitado->siguiente = *R;
    *R = quitado;
}

void listarNodo(Nodo *L)
{
    printf("\n----------");
    printf("\nID: %d", L->T.TareaID);
    printf("\nDescripcion: %s", L->T.Descripcion);
    printf("\nDuracion: %d", L->T.Duracion);
    printf("\n----------");
}

void mostrarLista(Nodo *L)
{
    Nodo * aux = L;
    if(aux){
        while (aux)
        {
            listarNodo(aux);
            aux = aux->siguiente;
        }
    } else {
        printf("\nNo hay tareas");
    }
    
}

Nodo * buscarPorId(Nodo *L, int id_buscar)
{
    Nodo * aux = L;

    while (aux && aux->T.TareaID != id_buscar)
    {
        aux = aux->siguiente;
    }

    return aux;
    
    
}

Nodo *buscarPorPalabra(Nodo *L, char *palabra)
{
    Nodo * aux = L;

    while (aux && !strstr(aux->T.Descripcion, palabra)) //strstr busca la primera ocurrencia de palabra en la descripcion
    {
        aux = aux->siguiente;
    }

    return aux;
    
}
