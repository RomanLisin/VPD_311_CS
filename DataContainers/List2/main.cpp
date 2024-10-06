#include<iostream>
using std::cin;
using std::cout;
using std::endl;
//#define BASE_CHECK
//#define iterators_check

#define tab "\t"
#define delimiter "\n----------------------------\n"

template <class T>
class List

{
	//template <class T>
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:

		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}

		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}

		friend class List;

	} *Head, * Tail;	//Объявляем два указателя на объекты класса 'Element' непосредственно после описания класса;
	//Element<T>* Head;
	//Element<T>* Tail;
	size_t size;	//Количество элементов списка

	//template <class T>
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp) :Temp(Temp) {}
		 ~ConstBaseIterator() {}
		 bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		T operator*()const
		{
			return this->Temp->Data;
		}
	};

public:

	//template <class T>
	class ConstIterator :public ConstBaseIterator	
	{
	public:
		//using ConstBaseIterator<T>::ConstBaseIterator; //наследуем конструктор базового класса, если включить, то можно обойтись без явной реализации конструктора
		ConstIterator(Element* Temp):ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "ITConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstIterator()
		{
#ifdef DEBUG
			cout << "ITDestructor:\t" << this << endl;
#endif // DEBUG
		}
		ConstIterator& operator++()        // Prefix increment	
		{
			this->Temp = this->Temp->pNext;
			return *this;
		}

		ConstIterator operator++(int)         // Postfix increment
		{
			ConstIterator old = *this;
			this->Temp = this->Temp->pNext;
			return old;
		}
		ConstIterator operator--() 
		{
			this->Temp = this->Temp->pPrev;
			return *this;;
		}
		ConstIterator operator--(int) 
		{
			ConstIterator old = *this;
			this->Temp = this->Temp->pPrev;
			return old;
		}
	};

	//template <class T>
	class ConstReverseIterator:public ConstBaseIterator
	{
	public:
		//using ConstBaseIterator<T>::ConstBaseIterator;    //                                           наследуем конструктор базового класса
		ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RITConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstReverseIterator()
		{
#ifdef DEBUG
			cout << "RITDestructor:\t" << this << endl;
#endif // DEBUG
		}

		ConstReverseIterator& operator++()
		{
			this->Temp = this->Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			this->Temp = this->Temp->pPrev;
			return old;
		}
		ConstReverseIterator operator--()
		{
			this->Temp = this->Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			this->Temp = this->Temp->pNext;
			return old;
		}
	};

	//template <class T>
	class Iterator : public ConstIterator
	{
	public:

		Iterator(Element* Temp) :ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*()
		{
			return this->Temp->Data;
		}
	};

	//template <class T>
	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) :ConstReverseIterator(Temp) {}
		~ReverseIterator() {}

		T& operator*()
		{
			return this->Temp->Data;
		}
	};


	//template <class T>
	ConstIterator begin() const
	{
		return Head;
	}
	//template <class T>
	 ConstIterator end() const
	{
		return nullptr;
	}
	//template <class T>
	Iterator begin() 
	{
		return Head;
	}
	//template <class T>
	Iterator end() 
	{
		return nullptr;
	}
	//template <class T>
	ConstReverseIterator rbegin() const
	{
		return Tail;
	}
	//template <class T>
	ConstReverseIterator rend() const
	{
		return nullptr;
	}
	//template <class T>
	ReverseIterator rbegin()
	{
		return Tail;
	}
	//template <class T>
	ReverseIterator rend()
	{
		return nullptr;
	}

	List()
	{
		//Конструктор по умолчанию создает пустой список
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstrutor:\t" << this << endl;
	}
	//template <class T>
	List(const std::initializer_list<T>& il) :List()
	{
		// begin()- возвращает итератор на начало контейнера.
		// end() - возвращает итератор на конец коентейнера.
		// Итератор - это указатель, при помощи которого можно получить доступ к элементам структуры
		cout << typeid(il.begin()).name() << endl;
		for (const T* it = il.begin(); it != il.end(); it++)
			push_back(*it);
	}
	//template <class T>
	List(const List& other):List() // Без делегирования может падать 
	{
		*this = other;
		cout << "LCopyConstructor:\t" << this << endl;
	}
	//template <class T>
	List(List&& other) :List()
	{
		*this = std::move(other); // явный вызов MoveAssignment

	}
	//template <class T>
	~List()
	{
		/*
		----------------------------
		while (Condition)
		{
			group - of - statements;
		}
		----------------------------
		while (Condition)expression;
		----------------------------
		*/
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestrutor:\t" << this << endl;
	}

	//       operators:
	//template <class T>
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();

		// Depp copy - Побитовое копироание:
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "LCopyAssignment:\t" << this << endl;
		return *this;
	}

	//template <class T>
	List& operator=(List&& other)
	{
		if (this == &other)return *this;
		while (Head) pop_front();

		// Shallow copy - Поверхостное копирование:
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;

		// обязательно нужно обнулить 'other'
		other.Head = other.Tail = nullptr;
		other.size = 0;

		cout << "LMoveAssignment:\t" << this << endl;
	}

	//					Adding elements:
	//template <class T>
	void push_front(T Data)
	{
		if (Head == nullptr && Tail == nullptr)
			Head = Tail = new Element(Data);
		else
		{
			////1) Создаем новый элемент:
			//Element* New = new Element(Data);

			////2) Присоединяем элемент к списку:
			//New->pNext = Head;

			////3) Присоединяем список к элементу:
			//Head->pPrev = New;

			////4) Смещаем Голову на новый элемент:
			//Head = New;
			Head = Head->pPrev = new Element(Data, Head);
		}
		size++;
	}
	//template <class T>
	void push_back(T Data)
	{
		if (Head == nullptr && Tail == nullptr) return push_front(Data);
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	//template <class T>
	void insert(T Data, int Index)
	{
		if (Index == 0)return push_front(Data);
			if (Index == size-1)return push_back(Data);
			if (Index >= size) throw std::exception("Insert: Out of range ecxeption");
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++) Temp = Temp->pNext;

		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev;
		}
		Temp->pNext->pPrev = Temp->pPrev->pNext = new Element(Data, Temp->pNext, Temp->pPrev);
		size++;
	}
	//             Removing elements:

	//template <class T>
	void pop_front()
	{
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size=0;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}

	//template <class T>
	void pop_back()
	{
		if (Head == Tail) return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	//						Methods:
	//template <class T>
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Tail:\t" << Tail << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	//template <class T>
	void reverse_print()const
	{
		cout << "Tail:\t" << Tail << endl;
		for(Element* Temp = Tail; Temp; Temp=Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Head:\t" << Head << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
};

template <class T>
List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> buffer;
	for (class List<T>::ConstIterator it = left.begin(); it != left.end(); ++it)buffer.push_back(*it); // без 'class' компилятор может интерпретировать List<T>
	for (class List<T>::ConstIterator it = right.begin(); it != right.end(); ++it) // ::ConstIterator как статический член данных или статическую функцию, а не как тип
	{
		buffer.push_back(*it);
		//*it *= 10;
	}
	return buffer;
}

//#define BASE_CHECK
//#define ITERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	T n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		// list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
	/*for (int i = 0; i < n*2; i++)list.pop_back();
	list.print();
	list.reverse_print();*/

	int index;
	T value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	try
	{
		list.insert(value, index);
		list.print();
		list.reverse_print();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
#endif // BASE_CHECK

#ifdef ITERATORS_CHECK
	List list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list)
	{
		cout << i<< tab;
	}
	cout << endl;

	for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	for (List::ReverseIterator it = list.rbegin();it != list.rend();++it}
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK

		List<int> list1 = { 3, 5, 8, 13, 21 };
		List<int> list2 = { 34, 55, 89 };
		List<int> list3 = list1+list2;
		for(int i:list1) cout << i << tab; cout << endl;
		for(int i:list2) cout << i << tab; cout << endl;
		for(int i:list3) cout << i << tab; cout << endl;

		for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it)
		{
			*it *= 10;
		}
		for(int i:list1) cout << i << tab; cout << endl;
}
