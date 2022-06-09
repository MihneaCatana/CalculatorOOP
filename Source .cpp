#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

//Aceasta clasa o folosim pentru a introduce ecuatiile 
class IntroducereDate {

private:
	char* vectorDeDate;

public:

	//constructor fara parametri 
	IntroducereDate()
	{
		vectorDeDate = nullptr;
	}

	//constructor cu 1 parametru
	IntroducereDate(char* vectorDeDate)
	{
		if (vectorDeDate != nullptr)
		{
			this->vectorDeDate = new char[strlen(vectorDeDate) + 1];
			strcpy_s(this->vectorDeDate, strlen(vectorDeDate) + 1, vectorDeDate);
		}
		else
			this->vectorDeDate = nullptr;
	}

	//getter pentru Vector de Date 
	char* getVectorDeDate()
	{
		if (vectorDeDate != nullptr)
		{
			char* copie = new char[strlen(vectorDeDate) + 1];
			strcpy_s(copie, strlen(vectorDeDate) + 1, vectorDeDate);
			return copie;
		}
		else
			return 0;

	}

	//setter pentru Vector de Date
	void setVectorDeDate(char* vectorDeDate)
	{
		if (vectorDeDate != nullptr)
		{
			this->vectorDeDate = new char[strlen(vectorDeDate) + 1];
			strcpy_s(this->vectorDeDate, strlen(vectorDeDate) + 1, vectorDeDate);
		}
		else
			this->vectorDeDate = nullptr;
	}

	//constructor de copiere 
	IntroducereDate(const IntroducereDate& t)
	{
		if (t.vectorDeDate != nullptr)
		{
			this->vectorDeDate = new char[strlen(t.vectorDeDate) + 1];
			strcpy_s(this->vectorDeDate, strlen(t.vectorDeDate) + 1, t.vectorDeDate);
		}
		else
			this->vectorDeDate = nullptr;
	}

	//supraincarcarea operatorului = 
	IntroducereDate operator=(const IntroducereDate& t)
	{
		if (this != &t)
		{
			delete[] vectorDeDate;
			vectorDeDate = nullptr;

			if (t.vectorDeDate != nullptr)
			{
				this->vectorDeDate = new char[strlen(t.vectorDeDate) + 1];
				strcpy_s(this->vectorDeDate, strlen(t.vectorDeDate) + 1, t.vectorDeDate);
			}
		}
		return *this;
	}

	//destructor
	~IntroducereDate()
	{
		delete[] vectorDeDate;
		vectorDeDate = nullptr;
	}


	//supraincarcarea operatorilor << si >>
	friend ostream& operator<<(ostream&, IntroducereDate);
	friend istream& operator>>(istream&, IntroducereDate&);
};

ostream& operator<<(ostream& out, IntroducereDate t)
{
	out << t.getVectorDeDate();
	return out;
}

istream& operator>>(istream& in, IntroducereDate& t)
{
	string copie;
	in >> copie;
	t.setVectorDeDate((char*)copie.c_str());
	return in;
}

//Aceasta clasa o folosim pentru a prelucra datele primite din prima clasa
class PrelucrareDate {

private:
	float* vectorNumere; // vectorul in care sunt stocate numerele 
	int nrElementeVectorNumere; //nr de elemente din vectorul de numere 
	char* vectorSemne; // folosit pentru a vedea ce semn avem 
	IntroducereDate vectorInitial; // preluam datele introduse 
	int nrErori; //verificam daca ecuatia are erori 
	int* vectorDeValori; // vectorul in care sunt atribuite valori fiecarui caracter
	const int ValoareMaxima = 5;

public:

	//constructor fara parametri 
	PrelucrareDate()
	{
		vectorNumere = nullptr;
		vectorSemne = nullptr;
		nrElementeVectorNumere = 0;
		nrErori = 0;
		vectorDeValori = nullptr;
	}

	//constructor cu parametri 
	PrelucrareDate(IntroducereDate vectorInitial) :PrelucrareDate()
	{
		this->vectorInitial.setVectorDeDate(vectorInitial.getVectorDeDate());
	}

