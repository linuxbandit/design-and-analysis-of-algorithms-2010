/**
        La classe Vertex.h è molto semplice: contiene
		  -puntatore a nodo rappresentante (NULL se è se stesso)
		  -puntatore a uno dei nodi rappresentati
		  -id del vertice

*/


#ifndef NULL
#define NULL 0
#endif

using namespace std;

class Vertex{
      public:

      Vertex* Rappresentante; //CONNECTED_TO         // Pointer in Tree to Next Vertex
      Vertex* Next; // Pointer in list of represented by me
      unsigned int ID;  // Number of the Vertex [0..n-1]

      Vertex()              // Default Constructor
      {
        Rappresentante = NULL;
		Next = NULL;
        ID = 0;
      }

	  Vertex(int id)              // ID Constructor
      {
        Rappresentante = NULL;
		Next = NULL;
        ID = id;
      }


	  int getID(){ return ID; }
	  void setID(int a){ ID = a; }



    };
