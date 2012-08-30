#ifndef NULL
#define NULL 0
#endif

using namespace std;

class Kruskal{

      public:

	  vector<Edge> MST;
	  vector<pair<int,int> > Cluster; // mi sembra meglio di una mappa!

	  Kruskal(){ }        // Default Constructor


	  void kruskalBuild(priority_queue< Edge , vector<Edge> , greater<Edge> > priorita,
						  vector <Vertex*> &v,
						  unsigned int numclust){

		 unsigned int counter=0;

		 Edge arco;
		 while(priorita.size()>0){

			arco=priorita.top();
			priorita.pop();
		
		
			if(findset( arco.getV1() ) 	!= 	findset( arco.getV2() ) ){//solito alg di Kruskal,non so che commentare
				MST.push_back(arco);
				unione(arco.getV1(),arco.getV2());
				counter++;
				if((numclust > 0) && counter==(v.size()-numclust))
					Clustering(v);
			}

		}
	  
	  }


	 int findset(Vertex* v){//solito findset,non so come commentare
          if(v->Rappresentante!=NULL)//vedo se ho un rappresentante
              return (v->Rappresentante)->getID();
		  else return v->getID();//senno sono io il mio rappresentante
	 }

	 int unione(Vertex* v1, Vertex* v2){
		
		Vertex* capo; //Il puntatore al vertice che sarà il superrappresentante
		Vertex* nuovo;//Il puntatore al vertice che rappresenta l'insieme che verrà unito
					  //ossia il puntatore al vertice che cambierà rappresentante(da se stesso a capo)
		 
		if(v1->Rappresentante!=NULL) //Mi assicuro che A sia il rappresentante di un insieme
			capo=v1->Rappresentante;
		else capo=v1;

		if(v2->Rappresentante!=NULL) //Mi assicuro che B sia il rappresentante di un insieme
			nuovo=v2->Rappresentante;
		else nuovo=v2;

		Vertex* poi=nuovo;//Vertex* poi=nuovo; //puntatore temporaneo che uso per scorrere i vertici dell'insieme

		while(poi!=NULL){  //questo primo giro imposto i rappresentanti
	
		   poi->Rappresentante=capo;
		   
		   poi=poi->Next;
		}
		
		//Ora devo rilinkare tutti i nodi rappresentati
		if(capo->Next==NULL) {//CASO 1
			capo->Next=nuovo; //Non ho ancora nessun rappresentato
			return 1;			//Allora il rappresentato è l'albero che ho appena unito a me
		} 
        

		//caso 2
		poi=capo->Next; //se non ho impostato già il rilink, devo cominciare dalla fine della lista
		                //di chi già rappresentavo
		while(poi!=NULL){  // questo secondo giro invece rilinka tutti i rappresentati
			if(poi->Next==NULL){
				poi->Next=nuovo;
				return 1;  //ed esce quando ha linkato i rappresentati (se no diventava un loop infinito)
			}
		    poi=poi->Next;
		}
		return 1;
	 }

	 void printresult(unsigned int clustnumb){
		float peso=0.0;
		for(int cont=0;cont<MST.size();++cont)
			peso+=MST[cont].getW();
	
		cout<<endl<<"s\tMST\t" << peso<<endl;//stampa prima riga
		for(int i=0;i<MST.size();++i)//e stampa il set
			cout<<"e\t"<<MST[i].getV1ID()+1<<"\t"<<MST[i].getV2ID()+1<<"\t"<<MST[i].getW()<<endl;

		if(clustnumb == -1)//se non ho cluster esco (-1 è il mio flag di errore)
			return;
		for(int i=0; i<Cluster.size();++i)//senno stampo
			cout<<"c\t"<<Cluster[i].first<<"\t"<<Cluster[i].second<<endl;		
	 }

	void Clustering(vector<Vertex* > &V){

		 int cluster_class=0;
		 vector<bool> bitVector(V.size());
		 pair<int,int> mappa; // rispettivamente vertice, cluster di appartenenza
 
		 for(int i=0; i<V.size();++i)//POCO EFFICIENTE CAMBIARE
		   bitVector[i] = false;
		 Vertex *poi; //scorrerà le liste,come in UNION
		 for(unsigned int i=0; i<V.size();++i){
			  poi = V[i];
			  if(poi->Rappresentante!=NULL) //solito controllo se non sono già il rappresentante di me stesso
			   poi = poi->Rappresentante;

			  if( !(bitVector[poi->getID()]) ){
				   cluster_class++;
				   
				   do{
					mappa.first = poi->getID()+1;
					mappa.second = cluster_class;
					Cluster.push_back(mappa);// ogni elemento di vector è vertice,cluster
					bitVector[poi->getID()] = true;
					poi = poi->Next;
				   }while(poi!=NULL); //assegno al cluster tutti i vertici linkati finora da union
			  }
		 }
	}
    };
