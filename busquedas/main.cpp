#include <iostream>
#include <list>
#include <stack>
#include <algorithm>
#include <vector>
#include <ctime>
#include <math.h>

using namespace std;


struct Point{
  int x, y;
  Point(int _x, int _y):x(_x),y(_y){}
  Point(){x=y=0;}
};

Point inicio(0,0);
Point fin(3,3);


template <class N, class E>
struct Node
{
    int id = 0;
    E x = 0;
    E y = 0;
    N distanceToObjective = 0;
    list<Node<N, E>*> edges; 

    Node(E x1, E y1, E _id, N _distance)
    {
        x = x1;
        y = y1;
        id = _id;
        distanceToObjective = _distance;
    }
    Node(E x1, E y1)
    {
        x = x1;
        y = y1;
        id = 0;
        distanceToObjective = 0;
    }
};

template <class N, class E>
struct Graph
{
    list<Node<N, E>*> nodes;
   
    bool insertNode(Node<N, E>* newNode)
    {
        nodes.push_back(newNode);
        return 1;
    }

    bool exist(E _x, E _y, Node<float, int>**& p)
    {
        for (list<Node<float, int>*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
        {
            if ((*it)->x == _x && (*it)->y == _y)
            {
                p = &(*it);
                return true;
            }
        }
        return false;
    }

    bool insertEdge(Node<N, E>* a, Node<N, E>* b, E value, bool distance)
    {
        return 1;
    }

    bool removeEdge(Node<N, E>* a, Node<N, E>* b, E value)
    {
        return 1;
    }

    bool removeNode(Node<N, E>* a)
    {
        return 1;
    }


  typedef vector<Node<float, int>*> ruta;
  typedef pair<Node<float, int>*,ruta> nodo;
  
  void dfs(){
    
    cout << endl;
    cout << "BUSQUEDA EN PROFUDIDAD " << endl;
    cout << endl;
    cout << "Ruta: " << endl<<endl;
    ruta r;
    Node<float, int>* temp;//nodo inicio;
    for(typename::list<Node<N, E>*>::iterator it = nodes.begin(); it != nodes.end(); ++it){
      if((*it)->x==inicio.x && (*it)->y==inicio.y){
        temp=(*it);
        break;
      }
    }
    
    nodo n(temp,r);
    stack<nodo> _stack;
    _stack.push(n);

    while(!_stack.empty()){
      nodo aux;
      aux=_stack.top();
      _stack.pop();

      if(aux.first->x==fin.x && aux.first->y==fin.y){
          for(auto i:aux.second){
           cout<<"(" << i->x << "," << i->y << ") -> ";
          }
        // for(int i=0; i<aux.second.size(); i++){
        //   cout << aux.second[i]->x << "," << aux.second[i]->y << "|";
        // }
        return;
      }
      
      for(typename::list<Node<N, E>*>::iterator ar=aux.first->edges.begin();ar!=aux.first->edges.end();++ar){
        bool encontrado=false;

        for(auto j:aux.second){
          if((*ar)==j){
             encontrado=true;
             break;
          }
        }
        // for(int i=0; i<aux.second.size(); i++){
        //   if((*ar)==aux.second[i]){
        //     encontrado=true;
        //     break;
        //   }
        // }

        if(!encontrado){
          nodo n2;
          n2.second=aux.second;//ruta actual
          n2.second.push_back(aux.first);//agregar nodo actual a la ruta
          n2.first=(*ar);//agregar el nuevo nodo
          _stack.push(n2);
        }
      }
    }
    
  }

  float distancia(int x1, int y1, int x2, int y2)
  {
    return sqrt(pow(x2 - x1, 2) +  pow(y2 - y1, 2) * 1.0);
  }
  
  void elMejorElPrimero(){
    
    cout << endl;
    cout<<"ALGORITMO EL MEJOR EL PRIMERO "<<endl;
    cout << endl;
    cout << "Ruta: " << endl<<endl;
    ruta r;
    Node<float, int>* temp;//nodo inicio;
    for(typename::list<Node<N, E>*>::iterator it = nodes.begin(); it != nodes.end(); ++it){
      if((*it)->x==inicio.x && (*it)->y==inicio.y){
        temp=(*it);
        break;
      }
    }
    
    nodo n(temp,r);
    stack<nodo> _stack;
    _stack.push(n);

    while(!_stack.empty()){
      nodo aux;
      aux=_stack.top();
      _stack.pop();

      if(aux.first->x==fin.x && aux.first->y==fin.y){
          for(auto i:aux.second){
            cout<<"(" << i->x << "," << i->y << ") -> ";
          }
        return;
      }

      vector<pair<float, nodo>> distancias;
      
      for(typename::list<Node<N, E>*>::iterator ar=aux.first->edges.begin();ar!=aux.first->edges.end();++ar){
        bool encontrado=false;

        for(auto j:aux.second){//recorre los nodos en ruta
          if((*ar)==j){
             encontrado=true;
             break;
          }
        }

        if(!encontrado){
          pair<float, nodo> x;
          x.first=distancia((*ar)->x,(*ar)->y,fin.x,fin.y);
         // cout << x.first << endl;
        
          nodo n2;
          n2.second=aux.second;
          n2.second.push_back(aux.first);//agregar nodo actual a la ruta
          n2.first=(*ar);

          x.second=n2;
          distancias.push_back(x);
        }
      }

      sort(distancias.begin(), distancias.end());
      reverse(distancias.begin(), distancias.end());

      for(int i=0; i<distancias.size(); i++){
        _stack.push(distancias[i].second);
      }
    }
  }

  
};



int main(){

  Graph<float,int> grafito;

  int columnas, filas;
  cout << "Ingresar filas: ";
  cin >> filas;
  cout << endl << "Ingresar columnas: ";
  cin >> columnas;

  for(int i=0; i<filas; i++){
    for(int j=0; j<columnas; j++){
        Node<float, int>* tmp = new Node<float, int>(i,j);
			  grafito.insertNode(tmp);
		}
  }


  for (list<Node<float, int>*>::iterator it = grafito.nodes.begin(); it != grafito.nodes.end(); ++it)
	{
		Node<float, int>** p;
		/*
		A B C
		D X E
		F G H
		*/
		if (grafito.exist(((*it)->x) - 1, ((*it)->y) - 1, p))
			(*it)->edges.push_back(*p); // A
		if (grafito.exist(((*it)->x) - 1, ((*it)->y), p))
			(*it)->edges.push_back(*p); // B
		if (grafito.exist(((*it)->x) - 1, ((*it)->y) + 1, p))
			(*it)->edges.push_back(*p); // C
		if (grafito.exist(((*it)->x), ((*it)->y) - 1, p))
			(*it)->edges.push_back(*p); // D
		if (grafito.exist(((*it)->x), ((*it)->y) + 1, p))
			(*it)->edges.push_back(*p); // E
		if (grafito.exist(((*it)->x) + 1, ((*it)->y) - 1, p))
			(*it)->edges.push_back(*p); // F
		if (grafito.exist(((*it)->x) + 1, ((*it)->y), p))
			(*it)->edges.push_back(*p); // G
		if (grafito.exist(((*it)->x) + 1, ((*it)->y) + 1, p))
			(*it)->edges.push_back(*p); // H
	}
  cout << endl;
  int x;
  cout<<"Ingresar el numero de nodos que desea borrar: ";
  cin>>x;//Pedir al usuario cuantos nodos desea borrar aleatoriamente 
  
  srand((unsigned) time(0));
  vector<Point> borrar;
  for(int k=0; k<x; k++){
    int v1=rand() % filas;
    int v2=rand() % columnas;
    //  int v1=3;
    //  int v2=2;
    if(v1!=inicio.x || v2!=inicio.y){
      if(v1!=fin.x || v2!=fin.y){
        borrar.push_back(Point(v1,v2)); 
      } 
    }
      
  }
  
    cout<<endl;
    cout << "ELIMINANDO LOS NODOS: " << endl << endl;
    for (list<Node<float, int>*>::iterator it = grafito.nodes.begin(); it != grafito.nodes.end(); ++it) {
        for (int i = 0; i < borrar.size(); i++) {
            if ((*it)->x == borrar[i].x && (*it)->y == borrar[i].y) {
                
                cout<<"(" << (*it)->x << "," << (*it)->y<<")" <<" ";

                for (list<Node<float, int>*>::iterator et = (*it)->edges.begin(); et != (*it)->edges.end(); ++et) {                   
                    for (list<Node<float, int>*>::iterator at = (*et)->edges.begin(); at != (*et)->edges.end(); ++at) {
                        if ((*at)->x == borrar[i].x && (*at)->y == borrar[i].y) {
                            (*et)->edges.erase(at);
                            break;
                        }
                    }
                }
                grafito.nodes.erase(it--);
            }
        }
    }

  
  // for(list<Node<float, int>*>::iterator it = grafito.nodes.begin();it!=grafito.nodes.end();++it){
  //  cout<<(*it)->x<<","<<(*it)->y<<endl;
  // }

  cout<<endl;
  cout<<"----------------------------------------------------------"<<endl;
  grafito.dfs();
  cout<<endl;
  cout<<"----------------------------------------------------------"<<endl;
  grafito.elMejorElPrimero();
  cout<<endl;
  cout<<"----------------------------------------------------------"<<endl;
  return 0;
}