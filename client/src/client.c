#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	
	int conexion;
	char* ip;
	char* puerto;
	char* valor;
	
	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
	

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
	log_info(logger,"Hola! Soy un log");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value (config,"PUERTO");
	valor = config_get_string_value(config,"CLAVE");
	
	// Loggeamos el valor de config
	log_info(logger, "VALOR leido de la config: %s", valor);
	
	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él
	
	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);
	if (conexion == -1) {
		log_error(logger, "Nohttps://prod.liveshare.vsengsaas.visualstudio.com/join?B0FB2F7EF32CE20981D34C408ABFAFC6618B se pudo establecer conexión con el servidor");
		terminar_programa(conexion, logger, config);
		return EXIT_FAILURE;
	}
	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor,conexion);
	
	// Armamos y enviamos el paquete
	paquete(conexion);
	
	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("tp0.log","process_name",true,LOG_LEVEL_INFO);


	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config = config_create("cliente.config");

	if(nuevo_config==NULL)
      {
        exit(EXIT_FAILURE);
      }

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
    log_info(logger, ">> %s", leido);     // %s representa una cadena de caracteres y >> es para que salga literal >>

    // El resto, las vamos leyendo y logueando hasta recibir un string vacío

    while(strcmp(leido, "") !=0)
    {
        free(leido);
        leido = readline("> ");
        log_info(logger, ">> %s", leido);
    }

    // ¡No te olvides de liberar las lineas antes de regresar!
    free(leido);

    if(strcmp(leido, "") ==0){
        exit(EXIT_FAILURE);
    }
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete


	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */

	  liberar_conexion(conexion);
	  log_destroy(logger);
	  config_destroy(config);

}
