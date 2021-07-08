#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#define DIM 10000

const char AR_CLI[] = "clientes.dat";
const char AR_CON[] = "consumos.dat";


/*** ESTRUCTURAS ***/
 typedef struct {
    int  id;
    int  nroCliente;
    char nombre[30];
    char apellido[30];
    char dni[10];
    char email[30];
    char domicilio[45];
    char telefonoMovil[12];
    int baja;                // 0 si esta activo - 1 si esta eliminado
 }stCliente;

 typedef struct {
    int id;
    int idCliente;
    int anio;
    int mes;                    // del 1 al 12
    int dia;                    // del 1 al ..... segun mes que corresponda
    int datosConsumidos;        /// expresados en mb.
    int baja;                   // 0 si esta activo - 1 si esta eliminado
}stConsumos;

/*** PROTOTIPADO ***/
/*** FUNCIONES DE MENU ***/
void menuPrincipal();
void menuSaludoFinal();
void tituloPrincipal();
void menuBuscar();
void menuInicio();
void menuClientes();
void menuMuestraClientes();
char finalizaModificacion();
void stopProgram();
///--------------------------------------------------------------------------------------------------------------------------------///
///--------------------------------------------------------------------------------------------------------------------------------///
/*** FUNCIONES DE CLIENTES ***/
int  lastID(char archivo[]);
int  bajaCliente(char archivo[], char dni[]);
int  reactivarCliente(char archivo[],char dni[]);
void enterClient(char cliente[]);
void clientRegister(char archivo[]);
void modificaCliente(char archivo[],stCliente c);
void getEstadoCliente(int estadoCliente, char estado[]);
stCliente seleccionCampoAmodificar(stCliente c);
/*** Funciones de busqueda y retorno de Clientes***/
int searchByID(char archivo[],int id);
int searchByDNI(char archivo[],char dni[]);
int searchByLastname(char archivo[],char apellido[]);
int searchByClientNumber(char archivo[],int numCliente);
int buscaClientesInactivos(char archivo[]);
int buscaClientesActivos(char archivo[]);
stCliente returnByID(char archivo[],int id);
stCliente returnByDNI(char archivo[], char dni[]);
stCliente returnByLastname(char archivo[],char apellido[]);
stCliente returnByClientNumber(char archivo[],int numCliente);
/*** Funciones de muestra ***/
void showClient(stCliente c);
void showAllClients(char archivo[]);
void muestraClientesActivos(char archivo[]);
void muestraClienteInactivos(char archivo[]);

///--------------------------------------------------------------------------------------------------------------------------------///
///--------------------------------------------------------------------------------------------------------------------------------///
/*** FUNCIONES DE CONSUMOS ***/
int  lastIDcharge(char archivo[]);
int  checkCharge(char archivo[], int idCliente);
int  validacionFecha(int dia, int mes, int anio);
int  bajaConsumo(char archivo[], int idConsumo);
int  modificaConsumo(char archivo[], int idConsumo);
void validateCharge(char archivoConsumos[], char archivoClientes[]);
void registerCharge(char consumos[], int idCliente);
int modificaConsumoPorEstructura(char archivo[],stConsumos c);
stConsumos returnChargeByID(char archivo[],int idConsumo);
stConsumos returnByIDandDate(char archivoConsumos[],int idCliente,int dia, int mes, int anio);
/*** Funciones de busqueda de Consumos***/
int  searchByDay(char archivo[],int dia);
int  searchByMonth(char archivo[],int mes);
int  searchByYear(char archivo[],int anio);
int  searchByDate(char archivo[],int anio, int mes, int dia);
int  comparaFechas(char archivo[],int dia, int mes, int anio);
void showClientCharge(int idCliente);
stConsumos retornaConsumoEnFecha(stConsumos consumos[], int v,int dia, int mes, int anio);
stConsumos seleccionCampoAmodificarConsumos(stConsumos c);
/*** Funciones de muestra ***/
void showCharge(stConsumos c);
void showAllConsumptions(char archivo[]);
void showAllConsumptionsByYear(char archivo[],int dia,int mes,int anio);
void showChargesByClient(char archivoConsumos[],stCliente client);
void showByYear(char archivo[],int anio);
///--------------------------------------------------------------------------------------------------------------------------------///
///--------------------------------------------------------------------------------------------------------------------------------///

/*** FUNCIONES DE ARREGLOS ***/
int  fileToClientsArray(char archivo[], stCliente array[],int dim);
int  fileToChargesArray(char archivo[], stConsumos array[],int dim);
int  fileToArrayByLastname(char archivo[], stCliente array[],int dim,char apellido[]);
int  fileToChargesArrayByID(char archivo[], stConsumos array[],int dim,int idCliente);
void showClientsArray(stCliente c[], int v);
void showChargesArray(stConsumos c[], int v);

int cuentaRegistros(char archivo[],int tamanioSt);
char getMesActual();
int getDiaActual();
int getMesRandom();
int getDiaRandom();
void cargaConsumosAleatorios(char archivoConsumos[], stConsumos origen);
stConsumos AsignaConsumos(int cantidadClientes);
void cargaMilRandom();
///***OTRAS FUNCIONES DE FECHA ***///
int returnDay();
int returnMonth();
int returnYear();

///--------------------------------------------------------------------------------------------------------------------------------///
///--------------------------------------------------------------------------------------------------------------------------------///
/*** MAIN ***/
int main()
{
    menuPrincipal();
//    int diaaa=returnDay();
//    int messs=returnMonth();
//    int aniio=returnYear();
//    printf("Hoy es %d de %d del %d", diaaa, messs,aniio);


    return 0;
}

///--------------------------------------------------------------------------------------------------------------------------------///
///--------------------------------------------------------------------------------------------------------------------------------///
/**** FUNCIONES MENU ***/
/*** Menu Principal ***/ //inicio del programa
void menuPrincipal(){
    int opcion = -1;
    char repite = 1;

    do{
        system("cls");
        tituloPrincipal();
        printf("\n\n\n\t\t\t\t   Bienvenido a su gestor de CLIENTES / CONSUMOS \n");
        printf("\n\n\t\t\t\t\t\t Desea ingresar %c",63);
        printf("\n\n\n\t\t\t\t [1].SI \t\t\t\t  [2].NO \n\n");
        printf("\n\t------------------------------------------------------------------------------------------------------------\n");
        printf("\t\t\t\t\t\t [0].SALIR \n");
        printf("\t------------------------------------------------------------------------------------------------------------\n");
        printf("\n\t\t\t\t\t\t  Ingrese su opci%cn: [ ]\b\b",162);   //se solicita una opcion de acceso a los submenús
        scanf("%d",&opcion);

        switch(opcion){
            case 1:   //en caso de que se elija S, se procede a la baja
                menuInicio();
                break;

            case 2:   // en caso de que se elija N, no se modifica ningun dato.
                menuSaludoFinal();
				printf("\n\n\n\n\n\t\t\t\t");
				system("pause");
                break;

            case 0:
				repite = 0;
				menuSaludoFinal();
				printf("\n\n\n\n\n\t\t\t\t");
				system("pause");
				break;
            }
	}while(repite);
}

/*** Saludo Final ***/ //saludo de cierre del programa
void menuSaludoFinal(){

    system("cls");
    tituloPrincipal();
    printf("\n\n\n\n\t\t\t\t\t     Gracias por utilizar nuestro servicio.");
    printf("\n\n\n\n\n\t------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t   created by Apolo 11%c",169);
    printf("\n\t------------------------------------------------------------------------------------------------------------\n");

}

/*** Titulo Principal ***/  //titulo que aparece en cada pantalla
void tituloPrincipal(){
    system("cls");
    printf("\n\t------------------------------------------------------------------------------------------------------------\n");
    printf("\t------------------------------------------------------------------------------------------------------------\n");
    printf("\t********************************************** DATASTORE S.A ***********************************************");
    printf("\n\t------------------------------------------------------------------------------------------------------------\n");
    printf("\t------------------------------------------------------------------------------------------------------------\n");
}

/*** Menu Inicial ***/  //primer menu al ingresar al sistema
void menuInicio(){
	char repite = 1;
	int opcion = -1;

	/* Cuando el usuario ingresa texto en lugar de  una opción, el programa no modifica el valor de opcion.
	 En ese caso, se está inicializando la variable opcion con un valor que no permita ejecutar ningún case.
	 Vuelve a interar y pide nuevamente la opción. */

	do {
		system("cls");
		tituloPrincipal();  //muestra el nombre del comercio
		printf("\n\t\t\t\t\t\t    MENU PRINCIPAL\n\n");
		printf("\n\n\t\t\t\t [1].CLIENTES \t\t\t\t  [2].CONSUMOS\n\n\n\n\n");
		printf("\n\t------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t\t\t [0].SALIR \n");
		printf("\t------------------------------------------------------------------------------------------------------------\n");
		printf("\n\t\t\t\t\t\t Ingrese su opci%cn: [ ]\b\b",162);   //se solicita una opcion de acceso a los submenús
		scanf( "%d",&opcion);

		switch(opcion){

			case 1:
				menuClientes();
				break;

			case 2:
				menuConsumos();
				break;

			case 0:
				repite = 0; //en caso de querer salir,se elije el case 3 que cambia el valor de repite para cortar el ciclo
				break;
		}
	}while(repite);
}

