#include<bits/stdc++.h>
#include <cstdlib>
#include<fstream>
#include <ctime>
using namespace std;

//Evalution parameters
//of treap 
static long int treap_comparisons = 0;    // key comparisons for treap
static long int treap_rotations = 0 ;	 //total rotations done in treap
static int treap_height = 0;			//final height of traeap
static double treap_avg_ht = 0;			//avg ht got from sum of all node's height/total nodes in tree
static int treap_tot_nodes =0 ; 		//total nodes after all operations

//of avl tree
static long int avl_comparisons = 0 ;    //same as above for avl tree
static long int avl_rotations = 0 ;
static int avl_height = 0;
static double avl_avg_ht = 0;
static int avl_tot_nodes =0 ; 

//of BST
static long int bst_comparisons = 0 ;	//same as above for BST tree
static int bst_height = 0;
static double bst_avg_ht = 0;
static int bst_tot_nodes =0 ; 
bool flag;

int total_ops[10];
int idx = 1;

static int cur_nodes;			//store current count of nodes in tree.
static double th_key_comps ;	//store theoretical count of key comparisons done


#include "treap.h"		//includes treap program
#include "bst.h"		//inlcude bst program
#include "avl.h"		//inludes avl program


void Execute(const std::string& test_name){
	treap* Treap = new treap() ;
    BST* Bst = new BST();
    avl_Tree* Avl = new avl_Tree();

    string op;                //operation
    int element , operations ; int c = 2 ;


    ifstream test;
    test.open(test_name); 
    if(!test.is_open()){
    	cout<< "Test file does not exist !!\n Exiting the program !!";
    	flag = false;
    	return;
    }
    flag = true;
    if(getline(test , op))
    	operations = stoi(op);          //store total no of opeartions from first line of test file

    total_ops[idx++] = operations;

    cur_nodes = 1; 						//resetting cur_nodes count and key comps count before running test file.
    th_key_comps = 0 ;

    while(test >> op >> element ) {

	  if(op == "Insert" || op=="insert"){

	  	try{
		  	Treap->insert(element);
		  	Bst->insert(element);
		  	Avl->insert(element);
		}
		catch(int element){
		 	continue;
		}

		cur_nodes++;	//increase node count
	  	th_key_comps += ceil(log2(cur_nodes) ) ;	//theoretically , log(n) key comparisons are done for insertion/deletion
	  	
	  }
	  else if(op == "Delete" || op == "delete"){

	  	try {
	  		Treap->Delete(element);
	  		Bst->Delete(element);
	  		Avl->Delete(element);
	  	}
	  	catch(int element){
	  		continue;
	  	}

	  	if(cur_nodes>1)cur_nodes--;	//decrease node count
	  	th_key_comps += ceil(log2(cur_nodes) );
	  	
	  } 
	}
	//Get height and avg height of nodes of tree.
	treap_height = Treap->height();
	bst_height = Bst->height();
	avl_height = Avl->height();

	treap_avg_ht = Treap->avg_ht();
	bst_avg_ht = Bst->avg_ht();
	avl_avg_ht = Avl->avg_ht();

	treap_tot_nodes = Treap->total_nodes();
	avl_tot_nodes = Avl->total_nodes();
	bst_tot_nodes = Bst->total_nodes();

}


