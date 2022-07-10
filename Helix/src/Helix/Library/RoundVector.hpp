#pragma once

#include "stdafx.hpp"

namespace hlx
{
	template<typename T>
	class RoundVector
	{
	public:
		using iterator = T*;

		RoundVector() : m_write{}, m_size{}, m_totalSize{} {}
		explicit RoundVector(unsigned int count) : RoundVector{}
		{
			resize(count);
		}
		~RoundVector() = default;

		T& at(unsigned int index) { return m_elements.at(index); }
		size_t size() const { return m_size; }
		void resize(unsigned int count)
		{
			m_elements.resize(count);

			m_totalSize = count;
			if (m_size > m_totalSize) m_size = m_totalSize;
		}

		void push_back(const T& element)
		{
			m_elements.at(m_write) = element;
			
			m_size = m_size + 1 > m_totalSize ? m_totalSize : m_size + 1;
			m_write = m_write + 1 > m_size - 1 ? 0 : m_write + 1;
		}

		void emplace_back(T&& element)
		{
			m_elements.at(m_write) = element;

			m_size = m_size + 1 > m_totalSize ? m_totalSize : m_size + 1;
			m_write = m_write + 1 > m_size ? 0 : m_write + 1;
		}

		iterator begin() { return m_elements.data(); }
		iterator end() { return m_elements.data() + m_size; }

	private:
		std::vector<T> m_elements;

		unsigned int m_write;

		unsigned int m_size;
		unsigned int m_totalSize;
	};
}