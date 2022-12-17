
#pragma once


//Imported libraries

#include <sstream>

#include <string>

#include <fstream>

#include <unordered_map>

#include "hashmap.h"

#include <map>

#include <vector>

#include <cctype>

#include "mainprog.h"



using namespace std;


typedef hashmap hashmapF;

typedef unordered_map <int, string> hashmapE;


struct HuffmanNode {

    int character;

    int count;

    HuffmanNode* zero;

    HuffmanNode* one;

};


struct compare

{

    bool operator()(const HuffmanNode *lhs,

        const HuffmanNode *rhs)

    {

        return lhs->count > rhs->count;

    }

};



//Jumpstart

/*class prioritize  // you could also use a struct

{

public:

  bool operator()(HuffmanNode*  p1, HuffmanNode*  p2) const

  {

    return p1 -> count > p2 -> count;  // HuffmanNode* will be different

  }

};*/



//Step 1: *This method frees the memory allocated for the Huffman tree.

void freeTree(HuffmanNode* node) {


Instructor
| 11/30 at 9:19 am
Grading comment:

This is a needlessly complicated recursive implementation. There is absolutely no need for the try-catch block.

    int choice;

    

    try{

        if(node == nullptr){

            choice = 1;

            throw choice;

        }

        else{

            choice = 2;

            throw choice;

        }

    }

    catch(int choice){

        if(choice == 1){

            return;

        }

        else{

            freeTree(node -> zero);

            freeTree(node -> one);

            delete node;

        }

    }

}



//Helper function to display the result if the condition of the isFile is false

void displayMap(string filename, bool isFile, hashmapF &map){

   

   int saveValue, modValue;

   if(isFile == false){

      for(char c: filename){

         if(map.containsKey(c) == false){

            map.put(c, 1);

         }

         else{

            saveValue = map.get(c);

            modValue = saveValue + 1;

            map.put(c, modValue);

            //Add this manually => Jumpstart

            //map.put(PSEUDO_EOF, 1);

         }

      }

   }

}

            

            


//

// *This function build the frequency map.  If isFile is true, then it reads

// from filename.  If isFile is false, then it reads from a string filename.

//

void buildFrequencyMap(string filename, bool isFile, hashmapF &map) {

   

   //Step 1: declare variables' names

   ifstream userFile;

   char target;

   string fileContents;

   int saveValue, modValue;

   

   //Step 2: check if the condition is true => read from filename => Jumpstart

   if(isFile == true){

      ifstream userFile(filename);

      

      //Step 3: Get the key and store it inside the target

      while(userFile.get(target)){

         

         //Step 4: Check if the hashmap contains the key or not

         if(map.containsKey(target) == true){

            saveValue = map.get(target);

            modValue = saveValue + 1;

            map.put(target, modValue);

         }

         else{

            map.put(target, 1);

         }

      }

   }

   else{

      displayMap(filename, isFile, map);

   }

    //Add this manually => Jumpstart

   map.put(PSEUDO_EOF, 1);

}



//Jumpstart

/*{

public:

  bool operator()(const pair<int,int>& p1, const pair<int,int>& p2) const

  {

    return p1.second > p2.second;  // HuffmanNode* will be different

  }

};*/



HuffmanNode* converter(priority_queue< HuffmanNode*, vector<HuffmanNode*>, compare> &pq){

   

   int size = pq.size();

   

   /*

   Get top node, call it first pop

   Pop

   Get top node, call it second pop

   Pop

   Make new node, zero child is first pop, one child is second pop (always)

   Enqueue new node

   */

   

   for(int i = size; i > 1; i--){

      //Step 1: take 2 nodes from the front of the queue => remove them

      HuffmanNode* childNode1 = pq.top();

      pq.pop();

      HuffmanNode* childNode2 = pq.top();

      pq.pop();

      /*int j = 0;

      while(j < 2){

         pq.pop();

         j++;

      }*/

      

      //Step 2: create a node where frequency is the sum => sum = count from both nodes => OH

      //NOT_A_CHAR = 257

      HuffmanNode* freqNode = new HuffmanNode();

      int sum1 = childNode1 -> count;

      int sum2 = childNode2 -> count;

      freqNode -> zero = childNode1;

      //int sum1 = childNode1 -> count;

      freqNode -> one = childNode2;

      //int sum2 = childNode2 -> count;

      freqNode -> character = NOT_A_CHAR;

      freqNode -> count = sum1 + sum2;

      

      

      //Step 3: enqueue the new node

      pq.push(freqNode);

   }

   

   return pq.top();

}



