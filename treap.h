//The Error are because variables are declared in main()
#include<bits/stdc++.h>
#include <cstdlib>
#include<fstream>
#include <ctime>
using namespace std;

static int node_id = 0;    
class TreapNode  { 
   private:
      int data;           
      int priority;
      int nodeID ;
      int ht ;
      TreapNode* left, *right;
      friend class treap;
   public:
      TreapNode(int _data) {
         data = _data;
         priority = rand() % INT_MAX ;
         left = right = nullptr;
         ht = 0;
      }
      
};

class treap{
    private: 
     void rotRight(TreapNode* &treap_root);
     void rotLeft(TreapNode* &treap_root);
     bool search(TreapNode* treap_root, int data);
     void insert(TreapNode* &treap_root, int data);
     void Delete(TreapNode* &treap_root, int data);
     void inorder(TreapNode* treap_root);
     void print(TreapNode* treap_root ,const std::string& name);
     void deleteTree(TreapNode* treap_root);  // This will be called by the destructor
     int height(TreapNode* treap_root);
     int total_nodes(TreapNode* treap_root);
     int Sum_ht(TreapNode* treap_root);
     double avg_ht(TreapNode* treap_root);
    public:
      TreapNode* treap_root;
     treap(){
         treap_root = nullptr ;
     };
     int height(){return height(treap_root);}
     bool search(int data){return search(treap_root , data);}  //wrapper functions! will be called by main()
     void insert(int data){insert(treap_root , data);}
     void Delete(int data){Delete(treap_root , data);}
     void inorder(){inorder(treap_root);}
     void print(const std::string& name){ print(treap_root , name);}
     int total_nodes(){return total_nodes(treap_root);}
     int Sum_ht(){return Sum_ht(treap_root);}
     double avg_ht(){return avg_ht(treap_root);}

     friend class TreapNode;
     ~treap();            
};

void treap::rotLeft(TreapNode* &treap_root) { //left rotation
   treap_rotations++;
   TreapNode* R = treap_root->right;
   TreapNode* X = treap_root->right->left;
   R->left = treap_root;
   treap_root->right= X;
   treap_root = R;
}
void treap::rotRight(TreapNode* &treap_root) { //right rotation
   treap_rotations++;
   TreapNode* L = treap_root->left;
   TreapNode* Y = treap_root->left->right;
   L->right = treap_root;
   treap_root->left= Y;
   treap_root = L;
}
bool treap::search(TreapNode* treap_root, int data) {

   if (treap_root == nullptr)
      return false;
   if (treap_root->data == data)
      return true;
   if (data < treap_root->data)
      return search(treap_root->left, data);
      return search(treap_root->right, data);
}

void treap::insert(TreapNode* &treap_root, int data) { //insertion
    treap_comparisons++; //count of key comparsions. Since it is recursive method ,so increments this at each func call.

   if (treap_root == nullptr) {
      treap_root = new TreapNode(data);
      return;
   }

   if(data == treap_root->data){
      return ;
    }

   else if (data < treap_root->data) {
      insert(treap_root->left, data);
      if (treap_root->left != nullptr && treap_root->left->priority < treap_root->priority)//
      rotRight(treap_root);

   } 
   else {
      insert(treap_root->right, data);
      if (treap_root->right!= nullptr && treap_root->right->priority < treap_root->priority)//
      rotLeft(treap_root);
   }
}

void treap::Delete(TreapNode* &treap_root, int data) {
   treap_comparisons++;
   
   if (treap_root == nullptr ){
      return;
   }
   if (data < treap_root->data)
      Delete(treap_root->left, data);
   else if (data > treap_root->data)
      Delete(treap_root->right, data);
      //TreapNode to be deleted which has two children
   else {
      if (treap_root->left ==nullptr && treap_root->right == nullptr) {
         delete treap_root;
         treap_root = nullptr;
      }
      else if (treap_root->left && treap_root->right) {
         if (treap_root->left->priority > treap_root->right->priority) {//
            rotLeft(treap_root);
            Delete(treap_root->left, data);
         } else {
            rotRight(treap_root);
            Delete(treap_root->right, data);
         }
      }
      //TreapNode to be deleted has only one child
      else {
         TreapNode* child = (treap_root->left)? treap_root->left: treap_root->right;
         TreapNode* curr = treap_root;
         treap_root = child;
         delete curr;
      }
   }
}


void treap::deleteTree(TreapNode* treap_root) //deleting all nodes recursively 
{
    if (treap_root == NULL)return;

    // first delete both subtrees 
    deleteTree(treap_root->left);
    deleteTree(treap_root->right); 
    //then delete the TreapNode 
    delete treap_root;
}
treap::~treap(){                    // calling deleteTree on treap_root of tree 
   deleteTree(treap_root);
   delete treap_root;
}

int treap::height(TreapNode* treap_root)
{
    if (treap_root == NULL)
        return 0;
    else
    {
     int lDepth = height(treap_root->left);
     int rDepth = height(treap_root->right);
     treap_root->ht = lDepth + rDepth ;

     
     if (lDepth > rDepth)
         return(lDepth + 1);
     else return(rDepth + 1);
    }
}

int treap::total_nodes(TreapNode* treap_root){
   if (treap_root == NULL)
        return 0;

     return 1 + total_nodes(treap_root->left) + total_nodes(treap_root->right);
}

int treap::Sum_ht(TreapNode* treap_root){
   if (treap_root == NULL)
        return 0;
    return (treap_root->ht + Sum_ht(treap_root->left) + Sum_ht(treap_root->right));
}

double treap::avg_ht(TreapNode* treap_root){
   double avg = Sum_ht(treap_root)*1.0/ total_nodes(treap_root); 
   return avg;
}
