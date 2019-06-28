#pragma once

template <typename T>
class TemplateSingleton
{
private:
	static T* m_pInstance;
protected:
	TemplateSingleton();
	~TemplateSingleton();

public:
	static T* GetInstance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new T;
		return m_pInstance;
	}

	static void DestoryInstace()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
};

template <typename T> T* TemplateSingleton<T>::m_pInstance = nullptr;


template<typename T>
TemplateSingleton<T>::TemplateSingleton()
{

}


template<typename T>
TemplateSingleton<T>::~TemplateSingleton()
{

}


//============================================================================


class Manager : public TemplateSingleton<Manager>
{
private:
	bool m_bExitCommand = false;
	string m_strCurFloor;

public:
	void Update();

	bool getExitCommend()const ;
	void setExitCommend(const bool &Event);
	string getCurFloor();
	void setCurFloor(const string & _floor);


	Manager();
	~Manager();

};
