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
#include "Train_Model.h"
#include <chrono> 
#include <array>
#include <iterator>
using namespace std;

typedef std::array<double, 22> twentyTwo_array;
typedef std::array<double, 200> twoHundred_array;

//Implementações dos métodos da classe Train_Model	
	
Train_Model::Train_Model()	// construtor da classe
{
	nCosts = 0;
	nFeats = 0;
	nSamples = 0;
	nClasses = 0;
	isAllocated = 0;
	filename = "";
}
//==============================================================================
	
void Train_Model::mostra(vector< twentyTwo_array > a)
{
	vector< twentyTwo_array >:: size_type i=0;
	int j=0;
	
	for(i=0;i<a.size();i++)
	{
		for(j=0;j<a[i].size();j++)
		{
			cout << a[i][j] << " ";
		}
		system("pause");
		cout << endl;
	}
}

void Train_Model::mostra(vector<double> a)
{
	vector<double>::size_type i;
	
	for(i=0;i<a.size();i++)
	{
		cout << a[i] << endl;
		system("pause");
	}
}

void Train_Model::mostra(vector<int> a)
{
	vector<int>::size_type i;
	
	for(i=0;i<a.size();i++)
	{
		cout << a[i] << endl;
		system("pause");
	}
}

//==============================================================================

void Train_Model::init(int a, int b,string nomedoarquivo)	// inicializa o número de custos e o numero de features
{
	nCosts = a;
	nFeats = b;
	filename = nomedoarquivo;	
}

//==============================================================================	
// determina o menor valor maior que zero de um array

double Train_Model::min(double *A, int n)
{
	vector<double> a;
	int i;

	for(i=0;i<n;i++)
	{
		if(A[i]>=0)
			a.push_back(A[i]);
	}

	sort(a.begin(),a.end());

	return *(a.begin());	
}

//	determina o menor valor maior que zero de um array
// indica em indice a posicao do minimo no array inicial
double Train_Model::min(double* A, int n, int& indice)
{
	vector<double> a;
	int i;
	double minimo;

	for(i=0;i<n;i++)
	{
		if(A[i]>=0)
			a.push_back(A[i]);
	}

	sort(a.begin(),a.end());
	
	minimo = *(a.begin());
	
	for(i=0;i<n;i++)
	{
		if(A[i] == minimo)
			break;
	}
	
	indice = i;
	return minimo;
}

//	determina o menor valor maior que zero de um vector
// retorna em "indice" a posicao do minimo no vector
double Train_Model::min(vector<double> A, int& indice)
{
	vector<double>::size_type i;
	vector<double> a;
	double minimo;
	
	if(A.size()>1)
	{
	
		for(i=0;i<A.size();i++)
		{
			if(A[i]>=0)
				a.push_back(A[i]);
		}
		
		if(a.size()<1)
		{
			indice = 0;
			return 1;
		}
	
		sort(a.begin(),a.end());
	
		minimo = *(a.begin());
	
		for(i=0;i<A.size();i++)
		{
			if(A[i] == minimo)
				break;
		}
	
		indice = static_cast<int>(i);
		return minimo;
	}
	
	else
		return A[0];
		indice = 0;
	
}

//==============================================================================	

void Train_Model::load()
{		
	int i=0,j;		
	double aux;	
	vector<double>::size_type k=0;
			
	ifstream meuarquivo(filename); 
	if (meuarquivo.is_open())
	{
		while (! meuarquivo.eof() ) 
		{
			meuarquivo >> aux;
			all.push_back(aux);
			i++;
		}
		meuarquivo.close();
	}

	else
   		cout << "Não foi possível abrir o aquivo !";
   		
   	nSamples = (i-1)/(nCosts+nFeats+2);
}

//============================================================================== 
// esse método cria o vector de vector "data". Ele contém os dados iniciais já tratados:
// classes só 0 e 1, custos normalizados, features "inúteis" retiradas

