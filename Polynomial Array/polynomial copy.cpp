#include "polynomial.h"
#include <iostream>
#include <math.h>


//
// Implementation
//


// Copy constructor
Polynomial::Polynomial(const Polynomial& source)
{
    // ToDo
    capacity = source.capacity;
    terms = source.terms;
    termArray = new Term[capacity];
    for (int i = 0; i < capacity; i++) {
        termArray[i].coef = source.termArray[i].coef;
        termArray[i].exp = source.termArray[i].exp;
    }
}

// Destructor
Polynomial::~Polynomial()
{
    // ToDo
    delete[] termArray;
    termArray = NULL;
}


Polynomial& Polynomial::operator = (const Polynomial& source)
{
    // ToDo
    if (this != &source) {
        delete[] termArray;
        capacity = source.capacity;
        terms = source.terms;
        termArray = new Term[capacity];
        for (int i = 0; i < capacity; i++) {
            termArray[i].coef = source.termArray[i].coef;
            termArray[i].exp = source.termArray[i].exp;
        }
    }
    return *this;
}



// Sum of *this and source polynomials
Polynomial Polynomial::operator +(const Polynomial& source)
{
    Polynomial c;

    // ToDo
    int aPos = 0, bPos = 0;
    int at = terms, bt = source.terms;

    if (at == 0) {
        return source;
    }

    if (bt == 0) {
        return *this;
    }

    while ((aPos < at) && (bPos < bt)) {
        if (termArray[aPos].exp == source.termArray[bPos].exp) {
            float t = termArray[aPos].coef + source.termArray[bPos].coef;
            if ((t) && (abs(t) > 1e-6)) {c.CreateTerm(t, termArray[aPos].exp); }
            aPos++;
            bPos++;
        }
        else if (termArray[aPos].exp < source.termArray[bPos].exp) {
            c.CreateTerm(source.termArray[bPos].coef, source.termArray[bPos].exp);
            bPos++;
        }
        else {
            c.CreateTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
    }
    for (; aPos<at ; aPos++) {
        c.CreateTerm(termArray[aPos].coef, termArray[aPos].exp);
    }
    for (; bPos<bt ; bPos++) {
        c.CreateTerm(source.termArray[bPos].coef, source.termArray[bPos].exp);
    }

    return c;
}

Polynomial Polynomial::operator - (const Polynomial& source)
{
    Polynomial c;

    // ToDo

    int aPos = 0, bPos = 0;
    int at = terms, bt = source.terms;
    if (at == 0) {
        for (int i=0; i < bt; i++) {
            c.CreateTerm(-source.termArray[i].coef, source.termArray[i].exp);
        }
        return c;
    }

    if (bt==0) {
        return *this;
    }

    while ((aPos < at) && (bPos < bt)) {
        if (termArray[aPos].exp == source.termArray[bPos].exp) {
            float t = termArray[aPos].coef - source.termArray[bPos].coef;
            if ((t) && (abs(t) > 1e-6)) {c.CreateTerm(t, termArray[aPos].exp); }
            aPos++;
            bPos++;
        }
        else if (termArray[aPos].exp < source.termArray[bPos].exp) {
            c.CreateTerm(-source.termArray[bPos].coef, source.termArray[bPos].exp);
            bPos++;
        }
        else {
            c.CreateTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
    }
    for (; aPos<at;aPos++) {
        c.CreateTerm(termArray[aPos].coef, termArray[aPos].exp);
    }
    for (; bPos<bt; bPos++) {
        c.CreateTerm(-source.termArray[bPos].coef, source.termArray[bPos].exp);
    }

    return c;
}


Polynomial Polynomial::operator * (const Polynomial& source)
{
    Polynomial c;

    // ToDo
    int at = terms, bt = source.terms;
    for (int i=0; i < at; i++) {
        for (int j = 0; j < bt; j++) {
            float t = termArray[i].coef*source.termArray[j].coef;
            int k = termArray[i].exp + source.termArray[j].exp;
            if ((t) && (abs(t) > 1e-6)){
                Polynomial temp;
                temp.CreateTerm(t,k);
                c = c + temp;
            }
        }
    }
    return c;
}


float Polynomial::Eval(float x)
{
    float ret = 0;

    // ToDo
    int aPos = 0;
    int at = terms;

    while (aPos<at) {
        ret += termArray[aPos].coef * pow(x, termArray[aPos].exp);
        aPos++;
    }
    return ret;
}




// Compute derivative of the current polynomial
Polynomial Polynomial::Derivative()
{
    Polynomial c;

    // ToDo

    int aPos = 0;
    int at = terms;

    while (aPos<at) {
        float t = termArray[aPos].coef * termArray[aPos].exp;
        if (t && (abs(t) > 1e-6)) {c.CreateTerm(t, termArray[aPos].exp-1); }
        aPos++;
    }
    return c;

}


void Polynomial::CreateTerm(const float coef, const int exp)
{
    // ToDo
    if (terms == capacity) {
        capacity *= 2;
        Term *temp = new Term[capacity];
        std::copy(termArray, termArray+terms, temp);
        delete[] termArray;
        termArray = temp;
    }
    termArray[terms].coef = coef;
    termArray[terms].exp = exp;
    terms++;

    for (int i = 1; i < terms; i++) {
        Term cur = termArray[i];
        int j = i-1;
        while ((j >= 0) && (termArray[j].exp < exp)) {
            termArray[j+1] = termArray[j];
            j--;
        }
        termArray[j+1]=cur;
    }
}
