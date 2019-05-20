#include "twoThree.h"
#include "time.h"
#include <iomanip>
#include <sstream>

TTT::TTT() {
	root = NULL;
}

bool TTT::isEmpty() {
	return root == NULL;
}

void TTT::contains() const {
	string input;
	node* foundNode = NULL;
	cout << "Search word: ";
	cin >> input;
	vector<int> lines;
	
	if (findhelp(root, input, lines)) {
		cout << "Line Numbers: " << lines[0];
		for (int i = 1; i < lines.size(); i++)
			cout << ", " << lines[i];
		cout << endl;
	}
	else
		cout << '\"' << input << "\" is not in the document\n";
}

void TTT::searchAllTree(ifstream& input) {
	vector<int> lines;
	stringstream tempWord;
	double totalTime, finishTime, startTime = clock();
	while (!input.eof()) {
		string tempLine, tempWord;

		//Read a whole line of text from the file
		getline(input, tempLine);
		for (int i = 0; i < tempLine.length(); i++) {
			//Insert valid chars into tempWord until a delimiter( newline or space) is found
			while (tempLine[i] != ' ' && tempLine[i] != '\n' && i < tempLine.length()) {
				tempWord.insert(tempWord.end(), tempLine[i]);
				i++;
			}

			//Trim any punctuation off end of word. Will leave things like apostrophes
			//and decimal points
			while (tempWord.length() > 0 && !isalnum(tempWord[tempWord.length() - 1]))
				tempWord.resize(tempWord.size() - 1);

			if (tempWord.length() > 0)
			{
				findhelp(root, tempWord, lines);
				//Clear out tempWord so we can use it again
				tempWord.clear();
			}
		}
	}
	//Do time and height calculation
	finishTime = clock();
	totalTime = (double)(finishTime - startTime) / CLOCKS_PER_SEC;

	//Print output
	cout << setw(40) << std::left
		<< "Total time taken by 2-3 Tree: " << totalTime << endl;
}

void TTT::printTreeHelper(node* t, ostream& out) const {
	if (t == NULL)
		return;
	else {
		printTreeHelper(t->left, out);
		if (t->llines.size() != 0) {
			out << setw(30) << std::left;

			out << t->lkey << " " << t->llines[0];
		
		for (int i = 1; i < t->llines.size(); i++)
			out << ", " << t->llines[i];
		out << endl;
		}
		printTreeHelper(t->center, out);
		if (t->rkey != "" && t->rlines.size() != 0) {
			out << setw(30) << std::left;
			out << t->rkey << " " << t->rlines[0];
			for (int i = 1; i < t->rlines.size(); i++)
				out << ", " << t->rlines[i];
			out << endl;
		}
		printTreeHelper(t->right, out);
	}
}

void TTT::printTree(ostream& out) const {
	out << "2-3 Tree Index:\n--------------\n";
		printTreeHelper(root, out);
}

void TTT::buildTree(ifstream& input, bool output) {
	int line = 1, numWords = 0, distWords = 0, treeHeight = 0;
	stringstream tempWord;
	double totalTime, finishTime, startTime = clock();
	while (!input.eof()) {
		string tempLine, tempWord;

		//Read a whole line of text from the file
		getline(input, tempLine);
		for (int i = 0; i < tempLine.length(); i++) {
			//Insert valid chars into tempWord until a delimiter( newline or space) is found
			while (tempLine[i] != ' ' && tempLine[i] != '\n' && i < tempLine.length()) {
				tempWord.insert(tempWord.end(), tempLine[i]);
				i++;
			}

			//Trim any punctuation off end of word. Will leave things like apostrophes
			//and decimal points
			while (tempWord.length() > 0 && !isalnum(tempWord[tempWord.length() - 1]))
				tempWord.resize(tempWord.size() - 1);

			if (tempWord.length() > 0)
			{
				//Once word is formatted,call insert with the word, the line of the input
				//file it came from, the root of our tree, and the distinct word counter
				root = inserthelp(root, tempWord, line, distWords);
				//Increment our total number of words inserted
				numWords++;
				//Clear out tempWord so we can use it again
				tempWord.clear();
			}

		}
		line++;
	}
	//Do time and height calculation
	finishTime = clock();
	totalTime = (double)(finishTime - startTime) / CLOCKS_PER_SEC;
	treeHeight = findHeight(root);

	//Print output
	if (output) {
		cout << setw(40) << std::left;
		cout << "Total number of words: " << numWords << endl;

		cout << setw(40) << std::left
			<< "Total number of distinct words: " << distWords << endl;

		cout << setw(40) << std::left
			<< "Total time spent building index: " << totalTime << endl;

		cout << setw(40) << std::left
			<< "Height of 2-3 Tree is : " << treeHeight << endl;
	}
}

bool TTT::findhelp(node* root, const string& k, vector<int>& lineNums) const{
    if (root == NULL) return false;          // val not found
	if (k.compare(root->lkey) == 0) {
		lineNums = root->llines;
		return true;
	}
	if ((root->rkey != "") && (k.compare(root->rkey) == 0)) {
		lineNums = root->rlines;
		return true;
	}
    if (k.compare(root->lkey) < 0)       // Search left
        return findhelp(root->left, k, lineNums);
    else if (root->rkey == "")           // Search center
        return findhelp(root->center, k, lineNums);
    else if (k.compare(root->rkey) < 0)  // Search center
        return findhelp(root->center, k, lineNums);
    else return findhelp(root->right, k, lineNums); // Search right
}

TTT::node* TTT::inserthelp(node*& rt, const string &k, int line, int& distWords) {
	node* retval;

	if (rt == NULL) { // Empty tree: create a leaf node for root
		node * temp = new node(k, "", NULL, NULL, NULL);
		temp->llines.push_back(line);
		distWords++;
		return temp;
	}
	if (rt->lkey == k) {
		rt->llines.push_back(line);
		return rt;
	}
	else if (rt->rkey == k) {
		rt->rlines.push_back(line);
		return rt;
	}
	if (rt->isLeaf()) { // At leaf node: insert here
		node* temp = new node(k, "", NULL, NULL, NULL);
		temp->llines.push_back(line);
		distWords++;
		return rt->add(temp);
	}
    // Add to internal node
    if (k.compare(rt->lkey) < 0) { // Insert left
        retval = inserthelp(rt->left, k, line, distWords);
		if (retval == rt->left)
			return rt;
		else {
			return rt->add(retval);
		}
    }
    else if((rt->rkey == "") || (k.compare(rt->rkey) < 0)) {
        retval = inserthelp(rt->center, k, line, distWords);
        if (retval == rt->center) return rt;
		else {
			return rt->add(retval);
		}
    }
    else { // Insert right
        retval = inserthelp(rt->right, k, line, distWords);
        if (retval == rt->right) return rt;
		else {
			return rt->add(retval);
		}
    }
}

// Add a new key/value pair to the node. There might be a subtree
// associated with the record being added. This information comes
// in the form of a 2-3 tree node with one key and a (possibly null)
// subtree through the center pointer field.


//Returns height of tree. If tree has only one node, height is 1
int TTT::findHeight(node* t) {
	if (t == NULL)
		return 0;
	else {
		int leftHeight = findHeight(t->left), centerHeight = findHeight(t->center), rightHeight = findHeight(t->right);
		if (leftHeight >= rightHeight && leftHeight >= centerHeight)
			return(leftHeight + 1);
		else if (centerHeight >= leftHeight && centerHeight >= rightHeight)
			return(centerHeight + 1);
		else
			return(rightHeight + 1);
	}
}