void Train_Model::getData()
{
  vector < twentyTwo_array >::size_type i;
  int j;
  int k;
  double a[11];
  int z=0;
  int w;
  double menor;

  for(i=0;i<nSamples;i++)
  {
    twentyTwo_array linhas;
    w=0;
    
    for(j=1;j<nCosts+nFeats+2;j++)
    {
    	if(j>=1 && j<=9)
      	{
		linhas[w] = (all[j + (nCosts+nFeats+2)*i]);
        w++;
    	}
    	
		if(j==11)
		{
			if(all[j + (nCosts+nFeats+2)*i] != 0)
			{
				linhas[w] = 1;
          		w++;
          	}
			else
			{
        		linhas[w] = 0;
       			 w++;
			}
		}
			
		if(j>11 && j<nCosts+nFeats+1)
		{
			z=0;
			for(k=12;k<nCosts+nFeats+1;k++)
			{
				a[z] = all[k + (nCosts+nFeats+2)*i];
				z++;
			}
			menor = min(a,z);
				
			linhas[w] = (all[j + (nCosts+nFeats+2)*i]/menor);
        	w++;
		}
			
		if(j==nCosts+nFeats+1)
		{
			linhas[w] = all[j + (nCosts+nFeats+2)*i];
        	w++;
        }
    }
    data.push_back(linhas);
  }

}	

//==============================================================================
   	
void Train_Model::getFeatures(const vector < twentyTwo_array>& data_in)   	
{
	int i,j,w;   	
	twentyTwo_array linha;

   	for(i=0;i<nSamples;i++)	
	{
		w=0;
		
		for(j=1;j<(nFeats-1);j++) 	//elimina a feature que é sempre 1 e a que é a média
		{
			linha[w] = data_in[i][j];
			w++;	
		}
		
		Features.push_back(linha);				//carrega o vector das features
	}
	
	nFeats = nFeats - 2;
		
}

//==============================================================================

void Train_Model::getCostsAndQP()
{
	double data_in[nSamples][nFeats+nCosts+2];
	int i,j;
	vector<double>::size_type k=0;
	
	for(i=0;i<nSamples;i++)
   	{
   		for(j=0;j<nCosts+nFeats+2;j++)
		{   
		   data_in[i][j] = all[k];
		   k++;
		}	
	}
	
	for(i=0;i<nSamples;i++)
	{
		vector<double> linha1;
		for(j=nFeats+1;j<(nFeats+nCosts+1);j++)
		{
			linha1.push_back(data_in[i][j]);	
		}
		Costs.push_back(linha1);				// carrega o vector dos custos
		QP.push_back(data_in[i][nFeats+nCosts+1]);	// carrega o vector dos QP's
	}
}

//==============================================================================
// ao sair desse método, as features estarão ordenados pelas colunas
// ao sair desse método, o cell de features não tem termos repetidos e tem seus elementos calculados como a média de cada b elementos

