#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define ESTN 1
#define CALIFN 16
#define IDtama 10
#define CalifNom 15

typedef struct{
    char Nombre[CALIFN];
    int puntos;
}CALIFICACIONES;

typedef struct{
    int IDest[IDtama];
    char PrimNom[CalifNom];
    char SegNom[CalifNom];
    CALIFICACIONES EvEst[20];
    float Calif;
}ESTUDIANTE;

FILE* abrir_archivo(char *nombre, char *modo);
void cerrar_archivo(FILE *archivo);
void ListaEstudiantil(ESTUDIANTE *Est);
int CapEstudiante(ESTUDIANTE *Est); //utilizado para ingresar los datos del estudiante
void leer_texto_archivo(char *nombre);
void escribir_estudiante_archivo(ESTUDIANTE *Est, char *nombre);

//Declaración de 10 de las materias relacionadas con la carrera de Ingeniería de Sistemas y computación
char materias[][1000] = {"","1- Fundamentos de Programaci%cn", "2- Int. a Sistemas de Comp.", "3- Int. a la Algoritmia", "4- Programacion I", "5- Logica Computacional", "6- Programacion Aplicada", "7- Estructuras de Datos", "8- Analisis de Sistemas", "9- Int. a Sistemas Digitales", "10- Programacion II"};

//Función para presentar la lista de materias asociadas al estudiante y por ende a la carrera de Ingeniería de Sistemas y Computación.
void imprimir_materias()
{
    system("cls");
    printf("\n Las asignaturas disponbies son : ");
    int longitud_arreglo = sizeof(materias) / sizeof(materias[0]) ;
    for (int i = 1; i < longitud_arreglo ; i++)
    {
        printf("\n %s", materias[i]);
    }
}

//Presentar el menu, capturar y retornar la seleccion que haga el usuario para entonces trabajar el switch.
int imprimir_menu()
{
    int SelecMenu = 0;
    printf("\n\n\n ---- MENU ----");
    char menu[][80] = {"1- Introducir informacion del estudiante", "2- Ingresar CALIFICACIONESes", "3- Imprimir calificaciones", "4- Consultar estudiante", "5- Salir"};

    int longitud_arreglo = sizeof(menu) / sizeof(menu[0]) ;
    for (int i = 0; i < longitud_arreglo ; i++)
    {
        printf("\n %s", menu[i]);
    }
    printf("\n\n ----> ");
    scanf("%d", &SelecMenu);

    return SelecMenu;
}

//FUNCIONES
//FUNCIONES
//FUNCIONES

FILE* abrir_archivo(char *nombre, char *modo){
    FILE *archivo = fopen(nombre, modo);
    if(archivo == NULL){
        fputs("Archivo no abierto, verificar...", stderr);
        exit(-1);
    }
    printf("Archivo abierto\n");
    return archivo;
}

void cerrar_archivo(FILE *archivo){
    int cerrado = fclose(archivo);
    cerrado == 0 ? printf("Archivo Cerrado\n") : printf("Error Archivo No Cerrado\n");
}

void leer_texto_archivo(char *nombre){
    FILE *archivo = abrir_archivo(nombre, "r+");
    printf("======= Información del archivo =========\n");
    char caracter;
    while ((caracter = fgetc(archivo)) != EOF){
        fputc(caracter, stdout);
    }
    printf("======= Fin Información del archivo =========\n");
    cerrar_archivo(archivo);
}

void escribir_estudiante_archivo(ESTUDIANTE *Est, char *nombre){
    FILE *archivo = abrir_archivo(nombre, "w");
    for(int i=0;i<ESTN;i++){
            CapEstudiante(Est);
        fwrite(&Est[i], sizeof(ESTUDIANTE), 1, archivo);
    }
    cerrar_archivo(archivo);
}

int CapEstudiante(ESTUDIANTE *Est){
    printf("ID del Estudiante: ");
    fflush(stdin);
    gets(Est->IDest);
    printf("PRIMER NOMBRE: ");
    fflush(stdin);
    gets(Est->IDest);
    printf("PRIMER APELLIDO: ");
    fflush(stdin);
    gets(Est->IDest);
    for(int i=0;i<3;i++){
        printf("Nombre de CALIFICACIONES %d: ", i+1);
        fflush(stdin);
        gets(Est->EvEst[i].Nombre);
        printf("Nota de CALIFICACIONES %d: ", i+1);
        scanf("%d", &Est->EvEst[i].puntos);

    }
}

void ListaEstudiantil(ESTUDIANTE *Est){
    int total;
    for(int i=0;i<ESTN;i++){
        for(int k=0;k<3;k++){
            total+=Est[i].EvEst[k].puntos;
        }
        Est[i].Calif = total/3;
        printf("%d \t", Est[i].IDest);
        //printf("%s \t",Est[i].PrimNom);
        //printf("%s \t", Est[i].SegNom);
        //printf("%.2f \t\n", Est[i].Calif);
    }
    return *Est;
}

//AQUI ESTA EL PROGRAMA
int main(void){

    ESTUDIANTE Est[ESTN];
    char NombreFILE[20] = "Lista_Est.txt";
    int Tecla = 0, i=0;

    bool salir = false;
    printf("\n PRACTICA DE FUNDAMENTOS DE PROGRAMACION\n\t ESTRUCTURAS Y ARCHIVOS\n ");
    do
    {
        switch(imprimir_menu())
        {
            case 1:
                imprimir_materias();
                break;
            case 2:
                escribir_estudiante_archivo(Est, NombreFILE);
                break;
            case 3:
                system("cls");
                ListaEstudiantil(Est);
                break;
            case 4:
                leer_texto_archivo(NombreFILE);;
                break;
            case 5:
                salir = true;
                break;
            default :
                printf("Opcion elegida no valida");
                break;
        }

    } while (!salir);

    return 0;
}
