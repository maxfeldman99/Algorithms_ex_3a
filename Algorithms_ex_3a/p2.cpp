#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

typedef struct Customer {

	int start;
	int end;
	int profit;

} Customer;


int getCustomerNum(ifstream&);
Customer* getCustomerData(int customerNum, ifstream&);
void buildArray(int *arr, int cusomerNum, Customer *customerList);
void findBestSchedule(Customer *customerList, int customerNum, int *arr, int j, int i);
int findMax(int *arr, int customerNum);


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
void buildArray(int *arr,int cusomerNum,Customer *customerList) {
	for (int i = 0; i < cusomerNum; i++) {
		arr[i] = customerList[i].profit;
		
	}
}

void findBestSchedule(Customer *customerList,int customerNum, int *arr,int j,int i) {
	while (j!= customerNum) {
		cout << " index j : " << j << endl;
		cout << " index i : " << i << endl;
		if (customerList[i].start < customerList[j].end) { // is there an intersection?
			if (i == customerNum) {
				j++;
			}
			else {
				i++;
				j = 0;
			}
			
		}
		else {
			arr[j] + customerList[i].profit > arr[i] ? arr[i] = arr[j] + customerList[i].profit : arr[i] = arr[j] + arr[i];
			
			if (j + 1 == i) {
				i++;
				j = 0;
			}
			if (i > customerNum) {
			
			}
			((j + 1) == i) ? (i++, j = 0) : j++;
			
		}
		

		findBestSchedule(customerList, customerNum, arr, j, i);
		
	}
	int maxVal;
	maxVal = findMax(arr,customerNum);
	cout << " The best match will give a revenue of " << maxVal << endl;
	system("pause");
}

int findMax(int *arr, int customerNum) {
	int max = arr[0];
	for (int i = 0; i < customerNum; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}




void main() {
	
	int num1, num2, profit;
	int customerNum;
	char fname[] = { "orders.txt" };
	ifstream myfile;
	myfile.open(fname);
	customerNum = getCustomerNum(myfile);
	cout << customerNum << endl;
	myfile.clear();
	myfile.close();
	myfile.open(fname);
	Customer* customerList = getCustomerData(customerNum,myfile);
	int *arr = new int[customerNum];
	buildArray(arr, customerNum, customerList);
	findBestSchedule(customerList,customerNum,arr,0,1);
	for (int i = 0; i < customerNum; i++) {

		cout << "the " << i+1 <<" customer is : " << endl;
		cout << customerList[i].start << endl;
		cout << customerList[i].end << endl;
		cout << customerList[i].profit << endl;
	}
				
	system("pause");


}