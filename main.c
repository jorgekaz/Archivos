#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>

#include "Librerias/pila.h"
#define archivoElementos "elementos.dat"
#define archivoAlumnos "alumnos.dat"

typedef struct {
     int legajo;
     char nombreYapellido [30];
     int edad;
     int anio;
} stAlumno;

void agregarElemento(); //1
void mostrarElementos(); //2
int cantidadElementos(); //3
void cargarArchivoAlumnos(); //4
void mostrarAlumno(stAlumno alumnos);  //5
void mostrarArchivoAlumnos(); //5
void cargarUnAlumno(); //6
void pasajePila(); //7
void contarEdad(int edadMayores);//8
int edadMenor(int rangoMin, stAlumno alumnos); //9
int edadMayor(int rangoMax, stAlumno alumnos); //9
void mostrarRango(int rangoMin, int rangoMax);//9
void mostrarMayor();//10
int cursantesAnio(int anio); //11
void copiarEnArchivo(stAlumno arreglo[],int validos); //12
void pasarArreglo(); //12
int cantidadRegistros(); //13
void mostrarContenido(int numero); //14
int buscarLegajo(); //15
void modificarRegistro(); //15
void invertirArchivo(); //16
int menu(); //17
void funcionMenu(); //17

int main(){
    funcionMenu();
}

/// 1.Hacer una función que agregue un elemento al final de un archivo.
void agregarElemento(){
    FILE* archivo = fopen(archivoElementos, "ab");
    printf("\n");
    if (archivo != NULL){
        int elemento=0;
        printf(" INGRESE EL ELEMENTO: ");
        scanf("%i", &elemento);
        fwrite(&elemento,sizeof(elemento), 1, archivo);
        fclose(archivo);
    }else{
        printf("\n NO SE PUEDE ACCEDER AL ARCHIVO\n");
    }
    printf("\n");
}

/// 2.Hacer una función que muestre por pantalla el contenido de un archivo.
void mostrarElementos(){
    FILE* archivo = fopen(archivoElementos,"rb");
    printf("\n");
    if(archivo!=NULL){
        int contador=0;
        int elementos=0;
        while(fread(&elementos,sizeof(elementos),1,archivo)>0){
            printf(" ELEMENTO N° %i: %i\n",contador,elementos);
            contador++;
        }
        fclose(archivo);
    }else{
        printf(" NO SE ENCUENTRA EL ARCHIVO\n");
    }
    printf("\n");
}

/// 3.Hacer una función que retorne la cantidad de registros que contiene un archivo.
int cantidadElementos(){
    int cantidad=0;
    int aux=0;
    FILE* archivo = fopen(archivoElementos,"rb");
    if(archivo!=NULL){
        while(fread(&aux,sizeof(aux),1,archivo)>0){
            cantidad++;
        }
        fclose(archivo);
    }else{
        printf(" NO SE ENCUENTRA EL ARCHIVO\n");
    }
    printf("\n LA CANTIDAD DE ELEMENTOS DEL ARCHIVO ES DE: %i\n\n",cantidad);
    return cantidad;
}

/// 4.Crear una función que cargue un archivo de alumnos. Abrirlo de manera tal de verificar si el archivo ya está
/// creado previamente. Cargar el archivo con 5 datos. Cerrarlo dentro de la función.
void cargarArchivoAlumnos(){
    FILE* fileAlumnos = fopen(archivoAlumnos,"wb");
    if(fileAlumnos!=NULL){
        stAlumno alumnos;
        alumnos.legajo = 1;
        strcpy(alumnos.nombreYapellido,"Jorge Karp");
        alumnos.edad = 33;
        alumnos.anio = 1;
        fwrite(&alumnos,sizeof(alumnos),1,fileAlumnos);
        alumnos.legajo = 2;
        strcpy(alumnos.nombreYapellido,"Juan Trionfini");
        alumnos.edad = 29;
        alumnos.anio = 2;
        fwrite(&alumnos,sizeof(alumnos),1,fileAlumnos);
        alumnos.legajo = 3;
        strcpy(alumnos.nombreYapellido,"Juan Genova");
        alumnos.edad = 27;
        alumnos.anio = 1;
        fwrite(&alumnos,sizeof(alumnos),1,fileAlumnos);
        alumnos.legajo = 4;
        strcpy(alumnos.nombreYapellido,"Cesar Olivera");
        alumnos.edad = 45;
        alumnos.anio = 2;
        fwrite(&alumnos,sizeof(alumnos),1,fileAlumnos);
        alumnos.legajo = 5;
        strcpy(alumnos.nombreYapellido,"German Bermudez");
        alumnos.edad = 18;
        alumnos.anio = 1;
        fwrite(&alumnos,sizeof(alumnos),1,fileAlumnos);
        fclose(fileAlumnos);
    }
}