/*** Menu Clientes ***/     // menu donde se podran ejecutar funciones relacionadas a los clientes
void menuClientes(){
    char repite = 1;
    int opcion = -1;
    char dni[10];
    int bajaC = -1;
    int existe = -1;
    stCliente cliente;
    int reactivar = -1;

	do {
		system("cls");
        tituloPrincipal();
        printf("\n\t\t\t\t\t\t MENU CLIENTES \n\n");
        printf("\t\t\t\t\t[1]. Alta de cliente \n");
		printf("\t\t\t\t\t[2]. Baja de cliente \n");
		printf("\t\t\t\t\t[3]. Buscar un cliente \n");
		printf("\t\t\t\t\t[4]. Reactivar cliente \n");
		printf("\t\t\t\t\t[5]. Modificar datos del cliente \n");
		printf("\t\t\t\t\t[6]. Ver listado de clientes \n\n\n");

        printf("\n\t------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t [0].SALIR ");
		printf("\n\t------------------------------------------------------------------------------------------------------------\n");

		printf("\n\t\t Ingrese su opci%cn: [ ]\b\b",162);   //solicita la opcion de ingreso a los submenús
        scanf("%d",&opcion);

		switch(opcion){
			case 1:
			    tituloPrincipal();
				clientRegister(AR_CLI);     //se llama a la funcion de alta de cliente validando la NO existencia previa
				break;

			case 2:
			    tituloPrincipal();
                printf("\n\t\t\t Ingrese el DNI del cliente a dar de baja: ");  //se solicita dni del cliente
                scanf("%s",dni);
                existe=searchByDNI(AR_CLI,dni);        //se corrobora la existencia del mismo
                if(existe == 1){
                    printf("\n\t\t\t\t Los datos del cliente a dar de baja son los siguientes: \n");  //en caso de existencia se muestran sus datos para que el usuario vea si corresponden al cliente o hay algun error en la busqueda
                    cliente=returnByDNI(AR_CLI,dni);    //se devuelve la estructura de cliente
                    showClient(cliente);                //se muestran sus datos
                    printf("\n\n\n\t\t\t\t Esta seguro que desea continuar con la baja? [S/N]");  //se hace una doble validacion para la baja
                    printf("\n\n\t\t\t\t Ingrese su opci%cn: [ ]\b\b",162);   //se toma la opcion ingresada en la validacion
                    scanf("%s",&opcion);
                    switch(opcion){
                    case 'S':   //en caso de que se elija S, se procede a la baja
                        bajaC=bajaCliente(AR_CLI,dni);
                        if(bajaC==1){
                            printf("\n\t\t\t\t El cliente ha sido dado de baja correctamente. \n\n\n");
                        }
                    stopProgram();
                        break;
                    case 'N':   // en caso de que se elija N, no se modifica ningun dato.
                        printf("\n\t\t\t\t No se procedi%c a la baja del cliente. \n\n\n",162);
                        stopProgram();
                        break;
                    } //cierro switch
                }else{  //en caso de que no se haya encontrado el dni a dar de baja, se le informa al usuario la NO existencia del cliente
                    printf("\n\t\t\t\t El DNI ingresado no se encuentra asociado a ning%cn cliente\n\n",163);
                    stopProgram();
                    }
                break;

			case 3:
				menuBuscar();
				break;

            case 4:
                tituloPrincipal();
			    printf("\n\t\t\t\t Ingrese el DNI del cliente a reactivar: ");    //se solicita el DNI del cliente
			    scanf("%s",dni);
				existe=searchByDNI(AR_CLI,dni);    //se corrobora su existencia
                    if(existe == 1){
                        printf("\n\t\t\t  Los datos del cliente a reactivar son los siguientes: \n"); //se muestran sus datos para corroborar que sean correctos
                        cliente=returnByDNI(AR_CLI,dni);
                        showClient(cliente);    //se muestra
                        printf("\n\n\n\t\t\t Esta seguro que desea continuar con la reactivaci%cn del cliente? [S/N]",162);  //se realiza una doble validacion para saber si realmente se procede a la reactivacion
                        printf("\n\n\t\t\t\t Ingrese su opci%cn: [ ]\b\b",162);   //se ingresa la opcion elegida por el usuario
                        scanf("%s",&opcion);
                        switch(opcion){
                            case 'S':   //en caso de presionar S, se reactiva el cliente y se informa al usuario
                                system("cls");
                                tituloPrincipal();
                                reactivar=reactivarCliente(AR_CLI,dni);
                                if(reactivar==1){
                                printf("\n\t\t\t\t El cliente ha sido reactivado correctamente. \n\n\n");
                                }
                                stopProgram();
                                break;
                            case 'N':  //en caso de presionar N, no se realizan modificaciones
                                system("cls");
                                tituloPrincipal();
                                printf("\n\t\t\t\t No se procedi%c a la reactivaci%cn del cliente. \n\n\n",162,162);
                                stopProgram();
                                break;
                            } //cierro switch
                        }else{  //en caso de no encontrar el dni en la busqueda, se informa al usuario la NO existencia del cliente en el archivo de datos
                        printf("\n\t\t\t\t El DNI ingresado no se encuentra asociado a ning%cn cliente\n\n",163);
                        stopProgram();
                        }
                    break;

			case 5:
			    tituloPrincipal();
			    printf("\n\t\t\t\t Ingrese el DNI del cliente a modificar: ");    //se solicita el DNI del cliente
                scanf("%s",dni);
			    cliente=returnByDNI(AR_CLI,dni);    //guardo el cliente encontrado con ese DNI en una estructura cliente
                cliente=seleccionCampoAmodificar(cliente); //la paso por parametro y guardo el resultado modificado en esa misma estructura
				modificaCliente(AR_CLI,cliente);    //la recibo nuevamente por parametro para modificarla en el archivo
				stopProgram();
				break;

			case 6:
				menuMuestraClientes();
				break;

			case 0:
				repite = 0;
				break;
		}
	}while(repite);
}

/*** Menu Muestra Clientes ***/
void menuMuestraClientes(){
	char repite = 1;
	int opcion = -1;
	int inactivos;
	int activos;

	do {
		system("cls");
        tituloPrincipal();
        printf("\n\t\t\t\t\t MOSTRAR LISTADO DE CLIENTES \n\n");
		printf("\t\t\t\t\t[1]. Clientes ACTIVOS. \n");
		printf("\t\t\t\t\t[2]. Clientes INACTIVOS. \n");
		printf("\t\t\t\t\t[3]. Todos los clientes \n\n\n");
		printf("\t------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t\t [0].SALIR \n");
		printf("\t------------------------------------------------------------------------------------------------------------\n");
		printf("\n\t\t\t Ingrese su opci%cn: [ ]\b\b",162);
        scanf("%d",&opcion);

        switch(opcion){

        case 1:
            activos = buscaClientesActivos(AR_CLI); //si encuentra al menos un activo retorna true
            if(activos == 1){
                muestraClientesActivos(AR_CLI);     //muestra los clientes activos
                }else{
                printf("\n\t\t\t No se encontraron clientes activos \n"); //en caso de no haber, informa al usuario
                }
            stopProgram();
            break;

        case 2:
            inactivos = buscaClientesInactivos(AR_CLI); //si encuentra al menos un inactivo retorna true
            if(inactivos==1){
                muestraClienteInactivos(AR_CLI);    //muestra los clientes inactivos
            }else{
                printf("\n\t\t\t No se encontraron clientes inactivos \n");   //en caso de no haber, informa al usuario
                }
            stopProgram();
            break;

        case 3:
            showAllClients(AR_CLI);
            stopProgram();
            break;

        case 0:
            repite = 0;
            break;
        }

	} while (repite);
}

