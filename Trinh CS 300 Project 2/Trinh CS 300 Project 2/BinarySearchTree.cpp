//============================================================================
// Name        : Project2.cpp
// Author      : Philip Trinh
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm> //added this due to error with "int __cdecl remove(const char *_Filename)" prevent compile 
                    //https://stackoverflow.com/questions/34361669/error-cannot-convert-stdbasic-stringchariterator-to-const-char-fo
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// define a structure to hold Course information
struct Course {
    string courseNumber; // unique identifier
    string courseName;
    vector<string> coursePrerequisites;
};

// Internal structure for tree node
struct Node {
    Course course;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a Course
    Node(Course aCourse) :
            Node() {
        course = aCourse;
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

void addNode(Node *node, Course course);
void inOrder(Node *node);

public:
BinarySearchTree();
virtual ~BinarySearchTree();
void InOrder();
void loadCourses();
void Insert(Course course);
Course Search(string courseNumber);
};


/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //initialize housekeeping variables
    //root is equal to nullptr
    root = nullptr;
}
//Destructor
BinarySearchTree::~BinarySearchTree() {
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // In order root
    // call inOrder fuction and pass root 
    inOrder(root);
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course ) {
    // Implement inserting a course into the tree
    // if root equal to null ptr, empty tree
    if (root == nullptr) {
        // root is equal to new node course
        root = new Node(course);
    // else
    }else{
    // add Node root and course
        this->addNode(root,course);
    }    
}


/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseNumber) {
    // Implement searching the tree for a course
    // set current node equal to root
    Node*current = root;
    //while current node is not empty
    while(current != nullptr){
        // keep looping downwards until bottom reached or matching courseNumber found
        if (current -> course.courseNumber.compare(courseNumber) == 0) {
            // if match found, return current course
            return current ->course;
        }
        // if course is smaller than current node then traverse left
        else if (courseNumber.compare(current->course.courseNumber) <0) {
            current = current -> left;
        }
        // else larger so traverse right
        else {
            current = current -> right;
        }
    }     
    Course course;
    return course;
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course Course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // Implement inserting a course into the tree      
        // if node is larger then add to left
        if (node != nullptr && node->course.courseNumber.compare(course.courseNumber)>0){
            // if no left node
            if (node->left == nullptr){
                // this node becomes left
                node->left = new Node(course);
                return;  
                 // else recurse down the left node    
            }else{        
                this->addNode(node->left, course);
            }
        // else if node is lesser then add to right
        } else if (node != nullptr && node ->course.courseNumber.compare(course.courseNumber)<0){
            // if no right node
             if (node->right == nullptr){
                // this node becomes right
                node->right = new Node(course);
                return;
            //else      
            }else{
                 // recurse down the right node
                this->addNode(node->right, course);
            }
        }
}
void BinarySearchTree::inOrder(Node* node) {
      //In order root   
      //if node is not equal to null ptr
    if (node != nullptr) {
         //InOrder left
        inOrder(node->left);
         //output courseNumber, courseName, coursePrerequisites
        cout << node ->course.courseNumber <<" , "<<node->course.courseName <<endl;
        //InOder right
        inOrder(node->right);  
      }
}
//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the course information to the console
 * @param course struct containing the course info
 */
void displayCourse(Course course) {
	 cout << course.courseNumber << ", " << course.courseName << endl; //default format for course list display per sample program output
    cout << "Prerequisites: ";

    //If no prerequisite, notify user
    if (course.coursePrerequisites.size() == 0) {
        cout << "None";
    }
    else {
        //Prints prerequisite at index zero
        cout << course.coursePrerequisites.at(0);

        //Starts at index 1 and prints any additional prerequsites, without we get out of range error
        for (unsigned int i = 1; i < course.coursePrerequisites.size(); ++i) {
            cout << ", " << course.coursePrerequisites.at(i);
        }
    }
    return;
}

/**
*trim function to takes a string as an input and removes any whitespace characters 
*from the beginning and end of the string. It then returns the trimmed string.
*references: https://stackoverflow.com/questions/216823/how-to-trim-an-stdstring
*/
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r"); //find_first_not_of give the index of the first non-whitespace character in the string 
    if (first == string::npos) { //if no non-whitespace characters in the string                            
        return ""; //return empty string
    }
    size_t last = str.find_last_not_of(" \t\n\r"); //find string containing all last non-whitespace characters 
    return str.substr(first, (last - first + 1)); //returns the trimmed string wihout white space
}

