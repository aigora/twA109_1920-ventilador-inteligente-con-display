#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#define MAX_PLAYERS 50
#define CARTAS 4
#define NCARTAS 8
#define MAX_GAMES 25
#define LONGITUD 20
#define MAX_INTENTOS 5


struct Fecha{
	int dia;
	char mes[LONGITUD];
	int anyo;
};

struct typePlayer{
	int id;
	char nombre[LONGITUD];
	char apellido[LONGITUD];
	struct Fecha dob;
	int nGames;
	int puntuacionTotal;
};

struct typeGame{
	int playerID;
	int cartas[CARTAS];
	int disposicion[NCARTAS];
	int puntuacion;

};
int menuprincipal(void);
void showinstrucciones(void);
void elegirCartas(int cartas[]);
int playGame(int game[]);
void setupGame(int game[], int cartas[]);
int rand(void);
void printVector(int v[]);
void showTablero(int faceUp[], int game[]);
struct typePlayer readPlayer (int id);
void showPlayer (struct typePlayer player);
void editPlayer(struct typePlayer *player);
void adminPlayers(struct typePlayer players[], int *nPlayers);
int menuprincipal(void);
void showPlayersList(struct typePlayer players[], int nPlayers);
struct typeGame newGame(int playerId);
void adminGames (struct typeGame gamesList [], int *nGames);
void removeGame(struct typeGame gamesList [], int *nGames);
int initializePlayersList(struct typePlayer playersList[]);
int initializeGamesList(struct typeGame gamesList[], int nPlayers, struct typePlayer playersList[]);
void copyVectorPlayers(struct typePlayer playerList1 [],struct typePlayer playerList2 []);
void ordenarVectorPlayers(struct typePlayer playersList[], int n);




int main(void){

	struct typePlayer players[MAX_PLAYERS];
	int identidad;
	int NPlayers=0;
	int NGames=0;
	int op;
	struct typeGame gamesList[MAX_GAMES];
	
    srand(7);
    NPlayers=initializePlayersList(players);
    NGames=initializeGamesList(gamesList,NPlayers,players);
    
	
	do{
		system("cls");
		printf("********************************\n");
		printf("BIENVENIDO AL JUEGO DE CONCENTRACION.\n");
		printf("********************************\n");
	  
		
		op=menuprincipal();
		switch(op){
			case 1:
				printf("1.Administrar jugadores\n");
				adminPlayers(players,&NPlayers);
				break;
			case 2:
				printf("2.Instrucciones\n");
			
				showinstrucciones();
				break;								
			case 3:
				printf("3.Jugar \n");
				printf("Por favor, introduce tu id: \n");
				scanf("%i",&identidad);
				if((identidad<=NPlayers)&&(identidad>0)){
					gamesList[NGames]=newGame(identidad); 
					NGames++;
					players[identidad-1].nGames++;
					players[identidad-1].puntuacionTotal=players[identidad-1].puntuacionTotal+gamesList[NGames-1].puntuacion;
				}
				break;
			case 0:
				printf("0.Salir \n");
				break;
		}
	}while(op!=0);
			
	

 system("PAUSE");
 return 0;


}

int menuprincipal(void){
    int op;

    printf(" 1. Administrar jugadores \n 2. Instrucciones  \n 3. Jugar \n 0. Salir \n");
    scanf("%i",&op);
	return(op);
}

//-------------------------------------------------------------

int initializePlayersList(struct typePlayer playersList[]){

    char nombres[16][LONGITUD]={"Carmen", "Antonio", "Isabel", "Jose", "Ana", "Manuel", "Pilar", "Francisco", "Dolores", "Juan", "Teresa", "David", "Laura", "Javier", "Cristina", "Jesus"};
    char apellidos[16][LONGITUD]={"Garcia", "Gonzalez", "Fernadez", "Rodriguez", "Lopez", "Martinez", "Sanchez", "Perez", "Gomez", "Martin", "Jimenez", "Ruiz", "Hernandez", "Diaz", "Moreno", "Alvarez"};
    char meses[12][LONGITUD]={"January", "February", "March", "April", "May", "June", "July", "Augst", "September", "October", "November", "December"};
    
    int nPlayers;
    int n=0, n2;
    int i, j;
    
    
    nPlayers=((rand() % (MAX_PLAYERS/10 + 1))+MAX_PLAYERS/5);   
    
    for (i=0; i<nPlayers; i++){
        playersList[i].id=i+1;
        
        n=(rand()%16);
        strcpy(playersList[i].nombre, nombres[n]);
        
        
        n=(rand()%16);
        strcpy(playersList[i].apellido, apellidos[n]);
        
        
        playersList[i].dob.dia=(rand()%28)+1;
        n=(rand()%12);
        strcpy(playersList[i].dob.mes, meses[n]);
        playersList[i].dob.anyo=1960+(rand()%30);  
        
       
        playersList[i].nGames=0;
        playersList[i].puntuacionTotal=0;
        
    }
    return nPlayers;
}


