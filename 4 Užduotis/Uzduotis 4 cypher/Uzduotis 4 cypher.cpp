
#include<iostream>
#include "AesForEx4.h"

using namespace std;

/*

25/11

Privalomos slapta�od�i� valdymo sistemos funkcijos :

13/11

Slapta�od�io atnaujinimas pagal pavadinim� :
suradus tinkam� slapta�od� jis pakei�iamas naujai �vestu.
Naujam slapta�od�iui taip pat turi b�ti pritaikytas �ifravimo algoritmas. (2 ta�kai)

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
ifstream pri("user.txt");
string input = "input.txt";
string output = "output.txt";
string temp = "temp.txt";
string data = "data.txt";
string user = "user.txt";
string password = "passwords.txt";
string username, userpassword, formname, URL, comment, formpassword, tempstring;
string pass1, pass2,delline;
char ch1;
int ch2;

int main()
{
	do
	{
		filedec(user, output);
		infomove(output, user);
		cout << "1)Prisijungti\n";
		cout << "2)Registruotis\n";
		cout << "Q baigti darba\n";
		cin >> ch1;
		if (ch1 == '1')
		{
			cout << "Iveskite naudotojo varda\n";
			cin >> username;
			cout << "Iveskite naudotojo slaptazodi\n";
			cin >> userpassword;

			if (prisijungti(pri,username, userpassword) == true)
			{
				infomove(user, temp);
				fileenc(temp, user);

				ch1 = '0';
			}
			else
			{
				infomove(user, temp);
				fileenc(temp, user);
			}
		}
		else if (ch1 == '2')
		{
			cout << "Iveskite naudotojo varda\n";
			cin >> username;
			cout << "Iveskite naudotojo slaptazodi\n";
			cin >> userpassword;
			registruotis(username, userpassword);
			infomove(user, temp);
			fileenc(temp, user);
		}
		else if (ch1 == 'Q')
		{
			infomove(user, temp);
			fileenc(temp, user);
			break;
		}
	} while (ch1 != '0');

	if (ch1 == '0')
	{
		//decrypting password
		filedec(password, output);
		infomove(output, password);

		do
		{
			cout << "-------Menu-------\n";
			cout << "__________________\n";
			cout << "1) nauja forma\n";
			cout << "2) slaptazodziu paieska pagal pavadinima\n";
			cout << "3) Slapta�od�io atnaujinimas pagal pavadinim�\n";
			cout << "4) Slapta�od�io i�trynimas pagal pavadinim�\n";
			cout << "0) iseiti\n";
			cin >> ch2;

			if (ch2 == 1)
			{
				formname = "";
				cout << "Iveskite formos pavadinima\n";
				cin >> formname;
				cout << "Iveskite formos slaptazodi\n";
				cin >> formpassword;
				cout << "Iveskite URL\n";
				cin >> URL;
				cout << "Iveskite komentara\n";
				cin >> comment;
				menu1(formname, username,formpassword, URL ,comment);
			}
			else if (ch2 == 2)
			{
				formname = "";
				ifstream file(password);
				cout << "Iveskite formos pavadinima\n";
				cin >> formname;
				cout << "\n";
				cout << "-------------Rasti:---------------\n";
				cout << "|Forma| |Naudotojas| |Slaptazodis|\n";
				tempstring = formname + " " + username;
				menu2(file, tempstring);
				cout << "\n";
			}
			else if (ch2 == 3)
			{
				formname = "";
				cout << "Iveskite formos pavadinima\n";
				cin >> formname;
				cout << "Iveskite slaptazodi kuri keiciam\n";
				cin >> pass1;
				cout << "Iveskite nauja slaptazodi\n";
				cin >> pass2;
				menu3(formname,username,pass1,pass2);
			}
			else if (ch2 == 4)
			{
				formname = "";
				cout << "Iveskite formos pavadinima kuria trinam\n";
				cin >> formname;
				cout << "Iveskite slaptazodi kuri trinam\n";
				cin >> pass1;
				delline = formname + " " + username + " " + pass1;
				menu4("passwords.txt", delline);
			}
		} while (ch2 != 0);

		//encrypting passwords
		infomove(password, temp);

		fileenc(temp, password);
	}
	else return 0;
}