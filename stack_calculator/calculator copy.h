#ifndef CALCULATOR_H
#define CALCULATOR_H

//
// Assignment 2 : Simple calculator using Stack
//
// COSE213 Spring 2021
//
// Won-Ki Jeong (wkjeong@korea.ac.kr)
//

#include <iostream>
#include <cassert>
#include <math.h>
#include <string.h>
#include "stack.h"


Stack<double> opr; // stack for operands
Stack<char> opt;   // stack for operators


//
// Modify Eval() below to evaluate the given expression
//
double Eval(char* in)
{
    double out = 0;

    char buf[1000]; // temp buffer
    char lastToken = '#';

    double operand;
    int i = 0, bi = 0, unary=0;

    opt.Push('#');

    char in1[strlen(in)+2];

    in1[i++] = '(';
    while (i < strlen(in)+1) {
        in1[i] = in[i-1];
        i++;
    }
    in1[i] = '\0';

    i=1;
    while(in1[i] != '\0')
    {
        char c = in1[i];

        // Operators
        if(c == '+' || c == '-' ||
           c == '*' || c == '/' ||
           c == '(' || c == ')') {
            if(bi > 0)
            {
                buf[bi++] = '\0';
                operand = atof(buf);
                if (unary == 1) {
                    operand = operand*(-1);
                    unary = 0;
                }

                bi = 0;

                // push operand
                std::cout << "New operand : " << operand << std::endl;
                opr.Push(operand);
            }

            // push operator
            std::cout << "New operator : " << c << std::endl;
            if (c=='(') {
                opt.Push(c);
            }
            else if (c==')') {
                while((opt.Top() != '(') && (opt.Top() != '#')) {
                    char imsi = opt.Top();
                    opt.Pop();
                    double num1 = opr.Top();
                    opr.Pop();
                    double num2 = opr.Top();
                    opr.Pop();

                    if (imsi =='+') {opr.Push(num1+num2);}
                    else if (imsi =='*') {opr.Push(num1*num2);}
                    else if (imsi =='/') {opr.Push(num2/num1);}
                    else if (imsi =='-') {opr.Push(num2-num1);}
                }
                if (opt.Top() == '(') {
                    opt.Pop();
                }
            }

            else if (c == '-') {
                if (in1[i-1] == '(') {
                    unary = 1;
                }

                else {
                    if ((opt.Top() == '#') || (opt.Top() == '(')) {
                        opt.Push(c);
                    }

                    else{
                        int rank;
                        while ((opt.Top() != '#') && (1 <= rank)) {
                            char imsi = opt.Top();
                            opt.Pop();
                            double num1 = opr.Top();
                            opr.Pop();
                            double num2 = opr.Top();
                            opr.Pop();

                            if (imsi =='+') {
                                opr.Push(num1+num2);
                                rank = 1;
                            }
                            else if (imsi =='*') {
                                opr.Push(num1*num2);
                                rank = 2;
                            }
                            else if (imsi =='/') {
                                opr.Push(num2/num1);
                                rank = 2;
                            }
                            else if (imsi =='-') {
                                opr.Push(num2-num1);
                                rank = 1;
                            }
                        }
                        opt.Push(c);
                    }
                }
            }

            else if (c == '+' || c == '*' || c == '/') {
                if ((opt.Top() == '#') || (opt.Top() == '(')) {
                    opt.Push(c);
                }
                else {
                    int rank1;
                    int rank2;
                    if (c == '*' || c == '/') {
                        rank1 = 2;
                    }
                    else if (c == '+') {
                        rank1 = 1;
                    }
                    if (opt.Top() == '*' || opt.Top() == '/') {
                        rank2 = 2;
                    }
                    else if (opt.Top() == '+' || opt.Top() == '-') {
                        rank2 = 1;
                    }

                    if (rank1 > rank2) {
                        opt.Push(c);
                    }

                    else {
                        while ((opt.Top() != '#') && (rank1 <= rank2)) {
                            char imsi = opt.Top();
                            opt.Pop();
                            double num1 = opr.Top();
                            opr.Pop();
                            double num2 = opr.Top();
                            opr.Pop();

                            if (imsi =='+') {
                                opr.Push(num1+num2);
                                rank2 = 1;
                            }
                            else if (imsi =='*') {
                                opr.Push(num1*num2);
                                rank2 = 2;
                            }
                            else if (imsi =='/') {
                                opr.Push(num2/num1);
                                rank2 = 2;
                            }
                            else if (imsi =='-') {
                                opr.Push(num2-num1);
                                rank2 = 1;
                            }
                        }
                        opt.Push(c);
                    }
                }
            }
        }
        // Operands
        else if(c == '0' || c == '1' ||
                c == '2' || c == '3' ||
                c == '4' || c == '5' ||
                c == '6' || c == '7' ||
                c == '8' || c == '9' ||
                c == '.')
        {
            buf[bi++] = c;
        }

        else {
            i++;
            continue;
        }

        i++;
    }

    // push the very last operand if exists
    if(bi > 0)
    {
        buf[bi++] = '\0';
        operand = atof(buf);
        bi = 0;

        // push operand
        std::cout << "New operand : " << operand << std::endl;
        opr.Push(operand);
    }
    i=0;
    while (opt.Top() != '#') {
        char imsi = opt.Top();
        opt.Pop();
        double num1 = opr.Top();
        opr.Pop();
        double num2 = opr.Top();
        opr.Pop();

        if (imsi =='+') {opr.Push(num1+num2);}
        else if (imsi =='*') {opr.Push(num1*num2);}
        else if (imsi =='/') {opr.Push(num2/num1);}
        else if (imsi =='-') {opr.Push(num2-num1);}
    }

    out = opr.Top();
    return out;
}

#endif