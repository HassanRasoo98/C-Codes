#include <iostream>
#include <cmath>
#include <bits/stdc++.h> // i use this library for my decimal to other systems conversions logic (for reversing the string)
using namespace std;

class number_system {
	string decimal;
	string hexadecimal;
	string binary;
	
	void display(int &num) {
		cout << "Enter 1 for decimal.\n";
		cout << "Enter 2 for binary.\n";
		cout << "Enter 3 for hexadecimal.\n";
		cout << "Enter -1 to exit.\n";
		
		cin >> num;
		if (num==-1) exit(0);
		// input validation
		while(num < 1 || num > 3) {
			cout << "Invalid number entered. Enter again : ";
			cin >> num;
			if (num==-1) exit(0);
		}
	}
	
	void display_results() {
		cout << "Decimal : " << this->decimal << endl;
		cout << "Binary : " << this->binary << endl;
		cout << "Hexadecimal : " << this->hexadecimal << endl;
		cout << "--------------------------------------------" << endl;
		
		// clearing the variables after displaying results
		decimal = "";
		binary = "";
		hexadecimal = "";
	}

	string convert_decimal_to_binary() {
		// enter your logic here
		string bin;
		int i, remainder;
		for (i=stoi(this->decimal) ; i != 0; i/=2){
			remainder = i%2;
			bin += to_string(remainder);
		}
		reverse(bin.begin(), bin.end());		
		return bin;
	}
	
	string convert_decimal_to_hexadecimal()	{
		// enter your logic here
		string hex;
		int i, remainder;
		for (i = stoi(this->decimal); i!=0; i/=16)	// for hexadecimal
		{
			remainder = i%16;
			if (remainder >= 10)
			{
				if (remainder == 10){
					hexadecimal += "A";
				}
				if (remainder == 11){
					hexadecimal += "B";
				}
				if (remainder == 12){
					hexadecimal += "C";
				}
				if (remainder == 13){
					hexadecimal += "D";
				}
				if (remainder == 14){
					hexadecimal += "E";
				}
				if (remainder == 15){
					hexadecimal += "F";
				}
			}
			else{
				hexadecimal += to_string(remainder);
			}
		} // hexadecimal
		reverse(hexadecimal.begin(), hexadecimal.end());		
		return hexadecimal;
	}
	
	string convert_binary_to_decimal() {
		int dec=0;
		for (int power=0, i=this->binary.length()-1; i>=0; i--, power++) {
			if (binary[i]=='1')
				dec += pow(2, power);
		}
		return to_string(dec);
	}
	
	string convert_hexadecimal_to_decimal() {
		int dec=0;
		char temp1;
		int temp2;
		
		for (int power=0, i=this->hexadecimal.length()-1; i>=0; i--, power++) {
			temp1 = hexadecimal[i];
			if (int(temp1) >= 65) {
				if (int(temp1)==65) temp2 = 10;
				if (int(temp1)==66) temp2 = 11;
				if (int(temp1)==67) temp2 = 12;
				if (int(temp1)==68) temp2 = 13;
				if (int(temp1)==69) temp2 = 14;
				if (int(temp1)==70) temp2 = 15;
			}
			else temp2 = temp1-48;
			
			dec += temp2 * pow(16, power);
		}
		return to_string(dec);			
	}	
	
	void upper_case(string &hex) {
		string temp;
		for (int i=0; i<hex.length(); i++) {
			if (hex[i] >= 97 && hex[i] <= 122) 
				hex[i] -= 32;
			temp += hex[i];
		}
		hex = temp;
	}			
	
public:
	void menu() {
		int option;
		display(option);
		switch(option) {
			case 1:
				get_decimal();
				break;
			case 2:
				get_binary();
				break;
			case 3:
				get_hexadecimal();
				break;
		}
		
		display_results();
	}
	
	void get_decimal() {
		cout << "Enter decimal number : ";
		cin >> this->decimal;
		
		// you can put a function here to check the validity of the entered decimal number
		
		this->binary = convert_decimal_to_binary();
		this->hexadecimal = convert_decimal_to_hexadecimal();
	}
	
	void get_binary() {
		cout << "Enter binary number : ";
		cin >> this->binary;
		
		// you can put a function here to check the validity of the entered binary number
		
		this->decimal = convert_binary_to_decimal();
		
		/*
			BIG BRAIN TIME
			since we have got the decimal number of the binary
			we can use previously defined funtion to convert this decimal into hexadecimal
			without having the need to convert binary to hexadecimal
		*/
		
		this->hexadecimal = convert_decimal_to_hexadecimal();
	}	
	
	void get_hexadecimal() {
		cout << "Enter hexadecimal number : ";
		cin >> this->hexadecimal;
		// converting all string into uppercase to ease calculation
		upper_case(this->hexadecimal);
		// you can put a function here to check the validity of the entered hexadecimal number
		
		this->decimal = convert_hexadecimal_to_decimal();
		// BIG BRAIN TIME AGAIN
		this->binary = convert_decimal_to_binary();
	}	
};

int main() {
	number_system ns;
	while(true)
		ns.menu();
}
