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

class Tree : public Train_Model
{
	
	public:
	vector< twentyTwo_array > root;
	Tree* raiz;
	Tree* pLeft;
	Tree* pRight;
	int feature;
	double value;
	bool isLeaf;
	int Class;
	int sizeInitialData;
	
	// constructor
	Tree();
	
	void initializeRaiz(Tree* pRoot);
	
	void destroyTree(Tree* raiz);
	
	// destructor
	~Tree();
	
	//limpa os campos "root" da �rvore j� criada
	void clearData(Tree* raiz);
	
	// cria a �rvore que ser� utilizada para classifica��o
	void treeGrowth(Tree* pRoot);
	
	// mostra a �rvore criada
	void showTree(Tree* pRoot);
	
	//	utiliza a �rvore gerada por treeGrowth() e classifica uma sample
	void DecisionTreeClassifier(Tree* pRoot, twentyTwo_array sample,int& classe);
	
};
