#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_board(char board[15][15]){ //funcion que imprime el tablero
	for(int i = 0; i < 15; i++){
	    for(int j = 0; j < 15; j++) printf("%c ", board[i][j]);
	    printf("\n");
	}
}

int main(void){
	srand(time(NULL)); //para que los random sean VERDADERAMENTE random
	char board[15][15]; //declaramos el tablero
	for(int i = 0; i < 15; i++){ //y lo llenamos de X
	    for(int j = 0; j < 15; j++) board[i][j] = 'X';
	}
	int count = 0; //cuando count vale 0 o 1, se carga O; cuando vale 2 o 3, se carga C
	//Es para no usar otro while
	while(count != 4){ //cuando se cargaron las cuatro casillas especiales, rompe
		int r = rand()%15; //los subindices random
	    int s = rand()%15;
	    if(board[r][s] == 'X'){ //esto verifica que no se superpongan O o C
	    	if(count < 2) board[r][s] = 'O'; //lo explicado anteriormente del count
	    	else board[r][s] = 'C';
		    count++; //count++ dentro del if para verificar que se cargue correctamente el pozo
		}
	}
	
	int c = 1; //contador de turnos
	int especiales[4] = {0, 0, 0, 0}; //array que guarda la cantidad de veces que cada jugador cayo en casillas especiales
	//especiales[0] = cant. veces que Tortuga cae en pozo (muertes)
	//especiales[1] = cant. veces que Tortuga cae en comodin
	//especiales[2] = cant. veces que Liebre cae en pozo (muertes)
	//especiales[3] = cant. veces que Liebre cae en comodin
	int t1 = 0; //subindice1 de la posicion de la tortuga
	int t2 = 0; //sub2 tortuga
	int l1 = 0; //sub1 liebre
	int l2 = 0; //sub2 liebre
	while(1){ //cada repeticion es una ronda
		int dado = (rand() % 6) + 1; //un random que indica cuantas casillas avanza el jugador
		board[t1][t2] = 'T'; //asignamos la posicion de la tortuga a la matriz board, para imprimirla
		board[l1][l2] = 'L'; //idem para la liebre
		print_board(board); //imprimimos el tablero con las posiciones de los jugadores
		printf("Muertes liebre = %d\n", especiales[2]);
		printf("Muertes tortuga = %d\n", especiales[0]);
		printf("Turno = %d\n", c);
		printf("\n[X]Turno de la %s![X]\n", c % 2 == 0 ? "liebre" : "tortuga"); 
		printf("Ingresa un numero cualquiera para tirar el dado: ");
		int x = 0;
		scanf("%d", &x); //esto es para que el jugador "tire" los dados
		//si lo comentamos el juego se vuelve automatico
		system("cls"); //limpiamos la terminal
		board[t1][t2] = 'X'; //volvemos a asignar X a las posiciones de ambos jugadores
		board[l1][l2] = 'X';
		//recordar que sus posiciones estan guardadas en t1 y t2; l1 y l2
		if(especiales[0] == 3 || especiales[2] == 3){ //si alguno de los dos murio tres veces
			printf("La %s cayo tres veces en el pozo y perdio", especiales[0] == 3 ? "Tortuga" : "Liebre");
			return 0;
		}
		if(t2 >= 15 || (t1 == 14 && t2 == 14)){ //si gano la tortuga
		//que t2 > 15 significa que se paso de la meta
		//que t1 == 14 y t2 == 14 significa que esta parada exactamente en la salida
			printf("Gano la tortuga!!!\n");
			printf("Cantidad de tiros que tardo: %d\n", c/2);
			printf("Cantidad de muertes: %d\n", especiales[0]);
			printf("Atravesaste %d COMODINES y %d POZOS", especiales[1], especiales[0]);
			return 0;
		}
		if(l2 >= 15 || (l1 == 14 && l2 == 14)){ //idem para la liebre
			printf("Gano la liebre!!!\n");
			printf("Cantidad de tiros que tardo: %d\n", c/2+1);
			printf("Cantidad de muertes: %d\n", especiales[2]);
			printf("Atravesaste %d COMODINES y %d POZOS", especiales[3], especiales[2]);
			return 0;
		}
		
		if(c % 2 == 0){ //si es el turno de la liebre
			if(l1+dado*2 >= 15){ //si se pasa de columna (l1 >= 15), cambia de columna
				l1 = l1+dado*2-15;
				l2++;
			} else l1 = l1+dado*2; //sino sigue recorriendo su columna
			
			if(board[l1][l2] == 'O'){ //si cae en un pozo se reinicia su posicion
				l1 = 0;
	            l2 = 0;
	            especiales[2]++; //se guarda la caida en el pozo
			}
			if(board[l1][l2] == 'C'){ //si cae en un comodin, se repite la logica del primer if
				if(l1+dado*2 >= 15){
				l1 = l1+dado*2-15;
				l2++;
			    } else l1 = l1+dado*2;
			    especiales[3]++; //se guarda la caida en el comodin
			}
		} else { //turno de la tortuga; todo igual a lo explicado antes
			if(t1+dado >= 15){
				t1 = t1+dado-15;
				t2++;
			} else t1 = t1+dado;
			
			if(board[t1][t2] == 'O'){
				t1 = 0;
	            t2 = 0;
	            especiales[0]++;
			}
			if(board[t1][t2] == 'C'){
				if(t1+dado >= 15){
				t1 = t1+dado-15;
				t2++;
			    } else t1 = t1+dado;
			    especiales[1]++;
			}
		}
		c++; //sumamos 1 a c para pasar a la siguiente ronda
	}
}
