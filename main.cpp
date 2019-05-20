//Andrew Langwell
//Devan Royal
//4-23-19
//CS 415 Gill
//Description: Takes a text file supplied by the user
//             and turns it into a word index, implemented
//             through the use of a BST 

#include <iostream>
#include <fstream>
#include "bst.h"
#include "twoThree.h"

using namespace std;

int main(int argc, char* argv[]) {
	int choice;
	char option;
	if (argc != 2) {
	    cout << "Incorrect input. Correct format: ./<exectuable.out> <inputtext.txt>\n";
	    return 1;
	}
	while (1) {
		option = ' ';
		cout << "Options: (a) BST, (b) 2-3 Tree, (c) Compare BST and 2-3 Tree\n";
		cin >> option;

		if (option == 'a') {
			ifstream input(argv[1]);
			BST myTree;

			if (input.is_open()) {
				myTree.buildTree(input, true);
				input.close();
				while (1) {
					choice = 0;
					cout << "Options: (1) display index, (2) search, (3) save index, (4) quit\n";
					cin >> choice;

					//Print index
					if (choice == 1)
						myTree.printTree(cout);

					//Search index for a word
					else if (choice == 2)
						myTree.contains();

					//Save index
					else if (choice == 3) {
						string outputFile;
						cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
						cin >> outputFile;
						ofstream output(outputFile.c_str());
						myTree.printTree(output);
						output.close();
						cout << "Saved\n";
					}

					//Quit	
					else
						break;
				}
			}
			else {
				cout << "Invalid File Name. Restart Program.\n";
				return 2;
			}
		}
		else if (option == 'b') {
			ifstream input(argv[1]);
			TTT myTree;

			if (input.is_open()) {
				myTree.buildTree(input, true);
				input.close();
				while (1) {
					choice = 0;
					cout << "Options: (1) display index, (2) search, (3) save index, (4) quit\n";
					cin >> choice;

					//Print index
					if (choice == 1)
						myTree.printTree(cout);

					//Search index for a word
					else if (choice == 2)
						myTree.contains();

					//Save index
					else if (choice == 3) {
						string outputFile;
						cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
						cin >> outputFile;
						ofstream output(outputFile.c_str());
						myTree.printTree(output);
						output.close();
						cout << "Saved\n";
					}
					//Quit	
					else
						break;
				}
			}
			else {
				cout << "Invalid File Name. Restart Program.\n";
				return 2;
			}
		}
		else if (option == 'c') {
			//build BST and 2-3 Tree, compares performance of seraching all words in the index in both trees.
			ifstream BSTinput(argv[1]), TTTinput(argv[1]), BSTsearch(argv[1]), TTTsearch(argv[1]);
			BST myBST;
			TTT myTTT;

			if (BSTinput.is_open()) {
				myBST.buildTree(BSTinput, false);
				BSTinput.close();
			}

			if (TTTinput.is_open()) {
				myTTT.buildTree(TTTinput, false);
				TTTinput.close();
			}

			if (BSTsearch.is_open()) {
				myBST.searchAllTree(BSTsearch);
				BSTsearch.close();
			}
	
			if (TTTsearch.is_open()) {
				myTTT.searchAllTree(TTTsearch);
				TTTsearch.close();
			}
		}
		else {
			break;
		}
	}
	return 0;
}
