#ifndef CALLBACK_H
#define CALLBACK_H
#pragma once

template <class T>
class Callback
{
public:
    typedef void (T::* fn)(int anArg);

    Callback(T& trg, fn op)
        : m_rTarget(trg)
        , m_Operation(op)
    {
    }

    void Execute(int in)
    {
        (m_rTarget.*m_Operation)(in);
    }

    void Execute()
    {
        (m_rTarget.*m_Operation)();
    }

private:

    Callback();
    Callback(const Callback&);

    T& m_rTarget;
    fn m_Operation;

};
#endif