/// 5.Crear una función que muestre por pantalla los registros de un archivo de alumnos. Modularizar.
void mostrarAlumno(stAlumno alumnos){
    printf(" LEGAJO: %i\n", alumnos.legajo);
    printf(" NOMBRE Y APELLIDO: %s\n", strupr(alumnos.nombreYapellido));
    printf(" EDAD: %i\n", alumnos.edad);
    printf(" AÑO: %i\n", alumnos.anio);
    printf(" ---------------------------------------\n");
}
void mostrarArchivoAlumnos(){
    FILE* fileAlumnos = fopen(archivoAlumnos,"rb");
    if(fileAlumnos!=NULL){
        stAlumno alumnos;
        printf(" ---------------------------------------\n");
        while(fread(&alumnos,sizeof(alumnos),1,fileAlumnos)>0){
            mostrarAlumno(alumnos);
        }
        fclose(fileAlumnos);
    }else{
        printf(" EL ARCHIVO NO EXISTE\n");
    }


}

/// 6.Crear una función que permita agregar de a un elemento al final del archivo. O sea, se debe abrir el archivo,
///se piden los datos (se llena una variable de tipo struct alumno), se escribe en el archivo y se cierra
void cargarUnAlumno(){
    FILE* fileAlumno = fopen(archivoAlumnos,"ab");
    printf("\n");
    if(fileAlumno!=NULL){
        stAlumno alumnosAux;
        printf(" INGRESE LEGAJO: ");
        fflush(stdin);
        scanf("%i",&alumnosAux.legajo);
        printf(" INGRESE NOMBRE Y APELLIDO: ");
        fflush(stdin);
        gets(alumnosAux.nombreYapellido);
        printf(" INGRESE EDAD: ");
        fflush(stdin);
        scanf("%i",&alumnosAux.edad);
        printf(" INGRESE AÑO: ");
        fflush(stdin);
        scanf("%i",&alumnosAux.anio);
        fwrite(&alumnosAux,sizeof(alumnosAux),1,fileAlumno);
        fclose(fileAlumno);
    }else{
        printf(" NO SE PUEDE TRABAJAR EN EL ARCHIVO\n");
    }
}

/// 7.Crear una función que pase a una pila los números de legajo de los alumnos mayores de edad.
void pasajePila(){
    FILE* fileAlumnos = fopen(archivoAlumnos,"rb");
    if(fileAlumnos!=NULL){
        stAlumno alumnos;
        Pila pilaLegajo;
        inicpila(&pilaLegajo);
        while(fread(&alumnos,sizeof(alumnos),1,fileAlumnos)>0){
            if(alumnos.edad>=18){
                apilar(&pilaLegajo, alumnos.legajo);
            }
        }
        printf(" PILA DE LEGAJOS\n");
        mostrar(&pilaLegajo);
        fclose(fileAlumnos);
    }else{
        printf(" NO SE ENCONTRO EL ARCHIVO\n");
    }
}

/// 8.Dado un archivo de alumnos, hacer una función que cuente la cantidad de alumnos mayores a edad específica
/// que se envía por parámetro.
void contarEdad(int edadMayores){
    FILE* fileAlumnos = fopen(archivoAlumnos,"rb");
    if(fileAlumnos!=NULL){
        stAlumno alumnos;
        int mayores=0;
        while(fread(&alumnos,sizeof(alumnos),1,fileAlumnos)>0){
            if(alumnos.edad>=edadMayores){
                mayores++;
            }
        }
        printf("\n LOS ALUMNOS MAYORES DE EDAD SON: %i\n\n",mayores);
        fclose(fileAlumnos);
    }else{
        printf("\n NO SE PUEDE TRABAJAR EN EL ARCHIVO\n\n");
    }
}

