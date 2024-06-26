//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Philip Trinh
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include <algorithm> //added this due to error with "int __cdecl remove(const char *_Filename)" prevent compile 
                    //https://stackoverflow.com/questions/34361669/error-cannot-convert-stdbasic-stringchariterator-to-const-char-fo
#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Bid bid;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Bid aBid) :
            Node() {
        bid = aBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree
{

private:
Node *root;

void addNode(Node *node, Bid bid);
void inOrder(Node *node);
void preOrder(Node *node);
void postOrder(Node *node);
Node *removeNode(Node *node, string bidId);

public:
BinarySearchTree();
virtual ~BinarySearchTree();
void InOrder();
void PostOrder();
void PreOrder();
void Insert(Bid bid);
void Remove(string bidId);
Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // FixMe (1): initialize housekeeping variables
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
/* reference 
https://www.techiedelight.com/delete-given-binary-tree-iterative-recursive/
*/
    //base case of empty tree
    if (root == nullptr){
        return;
    //if from root to left have children and right is empty
    } else if (root ->left != nullptr && root -> right == nullptr) {
    //create node point to temp equal to root to the right side
    Node *temp = root -> right;
    //delete temp
    delete temp;
    //set temp point to nullptr
    temp= nullptr;
    //if from root to right have children and right is empty
    } else if (root ->right != nullptr && root -> left == nullptr) {
    //create node point to temp equal to root to the left side
    Node *temp = root -> left;
    //delete temp
    delete temp;
    //set temp point to nullptr
    temp= nullptr;  
    //else delete root
    }else{
    delete root;
    //set root to nullptr
    root = nullptr;
    }
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // FixMe (2): In order root
    // call inOrder fuction and pass root 
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // FixMe (3): Post order root
    // postOrder root
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // FixMe (4): Pre order root
    // preOrder root
    preOrder(root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // FIXME (5) Implement inserting a bid into the tree
    // if root equal to null ptr, empty tree
    if (root == nullptr) {
        // root is equal to new node bid
        root = new Node(bid);
    // else
    }else{
    // add Node root and bid
        this->addNode(root,bid);
    }    
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // FIXME (6) Implement removing a bid from the tree
    // remove node root bidID
    this->removeNode(root,bidId);

}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // FIXME (7) Implement searching the tree for a bid
    // set current node equal to root
    Node*current = root;
    //while current node is not empty
    while(current != nullptr){
        // keep looping downwards until bottom reached or matching bidId found
        if (current -> bid.bidId.compare(bidId) == 0) {
            // if match found, return current bid
            return current ->bid;
        }
        // if bid is smaller than current node then traverse left
        else if (bidId.compare(current->bid.bidId) <0) {
            current = current -> left;
        }
        // else larger so traverse right
        else {
            current = current -> right;
        }
    }     
    Bid bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // FIXME (8) Implement inserting a bid into the tree      
        // if node is larger then add to left
        if (node != nullptr && node->bid.bidId.compare(bid.bidId)>0){
            // if no left node
            if (node->left == nullptr){
                // this node becomes left
                node->left = new Node(bid);
                return;  
                 // else recurse down the left node    
            }else{        
                this->addNode(node->left, bid);
            }
        // else if node is lesser then add to right
        } else if (node != nullptr && node ->bid.bidId.compare(bid.bidId)<0){
            // if no right node
             if (node->right == nullptr){
                // this node becomes right
                node->right = new Node(bid);
                return;
            //else      
            }else{
                 // recurse down the right node
                this->addNode(node->right, bid);
            }
        }
}
void BinarySearchTree::inOrder(Node* node) {
      // FixMe (9): In order root   
      //if node is not equal to null ptr
    if (node != nullptr) {
         //InOrder left
        inOrder(node->left);
         //output bidID, title, amount, fund
        cout << node ->bid.bidId <<" : "<<node->bid.title<<" | "<<node->bid.amount<< " | "<<node->bid.fund<<endl;
        //InOder right
        inOrder(node->right);  
      }
}
void BinarySearchTree::postOrder(Node* node) {
      // FixMe (10): Pre order root
    //if node is not equal to null ptr
    if (node != nullptr) {
        //postOrder left
        postOrder(node->left);
        //postOrder right
        postOrder(node->right);
         //output bidID, title, amount, fund
        cout << node ->bid.bidId <<" : "<<node->bid.title<<" | "<<node->bid.amount<< " | "<<node->bid.fund<<endl;
          
       }
}

void BinarySearchTree::preOrder(Node* node) {
      // FixMe (11): Pre order root
    //if node is not equal to null ptr
    if (node != nullptr) {
         //output bidID, title, amount, fund
        cout << node ->bid.bidId <<" : "<<node->bid.title<<" | "<<node->bid.amount<< " | "<<node->bid.fund<<endl;
        //preOrder left
        postOrder(node->left);
        //preOrder right
        postOrder(node->right);
       }    
}
Node *BinarySearchTree::removeNode(Node *node, string bidId) {
    //if node is empty 
    if (node == nullptr){
        //return node since nothing to remove
        return node;
    //else if compare bid with bidId if lesser
    } else if (bidId.compare(node->bid.bidId) < 0){ 
        //go left and remove
        node->left = removeNode(node->left, bidId);
    //else if compare bid with bidId if greater
    } else if (bidId.compare(node->bid.bidId) > 0) {
        //go right and remove
        node->right = removeNode(node->right, bidId);
        //else
    } else {
        //match point found
        if (node->left == nullptr && node ->right == nullptr) {
            //no children so this is a leaf node  
            delete node;
            node = nullptr;
        }
        //else if left side have one child and right is empty
        else if (node->left != nullptr && node-> right == nullptr) {
            //create a temporary node to hold the node
            Node *temp = node;
            //point node to the left
            node = node-> left;
            //then delete the temp 
            delete temp;
            //temp equal to nullptr
            temp = nullptr;
        }
        //else if right side have one child and left is empty
        else if (node->right != nullptr && node-> left == nullptr) {
            //create a temporary node to hold the node
            Node *temp = node;
            //point node to the right
            node = node-> right;
            //then delete the temp 
            delete temp;
            //temp equal to nullptr
            temp = nullptr;
    //else there are two children
    } else {
        //find the minimum of the right subtree nodes for BST
        //create a temporary node point to the right 
        Node *temp = node -> right;
        //while left node is not empty
        while (temp ->left != nullptr) {
            //temporary node recursively point to left,  because the smaller node should be on left side
            temp = temp ->left;
        }
        //when can't go down anymore, found the minimum bid, copy it to the temporary node to replace
        node -> bid = temp -> bid;
        //point to  node on the right side, remove the node on the right with the temp bidId, because tempbidId is the minimum node
        node -> right = removeNode(node->right, temp->bid.bidId);
    }   
    }
    //return the new node to the caller
    return node;
}
//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}