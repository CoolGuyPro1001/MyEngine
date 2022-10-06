#ifndef DELEGATE_H
#define DELEGATE_H

template<typename RetType, typename... Args>
struct FunctionWrapper
{
public:
    FunctionWrapper() = default;

    FunctionWrapper(RetType (*function)(Args...))
    {
        m_func = function;
    };

    FunctionWrapper(const FunctionWrapper<RetType, Args...>& other)
    {
        m_func = other.m_func;
    };

    virtual RetType Execute(Args... args)
    {
        if(m_func)
            m_func(args...);
    };

private:
    RetType (*m_func)(Args...);
};

template<class ObjType, typename RetType, typename... Args>
struct MemberFunctionWrapper : public FunctionWrapper<RetType, Args...>
{
public:
    MemberFunctionWrapper() = default;

    MemberFunctionWrapper(ObjType* object, RetType (ObjType::*function)(Args...))
    {
        m_func = function;
        m_obj = object;
    };

    MemberFunctionWrapper(const MemberFunctionWrapper<ObjType, RetType, Args...>& other)
    {
        m_func = other.m_func;
        m_obj = other.m_obj;
    };

    RetType Execute(Args... args)
    {
        if(m_func && m_obj)
            (m_obj->*m_func)(args...);
    };

private:
    RetType (ObjType::*m_func)(Args...);
    ObjType* m_obj;
};

template<typename RetType, typename... Args>
struct Delegate
{
    Delegate()
    {
        m_func_wrapper = nullptr;
    }

    Delegate(const Delegate& other)
    {
        m_func_wrapper = other.m_func_wrapper;
    };

    void operator=(const Delegate& other)
    {
        m_func_wrapper = other.m_func_wrapper;
    };

    void Bind(RetType (*function)(Args...))
    {
        m_func_wrapper = CreateShared<FunctionWrapper<RetType, Args...>>(function);
    };

    template<class ObjType>
    void Bind(ObjType* object, RetType (ObjType::*function)(Args...))
    {
        m_func_wrapper = CreateShared<MemberFunctionWrapper<ObjType, RetType, Args...>>(object, function);
    };

    template<class ObjType>
    void Bind(Shared<ObjType> object, RetType (ObjType::*function)(Args...))
    {
        m_func_wrapper = CreateShared<MemberFunctionWrapper<ObjType, RetType, Args...>>(object.get(), function);
    };

    RetType Execute(Args... args)
    {
        m_func_wrapper->Execute(args...);
    };

private:
    Shared<FunctionWrapper<RetType, Args...>> m_func_wrapper;
};


#endif