/// 9.Dado un archivo de alumnos, mostrar por pantalla el nombre de todos los alumnos entre un rango de edades específico
/// (por ejemplo, entre 17 y 25 años). Dicho rango debe recibirse por parámetro. Modularizar
int edadMenor(int rangoMin, stAlumno alumnos){
    int flag=0;
    if(alumnos.edad>=rangoMin){
        flag=1;
    }
    return flag;
}
int edadMayor(int rangoMax, stAlumno alumnos){
    int flag=0;
    if(alumnos.edad<=rangoMax){
        flag=1;
    }
    return flag;
}
void mostrarRango(int rangoMin, int rangoMax){
    FILE* fileAlumnos = fopen(archivoAlumnos,"rb");
    if(fileAlumnos!=NULL){
        stAlumno alumnos;
        printf("\n --------------------------------------\n");
        while(fread(&alumnos,sizeof(alumnos),1,fileAlumnos)>0){
            if(edadMenor(rangoMin,alumnos)==1 && edadMayor(rangoMax,alumnos)==1){
                printf(" NOMBRE: %s\n", strupr(alumnos.nombreYapellido));
                printf(" EDAD: %i\n", alumnos.edad);
                printf(" --------------------------------------\n\n");
              }
        }
        fclose(fileAlumnos);
    }else{
        printf(" NO SE PUEDE TRABAJAR CON EL ARCHIVO\n");
    }
}

/// 10.Dado un archivo de alumnos, mostrar los datos del alumno de mayor edad. Modularizar.
void mostrarMayor(){
    FILE* fileAlumnos = fopen(archivoAlumnos,"rb");
    printf("\n");
    if(fileAlumnos!=NULL){
        stAlumno alumnos;
        while(fread(&alumnos,sizeof(alumnos),1,fileAlumnos)>0){
            if(edadMenor(18,alumnos)){
                mostrarAlumno(alumnos);
            }
        }
        fclose(fileAlumnos);
    }else{
        printf(" NO SE PUEDE ACCEDER AL ARCHIVO\n");
    }
}

/// 11.Crear una función que retorne la cantidad de alumnos que cursan un determinado año. El año buscado se pasa por parámetro
int cursantesAnio(int anio){
    int cantidadAnio=0;
    FILE* fileAlumnos = fopen(archivoAlumnos,"rb");
    if(fileAlumnos!=NULL){
        stAlumno alumnos;
        while(fread(&alumnos,sizeof(alumnos),1,fileAlumnos)>0){
            if(alumnos.anio==anio){
                cantidadAnio++;
              }
        }
        fclose(fileAlumnos);
    }else{
        printf(" NO SE PUEDE ACCEDER AL ARCHIVO\n");
    }
    printf("\n LA CANTIDAD DE ALUMNOS CURSANDO %i ES DE: %i\n\n",anio,cantidadAnio);
    return cantidadAnio;
}

/// 12.Crear una función que reciba como parámetro un arreglo de tipo alumno y lo copie en el archivo.
/// Asimismo, realice otra función que pase los elementos del archivo a un arreglo de alumnos, filtrando los
/// estudiantes de un año en particular.
void copiarEnArchivo(stAlumno arreglo[],int validos){
    FILE* fileAlumnos = fopen(archivoAlumnos,"ab");
    if(fileAlumnos!=NULL){
        for(int i=0;i<validos;i++){
            fwrite(&arreglo[i],sizeof(arreglo[i]),1,fileAlumnos);
        }
        fclose(fileAlumnos);
    }else{
        printf(" NO SE PUEDE ACCEDER AL ARCHIVO\n");
    }
}
void pasarArreglo(){
    stAlumno arregloAux[8];
    int i=0;
    FILE* fileAlumnos = fopen(archivoAlumnos,"r+b");
    if(fileAlumnos!=NULL){
        stAlumno alumnos;
        int anios;
        printf("\n INGRESE AÑO A FILTRAR: ");
        fflush(stdin);
        scanf("%i", &anios);
        while(fread(&alumnos,sizeof(alumnos),1,fileAlumnos)>0 && i<8){
            if(alumnos.anio==anios){
                arregloAux[i]=alumnos;
                i++;
            }
        }
        fclose(fileAlumnos);
    }else{
        printf(" NO SE PUEDE ACCEDER AL ARCHIVO\n");
    }
    printf("\n ARREGLO FILTRADO\n\n");
    for(int j=0;j<i;j++){
        mostrarAlumno(arregloAux[j]);
    }
}

