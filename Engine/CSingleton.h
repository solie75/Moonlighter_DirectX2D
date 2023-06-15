#pragma once

typedef void (*EXIT)(void);

template<typename T>
class CSingleton
{
private:
	static T* mInst;

public:
	static T* GetInst();
	static void Destroy();

public:
	CSingleton() { }
	virtual ~CSingleton() {}
};

template<typename T>
T* CSingleton<T>::mInst = nullptr;

template<typename T>
inline T* CSingleton<T>::GetInst()
{
	if (nullptr == mInst)
	{
		mInst = new T;
		atexit((EXIT)&CSingleton<T>::Destroy);
	}

	return mInst;
}

template<typename T>
inline void CSingleton<T>::Destroy()
{
	if (nullptr != mInst)
	{
		delete mInst;
		mInst = nullptr;
	}
}