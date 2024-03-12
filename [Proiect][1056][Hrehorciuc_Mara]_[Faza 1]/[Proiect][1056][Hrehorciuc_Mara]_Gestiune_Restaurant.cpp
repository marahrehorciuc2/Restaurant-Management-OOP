#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class ExceptieExistentaDenumire {
	string mesaj;
public:
	ExceptieExistentaDenumire(string mesaj) :mesaj(mesaj) {}
	string getMesaj() { return this->mesaj; }
};

class Preparat {
private:
	string denumire = "-";
	int gramajPortie = 0;
	float nrCalorii = 0;
	int nrIngrediente = 0;
	string* ingrediente = nullptr;
	int* gramajIngrediente = nullptr;
	static int nrCaloriiGram;
public:

	Preparat() {
		this->denumire = "-";
		this->gramajPortie = 0;
		this->nrCalorii = 0;
		this->nrIngrediente = 0;
		this->ingrediente = nullptr;
		this->gramajIngrediente = nullptr;
	}

	void setGramajPortie(int gramajPortieNou) {
		if (gramajPortieNou > 0)
			this->gramajPortie = gramajPortieNou;
		else throw new ExceptieExistentaDenumire("Preparatul trebuie sa aiba un gramaj asociat!");
	}

	int getGramajPortie() {
		return this->gramajPortie;
	}

