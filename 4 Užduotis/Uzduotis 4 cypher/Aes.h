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

#pragma warning(disable : 4996)

using namespace std;

//we will read from file input.txt
int extendedlength = 0;
int choice;
string myText;

//clearing encryption.aes before editing
void flagCaes()
{
		ifstream File;
		string filepath = "encryption.aes";

		File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc);
		if (!File.is_open() || File.fail())
		{
			File.close();
			printf("\nError : failed to erase file content !");
		}
		File.close();
}

//encryption of text data

void fileencrypting()
{
	//reading plain text from input.txt 
		fstream newfile;
		newfile.open("input.txt", ios::in); //open a file to perform read operation using file object
		if (newfile.is_open())
		{   //checking whether the file is open
			cout << "Reading plain text from input.txt .........\n";
			Sleep(1000);
			string tp;
			cout << "Reading KEY from key.txt ......\n";
			Sleep(1000);
			cout << "Now encrypting ....\n";
			Sleep(1000);
			cout << "writing encrypted data in encryption.aes ..\n";
			Sleep(1000);
			cout << endl;
			while (getline(newfile, tp)) {
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
				fin.open("encryption.aes");
				fout.open("encryption.aes", ios::app); // Append mode
				if (fin.is_open())
					fout << encryptedtext << "\n"; // Writing data to file
				fin.close();
				fout.close();
			}
			cout << "128-bit AES encryption is done sucessfully\n";
			cout << "Data has been appended to file encryption.aes";
			newfile.close(); //close the file object.
		}
}

//clearing outputtext file
void flagCoutput()
{
	ifstream File;
	string filepath = "outputtext.txt";
	File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc);
	if (!File.is_open() || File.fail())
	{
		File.close();
		printf("\nError : failed to erase file content !");
	}
	File.close();
}

void filedecrypting()
{
	ifstream MyReadFile;
	MyReadFile.open("encryption.aes", ios::in | ios::binary);
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
			//printing our plain text
			for (int i = 0; i < messlength; i++)
			{
				cout <<"\n"<< decryptedtext[i]<<"\n";
				if (decryptedtext[i] == 0 && decryptedtext[i - 1] == 0)
					break;
			}

			//storing plain text in outputtext.txt file
			cout << endl;
			ofstream fout;  // Create Object of Ofstream
			ifstream fin;
			fin.open("outputtext.txt");
			fout.open("outputtext.txt", ios::app); // Append mode
			if (fin.is_open())
				fout << decryptedtext << "\n"; // Writing data to file

			fin.close();
			fout.close(); // Closing the file
			Sleep(500);
		}
	}
	else
	{
		cout << "Can not open input file\n ";
	}
	cout << "\n Data has been appended to file outputtext.txt";
	MyReadFile.close();
}