/*** Menu Búsqueda de Clientes ***/
void menuBuscar(){
	int  id;
    int  existe;
	int  nroCliente;
    int  vByLastname=0;
    char repite = 1;
	char dni[10];
	char apellido[30];
	char opcion=-1;
	stCliente cliente;
	stCliente clientesByLastname[DIM];


	do {
		system("cls");
        tituloPrincipal();
        printf("\n\t\t\t\t\t  BUSQUEDA DE CLIENTES \n\n");
		printf("\t\t\t\t\t[1]. Buscar por ID \n");
		printf("\t\t\t\t\t[2]. Buscar por DNI \n");
		printf("\t\t\t\t\t[3]. Buscar por apellido \n");
		printf("\t\t\t\t\t[4]. Buscar por n%cmero de cliente \n\n\n",163);
        printf("\t------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t\t [0].SALIR \n");
		printf("\t------------------------------------------------------------------------------------------------------------\n");
		printf("\n\t\t\t Ingrese su opci%cn: [ ]\b\b",162);
        scanf("%d",&opcion);

        switch(opcion){
            case 1:
            system("cls");
            tituloPrincipal();
            printf("\n\t\t\t\t  Ingrese el ID del cliente: ");    //se solicita el ID para realizar la busqueda en el archivo
            scanf("%d",&id);
            existe=searchByID(AR_CLI,id);    //si existe devuelve 1, sino 0
            if(existe == 1){
                cliente=returnByID(AR_CLI,id);
                printf("\n\t\t\t\t Los datos encontrados para el ID %d fueron: \n",id);  //en caso de existencia se muestran sus datos
                showClient(cliente);
                }else{
                printf("\n\n\n\t\t\t\t No se encontraron clientes asociados al ID: %d \n\n\n\n",id);    //en caso de no encontrar muestra el mensaje al usuario
                }
            stopProgram();
            break;

            case 2:
            system("cls");
            tituloPrincipal();
            printf("\n\t\t\t\t  Ingrese el DNI del cliente: ");  //se solicita el DNI para realizar la busqueda en el archivo
            fflush(stdin);
            scanf("%s",dni);
            existe=searchByDNI(AR_CLI, dni);
            if(existe == 1){
                cliente=returnByDNI(AR_CLI,dni);    //se realiza la busqueda por DNI y se retorna su estructura en caso de existir
                printf("\n\t\t\t\t Los datos encontrados para el DNI %s fueron: \n",dni);  //en caso de existencia se muestran sus datos
                showClient(cliente);
                }else{
                    printf("\n\n\n\t\t\t\t No se encontraron clientes asociados al DNI: %s \n\n\n\n",dni);
                }
            stopProgram();
            break;

            case 3:
            system("cls");
            tituloPrincipal();
            printf("\n\t\t\t\t  Ingrese el apellido del cliente: ");  //se solicita el DNI para realizar la busqueda en el archivo
            fflush(stdin);
            scanf("%s",apellido);
            existe=searchByLastname(AR_CLI, apellido);
            if(existe == 1){
                ///paso los apellidos a un arreglo por si hay mas de un cliente con el mismo apellido
                vByLastname=fileToArrayByLastname(AR_CLI,clientesByLastname,DIM,apellido);
                printf("\n\t\t\t\t Los datos encontrados para el apellido %s fueron: \n",apellido);  //en caso de existencia se muestran sus datos
                showClientsArray(clientesByLastname,vByLastname);
                }else{
                printf("\n\n\n\t\t\t\t No se encontraron clientes asociados al apellido: %s \n\n\n\n",apellido);
                }
            stopProgram();
            break;

            case 4:
            system("cls");
            tituloPrincipal();
            printf("\n\t\t\t\t  Ingrese el nro de cliente: ");  //se solicita el DNI para realizar la busqueda en el archivo
            scanf("%d",&nroCliente);
            existe=searchByClientNumber(AR_CLI,nroCliente);
            if(existe == 1){
                cliente=returnByClientNumber(AR_CLI,nroCliente);    //se realiza la busqueda por DNI y se retorna su estructura en caso de existir
                printf("\n\t\t\t\t Los datos encontrados para el nro. de cliente %d fueron: \n",nroCliente);  //en caso de existencia se muestran sus datos
                showClient(cliente);
                }else{
                printf("\n\n\n\t\t\t\t No se encontraron clientes asociados al nro de cliente: %d \n\n\n\n",nroCliente);
                }
            stopProgram();
            break;

        case 0:
            repite = 0; //en caso de que la opcion ingresada sea SALIR, repite toma valor 0 para finalizar la iteracion del ciclo.
            break;
        }
    }while (repite);
}

/*** Menu de finalizacion de modificaciones ***/
char finalizaModificacion(){
    int repite = 1;
    char opcion=-1;
    char ESC;

    system("cls");
    tituloPrincipal();
    printf("\n\n\t\t\t\t Los datos se actualizaron correctamente");

    do{
        printf("\n\n\n\t\t\t\t Desea realizar otro cambio o modificaci%cn? [S/N]",162);
        printf("\n\n\t\t\t\t Ingrese su opci%cn: [ ]\b\b",162);
        fflush(stdin);
        scanf("%c",&opcion);
        switch(opcion){
            case 'S':
                ESC=27;
                break;

            case 'N':
                repite=0;
                ESC=27;
                break;
        }
    }while(ESC !=27);

    return repite;
}

/*** Ejecuta una pausa con mensaje para continuar ***/
void stopProgram(){
    printf("\n\t\t\t\t\t");
    system("pause");    //pausa el sistema y muestra el mensaje centrado con el diseño del programa
}

///--------------------------------------------------------------------------------------------------------------------------------///
/*** FUNCIONES DE CLIENTES ***/
/*** Retorna ultimo ID ***/
int lastID(char archivo[]){
    stCliente cli;
    int id=0;

    FILE *pf = fopen(archivo, "rb");          // abro en modo lectura
    if(pf){
        fseek(pf, sizeof(stCliente) * -1, SEEK_END);  //me posiciono -1 registro al final del archivo
        if(fread(&cli, sizeof(stCliente),1,pf) > 0){      //leo el dato de ese registro
                id=cli.id;                                      //asigno el ultimo id
        }
      fclose(pf);         //cierro el archivo
    }
    return id;  //retorno el ultimo id encontrado en el archivo
}

/*** String del campo baja***/
void getEstadoCliente(int estadoCliente, char estado[]){

    switch(estadoCliente){
        case 0: strcpy(estado, "Activo");
            break;
        case 1: strcpy(estado, "Inactivo");
            break;
    }
}

/*** Alta clientes con validacion ***/
void clientRegister(char archivo[]){
    stCliente c;
    char ESC;
    char dni[20];
    int busquedaDni;

        system("cls");
        tituloPrincipal();
        while(ESC != 27){
            printf("\n\n\t\t\t\t\t Ingrese el DNI del nuevo cliente. \n\t\t\t\t Se verificar%c que no exista en la base de datos. \n",160);  ///pido el dni
            printf("\n\t\t\t\t\t DNI...................:");
            fflush(stdin);
            scanf("%s",dni);                                            //guardo en dni el valor del dni ingresado

            busquedaDni=searchByDNI(AR_CLI,dni);                   // realizo validacion del dni y retorno su valor para saber si existe o no
            if(busquedaDni == 1){
                printf("\n\t\t\t-------------------------------------------------------------------------\n");
                printf("\n\t\t\t El DNI que intenta cargar ya se encuentra asociado a otro cliente. \n");
            }
            else{
                system("cls");
                tituloPrincipal();
                printf("\n\t\t\t\t\tEl dni ingresado NO fue encontrado.");
                printf("\n\t\t\t\t\t Puede continuar con la carga datos.\n");
                enterClient(AR_CLI);
            }
            printf("\n\t\t\t     Presione ESC para salir o cualquier tecla para continuar\n");
            ESC = getch();
            system("cls");
    }
}

/*** Carga de datos de cliente ***/
void enterClient(char cliente[]){
    stCliente c;
    char ESC = 0;
    int id=lastID(AR_CLI) + 1;
    char estado[15];

    FILE *pf= fopen(cliente,"ab");        //abro archivo en modo append
    if(pf){

        do{ printf("\n\t\t------------------------------------------------------------------------------\n");
            printf("\n\n\t\t\t\t   DATOS DEL NUEVO CLIENTE \n\n");      //cargo el nuevo cliente

            c.id=id;
            printf("\t\t\t   ID CLIENTE................:%d \n",c.id);

            printf("\t\t\t   NRO CLIENTE................:");
            scanf("%d",&c.nroCliente);

            printf("\t\t\t   NOMBRE................:");
            fflush(stdin);
            scanf("%[^\n]",c.nombre);   //captura todos los datos ingresados hasta el enter, incluso espacios en blanco

            printf("\t\t\t   APELLIDO..............:");
            fflush(stdin);
            scanf("%[^\n]",c.apellido); //captura todos los datos ingresados hasta el enter, incluso espacios en blanco

            printf("\t\t\t   DNI...................:");
            fflush(stdin);
            scanf("%s",c.dni);

            printf("\t\t\t   EMAIL..............:");
            fflush(stdin);
            scanf("%s",c.email);

            printf("\t\t\t   DOMICILIO..............:");
            fflush(stdin);
            scanf("%[^\n]",c.domicilio);    //captura todos los datos ingresados hasta el enter, incluso espacios en blanco

            printf("\t\t\t   TELEFONO MOVIL..............:");
            fflush(stdin);
            scanf("%s",c.telefonoMovil);

            c.baja=0;   //colocamos 0 automaticamente, lo que significa que no esta de baja, por ende se esta activando en el alta
            getEstadoCliente(c.baja, estado);
            printf("\t\t\t   ESTADO DE CLIENTE................:%s",estado);

            fwrite(&c, sizeof(stCliente), 1 ,pf);      //escribo los datos en el archivo
            id++;

            printf("\n\n\n\t\t     Presione ESC para salir o cualquier tecla para continuar\n");
            ESC = getch();
            system("cls");
        }
        while(ESC != 27);

        fclose(pf);            //cierro el archivo
        tituloPrincipal();
        printf("\n\t\t\t        El nuevo cliente se ha cargado exitosamente \n\n\n");
        printf("\n\t\t------------------------------------------------------------------------------\n");
    }
}

/*** Baja de cliente (sin eliminar sus datos) ***/
int bajaCliente(char archivo[], char dni[]){
    int flag=0;
    stCliente c;

    FILE *pf = fopen(archivo, "r+b");

    if(pf){
        while(flag==0 && fread(&c, sizeof(stCliente), 1, pf) > 0){
            if(strcmp(c.dni,dni)==0){
                c.baja=1;   //coloco el estado en baja
                flag = 1;
                fseek(pf, -1 * sizeof(stCliente), SEEK_CUR);
                fwrite(&c,sizeof(stCliente),1, pf);
                }
            }
        fclose(pf);
    }
    return flag;        //retorna si se puso hacer la baja correctamente.
}

/*** Reactivar de Cliente ***/
int reactivarCliente(char archivo[],char dni[]){
    int flag=0;
    stCliente c;

    FILE *pf = fopen(archivo, "r+b");

    if(pf){
        while(flag==0 && fread(&c, sizeof(stCliente), 1, pf) > 0){
            if(strcmp(c.dni,dni)==0){
                c.baja=0;   //posiciona en 0 al cliente, en alta.
                flag = 1;
                fseek(pf, -1 * sizeof(stCliente), SEEK_CUR);
                fwrite(&c,sizeof(stCliente),1, pf);
                }
            }
        fclose(pf);
    }
    return flag;    //retorna si se pudo hacer la reactivacion.
}