/// 13.Crear una función que retorne la cantidad de registros que tiene el archivo. Usar fseek y ftell.
///Puede pensar la función para uso genérico, que sirva para averiguar la cantidad de registros de cualquier archivo.
int cantidadRegistros(){
    int registros=0;
    FILE* fileAlumnos = fopen(archivoAlumnos,"rb");
    if(fileAlumnos!=NULL){
        fseek(fileAlumnos,0,SEEK_END);
        registros = ftell(fileAlumnos)/sizeof(stAlumno);
        fclose(fileAlumnos);
    }else{
        printf(" NO SE PUDO ACCEDER AL ARCHIVO\n");
    }
    return registros;
}

/// 14.Dado un archivo de alumnos, que tenga al menos 10 registros, hacer una función que muestre el
/// contenido de un registro, cuyo número (entre 0 y 9) se pase por parámetro. Controlar no sobrepasar los
/// límites del archivo
void mostrarContenido(int numero){
    FILE* fileAlumnos = fopen(archivoAlumnos,"rb");
    if(fileAlumnos!=NULL){
        stAlumno alumnos;
        printf("\n --------------------------------------\n");
        if(numero>=0 && numero<=9 && cantidadRegistros()>=10){
            fseek(fileAlumnos,sizeof(stAlumno)*numero,SEEK_SET);
            fread(&alumnos,sizeof(alumnos),1,fileAlumnos);
            mostrarAlumno(alumnos);
        }
        fclose(fileAlumnos);
    }else{
        printf(" NO SE PUEDE ACCEDER AL ARCHIVO\n");
    }
}

/// 15.Realice una (o varias) funciones que permitan modificar un registro existente en el archivo de alumnos.
/// La misma debe permitir modificar uno o todos los campos de la estructura y sobrescribir el registro existente
/// en el archivo.
int buscarLegajo(){
    int posicion=-1;
    FILE* fileAlumnos = fopen(archivoAlumnos,"rb");
    if(fileAlumnos!=NULL){
        stAlumno alumnos;
        int legajo;
        int flag=0;
        printf("\n INGRESE LEGAJO PARA MODIFICAR: ");
        fflush(stdin);
        scanf("%i",&legajo);

        printf("\n --------------------------------------\n");
        while(fread(&alumnos,sizeof(alumnos),1,fileAlumnos)>0 && flag==0){
            if(alumnos.legajo==legajo){
                printf(" REGISTRO A MODIFICAR: \n\n");
                posicion=ftell(fileAlumnos)/sizeof(alumnos);
                mostrarAlumno(alumnos);
                flag=1;
            }
        }
        fclose(fileAlumnos);
    }else{
        printf(" NO SE PUEDE ACCEDER AL ARCHIVO\n");
    }
    return posicion;
}
void modificarRegistro(){
    FILE* fileAlumnos = fopen(archivoAlumnos,"r+b");
    if(fileAlumnos!=NULL){
        int pos;
        pos=buscarLegajo();
        stAlumno alumnos;
        if(pos!=-1){
            fseek(fileAlumnos,sizeof(stAlumno)*(pos-1),SEEK_SET);
            fread(&alumnos,sizeof(stAlumno),1,fileAlumnos);
            printf("\n NUEVOS DATOS\n");
            printf(" INGRESE NOMBRE Y APELLIDO: ");
            fflush(stdin);
            gets(alumnos.nombreYapellido);
            printf(" INGRESE EDAD: ");
            fflush(stdin);
            scanf("%i",&alumnos.edad);
            printf(" INGRESE AÑO: ");
            fflush(stdin);
            scanf("%i",&alumnos.anio);
            fseek(fileAlumnos,sizeof(stAlumno)*(-1),SEEK_CUR);
            fwrite(&alumnos,sizeof(stAlumno),1,fileAlumnos);
        }else{
            printf(" NO SE ENCONTRO EL LEGAJO\n");
        }
        fclose(fileAlumnos);
    }else{
        printf(" NO SE PUEDE ACCEDER AL ARCHIVO\n");
    }
}

