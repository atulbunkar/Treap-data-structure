#include<bits/stdc++.h>
#include<fstream>
using namespace std;

void gen_test(const std::string& name , int size, double p_insert ){
    cout<< "\nCreating file "<< name << " with number of operations = " << size ;
    cout<< " and Ratio of INSERT to DELETE = " << p_insert << endl; ;
	ofstream myfile;
    myfile.open(name); 
    string ops[2] = {"Insert", "Delete"};

    int index ; bool check ; int insert_cnt = 0;
    int inserted[size] ; int random , del_index;

    myfile<< size << endl;
    
    
    for(int i = 0 ; i < size ; i++){
        check = (rand()% 100) < p_insert*100;  //allots true/false based on prob_insert. We use this as : True->INSERT ,False ->DELETE
        
        if(check){                           //to print INSERT with random number from 1 to size of operations and store the number in array  inserted[].
            index = 0;
            random = rand()% size +1 ;
    	    myfile << ops[index] << " " << random <<  endl;  
            inserted[insert_cnt++] = random ;       
        }

        else{    
            index = 1 ;                       //to print DELETE with random number from inserted elements or random number
            myfile << ops[index] << " " ;

            check = (rand()% 100) < 95;       //95% times delete from already inserted nodes, else delete random element(can be non existant)
            if(!check || insert_cnt== 0){
                       myfile<< rand()%100000  <<  endl;       //delete random number                                          
            }
            else{   
                myfile<< inserted[rand()%insert_cnt] <<  endl;  // To delete from already inserted elements. 
            }
        }
        
    }
    myfile.close();

}

int main(){
    cout<< "\n----TEST FILE GENERATION----\n";
    srand(100);
    int test_size ;
    cout<<"Total 5 test files will be generated : \n";
    cout<<"User can vary the no of operations in each test files \n";
    cout<<"For my analysis , I used these no of operations : 10000,12000,14000,18000,20000 for the test files. \n\n";

    

    //test 1
    string name = "test1.txt";
    double prob_insert  = 0.7;  // 70% insertion , 30 % deletion
    while(1){
        cout<< "Enter Total No of operations to fill (Ex: 10000) for " << name <<" :\n";
        cin >> test_size ;
        while(cin.fail()) {
           cout << "Enter only Interger !!"  << std::endl;
           cin.clear();
           cin.ignore(256,'\n');
           cin >> test_size;
         }
        break;
    }
    
    gen_test(name,test_size , prob_insert ) ;   //refer test_gen.h to see how test files are generated.
    //prob_insert -> probability of insert operation


    //test 2
    name = "test2.txt";
    prob_insert = 0.6 ;   // 60% insertion , 40% deletion
    while(1){
        cout<< "Enter Total No of operations to fill (Ex: 10000) for " << name <<" :\n";
        cin >> test_size ;
        while(cin.fail()) {
           cout << "Enter only Interger !!"  << std::endl;
           cin.clear();
           cin.ignore(256,'\n');
           cin >> test_size;
         }
        break;
    }
    gen_test(name,test_size , prob_insert ) ;

    //test 3

    name = "test3.txt";
    prob_insert = 0.5 ;   // equal insertion , deletion
    while(1){
        cout<< "Enter Total No of operations to fill (Ex: 10000) for " << name <<" :\n";
        cin >> test_size ;
        while(cin.fail()) {
           cout << "Enter only Interger !!"  << std::endl;
           cin.clear();
           cin.ignore(256,'\n');
           cin >> test_size;
         }
        break;
    }
    gen_test(name, test_size , prob_insert ) ;

    //test 4

    name = "test4.txt";
    prob_insert = 0.4 ;  // 40 % insertion, 60% deletion
    while(1){
        cout<< "Enter Total No of operations to fill (Ex: 10000) for " << name <<" :\n";
        cin >> test_size ;
        while(cin.fail()) {
           cout << "Enter only Interger !!"  << std::endl;
           cin.clear();
           cin.ignore(256,'\n');
           cin >> test_size;
         }
        break;
    }
    gen_test(name,test_size , prob_insert ) ;

    //test 5
    name = "test5.txt";
    prob_insert = 0.3 ;  // 30 % insertion, 70% deletion
    while(1){
        cout<< "Enter Total No of operations to fill (Ex: 10000) for " << name <<" :\n";
        cin >> test_size ;
        while(cin.fail()) {
           cout << "Enter only Interger !!"  << std::endl;
           cin.clear();
           cin.ignore(256,'\n');
           cin >> test_size;
         }
        break;
    }
    gen_test(name,test_size , prob_insert ) ;

    cout<< "\nALL TEST FILES CREATED !!\n";

}
