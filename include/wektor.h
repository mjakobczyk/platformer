#ifndef WEKTOR_H_
#define WEKTOR_H_

template <typename T> std::ostream & operator<< (std::ostream & str, const Wektor<T> & w);

template <typename T>
class Wektor
{
	T * values;
	int size;
	int capacity;

public:
	Wektor();
	Wektor(int);
	Wektor(const Wektor &);
	~Wektor();

	int pobierzWielkosc() { return size; }
	void dodaj(T&);
	void dodaj(T*);
	int szukaj(const T&);
	bool usun(T&);
	bool zamien(T&, T&);
	bool zamien(T*&, T*&);
	bool czyPusty();

	Wektor & operator=(const Wektor&);
	T & operator[](int idx) const;

	friend std::ostream & operator<< <T> (std::ostream&, const Wektor<T>&);
};

//_______________________________________________________________________

// Konstruktor bezargumentowy
template <typename T>
Wektor<T>::Wektor()
{
	values = new T[16];
	size = 0;
	capacity = 16;
}

//_______________________________________________________________________

// Konstruktor z argumentem d³ugoœci wektora
template <typename T>
Wektor<T>::Wektor(int val)
{
	T = new T(val);
	size = 0;
	capacity = val;
}

//_______________________________________________________________________

// Konstruktor inicjalizacuj¹cy jeden wektor innym wektorem
template <typename T>
Wektor<T>::Wektor(const Wektor & w)
{
	this->size = w->size;
	this->capacity = w->capacity;
	for (int i = 0; i < this->size; ++i)
		this->values[i] = w->values[i];
}

//_______________________________________________________________________

// Destruktor
template <typename T>
Wektor<T>::~Wektor()
{
	delete[] values;
	values = nullptr;
	size = 0;
	capacity = 0;
}

//_______________________________________________________________________

// Metoda dodaj¹ca nowy element do wektora
template <typename T>
void Wektor<T>::dodaj(T & val)
{
	// Je¿eli w danym momencie rozmiar wektora przewy¿sza jego mo¿liwoœci pod wzglêdem
	// zaalokowanej pamiêci, to nale¿y zwiêkszyæ jego rozmiar. Za ka¿dym razem zwiêkszany
	// jest on dwukrotnie powiêkszany. Aby mechanizm dzia³a³ poprawnie, tworzymy tymczasow¹
	// tablicê elementów, do której przepisujemy zawartoœæ wektora, na rzecz któregó jest
	// wywo³ywana metoda. Nastêpnie usuwamy star¹ zawartoœæ i przypisujemy do wskaŸnika
	// 'values' 2-krotnie powiekszon¹ tablicê.
	if (size >= capacity && capacity > 0)
	{
		capacity = capacity * 2;
		T * temp = new T[capacity];
		for (int i = 0; i < size; ++i)
		{
			temp[i] = this->values[i];
		}
		if (values) delete[] values;
		values = temp;
	}

	values[size] = val;
	++size;

	return;
}

//_______________________________________________________________________

// Metoda dodaj¹ca nowy element do wektora
template <typename T>
void Wektor<T>::dodaj(T * val)
{
	// Je¿eli w danym momencie rozmiar wektora przewy¿sza jego mo¿liwoœci pod wzglêdem
	// zaalokowanej pamiêci, to nale¿y zwiêkszyæ jego rozmiar. Za ka¿dym razem zwiêkszany
	// jest on dwukrotnie powiêkszany. Aby mechanizm dzia³a³ poprawnie, tworzymy tymczasow¹
	// tablicê elementów, do której przepisujemy zawartoœæ wektora, na rzecz któregó jest
	// wywo³ywana metoda. Nastêpnie usuwamy star¹ zawartoœæ i przypisujemy do wskaŸnika
	// 'values' 2-krotnie powiekszon¹ tablicê.
	if (size >= capacity && capacity > 0)
	{
		capacity = capacity * 2;
		T * temp = new T[capacity];
		for (int i = 0; i < size; ++i)
		{
			temp[i] = this->values[i];
		}
		if (values) delete[] values;
		values = temp;
	}

	values[size] = *val;
	++size;

	return;
}

//_______________________________________________________________________

// Metoda wyszukuj¹ca element zwraca jego indeks, jeœli istnieje
template <typename T>
int Wektor<T>::szukaj(const T & val)
{
	// W pêtli iterujemy po wszystkich elementach wektora porównuj¹c ich
	// wartoœci z wartoœci¹ podan¹ jako argument metody. Metoda zwraca
	// indeks elementu w przypadku jego znalezienia. Jeœli element nie
	// zosta³ znaleziony, to zwracan¹ wartoœci¹ jest -1.
	for (int i = 0; i < size; ++i)
	{
		if (values[i] == val)
			return i;
	}

	return -1;
}

//_______________________________________________________________________