/// 16.	Dado un archivo de alumnos, hacer una función que invierta los elementos del mismo.
/// No se puede usar otro archivo auxiliar ni un arreglo auxiliar. Debe trabajar sobre el archivo.
/// Puede utilizar variables de tipo alumno auxiliares.
void invertirArchivo(){
    stAlumno posIncial;
    stAlumno posFinal;
    int inicio= 0;
    int fin=cantidadRegistros();
    fin--;
    FILE * fileAlumnos = fopen(archivoAlumnos, "r+b");
    if (fileAlumnos != NULL){
        while(inicio<fin){
            fseek(fileAlumnos, (inicio)*sizeof(stAlumno), SEEK_SET);
            fread(&posIncial, sizeof(stAlumno), 1, fileAlumnos);
            fseek(fileAlumnos, (fin)*sizeof(stAlumno), SEEK_SET);
            fread(&posFinal, sizeof(stAlumno), 1, fileAlumnos);
            fseek(fileAlumnos, (fin)*sizeof(stAlumno), SEEK_SET);
            fwrite(&posIncial, sizeof(stAlumno),1,fileAlumnos);
            fseek(fileAlumnos, (inicio)*sizeof(stAlumno), SEEK_SET);
            fwrite(&posFinal, sizeof(stAlumno),1,fileAlumnos);
            inicio++;
            fin--;
        }
        fclose(fileAlumnos);
    } else{
        printf("Error: el archivo no se pudo cargar el archivo.\n");
    }
}

/// 17.Hacer una función principal que pruebe el funcionamiento de todos los incisos anteriores,
/// con un menú de opciones para poder ejecutar todas las funciones requeridas. Tengan presente la correcta
/// declaración y el ámbito de variables.

int menu(){
    int option;
        color(11);
        printf("==================================\n");
        printf(" TRABAJO PRACTICO N° 7: ARCHIVOS\n");
        printf("==================================\n");
        color(7);
        printf(" 1.HACER UNA FUNCIÓN QUE AGREGUE UN ELEMENTO AL FINAL DE UN ARCHIVO.\n\n");
        printf(" 2.HACER UNA FUNCIÓN QUE MUESTRE POR PANTALLA EL CONTENIDO DE UN ARCHIVO.\n\n");
        printf(" 3.HACER UNA FUNCIÓN QUE RETORNE LA CANTIDAD DE REGISTROS QUE CONTIENE UN ARCHIVO.\n\n");
        printf(" 4.CREAR UNA FUNCIÓN QUE CARGUE UN ARCHIVO DE ALUMNOS. ABRIRLO DE MANERA TAL DE VERIFICAR SI EL ARCHIVO YA ESTÁ CREADO PREVIAMENTE. CARGAR EL ARCHIVO CON 5 DATOS. CERRARLO DENTRO DE LA FUNCIÓN.\n\n");
        printf(" 5.CREAR UNA FUNCIÓN QUE MUESTRE POR PANTALLA LOS REGISTROS DE UN ARCHIVO DE ALUMNOS. MODULARIZAR.\n\n");
        printf(" 6.CREAR UNA FUNCIÓN QUE PERMITA AGREGAR DE A UN ELEMENTO AL FINAL DEL ARCHIVO. O SEA, SE DEBE ABRIR EL ARCHIVO, SE PIDEN LOS DATOS (SE LLENA UNA VARIABLE DE TIPO STRUCT ALUMNO), SE ESCRIBE EN EL ARCHIVO Y SE CIERRA.\n\n");
        printf(" 7.CREAR UNA FUNCIÓN QUE PASE A UNA PILA LOS NÚMEROS DE LEGAJO DE LOS ALUMNOS MAYORES DE EDAD.\n\n");
        printf(" 8.DADO UN ARCHIVO DE ALUMNOS, HACER UNA FUNCIÓN QUE CUENTE LA CANTIDAD DE ALUMNOS MAYORES A EDAD ESPECÍFICA QUE SE ENVÍA POR PARÁMETRO.\n\n");
        printf(" 9.DADO UN ARCHIVO DE ALUMNOS, MOSTRAR POR PANTALLA EL NOMBRE DE TODOS LOS ALUMNOS ENTRE UN RANGO DE EDADES ESPECÍFICO (POR EJEMPLO, ENTRE 17 Y 25 AÑOS). DICHO RANGO DEBE RECIBIRSE POR PARÁMETRO. MODULARIZAR.\n\n");
        printf("10.DADO UN ARCHIVO DE ALUMNOS, MOSTRAR LOS DATOS DEL ALUMNO DE MAYOR EDAD. MODULARIZAR.\n\n");
        printf("11.CREAR UNA FUNCIÓN QUE RETORNE LA CANTIDAD DE ALUMNOS QUE CURSAN UN DETERMINADO AÑO. EL AÑO BUSCADO SE PASA POR PARÁMETRO.\n\n");
        printf("12.CREAR UNA FUNCIÓN QUE RECIBA COMO PARÁMETRO UN ARREGLO DE TIPO ALUMNO Y LO COPIE EN EL ARCHIVO. ASIMISMO, REALICE OTRA FUNCIÓN QUE PASE LOS ELEMENTOS DEL ARCHIVO A UN ARREGLO DE ALUMNOS, FILTRANDO LOS ESTUDIANTES DE UN AÑO EN PARTICULAR.\n\n");
        printf("13.CREAR UNA FUNCIÓN QUE RETORNE LA CANTIDAD DE REGISTROS QUE TIENE EL ARCHIVO. USAR FSEEK Y FTELL. PUEDE PENSAR LA FUNCIÓN PARA USO GENÉRICO, QUE SIRVA PARA AVERIGUAR LA CANTIDAD DE REGISTROS DE CUALQUIER ARCHIVO.\n\n");
        printf("14.DADO UN ARCHIVO DE ALUMNOS, QUE TENGA AL MENOS 10 REGISTROS, HACER UNA FUNCIÓN QUE MUESTRE EL CONTENIDO DE UN REGISTRO, CUYO NÚMERO (ENTRE 0 Y 9) SE PASE POR PARÁMETRO. CONTROLAR NO SOBREPASAR LOS LÍMITES DEL ARCHIVO.\n\n");
        printf("15.REALICE UNA (O VARIAS) FUNCIONES QUE PERMITAN MODIFICAR UN REGISTRO EXISTENTE EN EL ARCHIVO DE ALUMNOS. LA MISMA DEBE PERMITIR MODIFICAR UNO O TODOS LOS CAMPOS DE LA ESTRUCTURA Y SOBRESCRIBIR EL REGISTRO EXISTENTE EN EL ARCHIVO.\n\n");
        printf("16.DADO UN ARCHIVO DE ALUMNOS, HACER UNA FUNCIÓN QUE INVIERTA LOS ELEMENTOS DEL MISMO. NO SE PUEDE USAR OTRO ARCHIVO AUXILIAR NI UN ARREGLO AUXILIAR. DEBE TRABAJAR SOBRE EL ARCHIVO. PUEDE UTILIZAR VARIABLES DE TIPO ALUMNO AUXILIARES.\n\n");
        printf("17.HACER UNA FUNCIÓN PRINCIPAL QUE PRUEBE EL FUNCIONAMIENTO DE TODOS LOS INCISOS ANTERIORES, CON UN MENÚ DE OPCIONES PARA PODER EJECUTAR TODAS LAS FUNCIONES REQUERIDAS. TENGAN PRESENTE LA CORRECTA DECLARACIÓN Y EL ÁMBITO DE VARIABLES.\n\n");
        printf(" 0.SALIR\n\n");
        printf("\n ELIJA UNA OPCIÓN: ");
        fflush(stdin);
        scanf("%i", &option);
        return option;
}

