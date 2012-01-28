/*
 *	See http://www.daimi.au.dk/~gudmund/dynamicF04/project2.pdf
 */

#include <vector>
#include <string>
using namespace std;

class Bt_node_secondary;
class Bt_node;

class Leaf {
	char c;
public:
	Leaf(char c): c(c) {}
	char getC() {
		return this->c;
	}
	void setC(char c);
	char f() {
		if(this->c=='{' || this->c=='[')
			return '(';
		if(this->c=='}' || this->c==']')
			return ')';
		return '#';
	}
	bool matchF(Leaf* match) {
		if(this->f()=='(' && match->f()==')')
			return true;
		/* if(this->f()==')' && match->f()=='(')
			return true; */
		/* if(this->f()=='#' && match->f()=='#')
			return true; */
		return false;
	}
};

class Bt_node {
	char* f;
	char* gl;
	char* gr;
	char* gm;
	/* Leafs are at level 0 */
	int height;
	void* children[2];
public:
	Bt_node() {}
	Bt_node(char* gl, char* gr, char* gm): gl(gl), gr(gr), gm(gm) {}
	/* f, gl, gr, gm and balanced can be built using only values in the current subtree 
	 * These values are created starting at the leafs and going up to the root */
	/* Return the string located in the current subtree */
	char* getS() {
		char strLeft[2], strRight[2];
		strLeft[1] = '\0';
		strRight[1] = '\0';
		if(this->height==1) {
			Leaf* chdLeft = (Leaf*)this->children[0];
			Leaf* chdRight = (Leaf*)this->children[1];
			strLeft[0] = chdLeft->getC();
			strRight[0] = chdRight->getC();
			return strcat(strLeft, strRight);
		}
		Bt_node* chdLeft = (Bt_node*)this->children[0];
		Bt_node* chdRight = (Bt_node*)this->children[1];
		return strcat(chdLeft->getS(), chdRight->getS());
	}
	char* getF() {
		char strLeft[2], strRight[2];
		strLeft[1] = '\0';
		strRight[1] = '\0';
		if(this->height==1) {
			Leaf* chdLeft = (Leaf*)this->children[0];
			Leaf* chdRight = (Leaf*)this->children[1];
			strLeft[0] = chdLeft->f();
			strRight[0] = chdRight->f();
			return strcat(strLeft, strRight);
		}
		Bt_node* chdLeft = (Bt_node*)this->children[0];
		Bt_node* chdRight = (Bt_node*)this->children[1];
		return strcat(chdLeft->getF(), chdRight->getF());
	}


};



class Bt {

public:
	Bt() {}
	void init(int n);
	void change(int i, char c);
	bool isBalanced();
	void print();
	/* In the future */
	/* Insert character c between position i-1 and i */
	void insert(int i, char c);
	/* Delete character at position i */
	void remove(int i);
	/* Returns true if the substring 1-i is a member of Dyck languages */
	bool prefix(int i);
	/* If given the position of an open bracket, returns its match */
	int match(int i);
};

class Bt_node_secondary {
	char* substring;
	/* 0 1
	 * 2 3 */
	int matrix[4];
	/* Number of non blank symbols in substring */
	int nonBlank;
public:
	Bt_node_secondary(char* substring): substring(substring) {
		this->nonBlank = this->countNonBlanks();
	}
	void getMatrix(Bt_node_secondary* left, Bt_node_secondary* right) {
		this->matrix[0] = left->matrix[0]*right->matrix[0] + left->matrix[1]*right->matrix[2];
		this->matrix[1] = left->matrix[0]*right->matrix[1] + left->matrix[1]*right->matrix[3];
		this->matrix[2] = left->matrix[2]*right->matrix[0] + left->matrix[3]*right->matrix[2];
		this->matrix[1] = left->matrix[2]*right->matrix[1] + left->matrix[3]*right->matrix[3];
	}
	
	
};

class Bt_secondary {
	
	

};

#include <cstdlib>
#include <iostream>
int main() {
	int testSize;
	cout << "Please give the string size(power of two):" << endl;
	cin >> testSize;
	Bt* test = new Bt();
	test->init(testSize);
	int i, nChanges = rand()%testSize;
	char alphabet[5] = {'[', ']', '{', '}', '#'};
	char c;
	for(i=0;i<nChanges;i++) {
		c = alphabet[rand()%5];
		test->change(rand()%testSize, c);
	}
	cout << "This is the new string:" << endl;
	test->print();
	cout << "Is it balanced? " << test->isBalanced();	
}

/*
	char* getGm() {
		if(strlen(this->f)==0)
			this->f = this->getF();
		int fil, midpoint, size = strlen(this->f);
		midpoint = size/2;
		// Full interval length
		fil = 0;
		while(fil<size || stopCond) {
			if(this->f[midpoint+fil/2]=='(')
				stopCond = true;
			if(this->f[midpoint-fil/2]==')')
				stopCond = true;
			if(this->f[midpoint-fil/2]=='(' && this->f[midpoint+fil/2]==')') {
				this->f[midpoint-fil/2] = this->f[midpoint+fil/2] = '#';
			}
		
	}
	char* getGl() {
		char strLeft[2], strRight[2];
		strLeft[1] = '\0';
		strRight[1] = '\0';
		if(this->height==1) {
			if(this->children[0]->match(this->children[1]))
				strLeft[0] = strRight[0] = '#';
			// else {
			//	if(this->children[0]->isR())
			//		strLeft[0] = '#';
			//	if(this->children[1]->isR())
			//		strRight[0] = '#';
			//} 
			return strcat(strLeft, strRight);
		}
		
	}
*/