	//constructor de copiere 
	PrelucrareDate(PrelucrareDate& t)
	{
		
		//vector numere 
		if (t.nrElementeVectorNumere > 0 && t.vectorNumere != nullptr)
		{
			this->vectorNumere = new float[t.nrElementeVectorNumere];
			for (int i = 0; i < t.nrElementeVectorNumere; i++)
				vectorNumere[i] = t.vectorNumere[i];
			this->nrElementeVectorNumere = t.nrElementeVectorNumere;
		}
		else
		{
			nrElementeVectorNumere = 0;
			vectorNumere = nullptr;
		}

		//vector initial 
		if (t.vectorInitial.getVectorDeDate() != nullptr)
		{
			vectorInitial = t.vectorInitial;
		}
		else
		{
			vectorInitial.setVectorDeDate(nullptr);
		}

		if (t.vectorSemne != nullptr)
		{
			vectorSemne = new char[strlen(t.vectorSemne) + 1];
			strcpy_s(vectorSemne, strlen(t.vectorSemne) + 1, t.vectorSemne);
		}
		else
			vectorSemne = nullptr;

		//vector valori 
		if (t.vectorDeValori != nullptr)
		{
			vectorDeValori = new int[strlen(t.vectorInitial.getVectorDeDate()) + 1];
			for (int i = 0; i < strlen(t.vectorInitial.getVectorDeDate() + 1); i++)
				vectorDeValori[i] = t.vectorDeValori[i];
		}
		else
		{
			vectorDeValori = nullptr;
		}

		nrErori = t.nrErori;
	}

	//supraincarcarea operatorului = 
	PrelucrareDate operator=(const PrelucrareDate& t)
	{
		if (this != &t)
		{
			delete[] vectorNumere;
			nrElementeVectorNumere = 0;

			delete[] vectorSemne;

			delete[] vectorDeValori;

			//vector numere 
			if (t.nrElementeVectorNumere > 0 && t.vectorNumere != nullptr)
			{
				this->vectorNumere = new float[t.nrElementeVectorNumere];
				for (int i = 0; i < t.nrElementeVectorNumere; i++)
					vectorNumere[i] = t.vectorNumere[i];
				this->nrElementeVectorNumere = t.nrElementeVectorNumere;
			}
			else
			{
				nrElementeVectorNumere = 0;
				vectorNumere = nullptr;
			}

			//vector initial - avem validarile in supraincarcarea operatorului = 
			vectorInitial = t.vectorInitial;

			if (t.vectorSemne != nullptr)
			{
				vectorSemne = new char[strlen(t.vectorSemne) + 1];
				strcpy_s(vectorSemne, strlen(t.vectorSemne) + 1, t.vectorSemne);
			}
			else
				vectorSemne = nullptr;

			//vector valori 
			if (t.vectorDeValori != nullptr)
			{
				vectorDeValori = new int[strlen(vectorInitial.getVectorDeDate()) + 1];
				for (int i = 0; i < strlen(vectorInitial.getVectorDeDate() + 1); i++)
					vectorDeValori[i] = t.vectorDeValori[i];
			}
			else
			{
				vectorDeValori = nullptr;
			}

			nrErori = t.nrErori;
		}
		return *this;
	}


	//eliminam spatiile albe 
	IntroducereDate& EliminareSpatiiAlbe()
	{
		if (vectorInitial.getVectorDeDate() != nullptr)
		{
			for (int i = 0; i < strlen(vectorInitial.getVectorDeDate()) + 1; i++)
			{
				if (vectorInitial.getVectorDeDate()[i] == ' ')
				{
					char* copie = new char[strlen(vectorInitial.getVectorDeDate()) + 100];
					strcpy_s(copie, strlen(vectorInitial.getVectorDeDate()) + 1, vectorInitial.getVectorDeDate());
					strcpy_s(copie + i, strlen(vectorInitial.getVectorDeDate()) + 1, copie + i + 1);
					vectorInitial.setVectorDeDate(copie);
					i--;
				}
			}
		}
		return vectorInitial;
	}

