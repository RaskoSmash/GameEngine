#pragma once
#include <vector>
#include <queue>

//TODO: put definitions in a .cpp

template<typename T>
struct Handle
{
	int index;
	Handle(int i = -1) : index(i), dataref(&GCData<T>::getData()){}

#pragma region -> operator, * operator, int() operator
	T *operator->() 
	{return &GCData<T>::at(index);}

	T *operator->() const
	{return &GCData<T>::at(index);}

	T &operator*()
	{return GCData<T>::at(index);}

	T operator*() const
	{return GCData<T>::at(index);}

	T *operator&()
	{return &GCData<T>::at(index);}

	operator int()
	{return index;}

	operator int() const
	{return index;}
#pragma endregion

private:
	std::vector<T> *dataref;
};

//Global Homogeneous Contiguous Data
template<typename T>
class GCData
{
	int index;		//index of object in global data array
	bool isVacant;	//is this index free or not

	static std::queue<int> &getQueue() 
	{ static std::queue<int> q; return q; }
public:
	//global data
	static std::vector<T> &getData()
	{ static std::vector<T> d; return d; }

	//direct accessor
	static T &at(int i)
	{ return getData()[i]; }

	//frees an object in the global array
	static void free(int i)
	{
		if (i > -1 && !at(i).isVacant) //make sure it already isnt vacant
		{
			at(i).onFree();		//allows custom child logic upon deletion
			getQueue().push(i);
			at(i).isVacant = true;
			at(i).index = -1;
		}
	}

	//return a handle to our newly constructed object
	static Handle<T> make()
	{
		int i = -1;		//default invalid index

		//recycle data if free space
		if (getQueue().size() > 0)
		{
			i = getQueue().front();
			getQueue().pop();
			at(i) = T();
		}
		else //otherwise allocate new data in the array
		{
			i = getData().size();
			getData().emplace_back();
		}

		at(i).index = i;
		at(i).isVacant = false;
		return Handle<T>{ i };
	}

	int getIndex()
	{ return index; }

	bool isValid()
	{ return !isVacant; }

	virtual void onFree() {}
};