//-----------------------------------------------------------------

int initializeGamesList(struct typeGame gamesList[], int nPlayers, struct typePlayer playersList[]){

    int nGames; 
    int  nintentos=0;
    int i; 
    int j;
    int thisPlayerId; 
    
    
    nGames=(10);

    
    for (i=0; i< nGames; i++){
       
        for (j=0; j<CARTAS; j++){
           gamesList[i].cartas[j]=j+1; 
        }
       
        setupGame(gamesList[i].disposicion, gamesList[i].cartas); 
        
        gamesList[i].playerID=(rand()%nPlayers)+1;
      
        nintentos=(rand()%MAX_INTENTOS+2)+1;
        if (nintentos>5){                                                                    
            nintentos=5;
            gamesList[i].puntuacion=0;
        }else{
           gamesList[i].puntuacion=50-((nintentos-1)*10)  ; 
        }
      
        thisPlayerId =gamesList[i].playerID-1;
        playersList[thisPlayerId].puntuacionTotal=playersList[thisPlayerId].puntuacionTotal+ gamesList[i].puntuacion;
        playersList[thisPlayerId].nGames=playersList[thisPlayerId].nGames+1;
    }
    return nGames;        
}




//APARTADO 1. ADMINISTRAR JUGADORES
//----------------------------------------------------

void adminPlayers(struct typePlayer players[], int *nPlayers){
	
	int op;
	int id;
	struct typePlayer orden[MAX_PLAYERS];
	
	system("cls");
	printf("************************************************** \n");
	printf("	JUEGO DE CONCENTRACION			 \n");
	printf("************************************************** \n");
	
	do{
		printf(" 1. Registrar nuevo jugador. \n 2. Editar informacion de un jugador. \n 3. Ranking actual.  \n 0. Volver al menu\n");
		scanf("%i",&op);
		switch(op){
			case 1:
				if(*nPlayers<MAX_PLAYERS){
					players[*nPlayers]=readPlayer(*nPlayers);
					system("cls");
					*nPlayers=*nPlayers+1;
				}else{
					printf("Maximo de jugadores alcanzado. \n");
				}
				break;
			case 2:
				printf("Introduce el id del jugador que quieres modificar. \n");
				scanf("%i",&id);
				if((id<=*nPlayers)&&(id>0)){
					editPlayer(&players[id-1]);
				}else{
					printf("id no valido. \n");
				}
				break;
			case 3:
				printf("Mostrar ranking de jugadores \n");
				copyVectorPlayers(players,orden);
				ordenarVectorPlayers(orden,*nPlayers);
				showPlayersList(orden,*nPlayers);
				break;
			case 0:
				printf("Volver al menu. \n");
				break;
			default:
				printf("Opcion no valida. \n");
		}
	}while(op!=0);	
return;
}

//-----------------------------------------------------

struct typePlayer readPlayer (int id){
	
	struct typePlayer player;
	
	printf("Por favor introduce tu nombre. \n");
	scanf("%s",player.nombre);
	printf("Por favor introduce tu apellido. \n");
	scanf("%s",player.apellido);
	printf("Por favor introduce con numero el dia que naciste \n");
	scanf("%i",&player.dob.dia);
	printf("Por favor introduce el mes que naciste \n");
	scanf("%s", player.dob.mes);
	printf("Por favor escribe el año que naciste \n");
	scanf("%i",&player.dob.anyo);
	
	player.id=id+1;
	player.nGames=0;
	player.puntuacionTotal=0;
	
	return(player);
}

//-------------------------------------------------------