	//atribuim valori pentru a stabili o prioritate in ordinea calculelor
	int* AtribuireValori()
	{
		if (vectorInitial.getVectorDeDate() != nullptr)
		{
			vectorDeValori = new int[strlen(vectorInitial.getVectorDeDate()) + 1];
			for (int i = 0; i < strlen(vectorInitial.getVectorDeDate()) + 1; i++)
			{
				if ('0' <= vectorInitial.getVectorDeDate()[i] && '9' >= vectorInitial.getVectorDeDate()[i])
					vectorDeValori[i] = 0;
				else
					if (vectorInitial.getVectorDeDate()[i] == '+' || vectorInitial.getVectorDeDate()[i] == '-')
						vectorDeValori[i] = 1;
					else
						if (vectorInitial.getVectorDeDate()[i] == '*' || vectorInitial.getVectorDeDate()[i] == '/')
							vectorDeValori[i] = 2;
						else
							if (vectorInitial.getVectorDeDate()[i] == '^' || vectorInitial.getVectorDeDate()[i] == '#')
								vectorDeValori[i] = 3;
							else
								if (vectorInitial.getVectorDeDate()[i] == '[' || vectorInitial.getVectorDeDate()[i] == ']')
									vectorDeValori[i] = 4;
								else
									if (vectorInitial.getVectorDeDate()[i] == '(' || vectorInitial.getVectorDeDate()[i] == ')')
										vectorDeValori[i] = 5;
			}
		}
		return vectorDeValori;
	}

	//verificam erorile si vedem daca apar erori de sintaxa
	int VerificareNrErori()
	{
		nrErori = 0;
		AtribuireValori();
		if (vectorInitial.getVectorDeDate() != nullptr)
		{
			int contor = 0; //folosit atunci cand avem mai multe . .
			for (int i = 0; i < strlen(vectorInitial.getVectorDeDate()) + 1; i++)
			{
				if (vectorInitial.getVectorDeDate()[i] == '.')
					contor++;
				if (vectorInitial.getVectorDeDate()[i] == ' ' || vectorInitial.getVectorDeDate()[i] == '+'
					|| vectorInitial.getVectorDeDate()[i] == '-' || vectorInitial.getVectorDeDate()[i] == '*'
					|| vectorInitial.getVectorDeDate()[i] == '^' || vectorInitial.getVectorDeDate()[i] == '#' || vectorInitial.getVectorDeDate()[i] == '-')
					contor = 0;

				if (vectorDeValori[i] > ValoareMaxima)
					nrErori++;

				if (contor > 1)
					nrErori++;

				if ('a' <= vectorInitial.getVectorDeDate()[i] && 'z' > vectorInitial.getVectorDeDate()[i])
					nrErori++;

				if ('A' < vectorInitial.getVectorDeDate()[i] && 'Z' > vectorInitial.getVectorDeDate()[i])
					nrErori++;

				if (vectorInitial.getVectorDeDate()[i] == '/' && vectorInitial.getVectorDeDate()[i + 1] == '0' && (vectorInitial.getVectorDeDate()[i + 2] != '.' || i == strlen(vectorInitial.getVectorDeDate()) - 2))
					nrErori++;
			}
		}
		return nrErori;
	}

	//realizare vectori de numere

	float* FormareVectorNumere()
	{
		vectorNumere = new float[100]; // am stabilit limita la 100 de numere
		nrElementeVectorNumere = 0;
		float k = 0;  // variabila in care construim numerele ce vor fi introduse in vectorul de numere
		int subunitar = 0; // o sa folosim aceasta variabila pentru a construi numerele cu virgula - folosit pentru detectare 
		int cifra = 0;  //variabila in care preluam cifra 
		int p = -1; // folosit pentru a construi numerel cu virgula - folosit pentru construirea propriu zisa - e initializat cu -1 pt ca la prima zecimala sa fie egal cu 1 

		if (vectorInitial.getVectorDeDate() != nullptr)
		{

			for (int i = 0; i < strlen(vectorInitial.getVectorDeDate()) + 1; i++)
			{
				if (vectorInitial.getVectorDeDate()[i] == '(' || vectorInitial.getVectorDeDate()[i] == ')')  // scoatem cazul parantezelor si folosim un if gol
				{

				}
				else
				{
					int contor = 0; // vedem daca va indeplini una dintre cele 2 conditii ( daca este cifra sau . )
					if (vectorInitial.getVectorDeDate()[i] == '.')
					{
						subunitar = 1;
						contor++;
					}

					if (subunitar == 1)
						p++;

					if ('0' <= vectorInitial.getVectorDeDate()[i] && '9' >= vectorInitial.getVectorDeDate()[i])
					{
						cifra = vectorInitial.getVectorDeDate()[i] - '0';
						contor++;
					}



					if (contor == 0) //daca nu este nici cifra si nici punct, se introduce numarul in vector
					{
						p = -1;
						subunitar = 0;
						vectorNumere[nrElementeVectorNumere] = k;
						nrElementeVectorNumere++;
						k = 0;
					}
					else // se continua construirea numarului ce va fi introdus in vector
						if (vectorInitial.getVectorDeDate()[i] != '.')
						{
							if (subunitar == 0)
							{
								k = k * 10 + cifra;
							}
							else
								k = k + cifra * pow(0.1, p);
						}

				}

			}

		}
		return vectorNumere;
	}