/*** Seleccion de campos a modificar y retorno de estructura modificada ***/
stCliente seleccionCampoAmodificar(stCliente c){
    int repite = 1;
    int opcion=0;
    char ESC;

    printf("\t\t------------------------------------------------------------------------------\n");
    printf("\n\n\t\t\t\t\t Datos Actuales del cliente: \n");
    showClient(c);

	do {
        printf("\n\t------------------------------------------------------------------------------------------------------------\n");
		printf("\n\n\t\t\t\t\t Seleccione el campo a modificar \n\n");
        printf("\t\t\t\t[1]. Nro de cliente \n");
		printf("\t\t\t\t[2]. Nombre\n");
		printf("\t\t\t\t[3]. Apellido\n");
		printf("\t\t\t\t[4]. DNI\n");
		printf("\t\t\t\t[5]. Email \n");
		printf("\t\t\t\t[6]. Domicilio  \n");
		printf("\t\t\t\t[7]. Telefono Movil\n\n");
        printf("\t------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t [0].SALIR ");
		printf("\n\t------------------------------------------------------------------------------------------------------------\n");
		printf("\n\t\t\t\t Ingrese su opci%cn: [ ]\b\b",162);
        scanf("%d",&opcion);

		switch(opcion){

			case 1:
			    printf("\n\n\t\t\t\t Ingrese el nuevo nro de Cliente: "); //solicita el dato a cambiar
			    scanf("%d",&c.nroCliente);              //guarda el nuevo dato en la estructura del cliente
                repite=finalizaModificacion();          //pregunta si va a hacer mas cambio o no
                break;                                     //sale

			case 2:
                printf("\n\n\t\t\t\t Ingrese el nuevo nombre del Cliente: ");//solicita el dato a cambiar
                fflush(stdin);
			    scanf("%[^\n]", c.nombre);                  //guarda el nuevo dato en la estructura del cliente
			    repite=finalizaModificacion();          //pregunta si va a hacer mas cambio o no
                break;

			case 3:
		        printf("\n\n\t\t\t\t Ingrese el nuevo apellido del Cliente: ");   //solicita el dato a cambiar
		        fflush(stdin);
			    scanf("%[^\n]", c.apellido);            //guarda el nuevo dato en la estructura del cliente
			    repite=finalizaModificacion();      //pregunta si va a hacer mas cambio o no
                break;

			case 4:
                printf("\n\n\t\t\t\t Ingrese el nuevo DNI del Cliente: ");    //solicita el dato a cambiar
                fflush(stdin);
			    scanf("%s", c.dni);                 //guarda el nuevo dato en la estructura del cliente
			    repite=finalizaModificacion();         //pregunta si va a hacer mas cambio o no
                break;

			case 5:
                printf("\n\n\t\t\t\t Ingrese el nuevo email del Cliente: ");  //solicita el dato a cambiar
                fflush(stdin);
			    scanf("%s",c.email);                    //guarda el nuevo dato en la estructura del cliente
                repite=finalizaModificacion();          //pregunta si va a hacer mas cambio o no
                break;

			case 6:
                printf("\n\n\t\t\t Ingrese el nuevo domicilio del Cliente: ");    //solicita el dato a cambiar
                fflush(stdin);
			    scanf("%[^\n]", c.domicilio);                   //guarda el nuevo dato en la estructura del cliente
			    repite=finalizaModificacion();              //pregunta si va a hacer mas cambio o no
                break;

            case 7:
                printf("\n\n\t\t\t\t Ingrese el nuevo telefono movil del Cliente: "); //solicita el dato a cambiar
                fflush(stdin);
			    scanf("%s", c.telefonoMovil);           //guarda el nuevo dato en la estructura del cliente
                repite=finalizaModificacion();          //pregunta si va a hacer mas cambio o no
                break;

			case 0:
                repite = 0;
                menuClientes();
				break;
		}
	}while(repite);

    return c;   //retorna la estructura con los datos modificados para que luego sea reemplaza en el archivo por otra funcion
}

/*** Modificacion de datos del cliente en archivo ***/
void modificaCliente(char archivo[],stCliente c){
    stCliente a;
    FILE *pf = fopen(archivo, "r+b");   //abro el archivo en modo lectura y escritura
    int flag=0;

    if(pf){
        while(flag == 0 && fread(&a, sizeof(stCliente), 1, pf)>0){ // recorro el archivo
            if(a.id==c.id){                             // encuentro el id donde esta el dato a modificar
                a=c;        //coloco los datos de la nueva estructura recibida en la posicion deseada
                flag=1;
            }
            fseek(pf, -1 * sizeof(stCliente), SEEK_CUR);    //me posiciono una estructura para atras desde donde quedo el cursor de lectura
            fwrite(&a, sizeof(stCliente), 1, pf);            // escribo la nueva estructura
        }
        fclose(pf);
    }
}

///**** FUNCIONES DE BUSQUEDA Y RETORNO ***/
/*** Busqueda por DNI ***//***VALIDACION***/
int searchByDNI(char archivo[],char dni[]){

    stCliente c;
    int flag=0;

    FILE *pf = fopen(archivo,"rb");      //abro el archivo para leer sus datos
    if(pf){
        while(flag == 0 && fread(&c,sizeof(stCliente),1,pf) > 0){   // leer el archivo de a un cliente
             if(strcmp(c.dni,dni)==0){                          // comparo el dni ingresado con el dato dni de ese cliente
                flag=1;
             }
        }
        fclose(pf);
    }
    return flag;
}

/*** Retorna cliente por DNI***/
stCliente returnByDNI(char archivo[], char dni[]){
    int flag=0;
    stCliente c;

    FILE *pf = fopen(archivo, "rb");         //solo lectura
    if(pf){
        while(flag==0 && fread(&c,sizeof(stCliente),1,pf)> 0){
            if(strcmp(c.dni,dni)==0){
               flag = 1;
            }
        }
        fclose(pf);
    }
    return c;
}

/*** Busqueda por ID ***/
int searchByID(char archivo[],int id){
    stCliente c;
    int flag=0;

    FILE *pf = fopen(archivo, "rb");      //solo lectura
    if(pf){
        while(flag==0 && fread(&c,sizeof(stCliente),1,pf)> 0){
            if(c.id==id){
            flag=1;
            }
        }
        fclose(pf);
    }
    return flag;
}

/*** Retorna cliente por ID ***/
stCliente returnByID(char archivo[],int id){
    stCliente c;
    int flag=0;

    FILE *pf = fopen(archivo, "rb");         //solo lectura
    if(pf){
        while(flag==0 && fread(&c,sizeof(stCliente),1,pf)> 0){
            if(c.id==id){
            flag=1;
            }
        }
        fclose(pf);
    }
    return c;
}

/*** Busqueda por apellido ***/
int searchByLastname(char archivo[],char apellido[]){
    stCliente c;
    int flag=0;

    FILE *pf = fopen(archivo,"rb");         //solo lectura
    if(pf){
        while(flag==0 && fread(&c,sizeof(stCliente),1,pf)> 0){
            if(strcmp(c.apellido,apellido)==0){
                flag=1;
            }
        }
        fclose(pf);
    }
    return flag;
}

/*** Retorna estructura por apellido ***/
stCliente returnByLastname(char archivo[],char apellido[]){
    stCliente c;
    int flag=0;

    FILE *pf = fopen(archivo,"rb");         //solo lectura
    if(pf){
        while(flag==0 && fread(&c,sizeof(stCliente),1,pf)> 0){
            if(strcmp(c.apellido,apellido)==0){
                flag=1;
            }
        }
        fclose(pf);
    }
    return c;
}

/*** Busqueda por numero de Cliente ***/
int searchByClientNumber(char archivo[],int numCliente){
    stCliente c;
    int flag=0;

    FILE *pf = fopen(archivo, "rb");         //solo lectura
    if(pf){
        while(flag==0 && fread(&c,sizeof(stCliente),1,pf)> 0){
            if(c.nroCliente==numCliente){
                flag=1;
            }
        }
        fclose(pf);
    }
    return flag;
}

/*** Retorna estructura por numero de Cliente ***/
stCliente returnByClientNumber(char archivo[],int numCliente){
    stCliente c;
    int flag=0;

    FILE *pf = fopen(archivo, "rb");         //solo lectura
    if(pf){
        while(flag==0 && fread(&c,sizeof(stCliente),1,pf)> 0){
            if(c.nroCliente==numCliente){
                flag=1;
            }
        }
        fclose(pf);
    }
    return c;
}

/*** Busca si hay clientes INACTIVOS ***/
int buscaClientesInactivos(char archivo[]){
    stCliente c;
    int flag=0;

    FILE *pf = fopen(archivo,"rb"); //abro en modo lectura
    if(pf){
        while(flag == 0 && fread(&c, sizeof(stCliente), 1 ,pf)> 0){
            if(c.baja==1){
                flag=1;     //salgo si encuentro el dato con flag en 1
            }
        }
        fclose(pf); //cierro el archivo
     }else{
        printf("\n ERROR DE APERTURA DE ARCHIVO \n");
    }
    return flag;    //retorno si hay al menos un dato de cliente inactivo
}

/*** Busca si hay clientes ACTIVOS ***/
int buscaClientesActivos(char archivo[]){
    stCliente c;
    int flag=0;

    FILE *pf = fopen(archivo,"rb"); //abro archivo en modo lectura
    if(pf){
        while(flag ==0 && fread(&c, sizeof(stCliente), 1 ,pf)> 0){
            if(c.baja==0){  //si encuentor algun campo en 0, al menos 1
                flag=1;     //salgo del recorrido con flag en 1
            }
        }
        fclose(pf);
     }else{
        printf("\n ERROR DE APERTURA DE ARCHIVO \n");
    }
    return flag;    //retorno que existen datos de clientes activos
}

