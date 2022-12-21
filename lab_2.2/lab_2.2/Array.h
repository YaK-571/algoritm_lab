#pragma once
#include <iostream>

//������� �� ���������
constexpr static int defautArraycapacity_i = 8;

template<typename T>
class Array final
{
private:
	T* pi;
	int size;
	int capacity;

public:
	//��������� ������
	Array();
	Array(int capacity);

    ~Array();

	//����������� �����������
	Array(const Array& rhs);
	//move semantics, ������������ �����������
	Array(Array&& rhs);
	
	//��������������� ����������
	Array& operator = (const Array& rhs); 
	Array& operator = (Array&& rhs); 

	//������� � ������
	int insert(const T& value);
	int insert(int index, const T& value);
	
	//�������� ��������
	void remove(int index);

	//��������� � �������� �������
	const T& operator[](int index) const;
	T& operator[](int index);

	//����������� ������� �������
	size_t size_i() const;
	
	int capacity_i() const;

	class Iterator final {
	protected:

		T* cur; // ������-��������� �� ������� � �������
		Array& arr; // ��� ������
		bool direction; // ����������� �� �������� �� ����� � �������. �����-������� ��� ������-������

	public:
		Iterator(Array& const arr, bool direction) : arr(arr), direction(direction) {

			//�������� � ����� ������� ����� ������������ ����� �������
			//� ����� ������ ��������� ������� �� ������ �������, � ������ �� ���������
			if (direction == true) {
				cur = arr.pi;
			}
			else
			{
				cur = arr.pi + arr.size - 1;
			}

		}

		//����������� ���������� ��������
		const T& get() const {
			return *cur;
		}
		// ���������� �������� � �������� �����
		void set(const T& value) {

			*cur = value;
		}

		//������� �� ��������� ������� �������
		void next() {
			if (direction == true) {
				cur++;
			}
			else
			{
				cur--;
			}

		}

		//�������� ���� �� ��������� �������
		bool hasnext() const {
			if (direction == true)
				return cur >= arr.pi;
			else
				return cur < arr.pi + arr.size;
		}

	};

	//�� �� ����� ��� � ������� ���������, ������ ��� ������
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


//����������� ��� ��������� ������
template<typename T>
Array<T>::Array() : capacity(defautArraycapacity_i), size(0)
{
	pi = (T*)malloc(capacity * sizeof(T));
}
//����������� ��� ��������� ������ ��� �������� ����� ���������
template<typename T>
Array<T>::Array(int capacity)
{
	pi = (T*)malloc(capacity * sizeof(T));
}

//������� � ����� �������
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

//������� � ��������� ����� ������� �� ������� ��������� ������
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

//�������� �������� �� ������� ������ ��������� �����
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

//��������� � ���������� �������� �������
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

//����������� ������� �������
template<typename T>
size_t Array<T>::size_i() const {

	return size;
}

template<typename T>
int Array<T>::capacity_i() const {

	return capacity;
}


//����������� �����������
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



//��������������� ��������� ��� �����������
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


//��������������� ��������� ��� move
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