// *This function builds an encoding tree from the frequency map.

HuffmanNode* buildEncodingTree(hashmapF &map) {

   

   /*Step 1: place our counts into node structs (out of which we will build the binary tree); 

   each node stores a character and a count of its occurrences.

   zero => left

   one => right 

   */

    

   //Step 1: create a priority queue => Jumpstart

   vector <int> huffmanVector;

   //priority_queue<HuffmanNode*> pq;

   priority_queue< HuffmanNode*, vector<HuffmanNode*>, compare> pq; 

   //priority_queue< HuffmanNode*, vector<pair<int,int>>, prioritize> pq; 

   

   if(huffmanVector.size() == 0){

      huffmanVector = map.keys();

      int size = huffmanVector.size();

      int i = 0;

      

      //Check the jumpstart => DONE

      for(auto c: huffmanVector){

         HuffmanNode* current = new HuffmanNode();

         current -> count = map.get(c);

         current -> character = c;

         current -> zero = nullptr;

         current -> one = nullptr;

         pq.push(current);

      }

   }

   else{

      huffmanVector = huffmanVector;

   }

   

   int size = pq.size();

   while(size > 1){

      converter(pq);

      size--;

   }

   

   return pq.top();  

}



void recursiveTraversal(HuffmanNode* node, hashmapE &encodingMap, string str){}




// *Recursive helper function for building the encoding map.

void _buildEncodingMap(HuffmanNode* node, hashmapE &encodingMap, string str,

                       HuffmanNode* prev) {

    

    /*

    Building encoding map...

      256: 	EOF	-->	110

      32: 	' '	-->	111

      97: 	'a'	-->	10

      98: 	'b'	-->	01

      10: 	'\n'	-->	001

      99: 	'c'	-->	000

    */

    

    //Check project 5

    //str = " ";

    //string temp = " ";

    

    //Step 1: if the encoding tree is empty => return an empty map

    if(node == nullptr){

       return;

    }

    else{

       //Use the condition of a leaf node from the jumpstart => put to the encodingMap: node -> char + string (TA)

       if(node -> character != NOT_A_CHAR){

          //LEAF_NODE!

          int target = node -> character;

          //Hit a leaf? Node -> char, str @Jumpstart

          //encodingMap.put(target, str);

          //@https://cplusplus.com/reference/unordered_map/unordered_map/

          //Since we use an unordered map, the use if emplace is legal

          encodingMap.emplace(target, str);

          return;

       }

       else{

         //Base case

         if (node -> zero == nullptr && node -> one == nullptr) {

            //_buildEncodingMap(node -> character, encodingMap, str, prev);

            return;

         }

         //Recursive case

         if (node -> zero != nullptr) {

            //str += "0";

            _buildEncodingMap(node -> zero, encodingMap, str += "0", prev);

             str.pop_back();

         }

         if (node -> one != nullptr) {

            //str += "1";

            _buildEncodingMap(node -> one, encodingMap, str += "1", prev);

             str.pop_back();

         } 

      }  

   }

}



//

// *This function builds the encoding map from an encoding tree.

//