///****FUNCIONES DE MUESTRA ***/
/*** Muestra clientes Activos ***/
void muestraClientesActivos(char archivo[]){
    stCliente c;

    FILE *pf = fopen(archivo,"rb"); //leo el archivo

    if(pf){
        while(fread(&c, sizeof(stCliente), 1 ,pf)> 0){
            if(c.baja==0){
            showClient(c);  //muestro cada cliente que encuentre activo
            }
        }
        fclose(pf);
    } else{
        printf("\n ERROR DE APERTURA DE ARCHIVO \n");
    }
}

/*** Muestra clientes Inactivos ***/
void muestraClienteInactivos(char archivo[]){
    stCliente c;

    FILE *pf = fopen(archivo,"rb");     //leo el archivo
    if(pf){
        while(fread(&c, sizeof(stCliente), 1 ,pf)> 0){
            if(c.baja==1){          //por cada cliente inactivo lo muestro
            showClient(c);
            }
        }
        fclose(pf);
     }else{
        printf("\n ERROR DE APERTURA DE ARCHIVO \n");
    }
}

/*** Mostrar un cliente ***/
void showClient(stCliente c){

    char estado[15];
    getEstadoCliente(c.baja, estado);

    printf("\n\t\t----------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t ID CLIENTE: %-d \t\t\t\t NRO CLIENTE: %d", c.id, c.nroCliente);
    printf("\n\t\t----------------------------------------------------------------------------------------\n");
   // printf("\n\t\t\t DATOS PERSONALES:");
    printf("\n\t\t\t\t Nombre y apellido: %-s %-s",c.nombre, c.apellido);
    //printf("\n\t\t\t Apellido: %-s", c.apellido);
    printf("\n\t\t\t\t DNI: %s", c.dni);
    printf("\n\t\t\t\t Domicilio: %s", c.domicilio);
   // printf("\n\t\t------------------------------------------------------------------\n");
   // printf("\n\n\t\t\t DATOS DE CONTACTO:");
    printf("\n\t\t\t\t Email: %s", c.email);
    printf("\n\t\t\t\t Tel%cfono m%cvil: %s",130,162,c.telefonoMovil);
    printf("\n\t\t----------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t ESTADO DE CLIENTE: %s",estado);  //muestro el estado en forma de texto pero conserva internamente su valor numerico 0 o 1 segun el estado
    printf("\n\t\t----------------------------------------------------------------------------------------\n\n\n");

}

/***Muestra todos los clientes***/
void showAllClients(char archivo[]){
    stCliente c;

    FILE *pf = fopen(archivo,"rb"); //abro en modo lectura

    if(pf){
        while(fread(&c, sizeof(stCliente), 1 ,pf)> 0 ){ //recorro todo el archivo y por cada vez que leo muestro un cliente
            showClient(c);
        }
        fclose(pf);
    } else{
        printf("\n ERROR DE APERTURA DE ARCHIVO \n");
    }
}

///--------------------------------------------------------------------------------------------------------------------------------///
///--------------------------------------------------------------------------------------------------------------------------------///
/**** FUNCIONES DE MENU CONSUMOS ***/

///*** Menu consumos ***/
void menuConsumos(){
    char repite = 1;
    int opcion = -1;
    int opc=-1;
    int idConsumo;
    char dni[10];
    stConsumos consumo;
    stCliente cliente;
    int existe;
    int cancel;
    int modificado;
    int existeConsumo;

	do {
		system("cls");
		tituloPrincipal();
		printf("\n\t\t\t\t\t\t MENU CONSUMOS \n\n");
        printf("\t\t\t\t\t[1]. Alta de consumos \n");
		printf("\t\t\t\t\t[2]. Baja de consumos \n");
		printf("\t\t\t\t\t[3]. Modificar consumos de Cliente \n");
		printf("\t\t\t\t\t[4]. Consulta de consumos \n");
		printf("\t\t\t\t\t[5]. Carga 1000 consumos random \n\n\n");

        printf("\t------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t [0].SALIR \n");
		printf("\t------------------------------------------------------------------------------------------------------------\n");

		printf("\n\t\t\t Ingrese su opci%cn: [ ]\b\b",162);   //solicita la opcion de ingreso a los submenús
        scanf("%d",&opcion);

		switch(opcion){

			case 1:
			    tituloPrincipal();
			    validateCharge(AR_CON, AR_CLI);//se llama a la funcion de alta de consumos validando la existencia previa
				break;

			case 2:
			    tituloPrincipal();
                printf("\n\t\t\t Ingrese el DNI del cliente para dar de baja un consumo: ");  //se solicita dni del cliente
                scanf("%s",dni);
                existe=searchByDNI(AR_CLI,dni);        //se corrobora la existencia del mismo
                if(existe == 1){
                        printf("\n\n\t\t\t\t DATOS DEL CLIENTE. \n\n");
                        cliente=returnByDNI(AR_CLI,dni);    //se devuelve la estructura de cliente
                        showClient(cliente);                //se muestran sus datos
                        stopProgram();
                        system("cls");
                        tituloPrincipal();
                        printf("\n\t------------------------------------------------------------------------------------------------------------\n");
                        printf("\n\t\t\t\t CONSUMOS DEL CLIENTE.\n");  //en caso de existencia se muestran sus consumos
                        existeConsumo=checkCharge(AR_CON,cliente.id);
                        if(existeConsumo ==1 ){
                            showChargesByClient(AR_CON,cliente);    //recibo el archivo de consumos y el cliente para mostrar solo los de ese cliente
                            printf("\n\n\n\t\t\t\t Ingrese el ID del consumo que desea dar de baja [ ]\b\b");  //se hace una doble validacion para la baja
                            scanf("%d",&idConsumo);
                            consumo=returnChargeByID(AR_CON,idConsumo); //retorno el consumo que deseo desactivar
                            //showCharge(consumo);    //lo muestro para chequear que sea el deseado
                            }else{
                                printf("\n\t\t\t\t El cliente no tiene consumos.\n");
                            }

                    cancel=bajaConsumo(AR_CON,idConsumo);   //retorna si el consumo se dio o no de baja
                    if(cancel ==1){
                        printf("\n\t\t\t\t El consumo ha sido dado de baja correctamente. \n\n\n");
                        }else{
                            printf("\n\t\t\t\t No se procedi%c a la baja del consumo. \n\n\n",162);
                        }
                        stopProgram();
                        break;
                    }else{  //en caso de que no se haya encontrado el dni a dar de baja, se le informa al usuario la NO existencia del cliente
                    printf("\n\t\t\t El DNI ingresado no se encuentra asociado a ning%cn cliente\n\n",163);
                    stopProgram();
                    }
                break;

			case 3:
			    tituloPrincipal();
                printf("\n\t\t\t\t Ingrese el DNI del cliente para modificar un consumo: ");  //se solicita dni del cliente
                scanf("%s",dni);
                existe=searchByDNI(AR_CLI,dni);        //se corrobora la existencia del mismo
                if(existe == 1){
                        printf("\n\n\t\t\t\t DATOS DEL CLIENTE. \n\n");
                        cliente=returnByDNI(AR_CLI,dni);    //se devuelve la estructura de cliente
                        showClient(cliente);                //se muestran sus datos
                        stopProgram();
                        system("cls");
                        tituloPrincipal();
                        printf("\n\t------------------------------------------------------------------------------------------------------------\n");
                        printf("\n\t\t\t\t CONSUMOS DEL CLIENTE.\n");  //en caso de existencia se muestran sus consumos
                        existeConsumo=checkCharge(AR_CON,cliente.id);
                        if (existeConsumo ==1 ){
                            showChargesByClient(AR_CON,cliente);    //recibo el archivo de consumos y el cliente para mostrar solo los de ese cliente
                            printf("\n\n\n\t\t\t\t Ingrese el ID del consumo que desea modificar. [ ]\b\b");  //se hace una doble validacion para la baja
                            scanf("%d",&idConsumo);
                            consumo=returnChargeByID(AR_CON,idConsumo); //retorno el consumo que deseo desactivar
                            showCharge(consumo);    //lo muestro para chequear que sea el deseado

                            consumo=seleccionCampoAmodificarConsumos(consumo);
                            modificado=modificaConsumoPorEstructura(AR_CON,consumo);

                            }else{
                                    printf("\n\t\t\t\t El cliente no tiene consumos.\n");
                            }

                        //consumo=seleccionCampoAmodificarConsumos(consumo);
                       // modificado=modificaConsumoPorEstructura(AR_CON,consumo);
                        if(modificado == 1){
                            printf("\n\n\t\t\t El consumo se modifico correctamente.");
                        }else{
                            printf("\n\n\t\t\t El consumo no pudo ser modificado.");
                        }
                    }else{
                     printf("\n\t\t\t El DNI ingresado no se encuentra asociado a ning%cn cliente\n\n",163);
                     stopProgram();
                }
				break;

			case 4:
				menuConsultaConsumos();
				break;

			case 5:
                cargaMilRandom(AR_CON);
                printf("\n\n\t\t\t\t Se han cargadon 1000 consumos aleatorios correctamente");
                stopProgram();
                break;

			case 0:
				repite = 0;
				break;
            }


            }while (repite);

}

