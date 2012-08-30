/**
     La classe Edge.h amministra gli archi
	 Le 3 variabili sono rispettivamente
	     -i 2 vertici che l'arco unisce (puntatori ai vertici)
		 -il peso dell'arco
	 I membri interni sono gli overloading degli operatori di confronto
*/
#ifndef NULL
#define NULL 0
#endif

#include "Vertex.h"

using namespace std;


class Edge{
      public:

      Vertex* v1;
	  Vertex* v2;        // Vertices
      float w;             // Weight


	  Edge(){ v1=v2=NULL; w=0;}
	  //  Get/Set 
	  void createV1(Vertex* v){v1 = v;}
      void createV2(Vertex* v){v2 = v;}
	  void setV1(int a){v1->setID(a);}
      void setV2(int a){v2->setID(a);}
      void setW(float a){w=a;}
	  Vertex* getV1(){return v1;}
      Vertex* getV2(){return v2;}
	  int getV1ID(){return v1->getID();}
      int getV2ID(){return v2->getID();}
      float getW(){return w;}


      // Overloading operatori
      bool operator< (const Edge& b) const
      { return w < b.w;  }

      bool operator<= (const Edge& b) const
      { return w <= b.w; }

	  bool operator> (const Edge& b) const
      { return w > b.w;  }

      bool operator>= (const Edge& b) const
      { return w >= b.w; }

      bool operator== (const Edge& b) const
      { return w == b.w; }
    };