int main(){ 
    //----------------------------------------------------------------------------------------------------------------
    //Executing Test Files 
    cout<< "\n--------Execution of Test Files--------\n";

    int choice ; string name2;
    int tests ; string test_name = "test", final_name ;
    
    
    //To store Evalution paramteres
    int key_comps[10][3] ;   //3 col for 3 trees , one row to store info of one test.
    int rotations[10][3] ;	
    int height[10][3] ;
    double avg_node_height[10][3] ;
    int total_nodes[10][3];
    double th_height[10][3]; //theoretical height
    double th_key_comp[10] ; //theoretical key comparison count.
   
    
    cout<< "\n1. Use your own test file to run the Execute\n2. Use above created 5 test files :\n";
    cout << "Enter a choice(1/2) : ";
    cin>>choice;
    if(choice == 1){  //If TA wants to check with own single test file.
    	cout<< "\nEnter own test file name(including .txt):\n";   
    	cin>> final_name ;
    	tests= 1;
    	Execute(final_name);
    	if(!flag)return 0;	//file not present

    	key_comps[0][0] = treap_comparisons ;	  //storing count of key comparisions
   		key_comps[0][1] = avl_comparisons ;
   		key_comps[0][2] = bst_comparisons ;		 //Col 0 -> treap , col 1 -> avl , col 2 -> bst.

   		rotations[0][0] = treap_rotations ;			//storing rotation count 
   		rotations[0][1] = avl_rotations ;
   		rotations[0][2] = 0 ;				    	//No rotation for BST

   		height[0][0] = treap_height;		      //storing total height of trees
   		height[0][1] = avl_height;
   		height[0][2] = bst_height;

   		avg_node_height[0][0] = treap_avg_ht ;	//storing avg node height
   		avg_node_height[0][1] = avl_avg_ht ;
   		avg_node_height[0][2] = bst_avg_ht ;

   		total_nodes[0][0] = treap_tot_nodes;	//storing total nodes in final tree
   		total_nodes[0][1] = avl_tot_nodes ;
   		total_nodes[0][2] = bst_tot_nodes;

   		th_height[0][0] = floor( log2(treap_tot_nodes) ) ;		//for treap
   		th_height[0][1] = floor( 1.44 * log2(avl_tot_nodes) );  //for avl
   		th_height[0][2] = floor( 4.311*log(bst_tot_nodes) - 1.953*(log(log(bst_tot_nodes))) );	//for bst

   		th_key_comp[0] = th_key_comps ;

    }

    else {		//Else Run with 5 test files created above.
   		cout<< "\nRunning the Test Files on the 3 tree objects \n";
   		tests = 5;
   		for(int i = 1 ; i <= tests; i++){
   			final_name = test_name + to_string(i) +  ".txt";  //get name of test file
   			 //Col 0 -> treap , col 1 -> avl , col 2 -> bst.

	   		Execute(final_name);                  // run operations on test file
	   		//store evalution parameters got from Execute. All are in global variable. 

	   		key_comps[i][0] = treap_comparisons ;	         //storing count of key comparisions
	   		key_comps[i][1] = avl_comparisons ;
	   		key_comps[i][2] = bst_comparisons ;

	   		rotations[i][0] = treap_rotations ;			  //storing rotation count 
	   		rotations[i][1] = avl_rotations ;
	   		rotations[i][2] = 0 ;					    //No rotation for BST

	   		height[i][0] = treap_height;		      //storing total height of trees
	   		height[i][1] = avl_height;
	   		height[i][2] = bst_height;

	   		avg_node_height[i][0] = treap_avg_ht ;	//storing avg node height
	   		avg_node_height[i][1] = avl_avg_ht ;
	   		avg_node_height[i][2] = bst_avg_ht ;

	   		total_nodes[i][0] = treap_tot_nodes;	//storing total nodes in final tree
	   		total_nodes[i][1] = avl_tot_nodes ;
	   		total_nodes[i][2] = bst_tot_nodes;

	   		th_height[i][0] = floor( log2(treap_tot_nodes) ) ;		//for treap - Theoritical height
	   		th_height[i][1] = floor( 1.44 * log2(avl_tot_nodes) );  //for avl
	   		th_height[i][2] = floor( 4.311*log(bst_tot_nodes) - 1.953*(log(log(bst_tot_nodes))) );	//for bst

	   		th_key_comp[i] = th_key_comps ;		//storing theoretical count of key comparisons

	   		treap_comparisons = avl_comparisons = bst_comparisons = treap_rotations = avl_rotations = 0;
	   	}
	}
		
	
//-------------------------------------------------------------

	//Report and Analysis 
	cout<< "\n\n-------------Report Analysis !!-----------------\n\n";

	ofstream myfile;    			 //storing results in text file(for above created test files only)
    myfile.open("Analysis.txt");

	string trees[3] = {"TREAP" , "AVL tree" , "BST" };


	//Output Results of TAs File.
	if(choice ==1){
		cout << "\nAnalysis on the 3 trees from TAs test file : \n\n";
		for(int j = 0 ; j < 3 ;j++){
			cout<< "For " << trees[j] << " total key comparisons(insert+delete) = " << key_comps[0][j] << endl;	
		}
		cout<< endl;

		for(int j = 0 ; j < 3 ;j++){
			cout<< "For " << trees[j] << " total Rotations = " << rotations[0][j] << endl;
		}
		cout<<endl;

		for(int j = 0 ; j < 3 ;j++){
		cout<< "For " << trees[j] << " total height = " << height[0][j] << endl;
		}
		cout<<endl;

		for(int j = 0 ; j < 3 ;j++){
		cout<< "For " << trees[j] << " avg node height = " << avg_node_height[0][j] << endl;
		}
		cout<<endl;

		//
		cout<< "\nTHOERETICAL VS EMPIRICAL COMPARISION : \n";

		cout<< "\n->Treap :\n";
		cout<< "Thoeretical height(log n) : " << th_height[0][0] ;
		cout<< "\nActual Height : " << height[0][0];

		cout<< "\n\n-> AVL tree :\n";
		cout<< "Thoeretical height(1.44 * log(n)) : " << th_height[0][1] ;
		cout<< "\nActual Height : " << height[0][1];

		cout<< "\n\n-> BST :\n";
		cout<< "Thoeretical height(4.311*log(n) - 1.953*(log(log(n))) : " << th_height[0][2] ;
		cout<< "\nActual Height : " << height[0][2];

		cout<< "\n-------------------\n";
		cout<< "\nThoeretical Key comparisons  : " << th_key_comp[0];
		cout<< "\nActual Key comparisons : treap : " << key_comps[0][0] << "\tAVL :  " << key_comps[0][1] << "\tBST : " << key_comps[0][2] << endl;
		//


		cout<< "\n\n------------------------------------------------------------\n";

	}

	//Output Result of own test files
	//Col(j) 0 -> treap , col 1 -> avl , col 2 -> bst.
	else {
		cout<< "Analysis of the 3 trees from above created 5 test files: \n";
		for(int i = 1 ; i <= tests; i++){

			cout<< "\n\tTEST "<< i << endl<<endl;
			myfile<< "\nTEST "<< i << endl<<endl;
			cout << "\nTotal Operations Done : " <<total_ops[i] << endl;
			myfile << "\nTotal Operations Done : " <<total_ops[i] << endl;

			myfile << "Total key comparisons Done:\n";
			cout << " total key comparisons Done(insertion + deletion) :\n"; 
			for(int j = 0 ; j < 3 ;j++){
				cout<< "-> " << trees[j]  << " : "<< key_comps[i][j] << endl;	
				myfile<<"-> " << trees[j]  << " : "<< key_comps[i][j] << endl;
			}
			cout<<endl;
			myfile<< endl;

			myfile << "total Rotations Done :\n"; 
			cout << " total Rotations Done :\n";
			for(int j = 0 ; j < 3 ;j++){
				cout<< "-> " << trees[j] << " : " << rotations[i][j] << endl;
				myfile<<"-> " << trees[j] << " : " << rotations[i][j] << endl;
			}
			cout<<endl;
			myfile<< endl;

			myfile << "Final height of trees :\n"; 
			cout << "Final height of trees :\n";

			for(int j = 0 ; j < 3 ;j++){
				cout<< "-> " << trees[j] << " : " << height[i][j] << endl;
				myfile <<  "-> " << trees[j] << " : " << height[i][j] << endl;
			}
			cout<<endl;
			myfile<< endl;

			myfile << "Avg node height compare :\n";
			cout << "Avg node height of trees :\n";
			for(int j = 0 ; j < 3 ;j++){
				cout<< "-> " << trees[j] << " : " << avg_node_height[i][j] << endl;
				myfile<< "-> " << trees[j] << " : " << avg_node_height[i][j] << endl;

			}
			myfile<< endl;
			myfile << "\nTotal Nodes  :\n";
			for(int j = 0 ; j < 3 ;j++){
				myfile<< "-> " << trees[j] << " : " << total_nodes[i][j] << endl;
			}
			myfile<< endl;

			//printing to screen
			cout<< "\nTHOERETICAL VS EMPIRICAL COMPARISION : \n";

			cout<< "\n->Treap :\n";
			cout<< "Thoeretical height(log n) : " << th_height[i][0] ;
			cout<< "\nActual Height : " << height[i][0];

			cout<< "\n\n-> AVL tree :\n";
			cout<< "Thoeretical height(1.44 * log(n)) : " << th_height[i][1] ;
			cout<< "\nActual Height : " << height[i][1];

			cout<< "\n\n-> BST :\n";
			cout<< "Thoeretical height(4.311*log(n) - 1.953*(log(log(n))) : " << th_height[i][2] ;
			cout<< "\nActual Height : " << height[i][2];

			cout<< "\n-------------------\n";
			cout<< "Thoeretical Key comparisons  : " << th_key_comp[i];
			cout<< "\nactual Key comparisons : treap : " << key_comps[i][0] << "\tAVL :  " << key_comps[i][1] << "\tBST : " << key_comps[i][2] << endl;
			//


			cout<< "\n\n------------------------------------------------------------\n";


			//writing to file
			myfile<< "\nTHOERETICAL VS EMPIRICAL COMPARISION : \n";

			myfile<< "\n->Treap :\n";
			myfile<< "Thoeretical height(log n) : " << th_height[i][0] ;
			myfile<< "\nActual Height : " << height[i][0];

			myfile<< "\n\n-> AVL tree :\n";
			myfile<< "Thoeretical height(1.44 * log(n)) : " << th_height[i][1] ;
			myfile<< "\nActual Height : " << height[i][1];

			myfile<< "\n\n-> BST :\n";
			myfile<< "Thoeretical height(4.311*log(n) - 1.953*(log(log(n))) : " << th_height[i][2] ;
			myfile<< "\nActual Height : " << height[i][2];

			myfile<< "\n-------------------\n";
			myfile<< "Thoeretical Key comparisons  : " << th_key_comp[i];
			myfile<< "\nactual Key comparisons : treap : " << key_comps[i][0] << "\tAVL :  " << key_comps[i][1] << "\tBST : " << key_comps[i][2] << endl;
			//

			myfile<< "\n------------------------------------------------------------\n";
		}
	}
	myfile.close();

	cout<< "\n\n               You can see the Analysis in output file Analysis.txt as well. \n";


	return 1;

}
