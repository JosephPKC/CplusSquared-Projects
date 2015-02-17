#include <iostream>
#include <cstdlib>
#include <string>
#include "Utilities.h"
#include "BinaryTree.h"
#include <fstream>
#include "stack.h"
#include "ftokenizer.h"
using namespace std;

const string LEFT_NULL = "(";
const string RIGHT_NULL = ")";
const map<Type,string> fileSet = {
    {LEFT,LEFT_NULL},
    {RIGHT,RIGHT_NULL},
    {UNKNOWN,""},
    {END,"\n"},
    {VALID," \tabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_;:\'\",./?\\!@#$%^&~`|-+=*/<>{}[]"}

};
void play(TreeNode<string>* root);
void learn(TreeNode<string>*& leaf);
void instructions();
TreeNode<string>* createBeginningTree();
void askAndMove(TreeNode<string>*& current);
bool saveToFile(TreeNode<string>* root, ofstream &out);
bool loadFromFile(TreeNode<string> *&root, string file);

//Left is Yes, Right is No
int main()
{
    TreeNode<string>* root;
    instructions();
//    root = createBeginningTree();
    ofstream out;

    if(!loadFromFile(root,"animals.txt")) return EXIT_FAILURE;
//    print(root,5);



    do play(root);
    while(inquire("Shall we play again?"));
    out.open("animals.txt");
    if(!out.is_open()) return EXIT_FAILURE;
    saveToFile(root,out);
    return EXIT_SUCCESS;
}

bool saveToFile(TreeNode<string>* root, ofstream& out){
    if(root == NULL) return false;
    if(!saveToFile(root->left(),out))
        out << LEFT_NULL;
    if(!saveToFile(root->right(),out))
        out << RIGHT_NULL;
    out << root->data() << endl;
    return true;
}

bool loadFromFile(TreeNode<string>*& root, string file){
    FTokenizer ftk(file);
    if(!ftk.isFileSet()) return false;
    ftk.setDictionary(fileSet);
    Stack<TreeNode<string> > stk;
    Token t;
    TreeNode<string>* hold;
    bool hasLeft = false;
    bool hasRight = false;
    while(ftk.moreInFile()){
        t = ftk.nextToken();
        if(t.getType() == LEFT) hasLeft = false;
        else if(t.getType() == RIGHT) hasRight = false;
        else if(t.getType() == VALID){
            hold = new TreeNode<string>();
            if(hasRight) hold->setRight(new TreeNode<string>(stk.pop()));
            if(hasLeft) hold->setLeft(new TreeNode<string>(stk.pop()));
            hold->setData(t.getToken());
            stk.push(*hold);
            hasLeft = true;
            hasRight = true;
        }
        else{}//Unknowns  or endline we skip
    }
    TreeNode<string> tn = stk.pop();
    root = new TreeNode<string>(tn.data(),tn.left(),tn.right());
    return true;
}

void play(TreeNode<string>* root){
    cout << "Think of an animal, then press the return key.";
    eatLine();
    while(!root->isLeaf()) askAndMove(root);
    cout << "My guess is " + root->data() + ", ";
    if(!inquire("Am I right?")) learn(root);
    else cout << "I knew it all along!" << endl;
}

void learn(TreeNode<string>*& leaf){
    string guess;
    string correct;
    string newQ;
    guess = leaf->data();
    cout << "I give up. What are you?" << endl;
    getline(cin,correct);
    cout << "Please type a yes/no question that will distinguish a "
         << correct << " from a " << guess << "." << endl;
    cout << "Your question: " << endl;
    getline(cin,newQ);
    leaf->setData(newQ);
    cout << "As a " << correct << ", " << newQ << endl;
    if(inquire("Please answer")){
        leaf->setLeft(new TreeNode<string>(correct));
        leaf->setRight(new TreeNode<string>(guess));
    }
    else{
        leaf->setRight(new TreeNode<string>(correct));
        leaf->setLeft(new TreeNode<string>(guess));
    }
}

void instructions(){
    cout << "Pick an animal and I will try to guess which animal it is by asking a series of questions." << endl;
}

TreeNode<string>* createBeginningTree(){
    TreeNode<string>* root;
    TreeNode<string>* branch;
    const string rootQ  ("Are you a mammal?");
    const string leftQ  ("Do you live underwater?");
    const string rightQ ("Are you a reptile?");
    const string leaf1  ("Whale");
    const string leaf2  ("Kangaroo");
    const string leaf3  ("Turtle");
    const string leaf4  ("Falcon");
    root = new TreeNode<string>(rootQ);
    branch = new TreeNode<string>(leftQ);
    branch->setLeft(new TreeNode<string>(leaf1));
    branch->setRight(new TreeNode<string>(leaf2));
    root->setLeft(branch);
    branch = new TreeNode<string>(rightQ);
    branch->setLeft(new TreeNode<string>(leaf3));
    branch->setRight(new TreeNode<string>(leaf4));
    root->setRight(branch);
    return root;

}

void askAndMove(TreeNode<string>*& current){
    cout << current->data();
    if(inquire(" Please answer:")) current = current->left();
    else current = current->right();
}