// Metoda usuwaj¹ca wyznaczony element z wektora
template <typename T>
bool Wektor<T>::usun(T & val)
{
	// Przed usuniêciem elementu nale¿y sprawdziæ, czy faktycznie nale¿y
	// on do kontenera. Z tego powodu wywo³ywana jest metoda szukaj().
	if (szukaj(val) == -1) return false;

	// Jeœli znaleziono element nastêpuje jeszcze jedno sprawdzenie czy
	// indeks ten jest poprawny. W tym celu musi byæ równy co najmniej 0,
	// a conajwy¿ej tyle, co wielkoœæ kontenera - 1. Jeœli sprawdzenie siê
	// powiedzie to nastêpuje przepisanie wszystkich elementów o jedno
	// miejsce w lewo. Po wykonanych operacjach nastêpuje dekrementacja
	// wielkoœci wektora.
	if (szukaj(val) >= 0 && szukaj(val) < size)
	{
		for (int i = szukaj(val) + 1; i < size; ++i)
			values[i - 1] = values[i];
		--size;
		return true;
	}

	// W ca³ej reszcie przypadków je¿eli indeks siê nie zgadza, to metoda
	// zwraca fa³sz.
	return false;
}

//_______________________________________________________________________

// Metoda zamieniaj¹ca miejscami dwa elementy wektora
template <typename T>
bool Wektor<T>::zamien(T & val1, T & val2)
{
	// Najpierw nastêpuje sprawdzenie czy elementy nale¿¹ do wektora.
	// Je¿eli ich indeksy s¹ równe -1 to znaczy, ¿e nie s¹ elementami
	// kontera.
	if (szukaj(val1) <= -1 && szukaj(val2) <= -1) return false;

	T temp;

	// Je¿eli indeksy po kolejnym sprawdzeniu siê zgadzaj¹, to nastêpuje
	// zamiana wartoœci elementów o podanych indeksach.
	if (szukaj(val1) >= 0 && szukaj(val1) < size &&
		szukaj(val2) >= 0 && szukaj(val2) < size)
	{
		temp = val1;
		values[szukaj(val1)] = val2;
		values[szukaj(val2)] = temp;

		return true;
	}

	// W ca³ej reszcie przypadków zwracamy fa³sz.
	return false;
}

//_______________________________________________________________________

// Metoda zamieniaj¹ca miejscami dwa elementy wektora
template <typename T>
bool Wektor<T>::zamien(T * & val1, T * & val2)
{
	// Najpierw nastêpuje sprawdzenie czy elementy nale¿¹ do wektora.
	// Je¿eli ich indeksy s¹ równe -1 to znaczy, ¿e nie s¹ elementami
	// kontera.
	if (szukaj(val1) <= -1 && szukaj(val2) <= -1) return false;

	T * temp = nullptr;

	// Je¿eli indeksy po kolejnym sprawdzeniu siê zgadzaj¹, to nastêpuje
	// zamiana wartoœci elementów o podanych indeksach.
	if (szukaj(val1) >= 0 && szukaj(val1) < size &&
		szukaj(val2) >= 0 && szukaj(val2) < size)
	{
		*temp = *val1;
		*(values[szukaj(val1)]) = *val2;
		*(values[szukaj(val2)]) = *temp;

		return true;
	}

	// W ca³ej reszcie przypadków zwracamy fa³sz.
	return false;
}

//_______________________________________________________________________

// Metoda sprawdzaj¹ca czy kontener zawiera jakieœ dane
template <typename T>
bool Wektor<T>::czyPusty()
{
	if (size <= 0) return true;
	else return false;
}

//_______________________________________________________________________

// Operator= przypisuj¹cy obiekt innemu obiektowi
template <typename T>
Wektor<T> & Wektor<typename T>::operator=(const Wektor & w)
{
	// Przypisuj¹c jeden wektor do drugiego najpierw usuwamy star¹
	// zawartoœæ pierwszego z nich. Nastêpnie alokujemy tyle pamiêci, ile
	// jest potrzebnej do zapisania danych z drugiego wektora. Na koniec,
	// iteruj¹c po nim, przypisujemy wszystkie wartoœci elementów.

	delete[] values;
	this->w = new T[w.size];
	this->size = w->size;

	for (int i = 0; i < size; ++i)
		this->values[i] = w->values[i];

	return *this;
}

//_______________________________________________________________________

// Operator[] indeksuj¹cy elementy wektora
template <typename T>
T & Wektor<T>::operator[](int idx) const
{
	// Je¿eli indeks jest poprawny, to zwracamy wartoœæ tego elementu.

	if (idx >= 0 && idx < size)
		return values[idx];
}

//_______________________________________________________________________

// Operator << do wypisywania zawartoœci wektora
template <typename T>
std::ostream & operator<< (std::ostream & str, const Wektor<T> & w)
{
	for (int i = 0; i < w.size; ++i)
		str << i + 1 << ". " << w.values[i] << std::endl;
	str << std::endl;

	return str;
}

//_______________________________________________________________________
#endif