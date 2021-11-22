//The Error are because variables are declared in main()
#include<iostream>
using namespace std;

class BST {
    struct bst_node {
        int key;
        bst_node* left;
        bst_node* right;
        int ht;
    };

    bst_node* bst_root;

    bst_node* deletetree(bst_node* t) {
        if(t == NULL)
            return NULL;
        {
            deletetree(t->left);
            deletetree(t->right);
            delete t;
        }
        return NULL;
    }

    bst_node* insert(int node, bst_node* t)
    {
        bst_comparisons++;
        if(t == NULL)
        {
            t = new bst_node;
            t->key = node;
            t->left = t->right = NULL;
        }
        else if(node == t->key){
            return t;
        }
        else if(node < t->key){
            t->left = insert(node, t->left);
        }
        else if(node > t->key){
            t->right = insert(node, t->right);
        }
        return t;
    }

    bst_node* findMin(bst_node* t)
    {
        bst_comparisons++;
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else{
            return findMin(t->left);
        }
    }

    // bst_node* findMax(bst_node* t) {
    //     if(t == NULL)
    //         return NULL;
    //     else if(t->right == NULL)
    //         return t;
    //     else
    //         return findMax(t->right);
    // }

    bst_node* Delete(int node, bst_node* t) {
        bst_comparisons++;
        bst_node* temp;
        if(t == NULL){
            return NULL;
        }
        else if(node < t->key){
            t->left = Delete(node, t->left);
        }
        else if(node > t->key){
            t->right = Delete(node, t->right);
        }
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->key = temp->key;
            t->right = Delete(t->key, t->right);
        }
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }

        return t;
    }

    bst_node* Search(bst_node* t, int node) {
        if(t == NULL)
            return NULL;
        else if(node < t->key)
            return Search(t->left, node);
        else if(node > t->key)
            return Search(t->right, node);
        else
            return t;
    }

    int height(bst_node* _root)
    {
        if (_root == NULL)
            return 0;
        else
        {
            int lDepth = height(_root->left);
            int rDepth = height(_root->right);
            _root->ht = lDepth + rDepth;
          
            if (lDepth > rDepth)
                return(lDepth + 1);
            else return(rDepth + 1);
        }
    }

    int total_nodes(bst_node* _root){
        if(_root == NULL)
            return 0;

        return 1 + total_nodes(_root->left) + total_nodes(_root->right);
    }
    
    int Sum_ht(bst_node* r){
       if (r == NULL)
            return 0;
        return (r->ht + Sum_ht(r->left) + Sum_ht(r->right));
    }

    double avg_ht(bst_node* r){
       double avg = Sum_ht(r)*1.0/ total_nodes(r); 
       return avg;
    }

    void inorder(bst_node* r){
        if (r == NULL)
        return;
 
        /* first recur on left child */
        inorder(r->left);
     
        /* then print the data of node */
        cout << r->key << " ";
     
        /* now recur on right child */
        inorder(r->right);
    }

    public:
        BST() {
            bst_root = NULL;
        }

        ~BST() {
            bst_root = deletetree(bst_root);
        }

        void insert(int node) {
            bst_root = insert(node, bst_root);
        }

        void Delete(int node) {
            bst_root = Delete(node, bst_root);
        }

        void search(int node) {
            bst_root = Search(bst_root, node);
        }

        int height(){return height(bst_root);}

        int total_nodes(){return total_nodes(bst_root);}

        void inorder(){
            return inorder(bst_root);
        }

        int Sum_ht(){
            return Sum_ht(bst_root);
        }

        double avg_ht(){
            return avg_ht(bst_root);
        }



};
