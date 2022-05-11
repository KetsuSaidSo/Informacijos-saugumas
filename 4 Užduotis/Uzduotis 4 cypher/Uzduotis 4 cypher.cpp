
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

/*

25/0

Privalomos slapta�od�i� valdymo sistemos funkcijos :

13/0

Paleidus sistem� pirm� kart� sukuriamas.csv arba.txt failas.
I�jungiant sistem� �is failas turi b�ti u��ifruojamas AES algoritmu.Kit� kart� paleidus sistem� failas yra de�ifruojamas. (4 ta�kai)

Naujo slapta�od�io i�saugojimas : u�pild�ius form�(pavadinimas,
slapta�odis, URL / aplikacija, komentaras), visa jos informacija saugojama.csv arba.txt faile.
Slapta�od�iui pritaikomas �ifravimo algoritmas(pvz.: AES, DES ar RSA.Renkat�s savo nuo�i�ra). (3 ta�kai)

Slapta�od�io paie�ka pagal pavadinim�. (2 ta�kai)

Slapta�od�io atnaujinimas pagal pavadinim� :
suradus tinkam� slapta�od� jis pakei�iamas naujai �vestu.
Naujam slapta�od�iui taip pat turi b�ti pritaikytas �ifravimo algoritmas. (2 ta�kai)

Slapta�od�io i�trynimas pagal pavadinim� :
suradus tinkam� slapta�od� visa informacija apie j� i�trinama i�.csv arba.txt failo. (2 ta�kai)

Papildomos funkcijos :

12/0

Paleidus sistem� pirm� kart� reikalinga vartotojo paskyros suk�rimo forma :
slapyvardis, slapta�odis(�ifruojamas PBKDF2, Bcrypt, Scrypt, Argon2 arba pasirenkant mai�os funkcij�).
Kuriant vartotojo paskyr� yra sugeneruojamas ir vartotojui priskiriamas.csv arba.txt failas.Failas yra u��ifruojamas AES algoritmu. (3 ta�kai)

Prisijungimas prie sistemos : vartotojui prijungus failas de�ifruojamas. (3 ta�kai)

Atsitiktinio slapta�od�io generavimo funkcija(panaudojama kuriant nauj� slapta�od�). (2 ta�kai)

Papildoma funkcija slapta�od�io paie�kai pagal pavadinim� : suradus tinkam� slapta�od� 
jis i�kart nerodomas, pateikiamas tik jo u��ifruotas rezultatas.Paspaudus mygtuk� rodyti 
parodomas slapta�odis. (2 ta�kai)

Mygtukas galintis nukopijuoti slapta�od� � i�karpin�. (2 ta�kai)
*/

int main()
{
	//we will read from file input.txt
	int extendedlength = 0;
	int choice;
	string myText;

		//encryption of text data
		ifstream File;
		string filepath = "encryption.aes";
		//clearing encryption.aes before editing
		File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc);
		if (!File.is_open() || File.fail())
		{
			File.close();
			printf("\nError : failed to erase file content !");
		}
		File.close();
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
		cout << "Reading encrypted data from encryption.txt .........\n";
		Sleep(1000);
		string tp;
		cout << "Reading KEY from key.txt ......\n";
		Sleep(1000);
		cout << "Now Decrypting ....\n";
		Sleep(1000);
		cout << "writing decrypted data in outputtext.txt ..\n";
		Sleep(1000);
		cout << endl;
		cout << "Following is our decrypted text:- \n";
		//clearing outputtext file
		ifstream File2;
		string filepath2 = "outputtext.txt";
		File2.open(filepath2.c_str(), std::ifstream::out | std::ifstream::trunc);
		if (!File2.is_open() || File2.fail())
		{
			File2.close();
			printf("\nError : failed to erase file content !");
		}
		File2.close();

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
					cout << decryptedtext[i];
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