// split function to split string by delimiter and return as vector of strings
//references: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
vector<string> split(const string& s, const char delimiter) {
    vector<string> tokens; //declares a vector of strings to hold tokens
    stringstream ss(s); //creates a stringstream object initialized with the input string s
    string token; //declares a string variable token to hold each token as it is extracted
    while (getline(ss, token, delimiter)) { //loop that reads tokens from the stringstream ss using the getline function
        token = trim(token); // remove leading and trailing whitespace
        tokens.push_back(token); //adds the resulting token to the tokens vector using the push_back function.
    }
    return tokens; //returns the tokens vector containing the trimmed tokens.
}

/** read and parse CSV file
* @param csvPath path to csv file
* @return file content in a vector
*/
vector<vector<string>> readFile(const string& csvPath) {
    vector<vector<string>> data; //declares a vector of vectors of strings to hold the data read from the CSV file
    ifstream csvFile(csvPath); //creates an input file stream object csvFile and opens the CSV file located at the given csvPath.
    if (!csvFile.is_open()) { //check if successfully open the file
        throw runtime_error("Failed to open file: " + csvPath); //throw error if not able to open
    }
    string line; //declares a string variable line to hold each line read from the CSV file.
    while (getline(csvFile, line)) { //loop that reads each line from the CSV file using the getline function
        if (!line.empty()) { //if line not empty
            vector<string> row = split(line, ','); // splits the line into tokens using the split function and a delimiter character ,.
            data.push_back(row); //add resulting tokens to a new vector row.
        }
    }
    csvFile.close(); //close file after done to prevent corrupt
    return data; //return data read
}
/**
 * Load a CSV file containing courses into a container
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the courses read
 * load courses from CSV file into binary search tree
 * */
void loadCourses(const string& csvPath, BinarySearchTree* node) {
    vector<string> courseTitles;
    try {
        // read file file
        vector<vector<string>> Data = readFile(csvPath);
           // extract course titles
           // Loop iterates through each row of data in Data vector to extract the course titles.
        for (unsigned int i = 0; i < Data.size(); ++i) {
            vector<string> row = Data.at(i);
            if (row.size() >= 2) {
                courseTitles.push_back(row.at(0)); // extract course titles
            }
        }
        for (unsigned int i =0; i < Data.size(); ++i) {// loop iterates through each row of data in the data vector to extract 
            vector<string> row = Data.at(i);
            if (row.size() < 2) { //If row have less than two elements
            cout << "Error File Format"; //Prints an error message and break
            break;
            }
            else if (row.size() >= 2) { //else
                Course course;

                //add course number to beginning of the row
                course.courseNumber = row.at(0); 

                //add course name second
                course.courseName = row.at(1);

                //add prerequisite after that if exist
                for (unsigned int i = 2; i < row.size(); ++i) { //loop through and find any elements after 2, will be prerequisites
                    if (find(courseTitles.begin(), courseTitles.end(), row.at(i)) != courseTitles.end()) {
                        course.coursePrerequisites.push_back(row.at(i)); //add prerequisites if exist
                    }
                }

                // insert into binary search tree
                node->Insert(course);
            }
        }
    }
    //prints the error message to the standard error stream (cerr) if an exception was caught during the file reading process.
    catch (const exception & e) {  
        cerr << e.what() << endl;
    }


}

/**
 * The one and only main() method
 */

int main() {
  BinarySearchTree*node = new BinarySearchTree();

  Course course;
  //declare variables
  string fileName;
  string userInput; 
  int choice = 0;
    cout << "Welcome to the course planner."<<endl;

//loop to print a menu
  while (choice != 9) {
    cout << "1. Load Data Structure" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course" << endl;
    cout << "9. Exit" << endl;

    cout << "What would you like to do? ";
    cin >> choice;

    switch (choice) {
    //choice 2 will load the file
    case 1:
            cout << "Enter the file name: (hint: Course.csv)" << endl;
            //Holds user input
            cin >> fileName;
			// call file loading function
			loadCourses(fileName, node); //call load course function
			break;

    //choice 2 will print out a sorted list of courses
    case 2:
            cout << "Here is a sample schedule: " << endl;
            cout << endl;
            node->InOrder(); //call sort function
            cout <<endl;
            break;

    //choice 3 will print out information display of a specific couse
    case 3:
            cout << "What course do you want to know about?" << endl;
            cin >> userInput; //save userInput

            //converts lowercase to uppercase for user convinience.
            //reference https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/
            transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);        

            //passes the searched course into the search method
            course = node->Search(userInput); 

            if (!course.courseNumber.empty()) {
            displayCourse(course); //call function display course passing variable course
            cout << endl; 
            }
            else {
                cout << "Course " << userInput << " not found."; //display message if course not found
            }
            cout << endl;
            break;

    //choice 9 to exit
    case 9:
            cout << "Thank you for using the course planner!" << endl;
            exit(0);
    default:
            cout << choice << " is not a valid option." //any choice that is not 1,2,3, or 9
           << endl;
         }
    }  while (choice != 9); //if choice not 9
    return 0;
}