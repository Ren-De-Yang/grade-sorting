#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>  //char* into int
#include <iomanip>

using namespace std;

ifstream input("grade_data.csv");

ofstream output("ans.txt");

int main(int argc, char** argv) {
	
	string temp;
	char * token;
	int t, row_n, col_n;
	float per_grade;
	
	//讀取人數及科目數 
	while (getline(input, temp)) {
		row_n = row_n + 1;
		
		col_n=0;
		token = strtok(&temp[0], ",");
		while (token!=NULL) {
			col_n = col_n + 1;
			token = strtok(NULL, ",");
		}
	}
	int grades[row_n+1][col_n+4]; //每人成績
	float subjects[col_n]; //每科成績 
	
	input.close();
	
	
	
	//初始成績陣列 
	for (int i=0; i<row_n+1; i++) {
		for (int j=0; j<col_n+4; j++) {
			grades[i][j]=0;
		}
	}
	
	for (int i=0; i<col_n; i++) {
		subjects[i]=0;
	}
	
	
	ifstream input2("grade_data.csv");
	row_n=0;
	col_n = 0;
	//讀取資料, 存入陣列 
	while (getline(input2, temp)) {
		row_n = row_n + 1;
		col_n = 0;
		token = strtok(&temp[0], ",");
	
		while (token!=NULL) {
			col_n = col_n + 1;
			grades[row_n-1][col_n-1] = atoi(token);
			token = strtok(NULL, ",");	
		}
	}
	
	
	
	//統計每人總成績, 平均  , 不及格科目 
	int fail;
    per_grade = 0;
	for (int i=0; i<row_n; i++) {
		per_grade = 0;
		fail=0;
		for (int j=0; j<col_n; j++) {
		//	cout  << grades[i][j] << " ";
			per_grade = per_grade + grades[i][j];
			subjects[j] = subjects[j] + grades[i][j];
			if(grades[i][j]<60){
				fail++;
			}
		}
		grades[i][col_n]= per_grade;
		grades[i][col_n+1]= (per_grade/(float) col_n);
		grades[i][col_n+2]= fail;
	}
	
	//名次
	int ranking[row_n]; 
	int temp2=0; 
	for(int i=0; i<=row_n; i=i+1){
		ranking[i]= grades[i][col_n]; 
	} 
	for (int i=0; i<=row_n; i=i+1) {
		for (int j=i+1; j<=row_n; j=j+1) {
			if (ranking[i] < ranking[j]) {
				temp2 = ranking[i];
				ranking[i] = ranking[j];
				ranking[j] = temp2;
			}
		}
	}
	for (int i=0; i<=row_n; i=i+1) {
		for (int j=0; j<=row_n; j=j+1) {
			if(ranking[i]==grades[j][col_n]) 
				grades[j][col_n+3]=i+1;
		}
	}	 
	
	
	
	//各科平均 
	for (int i=0; i<col_n; i++) {
		grades[row_n][i]= (subjects[i]/(float) row_n);
	}
	
	
	
	
	
	
	//輸出 
	for(int j=0;j<row_n;j++){
		cout <<"總分" << setw(3)<<grades[j][col_n] << ", 平均" << setw(3)<<grades[j][col_n+1] << ", 不及格科目"  <<setw(3)<<grades[j][col_n+2]<<", 名次" <<setw(3)<< grades[j][col_n+3]<<endl;
		output <<"總分" << grades[j][col_n] << ", 平均" << grades[j][col_n+1] << ", 不及格科目" << grades[j][col_n+2]<<", 名次" << grades[j][col_n+3]<<endl;
	}
	cout<< "各科平均"; 
	for (int i=0; i<col_n; i++) {
		cout << grades[row_n][i] << " ";
	}


	input2.close();
	output.close();
	
	system("pause");
	return 0;
}
