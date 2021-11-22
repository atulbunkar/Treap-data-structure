#include<bits/stdc++.h>
#include <cstdlib>
#include<fstream>
#include <ctime>
using namespace std;

static int treap_comparisons = 0;   //total no. key comparisions done
static int treap_rotations = 0 ;    //total no. of rotations done

static int node_id = 0;    
class TreapNode{ 
   private:
      int key;           
      int priority;  //Store priority. I followed min heap , so less priority nodes are parent of larger priority nodes.
      int nodeID ;
      TreapNode* left, *right;
      friend class treap;
   public:
      TreapNode(int _data){
         key = _data;
         priority = rand() % INT_MAX ; //to give a random priority btw 0-INT_MAX
         left = right = nullptr;
         nodeID = node_id++;         // Used in printing tree. Gives unique ID to each node
   }
      
};

class treap{
    private: 
     void rotRight(TreapNode* &node);
     void rotLeft(TreapNode* &node);
     bool search(TreapNode* node, int key);
     void insert(TreapNode* &node, int key);
     void Delete(TreapNode* &node, int key);
     void print(TreapNode* node ,const std::string& name); //print png image of tree.
     void deleteTree(TreapNode* node);  // This will be called by the destructor
    public:
      TreapNode* node;
     treap(){
         node = nullptr ;
     };
     //wrapper functions!
     bool search(int key){return search(node , key);}  
     void insert(int key){insert(node , key);}
     void Delete(int key){Delete(node , key);}   
     void print(const std::string& name){ print(node , name);} 
     friend class TreapNode;
     ~treap();            
};


void treap::insert(TreapNode* &node, int key){ //insertion
    treap_comparisons++; //count of key comparsions. Since it is recursive method ,so increments this at each func call.

   if (node == nullptr) {  //insert node when null found
      node = new TreapNode(key);
      return;
   }

   else if(key == node->key){ //if same key found
      cout<< "Element already exist !\n";
      return ;
    }

   else if (key < node->key) {      //if key to insert is smaller than current , go left.
      insert(node->left, key);
      if (node->left != nullptr && node->left->priority < node->priority){ 
         rotRight(node);          //if priority of left child by bigger , rotate tree anticlockwise
      }

   } 
   else {                     //else go right.
      insert(node->right, key);
      if (node->right!= nullptr && node->right->priority < node->priority){ 
         rotLeft(node);       //if priority of right child is bigger , rotate tree clockwise
      }
   }
   
}

void treap::Delete(TreapNode* &node, int key) {
   treap_comparisons++;

   //finding node to delete
   if(node == nullptr ){                  //if element is not found
      cout<< "Element does no exist !!\n";
      return;
   }
   
   if (key > node->key){             // if key to delete is bigger , go right 
      Delete(node->right, key);
   }

   else if(key < node->key){         // if key to delete is smaller , go left 
      Delete(node->left, key);
   }

   //key found , now to delete it based on its no of child.
   else {
      //node to  delete has two children
      if(node->left && node->right) {

         if (node->left->priority < node->right->priority)  {
            rotRight(node);   //left child has higher priority than right , make left child parent of right
            Delete(node->right, key);
         }

         else{
            rotLeft(node);    //else the opposite.
            Delete(node->left, key);
         } 
      }

      //node to delete has no child
      else if (node->right == nullptr and node->left ==nullptr) {
         delete node;      //simply delete the node
         node = nullptr;
      }

      //node to be deleted has only one child
      else {
         TreapNode* child;
         if(node->left){      //check which child it has and allot that to "child".
           child =  node->left;
         }
         else{
            child =  node->right;
         }

         TreapNode* temp ;
         temp = node;      //store node to delete in temp
         node = child;     //set the child in place of node to delete
         delete temp;      //delete temp aka actual node to delete.
      }
   }
}

bool treap::search(TreapNode* node, int key) {

   if (node == nullptr){     //if not present in tree(it's recursive function)
      return false;
   }

   if (node->key == key){   //node found
      return true;
   }

   else if(key > node->key){
      return search(node->right, key);   //key is bigger than current node key
   }

   else {
      return search(node->left, key);   //key is smaller than current node key
   } 
}


void treap::rotRight(TreapNode* &node) {  //rotates the tree clock wise with node as pivot
   treap_rotations++;
   TreapNode* Y = node->left->right;
   TreapNode* L = node->left;
   
   node->left= Y;    //anything right of node's left child is now node's left child
   L->right = node;  //node becomes right child of its left child
   node = L;         //left child of node is now the node
}

