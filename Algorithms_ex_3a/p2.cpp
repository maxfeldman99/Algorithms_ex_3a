#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

typedef struct Customer {

	int start;
	int end;
	int profit;

} Customer;


int getCustomerNum(ifstream&);
Customer* getCustomerData(int customerNum, ifstream&);


int getCustomerNum(ifstream &myfile) {
	int customerNum;
	string line;
	int lineCounter=0;
	if (!myfile.is_open()) {
		exit(EXIT_FAILURE);
	}
	else {
		while (getline(myfile, line)){

			stringstream iss(line);
			if (lineCounter == 0) {
				iss >> customerNum;
				lineCounter++;
			}
			else {
				return customerNum;
			}

		}

	}
	myfile.close();

	
}

Customer* getCustomerData(int customerNum,ifstream &myfile) {
	int num1, num2, profit;
	int firstLine = 0;
	int i = 0;
	char a;
	string line;
	Customer *customerList = new Customer[customerNum];
	
	if (!myfile.is_open()) {
		exit(EXIT_FAILURE);
	}
	else {
		
		while (getline(myfile, line)) {

			stringstream iss(line);
			if (firstLine++ == 0) {
			
			}
			else {
				iss >> num1 >> a >> num2 >> a >> profit;
				cout << line << endl;
				customerList[i].start = num1;
				customerList[i].end = num2;
				customerList[i].profit = profit;
				i++;
			}
		}
	}
	return customerList;
}




void main() {
	int len = 0;
	int num1, num2, profit;
	int customerNum;
	int *arr;
	char c, a, b;
	//string line;
	
	string filename = "orders.txt";
	char fname[] = { "orders.txt" };
	

	int lineCounter = 0;
	string line;
	ifstream myfile;
	

	myfile.open(fname);
	customerNum = getCustomerNum(myfile);
	cout << customerNum << endl;
	myfile.clear();
	myfile.close();
	myfile.open(fname);
	Customer* customerList = getCustomerData(customerNum,myfile);

	for (int i = 0; i < customerNum; i++) {

		cout << "the " << i+1 <<" customer is : " << endl;
		cout << customerList[i].start << endl;
		cout << customerList[i].end << endl;
		cout << customerList[i].profit << endl;
	}
				
	system("pause");


}