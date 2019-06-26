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
#include "Tree.h"
#include <chrono> 
#include <array>
#include <iterator>
using namespace std;

typedef std::array<double, 22> twentyTwo_array;
typedef std::array<double, 200> twoHundred_array;

//Implementações dos métodos da classe Tree	

Tree::Tree()	// constructor
{
	raiz = NULL;
	pLeft=NULL;
	pRight=NULL;
	feature=-1;
	value=-1;
	isLeaf=false;
	Class=-1;
}

void Tree::initializeRaiz(Tree* pRoot)
{
	raiz = pRoot;
}

void Tree::destroyTree(Tree* raiz)
{
	if(raiz!=NULL)
	{
		destroyTree(raiz->pLeft);
		destroyTree(raiz->pRight);
		delete raiz;
	}
	raiz = NULL;
}

Tree::~Tree()	// destructor
{
	destroyTree(raiz);	
}

// limpa os campos "root" da árvore já criada
void Tree::clearData(Tree* pRoot)
{
	if(pRoot!=NULL)
	{
		clearData(pRoot->pLeft);
		clearData(pRoot->pRight);
		pRoot->root.clear();
	}
}

// cria a árvore que será utilizada para classificação
void Tree::treeGrowth(Tree* pRoot)
{
	bool stop;
	Tree* psLeft  = NULL;
    Tree* psRight = NULL;
    static vector< twentyTwo_array >::size_type N = pRoot->root.size();
	
	stop = Train_Model::stopCond(pRoot->root,N);
	
	if(stop)
	{
		pRoot->Class = Train_Model::Classify(pRoot->root);
		pRoot->isLeaf = true;
		pRoot->feature = -1;
		pRoot->value = -1;
	}
	
	else
	{
		psLeft = new Tree;
    	psRight = new Tree;
		
		Train_Model::splitData(psLeft->root,psRight->root,pRoot->feature,pRoot->value,pRoot->root);
		//system("pause");
		
		pRoot->pLeft = psLeft;
		pRoot->pRight = psRight;
		pRoot->isLeaf = false;

		treeGrowth(psLeft);
		treeGrowth(psRight);
	}		
}

void Tree::showTree(Tree* pRoot)
{
	cout << "Size root: " << pRoot->root.size() << endl;
	cout << "feat: " << pRoot->feature << endl;
	cout << "val: " << pRoot->value << endl;
	cout << "isLeaf: " << pRoot->isLeaf << endl;
	cout << "Class: " << pRoot->Class << endl << endl;	
	
	if(pRoot->pRight != NULL)
	{
	cout << "Size root: " << pRoot->pRight->root.size() << endl;
	cout << "feat: " << pRoot->pRight->feature << endl;
	cout << "val: " << pRoot->pRight->value << endl;
	cout << "isLeaf: " << pRoot->pRight->isLeaf << endl;
	cout << "Class: " << pRoot->pRight->Class << endl << endl;
	}
	 
	if(pRoot->pLeft != NULL)
	{
	cout << "Size root: " << pRoot->pLeft->root.size() << endl;
	cout << "feat: " << pRoot->pLeft->feature << endl;
	cout << "val: " << pRoot->pLeft->value << endl;
	cout << "isLeaf: " << pRoot->pLeft->isLeaf << endl;
	cout << "Class: " << pRoot->pLeft->Class << endl << endl;
	}
	
	system("pause");system("cls");
	
	if(pRoot->pRight != NULL)
		showTree(pRoot->pRight);
	if(pRoot->pLeft != NULL)	
		showTree(pRoot->pLeft);
}

//	utiliza a árvore gerada por treeGrowth() e classifica uma sample
void Tree::DecisionTreeClassifier(Tree* pRoot, twentyTwo_array sample,int& classe)
{
	int feat;
	double val;
	
	if(pRoot->isLeaf == false)
	{
		feat = pRoot->feature;
		val = pRoot->value;
		
		if(sample[feat] >= val)
			DecisionTreeClassifier(pRoot->pRight,sample,classe);
		else
			DecisionTreeClassifier(pRoot->pLeft,sample,classe);	
	}
	
	else{
		classe = pRoot->Class;
		}
}
