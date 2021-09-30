#include <iostream>
#include <vector>

using namespace std;
#define INF 12345
int maxDepth;


//    int tablero[8][8] = {
//   {0, -1, 0, -1, 0, -1, 0, -1},
//   {-1, 0, -1, 0, -1, 0, -1, 0},
//   {0, -1, 0, -1, 0, -1, 0, -1},
//   {0, 0, 0, 0, 0, 0, 0, 0},
//   {0, 0, 0, 0, 0, 0, 0, 0},
//   {1, 0, 1, 0, 1, 0, 1, 0},
//   {0, 1, 0, 1, 0, 1, 0, 1},
//   {1, 0, 1, 0, 1, 0, 1, 0}
// };

int tablero[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, -1, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0}
};



  bool revisarGanador(int jugador){
    bool mov=false;
    for (int i = 0; i < 8; ++i){
      for (int j = 0; j < 8; ++j){
        if(tablero[i][j]==jugador){
          if(tablero[i-1][j-1]==0 && i-1<8 && i-1>=0 && j-1<8 && j-1>=0)
            mov=true;
          if(tablero[i-1][j+1]==0 && i-1<8 && i-1>=0 && j+1<8 && j+1>=0)
            mov=true;
          if(tablero[i-2][j-2]==0 && i-2<8 && i-2>=0 && j-2<8 && j-2>=0)
            mov=true;
          if(tablero[i-2][j+2]==0 && i-2<8 && i-2>=0 && j+2<8 && j+2>=0)
            mov=true; 
        }   
      }
    }
    return mov;
  }



  int tablero1[8][8] = {
  {0, -1, 0, -1, 0, -1, 0, -1},
  {-1, 0, -1, 0, -1, 0, -1, 0},
  {0, -1, 0, -1, 0, -1, 0, -1},
  {0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 1, 0, 1, 0, 0},
  {1, 0, 1, 0, 0, 0, 1, 0},
  {0, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 0}
};

// bool ganar(){
//   for(int i=0;i<8;i++){
//     for(int j=0;j<8;j++){
      
//     }
//   }
// }


void copiar(int t1[8][8],int t2[8][8]) {
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 8; ++j)
      t1[i][j] = t2[i][j];
}

 
struct movimiento{
  movimiento(){}

  movimiento(int t[8][8]){
    copiar(tablerinho,t);
  }
  
  int tablerinho[8][8];

  void print()
  {
      int rr, cc, pp;
      
      printf("  +---+---+---+---+---+---+---+---+\n");
      
      for (rr=0; rr<8; ++rr)
      {
          printf("%d |", rr);
          for (cc=0; cc<8; ++cc)
          { 
              if(tablerinho[rr][cc]==1){
                cout << " # |";
              }
              if(tablerinho[rr][cc]==-1){
                cout << " $ |";
              }
              if(tablerinho[rr][cc]==0){
                cout << "   |";
              }
              
          }
          printf("\n");
          printf("  +---+---+---+---+---+---+---+---+\n");
      }
      
      printf("    0   1   2   3   4   5   6   7\n");
  }

};

vector<movimiento> SaveTablerinho;


 int FuncionUtilidad(int table[8][8]) {
   int ans = 0;

  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 8; ++j)
      ans += -table[i][j];

  return ans;
}
pair< int,  int> bot_movs[2] = {{1, -1}, {1, 1}};
pair< int,  int> jugador_movs[2] = {{-1, -1}, {-1, 1}};


void Resultados() {
   int result = FuncionUtilidad(tablero);

  if (result < 0)
    cout << "El jugador gana!!" <<  endl;
  else if (result == 0)
    cout << "Empate, nadie gana :c" <<  endl;
  else
    cout << "El bot gana!!" <<  endl;
}


struct Nodo {
    int mejor_tablero[8][8];
    int tablero_actual[8][8];
    int depth;

    bool minimize;
    Nodo(int c[8][8],int d){
    depth=d;
    copiar(tablero_actual, c);
    minimize = depth & 1;
    }

