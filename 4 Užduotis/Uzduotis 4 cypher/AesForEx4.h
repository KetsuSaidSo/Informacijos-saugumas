#pragma once

#include<iostream>
#include<fstream>
#include<cstring>
#include<sstream>
#include "AesKeyExpand.h"
#include "AesEncoding.h"
#include "AesDecoding.h"
#include <typeinfo>
#include<windows.h>
#include <vector>

#pragma warning(disable : 4996)

int extendedlength = 0;
string myText;

using namespace std;

bool prisijungti(ifstream& stream, string token, string password)
{
	string line;
	while (getline(stream, line)) {
		if (line.find(token) != string::npos) 
		{
			if (line.find(password) != string::npos)
			{
				return true;
				cout << "Prisijungta\n";
			}
			cout << line << endl;
			cout << "Neteisingas slaptazodis\n";
			return false;
		}
	}
	cout << token << " Naudotojas nerastas" << endl;
	return false;
}

void registruotis(string username, string password)
{
	string filename("user.txt");
	ofstream file_out;

	file_out.open(filename, std::ios_base::app);
	file_out<<username + " " + password << "\n";
	cout << "sekmingai uzregistruota galite jugntis prie programos\n";
	file_out.close();
}

void menu1(string name,string username, string password, string URL, string comment)
{
	string filename("data.txt");
	ofstream file_out;

	file_out.open(filename, std::ios_base::app);
	file_out <<"\n"+ name + " " + username + " " + URL + " " + comment << "\n";
	file_out.close();

	string filename2("passwords.txt");
	ofstream file_out2;
	file_out2.open(filename2, std::ios_base::app);
	file_out2 << name + " " + username + " " + password<<"\n";
	file_out2.close();
}

void menu2(ifstream& stream, string token)
{
		string line;
		while (getline(stream, line)) {
			if (line.find(token) != string::npos) {
				cout << line << endl;
			}
		}
		cout << token << " not found" << endl;
}

void menu3(string fname, string username, string password, string rpassword)
{
	fstream file;
	file.open("passwords.txt", ios::in);

	if (file.is_open()) {
		string replace = password;
		string replace_with = rpassword;
		string line;
		vector<string> lines;

		while (getline(file, line)) {
			cout << line << std::endl;

			string::size_type pos = 0;

			while ((pos = line.find(replace, pos)) != string::npos) 
			{
				if (line.find(fname,pos) && line.find(username, pos))
				{
					line.replace(pos, line.size(), replace_with);
					pos += replace_with.size();
				}
			}

			lines.push_back(line);
		}

		file.close();
		file.open("passwords.txt", ios::out | ios::trunc);

		for (const auto& i : lines) {
			file << i << endl;
		}
	}
}

void menu4(std::string path, std::string eraseLine) 
{
	std::string line;
	std::ifstream fin;

	fin.open(path);
	// contents of path must be copied to a temp file then
	// renamed back to the path file
	std::ofstream temp;
	temp.open("temp1.txt");

	while (getline(fin, line)) {
		// write all lines to temp other than the line marked for erasing
		if (line != eraseLine)
			temp << line << std::endl;
	}

	temp.close();
	fin.close();

	// required conversion for remove and rename functions
	const char* p = path.c_str();
	remove(p);
	rename("temp1.txt", p);
}

