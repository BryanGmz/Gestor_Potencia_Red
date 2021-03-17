#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Declarando procedimientos a utilizar
char *leerSalidaComando();
char *split();
void gestionarPotencia(char wlo[], char comando[]);

int main() {
	

	//char macDevice[17];    
	char macDevice[] = "18:01:f1:8c:35:94";
	char interfaceWiFi[] = "wlo1";	
	//char interfaceWiFi[15];

	char *comando = malloc(500);	
	printf("Ingrese la direccion MAC del dispositivo en RED: \n");
	//scanf("%s", macDevice);
	printf("Ingrese la el nombre de la tarjeta de RED: \n");
	//scanf("%s", interfaceWiFi);
	
	strcat(comando, "sudo iw dev ");	
	strcat(comando, interfaceWiFi);
	strcat(comando, " station get ");
	strcat(comando, macDevice);
	strcat(comando, " | grep signal");
	printf("\nComando: %s", comando);
	printf("\nLectura: \n%s", leerSalidaComando(comando));
	
	gestionarPotencia(interfaceWiFi, comando);
	return 0;
}

void gestionarPotencia(char wlo[], char comando[]){
	char *signal = malloc(50);
	int signal_entero;
	char *comando_static = malloc(100);
	strcat(comando_static, "sudo iwconfig ");
	strcat(comando_static, wlo);
	strcat(comando_static, " txpower ");
	printf("\n%s\n", comando_static);
	while(1 == 1){
		//Separar datos	de la potencia del dispositivo
		signal = strtok(leerSalidaComando(comando), "\n");
		signal = split(signal, "-");
		signal = split(signal, " dBm");
		signal_entero = atoi(signal) * -1;	
		printf("Signal dBm: <%d>\n", signal_entero);
		if()		
		sleep(1);
	}
}

int obtenerLatencia(int potencia){
	if(potencia <= 0 && <= -55)
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