hashmapE buildEncodingMap(HuffmanNode* tree) {

   

    hashmapE encodingMap;

    HuffmanNode* node = tree;

    HuffmanNode* prev = nullptr;

    string temp = "";

    /*

      if (node -> zero == nullptr && node -> one == nullptr) {

         //_buildEncodingMap(node -> character, encodingMap, str, prev);

         return;

      }

         

      //Recursive case

      if (node -> zero != nullptr) {

         //str += "0";

         _buildEncodingMap(node -> zero, encodingMap, str += "0", prev);

         str.pop_back();

      }

      if (node -> one != nullptr) {

         //str += "1";

         _buildEncodingMap(node -> one, encodingMap, str += "1", prev);

         str.pop_back();

      } 

    */

    _buildEncodingMap(node, encodingMap, temp, prev);

    

    return encodingMap; 

}



//

// *This function encodes the data in the input stream into the output stream

// using the encodingMap.  This function calculates the number of bits

// written to the output stream and sets result to the size parameter, which is

// passed by reference.  This function also returns a string representation of

// the output file, which is particularly useful for testing.

//

string encode(ifstream& input, hashmapE &encodingMap, ofbitstream& output,

              int &size, bool makeFile) {

    

    string temp = "";

    char fileContents;

    int bits = 0;

    

     while (input.get(fileContents)) {

        //string temp += encodingMap.get(fileContents);

         temp += encodingMap[fileContents];

     }

        //Manually add Pseudo_EOF => Jumpstart

        temp += encodingMap[PSEUDO_EOF];

        

        if(makeFile == true){

            for (auto i : temp) {

               if(i == '0'){

                  output.writeBit(0);

                  //temp += '0';

               }

               else{

                  output.writeBit(1);

                  //temp += "1";

               }

            }

        }

        

        //Update the size after iteration

        size = temp.size();

    //}

    

    //Step 1: encode the data in the input stream

    /*do{

       

      //temp+= encodingMap.get(atoi(fileContents));

      

    }while(input.get(fileContents));

    

    if(makeFile){

       

       

    }

    else{

      

    }*/

    

    //Return the new string

    return temp;  

}



//

// *This function decodes the input stream and writes the result to the output

// stream using the encodingTree.  This function also returns a string

// representation of the output file, which is particularly useful for testing.

//

string decode(ifbitstream &input, HuffmanNode* encodingTree, ofstream &output) {

    

    string result;

    bool driver = false;

    HuffmanNode* curr = encodingTree;

    

    //Jumpstart

   while (!input.eof()){

      int bit = input.readBit();

      //HuffmanNode* curr = encodingTree;

      

      //Check if the bit must goe to the left or right

      try{

         if(bit == 0){

            curr = curr -> zero; //Left

         }

         else{

            throw 1;

         }

      }

      catch(int e){

         if(e == 1){

            curr = curr -> one; //Right

         }

         else{

            curr = curr -> zero;

         }

      }

      

      //Check the special case => Jumpstart

      try{

         //Marker to break the loop

         if(curr -> character == PSEUDO_EOF){

            curr = encodingTree;

            break;

         }

         else{

            throw driver;

         }

      }

      catch(bool e){

         if(e == false && curr -> character != NOT_A_CHAR){

            result += curr -> character;

            curr = encodingTree;

         }

      }

   }

   

   //cout << result << endl;

               

    

    return result;  

}



//Helper function to build a filename with .huf

string fileBuilder(string filename){

   

   string temp;

   temp = filename;

   

   /*if(temp.find(".huf") != string::npos){

      temp += ".huf";

   }*/

   

   return temp += ".huf";

}

   


//

// *This function completes the entire compression process.  Given a file,

// filename, this function (1) builds a frequency map; (2) builds an encoding

// tree; (3) builds an encoding map; (4) encodes the file (don't forget to

// include the frequency map in the header of the output file).  This function

// should create a compressed file named (filename + ".huf") and should also

// return a string version of the bit pattern.

//