void showClientCharge(int idCliente){
    stCliente cliente;
    stConsumos consumo;
    int idConsumo;
    int existeConsumo;

    printf("\n\t\t\t\t CONSUMOS DEL CLIENTE.\n");  //en caso de existencia se muestran sus consumos
    ///como saber si tiene o no consumos un cliente
    //
    existeConsumo=checkCharge(AR_CON,idCliente);
    if (existeConsumo ==1 ){
        showChargesByClient(AR_CON,cliente);    //recibo el archivo de consumos y el cliente para mostrar solo los de ese cliente
        printf("\n\n\n\t\t\t\t Ingrese el ID del consumo que desea dar de baja [ ]\b\b");  //se hace una doble validacion para la baja
        scanf("%d",&idConsumo);
        consumo=returnChargeByID(AR_CON,idConsumo); //retorno el consumo que deseo desactivar
        showCharge(consumo);    //lo muestro para chequear que sea el deseado
    }else{
        printf("\n\t\t\t\t El cliente no tiene consumos.\n");
    }

}

/*** Seleccion de campos a modificar y retorno de estructura modificada CONSUMOS ***/
stConsumos seleccionCampoAmodificarConsumos(stConsumos c){
    int repite = 1;
    int opcion=0;
    char ESC;

	do {
        printf("\n\n\t\t------------------------------------------------------------------\n");
		printf("\n\n\t\t\t\t Seleccione el campo a modificar \n\n");
        printf("\t\t\t[1]. A%co \n", 164);
		printf("\t\t\t[2]. Mes\n");
		printf("\t\t\t[3]. Des \n");
		printf("\t\t\t[4]. Datos Consumidos \n");
        printf("\t\t------------------------------------------------------------------\n");
		printf("\t\t\t\t\t [0].SALIR \n");
		printf("\t\t------------------------------------------------------------------\n");
		printf("\n\t\t Ingrese su opci%cn: [ ]\b\b",162);
        scanf("%d",&opcion);

		switch(opcion){

			case 1:
			    printf("\n\n\t\t\t Ingrese el nuevo a%co del consumo: ", 164); //solicita el dato a cambiar
			    scanf("%d",&c.anio);              //guarda el nuevo dato en la estructura del cliente
                repite=finalizaModificacion();          //pregunta si va a hacer mas cambio o no
                break;                                     //sale

			case 2:
                printf("\n\n\t\t\t Ingrese el nuevo mes del consumo: ");//solicita el dato a cambiar
			    scanf("%d", &c.mes);                  //guarda el nuevo dato en la estructura del cliente
			    repite=finalizaModificacion();          //pregunta si va a hacer mas cambio o no
                break;

			case 3:
		        printf("\n\n\t\t\t Ingrese el nuevo dia del consumo: ");   //solicita el dato a cambiar
			    scanf("%d", &c.dia);            //guarda el nuevo dato en la estructura del cliente
			    repite=finalizaModificacion();      //pregunta si va a hacer mas cambio o no
                break;

			case 4:
  		        printf("\n\n\t\t\t Ingrese el nuevo valor de datos consumidos: ");   //solicita el dato a cambiar
			    scanf("%d", &c.datosConsumidos);            //guarda el nuevo dato en la estructura del cliente
			    repite=finalizaModificacion();      //pregunta si va a hacer mas cambio o no
                break;

			case 0:
                repite = 0;
				break;
		}
	}while(repite);

    return c;   //retorna la estructura con los datos modificados para que luego sea reemplaza en el archivo por otra funcion
}

/*** Modificacion de datos del cliente en archivo ***/
int modificaConsumoPorEstructura(char archivo[],stConsumos c){
    stConsumos a;
    FILE *pf = fopen(archivo, "r+b");   //abro el archivo en modo lectura y escritura
    int flag=0;

    if(pf){
        while(flag == 0 && fread(&a, sizeof(stConsumos), 1, pf)>0){ // recorro el archivo
            if(a.id==c.id){                             // encuentro el id donde esta el dato a modificar
                a=c;        //coloco los datos de la nueva estructura recibida en la posicion deseada
                flag=1;
            }
            fseek(pf, -1 * sizeof(stConsumos), SEEK_CUR);    //me posiciono una estructura para atras desde donde quedo el cursor de lectura
            fwrite(&a, sizeof(stConsumos), 1, pf);            // escribo la nueva estructura
        }
        fclose(pf);
    }
    return flag;
}

/*** Menu consulta consumos ***/
void menuConsultaConsumos(){
	char repite = 1;
	int opcion = -1;
	int inactivos;
	int activos;
	int anio;
	int searchYear;
	int dia;
	int mes;
	int byDate=-1;

	do {
		system("cls");
        tituloPrincipal();
        printf("\n\t\t\t\t CONSULTA DE CONSUMOS \n\n");
		printf("\t\t\t\t[1]. Ver consumos por a%co. \n",164);
		printf("\t\t\t\t[2]. Ver todos los consumos. \n");
		printf("\t\t\t\t[3]. Ver un consumo por fecha. \n");
		printf("\t\t\t\t[4]. Ver consumos random. \n\n");
		printf("\t\t------------------------------------------------------------------\n");
		printf("\t\t\t\t\t [0].SALIR \n");
		printf("\t\t------------------------------------------------------------------\n");
		printf("\n\t\t Ingrese su opci%cn: [ ]\b\b",162);
        scanf("%d",&opcion);

        switch(opcion){

        case 1:
            system("cls");
            tituloPrincipal();
            printf("\n\t\t\t Ingrese el a%co en que se realizaron consumos: ",164);
            scanf("%d",&anio);
            searchYear=searchByYear(AR_CON,anio);
            if(searchYear==1){
                showByYear(AR_CON,anio);
            }else{
                printf("\n\t\t\t No se encontraron consumos para el a%co ingresado. \n",164);   //en caso de no haber, informa al usuario
                }
            stopProgram();
            break;

        case 2:
            showAllConsumptions(AR_CON);
            stopProgram();
            break;

        case 3:
            system("cls");
            tituloPrincipal();
            printf("\n\t\t  Ingrese la fecha espec%cfica en que se realiz%c el consumo: ",161,162);     //se solicita el nro de cliente para realizar la busqueda en el archivo
            printf("\n\n\t\t\t D%ca de consumo: ",161);
            scanf("%d",&dia);
            printf("\n\t\t\t Mes de consumo: ");
            scanf("%d",&mes);
            printf("\n\t\t\t A%co de consumo: ",164);
            scanf("%d",&anio);
            printf("\n\t\t");
            byDate=searchByDate(AR_CON,anio,mes,dia);
            if(byDate == 1){
                showAllConsumptionsByYear(AR_CON,dia,mes,anio);
            }else{
            printf("\n\t\t\t No se encontraron consumos para esa fecha. \n");
            }
            stopProgram();
            break;

        case 4:
            showAllConsumptions(AR_CON);
            stopProgram();
            break;

        case 0:
            repite = 0;
            break;
        }

	} while(repite);
}

/**** FUNCIONES DE CONSUMOS ***/
/*** Last ID Consumo ***/
int lastIDcharge(char archivo[]){
    stConsumos c;
    int id=0;

    FILE *pf = fopen(archivo, "rb");          // abro en modo lectura

    if(pf){
        fseek(pf, sizeof(stConsumos) * -1, SEEK_END);  //me posiciono -1 registro al final del archivo
        if(fread(&c, sizeof(stConsumos),1,pf) > 0){      //leo el dato de ese registro
            id=c.id;                                      //asigno el ultimo id
        }
      fclose(pf);         //cierro el archivo
    }
    return id;  //retorno el ultimo id encontrado en el archivo
}

/*** Existe consumo ***/
int checkCharge(char archivo[], int idCliente){
    stConsumos c;
    int flag=0;

    FILE *pf = fopen(archivo,"rb");     //abro en modo lectura
    if(pf){
        while(flag==0 && fread(&c, sizeof(stConsumos), 1, pf) > 0){
             if(c.idCliente==idCliente){ // comparo IDs de clientes
                if(c.datosConsumidos > 0){ // si el cliente tiene consumos, muevo la bandera a 1
                    flag=1;
                }
             }
        }
        fclose(pf);
    }
    return flag;    //retorno si el cliente tiene consumos
}