	Preparat(string denumire, int gramajPortie, float nrCalorii, int nrIngrediente, string* ingrediente, int* gramajIngrediente) {
		if (denumire.length() > 0)
			this->denumire = denumire;
		if (gramajPortie > 0)
			this->gramajPortie = gramajPortie;
		if (nrCalorii > 0)
			this->nrCalorii = nrCalorii;
		if (nrIngrediente > 0) {
			this->nrIngrediente = nrIngrediente;
			this->ingrediente = new string[this->nrIngrediente];
			this->gramajIngrediente = new int[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->ingrediente[i] = ingrediente[i];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->gramajIngrediente[i] = gramajIngrediente[i];
		}
	}

	Preparat(const Preparat& p) {
		if (p.denumire.length() > 0)
			this->denumire = p.denumire;
		if (p.gramajPortie > 0)
			this->gramajPortie = p.gramajPortie;
		if (p.nrCalorii > 0)
			this->nrCalorii = p.nrCalorii;
		if (p.nrIngrediente > 0) {
			this->nrIngrediente = p.nrIngrediente;
			this->ingrediente = new string[this->nrIngrediente];
			this->gramajIngrediente = new int[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->ingrediente[i] = p.ingrediente[i];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->gramajIngrediente[i] = p.gramajIngrediente[i];
		}
	}

	~Preparat() {
		delete[] this->gramajIngrediente;
		this->gramajIngrediente = nullptr;
		delete[] this->ingrediente;
		this->ingrediente = nullptr;
	}

	Preparat& operator=(const Preparat& p) {
		delete[] this->gramajIngrediente;
		this->gramajIngrediente = nullptr;
		delete[] this->ingrediente;
		this->ingrediente = nullptr;
		if (p.denumire.length() > 0)
			this->denumire = p.denumire;
		if (p.gramajPortie > 0)
			this->gramajPortie = p.gramajPortie;
		if (p.nrCalorii > 0)
			this->nrCalorii = p.nrCalorii;
		if (p.nrIngrediente > 0) {
			this->nrIngrediente = p.nrIngrediente;
			this->ingrediente = new string[this->nrIngrediente];
			this->gramajIngrediente = new int[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->ingrediente[i] = p.ingrediente[i];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->gramajIngrediente[i] = p.gramajIngrediente[i];
		}
		return *this;
	}

	friend bool operator==(string denumire, const  Preparat& p) {
		if (p.denumire.length() > 0)
			return denumire == p.denumire;
		else throw new ExceptieExistentaDenumire("Preparatul nu a fost denumit inca!");
	}

	

	Preparat operator-(int gramajDeficitar) {
		if (gramajDeficitar > 0) {
			Preparat p = *this;
			p.gramajPortie -= gramajDeficitar;
			return p;
		}
	}

	Preparat operator+(int gramajSuplimentar) {
		if (gramajSuplimentar > 0) {
			Preparat p = *this;
			p.gramajPortie += gramajSuplimentar;
			return p;
		}
	}

	friend istream& operator>>(istream& in, Preparat& p) {
		delete[] p.ingrediente;
		p.ingrediente = nullptr;
		if (p.denumire.length() > 0)
			cout << "Denumirea preparatului este: ";
		in >> p.denumire;
		if (p.gramajPortie > 0)
			cout << "Gramajul unei portii este: ";
		in >> p.gramajPortie;
		if (p.nrCalorii > 0)
			cout << "Numarul de calorii al unei portii este: ";
		in >> p.nrCalorii;
		if (p.nrIngrediente > 0) {
			p.ingrediente = new string[p.nrIngrediente];
			p.gramajIngrediente = new int[p.nrIngrediente];
			for (int i = 0; i < p.nrIngrediente; i++) {
				cout << "Ingredientul cu numarul " << i << " din reteta este: ";
				in >> p.ingrediente[i];
			}
			for (int i = 0; i < p.nrIngrediente; i++) {
				cout << "Ingredientul cu numarul " << i << " din reteta are gramajul: ";
				in >> p.gramajIngrediente[i];
			}
		}
		return in;
	}


	friend ostream& operator<<(ostream& out, const Preparat& p) {
		if (p.denumire.length() > 0)
			out << "Denumire: " << p.denumire << endl;
		if (p.gramajPortie > 0)
			out << "Gramajul portiei este: " << p.gramajPortie << endl;
		if (p.nrCalorii > 0)
			out << "Numarul de calorii al portiei este: " << p.nrCalorii << endl;
		if (p.nrIngrediente > 0) {
			out << "Numarul de ingrediente este: " << p.nrIngrediente << endl;
			for (int i = 0; i < p.nrIngrediente; i++)
				out << "Ingredientul cu numarul " << i << " din lista este:" << p.ingrediente[i] << endl;
			for (int i = 0; i < p.nrIngrediente; i++)
				out << "Ingredientul cu numarul " << i << " din lista are gramajul:" << p.gramajIngrediente[i] << endl;
		}
		out << "-------------------------------------" << endl;
		return out;
	}

	void afisare() {
		cout << "\n---------AFISARE PREPARAT-----------";
		cout << "\nDenumirea preparatului este: " << this->denumire;
		cout << "\nGramajul unei portii este: " << this->gramajPortie;
		cout << "\nNumarul de calorii al unei portii este: " << this->nrCalorii;
		cout << "\nNumarul de ingrediente necesare este:" << this->nrIngrediente;
		cout << "\nLista ingredientelor si a gramajelor din fiecare: " << endl;
		for (int i = 0; i < this->nrIngrediente; i++)
			cout << this->ingrediente[i] << " : " << this->gramajIngrediente[i] << " grame " << endl;
		cout << "\n----------------------------\n";
	}

	friend class MeniuPreparate;
};

int Preparat::nrCaloriiGram = 30;

class MeniuPreparate {
private:
	int nrPreparate = 0;
	Preparat* preparate = nullptr;
	float* preturiPreparate = nullptr;

public:

	MeniuPreparate(Preparat preparate) {
		this->nrPreparate = 0;
		this->preparate = nullptr;
		this->preturiPreparate = nullptr;
	}

	MeniuPreparate() {
		this->nrPreparate = 0;
		this->preparate = nullptr;
		this->preturiPreparate = nullptr;
	}
	int getnrPreparate() {
		return this->nrPreparate;
	}

	int setnrPreparate(int nrPreparateNou) {
		if (nrPreparateNou > 0)
			this->nrPreparate = nrPreparateNou;
		else throw new ExceptieExistentaDenumire("Trebuie sa avem preparate in meniu!");
	}


	MeniuPreparate(int nrPreparate, Preparat* preparate, float* preturiPreparate) {
		if (nrPreparate > 0) {
			this->nrPreparate = nrPreparate;
			this->preparate = new Preparat[this->nrPreparate];
			this->preturiPreparate = new float[this->nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++)
				this->preparate[i] = preparate[i];
			for (int i = 0; i < this->nrPreparate; i++)
				this->preturiPreparate[i] = preturiPreparate[i];
		}
	}

	
	~MeniuPreparate() {
		delete[] this->preturiPreparate;
		this->preturiPreparate = nullptr;
		delete[] this->preparate;
		this->preparate = nullptr;	
	}

	MeniuPreparate(const MeniuPreparate& m) {
		if (m.nrPreparate > 0) {
			this->nrPreparate = m.nrPreparate;
			this->preparate = new Preparat[this->nrPreparate];
			this->preturiPreparate = new float[this->nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++)
				this->preparate[i] = m.preparate[i];
			for (int i = 0; i < this->nrPreparate; i++)
				this->preturiPreparate[i] = m.preturiPreparate[i];
		}
	}

	

	bool operator<=(const MeniuPreparate& m) {
		if (this->nrPreparate > 0 && m.nrPreparate > 0) {
			if (this->preturiPreparate[this->nrPreparate - 1] <= m.preturiPreparate[m.nrPreparate - 1])
				return true;
			return false;
		}
		else throw exception("Nu toate preparatele au preturi inca, deoarece au fost adaugate recent in meniu!");
	}

	MeniuPreparate& operator=(const MeniuPreparate& m) {
		delete[] this->preturiPreparate;
		this->preturiPreparate = nullptr;
		delete[] this->preparate;
		this->preparate = nullptr;
		if (m.nrPreparate > 0) {
			this->nrPreparate = m.nrPreparate;
			this->preparate = new Preparat[this->nrPreparate];
			this->preturiPreparate = new float[this->nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++)
				this->preparate[i] = m.preparate[i];
			for (int i = 0; i < this->nrPreparate; i++)
				this->preturiPreparate[i] = m.preturiPreparate[i];
		}
			return *this;
	}

	float operator[](int pozitie) {
		if (pozitie >= 0 && pozitie < this->nrPreparate) {
			if (this->preturiPreparate != nullptr) {
				return this->preturiPreparate[pozitie];
			}
		}
	}

	friend istream& operator>>(istream& in, MeniuPreparate& m) {
		delete[] m.preturiPreparate;
		m.preturiPreparate = nullptr;
		delete[] m.preparate;
		m.preparate = nullptr;
		cout << "Numarul de preparate din meniu este: ";
		in >> m.nrPreparate;
		if (m.nrPreparate > 0) {
			m.preparate = new Preparat[m.nrPreparate];
			m.preturiPreparate = new float[m.nrPreparate];
			for (int i = 0; i < m.nrPreparate; i++) {
				cout << "Preparatul cu numarul " << i << " din meniu este: ";
				in >> m.preparate[i];
			}
			for (int i = 0; i < m.nrPreparate; i++) {
				cout << "Pretul preparatului cu numarul " << i << " din meniu este: ";
				in >> m.preturiPreparate[i];
			}
		}
		return in;
	}
	

	friend ostream& operator<<(ostream& out, const MeniuPreparate& m) {
		out << "----------MENIU PREPARATE----------" << endl;
		if (m.nrPreparate > 0) {
			out << "Numarul de preparate din meniu este: " << m.nrPreparate << endl;
			for (int i = 0; i < m.nrPreparate; i++)
				out << "Preparatul cu numarul " << i << " are datele: " <<endl<< m.preparate[i] << endl;
			for (int i = 0; i < m.nrPreparate; i++)
				out << "Preparatul cu numarul " << i << " are pretul: " << m.preturiPreparate[i] << endl;
		} 
		out << "---------------------------------------"<<endl;
		return out;
	}

	void afisare() {
		cout << "\n---------AFISARE MENIU PREPARATE-----------";
		for (int i = 0; i < this->nrPreparate; i++)
			cout << this->preparate[i];
		for (int i = 0; i < this->nrPreparate; i++)
			cout << this->preturiPreparate[i];
	}

};

class MeniuBauturi {
private:
	int nrBauturi = 0;
	string* bauturi = nullptr;
	float* preturiBauturi = 0;

public:
	MeniuBauturi() {
		this->nrBauturi = 0;
		this->bauturi = nullptr;
		this->preturiBauturi = 0;
	}

	int getnrBauturi() {
		return this->nrBauturi;
	}

	int setnrBauturi(int nrBauturiNou) {
		if (nrBauturiNou > 0)
			this->nrBauturi = nrBauturiNou;
		else throw new ExceptieExistentaDenumire("Trebuie sa avem bauturi in meniu!");
	}

	MeniuBauturi(int nrBauturi, string* bauturi, float* preturiBauturi) {
		if (nrBauturi > 0) {
			this->nrBauturi = nrBauturi;
			this->bauturi = new string[this->nrBauturi];
			this->preturiBauturi = new float[this->nrBauturi];
			for (int i = 0; i < this->nrBauturi; i++)
				this->bauturi[i] = bauturi[i];
			for (int i = 0; i < this->nrBauturi; i++)
				this->preturiBauturi[i] = preturiBauturi[i];
		}
	}

		~MeniuBauturi() {
			delete[] this->preturiBauturi;
			this->preturiBauturi = nullptr;
			delete[] this->bauturi;
			this->bauturi = nullptr;
		}

	MeniuBauturi(const MeniuBauturi& b) {
		if (b.nrBauturi > 0) {
			this->nrBauturi = b.nrBauturi;
			this->bauturi = new string[this->nrBauturi];
			this->preturiBauturi = new float[this->nrBauturi];
			for (int i = 0; i < this->nrBauturi; i++)
				this->bauturi[i] = b.bauturi[i];
			for (int i = 0; i < this->nrBauturi; i++)
				this->preturiBauturi[i] = b.preturiBauturi[i];
		}
	}

	MeniuBauturi& operator=(const MeniuBauturi& b) {
		delete[] this->preturiBauturi;
		this->preturiBauturi = nullptr;
		delete[] this->bauturi;
		this->bauturi = nullptr;
		if (b.nrBauturi > 0) {
			this->nrBauturi = b.nrBauturi;
			this->bauturi = new string[this->nrBauturi];
			this->preturiBauturi = new float[this->nrBauturi];
			for (int i = 0; i < this->nrBauturi; i++)
				this->bauturi[i] = b.bauturi[i];
			for (int i = 0; i < this->nrBauturi; i++)
				this->preturiBauturi[i] = b.preturiBauturi[i];
		}
			return *this;
	}


	friend istream& operator>>(istream& in, MeniuBauturi& b) {
		delete[] b.preturiBauturi;
		b.preturiBauturi = nullptr;
		delete[] b.bauturi;
		b.bauturi = nullptr;
		cout << "Numarul de bauturi din meniu este: ";
		in >> b.nrBauturi;
		if (b.nrBauturi > 0) {
			b.bauturi = new string[b.nrBauturi];
			b.preturiBauturi = new float[b.nrBauturi];
			for (int i = 0; i < b.nrBauturi; i++) {
				cout << "Bautura cu numarul " << i << " din meniu este: ";
				in >> b.bauturi[i];
			}
			for (int i = 0; i < b.nrBauturi; i++) {
				cout << "Pretul bauturii cu numarul " << i << " din meniu este: ";
				in >> b.preturiBauturi[i];
			}
		}
		return in;
	}

	friend ostream& operator<<(ostream & out, const MeniuBauturi & b) {
	    out << "----------MENIU BAUTURI----------"<<endl;
		if (b.nrBauturi > 0) {
		 out << "Numarul de bauturi din meniu este: " << b.nrBauturi << endl;
		for (int i = 0; i < b.nrBauturi; i++)
		 out << "Bautura cu numarul " << i << " din meniu este: " << b.bauturi[i] << endl;
		for (int i = 0; i < b.nrBauturi; i++)
		 out << "Bautura cu numarul " << i << " are pretul: " << b.preturiBauturi[i] << endl;
		}
		out << "----------------------------------"<<endl;
		return out;
	}

	void afisare() {
	 cout << "\n---------AFISARE MENIU BAUTURI-----------";
	 for (int i = 0; i < this->nrBauturi; i++)
	 cout << this->bauturi[i];
	 for (int i = 0; i < this->nrBauturi; i++)
	 cout << this->preturiBauturi[i];
	}

};

class Comanda {
private:
	const int id;
	int nrPreparateComandate = 0;
	string* preparateComandate = nullptr;
	int nrBauturiComandate = 0;
	string* bauturiComandate = nullptr;
	float pretComanda = 0;

public:
	Comanda(int id, int nrPreparateComandate, string* preparateComandate, int nrBauturiComandate, string* bauturiComandate, float pretComanda) :id(id) {
		if (nrPreparateComandate > 0) {
			this->nrPreparateComandate = nrPreparateComandate;
			this->preparateComandate = new string[this->nrPreparateComandate];
			for (int i = 0; i < this->nrPreparateComandate; i++)
				this->preparateComandate[i] =preparateComandate[i];
		}
		if (nrBauturiComandate > 0) {
			this->nrBauturiComandate = nrBauturiComandate;
			this->bauturiComandate = new string[this->nrBauturiComandate];
			for (int i = 0; i < this->nrBauturiComandate; i++)
				this->bauturiComandate[i] = bauturiComandate[i];
		}
		if (pretComanda > 0)
			this->pretComanda = pretComanda;
	}

	Comanda(const Comanda& c) :id(c.id) {
		if (c.nrPreparateComandate > 0) {
			this->nrPreparateComandate = c.nrPreparateComandate;
			this->preparateComandate = new string[this->nrPreparateComandate];
			for (int i = 0; i < this->nrPreparateComandate; i++)
				this->preparateComandate[i] = c.preparateComandate[i];
		}
		if (c.nrBauturiComandate > 0) {
			this->nrBauturiComandate = c.nrBauturiComandate;
			this->bauturiComandate = new string[this->nrBauturiComandate];
			for (int i = 0; i < this->nrBauturiComandate; i++)
				this->bauturiComandate[i] = c.bauturiComandate[i];
		}
		if (c.pretComanda > 0)
			this->pretComanda = c.pretComanda;
	} 

	~Comanda() {
		delete[] this->bauturiComandate;
		this->bauturiComandate = nullptr;
		delete[] this->preparateComandate;
		this->preparateComandate = nullptr;
	}


	Comanda& operator=(const Comanda& c) {
		delete[] this->bauturiComandate;
		bauturiComandate = nullptr;
		delete[] this->preparateComandate;
		preparateComandate = nullptr;
		if (c.nrPreparateComandate > 0) {
			this->nrPreparateComandate = c.nrPreparateComandate;
			this->preparateComandate = new string[this->nrPreparateComandate];
			for (int i = 0; i < this->nrPreparateComandate; i++)
				this->preparateComandate[i] = c.preparateComandate[i];
		}
		if (c.nrBauturiComandate > 0) {
			this->nrBauturiComandate = c.nrBauturiComandate;
			this->bauturiComandate = new string[this->nrBauturiComandate];
			for (int i = 0; i < this->nrBauturiComandate; i++)
				this->bauturiComandate[i] = c.bauturiComandate[i];
		}
		if (c.pretComanda > 0)
			this->pretComanda = c.pretComanda;
		return *this;
	}

	bool operator!() {
		if (this->bauturiComandate == nullptr)
			return true;
		return false;
	}

	
	friend istream& operator>>(istream& in, Comanda& c) {
		delete[] c.bauturiComandate;
		c.bauturiComandate = nullptr;
		delete[] c.preparateComandate;
		c.preparateComandate = nullptr;
		cout << "Numarul de preparate comandate este: ";
		in >> c.nrPreparateComandate;
		if (c.nrPreparateComandate > 0) {
			c.preparateComandate = new string[c.nrPreparateComandate];
			for (int i = 0; i < c.nrPreparateComandate; i++) {
				cout << "Preparatul cu numarul " << i << " din comanda este: ";
				in >> c.preparateComandate[i];
			}
		}
		cout << "Numarul de bauturi comandate este: ";
		in >> c.nrBauturiComandate;
		if (c.nrBauturiComandate > 0) {
			c.bauturiComandate = new string[c.nrBauturiComandate];
			for (int i = 0; i < c.nrBauturiComandate; i++) {
				cout << "Bautura cu numarul " << i << " din comanda este: ";
				in >> c.bauturiComandate[i];
			}
		}
		if (c.pretComanda > 0)
			cout << "Pretul comenzii este: ";
		in >> c.pretComanda;
		return in;
	}

	friend ostream& operator<<(ostream& out, const Comanda& c) {
		out << "---------COMANDA---------" << endl;
		out << "ID comanda: " << c.id << endl;
		if (c.nrPreparateComandate > 0) {
			out << "Numarul de preparate comandate este: " << c.nrPreparateComandate << endl;
			for (int i = 0; i < c.nrPreparateComandate; i++)
				out << "Preparatul comandat cu numarul " << i << " este: " << c.preparateComandate[i] << endl;
		}
		if (c.nrBauturiComandate > 0) {
			out << "Numarul de bauturi comandate este: " << c.nrBauturiComandate << endl;
			for (int i = 0; i < c.nrBauturiComandate; i++)
				out << "Bautura comandata cu numarul " << i << " este: " << c.bauturiComandate[i] << endl;
		}
		if (c.pretComanda > 0)
			out << "Pretul total al comenzii este: " << c.pretComanda << endl;
		out << "-----------------------"<<endl;
		return out;
	}

	void afisare() {
		cout << "\n---------AFISARE COMANDA-----------";
		cout << "ID-ul comenzii este: " << this->id;
		cout << "Numarul de preparate comandate este: " << this->nrPreparateComandate;
		for (int i = 0; i < this->nrPreparateComandate; i++)
			cout << this->preparateComandate[i];
		cout << "Numarul de bauturi comandate este: " << this->nrBauturiComandate;
		for (int i = 0; i < this->nrBauturiComandate; i++)
			cout << this->bauturiComandate[i];
		cout << "Pretul total al comenzii este: " << this->pretComanda;
	}
};

class StocMateriiPrime {
private:
	string denumire = "-";
	float cantitate = 0;
	int localizarePeRaft = 0;
	char* furnizor = nullptr;

public:

	void setFurnizor(const char* furnizorNou)
	{
		if (strlen(furnizorNou) > 0)
			strcpy(this->furnizor, furnizorNou);
		else throw new ExceptieExistentaDenumire("Furnizorul trebuie sa aiba nume!");
	}

	char* getFurnizor()
	{
		return this->furnizor;
	}

	void setCantitate(int cantitateNoua) {
		if (cantitateNoua > 0)
			this->cantitate = cantitateNoua;
		else throw new ExceptieExistentaDenumire("Cantitatea trebuie sa fie pozitiva!");
	}

	int getCantitate()
	{
		return this->cantitate;
	}

	int stoc() {
		if (this->cantitate >= 0)
			return 1;
		else return 0;
	}

	StocMateriiPrime(string denumire, int cantitate, int localizarePeRaft, const char* furnizor) {
		if (denumire.length() > 0)
			this->denumire = denumire;
		if (cantitate > 0)
			this->cantitate = cantitate;
		if (localizarePeRaft > 0)
			this->localizarePeRaft = localizarePeRaft;
		if (furnizor != nullptr) {
			this->furnizor = new char[strlen(furnizor) + 1];
			strcpy(this->furnizor, furnizor);
		}
	}

	~StocMateriiPrime() {
		delete[] this->furnizor;
		this->furnizor = nullptr;	
	}

	StocMateriiPrime(const StocMateriiPrime& s) {
		if (s.denumire.length() > 0)
			this->denumire = s.denumire;
		if (s.cantitate > 0)
			this->cantitate = s.cantitate;
		if (s.localizarePeRaft > 0)
			this->localizarePeRaft = s.localizarePeRaft;
		if (s.furnizor != nullptr) {
			this->furnizor = new char[strlen(s.furnizor) + 1];
			strcpy(this->furnizor, s.furnizor);
		}
	}

	StocMateriiPrime& operator=(const StocMateriiPrime& s) {
		delete[] this->furnizor;
		this->furnizor = nullptr;
		if (s.denumire.length() > 0)
			this->denumire = s.denumire;
		if (s.cantitate > 0)
			this->cantitate = s.cantitate;
		if (s.localizarePeRaft > 0)
			this->localizarePeRaft = s.localizarePeRaft;
		if (s.furnizor != nullptr) {
			this->furnizor = new char[strlen(s.furnizor) + 1];
			strcpy(this->furnizor, s.furnizor);
		}
		return *this;
	}

	//forma pre-incrementare
	StocMateriiPrime& operator--() {
		this->cantitate--;
		return *this;//returneaza starea stocului de dupa modificarea acestuia
	}

	//forma post-incrementare
	StocMateriiPrime operator--(int) {
		StocMateriiPrime copie = *this;
		this->cantitate--;
		return copie;//returneaza starea stocului inainte de modificarea acestuia
	}

	explicit operator int() {
		return this->cantitate;
	}

	
	friend istream& operator>>(istream& in, StocMateriiPrime& s) {
		delete[] s.furnizor;
		s.furnizor = nullptr;
		if (s.denumire.length() > 0)
			cout << "Denumirea materiei prime este: ";
		in >> s.denumire;
		if (s.cantitate > 0)
			cout << "Cantitatea pe care o avem din materia prima respectiva este, in kg: ";
		in >> s.cantitate;
		if (s.localizarePeRaft > 0)
			cout << "Materia prima cautata se afla pe raftul cu numarul: ";
		in >> s.localizarePeRaft;
		if (s.furnizor != nullptr) {
			s.furnizor = new char[strlen(s.furnizor) + 1];
			cout << "Furnizorul de la care procuram materia prima respectiva este, in prezent: ";
			in >> s.furnizor;
		}
		return in;
	}

	friend ostream& operator<<(ostream& out, const StocMateriiPrime& s) {
		out << "---------STOCUL MATERIILOR PRIME---------" << endl;
		if (s.denumire.length() > 0)
			out << "Denumirea materiei prime este: " << s.denumire << endl;
		if (s.cantitate > 0)
			out << "Cantitatea pe care o avem din materia prima respectiva este, in kg: " << s.cantitate << endl;
		if (s.localizarePeRaft > 0)
			out << "Materia prima cautata se afla pe raftul cu numarul: " << s.localizarePeRaft << endl;
		if (s.furnizor != nullptr)
			out << "Furnizorul de la care procuram materia prima respectiva este, in prezent: " << s.furnizor << endl;
			out << "-------------------------"<<endl;
			return out;
		}

	void afisare() {
		cout << "\n---------AFISARE STOC-----------";
		cout << "Denumirea materiei prime este: " << this->cantitate;
		cout << "Localizarea pe raft este: " << this->localizarePeRaft;
		cout << "Furnizorul este: " << this->furnizor;
	}

};

	

int main() {
	//materiile prime aflate in stocul nostru, cantitatile lor, localizarea pe raft si furnizorul
	StocMateriiPrime faina("faina", 200, 1, "Selgros");
	StocMateriiPrime apa("apa", 500, 1, "Selgros");
	StocMateriiPrime orez("orez", 60, 2, "Selgros");
	StocMateriiPrime smantana("smantana", 100, 4, "Tudia");
	StocMateriiPrime pieptdepui("piept de pui", 150, 4, "Fragedo");
	StocMateriiPrime sunca("sunca", 50, 4, "SuperStar");
	StocMateriiPrime mozzarella("mozzarella", 50, 4, "Tudia");
	StocMateriiPrime ciuperci("ciuperci", 50, 2, "Metro");
	StocMateriiPrime sosderosii("sos de rosii", 60, 3, "Selgros");
	StocMateriiPrime oua("oua", 100, 4, "Metro");
	StocMateriiPrime paste("paste", 50, 1, "Metro");
	StocMateriiPrime salata("salata verde", 30, 1, "Metro");
	StocMateriiPrime rosii("rosii", 20, 1, "Metro");
	StocMateriiPrime castraveti("castraveti", 20, 1, "Selgros");

	//crearea unui meniu cu preparate si date despre aceste preparate
	string ingredienteAlfredo[5] = { "faina", "smantana", "piept de pui", "ciuperci", "paste" };
	int gramajAlfredo[5] = { 30,100,100,20,200 };
	Preparat pasteAlfredo("Paste Alfredo", 450, 1350, 5, ingredienteAlfredo, gramajAlfredo);

	string ingredientePizza[7] = { "faina", "apa", "sunca", "mozzarella", "ciuperci", "sos de rosii", "oua" };
	int gramajPizza[7] = { 100, 50, 50, 60, 30, 30, 90 };
	Preparat pizza("Pizza", 450, 1350, 7, ingredientePizza, gramajPizza);

	string ingredienteOrez[4] = { "orez", "apa", "piept de pui", "sos de rosii" };
	int gramajOrez[4] = { 100, 50, 50, 60 };
	Preparat orezcuPui("Orez cu piept de pui", 400, 1200, 4, ingredienteOrez, gramajOrez);

	string ingredienteSalata[5] = { "salata verde", "rosii", "piept de pui", "castraveti", "mozzarella" };
	int gramajSalata[5] = { 100, 50, 80, 50, 80 };
	Preparat salatacuPui("Salata cu piept de pui", 500, 1500, 4, ingredienteSalata, gramajSalata);

	Preparat preparateNr1[4] = { pasteAlfredo, pizza, orezcuPui, salatacuPui };
	float preturiNr1[4] = { 37,31,27, 25 };
	MeniuPreparate meniu1(4, preparateNr1, preturiNr1);
	
	//crearea unui meniu cu bauturi
	string bauturiMeniu1[4] = { "Hugo", "Mojito", "Campari Orange", "Gin Tonic" };
	float preturiBauturiMeniu1[4] = { 27, 25, 30, 27};
	MeniuBauturi meniuBauturi1(4, bauturiMeniu1, preturiBauturiMeniu1);

	int optiune;
	int ok = 0;
	while (ok == 0)
	{
		cout << "Alegeti optiunea dorita: " << endl;
		cout << "1.Doresc sa consult meniul de bauturi! " << endl;
		cout << "2.Doresc sa consult meniul de preparate! " << endl;
		cout << "3.Doresc sa comand!" << endl;
		cout << "4.Nu sunt hotarat inca, va rog sa reveniti! " << endl;

		cin >> optiune;
		switch (optiune) {

		case 1: cout << meniuBauturi1;
			break;

		case 2: cout << meniu1;
			break;

		case 3: cout << "Introduceti numarul de bauturi dorite: " << endl;
			int nrBauturiComanda;  cin >> nrBauturiComanda;
			for (int i = 0; i < nrBauturiComanda; i++)
			{
				cout << "Introduceti  numarul corespunzator bauturii dorite din meniu: ";
				int nrB; cin >> nrB;
				if (nrB == 1)
					cout << "Bautura comandata este Hugo" << endl;
				else
					if (nrB == 2)
						cout << "Bautura comandata este Mojito" << endl;

					else
						if (nrB == 3)
							cout << "Bautura comandata este Campari Orange" << endl;
						else
							if (nrB == 4)
								cout << "Bautura comandata este Gin Tonic" << endl;
			}
			cout << "Introduceti numarul de preparate dorite: " << endl;
			int nrPreparateComanda; cin >> nrPreparateComanda;
			for (int i = 0; i < nrPreparateComanda; i++)
			{
				cout << "Introduceti  numarul corespunzator preparatului dorit din meniu: ";
				int nr; cin >> nr;
				if (nr == 1) {
					faina.setCantitate(200);
					--faina;
					smantana.setCantitate(100);
					--smantana;
					pieptdepui.setCantitate(150);
					--pieptdepui;
					ciuperci.setCantitate(50);
					--ciuperci;
					paste.setCantitate(50);
					--paste;
					cout << "Ati comandat paste Alfredo!" << endl;
					//ne dorim sa vedem ce cantitate din fiecare materie prima avem in stoc dupa realizarea unei comenzi cu paste Alfredo
					cout << faina.getCantitate() << endl;
					cout << smantana.getCantitate() << endl;
					cout << pieptdepui.getCantitate() << endl;
					cout << ciuperci.getCantitate() << endl;
					cout << paste.getCantitate() << endl;
				}
				else
					if (nr == 2) {
						faina.setCantitate(100);
						--faina;
						apa.setCantitate(100);
						--apa;
						sunca.setCantitate(50);
						--sunca;
						mozzarella.setCantitate(50);
						--mozzarella;
						ciuperci.setCantitate(30);
						--ciuperci;
						sosderosii.setCantitate(60);
						--sosderosii;
						oua.setCantitate(100);
						--oua;
						cout << "Ati comandat pizza!" << endl;
						//ne dorim sa vedem ce cantitate din fiecare materie prima avem in stoc dupa realizarea unei comenzi cu pizza
						cout << faina.getCantitate() << endl;
						cout << apa.getCantitate() << endl;
						cout << sunca.getCantitate() << endl;
						cout << mozzarella.getCantitate() << endl;
						cout << ciuperci.getCantitate() << endl;
						cout << sosderosii.getCantitate() << endl;
						cout << oua.getCantitate() << endl;
					}
			else
			if (nr == 3) {
				orez.setCantitate(60);
				--orez;
				apa.setCantitate(90);
				--apa;
				pieptdepui.setCantitate(100);
				--pieptdepui;
				sosderosii.setCantitate(40);
				--sosderosii;
				cout << "Ati comandat orez cu pui!" << endl;
				//ne dorim sa vedem ce cantitate din fiecare materie prima avem in stoc dupa realizarea unei comenzi cu orez cu pui
				cout << orez.getCantitate() << endl;
				cout << apa.getCantitate() << endl;
				cout << pieptdepui.getCantitate() << endl;
				cout << sosderosii.getCantitate() << endl;
			}
						else
							if (nr == 4) {
								salata.setCantitate(30);
								--salata;
								rosii.setCantitate(20);
								--rosii;
								castraveti.setCantitate(20);
								--castraveti;
								mozzarella.setCantitate(40);
								--mozzarella;
								cout << "Ati comandat salata cu pui!" << endl;
								//ne dorim sa vedem ce cantitate din fiecare materie prima avem in stoc dupa realizarea unei comenzi cu salata cu pui
								cout << salata.getCantitate() << endl;
								cout << rosii.getCantitate() << endl;
								cout << castraveti.getCantitate() << endl;
								cout << mozzarella.getCantitate() << endl;
							}
			}

if (salata.stoc() == 1 && rosii.stoc() == 1 && sunca.stoc() == 1 && castraveti.stoc() == 1 && mozzarella.stoc() == 1
	&& apa.stoc() == 1 && pieptdepui.stoc() == 1 && faina.stoc() == 1 && sosderosii.stoc() == 1 && ciuperci.stoc() == 1
	&& orez.stoc() == 1 && oua.stoc() == 1 && smantana.stoc() == 1)
			cout << "Comanda a fost plasata cu succes, pofta buna!" << endl;
		else
			cout << "Comanda nu a fost plasata, nu exista suficiente materii prime!" << endl;

			break;
			
		}
	}

	//Mai jos am testat apelul constructorilor si al metodelor 
	
		//apel constructor cu toti parametrii
		string bauturi1[2] = { "Hugo", "Mojito" };
		float preturib1[2] = { 27, 25 };
		MeniuBauturi b1(2, bauturi1, preturib1);
		cout << b1;

		//apel operator=
		string bauturi2[2] = { "Campari Orange", "Gin Tonic" };
		float preturib2[2] = { 30, 27 };
		MeniuBauturi b2(2, bauturi2, preturib2);
		b2 = b1;
		cout << b2;

		//apel constructor copy
		MeniuBauturi b4(b2);
		cout << b4;

		//apel constructor cu toti parametrii
		string ingrediente1[6] = { "Faina", "Apa","Sunca", "Sos de rosii", "Mozzarella", "Busuioc" };
		int gramajIngrediente1[6] = { 200, 100,50,20,40,10 };
		Preparat p1("Pizza", 400, 1200, 6, ingrediente1, gramajIngrediente1);
		cout << p1;

		//apel operator =
		string ingrediente2[5] = { "Salata verde", "Rosii", "Castraveti", "Piept de pui", "Telemea" };
		int gramajIngrediente2[6] = { 80,50,50,70,50 };
		Preparat p2("Salata cu piept de pui", 300, 900, 5, ingrediente2, gramajIngrediente2);
		p2 = p1;
		cout << p2;

		//apel constructor copy
		Preparat p3(p2);
		cout << p3;

		//apel operator -
		string ingrediente4[3] = { "Paste", "Smantana", "Piept de pui" };
		int gramajIngrediente4[3] = { 200, 50, 100 };
		Preparat p4("Paste Alfredo", 450, 1300, 3, ingrediente4, gramajIngrediente4);
		Preparat p5 = p4;
		p5 = p4 - 100;
		cout << p5;

		//apel operator +
		Preparat p6 = p5;
		p6 = p5 + 200;
		cout << p6;

		//apel constructor cu toti parametrii
		string preparateComandate1[2] = { "Paste Alfredo", "Ciorba de burta" };
		string bauturiComandate1[2] = { "Bellini" };
		Comanda c1(1, 2, preparateComandate1, 1, bauturiComandate1, 120);
		cout << c1;


		//apel constructor cu toti parametrii
		StocMateriiPrime s1("faina", 15, 1, "Selgros");
		cout << s1;

		//apel operator =
		StocMateriiPrime s2("orez", 10, 2, "Metro");
		s2 = s1;
		cout << s2;

		//apel constructor copy
		StocMateriiPrime s3(s2);
		cout << s3;

		//apel operator-- forma pre-incrementare
		s3 = --s2;
		cout << s3;

		//apel operator-- forma post-incrementare
		s3 = s2--;
		cout << s3;

		//apelul operatorului cast explicit
		int cantitate = (int)s3;
		cout << cantitate << endl;

		//apel set si get
		s3.setFurnizor("Metro");
		cout << endl << "Noul furnizor este: " << s3.getFurnizor() << endl;
		s3.setCantitate(3);
		cout << endl << "Noua cantitate este: " << s3.getCantitate() << endl;

		return 0;
	
}
