//programa en C para consultar los datos de la base de datos
//#include <my_global.h>
#include <mysql.h>
#include <string.h>

int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char consulta [200];
	conn = mysql_init(NULL);
	if (conn==NULL)
	{
		printf ("Error al crear la conexión: %u %s\n",
		mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "Ejindividual",0, NULL, 0);
	if (conn==NULL)
	{
		printf ("Error al inicializar la conexión: %u %s\n",
		mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	printf("Consulta de la maxima puntuacion:\n");
	
	sprintf (consulta, "SELECT DISTINCT JUGADORES.USUARIO, RANKING.PUNTUACION_MAXIMA FROM (PARTIDA, JUGADORES, RANKING) WHERE JUGADORES.ID = RANKING.ID_U");
	err=mysql_query (conn, consulta);
	if (err!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
	exit (1);
	}
/*
. . .
*/
	//recogemos el resultado de la consulta
	resultado = mysql_store_result (conn);
	// El resultado es una estructura matricial en la que cada
	// fila contiene los datos de una socio y sucesivos
	// columnas contienen cada uno de los datos del socio
	// recorremos una a una cada fila del resultado
	// ahora obtenemos la siguiente fila
	row = mysql_fetch_row (resultado);
	
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
	{
		int usuario = 0;
		int ganador= 0;
		int puntuacion1 = 0;
		int puntuacion2 = 0;
		while (row !=NULL)
		{
			
			printf ("Usuario: %s Puntuacion: %s\n", row[0], row[1]);
				usuario= row[0];
				puntuacion1= row[1];
				if (puntuacion1>puntuacion2){
					puntuacion2=puntuacion1;
					ganador=usuario;
				}
				
				
			
			row = mysql_fetch_row (resultado);
		}
		printf("Persona con mas puntos es: %s Con estos puntos: %s\n", ganador, puntuacion2);
	}
	// cerrar la conexión con el servidor MYSQL
	mysql_close (conn);
}