	//formarea vectorului de semne 
	char* FormareVectorSemne()
	{
		if (vectorInitial.getVectorDeDate() != nullptr)
		{
			int c = 0;  //contor
			vectorSemne = new char[strlen(vectorInitial.getVectorDeDate()) + 1];
			for (int i = 0; i < strlen(vectorInitial.getVectorDeDate()) + 1; i++)
				if (vectorInitial.getVectorDeDate()[i] == '*' || vectorInitial.getVectorDeDate()[i] == '/' || vectorInitial.getVectorDeDate()[i] == '^' ||
					vectorInitial.getVectorDeDate()[i] == '#' || vectorInitial.getVectorDeDate()[i] == '+' || vectorInitial.getVectorDeDate()[i] == '-' ||
					vectorInitial.getVectorDeDate()[i] == '[' || vectorInitial.getVectorDeDate()[i] == ']' ||
					vectorInitial.getVectorDeDate()[i] == '(' || vectorInitial.getVectorDeDate()[i] == ')')
				{
					vectorSemne[c] = vectorInitial.getVectorDeDate()[i];
					c++;
				}
			vectorSemne[c] = '\0';
		}

		return vectorSemne;
	}
	//am realizat o functie unde se apeleaza toate functiile realizate de pana acum 
	PrelucrareDate RealizareaFunctiilor()
	{
		//mai intai eliminam spatiile albe si dupa formam vectorii

		EliminareSpatiiAlbe();

		AtribuireValori();

		VerificareNrErori();

		FormareVectorNumere();

		FormareVectorSemne();

		return *this;
	}

	//getteri 

	int getNrElementeVector()
	{
		return nrElementeVectorNumere;
	}

	int getNrErori()
	{
		return nrErori;
	}

	int getValoareMaxima()
	{
		return ValoareMaxima;
	}

	int* getVectoriValori()
	{
		if (nrElementeVectorNumere > 0 && vectorDeValori != nullptr)
		{
			int* copie = new int[strlen(vectorInitial.getVectorDeDate()) + 1];
			for (int i = 0; i < strlen(vectorInitial.getVectorDeDate()) + 1; i++)
				copie[i] = vectorDeValori[i];
			return copie;
		}
		else
			return nullptr;

	}

	float* getVectoriNumere()
	{
		if (nrElementeVectorNumere > 0 && vectorNumere != nullptr)
		{
			float* copie = new float[nrElementeVectorNumere];
			for (int i = 0; i < nrElementeVectorNumere; i++)
				copie[i] = vectorNumere[i];
			return copie;
		}
		else
			return nullptr;
	}

	char* getVectorSemne()
	{
		if (vectorSemne != nullptr)
		{
			char* copie = new char[strlen(vectorSemne) + 1];
			strcpy_s(copie, strlen(vectorSemne) + 1, vectorSemne);
			return copie;
		}
		else
			return nullptr;
	}

	char* getVectorInitial()
	{
		if (vectorInitial.getVectorDeDate() != nullptr)
		{
			char* copie = new char[strlen(vectorInitial.getVectorDeDate()) + 1];
			strcpy_s(copie, strlen(vectorInitial.getVectorDeDate()) + 1, vectorInitial.getVectorDeDate());
			return copie;
		}
		else
			return nullptr;
	}


	//setter vectorSemne
	void setVectorSemne(char* vectorSemne)
	{
		if (vectorSemne != nullptr)
		{
			this->vectorSemne = new char[strlen(vectorSemne) + 1];
			strcpy_s(this->vectorSemne, strlen(vectorSemne) + 1, vectorSemne);
		}
		else
			this->vectorSemne = nullptr;
	}


	//destructorul 
	~PrelucrareDate()
	{
		delete[] vectorNumere;
		nrElementeVectorNumere = 0;

		delete[] vectorSemne;

		delete[] vectorDeValori;
	}
};

//Aceasta clasa este folosita pentru a afisa rezultatul 
class Rezultat {

private:
	static string Eroare;
	PrelucrareDate date;
	float solutie;


public:

	//constructor fara parametri 
	Rezultat()
	{
		solutie = 0;
	}

