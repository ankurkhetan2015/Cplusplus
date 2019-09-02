#ifndef MY_MAP_H
#define MY_MAP_H

#include "key_value.h"
#include <iterator> 
#include <vector>
#include <iterator>
using namespace std;
template <typename T, typename E>
struct my_map
{
    class map_iter : public iterator<input_iterator_tag, key_value<T,E>>
    {
    public:
        int index;
        vector<key_value<T,E>>& vec;
        map_iter(int start, vector<key_value<T,E>>& vec_) :index(start), vec(vec_){}
        map_iter(const map_iter& iter) : index(iter.index), vec(iter.vec){}
        map_iter& operator++()
        {
			index++;
            return *this;
        }

        map_iter operator++(int) {map_iter tmp(*this); operator++(); return tmp;}
        bool operator==(const map_iter& rhs) const {return index == rhs.index;}
        bool operator!=(const map_iter& rhs) const {return index != rhs.index;}

        key_value<T,E>& operator*() 
        {
			return vec[index];
        }
    };

    vector<key_value<T,E>> container;

    my_map() : container() { }
    my_map(const my_map<T, E>& other);
    my_map<T, E>& operator=( const my_map<T, E>& other );

    E& operator[](T search_key);
    E* search_for_key(T search_key);
    void insert_new_kvp(T search_key);
    map_iter begin()
    {
        return map_iter(0, container);
    }

    map_iter end()
    {
        return map_iter(container.size(), container);
    }
};

template <typename T, typename E>
ostream& operator<<(ostream& out, my_map<T, E> map)
{
	for (my_map<T, E>::map_iter it = map.begin(); it != map.end(); it++)
		out << (*it) << endl;
	
    return out;
}

template <typename T, typename E>
my_map<T,E>::my_map(const my_map<T, E>& other)
    :   container(other.container)   
{}

template <typename T, typename E>
my_map<T, E>& my_map<T,E>::operator=( const my_map<T, E>& other )
{
    container(other.container);
}

template <typename T, typename E>
E& my_map<T, E>::operator[](T search_key)
{
	// Case when it is empty
	if (container.empty())
	{
		insert_new_kvp(search_key);
		return container.front().value;
	}

	// Quick search at front
	if (search_key < container.front().key)
	{
		insert_new_kvp(search_key);
		return container.front().value;
	}

	// Quick search at back
	else if (search_key > container.back().key)
	{
		insert_new_kvp(search_key);
		return container.back().value;
	}

	// Insert the key, the insert method will handle duplicate
	insert_new_kvp(search_key);

	// Search the index where search key is located
	unsigned l = 0;
	unsigned r = container.size() - 1;

	while (l <= r)
	{
		unsigned m = l + (r - l) / 2;

		if (search_key < container[m].key)
			r = m - 1; // Search left half
		else if (search_key > container[m].key)
			l = m + 1; // Search right half
		else
			return container[m].value; // Found it!
	}

	// Code should not reach here
	throw std::exception();
}

template <typename T, typename E>
E* my_map<T,E>::search_for_key(T search_key)
{
	// Quick search for empty
	if (container.empty())
		return NULL;

	// Quick search at front
	if (search_key < container.front().key)
		return NULL;

	// Quick search at back
	if (search_key > container.back().key)
		return NULL;

	unsigned l = 0;
	unsigned r = container.size() - 1;

	while (l <= r)
	{
		unsigned m = l + (r - l) / 2;

		if (search_key < container[m].key)
			r = m - 1; // Search left half
		else if (search_key > container[m].key)
			l = m + 1; // Search right half
		else
			return &container[m].value; // Found it!
	}

    return NULL;
}

template <typename T, typename E>
void my_map<T,E>::insert_new_kvp(T search_key)
{
	// Quick insert for empty
	if (container.empty())
	{
		container.push_back(key_value<T, E>(search_key));
		return;
	}

	// Quick insert at back
	if (search_key > container.back().key)
	{
		container.push_back(key_value<T, E>(search_key));
		return;
	}

	// Insert front or in-between
	int insertIndex = 0;

	for (unsigned i = 0; i < container.size(); i++)
	{
		if (search_key == container[i].key)
			return; // Stop on duplicate
		
		if (search_key < container[i].key)
		{
			insertIndex = i;
			break;
		}
	}

	// Do insert
	container.insert(container.begin() + insertIndex, key_value<T, E>(search_key));
}

#endif