vector< twoHundred_array >  Train_Model::reduceOptions(const vector< twentyTwo_array >& a,double b)
{
	vector< vector<double> > out;
	vector< vector<double> > F;
	vector< twentyTwo_array >::size_type i=0;
	int j=0;
	vector<double> n;
	vector<double> n_copy;
	vector<double> n_copy_aux;
	vector<double>::iterator it;
	vector<double>::iterator it2;
	vector<double>::iterator it3;
	int i1;
	int j1;
	double x;
	vector< vector<double> > z;
	vector<double> aux;
	int newSize;
	double fixed_b = b;
	double mean=0;
	double r;
	
	for(i=0;i<a.size();i++)
	{
		vector<double> linhas2;
		for(j=0;j<9;j++)
		{
			linhas2.push_back(a[i][j]);
		}
		
		F.push_back(linhas2);
	}

	j=0;
	while(j!=F[0].size())
	{
		n.clear();
		for(i=0;i<F.size();i++)
		{
			n.push_back(F[i][j]);	//pega a coluna de features
		}

		n_copy.clear();	
		n_copy = n;
		sort(n.begin(),n.end());

		it = unique_copy(n.begin(),n.end(),n_copy.begin());
		n_copy.clear();	
		for(it2=n_copy.begin();it2!=it;++it2)
			n_copy.push_back(*(it2)); 
			
		n_copy_aux = n_copy;	
		
		b = fixed_b;
		if(n_copy.size()>=fixed_b)
			newSize = ceil(n_copy.size()/b);
		else
			newSize = n_copy.size();	
			
		z.clear();
		
		for(j1=0;j1<newSize;j1++)
		{
			x=0;
			for(r=0;r<n_copy.size();r++)
				x++;

			if(x/b >= 1)
				b=b;
			else
				b=x;
				
			vector<double> linhas1;	
			for(i1=0;i1<b;i1++)
			{
				linhas1.push_back(n_copy[i1]);
			}
					
			for(i1=0;i1<b;i1++)
			{
				n_copy.erase(n_copy.begin());
			}
			
			z.push_back(linhas1);
		}
		
		aux.clear();
		
		if(n_copy_aux.size()>=fixed_b)
		{
		
			for(j1=0;j1<newSize;j1++)
			{
				it3 = z[j1].begin();
				mean=0;
				while(it3 != z[j1].end())
				{
					mean = mean + *it3;
					++it3;
				}
			
				mean = mean/z[j1].size();
				aux.push_back(mean);	
			}
		}
		else
			aux = n_copy_aux;
			
		out.push_back(aux);
		j++;		
	}	
	
	
	
	
	vector< vector<double> >::size_type ixp;
	vector<double>::size_type jxp;
	vector<double>::size_type sizeLinha;
	vector< twoHundred_array > finalOut;
	twoHundred_array linha;
	int w;
	
	for(ixp=0;ixp<out.size();ixp++)
	{
		w=0;
		sizeLinha = out[ixp].size();
		
		for(jxp=0;jxp<200;jxp++)
		{
			if(jxp< sizeLinha)
			{
				linha[w] = out[ixp][jxp];
				w++;
			}
			else
			{
				linha[w] = -1; //esse valor não é possível para features
				w++;
			}			
		}
		
		finalOut.push_back(linha);
		
	}
	
	return finalOut;
}

//==============================================================================

vector< vector<double> > Train_Model::reduceOptions_v2(const vector < twentyTwo_array >& a, int b)
{
vector< twentyTwo_array >::size_type i;
int j;
vector< vector<double> > F; 
F.reserve(9); //sempre serão 9 features
vector<double> linhas; //cada linha são todos os valores possíveis para aquela feature
int N = a.size(); //número de amostras
linhas.reserve(N);
vector<double> linhas_aux; //valores já reduzidos
linhas_aux.reserve(b);
vector<double>::size_type m, b_aux = b, k;


for(j=0;j<9;j++)
{
  linhas.clear();
  for(i=0;i<N;i++)
  {
    linhas.push_back(a[i][j]);
  }
  sort(linhas.begin(), linhas.end());
  linhas.erase( unique(linhas.begin(),linhas.end()), linhas.end() );
  //cout << "Tamanho logo apos remover duplicatas: " << linhas.size() << endl;

  if(linhas.size()>b_aux)
  {
    linhas_aux.clear();
    k=0;
    m=0;
    linhas_aux.push_back(linhas[0]);
    while(linhas_aux.size() < b_aux)
    {
      m = m + (int)linhas.size()/b;
      linhas_aux.push_back(linhas[m]);
      k++;
    }
	//cout << "Tamanho apos reducao: " << linhas_aux.size() << endl;
	//system("pause");
    F.push_back(linhas_aux);
  }

  else
    F.push_back(linhas);
}
return F;
}

//==============================================================================
//data está ordenado por linhas e as saídas também
// feat é um inteiro no range [0,9]

vector< twentyTwo_array >  Train_Model::divideData(const vector< twentyTwo_array >& data_in,vector< twentyTwo_array >& dataR ,int feature ,double value)
{
	vector< twentyTwo_array > outL;
	vector< twentyTwo_array >:: size_type i=0;
	int j=0;
	
	dataR.clear();

	j = feature;	
	
	for(i=0;i<data_in.size();i++)
	{
		if(data_in[i][j] < value)
			outL.push_back(data_in[i]);
		else
			dataR.push_back(data_in[i]);
	}
	
	return outL;
}