	//constructor cu un parametru
	Rezultat(PrelucrareDate& t) :Rezultat()
	{
		date = t;
	}

	//constructor de copiere
	Rezultat(Rezultat& t)
	{
		solutie = t.solutie;
		date = t.date;
		Eroare = t.Eroare;
	}

	//supraincarcarea operatorului egal 
	Rezultat operator=(const Rezultat& t)
	{
		if (this != &t)
		{
			solutie = t.solutie;
			date = t.date;
			Eroare = t.Eroare;
		}
		else
		{
			solutie = 0;
		}
	}

	float ObtinereRezultatFaraOrdine() //folosit daca * , / sunt in ordine , prioritatea semnelor nefiind luata in calcul
	{

		if (date.getNrElementeVector() != 0)
		{
			int j = 0;
			solutie = date.getVectoriNumere()[j];
			j++;

			for (int i = 0; i < strlen(date.getVectorSemne()); i++)
			{
				switch (date.getVectorSemne()[i])
				{
				case '+':
					solutie = solutie + date.getVectoriNumere()[j];
					j++;
					break;

				case '-':
					solutie = solutie - date.getVectoriNumere()[j];
					j++;
					break;

				case '*':
					solutie = solutie * date.getVectoriNumere()[j];
					j++;
					break;

				case '/':
					solutie = solutie / date.getVectoriNumere()[j];
					j++;
					break;

				case '^':
					solutie = pow(solutie, date.getVectoriNumere()[j]);
					j++;
					break;

				case '#':
					solutie = pow(solutie, 1 / date.getVectoriNumere()[j]);
					j++;
					break;
				}

			}

		}
		return solutie;
	}

	float ObtinereRezultatCuOrdine() // prioritatea semnelor fiind luata in calcul
	{

		if (date.getNrElementeVector() != 0)
		{
			int contor = 0;

			//facem o copie pentru vectorul de semne si pentru nr de elemente + vectorulul de numere
			char* copieSemne = new char[strlen(date.getVectorSemne()) + 1];
			strcpy_s(copieSemne, strlen(date.getVectorSemne()) + 1, date.getVectorSemne());

			//facem o copie pentru vectorul de numere + nr de elemente
			int nrElementeCopieNumere = date.getNrElementeVector();
			float* copieNumere = new float[nrElementeCopieNumere];
			for (int i = 0; i < nrElementeCopieNumere; i++)
				copieNumere[i] = date.getVectoriNumere()[i];


			/* Modificam sirul pentru operatiile ^ si #   */
			for (int i = 0; i < strlen(copieSemne); i++)
			{
				if (copieSemne[i] == '^')
				{
					copieNumere[i] = pow(copieNumere[i], copieNumere[i + 1]);  //se realizeaza operatia 

					//se elimina semnul din vector
					strcpy_s(copieSemne + i, strlen(copieSemne), copieSemne + i + 1);

					//se elimina numarul din vector
					for (int p = i + 1; p < nrElementeCopieNumere; p++)
						copieNumere[p] = copieNumere[p + 1];
					nrElementeCopieNumere--;

					i--;
				}

				if (copieSemne[i] == '#')
				{
					copieNumere[i] = pow(copieNumere[i], 1 / copieNumere[i + 1]);//se realizeaza operatia 

					//se elimina semnul din vector
					strcpy_s(copieSemne + i, strlen(copieSemne), copieSemne + i + 1);

					//se elimina numarul din vector
					for (int p = i + 1; p < nrElementeCopieNumere; p++)
						copieNumere[p] = copieNumere[p + 1];
					nrElementeCopieNumere--;

					i--;

				}


			}


			/* Modificam sirul si pentru operatiile * si / */
			for (int i = 0; i < strlen(copieSemne); i++)
			{
				if (copieSemne[i] == '*')
				{

					if (copieNumere[i] != 0 && copieNumere[i + 1] != 0)
						copieNumere[i] = copieNumere[i] * copieNumere[i + 1];  //se realizeaza operatia 
					else
						copieNumere[i] = 0;

					//se elimina semnul din vector
					strcpy_s(copieSemne + i, strlen(copieSemne), copieSemne + i + 1);

					//se elimina numarul din vector
					for (int p = i + 1; p < nrElementeCopieNumere; p++)
						copieNumere[p] = copieNumere[p + 1];
					nrElementeCopieNumere--;

					i--;
				}

				if (copieSemne[i] == '/')
				{
					copieNumere[i] = copieNumere[i] / copieNumere[i + 1];//se realizeaza operatia 

					//se elimina semnul din vector
					strcpy_s(copieSemne + i, strlen(copieSemne), copieSemne + i + 1);

					//se elimina numarul din vector
					for (int p = i + 1; p < nrElementeCopieNumere; p++)
						copieNumere[p] = copieNumere[p + 1];
					nrElementeCopieNumere--;

					i--;

				}


			}

			/* Modificam functia de mai sus pentru a se potrivi pe vectorul nostru modificat */
			int j = 0;
			solutie = copieNumere[j];
			j++;

			for (int i = 0; i < strlen(copieSemne); i++)
			{
				switch (copieSemne[i])
				{
				case '+':
					solutie = solutie + copieNumere[j];
					j++;
					break;

				case '-':
					solutie = solutie - copieNumere[j];
					j++;
					break;

				case '*':
					if (solutie == 0 || copieNumere[j] == 0)
						solutie = 0;
					else {
						solutie = solutie * copieNumere[j];
						j++;
					}
					break;

				case '/':
					solutie = solutie / copieNumere[j];
					j++;
					break;

				case '^':
					solutie = pow(solutie, date.getVectoriNumere()[j]);
					j++;
					break;

				case '#':
					solutie = pow(solutie, 1 / date.getVectoriNumere()[j]);
					j++;
					break;
				}

			}

		}
		return solutie;
	}

