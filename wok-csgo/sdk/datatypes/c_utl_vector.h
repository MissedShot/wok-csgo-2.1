#pragma once

template <typename T, typename I = int>
class c_utl_memory {
public:
	__forceinline static int calc_new_allocation_count(int allocation_count, int grow_size, int new_size, int bytes_item) {
		if (grow_size) {
			allocation_count = ((1 + ((new_size - 1) / grow_size)) * grow_size);
		}
		else {
			if (!allocation_count) {
				allocation_count = (31 + bytes_item) / bytes_item;
			}

			while (allocation_count < new_size) {
				allocation_count *= 2;
			}
		}

		return allocation_count;
	}

	__forceinline T& operator[](I i) { return m_memory[i]; }

	__forceinline const T& operator[](I i) const { return m_memory[i]; }

	__forceinline T* get() { return m_memory; }

	__forceinline int get_alloc_count() const { return m_alloc_count; }

	__forceinline void purge() {
		if (m_grow_size < 0)
			return;

		if (m_memory) {
			interfaces::m_mem_alloc->free(m_memory);

			m_memory = 0;
		}

		m_alloc_count = 0;
	}

	__forceinline void grow(int number) {
		if (m_grow_size < 0)
			return;

		const auto alloc_requested = m_alloc_count + number;

		auto new_alloc_count = calc_new_alloc_count(m_alloc_count, m_grow_size, alloc_requested, sizeof(T));

		if (static_cast<int>(static_cast<I>(new_alloc_count)) < alloc_requested) {
			if (static_cast<int>(static_cast<I>(new_alloc_count)) == 0
				&& static_cast<int>(static_cast<I>(new_alloc_count - 1)) >= alloc_requested) {
				new_alloc_count--;
			}
			else {
				if (static_cast<int>(static_cast<I>(alloc_requested)) != alloc_requested)
					return;

				while (static_cast<int>(static_cast<I>(new_alloc_count)) < alloc_requested) {
					new_alloc_count = (new_alloc_count + alloc_requested) / 2;
				}
			}
		}

		m_alloc_count = new_alloc_count;

		m_memory = reinterpret_cast<T*>(
			m_memory
			? interfaces::m_mem_alloc->realloc(m_memory, m_alloc_count * sizeof(T))
			: interfaces::m_mem_alloc->alloc(m_alloc_count * sizeof(T))
			);
	}
protected:
	T* m_memory;

	int m_alloc_count;
	int m_grow_size;
};

template <typename T>
void destruct(T *memory) { memory->~T(); }

template <class T>
T* construct(T* memory) { return ::new(memory) T; }

template <class T>
T* copy_construct(T* memory, T const& src) { return ::new(memory) T(src); }

template <typename T, typename M = c_utl_memory<T>>
class c_utl_vector {
public:
	__forceinline T& operator[](int i) { return m_memory[i]; }

	__forceinline const T& operator[](int i) const { return m_memory[i]; }

	__forceinline T& at(int i) { return m_memory[i]; }

	__forceinline const T& at(int i) const { return m_memory[i]; }

	__forceinline int size() const { return m_size; }

	__forceinline void clear() {
		for (auto i = m_size; --i >= 0;) {
			destruct(&at(i));
		}

		m_size = 0;
	}

	__forceinline void purge() {
		clear();

		m_memory.purge();
	}

	__forceinline void shift_elements_right(int index, int number = 1) {
		if (number <= 0)
			return;

		const auto num_to_move = m_size - index - number;
		if (num_to_move <= 0)
			return;

		std::memmove(&at(index + number), &at(index), num_to_move * sizeof(T));
	}

	__forceinline void shift_elements_left(int index, int number = 1) {
		if (number <= 0)
			return;

		const auto num_to_move = m_size - index - number;
		if (num_to_move <= 0)
			return;

		std::memmove(&at(index), &at(index + number), num_to_move * sizeof(T));
	}

	__forceinline void grow_vector(int number = 1) {
		if (m_size + number > m_memory.get_alloc_count()) {
			m_memory.grow(m_size + number - m_memory.get_alloc_count());
		}

		m_size += number;
	}

	__forceinline int insert_before(int index) {
		grow_vector();

		shift_elements_right(index);

		construct(&at(index));

		return index;
	}

	__forceinline int add_to_head() { return insert_before(0); }

	__forceinline int add_to_tail() { return insert_before(m_size); }

	__forceinline int insert_before(int index, const T& value) {
		grow_vector();

		shift_elements_right(index);

		copy_construct(&at(index), value);

		return index;
	}

	__forceinline int insert_multiple_before(int index, int number) {
		grow_vector(number);

		shift_elements_right(index, number);

		for (auto i = 0; i < number; i++) {
			construct(&at(index + i));
		}

		return index;
	}

	__forceinline int add_to_tail(const T& value) { return insert_before(m_size, value); }

	__forceinline int add_multiple_to_tail(const T& value) { return insert_multiple_before(m_size, value); }

	__forceinline void ensure_count(int number) {
		if (m_size >= number)
			return;

		add_multiple_to_tail(number - m_size);
	}

	__forceinline int find(const T& value) const {
		for (auto i = 0; i < m_size; i++) {
			if (at(i) != value)
				continue;

			return i;
		}

		return -1;
	}

	__forceinline void remove(int index) {
		destruct(&at(index));

		shift_elements_left(index);

		m_size--;
	}

	__forceinline bool remove(const T& value) {
		const auto element = find(value);
		if (element == -1)
			return false;

		remove(element);

		return true;
	}

	__forceinline T* begin() { return m_memory.get(); }

	__forceinline const T* begin() const { return m_memory.get(); }

	__forceinline T* end() { return m_memory.get() + m_size; }

	__forceinline const T* end() const { return m_memory.get() + m_size; }
protected:
	M m_memory;

	int m_size;
	T* m_elements;
};