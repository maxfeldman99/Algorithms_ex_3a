#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;

typedef struct Customer {

	int start;
	int end;
	int profit;
	int orderNum;
	vector<int> list;

} Customer;

typedef struct MaxVal {
	int maxProfit;
	vector<int> list;

}MaxVal;


int getCustomerNum(ifstream&);
Customer* getCustomerData(int customerNum, ifstream&);
void buildArray(int *arr, int cusomerNum, Customer *customerList);
void findBestSchedule(Customer *customerList, int customerNum, int *arr, int j, int i);
MaxVal findMax(int *arr, int customerNum,Customer *customerList);
void MergeSort(Customer *a, int low, int high, int customersNum);
void Merge(Customer *a, int low, int high, int mid, int customersNum);
MaxVal getOrders(int index, Customer *customerList, int CustomerNum);


void Merge(Customer *a, int low, int high, int mid, int customersNum)

{
	// We have low to mid and mid+1 to high already sorted.
	int i, j, k;
	Customer *temp;
	temp = new Customer[customersNum];
	i = low;
	k = 0;
	j = mid + 1;

	// Merge the two parts into temp[].

	while (i <= mid && j <= high)
	{
		if (a[i].end < a[j].end)
		{
			temp[k] = a[i];
			k++;
			i++;
		}
		else
		{
			temp[k] = a[j];
			k++;
			j++;
		}
	}



	// Insert all the remaining values from i to mid into temp[].

	while (i <= mid)
	{
		temp[k] = a[i];
		k++;
		i++;
	}



	// Insert all the remaining values from j to high into temp[].

	while (j <= high)
	{
		temp[k] = a[j];
		k++;
		j++;
	}




	// Assign sorted data stored in temp[] to a[].

	for (i = low; i <= high; i++)
	{
		a[i] = temp[i - low];
	}
}




void MergeSort(Customer *a, int low, int high, int customersNum)

{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;
		// Split the data into two half.
		MergeSort(a, low, mid, customersNum);
		MergeSort(a, mid + 1, high, customersNum);
		// Merge them to get sorted output.
		Merge(a, low, high, mid, customersNum);
	}

}





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
				customerList[i].start = num1;
				customerList[i].end = num2;
				customerList[i].profit = profit;
				customerList[i].orderNum = i+1;
				customerList[i].list.reserve(customerNum);
				customerList[i].list.push_back(i+1); // first element of the potential best solution
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
	vector<int>::const_iterator p;
	while (j!= customerNum-1 && i!=customerNum) {
	
		if (customerList[i].start < customerList[j].end && j + 1 == i) { // intersection and j=i-1

				i++;
				j = 0;
			}
		else if (customerList[i].start < customerList[j].end && j + 1 != i) { // intersection and j!= i-1
			j++;
		}

		else { // no intersection



			if (arr[j] + customerList[i].profit > arr[i]) {

				arr[i] = arr[j] + customerList[i].profit;



				for (p = customerList[j].list.begin(); p!= customerList[j].list.end(); ++p) {  // this section will check if there is an intersection in the index's that were already pushed to the best answer so far and the new candidate
					if (customerList[(*p)-1].start >= customerList[j].end) {
						customerList[i].list.push_back(customerList[j].orderNum);
						break;
					}
				}
			
			}
			else {

			}
			/*arr[j] + customerList[i].profit > arr[i] ? arr[i] = arr[j] + customerList[i].profit : arr[i] =  arr[i];*/

		
			((j + 1) == i) ? (i++, j = 0) : j++;
			
			if (i == customerNum) {
				j++;
			}
			
		}
		

		findBestSchedule(customerList, customerNum, arr, j, i);
		
	}
	MaxVal answer;
	
	
	answer = findMax(arr, customerNum, customerList);
	
	if (customerNum == 1) {
		cout << "order : 1, ";
	}
	cout << "Max value =  " << answer.maxProfit << endl;
	system("pause");
}

MaxVal findMax(int *arr, int customerNum,Customer *customerList) {
	MaxVal bestNode;
	int a;
	bestNode.maxProfit = arr[0];
	if (customerNum == 1) { // if there is only 1 customer 
		return bestNode;
	}
	for (int i = 0; i < customerNum; i++) {
		if (arr[i] > bestNode.maxProfit) {
			bestNode.maxProfit = arr[i];
			a = i;
		}
		
	}


	getOrders(a, customerList, customerNum);
	
	
	
	return bestNode;
}

MaxVal getOrders(int index,Customer *customerList,int CustomerNum) {
	MaxVal bestOrderNode;
	vector<int>::const_iterator i;
		

		bestOrderNode.list = customerList[index].list;
		cout << "orders :";

		for (i = customerList[index].list.begin(); i != customerList[index].list.end(); ++i) {
			cout << (*i) << ",";
		}
		cout << " ";

		return bestOrderNode;
	
}




void main() {
	//
	int num1, num2, profit;
	int customerNum;
	char fname[] = { "orders.txt" };
	ifstream myfile;
	myfile.open(fname);
	customerNum = getCustomerNum(myfile);
	myfile.clear();
	myfile.close();
	myfile.open(fname);
	Customer* customerList = getCustomerData(customerNum,myfile);
	// customerList must be sorted here by end time
	MergeSort(customerList, 0, customerNum - 1, customerNum);
	int *arr = new int[customerNum];
	buildArray(arr, customerNum, customerList);
	findBestSchedule(customerList,customerNum,arr,0,1);
	
				
	system("pause");


}