/*** Alta Consumo con validacion (modularizada) ***/
void validateCharge(char archivoConsumos[], char archivoClientes[]){
    stConsumos c;
    stConsumos consumoMismaFecha;
    stCliente cli;
    char ESC;
    char dni[10];
    int busquedaDni;
    int busquedaConsumos;
    int vConsumos;
    stConsumos clientCharges[DIM];
    int mismaFecha;
    int id=lastIDcharge(AR_CON) + 1;
    int fechaCorrecta=-1;
    int dia=0;
    int mes=0;
    int anio=0;
    char opcion= -1;
    int consumoNew;
    int validFecha=-1;
    int sumaConsumos;
    int consumoModificado;

        FILE *pfCliente = fopen(archivoClientes,"rb");
        FILE *pfConsumo = fopen(archivoConsumos, "ab");
        if(pfCliente && pfConsumo){
        system("cls");
       // tituloPrincipal();
        while(ESC != 27){
            tituloPrincipal();
            printf("\n\n\t\t\t Ingrese el DNI del cliente al que se asignar%c el consumo. \n",160);  //pido el dni
            printf("\n\t\t\t DNI...................:");
            fflush(stdin);
            scanf("%s",dni);                                     //guardo en dni el valor del dni ingresado
            busquedaDni=searchByDNI(AR_CLI,dni);                   // realizo validacion del dni y retorno su valor para saber si existe o no
            if(busquedaDni == 1){
                cli=returnByDNI(AR_CLI,dni);    //en caso de que exista lo busco y lo retorno en una estructura cliente
                busquedaConsumos=checkCharge(AR_CON,cli.id); //le paso por parametro el id de ese cliente para saber si tiene consumos
                if(busquedaConsumos==1){
                    printf("\n\t\t------------------------------------------------------------------------------\n");
                        printf("\n\n\t\t\t\t   DATOS DEL NUEVO CONSUMO \n\n");
                        c.id=id;
                        c.idCliente=cli.id;

                        printf("\t\t\t   ID CONSUMO................:%d \n",c.id);
                        printf("\t\t\t   ID CLIENTE................:%d \n",c.idCliente);

                        do{
                        printf("\n\n\t\t\t Ingrese la fecha en que se realiz%c el consumo: \n",162);
                        printf("\n\t\t\t   D%cA................:",214);
                        scanf("%d",&dia);
                        printf("\n\t\t\t   MES.................:");
                        scanf("%d",&mes);
                        printf("\n\t\t\t   A%cO................:",165);
                        scanf("%d",&anio);

                        validFecha=validacionFecha(dia,mes,anio); //valida que la fecha sea correcta
                        }
                        while(validFecha!=1);

                        c.dia=dia;
                        c.mes=mes;
                        c.anio=anio;

                        printf("\t\t\t   DATOS CONSUMIDOS......:");
                        scanf("%d",&c.datosConsumidos);

                        c.baja=0;   //carga como activo el consumo

                        mismaFecha=comparaFechas(AR_CON,dia,mes,anio);

                        if(mismaFecha == 1){
                           consumoMismaFecha=returnByIDandDate(AR_CON,cli.id,dia,mes,anio);
                            c.id--;
                            sumaConsumos=consumoMismaFecha.datosConsumidos + c.datosConsumidos;    //sumo ambos consumos
                            c.datosConsumidos = sumaConsumos;   //lo asigno

                            consumoModificado=modificaConsumoPorEstructura(AR_CON,c);
                                if(consumoModificado == 1){
                                printf("\n\n\t\t\t Se ha cargado el nuevo consumo en la fecha indicada");
                                }else {
                                    printf("\n\n\t\t\t El consumo no pudo ser cargado.");
                                }
                        }else{
                            fwrite(&c,sizeof(stConsumos),1,pfConsumo);
                            printf("\n\n\t\t\t Se ha cargado el nuevo consumo correctamente.");
                        }

                }else{  printf("\n\t\t------------------------------------------------------------------\n");
                        printf("\n\n\t\t\t\t   DATOS DEL NUEVO CONSUMO \n\n");
                        c.id=id;
                        c.idCliente=cli.id;

                        printf("\t\t\t   ID CONSUMO................:%d \n",c.id);
                        printf("\t\t\t   ID CLIENTE................:%d \n",c.idCliente);

                        do{
                        printf("\n\n\t\t Ingrese la fecha en que se realiz%c el consumo: \n",162);
                        printf("\n\t\t\t   D%cA................:",214);
                        scanf("%d",&dia);
                        printf("\n\t\t\t   MES.................:");
                        scanf("%d",&mes);
                        printf("\n\t\t\t   A%cO................:",165);
                        scanf("%d",&anio);

                        validFecha=validacionFecha(dia,mes,anio); //valida que la fecha sea correcta
                        }
                        while(validFecha!=1);
                        c.dia=dia;
                        c.mes=mes;
                        c.anio=anio;

                        printf("\n\t\t\t   DATOS CONSUMIDOS......:");
                        scanf("%d",&c.datosConsumidos);

                        c.baja=0;   //carga como activo el consumo
                        fwrite(&c,sizeof(stConsumos),1,pfConsumo);
                        printf("\n\n\t\t\t Se ha cargado el nuevo consumo correctamente.");

                    }

            }else{
                system("cls");
                tituloPrincipal();
                printf("\n\n\t\t\t\t El dni ingresado NO fue encontrado. \n\n\t\t\t\t No es posible asignar ning%cn consumo. \n",163);
            }

            printf("\n\n\n\n\n\t\t\t\t Presione ESC para salir o cualquier tecla para continuar \n");
            ESC = getch();
            system("cls");
        }
    fclose(pfCliente);
    fclose(pfConsumo);
    }else{
    printf("\n\n\t\t ERROR EN LA APERTURA DE ARCHIVO \n\n");
    }
}

/***Retorna por ID y fecha ***/
stConsumos returnByIDandDate(char archivoConsumos[],int idCliente,int dia, int mes, int anio){
    stConsumos c;
    int flag=0;

    FILE *pf=fopen(archivoConsumos,"rb");
    if(pf){
        while(flag==0 && fread(&c,sizeof(stConsumos),1,pf) > 0){
            if(c.idCliente==idCliente && c.dia==dia && c.mes==mes && c.anio==anio){
                flag==1;
            }
        }
    }
    return c;
}

/*** Baja de consumo ***/
int bajaConsumo(char archivo[], int idConsumo){
    int flag=0;
    stConsumos c;

    FILE *pf = fopen(archivo, "r+b");   //abro el archivo en modo lectura/escritura

    if(pf){
        while(flag==0 && fread(&c, sizeof(stConsumos), 1, pf) > 0){
            if(c.id==idConsumo){
                c.baja=1;   //coloco el estado en baja
                flag = 1;
                fseek(pf, -1 * sizeof(stConsumos), SEEK_CUR);    //me posiciono para atras una posicion desde donde quedo el cursor
                fwrite(&c,sizeof(stConsumos),1, pf);             //grabo la modificacion
                }
            }
        fclose(pf);
    }
    return flag;        //retorna si se puso hacer la baja correctamente.
}

/*** Retorna consumo por ID de consumo ***/
stConsumos returnChargeByID(char archivo[],int idConsumo){
    stConsumos consumo;
    int flag=0;

    FILE *pf = fopen(archivo, "rb");    //abro solo para buscar el consumo
    if(pf){
        while(flag==0 && fread(&consumo, sizeof(stConsumos),1,pf) > 0){
            if(consumo.id == idConsumo){
                flag=1; //salgo porque ya encontre el dato
            }
        }
    fclose(pf);
    }
    return consumo;
}

/*** Validacion por fecha ***/
int validacionFecha(int dia, int mes, int anio){
    char ESC=0;
    int valido=0;

    do{
        if(anio <=2021 && anio >=1950){

        if(mes >=1 && mes <= 12){   //valido que los dias ingresados sean correctos segun la cantidad de dias que tiene cada mes
        switch(mes){
            //meses de 31 dias
            case  1 :
            case  3 :
            case  5 :
            case  7 :
            case  8 :
            case 10 :
            case 12 : if (dia >= 1 && dia <= 31){
                          valido=1;
                            }else{
                          printf("\n\n\t\t\t\t   Debe ingresar un valor de d%ca entre 1 y 31 para el mes asignado",161);
                        }
            break;
            //meses de 30 dias
            case  4 :
            case  6 :
            case  9 :
            case 11 : if(dia >= 1 && dia <= 30){
                        valido=1;
                        }else{
                        printf("\n\n\t\t\t\t   Debe ingresar un valor de d%ca entre 1 y 30 para el mes asignado",161);
                    }
            break;
            //febrero con dias variables segun año biciesto o no
            //Son bisiestos todos los años múltiplos de 4, excepto aquellos que son múltiplos de 100 pero no de 400.
            case  2 : if(anio%4 ==0 && anio%100 != 0 || anio %400 == 0){
                        //si el dia esta entre el 1 y el 29 ingresa a este if
                        if(dia >= 1 && dia <= 29){
                                valido=1;
                                }else{
                                printf("\n\n\t\t\t\t   Debe ingresar un valor de d%ca entre 1 y 29 para el d%ca del año asignado",161,161);
                                }
                        }
                        //si el dia esta entre el 1 y el 28 ingresa a este if
                        else if(dia >= 1 && dia <= 28){
                                valido=1;
                                }else{
                                printf("\n\n\t\t\t\t   Debe ingresar un valor de d%ca entre 1 y 28 para el d%ca del año asignado.",161,161);
                            }
            break;
            } //cierro el switch de validacion de mes y dia y año
        }else{
        printf("\n\t\t\t El mes ingresado es incorrecto. \n");
        }

        }else{
        printf("\n\t\t\t El anio ingresado es incorrecto. \n");
        }
        printf("\n\t\t\t Presione ESC para continuar. \n");
        ESC=getch();
    }while(ESC !=27);
    return valido;
}

/*** Mostrar un consumo ***/
void showCharge(stConsumos c){

    char estado[15];
    getEstadoCliente(c.baja, estado);

    printf("\n\t ID CONSUMO   |   ID CLIENTE   |   A%cO   |   MES   |   DIA   |   CANT. CONSUMIDA   |   ESTADO DEL CONSUMO \n",165);
    printf("\n\t------------------------------------------------------------------------------------------------------------\n");
    printf("\t %6d %15d %14d %8d %10d %16d %20s \n", c.id, c.idCliente, c.anio, c.mes, c.dia, c.datosConsumidos, estado);
    printf("\t------------------------------------------------------------------------------------------------------------\n");

}

/*** Mostrar todos los consumos ***/
void showAllConsumptions(char archivo[]){
    stConsumos c;

    FILE *pf = fopen(archivo,"rb"); //abro en modo lectura

    if(pf){
        while(fread(&c, sizeof(stConsumos), 1 ,pf)> 0 ){
            showCharge(c);
        }
        fclose(pf);
    } else{
        printf("\n ERROR DE APERTURA DE ARCHIVO \n");
    }
}

void showAllConsumptionsByYear(char archivo[],int dia, int mes,int anio){
    stConsumos c;

    FILE *pf = fopen(archivo,"rb"); //abro en modo lectura

    if(pf){
        while(fread(&c, sizeof(stConsumos), 1 ,pf)> 0 && c.dia == dia && c.mes == mes && c.anio ==anio ){
            showCharge(c);
        }
        fclose(pf);
    } else{
        printf("\n ERROR DE APERTURA DE ARCHIVO \n");
    }
}

