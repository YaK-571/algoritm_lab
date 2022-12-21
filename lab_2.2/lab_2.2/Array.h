#pragma once
#include <iostream>

//ёмкость по умолчанию
constexpr static int defautArraycapacity_i = 8;

template<typename T>
class Array final
{
private:
	T* pi;
	int size;
	int capacity;

public:
	//выделение памяти
	Array();
	Array(int capacity);

    ~Array();

	//конструктор копирования
	Array(const Array& rhs);
	//move semantics, перемещающий конструктор
	Array(Array&& rhs);
	
	//Переопределение операторов
	Array& operator = (const Array& rhs); 
	Array& operator = (Array&& rhs); 

	//вставка в массив
	int insert(const T& value);
	int insert(int index, const T& value);
	
	//удаление элемента
	void remove(int index);

	//обращение к элементу массива
	const T& operator[](int index) const;
	T& operator[](int index);

	//определение размера массива
	size_t size_i() const;
	
	int capacity_i() const;

	class Iterator final {
	protected:

		T* cur; // индекс-указатель на элемент в массиве
		Array& arr; // сам массив
		bool direction; // направление по которому мы ходим в массиве. Слева-направо или справо-налево

	public:
		Iterator(Array& const arr, bool direction) : arr(arr), direction(direction) {

			//проверка в какую сторону будет производится обход массива
			//в одном случае указатель встанет на первый элемент, в другом на последний
			if (direction == true) {
				cur = arr.pi;
			}
			else
			{
				cur = arr.pi + arr.size - 1;
			}

		}

		//возвращение выбранного элемента
		const T& get() const {
			return *cur;
		}
		// перезапись элемента в заданном месте
		void set(const T& value) {

			*cur = value;
		}

		//переход на следующий элемент массива
		void next() {
			if (direction == true) {
				cur++;
			}
			else
			{
				cur--;
			}

		}

		//проверка есть ли следующий элемент
		bool hasnext() const {
			if (direction == true)
				return cur >= arr.pi;
			else
				return cur < arr.pi + arr.size;
		}

	};

	//то же самое что и прошлый итерратор, только без записи
	class ConstIterator final {
	protected:

		T* cur;
		Array& arr;
		bool direction;

	public:
		ConstIterator(Array& const arr, bool direction) : arr(arr), direction(direction) {

			if (direction == true) {
				cur = arr.pi;
			}
			else
			{
				cur = arr.pi + arr.size - 1;
			}
		}

		const T& get() const {
			return *cur;
		}

		void next() {
			if (direction == true) {
				cur++;
			}
			else
			{
				cur--;
			}

		}

		bool hasnext() const {
			if (direction == true)
				return cur >= arr.pi;
			else
				return cur < arr.pi + arr.size;
		}

	};

	Iterator iterator() {
		return Iterator(*this, true);
	}

	ConstIterator constIterator() const {
		return ConstIterator(*this, true);
	}

	Iterator reverseiterator() {
		return Iterator(*this, false);

	}

	ConstIterator reverseconstIterator() const {

		return ConstIterator(*this, false);
	}

};


//конструктор для выделения памяти
template<typename T>
Array<T>::Array() : capacity(defautArraycapacity_i), size(0)
{
	pi = (T*)malloc(capacity * sizeof(T));
}
//конструктор для выделения памяти под заданное число элементов
template<typename T>
Array<T>::Array(int capacity)
{
	pi = (T*)malloc(capacity * sizeof(T));
}

//вставка в конец массива
template <typename T>
int Array<T>::insert(const T& value) {
	if (size >= capacity) {
		capacity *= 2;
		T* p = (T*)malloc(capacity * sizeof(T));

		for (int i = 0; i < size; i++) {
			new (p + i) T(std::move(pi[i]));
		}

		for (int i = 0; i < size; i++) {
			pi[i].~T();
		}
		free(pi);
		pi = p;

	}
	new (pi + size) T(value);
	size += 1;
	return size - 1;

}

//вставка в указанное место массива со сдвигом элементов вправо
template <typename T>
int Array<T>::insert(int index, const T& value) {
	if (index > size || index < 0) {
		return -1;
	}

	if (size >= capacity) {
		capacity *= 2;
		T* p = (T*)malloc(capacity * sizeof(T));

		for (int i = 0; i < size; i++) {
			new (p + i) T(std::move(pi[i]));
		}

		for (int i = 0; i < size; i++) {
			pi[i].~T();
		}
		free(pi);
		pi = p;
	}

	for (int i = size; i > index; i--) {
		new (pi + i) T(std::move(pi[i - 1]));
		pi[i - 1].~T();
	}

	new (pi + index) T(value);

	size++;
	return index;

}

//удаление элемента со вдвигом других элементов влево
template<typename T>
void Array<T>::remove(int index) {

	if (index > size || index < 0) {
		return;
	}


	for (int i = index; i < size - 1; i++) {
		pi[index].~T();
		new (pi + i) T(std::move(pi[i + 1]));
	}
	size -= 1;


}

//обращение к указанному элементу массива
template<typename T>
const T& Array<T>::operator[](int index) const
{
	return pi[index];
}
template<typename T>
T& Array<T>:: operator[](int index)
{
	return pi[index];
}

//определение размера массива
template<typename T>
size_t Array<T>::size_i() const {

	return size;
}

template<typename T>
int Array<T>::capacity_i() const {

	return capacity;
}


//конструктор копирования
template<typename T>
Array<T>::Array(const Array& rhs)
{
	pi = (T*)malloc(capacity * sizeof(T));

	for (int i = 0; i < size; i++) {
		new (pi + i) T(rhs.pi[i]);
	}
	size = rhs.size;
	capacity = rhs.capacity;
}


//move
template<typename T>
Array<T>::Array(Array&& rhs)
{
	pi = rhs.pi;
	size = rhs.size;
	capacity = rhs.capacity;

	rhs.pi = nullptr;
	rhs.size = 0;
	rhs.capacity = 0;
}



//переопределение оператора для копирования
template<typename T>
Array<T>& Array<T>:: operator = (const Array& rhs)
{
	if (this != rhs) {
		Array<T> temp = rhs;

		free(pi);
		capacity = temp.capacity;
		size = temp.size;
		pi = (T*)malloc(sizeof(T) * capacity);
		for (int i = 0; i < capacity_i; i++) {
			new (pi + i) T(rhs.pi[i]);
		}
	}
	return *this;
}


//переопределение оператора для move
template<typename T>
Array<T>& Array<T>:: operator = (Array&& rhs)
{
	if (this != &rhs) {
		for (int i = 0; i < size; i++) {
			pi[i].~Array();
		}
		free(pi);

		pi = rhs.pi;
		size = rhs.size;
		capacity = rhs.capacity;

		rhs.pi = nullptr;
		rhs.size = 0;
		rhs.capacity = 0;
	}
	return *this;
}

template<typename T>
Array<T>::~Array()
{
	for (int i = 0; i < size; i++) {
		pi[i].~T();
	}

	free(pi);
}