string compress(string filename) {

    

    //Declare the required variables

    hashmap freqMap; //Step 1 => used for building a frequency map

    string result; //Step 2 => builds an encoding tree

    hashmapE encodingMap; //Step 3 => builds an encoding map

    int size = 0; //For encode function

    ifstream userFile(filename);

    string temp;

    string fileContents;

    bool driver = true;

    HuffmanNode *curr;

    temp = fileBuilder(filename);

    //cout << "THE CURRENT FILENAME: " << temp << endl;

    //ofbitstream output("belgian_waffle.txt.huf");

    ofbitstream output(temp);

    

    /*

    1. belgian_waffle.txt

    2. ofbitstream output("belgian_waffle.txt.huf");

    3. output << frequencyMap;

    4. Call Encode: ifstream input("belgian_waffle.txt");

    5. Return the result => type string

    */

    


   //Step 1: check if the file is open

   try{

       if(userFile.is_open()){

          //Step 2: construct the frequency map using the function

         buildFrequencyMap(filename, driver, freqMap);

         

         //Step 3: if true => build the encoding tree using the freqMap

         curr = buildEncodingTree(freqMap);

         

         //Step 4: Build the map for hashMapE if true

         encodingMap = buildEncodingMap(curr);

         

         //Step 5: output << frequencyMap @Jumpstart

         output << freqMap;

         size = 0;

         result = encode(userFile, encodingMap, output, size, driver);

         freeTree(curr);

         throw 1;

       }

       else{

         throw 0;

       }

   }

   catch(int e){

      if(e == 1){

         return result;

      }

      else{

         return "";

      }

   }

}



//Helper function to clean the provided token and modify it as requested

string eraser(string& filename, bool driver){

   

   string target = ".txt.huf";

   string copy = filename;

   size_t index = copy.find(target);

   int length = copy.length();

   

   if(driver == true && index != string::npos){

      copy.erase(index, length);

      //int loc = copy.find(".txt.huf");

      //copy.erase(loc);

   }

   //else{

      //copy = filename;

   //}

   

   copy += "_unc.txt";

   

   return copy;

}



//

// *This function completes the entire decompression process.  Given the file,

// filename (which should end with ".huf"), (1) extract the header and build

// the frequency map; (2) build an encoding tree from the frequency map; (3)

// using the encoding tree to decode the file.  This function should create a

// compressed file using the following convention.

// If filename = "example.txt.huf", then the uncompressed file should be named

// "example_unc.txt".  The function should return a string version of the

// uncompressed file.  Note: this function should reverse what the compress

// function did.

//

string decompress(string filename) {

    

    //Declare the required variables

    hashmapF freqMap; //Used for building a frequency map

    hashmapE encodingMap; //Builds an encoding map

    string cleanedCopy;

    bool driver = true;

    HuffmanNode *curr; //Builds an encoding tree

    

    //prepare an input bit stream from the .huf file given

    ifbitstream userFile(filename);

    int loc = filename.find(".txt.huf");

    filename.erase(loc);

    string temp;

    temp = filename;

    temp = eraser(temp, driver);

    //cout << "THE ORIGINAL FILENAME WAS: " << filename << endl;

    //printTextFile(filename);

    //cout << "THE CLEANED FILENAME IS: " << endl;

    //cout << "THE CURRENT FILENAME IS: " << temp << endl;

   

    //prepare an output stream to a new file you will make

    ofstream output(temp);

    string decompressed; 

    

    

    //curr = buildEncodingTree(freqMap);

    

    //Step 1: check if the file is open

   try{

      

          //Step 2: construct the frequency map using the function

         userFile >> freqMap;

         //buildFrequencyMap(temp, driver, freqMap);

         

         //Step 3: if true => build the encoding tree using the freqMap

         curr = buildEncodingTree(freqMap);

         

         if(curr -> character == PSEUDO_EOF){

            throw 0;

         }

         else{

            decompressed = decode(userFile, curr, output);

            output.close();

            freeTree(curr);

            throw 1;

         }

   }

   catch(int e){

      if(e == 1){

         return decompressed;

      }

      else{

         return "";

      }

   }

    

   return string(decompressed);  

}


