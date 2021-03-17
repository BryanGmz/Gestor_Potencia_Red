#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Declarando procedimientos a utilizar
char *leerSalidaComando();
char *split();
int obtenerLatencia(int potencia);
void gestionarPotencia(char wlo[], char comando[]);

int main() {
	//char macDevice[] = "18:01:f1:8c:55:94";
	//char interfaceWiFi[] = "wlo1";	
	char macDevice[17];
	char interfaceWiFi[15];
	char *comando = malloc(500);	
	printf("Ingrese la direccion MAC del dispositivo conectado a la red: \n");
	scanf("%s", macDevice);
	printf("Ingrese la el nombre de la tarjeta wireles: \n");
	scanf("%s", interfaceWiFi);
	
	strcat(comando, "sudo iw dev ");	
	strcat(comando, interfaceWiFi);
	strcat(comando, " station get ");
	strcat(comando, macDevice);
	strcat(comando, " | grep signal");
	gestionarPotencia(interfaceWiFi, comando);
	return 0;
}

void gestionarPotencia(char wlo[], char comando[]){
	char *signal = malloc(60);
	char comparar[] = "\n";
	char *comando_static = malloc(100);
	int signal_entero;
	int ret;
	strcat(comando_static, "sudo iwconfig ");
	strcat(comando_static, wlo);
	strcat(comando_static, " txpower ");
	printf("\n\n----------------------Inicia la regulacion de Potencia----------------\n\n");
	while(1 == 1){
		char *snum = malloc(3);
		char comando_execute[50];
		for(int i = 0; i < 50; i++) {
			comando_execute[i] == ' ';
		}		
		//Separar datos	de la potencia del dispositivo
		signal = strtok(leerSalidaComando(comando), "\n");
		signal = split(signal, "-");
		signal = split(signal, " dBm");		
		signal_entero = atoi(signal);	
		if(signal_entero == 0){
			printf("Error, en los datos ingresados, vuelve a ejecutar el programa!!!\n");
			exit(1);		
		}
		printf("\nSignal dBm: <-%d>", signal_entero);	
		strcat(comando_execute, comando_static);	
		sprintf(snum, "%d", obtenerLatencia(signal_entero));		
		strcat(comando_execute, snum);
		system(comando_execute);
		*comando_execute = NULL;
		snum = NULL;
		system("sudo iwconfig");
		sleep(2);
	}
}

int obtenerLatencia(int potencia){
	if(potencia >= 0 && potencia < 50) {
		return 0;	
	} else if (potencia >= 50 && potencia < 60) {
		return (potencia/2.5 - 20); 	
	} else if (potencia >= 60 && potencia < 69) {
		return potencia - 48;	
	} else {	
		return 22; 
	}
}

char *split(char cadena[], char delimitador[]){
	char *regresar;
	char *token = strtok(cadena, delimitador);
	if(token != NULL){
		while(token != NULL){
			// Sólo en la primera pasamos la cadena; en las siguientes pasamos NULL
			regresar = token;
			token = strtok(NULL, delimitador);
		} 
	}
	return regresar;
}

char *leerSalidaComando(char comando[]){
	char *texto = malloc(2000);
	FILE *fp;
	char path[1035];
	fp = popen(comando, "r");
	if (fp == NULL){
		printf("Failed to run comand\n");
		exit(1);	
	}
	while (fgets(path, sizeof(path), fp) != NULL) {
		strcat(texto, path);	
	}
	pclose(fp);
	return texto;
}