	//Verificam daca ecuatia introdusa are erori si afisam un mesaj 
	string VerificamEroare()
	{
		if (date.getNrErori() != 0)
			return Eroare;
		return "Nu avem erori";
	}

	// in aceasta functie este luata in calcul prioritatea semnelor si existenta parantezelor rotunde
	float EcuatiiCuParanteze()
	{
		int contor = 1;

		char* sirModificat = new char[strlen(date.getVectorInitial()) + 1];
		strcpy_s(sirModificat, strlen(date.getVectorInitial()) + 1, date.getVectorInitial());

		do
		{
			int pozInceput = -1;
			int pozFinal = -1;
			contor = 0;

			for (int i = 0; i < strlen(sirModificat); i++)
			{
				if (sirModificat[i] == '(' && pozInceput == -1)
					pozInceput = i;
				else
					if (sirModificat[i] == ')')
					{
						pozFinal = i;
						contor++;
						break;
					}
			}

			if (contor != 0)
			{
				char* copieFaraParanteze = new char[pozFinal - pozInceput + 2];
				int k = 0;
				for (int i = pozInceput + 1; i < pozFinal; i++)
				{
					copieFaraParanteze[k] = sirModificat[i];
					k++;
				}

				copieFaraParanteze[k] = '\0';

				PrelucrareDate solutie(copieFaraParanteze);
				solutie.RealizareaFunctiilor();
				Rezultat paranteza(solutie);
				paranteza.ObtinereRezultatCuOrdine();

				float b = paranteza.ObtinereRezultatCuOrdine();
				string rez = to_string(b);

				char* sir1 = new char[strlen(sirModificat) + 1];
				strcpy_s(sir1, strlen(sirModificat) + 1, sirModificat);
				sir1[pozInceput] = '\0';

				string str1(sir1);

				char* sir2 = new char[strlen(sirModificat) + 1];
				strcpy_s(sir2, strlen(sirModificat) + 1, sirModificat + pozFinal + 1);

				string str2(sir2);

				str1 = str1 + rez;

				str1 = str1 + sir2;

				strcpy_s(sirModificat, strlen(str1.c_str()) + 1, str1.c_str());
			}


		} while (contor == 1);

		PrelucrareDate a1(sirModificat);
		a1.RealizareaFunctiilor();
		Rezultat f1(a1);
		float b = f1.ObtinereRezultatCuOrdine();
		return b;
	}

	//modificarea erorii 
	static string ModificaEroarea(string Eroare)
	{
		Rezultat::Eroare = Eroare;
	}