void treap::rotLeft(TreapNode* &node) { //rotates the tree anticlock wise with node as pivot
   treap_rotations++;

   TreapNode* X = node->right->left;
   TreapNode* R = node->right;

   node->right = X;      //anything left of node's right child is now node's right child
   R->left = node;      //node becomes left child of its right child
   node = R;            //right child of node is now the node
}


void treap::print(TreapNode* node, const std::string& name){
    ofstream myfile;
    myfile.open(name); 

    queue<TreapNode*> nodes;      //Needed for Level order traversal of the tree

    nodes.push(node);

    myfile<<"digraph G{\n" ;                      //DOT code.
    myfile<<"node[shape=record];\n" ;

    while(!nodes.empty()){
        TreapNode* cur =  nodes.front(); 
         nodes.pop(); 
        //Code for node key, fills node in format : left ptr|| key || node's balance factor || right ptr 
        //bf is height of left subtree - height of right subtree

        myfile<< cur->nodeID<<"[label = \"<f1>  "<< "|<f2> key: "<< cur->key  << " |<f3>  priority: " << cur->priority << " |<f4>   " << " \"] \n"; 

        //code for edge key. Tells which node is connected to which node
        if(cur->left){
            myfile<< cur->nodeID << ":f1 -> " << cur->left->nodeID << endl; 
            nodes.push(cur->left); // stores next nodes to queue
        }
        if(cur->right){
             myfile<< cur->nodeID << ":f4 -> " <<cur->right->nodeID <<endl;
             nodes.push(cur->right);
         }
    }
    myfile<< "}\n";
    myfile.close();

    //cmd line to convert gv file to png
    string cmd = "dot.exe -Tpng "+ name + " -o " + name + ".png";  
    system((const char*)cmd.c_str());
}

void treap::deleteTree(TreapNode* node) //deleting all nodes recursively 
{
    if (node == NULL)return;

    // first delete both subtrees 
    deleteTree(node->left);
    deleteTree(node->right); 
    //then delete the node 
    delete node;
}
treap::~treap(){                    // calling deleteTree on root of tree 
   deleteTree(node);
}

int main(){
   int cmd;
   int element;
   string name;
   treap* tree = new treap() ;
   srand(time(NULL));
   while (1) {
      cout << "\n-------------------------TREAP MENU-------------------------------------- \n\n";
      

      while(1){
         cout<<"Enter one of the following choice(int) :\n1 -> to insert element \n2 -> to delete element \n3 -> to search an element \n4 -> to print tree png \n5 ->To exit the program\n";
         cin >> cmd;
         while(cin.fail()) {
           cout << "Enter only Interger !!"  << std::endl;
           cin.clear();
           cin.ignore(256,'\n');
           cin >> cmd;
         }
        break;
      }
      
      if (cmd == 1){
         while(1){
            cout<< "Enter Element to insert or 'q' to stop inserting : ";
            cin >> element;
            if(!cin.fail()){
               tree->insert(element);
            }

            else if(cin.fail()) {
              cout << "Exiting insert operation !\n" ;
              cin.clear();
              cin.ignore(256,'\n');
              break;
            }
         }
      }
         
      else if (cmd == 2){
         cout<< "Enter Element to delete : ";
         cin >> element;
         if(!cin.fail()){
            tree->Delete(element);
         }

         while(cin.fail()) {
           cout << "Enter only Interger !!"  << std::endl;
           cin.clear();
           cin.ignore(256,'\n');
           cin >> element;
         }
      }
      else if(cmd == 3){
         cout<< "Enter Element to search : ";
         cin>>element;

         if(!cin.fail()){ 
         bool res ;
         res = tree->search(element);
         if(!res)
            cout<<endl << element <<" Not present in treap !!\n";
         else
            cout<<endl << element <<" is present in treap !!\n";
         }
         
        while(cin.fail()) {
           cout << "Enter only Interger" << std::endl;
           cin.clear();
           cin.ignore(256,'\n');
           cin >> element;
         }

      }
      else if(cmd == 4){
         cout<< "Enter any filename to create image file(without .png)\n";
         cin>> name;
         cout << "See the tree in " << name << ".png file created\n" ;
         tree->print(name); 
         cout << endl;
      }
      else{
         cout<< "Freeing the memory!!!\n ";
         delete tree;
         cout<< "!!! Exiting the program !!! \n";
         break;       //breaks on any other input
      }
      cout << endl;  
   }
   return 0;
}