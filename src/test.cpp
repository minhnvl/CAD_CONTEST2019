
#include <bits/stdc++.h>
#include <map>
#include <regex>
#include<string.h> 
#include <iostream> 
// #include "Code_ReadInput.h"
using namespace std;

int main(){
	std::vector<int> v = { 7, 3, 6, 2, 6 };
	int key = 6;

	// std::vector<int>::iterator itr = std::find(v.begin(), v.end(), key);
	int i = 0;

	// while (itr  != v.cend())
	// {
	// 	++i;
	// 	cout << i << endl;
	// 	// B.push_back(std::distance(A.begin(), it);)
	// 	// it++;
	// }


	// while(itr != v.cend())
	// if (itr != v.cend()) {
	// 	std:: cout << *itr << endl;
	// 	std::cout << "Element present at index " << std::distance(v.begin(), itr) << endl;
	// }
	// else {
	// 	std::cout << "Element not found";
	// }
	std::vector<int>::iterator it = v.begin();
	while ((it = std::find(it, v.end(), key)) != v.end())
	{
		// B.push_back(std::distance(A.begin(), it);)
		cout << distance(v.begin(), it) << endl;
		it++;
	}
	// return 0;




}