	float EcuatiecuParantezeDrepte() //aici sunt luate in considerare toate cazurile posibile 
	{
		int contor1 = 1;
		int transformare = 0;

		char* sirModificatDrepte = new char[strlen(date.getVectorInitial()) + 1];
		strcpy_s(sirModificatDrepte, strlen(date.getVectorInitial()) + 1, date.getVectorInitial());

		do
		{
			int pozInceput = -1;
			int pozFinal = -1;
			contor1 = 0;

			for (int i = 0; i < strlen(sirModificatDrepte); i++)
			{
				if (sirModificatDrepte[i] == '(' && pozInceput == -1)
					pozInceput = i;
				else
					if (sirModificatDrepte[i] == ')')
					{
						pozFinal = i;
						contor1++;
						break;
					}

			}

			if (contor1 != 0)
			{
				char* copieFaraParanteze = new char[pozFinal - pozInceput + 2];
				int k = 0;
				for (int i = pozInceput + 1; i < pozFinal; i++)
				{
					copieFaraParanteze[k] = sirModificatDrepte[i];
					k++;
				}

				copieFaraParanteze[k] = '\0';

				char* sir1 = new char[strlen(sirModificatDrepte) + 1];
				strcpy_s(sir1, strlen(sirModificatDrepte) + 1, sirModificatDrepte);
				sir1[pozInceput] = '\0';

				string str1(sir1);

				char* sir2 = new char[strlen(sirModificatDrepte) + 1];
				strcpy_s(sir2, strlen(sirModificatDrepte) + 1, sirModificatDrepte + pozFinal + 1);

				string str2(sir2);

				PrelucrareDate a1(copieFaraParanteze);
				a1.RealizareaFunctiilor();
				Rezultat f1(a1);
				float b = f1.ObtinereRezultatCuOrdine();
				string rez = to_string(b);

				str1 = str1 + rez;

				str1 = str1 + sir2;

				strcpy_s(sirModificatDrepte, strlen(str1.c_str()) + 1, str1.c_str());
			}

			if (contor1 == 0 && transformare == 0)
			{
				transformare = 1;
				contor1 = 1;

				for (int i = 0; i < strlen(sirModificatDrepte); i++)
				{
					if (sirModificatDrepte[i] == '[')
						sirModificatDrepte[i] = '(';

					if (sirModificatDrepte[i] == ']')
						sirModificatDrepte[i] = ')';
				}
			}

		} while (contor1 == 1);
		PrelucrareDate a1(sirModificatDrepte);
		a1.RealizareaFunctiilor();
		Rezultat f1(a1);
		float b = f1.ObtinereRezultatCuOrdine();
		return b;
	}

	//getter Eroare
	string getEroare()
	{
		return Eroare;
	}
};

string Rezultat::Eroare = "Ecuatia ta are probleme si nu poate fi calculata ";

void RulareInMainConsola(string sirIntrare) // functie in care se face afiseaza in consola rezultatul 
{
	char* sirConvertit = new char[sirIntrare.length()];
	strcpy_s(sirConvertit, sirIntrare.length() + 1, sirIntrare.c_str());
	IntroducereDate t2(sirConvertit);
	PrelucrareDate p1(t2);
	p1.RealizareaFunctiilor();
	Rezultat sol(p1);

	if (sol.VerificamEroare() != sol.getEroare())
	{
		cout << endl;
		cout << sol.EcuatiecuParantezeDrepte() << endl;
	}
	else
	{
		cout << endl;
		cout << sol.VerificamEroare() << endl;
	}
}

void RulareDinConsolaInFisier(string sirIntrare, string numeFisierIesire)
{
	ofstream g;
	g.open(numeFisierIesire, ios::out);
	char* sirConvertit = new char[sirIntrare.length()];
	strcpy_s(sirConvertit, sirIntrare.length() + 1, sirIntrare.c_str());
	IntroducereDate t2(sirConvertit);
	PrelucrareDate p1(t2);
	p1.RealizareaFunctiilor();
	Rezultat sol(p1);
	if (sol.VerificamEroare() != sol.getEroare())
	{

		g << sol.EcuatiecuParantezeDrepte() << endl;
	}
	else
	{
		g << sol.VerificamEroare() << endl;
	}
}


void RulareInMainFisier(string numeFisierIntrare, string numeFisierIesire) // functie pentru afisarea in fisierul de iesire a datelor din fisierul de intrare
{


	ofstream g;
	g.open(numeFisierIesire, ios::out);
	ifstream f;
	f.open(numeFisierIntrare, ios::in);
	while (!f.eof())
	{
		string sirFisier;
		getline(f, sirFisier);
		char* sirConvertit = new char[sirFisier.length()];
		strcpy_s(sirConvertit, sirFisier.length() + 1, sirFisier.c_str());
		IntroducereDate t2(sirConvertit);
		PrelucrareDate p1(t2);
		p1.RealizareaFunctiilor();
		Rezultat sol(p1);
		if (sol.VerificamEroare() != sol.getEroare())
		{
			g << sol.EcuatiecuParantezeDrepte() << endl;
		}
		else
		{
			g << endl;
			g << sol.VerificamEroare() << endl;
		}
	}

}