void editPlayer(struct typePlayer *player){
	
	int continuar;
	int option;
	system("cls");
	printf("************************************************** \n");
	printf("Juego De Memoria: Modificar perfil del jugador. \n");
	printf("************************************************** \n");
	
	showPlayer(*player);
	printf("Quieres modificar algo? (1--SI // 0--NO)\n");
	scanf("%i",&continuar);
	if(continuar==1){
		printf("Introduce lo que quieres modificar. \n");
		printf("1.Nombre \n");
		printf("2.Apellido \n");
		printf("3.Fecha de nacimiento \n");
		scanf("%i",&option);
		switch(option){
			case 1:
				printf("Introduce el nuevo nombre \n");
				scanf("%s",(*player).nombre);
				break;
			case 2:
				printf("Introduce el nuevo apellido \n");
				scanf("%s",(*player).apellido);
				break;
			case 3:
				printf("Introduce el dia de nacimiento \n");
				scanf("%i",&(*player).dob.dia);
				printf("Introduce el mes \n");
				scanf("%s", (*player).dob.mes);
				printf("Introduce el anio \n");
				scanf("%i",&(*player).dob.anyo);
				break;		
		}
		printf("Perfil del jugador ID:%i ha sido modificada. \n",(*player).id);
	}else{
		printf("No se han producido cambios en el perfil. \n");
	}
	return;
}

//-----------------------------------------------------------------
void copyVectorPlayers(struct typePlayer playerList1 [],struct typePlayer playerList2 []){
	int i;
	for(i=0;i<MAX_PLAYERS;i++){
		playerList2[i]=playerList1[i];
	}

	return;
}

//-----------------------------------------------------------------

void ordenarVectorPlayers(struct typePlayer playersList[], int n){
	
	int i,j;
	struct typePlayer aux;	
	
	for (i=1;i<=n-1;i++){
		for(j=0;j<n-i;j++) {
 			if(playersList[j].puntuacionTotal<playersList[j+1].puntuacionTotal){
 				aux=playersList[j];
 				playersList[j]=playersList[j+1];
 				playersList[j+1]=aux;
 			}
 		}		
	}
return;
}

//----------------------------------------------------

void showPlayersList(struct typePlayer players[MAX_PLAYERS], int nPlayers){
   
    int i;
    system("cls"); 
    printf ("*****************************************\n");
    printf ("Memoria: Lista de jugadores\n");
    printf ("*****************************************\n");
    printf ("\n");
    printf ("Numero de jugadores %i\n\n",nPlayers);

    printf ("ID\t    NOMBRE    \t  APELLIDO \t FECHA NACIMIENTO   JUGADAS  PUNTUACION\n");
    for (i=0; i<nPlayers; i++){
        printf ("%i\t %10s\t %10s\t %.2i %10s %i", players[i].id, players[i].nombre, players[i].apellido, players[i].dob.dia, players[i].dob.mes, players[i].dob.anyo);
        printf ("\t%i\t%i\n", players[i].nGames ,players[i].puntuacionTotal);
    }
    printf("\n");
    return; 
}

//----------------------------------------------------

void showPlayer (struct typePlayer player){
	
	printf("ID: %i \n",player.id);
	printf("Nombre: %s \n",player.nombre);
	printf("Apellido: %s \n",player.apellido);
	printf("Fecha de nacimiento: %i / %s / %i \n",player.dob.dia,player.dob.mes,player.dob.anyo);
	printf("Veces jugadas: %i \n",player.nGames);
	printf("Puntuacion total: %i \n",player.puntuacionTotal);
	
	return;
}


//APARTADO 2.INSTRUCCIONES
//---------------------------------------------------------------------------------------------    
 
void showinstrucciones(void){

	system("cls"); 
	printf("********************************\n");
	printf("INSTRUCCIONES DEL JUEGO DE CONCENTRACION.\n");
	printf("********************************\n\n");
	printf("\t*IDENTIFICACION/REGISTRO*\n");
	printf("En primer lugar, para jugar deberas escribir tu id. En caso de no tener, te deberas de registrar en el apartado de administrar jugadores y completar los datos que te pida.\n");
	printf("Si ya estas registrado, solo tendras que irte al apartado 3 donde pone jugar.\n\n");
	printf("\t*DESARROLLO DEL JUEGO* \n");
	printf("Tendras que elegir 4 valores, que seran con los que vayas a jugar. Estos valores deben estar entre el 1 y el 10.\n");
	printf("Cada valor estara repetido, a modo de pareja. Estas parejas se descolocaran de forma aleatoria, y apareceran asteriscos(como si fueran fichas dadas la vuelta)\n");
	printf("El jugador debe de ir descubriendo estos asteriscos eligiendo dos de ellos. Si los numeros descubiertos son iguales, se dejaran descubiertos y no contara como fallo.\n");
	printf("Pero si son valores distintos, se te añadira un fallo y los valores se volveran a convertir en asteriscos.\n\n");
	printf("\t*OBJETIVO DEL JUEGO* \n");
	printf("El objetivo sera encontrar la pareja de todos los valores con el menor numero de fallos posible, para alcanzar la puntuacion mas alta, que quedara registrada en el ranking\n");
	printf("La puntuacion maxima sera 50 si no se ha cometido ningun fallo. Cada fallo te descuenta 10 puntos. Si tienes 5 fallos obtienes 0 puntos y pierdes.\n \n");
	
	menuprincipal();
	
	return;
}

