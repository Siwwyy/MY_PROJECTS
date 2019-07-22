#pragma once
#ifndef _HANDLER_HPP
#define _HANDLER_HPP

#include <iostream>
#include <windows.h>
#include <string>
#include <thread>
#include <mutex>
#include <memory>

namespace MY_HANDLE
{
	using _STD cout;
	using _STD cin;
	using _STD cerr;

	#define NEW_LINE '\n'


	template<typename _Ty = void>
	class _HANDLER
	{
	private:
		/*
			PRIVATE VARIABLES
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		_STD thread handle_thread;
		_STD unique_lock<_STD mutex> unique_mu_locker;
		_STD mutex mu_locker;
		_STD once_flag flag;
		_Ty * pointer_to_handler;
		bool if_deleted;
		/////////////////////////////////////////////////////////////////////////////////////////////
	protected:
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			PROTECTED FUNCTIONS
		*/
		void Delete_Handle_Pointer();
		/////////////////////////////////////////////////////////////////////////////////////////////
	public:
		/*
			PUBLIC CONSTRUCTORS
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		_HANDLER();
		_HANDLER(const _Ty & pointer_to_handle);
		_HANDLER(const _HANDLER& Object) = delete;
		_HANDLER(_HANDLER&& Object) noexcept;
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			PUBLIC FUNCTIONS
		*/
		void Join_Asynchronously();
		void Join_Synchronously();
		void Lock_Mutex();
		void Unlock_Mutex();
		void Lock_Guard();
		void Unique_Lock();
		void Unique_Unlock();
		void Call_Once();
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			SETTERS
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		void Set_Pointer_To_Handler(const _Ty& new_pointer_to_handle);
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			GETTERS
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		constexpr _Ty* Get_Pointer_To_Handler() const;
		constexpr _Ty & Get_Reference_To_Handler() const;
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			OPERATORS
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		_HANDLER& operator=(const _HANDLER& Object) = delete;
		_HANDLER& operator=(_HANDLER&& Object);
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			DESTRUCTOR
		*/
		virtual ~_HANDLER();
		/////////////////////////////////////////////////////////////////////////////////////////////
	};

	template<typename _Ty>
	__forceinline void _HANDLER<_Ty>::Delete_Handle_Pointer()
	{
		if_deleted = true;
		delete this->pointer_to_handler;
	}

	template<typename _Ty>
	inline _HANDLER<_Ty>::_HANDLER():
		mu_locker(),
		flag(),
		unique_mu_locker(mu_locker,_STD defer_lock),
		handle_thread(),
		if_deleted(false),
		pointer_to_handler(new _Ty)
	{
		//NOTHING HERE
	}

	template<typename _Ty>
	inline _HANDLER<_Ty>::_HANDLER(const _Ty & pointer_to_handle) :
		pointer_to_handler(new _Ty(pointer_to_handle)),
		flag(),
		unique_mu_locker(mu_locker, _STD defer_lock),
		handle_thread(pointer_to_handle), 
		mu_locker(),
		if_deleted(false)
	{
		//NOTHING HERE
	}

	template<typename _Ty>
	inline _HANDLER<_Ty>::_HANDLER(_HANDLER&& Object) noexcept :
		handle_thread(std::move(Object.handle_thread)),
		unique_mu_locker(std::move(Object.unique_mu_locker)),	//transfering the ownership of mutex mu_locker
		pointer_to_handler(nullptr)
	{
		this->pointer_to_handler = new _Ty(Object.Get_Reference_To_Handler());
		Object.Delete_Handle_Pointer();
	}

	template<typename _Ty>
	__forceinline void _HANDLER<_Ty>::Join_Asynchronously()
	{
		if (handle_thread.joinable())
		{
			this->handle_thread.detach();
		}
	}

	template<typename _Ty>
	__forceinline void _HANDLER<_Ty>::Join_Synchronously()
	{
		if (handle_thread.joinable())
		{
			handle_thread.join();
		}
	}

	template<typename _Ty>
	__forceinline void _HANDLER<_Ty>::Lock_Mutex()
	{
		mu_locker.lock();
	}

	template<typename _Ty>
	__forceinline void _HANDLER<_Ty>::Unlock_Mutex()
	{
		mu_locker.unlock();
	}

	template<typename _Ty>
	__forceinline void _HANDLER<_Ty>::Lock_Guard()
	{
		_STD lock_guard<_STD mutex> locker(mu_locker);
	}

	template<typename _Ty>
	__forceinline void _HANDLER<_Ty>::Unique_Lock()
	{
		unique_mu_locker.lock();
	}

	template<typename _Ty>
	__forceinline void _HANDLER<_Ty>::Unique_Unlock()
	{
		unique_mu_locker.unlock();
	}

	template<typename _Ty>
	__forceinline void _HANDLER<_Ty>::Call_Once()
	{
		_STD call_once(flag, [&](){*pointer_to_handler;} );
	}

	template<typename _Ty>
	__forceinline void _HANDLER<_Ty>::Set_Pointer_To_Handler(const _Ty& new_pointer_to_handle)
	{
		delete pointer_to_handler;
		this->pointer_to_handler = new _Ty(new_pointer_to_handle);
	}

	template<typename _Ty>
	__forceinline constexpr _Ty* _HANDLER<_Ty>::Get_Pointer_To_Handler() const
	{
		return this->pointer_to_handler;
	}

	template<typename _Ty>
	__forceinline constexpr _Ty& _HANDLER<_Ty>::Get_Reference_To_Handler() const
	{
		return (*this->pointer_to_handler);
		//return _STD reference_wrapper<_Ty>(*this->pointer_to_handler);
	}

	template<typename _Ty>
	__forceinline _HANDLER<_Ty>& _HANDLER<_Ty>::operator=(_HANDLER&& Object)
	{
		if (this != _STD addressof(Object))
		{
			this->pointer_to_handler = new _Ty(Object.Get_Reference_To_Handler());
			this->handle_thread = std::move(Object.handle_thread);
			this->unique_mu_lock = std::move(Object.unique_mu_lock); //transfering the ownership of mutex mu_locker
			Object.Delete_Handle_Pointer();
		}
		return *this;
	}

	template<typename _Ty>
	inline _HANDLER<_Ty>::~_HANDLER()
	{
		if (if_deleted == false)
		{
			delete pointer_to_handler;
		}	
		//pointer_to_handler = nullptr;
	//	handle_thread.~thread();
		//unique_mu_locker.~unique_lock();
	}
}

#endif /* _HANDLER_HPP */