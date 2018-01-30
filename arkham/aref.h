#pragma once

// Standart reserve procedure
void* rmreserve(void* ptr, unsigned size, bool focre_to_size);

// Get total count of records.
inline int optimal(int need_count, int mc = 256 * 256) {
	int m = 64;
	while(m < mc) {
		if(need_count < m)
			return m;
		m = m << 1;
	}
	return m;
}

// Simplest array - pointer and count. Used only for POD types.
// Not POD types NEED sublass clear(), reserve(), reserve(n).
template<class T>
struct aref {
	T*			data;
	unsigned	count;

	inline T& operator[](int index) { return data[index]; }
	operator bool() const { return count != 0; }

	constexpr aref() = default;
	template<unsigned N> constexpr aref(T(&data)[N]) : data(data), count(N) {}

	// Add new item
	T* add() {
		return &data[count++];
	}

	// Add new item to collection
	void add(const T& e) {
		data[count++] = e;
	}

	T* begin() {
		return data;
	}

	const T* begin() const {
		return data;
	}

	void initialize() {
		data = 0; count = 0;
	}

	void clear() {
		count = 0;
	}

	T* end() {
		return data + count;
	}

	const T* end() const {
		return data + count;
	}

	int indexof(const T* t) const {
		if(t<data || t>data + count)
			return -1;
		return t - data;
	}

	int indexof(const T t) const {
		for(unsigned i = 0; i < count; i++)
			if(data[i] == t)
				return i;
		return -1;
	}

	bool is(const T value) const {
		return indexof(value) != -1;
	}

	// Allocate memory for count records
	void reserve(int count) {
		data = (T*)rmreserve(data, sizeof(T)*optimal(count, 256 * 256 * 256));
	}

	// Allocate memory for one record
	void reserve() {
		reserve(count + 1);
	}

	// Remove elements_count from array starting from index
	void remove(int index, int elements_count = 1) {
		if(index < 0 || index >= count)
			return;
		count -= elements_count;
		if(index >= count)
			return;
		memmove(data + index, data + index + elements_count, sizeof(data[0])*(count - index));
	}

};
#define AREF(t) {t, sizeof(t)/sizeof(t[0])}