void SalvareBinar(string numeFisierIesire, string sirIntrare)
{
	ofstream bf(numeFisierIesire, ios::out | ios::binary | ios::app);

	char* sirConvertit = new char[sirIntrare.length()];
	strcpy_s(sirConvertit, sirIntrare.length() + 1, sirIntrare.c_str());
	IntroducereDate t2(sirConvertit);
	PrelucrareDate p1(t2);
	p1.RealizareaFunctiilor();
	Rezultat sol(p1);
	if (sol.VerificamEroare() != sol.getEroare())
	{

		bf << sol.EcuatiecuParantezeDrepte() << endl;
	}
	else
	{
		bf << sol.EcuatiecuParantezeDrepte() << endl;
	}
}

void RulareDinCommandLine(int n, char* sir[]) //rularea din command line a unei singure ecuatii
{
	/*cout << n << endl;  -- in caz ca vrem sa afisam ecuatia scrisa,numele programului si numarul de
	for (int i = 0; i < n; i++) {
		cout << sir[i] << endl;
	}*/

	if (n == 2)
	{
		string sirComandLine = sir[1];
		RulareInMainConsola(sirComandLine);
	}
	else
	{
		if (n == 1)
			cout << "Nu ai introdus destule ecuatii";
		else
			cout << "Introdu o singura ecuatie";
	}
}

void Meniu(int variabila)
{
	cout << "------------------------------------------------------------------------------------------------------------------------";
	cout << endl;
	cout << "|                                                      Bine ai venit!                                                  |" << endl;

	int contor = 0;

	cout << endl;
	cout << endl;
	cout << "Operatiile posibile sunt:" << endl;
	cout << "Introducere ecuatie, calcularea acesteia si afisarea in consola - 1 " << endl;
	cout << "Calcularea ecuatiilor din fisierul de intrare si afisarea rezultatelor in fisierul FisierIesire - 2 " << endl;
	cout << "Introducere ecuatie, calcularea acesteia si afisarea in fisier - 3 " << endl;
	cout << "Introducere ecuatie si afisarea acesteia - 4" << endl;
	cout << "Oprire program - 0" << endl;
	while (contor != 1)
	{
		cout << endl;
		cout << "Tastati numarul operatiei dorite: ";
		int numar;
		cin >> numar;

		string sirEcuatie;

		switch (numar)
		{
		case 1:
			cout << "Introducere ecuatie si calcularea acesteia: ";
			cin.ignore(1000, '\n');
			getline(cin, sirEcuatie);
			RulareInMainConsola(sirEcuatie);
			if (variabila == 1)
				SalvareBinar("Fisier.bin", sirEcuatie);
			break;
		case 2:
			RulareInMainFisier("fisierIntrare.txt", "fisierIesire.txt");
			break;
		case 3:
			cout << "Introducere ecuatie si calcularea acesteia: ";
			cin.ignore(1000, '\n');
			getline(cin, sirEcuatie);
			RulareDinConsolaInFisier(sirEcuatie, "fisierIesire.txt");
			if (variabila == 1)
				SalvareBinar("Fisier.bin", sirEcuatie);
			break;
		case 4:
			cout << "Introducere ecuatie: ";
			cin.ignore(1000, '\n');
			getline(cin, sirEcuatie);
			cout << sirEcuatie;
			if (variabila == 1)
				SalvareBinar("Fisier.bin", sirEcuatie);
			break;
		case 0:
			cout << "Oprire program " << endl;
			contor = 1;
			break;
		default:
			cout << "Caracterul nu se exista in lista predefinita!" << endl;
			break;
		}
	}
}


int main(int argc, char* argv[])
{
	//testing

	if (argc == 2)
	{
		RulareDinCommandLine(argc, argv);
	}
	else
	{
		int contorizare = 0;
		cout << "Doriti sa salvati datele intr-un fisier binar? DA/NU " << endl;
		string propozitie;
		cin >> propozitie;
		if (propozitie == "DA")
			contorizare = 1;

		Meniu(contorizare);
	}



	//RulareInMainFisier("fisierIntrare.txt", "fisierIesire.txt");

}