//==============================================================================
//data está ordenado por linhas e as saídas também
// feat é um inteiro no range [0,9]

vector< vector<double> >  Train_Model::divideData(const vector< vector<double> >& data_in,vector< vector<double> >& dataR ,int feature ,double value)
{
	vector< vector<double> > outL;
	vector< vector<double> >:: size_type i=0;
	vector<double>::size_type j=0;
	
	dataR.clear();

	j = feature;	
	
	for(i=0;i<data_in.size();i++)
	{
		if(data_in[i][j] < value)
			outL.push_back(data_in[i]);
		else
			dataR.push_back(data_in[i]);
	}
	
	return outL;
}

//==============================================================================
// calcula a entropia dadas as probabilidades
// para o caso desse problema, como só temos classes 0 e 1, esse array sempre terá tamanho igual a 2

double Train_Model::entropyCalc(double p[])
{
	int i;
	double a[2];
	double s=0;
	
	for(i=0;i<2;i++)
	{
		if(p[i] != 0)
			a[i] = -1*p[i]*log2(p[i]);
		else
			a[i] = 0;	
		
		s = s+a[i];
	}
	
	return s;
}

//==============================================================================
//	calcula a entropia de um banco de dados

double  Train_Model::dataEntropy(const vector< twentyTwo_array >& a)
{
	vector<double> c;
	vector< twentyTwo_array >::size_type i;
	double p[2];
	int count0 = 0;
	int count1 = 0;
	double aux = 0;
	
	for(i=0;i<a.size();i++)
	{
		if(a[i][9] == 0)
			count0++;
		else
			count1++;	
			
		aux++;	
	}
	
	p[0] = count0/aux;
	p[1] = count1/aux;
	
	return entropyCalc(p);
	
}

//==============================================================================
// esse método vai criar dois grupos a partir do grupo inicial de tal forma a minimizar o Weighted Average Impurity Measure (WAIM)
// esse método indica qual feature [0,8] e o correspondente valor que geraram a divisão ótima

void Train_Model::splitData(vector< twentyTwo_array >& dataL, vector< twentyTwo_array >& dataR, int& feat, double& val,const vector< twentyTwo_array >& data_in)
{
	vector< vector<double> > n;
	vector< vector<double> >::size_type j;
	int i;
	int b=10;
	
	n = reduceOptions_v2(data_in,b);	//n é o cell das features já comprimidas n[i,j] é o j-ésimo valore da i-ésima feature
	
	int N = data_in.size();	//quantidade de amostras no dataset
	const int Nf = 9; // quantidade de features
	vector< vector<double> > x;
	x.reserve(18);
	vector<double> linhas1;
	vector<double> linhas2;
	linhas1.reserve(b);
	linhas2.reserve(b);
	double Raux;
	double Laux;
	double Naux = N;

	for(j=0;j<Nf;j++)
	{		
	
		linhas1.clear();
		linhas2.clear();
		
		for(i=0;i<n[j].size();i++)
		{		
			dataL.clear();
			dataR.clear();
			
			dataL = divideData(data_in,dataR,j,n[j][i]);							
			
			if((dataL.size() != 0) && (dataR.size() != 0))
			{
				Raux = dataR.size();
				Laux = dataL.size();
				
				linhas1.push_back((Raux*dataEntropy(dataR)/Naux) + (Laux*dataEntropy(dataL)/Naux));
				linhas2.push_back(n[j][i]);
			}
			
			else
			{
				linhas1.push_back(-1);
				linhas2.push_back(-1);
			}
		}
		
		x.push_back(linhas1);
		x.push_back(linhas2);
		
	}
	
	double possibilities[Nf][3];
	int m=-1;
	
	int I;
	double Y;
	vector<double>::iterator it;
	
	
	for(i=0;i<2*Nf;i=i+2)
	{	
		m++;
		auto it = min_element(x[i].begin(),x[i].end(), [](const double &t1, const double &t2) {return t1 > 0 && (t2 <= 0 || t1 < t2);});
		Y = *it;
		I = distance(x[i].begin(), it);
				
		possibilities[m][0] = Y;
		possibilities[m][1] = x[i+1][I];
		possibilities[m][2] = m;
	}
	
	double aux[Nf];
	
	for(m=0;m<Nf;m++)
		aux[m] = possibilities[m][0];
			
	Y = min(aux,Nf,I);
	feat = I;
	val = possibilities[I][1];	
	
	dataL = divideData(data_in,dataR,feat,val);
	
	//cout << "deu bom!";
}

