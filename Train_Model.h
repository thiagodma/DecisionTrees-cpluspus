//Thiago Dantas de Moraes Almeida

#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <math.h>
#include <new>
#include <chrono> 
#include <array>
#include <iterator>
using namespace std;

typedef std::array<double, 22> twentyTwo_array;
typedef std::array<double, 200> twoHundred_array;

class Train_Model{
	public:
		int nCosts;
		int nFeats;
		int nSamples;
		int nClasses;
		int isAllocated;
		string filename;
		vector<double> all;
		vector< twentyTwo_array > data;
		vector< twentyTwo_array > Features;
		vector< vector<double> > Costs;
		vector<int> Classes;
		vector<int> QP;
	
	
	Train_Model();	// construtor da classe
//==============================================================================
	
	void mostra(vector< twentyTwo_array > a);
	
	void mostra(vector<double> a);
	
	void mostra(vector<int> a);
	
//==============================================================================
	
	void init(int a, int b,string nomedoarquivo);	// inicializa o número de custos e o numero de features
	
	
//==============================================================================	
	// determina o menor valor maior que zero de um array
	
	double min(double *A,int n);
	
	//	determina o menor valor maior que zero de um array
	// indica em indice a posicao do minimo no array inicial
	double min(double *A, int n, int& indice);
	
	//	determina o menor valor maior que zero de um vector
	// retorna em "indice" a posicao do minimo no vector
	double min(vector<double> A, int& indice);
	
//==============================================================================	

	void load();
	
//============================================================================== 
	// esse método cria o vector de vector "data". Ele contém os dados iniciais já tratados:
	// classes só 0 e 1, custos normalizados, features "inúteis" retiradas

	void getData();	
	
//==============================================================================
	   	
	void getFeatures(const vector < twentyTwo_array>& data_in);
	
//==============================================================================
	
	void getCostsAndQP();
	
//==============================================================================
	//data está ordenado por linhas e as saídas também
	// feat é um inteiro no range [0,9]
	
	vector< twentyTwo_array >  divideData(const vector< twentyTwo_array >& data_in,vector< twentyTwo_array >& dataR ,int feature ,double value);	
	
//==============================================================================
	
	vector< twoHundred_array >  reduceOptions(const vector< twentyTwo_array >& a,double b);
	
	vector< vector<double> > reduceOptions_v2(const vector < twentyTwo_array >& a, int b);
	
//==============================================================================
	//data está ordenado por linhas e as saídas também
	// feat é um inteiro no range [0,9]
	
	vector< vector<double> >  divideData(const vector< vector<double> >& data_in,vector< vector<double> >& dataR ,int feature ,double value);
	
//==============================================================================
	// calcula a entropia dadas as probabilidades
	// para o caso desse problema, como só temos classes 0 e 1, esse array sempre terá tamanho igual a 2
	
	double entropyCalc(double p[]);
	
//==============================================================================
	//	calcula a entropia de um banco de dados

	double  dataEntropy(const vector< twentyTwo_array >& a);

//==============================================================================
	// esse método vai criar dois grupos a partir do grupo inicial de tal forma a minimizar o Weighted Average Impurity Measure (WAIM)
	// esse método indica qual feature [0,8] e o correspondente valor que geraram a divisão ótima
	
	void splitData(vector< twentyTwo_array >& dataL, vector< twentyTwo_array >& dataR, int& feat, double& val,const vector< twentyTwo_array >& data_in);

//==============================================================================
	// calcula o custo de falar que todas as amostras do data_in são da classe 1 (custo1) ou da classe 0 (custo0)
	
	double Custo0xCusto1(const vector< twentyTwo_array >& data_in, double& custo1);

//==============================================================================
	// retorna 0 se não deve parar
	// retorna 1 se deve parar
	
	bool stopCond(const vector< twentyTwo_array >& data_in, int N_aux); //N_aux é o tamanho do data inicial(primeiro de todos)

//==============================================================================
	//	classifica um grupo de forma a minimizar o custo
	
	int Classify(const vector< twentyTwo_array >& data_in);

//==============================================================================
};
