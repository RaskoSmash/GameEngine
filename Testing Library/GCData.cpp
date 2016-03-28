#pragma once
#include "GCData.h"



/*
template<typename T>
class GCData
{
	int index;		//index of object in global data array
	bool isVacant;	//is this index free or not

	static std::queue<int> &getQueue()
	{
		static std::queue<int> q; return q;
	}
public:
	//global data
	static std::vector<T> &getData()
	{
		static std::vector<T> d; return d;
	}

	//direct accessor
	static T &at(int i)
	{
		return getData()[i];
	}

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
	{
		return index;
	}

	bool isValid()
	{
		return !isVacant;
	}

	virtual void onFree() {}
};*/