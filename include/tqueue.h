#include <iostream>
#include <deque>

//template <class T>
//class Queue {
//	std::deque<T> data;
//public:
//	Queue() {};
//
//	void push(const T& value) {
//		data.push_back(value);
//	}
//
//	void pop() {
//		if (!empty()) {
//			data.pop_back();
//		}
//		else {
//			throw std::out_of_range("Stack is empty");
//		}
//	}
//
//	T front() const() {
//		if (!empty()) {
//			return data.front();
//		}
//		else {
//			throw std::out_of_range("Stack is empty");
//		}
//	}
//
//	T back() const() {
//		if (!empty()) {
//			return data.back();
//		}
//		else {
//			throw std::out_of_range("Stack is empty");
//		}
//	}
//	
//	bool empty() const {
//		return data.empty();
//	}
//
//	size_t size() const {
//		return data.size();
//	}
//};

template <class T>
class Queue {
	T* data;
	size_t capacity;
	int head;
	int tail;

	void repack() {
		T* temp_data = new T[capacity];
		for (int i = 0; i < (tail - head + 1); ++i) {
			temp_data[i] = data[i];
		}
		delete[] data;
		capacity = 2 * capacity;
		data = new T[capacity];
		for (int i = 0; i < (tail - head + 1); ++i) {
			data[i] = temp_data[i];
		}
		delete[] temp_data;
	}

	void move() {
		for (int i = head; i < tail; i++) {
			data[i - head] = data[i];
		}
		tail = tail - head;
		head = 0;
	}

public:
	Queue() : capacity(4), head(0), tail(-1) { data = new T[capacity]; };

	~Queue() { delete[] data; }

	void push(const T& value) {
		if ((tail - head + 1) == capacity) repack();
		else if (tail == (capacity - 1)) move();
		tail++;
		data[tail] = value;
	}

	void pop() {
		if (!empty()) head++;
		else {
			throw std::out_of_range("Stack is empty");
		}
	}

	T front() const {
		if (!empty()) return data[head];
		else {
			throw std::out_of_range("Stack is empty");
		}
	}

	T back() const {
		if (!empty()) return data[tail];
		else {
			throw std::out_of_range("Stack is empty");
		}
	}
	
	bool empty() const {
		return (tail < head);
	}

	size_t size() const {
		return (tail - head + 1);
	}
};

