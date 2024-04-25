#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

struct{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}typedef Tarea;

typedef struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
}Nodo;

Nodo *crear_lista_vacia();
Nodo *crear_nodo(int id);
void insertar_pendientes(Nodo **Pendientes, int *id);
void mostrar_tareas(Nodo *tareas);
Nodo *quitar_pend(Nodo **Pendientes, int id_borrar);
void insertar_realizadas(Nodo **Realizadas, Nodo *quitado);
int buscar_por_id(Nodo *Realizadas, Nodo *Pendientes, int id_buscar);
int buscar_por_palabra_clave(Nodo *Realizadas, Nodo *Pendientes, char *palabra);

int main(){
    srand(time(NULL));

    int id = 1000, opcion, id_pend, id_buscar;
    char *palabra = (char *)malloc(sizeof(char) * 20);

    Nodo *Pendientes = crear_lista_vacia();
    Nodo *Realizadas = crear_lista_vacia();

    do{
        printf("\n-----MENU-----");
        printf("\n1- Agregar tarea pendiente");
        printf("\n2- Mostrar lista de pendientes");
        printf("\n3- Mostrar lista de realizadas");
        printf("\n4- Marcar tarea pendiente como realizada");
        printf("\n5- Buscar tarea por id");
        printf("\n6- Buscar tarea por palabra clave");
        printf("\nOpcion (0 para salir): ");
        scanf("%d", &opcion);
        switch (opcion){
            case 1: insertar_pendientes(&Pendientes, &id);
                break;
            case 2: if(Pendientes == NULL){
                        printf("\nNo tiene tareas pendientes");
                    } else {
                        mostrar_tareas(Pendientes);
                    }
                break;
            case 3: if (Realizadas == NULL){
                        printf("\nNo se ha realizado ninguna tarea");
                    }
                    else{
                        mostrar_tareas(Realizadas);
                    }
                break;
            case 4: printf("\nIngresar id a marcar como realizada: ");
                    scanf("%d", &id_pend);
                   
                    Nodo *nodo_quitado = quitar_pend(&Pendientes, id_pend);
                    if (nodo_quitado == NULL){
                        printf("\nNo se ha encontrado el id solicitado");
                    }
                    else{
                        printf("\nSe ha marcado como realizada la tarea de id %d", id_pend);
                        insertar_realizadas(&Realizadas, nodo_quitado);  
                    }
                break;
            case 5: printf("\nIngrese id a buscar: ");
                    scanf("%d", &id_buscar);
                    switch (buscar_por_id(Realizadas, Pendientes, id_buscar)){
                        case 0: printf("\nLa tarea de id %d no existe", id_buscar);
                            break;
                        case 1: printf("\nLa tarea de id %d se encuentra en tareas pendientes", id_buscar);
                            break;
                        case 2: printf("\nLa tarea de id %d se encuentra en tareas realizadas", id_buscar);
                            break;
                    }
                break;
            case 6: printf("\nIngrese palabra clave a buscar");
                    fflush(stdin);
                    gets(palabra);
                    palabra = (char *)realloc(palabra, sizeof(char) * (strlen(palabra) + 1));
                    switch (buscar_por_palabra_clave(Realizadas, Pendientes, palabra)){
                        case 0: printf("\nLa palabra clave '%s' no existe", palabra);
                            break;
                        case 1: printf("\nLa palabra clave '%s' se encuentra en tareas pendientes", palabra);
                            break;
                        case 2: printf("\nLa palabra clave '%s' se encuentra en tareas realizadas", palabra);
                            break;
                    }
                break;
            default:
                break;
        }
    }while(opcion != 0);

    return 0;
}

Nodo *crear_lista_vacia(){
    return NULL;
}

Nodo *crear_nodo(int id){
    Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
    
    nodo->T.TareaID = id;
    nodo->T.Duracion = rand() % 91 + 10; 
    
    char *buff = (char *)malloc(sizeof(char)*100);
    printf("\nDescripcion: ");
    fflush(stdin);
    gets(buff); 
    nodo->T.Descripcion = (char *)malloc(sizeof(char) * (strlen(buff) + 1));
    strcpy(nodo->T.Descripcion, buff);
    free(buff);
    
    nodo->Siguiente = NULL;
    return nodo;
}

void insertar_pendientes(Nodo **Pendientes, int *id){
    Nodo *tarea = crear_nodo(*id);
    (*id)++;
    tarea->Siguiente = *Pendientes;
    *Pendientes = tarea;
}

void mostrar_tareas(Nodo *tareas){
    Nodo *aux = tareas;
    
    while (aux){ //aux != NULL
        printf("\n------------------------------");
        printf("\nProducto con ID: %d", aux->T.TareaID);
        printf("\nDescripcion: %s", aux->T.Descripcion);
        printf("\nDuracion: %d", aux->T.Duracion);
        aux = aux->Siguiente;
    }
}

Nodo *quitar_pend(Nodo **Pendientes, int id_borrar)
{
    Nodo *anterior = NULL;
    Nodo *actual = *Pendientes;

    while (actual && id_borrar != actual->T.TareaID){
        anterior = actual;
        actual = actual->Siguiente;
    }

    if(actual == NULL){
        return NULL;
    }

    if (anterior != NULL){
        anterior->Siguiente = actual->Siguiente;  
    } else {
        *Pendientes = actual->Siguiente;
    }
    
    return actual;
}

void insertar_realizadas(Nodo ** Realizadas, Nodo *quitado){
    quitado->Siguiente = *Realizadas;  //lo meto al principio de la lista
    *Realizadas = quitado;
}

int buscar_por_id(Nodo *Realizadas, Nodo *Pendientes, int id_buscar){
    Nodo *aux_pen = Pendientes;
    Nodo *aux_real = Realizadas;

    while (aux_pen && aux_pen->T.TareaID != id_buscar){
        aux_pen = aux_pen->Siguiente;
    }
    
    if(aux_pen == NULL){ //para que no busque innecesariamente si es que lo encontro en pendientes
        while (aux_real && aux_real->T.TareaID != id_buscar){
            aux_real = aux_real->Siguiente;
        }
    } 

    if(aux_real == NULL && aux_pen == NULL){
        return 0;
    } else if(aux_pen){
        return 1;
    } else {
        return 2;
    }
}

int buscar_por_palabra_clave(Nodo *Realizadas, Nodo *Pendientes, char *palabra){
    Nodo *aux_pen = Pendientes;
    Nodo *aux_real = Realizadas;

    while (aux_pen){
        if(strstr(aux_pen->T.Descripcion, palabra)){ //busca la primera ocurrencia de la palabra en la descripcion
            return 1;
        }
        aux_pen = aux_pen->Siguiente;
    }
    
     while (aux_real){
        if(strstr(aux_real->T.Descripcion, palabra)){
            return 2;
        }
        aux_real = aux_real->Siguiente;
    }
    
    if(aux_real == NULL && aux_pen == NULL){
        return 0;
    }
}
