#include <iostream> //input generico
#include <fstream>  //input CSV
#include <sstream>  //conversione sstring
#include <vector>   //memorizzazione CSV
#include <queue>    //priorità per Kruskal
#include <string>   //stringhe
#include <math.h>   //distanza euclidea
#include <cstdlib>

#include "Edge.h"
#include "Kruskal.h"

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

//NB nel file sono state eliminate le chiamate di sistema
// system("PAUSE") in quanto funzionanti solamente per il sistema windows
using namespace std;

float distance(vector<double> *v1,vector<double>* v2){
      float distance=0.0;
      for(int i=0;i<v1->size();i++){
              distance+=pow( ( v1->at(i) - v2->at(i) ) ,2);
    }
      return sqrt(distance);
}
// IT WORKS!

int StoreCSV(char* filename,vector< vector<double> > &collezione,vector<Vertex*> &vertices)
{
	ifstream file;
    stringstream ss;  //per il cast a x
	string riga;
	Vertex* vertice;

	file.open(filename);

	if (!file) {
		cout << "Impossibile aprire il file.";
		cout << "Abbiamo gia mandato una squadra di scimmie ";
		cout << "altamente addestrata per risolvere il problema" << endl;
		return EXIT_FAILURE;
	}
	
	//Scarto la prima riga "Parametri" prendendola e quindi 
	//facendo passare il cursore del file alla riga 2
	getline(file,riga);
        int id=-1;//gli id del vertice (parte da 0 con ++id)
	while(getline(file,riga)) { // !file.eof()
		int i=0;
		while(riga[i]!=',') //Scarta l'ID
			i++;
		vector<double> temp;
		string s = " ";
		for(i+=1; i < riga.size(); i++) {
               s= s + riga[i];
			if((riga[i] == ',') || ( i == riga.size() -1)) {
                ss.str(s);
				double x=0.0;
                ss >> x; //Trasformo la stringa in double
				temp.push_back(x);
				s.clear();
				ss.clear();
			}		
		}
		vertice=new Vertex(++id);
		vertices.push_back(vertice);
		collezione.push_back(temp);
	}

	file.close();

	return EXIT_SUCCESS;
}
// IT WORKS!

int main(int argc, char *argv[]) {
    
    if( argc!=2 && argc != 3 ) {  //controllo che l'input sia giusto 
        cout << "Error: missing parameter name";//che ci sia il parametro
		cout<<"/wrong parameter usage"<< endl; //o che sia corretto
        return EXIT_FAILURE;
    }
    
    vector< vector<double> > vettore; //contenitore dei dati letti da CSV
	priority_queue< Edge , vector<Edge> , greater<Edge> > priorita;  //coda prioritaria pegli archi
	vector<Vertex*> vert_vect;

    cout.precision(4);// imposto per mera bellezza
    
	if(StoreCSV(argv[1],vettore,vert_vect)) // EXIT_SUCCESS è definito a 0
       return EXIT_FAILURE;       // quindi se sbaglio la lettura esco

	Edge arco;
	for(int i=0;i<vettore.size();++i){    //Priority queue
            for(int k=i+1;k<vettore.size();++k){ 
				arco.createV1(vert_vect[i]);
				arco.createV2(vert_vect[k]);
				arco.setW( distance(&vettore[i],&vettore[k]) );
				priorita.push(arco);
            }
    }//tutto dinamico. oiea.
    
	cout<<endl;

	Kruskal MinSpTree;  // classe di utilità che contiene l'MST e il metodo kruskal
	
	int c=0;
	if(argv[2])//controllo di avere il parametro
		c=atoi(argv[2]);
	if (c<1||c>vettore.size())//controllo che sia giusto
		c=-1;//significa ignora il clustering
	//controllo sul dato in input

	MinSpTree.kruskalBuild(priorita,vert_vect,c);//c=-1 significa ignora la parte di clustering
	
    MinSpTree.printresult(c);
	
	

    return EXIT_SUCCESS;
}