void funcionMenu(){
    setlocale(LC_ALL, "");
    int option=0;
    do{
        option=menu();
        system("cls");
        switch(option){
        case 1:{
            color(11);
            printf("  1.HACER UNA FUNCIÓN QUE AGREGUE UN ELEMENTO AL FINAL DE UN ARCHIVO.\n");
            color(7);
            agregarElemento();
            system("pause");
            system("cls");
        }
        break;
        case 2:{
            color(11);
            printf("  2.HACER UNA FUNCIÓN QUE MUESTRE POR PANTALLA EL CONTENIDO DE UN ARCHIVO.\n");
            color(7);
            mostrarElementos();
            system("pause");
            system("cls");
        }
        break;
        case 3:{
            color(11);
            printf("  3.HACER UNA FUNCIÓN QUE RETORNE LA CANTIDAD DE REGISTROS QUE CONTIENE UN ARCHIVO.\n");
            color(7);
            cantidadElementos();
            system("pause");
            system("cls");
        }
        break;
        case 4:{
            color(11);
            printf("  4.CREAR UNA FUNCIÓN QUE CARGUE UN ARCHIVO DE ALUMNOS. ABRIRLO DE MANERA TAL DE VERIFICAR SI EL ARCHIVO YA ESTÁ CREADO PREVIAMENTE. CARGAR EL ARCHIVO CON 5 DATOS. CERRARLO DENTRO DE LA FUNCIÓN.\n");
            color(7);
            printf("\n ARCHIVO CARGADO, VAYA AL EJERCICIO 5 PARA VISUALIZARLO\n\n");
            cargarArchivoAlumnos();
            system("pause");
            system("cls");
        }
        break;
        case 5:{
            color(11);
            printf("  5.CREAR UNA FUNCIÓN QUE MUESTRE POR PANTALLA LOS REGISTROS DE UN ARCHIVO DE ALUMNOS. MODULARIZAR.\n");
            color(7);
            mostrarArchivoAlumnos();
            system("pause");
            system("cls");
        }
        break;
        case 6:{
            color(11);
            printf("  6.CREAR UNA FUNCIÓN QUE PERMITA AGREGAR DE A UN ELEMENTO AL FINAL DEL ARCHIVO. O SEA, SE DEBE ABRIR EL ARCHIVO, SE PIDEN LOS DATOS (SE LLENA UNA VARIABLE DE TIPO STRUCT ALUMNO), SE ESCRIBE EN EL ARCHIVO Y SE CIERRA.\n");
            color(7);
            cargarUnAlumno();
            mostrarArchivoAlumnos();
            system("pause");
            system("cls");
        }
        break;
        case 7:{
            color(11);
            printf("  7.CREAR UNA FUNCIÓN QUE PASE A UNA PILA LOS NÚMEROS DE LEGAJO DE LOS ALUMNOS MAYORES DE EDAD.\n");
            color(7);
            pasajePila();
            system("pause");
            system("cls");
        }
        break;
        case 8:{
            color(11);
            printf("  8.DADO UN ARCHIVO DE ALUMNOS, HACER UNA FUNCIÓN QUE CUENTE LA CANTIDAD DE ALUMNOS MAYORES A EDAD ESPECÍFICA QUE SE ENVÍA POR PARÁMETRO.\n");
            color(7);
            int edad;
            printf("\n A PARTIR DE QUE EDAD DESEA BUSCAR?: ");
            fflush(stdin);
            scanf("%i",&edad);
            contarEdad(edad);
            system("pause");
            system("cls");
        }
        break;
        case 9:{
            color(11);
            printf("  9.DADO UN ARCHIVO DE ALUMNOS, MOSTRAR POR PANTALLA EL NOMBRE DE TODOS LOS ALUMNOS ENTRE UN RANGO DE EDADES ESPECÍFICO (POR EJEMPLO, ENTRE 17 Y 25 AÑOS). DICHO RANGO DEBE RECIBIRSE POR PARÁMETRO. MODULARIZAR.\n");
            color(7);
            int minimo;
            int maximo;
            printf("\n INGRESE EL RANGO MINIMO DE EDAD: ");
            fflush(stdin);
            scanf("%i", &minimo);
            printf("\n INGRESE EL RANGO MAXIMO DE EDAD: ");
            fflush(stdin);
            scanf("%i", &maximo);
            mostrarRango(minimo,maximo);
            system("pause");
            system("cls");
        }
        break;
        case 10:{
            color(11);
            printf("  10.DADO UN ARCHIVO DE ALUMNOS, MOSTRAR LOS DATOS DEL ALUMNO DE MAYOR EDAD. MODULARIZAR.\n");
            color(7);
            mostrarMayor();
            system("pause");
            system("cls");
        }
        break;
        case 11:{
            color(11);
            printf("  11.CREAR UNA FUNCIÓN QUE RETORNE LA CANTIDAD DE ALUMNOS QUE CURSAN UN DETERMINADO AÑO. EL AÑO BUSCADO SE PASA POR PARÁMETRO.\n");
            color(7);
            int anioCursado;
            printf("\n INGRESE EL AÑO QUE DESEA BUSCAR: ");
            fflush(stdin);
            scanf("%i",&anioCursado);
            cursantesAnio(anioCursado);
            system("pause");
            system("cls");
        }
        break;
        case 12:{
            color(11);
            printf("  12.CREAR UNA FUNCIÓN QUE RECIBA COMO PARÁMETRO UN ARREGLO DE TIPO ALUMNO Y LO COPIE EN EL ARCHIVO. ASIMISMO, REALICE OTRA FUNCIÓN QUE PASE LOS ELEMENTOS DEL ARCHIVO A UN ARREGLO DE ALUMNOS, FILTRANDO LOS ESTUDIANTES DE UN AÑO EN PARTICULAR.\n");
            color(7);
            stAlumno arregloAlumno[3];

            arregloAlumno[0].legajo = 10;
            strcpy(arregloAlumno[0].nombreYapellido,"Rodrigo Ruiz");
            arregloAlumno[0].edad = 18;
            arregloAlumno[0].anio = 1;

            arregloAlumno[1].legajo = 11;
            strcpy(arregloAlumno[1].nombreYapellido,"Lucas Sosa");
            arregloAlumno[1].edad = 18;
            arregloAlumno[1].anio = 1;

            arregloAlumno[2].legajo = 12;
            strcpy(arregloAlumno[2].nombreYapellido,"Florencia Aguiar");
            arregloAlumno[2].edad = 25;
            arregloAlumno[2].anio = 1;
            copiarEnArchivo(arregloAlumno,3);
            mostrarArchivoAlumnos();
            pasarArreglo();
            system("pause");
            system("cls");
        }
        break;
        case 13:{
            color(11);
            printf("  13.CREAR UNA FUNCIÓN QUE RETORNE LA CANTIDAD DE REGISTROS QUE TIENE EL ARCHIVO. USAR FSEEK Y FTELL. PUEDE PENSAR LA FUNCIÓN PARA USO GENÉRICO, QUE SIRVA PARA AVERIGUAR LA CANTIDAD DE REGISTROS DE CUALQUIER ARCHIVO.\n");
            color(7);
            printf("\n LA CANTIDAD DE REGISTROS ES DE: %i\n\n",cantidadRegistros());
            system("pause");
            system("cls");
        }
        break;
        case 14:{
            color(11);
            printf("  14.DADO UN ARCHIVO DE ALUMNOS, QUE TENGA AL MENOS 10 REGISTROS, HACER UNA FUNCIÓN QUE MUESTRE EL CONTENIDO DE UN REGISTRO, CUYO NÚMERO (ENTRE 0 Y 9) SE PASE POR PARÁMETRO. CONTROLAR NO SOBREPASAR LOS LÍMITES DEL ARCHIVO.\n");
            color(7);
            int reg;
            printf("\n INGRESE UN NUMERO ENTRE EL 0 Y 9: ");
            fflush(stdin);
            scanf("%i",&reg);
            mostrarContenido(reg);
            system("pause");
            system("cls");
        }
        break;
        case 15:{
            color(11);
            printf("  15.REALICE UNA (O VARIAS) FUNCIONES QUE PERMITAN MODIFICAR UN REGISTRO EXISTENTE EN EL ARCHIVO DE ALUMNOS. LA MISMA DEBE PERMITIR MODIFICAR UNO O TODOS LOS CAMPOS DE LA ESTRUCTURA Y SOBRESCRIBIR EL REGISTRO EXISTENTE EN EL ARCHIVO.\n");
            color(7);
            modificarRegistro();
            mostrarArchivoAlumnos();
            system("pause");
            system("cls");
        }
        break;
        case 16:{
            color(11);
            printf("  16.DADO UN ARCHIVO DE ALUMNOS, HACER UNA FUNCIÓN QUE INVIERTA LOS ELEMENTOS DEL MISMO. NO SE PUEDE USAR OTRO ARCHIVO AUXILIAR NI UN ARREGLO AUXILIAR. DEBE TRABAJAR SOBRE EL ARCHIVO. PUEDE UTILIZAR VARIABLES DE TIPO ALUMNO AUXILIARES.\n");
            color(7);
            printf(" ARCHIVO INVERTIDO\n");
            invertirArchivo();
            mostrarArchivoAlumnos();
            system("pause");
            system("cls");
        }
        break;
        case 17:{
            color(11);
            printf("  17.HACER UNA FUNCIÓN PRINCIPAL QUE PRUEBE EL FUNCIONAMIENTO DE TODOS LOS INCISOS ANTERIORES, CON UN MENÚ DE OPCIONES PARA PODER EJECUTAR TODAS LAS FUNCIONES REQUERIDAS. TENGAN PRESENTE LA CORRECTA DECLARACIÓN Y EL ÁMBITO DE VARIABLES.\n");
            color(7);
            system("pause");
            system("cls");
        }
        break;
        case 0:{
            color(11);
            printf("  0.SALIR\n");
            color(7);
            system("pause");
            system("cls");
        }
        break;
        default:
            color(12);
            printf("\n OPCION INCORRECTA\n\n");
            color(7);
            system("pause");
            system("cls");
        break;
        }
    }while(option!=0);
    color(12);
    printf("\n FIN DEL PROGRAMA\n\n");
    color(7);
    system("pause");
}
