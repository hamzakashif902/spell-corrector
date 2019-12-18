// spell checker and spell corrector for DSA
#include<iostream>
#include<fstream>
#include<string.h>
#define size 100000
using namespace std;
class node{
	public:
		string data;
		node *left, *right, *parent;
};
class BST{
	private:
		node *root;
	public:
		BST(){
			root = NULL;
		}
		node* get_root(){
			return root;
		}
//compare strings
	int string_comparison(string str1, string str2){
		int res = str1.compare(str2);
		return res;
	}
//  inserting BST
		void insert(string word){
			node *temp = new node;
			node *sub_root = root;
			temp -> data = word;
			temp -> left = NULL;
			temp -> right = NULL;
			if(root == NULL){
				root = temp;
				sub_root = temp;
			}
			else{
				while(sub_root != NULL ){
					if(string_comparison(temp -> data, sub_root -> data) == 1){   //temp -> data < sub_root -> data 
						if(sub_root -> left == NULL){
							sub_root -> left = temp;
							temp -> parent = sub_root;
							return;
						}else{
							sub_root = sub_root -> left;
						}
					}else{
						if(sub_root -> right == NULL){
							sub_root -> right = temp;
							temp -> parent = sub_root;
							return;
						}else{
							sub_root = sub_root -> right;
						}
					}
				}
			}
			
		}
//  printing BST in inorder
		void print_inorder(node *temp){
			if(temp != NULL){
				print_inorder(temp -> left);
				cout << endl << temp -> data;
				print_inorder(temp -> right);
			}
		}
//  printing BST in postorder
		void print_postorder(node *temp){
			if(temp != NULL){
				print_postorder(temp -> left);
				print_postorder(temp -> right);
				cout << temp -> data;
			}
		}
//  printing BST in preorder
		void print_preorder(node *temp){
			if(temp != NULL){
				cout << temp -> data;
				print_preorder(temp -> left);
				print_preorder(temp -> right);
			}
		}
//  searching in BST
		int search(string word, node *temp, int &i, string arr[50], int &found){
			if(temp == NULL){
				return 0;
			}else if(string_comparison(word, temp -> data) == 0){                       
				cout << endl << "Word is found that is: " << temp -> data << endl;
				found = 1;
				return 1;
			}else{
				if(string_comparison(word, temp -> data) == 1){                        
					search(word, temp -> left, i, arr, found);
				}else{
					search(word, temp -> right, i, arr, found);
				}
			}
			
		}

//spell corrector

		int hamingDistance(string str1, string str2){
			int i = 0;
			int distance = 0;
			while(i < str1.length() || i < str2.length()){
				if(str1[i] != str2[i]){
					distance++;
				}
				i++;
			}
			return distance;
		}

		void correct(string word, node *temp, int &i, string arr[]){
			
			if(temp != NULL){
				correct(word, temp -> left, i, arr);
				if(hamingDistance(word, temp -> data) <= 2){
					arr[i] = temp -> data;					
					i++;
				}
				correct(word, temp -> right, i, arr);
			}
		}


		
};


int main(){
	int check = 0;
	int i = 0;
	int found = 0;
	string arr[size];
	system("color 88");
	BST B;
	string word1;
	ifstream mfile("spellDic.txt");
	if (mfile.is_open()){
		while(getline(mfile,word1)){
    		B.insert(word1);
    	}
    	mfile.close();
	}
	else{
		check = 1;
	 cout << "Unable to open the dictionary file";
	 
}
    if (check == 0){
    	
	cout << endl << "Enter the Word you want to search: ";
	string word = "";
	cin >> word;
	B.search(word, B.get_root(), i, arr, found);
	
	if(found != 1){

		cout << endl << "\tWord is Not Found select the operation you want to perform :" << endl << endl;
		cout << "Enter 0 to add the word into Dictionary and 1 to show suggestions: ";
		int option_of_word;
		cin >> option_of_word;
		

		if(option_of_word == 1){
			cout <<endl;
			B.correct(word, B.get_root(), i, arr);
			if(i == 0){
				cout << "No suggestion";
			}
			else{
				for(int j = 0; j < i; j++){
					cout << "\t\tEnter: " << j << " for: " << arr[j] << endl;
				}
		
				cout << endl << "Enter the option number you want to select: ";
				int suggested_word;
				cin >> suggested_word;
				if(((suggested_word <= i) && (suggested_word >= 0))){
					cout << endl << "The word you selected is: " << arr[suggested_word];	
				}
				else{
					cout << endl << "There is no such option.";
				}
			}	
				
		}
		else if(option_of_word == 0){

			ofstream mfile("spellDic.txt", ios::app); 
 		    mfile<< word << endl; 	
    		mfile.close();
			cout << " Word is in your dictionary" ;

		}
	}
}
	return 0;
}