//APARTADO 3.JUGAR
//---------------------------------------------------------

struct typeGame newGame(int playerId){
	
	int intentos , puntos ;
 	int game [NCARTAS] , cartas[CARTAS] ;
 	struct typeGame partida;
 	
 	elegirCartas(partida.cartas);
 	setupGame(partida.disposicion,partida.cartas);
 	intentos=playGame(partida.disposicion);
 	puntos=50-(10*intentos);
 	partida.playerID=playerId;
 	partida.puntuacion=puntos;
 	
 	if(intentos<=5){
 		printf("Puntuacion obtenida: %i\n",puntos);
	 }else{
	 	printf("PERDISTE\n");
	 }
	system("PAUSE");
	return(partida);
	
}

//----------------------------------------------------

void elegirCartas(int cartas[]){

	int i=0,j,valor;

	cartas[i]=0;	
	do{
		printf("Escribe el valor %i a emparejar del 1 al 10: \n",i+1);
		scanf("%i",&valor);
		if((valor>0)&&(valor<11)){
			for(j=0;j<i+1;j++){
				if(valor!=cartas[j]){
					if(j==i){
						cartas[i]=valor;
					}
				}else{
					j=i+1;
					i=i-1;
				}
			}
		}else{
			i=i-1;
		}
		i++;
	}while(i<CARTAS);
	
	return;
}
//-----------------------------------------------------------
int myrand(void){
	int position;
	
	position=rand()%NCARTAS;

	return position;
}

void setupGame(int game[], int cartas[]){
	int i,aux,r1,r2;
	
	for(i=0;i<CARTAS;i++){	
		game[i]=cartas[i];
		game[i+CARTAS]=cartas[i];
	}
	for(i=0;i<NCARTAS;i++){
		printf("%i\t",game[i]);
	}
	//Barajamos 
	printf("\n\n");
	
		r1=myrand();
		r2=myrand();
		aux=game[r1];            
		game[r1]=game[r2];
		game[r2]=aux;
	//printVector(game);     Esta función imprimiría la solución, la hemos usado para comprobar el desarrollo del juego durante la programación.
	
	return;
}

//-----------------------------------------------------------

int playGame(int game[NCARTAS]){
	
	int i,p1,p2;
	int faceUp[NCARTAS]={0,0,0,0,0,0,0,0};
	int intentos=0;
	int aciertos=0;
	
	do{
		printf(" \n Fallos %i: \n",intentos);
		showTablero(faceUp,game);
		printf("Introduzca dos posiciones:\n");
		scanf("%i %i",&p1,&p2);
		if(game[p1]==game[p2]){
			faceUp[p1]=1;
			faceUp[p2]=1;
			aciertos++;
		}else{
			faceUp[p1]=1;
			faceUp[p2]=1;
			showTablero(faceUp,game);
			for(i=0;i<NCARTAS;i++){
				faceUp[i]=0;
			}
			aciertos=0;
			intentos++;
		}
	}while((intentos<5) && (aciertos<4));
	
return(intentos);
}


//------------------------------------------------------

void printVector(int v[]){
	int i;
	for(i=0;i<NCARTAS;i++){
		printf("%i\t",v[i]);
	}
	
 return;
}

//------------------------------------------------------

void showTablero(int faceUp[], int game[]){
	int i;
	
	for (i=0;i<NCARTAS;i++){
		if (faceUp[i]==1)
			printf ("%i\t", game[i]);
		else
			printf("*\t");
	}
	printf("\n");
	return;
}






