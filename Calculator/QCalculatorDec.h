#ifndef QCALCULATORDEC_H
#define QCALCULATORDEC_H
#include <QString>
#include <QStack>
#include <QQueue>
#include <QDebug>
class QCalculatorDec
{
private:
    QQueue<QString> Split(const QString& exp);         
    QQueue<QString> Transfer(QQueue<QString>& exp);    
    QString Calculate(QQueue<QString>& exp);           

    QString Calculate(QString& l,QString& op,QString& r );
    QString ValidNum(QString str);

public:
    QCalculatorDec();
    QString Result(const QString& exp);
};

#endif // QCALCULATORDEC_H
The QCalculatorDec.cpp code is as follows:

#include "QCalculatorDec.h"

QCalculatorDec::QCalculatorDec()
{
}

QQueue<QString> QCalculatorDec::Split(const QString& exp)         
{
    QQueue<QString> ret;
    QString num="";

    for(int i=0;i<exp.length();i++)
    {
        if( (exp[i]=='.') || ( (exp[i]>='0') && (exp[i]<='9') ))   
        {
            num += exp[i];
        }

        else if(exp[i]== '(' || exp[i]== ')' || exp[i]== '*' || exp[i]== '/'  )
        {
            if(!num.isEmpty())
            {
                ret.enqueue(num);        
                num.clear();
            }
            ret.enqueue(exp[i]);
        }

        else if(exp[i]== '+' || exp[i]== '-')          
        {
            if(i==0)     
            {
             num+= exp[i];
            }

            else if(exp[i-1]=='(' || exp[i-1]=='+' || exp[i-1]=='-' || exp[i-1]=='*' || exp[i-1]=='/')
            {
             num+= exp[i];
            }
            else
            {
                if(!num.isEmpty())
                {
                    ret.enqueue(num);        
                    num.clear();
                }
             ret.enqueue(exp[i]);
            }
        }
    }

    if(!num.isEmpty())        
    {
        ret.enqueue(num);
        num.clear();
    }
return ret;
}

QQueue<QString> QCalculatorDec::Transfer(QQueue<QString>& exp)     
{
    QStack<QString> stack;
    QQueue<QString> ret;
    bool num_ok;
    QString symbol;

    while(!exp.isEmpty())
    {
      symbol = exp.dequeue();   //Outgoing queue
      symbol.toDouble(&num_ok);

      if(num_ok==true)          //number
      {
           stack.push(symbol);
      }

      else if(symbol=="+"||symbol=="-")
      {
          while(!stack.isEmpty() &&(stack.top()!="("))
          {
              ret.enqueue(stack.pop());
          }
          stack.push(symbol);
      }

      else if(symbol=="*"||symbol=="/")
      {
          while(!stack.isEmpty() && (stack.top()!="(") && (stack.top()!="+") && (stack.top()!="-"))
          {
              ret.enqueue(stack.pop());    
          }
          stack.push(symbol);
      }

      else if(symbol == "(")
      {
         stack.push(symbol);
      }

      else if(symbol ==")")
      {
          while(!stack.isEmpty() && (stack.top()!="("))
          {
              ret.enqueue(stack.pop());    
          }
          if(stack.top()=="(")
            stack.pop();
      }
    }

    while(!stack.isEmpty()&& (stack.top()!="("))        
    {
       ret.enqueue(stack.pop());    
    }return ret;
}

QString QCalculatorDec::ValidNum(QString str)
 {
    QString num;
if(str.indexOf(".")== -1) 
        return str;

    while(str.length()>1)  
    {
         num=str.right(1);
         if(num=="."||num=="0")
         {
             str.chop(1);
             if(num==".")
                 return  str;
         }
         else
             return str;
    }
    return str;
}

QString QCalculatorDec::Calculate(QString& l,QString& op,QString& r )
{
    double left,right,res;
    QString ret="";
    left = l.toDouble();
    right = r.toDouble();
    if(op == "+")
    {
        res = left + right;
    }

    else if(op == "-")
    {
        res = left - right;
    }

    else if(op == "*")
    {
        res = left * right;
    }

    else if(op == "/")
    {
        if( (right>(-0.000000000000001)) && (right<(0.000000000000001)) )   
            return NULL;
        else
            res = left/right;
    }

    ret.sprintf("%f",res);
    return ret;
}

QString QCalculatorDec::Calculate(QQueue<QString>& exp)            
{
    QStack<QString> stack;
    QString symbol,L,R,op,ret;
    bool num_ok;

    while(!exp.isEmpty())
    {
      symbol = exp.dequeue();  
      symbol.toDouble(&num_ok);

      if(num_ok==true)     
      {
        stack.push(symbol);
      }
      else                 
      {
          if(stack.size()<2)
              return "Error";

          R= stack.pop();
          L= stack.pop();
          ret = Calculate(L,symbol,R );
          if(ret==NULL)
              return ret;

          stack.push(ret);
      }
    }
    if(stack.size()==1) 
    {
         return ValidNum(stack.pop());
    }
    else
    {return "Error";
    }
}

QString QCalculatorDec::Result(const QString& exp)
{
      QQueue<QString> q=Split(exp); 
      q=Transfer(q);                
      return Calculate(q);          
}