   int MinMax() {
    if (depth == maxDepth)
      return FuncionUtilidad(tablero_actual);

    //recursion
    int mejor = minimize ? INF : -INF;
    int jugador = minimize ? 1 : -1;
     pair<  int,   int>* options = minimize ? jugador_movs : bot_movs;

    //visitar nodos hijo
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (tablero_actual[i][j] == jugador) {
          for (int k = 0; k < 2; ++k) {
              int a = i + options[k].first;
              int b = j + options[k].second;

            if (a >= 0 && a < 8 && b >= 0 && b < 8 && tablero_actual[a][b] == 0) {
              // movimiento simple
              tablero_actual[i][j] = 0;
              tablero_actual[a][b] = jugador;
              Nodo child(tablero_actual, depth + 1);
                int score = child.MinMax();

              if (minimize && score < mejor) {
                mejor = score;
                copiar(mejor_tablero, tablero_actual);
              }

              if (!minimize && score > mejor) {
                mejor = score;
                copiar(mejor_tablero, tablero_actual);
              }

              tablero_actual[i][j] = jugador;
              tablero_actual[a][b] = 0;
            }

            a = a + options[k].first;
            b = b + options[k].second;

            if (a >= 0 && a < 8 && b >= 0 && b < 8 && tablero_actual[a][b] == 0 &&
                tablero_actual[a-options[k].first][b-options[k].second] == -jugador) {
              // comer una pieza
              tablero_actual[i][j] = 0;
              tablero_actual[a-options[k].first][b-options[k].second] = 0;
              tablero_actual[a][b] = jugador;
              Nodo child(tablero_actual, depth + 1);
                int score = child.MinMax();

              if (minimize && score < mejor) {
                mejor = score;
                copiar(mejor_tablero, tablero_actual);
              }

              if (!minimize && score > mejor) {
                mejor = score;
                copiar(mejor_tablero, tablero_actual);
              }

              tablero_actual[i][j] = jugador;
              tablero_actual[a-options[k].first][b-options[k].second] = -jugador;
              tablero_actual[a][b] = 0;
            }
          }
        }
      }
    }

    return mejor;
  }

};


void PrintTablero() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j)
       cout << tablero[i][j] << "\t";

     cout <<  endl;
  }
}

void printChevere()
{
    int rr, cc, pp;
    
    printf("  +---+---+---+---+---+---+---+---+\n");
    
    for (rr=0; rr<8; ++rr)
    {
        printf("%d |", rr);
        for (cc=0; cc<8; ++cc)
        { 
            if(tablero[rr][cc]==1){
              cout << " # |";
            }
            if(tablero[rr][cc]==-1){
              cout << " $ |";
            }
            if(tablero[rr][cc]==0){
              cout << "   |";
            }
            
        }
        printf("\n");
        printf("  +---+---+---+---+---+---+---+---+\n");
    }
    
    printf("    0   1   2   3   4   5   6   7\n");
}




int main(){

  bool jugador;
  cout << "Elegir quien empieza el juego 0=computadora 1=jugador: ";
  cin >> jugador;
  cout << endl << "Indicar la profundidad para el algoritmo(entre el 1 al 7): ";
  cin >> maxDepth;

  while(true){
    
    if(jugador){//movimiento jugador
      int x_i, y_i, x_f, y_f;
    
      if(!revisarGanador(1)){break;}

      while(true){
        
        printChevere();
        //PrintTablero();

        cout<<"Ingrese las coordenadas de la posicion inicial: "<<endl;
        cout<<"Fila: ";
        cin>>x_i;
        cout<<"Columna: ";
        cin>>y_i;
        cout << "Ingrese las coordenadas de la posicion final: "<< endl;
        cout<<"Fila: ";
        cin>>x_f;
        cout<<"Columna: ";
        cin>>y_f;

        if(tablero[x_i][y_i]!=1){
          cout << "Movimiento invalido, intente nuevamente";
          continue; 
        }
        if(x_f==x_i-1 && y_f==y_i-1){//diagonal izquierda
          if(tablero[x_f][y_f]==0){
            tablero[x_i][y_i]=0;
            tablero[x_f][y_f]=1;
            movimiento tablerinho(tablero);
            SaveTablerinho.push_back(tablerinho);
            break;
          }
        }
        if(x_f==x_i-1 && y_f==y_i+1){//diagonal derecha
          if(tablero[x_f][y_f]==0){
            tablero[x_i][y_i]=0;
            tablero[x_f][y_f]=1;
            movimiento tablerinho(tablero);
            SaveTablerinho.push_back(tablerinho);
            break;
          }
          
        }
        if(x_f==x_i-2 && y_f==y_i-2){//comer una ficha izquierda
          if(tablero[x_f][y_f]==0 && tablero[x_i-1][y_i-1]==-1){
            tablero[x_i][y_i]=0;
            tablero[x_f][y_f]=1;
            tablero[x_i-1][y_i-1]=0;
            movimiento tablerinho(tablero);
            SaveTablerinho.push_back(tablerinho);
            break;

          }
        }
        if(x_f==x_i-2 && y_f==y_i+2){//comer una ficha derecha
           if(tablero[x_f][y_f]==0 && tablero[x_i-1][y_i+1]==-1){
            tablero[x_i][y_i]=0;
            tablero[x_f][y_f]=1;
            tablero[x_i-1][y_i+1]=0;
            movimiento tablerinho(tablero);
            SaveTablerinho.push_back(tablerinho);
            break;
          }
        }

      }
    }//acaba el if
    else{ //movimiento de bot
        
        Nodo root(tablero, 0);
          int result;

        result = root.MinMax();

        if (result == -INF) {
          break;
        }
        
        copiar(tablero, root.mejor_tablero);
        printChevere();
        movimiento tablerinho(tablero);
        SaveTablerinho.push_back(tablerinho);
    }//acaba el else
        

    jugador = (!jugador);
  } //fin del while

  Resultados();

}