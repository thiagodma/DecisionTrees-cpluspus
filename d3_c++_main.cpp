//Thiago Dantas de Moraes ALmeida

#include <iostream>
#include <fstream>
#include <typeinfo>
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

int main()
{	
	auto start = std::chrono::high_resolution_clock::now();

	Train_Model obj1;
	Tree obj2;
	Train_Model obj3;

	vector<int> classified_samples;
	vector < vector<double> >::size_type i=0;
	vector<int>::iterator j;
	vector<int>::size_type k=0;
	int count = 0;
	int classe = -1;

//-------------------------------------------

	obj1.init(11,11,"Features_Depth_0_Training_1.txt");	//training set
	obj1.load();
	obj1.getData();	
	obj1.getFeatures(obj1.data);

	vector< twentyTwo_array > dataL, dataR;
	int feat;
	double val;
	
	auto start1 = std::chrono::high_resolution_clock::now();

 //Descomentar esse bloco
	Tree* pRoot = new Tree;
	pRoot->root = obj1.data;
	obj2.initializeRaiz(pRoot);
	obj2.treeGrowth(pRoot);
	obj2.clearData(pRoot);

	auto finish1 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed1 = finish1 - start1;
	cout << "Elapsed time (training process): " << elapsed1.count() << "s" << endl;

//--------------------------------------------

	obj3.init(11,11,"Features_Depth_0_Training_3.txt"); //test set
	obj3.load();
	obj3.getData();

	auto start2 = std::chrono::high_resolution_clock::now();
	
	for(i=0;i<obj3.data.size();i++)
	{
		obj2.DecisionTreeClassifier(pRoot,obj3.data[i],classe);
		classified_samples.push_back(classe);
	}
	
	auto finish2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed2 = finish2 - start2;
	cout << "Elapsed time (classification process): " << elapsed2.count() << "s" << endl;

	for(j = classified_samples.begin();j!=classified_samples.end();++j)
	{
		if(*j == obj3.data[k][9])
			count++;
		k++;
	}

	cout <<"Acuracia: " << 100* static_cast<double>(count)/static_cast<double>(obj3.data.size()) << "%";
	cout << endl;


	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	cout << "Elapsed time (hole function): " << elapsed.count() << "s" << endl;
	return 0;
}