/*** Mostrar consumos por cliente( se recibe por parametro la estructura del cliente)***/
void showChargesByClient(char archivoConsumos[],stCliente client){
    stConsumos con;

    FILE *pf = fopen(archivoConsumos, "rb");
    if(pf){
        while(fread(&con, sizeof(stConsumos),1,pf) > 0 ){
            if(client.id == con.idCliente){
                showCharge(con);
            }
        }
        fclose(pf);
    }else{
        printf("\n\n\t\t\t ERROR EN LA APERTURA DE ARCHIVO\n\n");
    }
}

///****FUNCIONES DE BUSQUEDA ***/
/*** Buscar consumos por fecha ***/
int searchByDate(char archivo[],int anio, int mes, int dia){
    stConsumos c;
    int flag =0;

    FILE *pArchi = fopen(archivo, "rb");    //solo lectura
    if(pArchi){
        while(flag == 0 && fread(&c,sizeof(stConsumos),1,pArchi)> 0){
            if(c.anio == anio && c.mes == mes && c.dia == dia){
        //        showCharge(c);
                flag=1;     //corto la busqueda si encuentro el dato
            }
        }
        fclose(pArchi);
    }
    return flag;    //retorno si se encontro un consumo con esa fecha ingresada
}

/*** Buscar consumos por año ***/
int searchByYear(char archivo[],int anio){
    stConsumos c;
    int flag=0;

    FILE *pArchi = fopen(archivo, "rb");         //solo lectura
    if(pArchi){
        while(flag ==0 && fread(&c,sizeof(stConsumos),1,pArchi)> 0){
            if(c.anio==anio){
                 flag=1;
            }
        }
        fclose(pArchi);
    }
    return flag;    //retorno si se encontraron consumos de ese año
}

/***Mostrar consumos por año***/
void showByYear(char archivo[],int anio){
    stConsumos c;
    int flag=0;

    FILE *pArchi = fopen(archivo, "rb");         //solo lectura
    if(pArchi){
        while(flag ==0 && fread(&c,sizeof(stConsumos),1,pArchi)> 0){
            if(c.anio==anio){
                 showCharge(c);
            }
        }
        fclose(pArchi);
    }
}

/*** Buscar consumos por mes ***/
int searchByMonth(char archivo[],int mes){
    stConsumos c;
    int flag=0;

    FILE *pArchi = fopen(archivo, "rb");         //solo lectura
    if(pArchi){
        while(flag==0 && fread(&c,sizeof(stConsumos),1,pArchi)> 0){
            if(strcmp(c.mes,mes)==0){
                 flag=1;
            }
        }
        fclose(pArchi);
    }
    return flag;
}

/*** Buscar consumos por dia ***/
int searchByDay(char archivo[],int dia){
    stConsumos c;
    int flag=0;

    FILE *pArchi = fopen(archivo, "rb");         //solo lectura
    if(pArchi){
        while(flag ==0 && fread(&c,sizeof(stConsumos),1,pArchi)> 0){
            if(strcmp(c.dia,dia)==0){
                 flag=1;
            }
        }
        fclose(pArchi);
    }
    return flag;
}

/*** Pasa estructuras de CLIENTES a un arreglo ***/
int fileToClientsArray(char archivo[], stCliente array[],int dim){
    stCliente c;
    int i=0;

    FILE *pf = fopen(archivo, "rb");    //abro en modo lectura
    if(pf){
        while(fread(&c,sizeof(stCliente),1,pf)>0 && i<dim){
            array[i]=c; //paso al arreglo cada estructura del archivo
            i++;
        }
        fclose(pf);
        }
    return i;   //retorno la cantidad de datos que se cargaron para saber los validos
}

/*** Pasa CLIENTES a un arreglo por apellido***/
int fileToArrayByLastname(char archivo[], stCliente array[],int dim,char apellido[]){
    stCliente c;
    int i=0;

    FILE *pf = fopen(archivo, "rb");    //abro en modo lectura
    if(pf){
        while(fread(&c,sizeof(stCliente),1,pf)>0 && i<dim){
            if(strcmp(c.apellido,apellido)==0){
                array[i]=c; //paso al arreglo cada estructura del archivo
                i++;
            }
        }
        fclose(pf);
        }
    return i;   //retorno la cantidad de datos que se cargaron para saber los validos
}

/*** Pasa estructuras de CONSUMOS a un arreglo ***/
int fileToChargesArray(char archivo[], stConsumos array[],int dim){
    stConsumos c;
    int i=0;

    FILE *pf = fopen(archivo, "rb");    //abro en modo lectura
    if(pf){
        while(fread(&c,sizeof(stConsumos),1,pf)>0 && i<dim){
            array[i]=c; //paso al arreglo cada estructura del archivo
            i++;
        }
        fclose(pf);
        }
    return i;   //retorno la cantidad de datos que se cargaron para saber los validos
}

/*** Pasa estructuras de CONSUMOS a un arreglo por ID ***/
int fileToChargesArrayByID(char archivo[], stConsumos array[],int dim, int idCliente){
    stConsumos c;
    int i=0;

    FILE *pf = fopen(archivo, "rb");    //abro en modo lectura
    if(pf){
        while(fread(&c,sizeof(stConsumos),1,pf)>0 && i<dim){
            if(c.idCliente==idCliente){
            array[i]=c; //paso al arreglo cada estructura del archivo
            i++;
            }
        }
        fclose(pf);
        }
    return i;   //retorno la cantidad de datos que se cargaron para saber los validos
}

/*** Compara fechas ***/
int comparaFechas(char archivo[],int dia, int mes, int anio){
    stConsumos c;
    int flag=0;

    FILE *pf = fopen(archivo, "rb");
    if(pf){
            while(flag==0 && fread(&c,sizeof(stConsumos),1,pf) > 0){
                if(c.anio == anio){
                    if(c.mes){
                    if(c.dia){
                    flag=1;
                }
            }
        }
    }
    }
    return flag;
}

///*** FUNCIONES DE MUESTRA DE ARREGLOS ***/
/*** Muestra arreglo de Clientes ***/
void showClientsArray(stCliente c[], int v){
    for(int i=0;i<v;i++){
        showClient(c[i]);
    }
}

/*** Muestra arreglo de Consumos ***/
void showChargesArray(stConsumos c[], int v){
    for(int i=0;i<v;i++){
        showCharge(c[i]);
    }
}

/*** Retorna consumos por fecha***/
stConsumos retornaConsumoEnFecha(stConsumos consumos[], int v,int dia, int mes, int anio){
    int i=0;
    int flag=0;

    while(i<v && flag==0){
        if(consumos[i].anio == anio){   //si coincide el año
            if(consumos[i].mes){            //y coincide el mes
                if(consumos[i].dia){        //y coincide el dia
                    flag=1;
                }
            }
        }
    i++;
    }
    return consumos[i];     //retorno la estructura de ese consumo
}

/*** Cuenta registros del archivo ***/
int cuentaRegistros(char archivo[],int tamanioSt){
    int cantidadRegistros=0;

    FILE *p = fopen(archivo,"rb");
    if(p){
        fseek (p,0,SEEK_END);
        cantidadRegistros =ftell(p) / tamanioSt;
        fclose(p);
    }
    return cantidadRegistros;
}

/*** Asigna consumos random ***/
stConsumos AsignaConsumos(int cantidadClientes){
    stConsumos c;
    int topeMes = returnMonth();
    int topeDia = returnDay();

    c.id = lastIDcharge(AR_CON) + 1;
    c.idCliente = rand()% (cantidadClientes - 1) + 1;
    c.anio = returnYear();
    c.mes = rand()%(topeMes - 1) + 1;
    c.dia = rand()%(topeDia - 1) + 1;
    c.datosConsumidos = rand()%3500;
    c.baja=0;

    return c;    //devuelve la estructura con datos random
}

/*** Carga en archivo consumos random ***/
void cargaConsumosAleatorios(char archivoConsumos[], stConsumos origen){
    stConsumos c=origen;

    FILE *pf = fopen(archivoConsumos, "a+b");
    if(pf){
        fwrite(&c, sizeof(stConsumos),1,pf);
         fclose(pf);
        }
}

/*** Carga Mil consumos random ***/
void cargaMilRandom(){
    stConsumos consumo;
    int registrosCliente;

    registrosCliente=cuentaRegistros(AR_CLI,sizeof(stCliente));
    for(int i=0; i<1000; i++){
        consumo=AsignaConsumos(registrosCliente);
        cargaConsumosAleatorios(AR_CON,consumo);
    }
}

/*** Retorna Dia con localtime ***/
int returnDay(){
    time_t t;
    struct tm *tm;
    char dia[10];
    int day;

    t=time(NULL);
    tm=localtime(&t);
    strftime(dia, 10, "%d",tm);
    day = atoi(dia);

    return day;
}

/*** Retorna Mes con localtime ***/
int returnMonth(){
    time_t t;
    struct tm *tm;
    char mes[10];
    int month;

    t=time(NULL);
    tm=localtime(&t);
    strftime(mes, 10, "%m",tm);
    month = atoi(mes);

    return month;
}

/*** Retorna Año con localtime ***/
int returnYear(){
    time_t t;
    struct tm *tm;
    char anio[10];
    int year;

    t=time(NULL);
    tm=localtime(&t);
    strftime(anio, 10, "%Y",tm);
    year = atoi(anio);

    return year;
}