//==============================================================================
// calcula o custo de falar que todas as amostras do data_in são da classe 1 (custo1) ou da classe 0 (custo0)

double Train_Model::Custo0xCusto1(const vector< twentyTwo_array >& data_in, double& custo1)
{
	double custo0 = 0;
	vector< vector<double> > custos1;
	vector< twentyTwo_array >::size_type i;
	int j;
	int indice=0;
	custo1 = 1;
	
	for(i=0;i<data_in.size();i++)
	{
		vector<double> linhas;
		
		for(j=11;j<=20;j++)
		{
			linhas.push_back(data_in[i][j]);
		}
		
		custos1.push_back(linhas);
	}
	
	for(i=0;i<data_in.size();i++)
	{
		custo0 = custo0 + data_in[i][10];
		if(custos1[i].size()>0)
			custo1 = custo1 + min(custos1[i], indice);	
	}
	
	custo1 =  custo1 - 1;
	custo0 = custo0/data_in.size();
	custo1 = custo1/data_in.size();

	return custo0;
}

//==============================================================================
// retorna 0 se não deve parar
// retorna 1 se deve parar

bool Train_Model::stopCond(const vector< twentyTwo_array >& data_in, int N_aux) //N_aux é o tamanho do data inicial(primeiro de todos)
{
	vector< twentyTwo_array >::size_type a = data_in.size();
	bool stop = 0;
	vector< twentyTwo_array >::size_type i;
	int j;
	double a_aux = static_cast<double>(a);
	int count = 0; //numero de vetores [0 0 0 0 0 0 1 0 0] em data_in
	int count_match = 0; //
	vector<double> v;
	
	v.push_back(0);
	v.push_back(0);
	v.push_back(0);
	v.push_back(0);
	v.push_back(0);
	v.push_back(0);
	v.push_back(1);
	v.push_back(0);
	v.push_back(0);
	
	if(a==0)
		return 0;
	
	//checar quantos casos dentro de data_in temos o feature vector [0 0 0 0 0 0 1 0 0]. Se for mais que 80% do data_in de vetores desse tipo
	//a função deve retornar 1 para evitar recursão infinita
	
	for(i=0;i<a;i++)
	{
		for(j=0;j<9;j++)
		{
			if(data_in[i][j] == v[j])
				count_match++;
			else
			{
				count_match=0;
				break;
			}
			
			count++;	
		}
	}
	
	//cout << "sizeData: " << a_aux << endl;
	
	if(count/a_aux >= 0.8*a_aux) // se o número de vetores v em data_in for maior ou igual a 80% de data_in, a recursão para
	{//cout << 1 << endl;
	
		return 1;}	
	
	if(dataEntropy(data_in) == 0)
	{//cout << 2 << endl;
		return 1;}
		
	if(dataEntropy(data_in) <= 0.4)
	{//cout << 3 << endl;
		stop = 1;}	
	
	if(a_aux <= ((0.1)*N_aux))
	{//cout << 4 << endl;	
		stop = 1;	}
		
	/*if((dataEntropy(data_in) > 0.9) && (a_aux > ((0.05)*N_aux)))
	{cout << 5 << endl;
	
		stop = 0;}	*/
		
	//system("pause");	
	return stop;
}

//==============================================================================
//	classifica um grupo de forma a minimizar o custo

int Train_Model::Classify(const vector< twentyTwo_array >& data_in)
{
	double custo0=0;
	double custo1=0; 
	
	
	custo0 = Custo0xCusto1(data_in,custo1);
	
	if(custo0 <= custo1)
		return 0;
	else
		return 1;		
}