void fileenc(string input, string output)
{
	fstream newfile;
	newfile.open(input, ios::in); //open a file to perform read operation using file object
	if (newfile.is_open())
	{
		string tp;
		while (getline(newfile, tp))
		{
			//read data from file object and put it into string.
			int messlength = tp.length();
			int extendedlength;
			if ((messlength % 16) != 0)
			{
				extendedlength = messlength + (16 - (messlength % 16));
			}
			else
			{
				extendedlength = messlength;
			}
			unsigned char* encryptedtext = new unsigned char[extendedlength];
			for (int i = 0; i < extendedlength; i++)
			{
				if (i < messlength)
					encryptedtext[i] = tp[i];
				else
					encryptedtext[i] = 0;
			}

			//getting key from key.txt
			string k;
			ifstream infile;
			infile.open("key.txt");
			if (infile.is_open())
			{
				getline(infile, k); // The first line of file should be the key
				infile.close();
			}
			else cout << "Unable to open file";

			istringstream tempkey(k);
			unsigned char key[16];
			unsigned int x;
			for (int i = 0; i < 16; i++)
			{
				tempkey >> hex >> x;
				key[i] = x;
			}
			//extending key
			unsigned char extendedkeys[176];
			Key_extenxion(key, extendedkeys);

			//encrypting our plain text
			for (int i = 0; i < extendedlength; i += 16)
			{
				unsigned char* temp = new unsigned char[16];
				for (int j = 0; j < 16; j++)
				{
					temp[j] = encryptedtext[i + j];
				}
				encryption(temp, extendedkeys);
				for (int j = 0; j < 16; j++)
				{
					encryptedtext[i + j] = temp[j];
				}
			}

			//storing our encrypted data in encryption.aes	 		 
			ofstream fout;  // Create Object of Ofstream
			ifstream fin;
			fin.open(output);
			fout.open(output, ios::app); // Append mode
			if (fin.is_open())
				fout << encryptedtext << "\n"; // Writing data to file
			fin.close();
			fout.close();

			ifstream File;
			string filepath = input;
			File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc);
			if (!File.is_open() || File.fail())
			{
				File.close();
				printf("\nError : failed to erase file content !");
			}
			File.close();
		}
	}
}

void infomove(string from, string to)
{
	string line;
	//For writing text file
	//Creating ofstream & ifstream class object
	ifstream ini_file{ from };
	ofstream out_file{ to };

	if (ini_file && out_file) {

		while (getline(ini_file, line)) {
			out_file << line << "\n";
		}
	}
	else {
		//Something went wrong
		printf("Cannot read File");
	}

	ifstream File;
	string filepath = from;
	File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc);
	if (!File.is_open() || File.fail())
	{
		File.close();
		printf("\nError : failed to erase file content !");
	}
	File.close();

	//Closing file
	ini_file.close();
	out_file.close();
}

void cleandata(string file)
{
	ifstream File;
	string filepath = file;
	File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc);
	if (!File.is_open() || File.fail())
	{
		File.close();
		printf("\nError : failed to erase file content !");
	}
	File.close();
}

void filedec(string input, string output)
{
	ifstream MyReadFile;
	MyReadFile.open(input, ios::in | ios::binary);
	if (MyReadFile.is_open())
	{
		while (getline(MyReadFile, myText))
		{
			cout.flush();
			char* x;
			x = &myText[0];
			int messlength = strlen(x);
			char* msg = new char[myText.size() + 1];

			strcpy(msg, myText.c_str());

			int n = strlen((const char*)msg);
			unsigned char* decryptedtext = new unsigned char[n];

			//decrypting our encrypted data
			for (int i = 0; i < n; i++) {
				decryptedtext[i] = (unsigned char)msg[i];
			}

			//reading key from key.txt file
			string k;
			ifstream infile;
			infile.open("key.txt");
			if (infile.is_open())
			{
				getline(infile, k); // The first line of file should be the key
				infile.close();
			}
			else cout << "Unable to open file";

			istringstream tempkey(k);
			unsigned char key[16];
			unsigned int x1;
			for (int i = 0; i < 16; i++)
			{
				tempkey >> hex >> x1;
				key[i] = x1;
			}

			//extending key
			unsigned char extendedkeys[176];
			Key_extenxion(key, extendedkeys);

			//decrypting our data  
			for (int i = 0; i < messlength; i += 16)
			{
				unsigned char* temp = new unsigned char[16];
				for (int j = 0; j < 16; j++)
					temp[j] = decryptedtext[i + j];
				decryption(temp, extendedkeys);
				for (int j = 0; j < 16; j++)
					decryptedtext[i + j] = temp[j];
			}

			cout << "\n";

			//printing our plain text
			for (int i = 0; i < messlength; i++)
			{
				cout << decryptedtext[i];
				if (decryptedtext[i] == 0 && decryptedtext[i - 1] == 0)
					break;
			}

			//storing plain text in outputtext.txt file
			cout << endl;
			ofstream fout;  // Create Object of Ofstream
			ifstream fin;
			fin.open(output);
			fout.open(output, ios::app); // Append mode
			if (fin.is_open())
				fout << decryptedtext << "\n"; // Writing data to file
			fin.close();
			fout.close(); // Closing the file

			ifstream File;
			string filepath = input;
			File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc);
			if (!File.is_open() || File.fail())
			{
				File.close();
				printf("\nError : failed to erase file content !");
			}
			File.close();
		}
	}
}