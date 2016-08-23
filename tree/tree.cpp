//main.cpp 定义程序入口点
#include"stdafx.h"
#include"tree.h"
#include<string>




int main() {
	//chTree a("1+2*3-4*93 / (2+ 3*2 )");
	std::string b;
	getline(std::cin,b,'=');
	std::cout <<b<< "=";
	chTree bb(b);
	std::cout << bb.getAnswer();
	//BinaryTree<int>p;
	//p.createTree(-1);
	system("pause");
	return 0;
}