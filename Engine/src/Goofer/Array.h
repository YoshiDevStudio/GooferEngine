#pragma once
#include <vector>
#include <iostream>
#include "Core.h"
namespace Goofer
{
	template <typename T> class Array
	{
	public:
		Array() = default;
		~Array()
		{
			m_arr.clear();
		}

		T& operator[](int index)
		{
			int newIndex = GetIndexSign(index);
			return m_arr[newIndex];
		}

		//Adds item to End of Array
		void PushBack(T& obj)
		{
			if (readonly)
				return;

			m_arr.push_back(obj);
		}
		//Adds item to Front of Array
		void PushFront(T& obj)
		{
			if (readonly)
				return;

			m_arr.insert(m_arr.begin(), 1, obj);
		}
		//Adds item to End of Array
		void PushBack(const T& obj)
		{
			if (readonly)
				return;

			T newObj = obj;
			m_arr.push_back(newObj);
		}
		//Adds item to Front of Array
		void PushFront(const T& obj)
		{
			if (readonly)
				return;

			T newObj = obj;
			m_arr.insert(m_arr.begin(), 1, newObj);
		}
		//Removes item at End of Array
		void PopBack()
		{
			if (readonly)
				return;

			m_arr.pop_back();
		}
		//Removes item at Front of Array
		void PopFront()
		{
			if (readonly)
				return;

			m_arr.erase(m_arr.begin());
		}
		//Removes First item that matches obj
		void Remove(T& obj)
		{
			if (readonly)
				return;

			for (int i = 0; i < Size(); i++)
			{
				if (obj == m_arr[i])
				{
					m_arr.erase(m_arr.begin() + i);
					return;
				}
			}
		}
		//Removes First item that matches obj
		void Remove(const T& obj)
		{
			if (readonly)
				return;

			T newObj = obj;
			for (int i = 0; i < Size(); i++)
			{
				if (newObj == m_arr[i])
				{
					m_arr.erase(m_arr.begin() + i);
					return;
				}
			}
		}
		//Removes item at index given
		void RemoveAt(int index)
		{
			if (readonly)
				return;

			int newIndex = GetIndexSign(index);
			m_arr.erase(m_arr.begin() + newIndex);
		}
		//Removes all items
		void Clear()
		{
			if (readonly)
				return;

			m_arr.clear();
		}
		//Copys other Array of same type
		void Copy(Array<T>& arrayToCopy)
		{
			if (readonly)
				return;

			m_arr = arrayToCopy.GetArray();
		}

		//Reverses Array
		void Reverse()
		{
			if (readonly)
				return;

			std::vector<T> newArr;
			for (int i = 0; i < Size(); i++)
			{
				//-i subtracted by 1 so GetIndexSign doesnt return 0 the first loop
				newArr.push_back(m_arr[GetIndexSign(-i - 1)]);
			}

			m_arr = newArr;
		}
		//Checks if obj is in Array returns true if obj is found
		bool Has(T& obj)
		{
			for (int i = 0; i < Size(); i++)
			{
				if (obj == m_arr[i])
				{
					return true;
				}
			}
			return false;
		}
		//Checks if obj is in Array returns true if obj is found
		bool Has(const T& obj)
		{
			T newObj = obj;
			for (int i = 0; i < Size(); i++)
			{
				if (newObj == m_arr[i])
				{
					return true;
				}
			}
			return false;
		}
		//Checks if Array is empty
		bool IsEmpty()
		{
			return Size() == 0;
		}

		//Gets Amount of items in Array
		int Size()
		{
			if (m_arr.empty())
				return 0;
			return m_arr.size();
		}
		//Looks through array for item matching obj and returns its index
		int Find(T& obj, int from = 0)
		{
			if (from >= Size())
			{
				return NULL;
			}
			if (from < 0)
			{
				for (int i = from; i > Size(); i--)
				{
					if (obj == m_arr[i])
					{
						return i;
					}
				}
			}
			else
			{
				for (int i = from; i < Size(); i++)
				{
					if (obj == m_arr[i])
					{
						return i;
					}
				}
			}
			return NULL;
		}
		//Looks through array for item matching obj and returns its index
		int Find(const T& obj, int from = 0)
		{
			T newObj = obj;
			if (from >= Size())
			{
				return NULL;
			}
			if (from < 0)
			{
				for (int i = from; i > Size(); i--)
				{
					if (newObj == m_arr[i])
					{
						return i;
					}
				}
			}
			else
			{
				for (int i = from; i < Size(); i++)
				{
					if (newObj == m_arr[i])
					{
						return i;
					}
				}
			}
			return NULL;
		}

		//Returns the number of times an item is in the Array
		int Count(T& obj)
		{
			int itemCount = 0;
			for (int i = 0; i < Size(); i++)
			{
				if (m_arr[i] == obj)
					itemCount++;
			}
			return itemCount;
		}
		//Returns the number of times an item is in the Array
		int Count(const T& obj)
		{
			T newObj = obj;
			int itemCount = 0;
			for (int i = 0; i < Size(); i++)
			{
				if (m_arr[i] == newObj)
					itemCount++;
			}
			return itemCount;
		}

		//Inserts item into array from index
		void Insert(int index, T& obj)
		{
			if (readonly)
				return;

			int newIndex = GetIndexSign(index);
			m_arr.insert(m_arr.begin() + newIndex, obj);
		}
		//Inserts item into array from index
		void Insert(int index, const T& obj)
		{
			if (readonly)
				return;

			T newObj = obj;
			int newIndex = GetIndexSign(index);
			m_arr.insert(m_arr.begin() + newIndex, newObj);
		}

		//returns item at front of Array
		T Front()
		{
			if (m_arr[0] != NULL) return m_arr[0];
			else return NULL;
		}
		//returns item at back of Array
		T Back()
		{
			if (m_arr[Size() - 1] != NULL) return m_arr[Size() - 1];
			else return NULL;
		}

		//Directly access Array
		std::vector<T> GetArray()
		{
			return m_arr;
		}

		bool readonly = false;
	private:

		//if index is negative start counting from back of array
		int GetIndexSign(int index)
		{
			//index is negative
			if (index < 0)
			{
				if (-index > Size())
				{
					LOG_ERROR("Index was out of Array bounds");
					return Size();
				}
				//Add since index is negative
				return (Size() + index);
			}
			else
			{
				if (index > Size())
				{
					LOG_ERROR("Index was out of Array bounds");
					return Size();
				}
				return index;
			}
		}

		std::vector<T> m_arr;
	};
}

