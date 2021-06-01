#include "QCalculatorUI.h"

QCalculatorUI::QCalculatorUI() : QWidget(NULL,Qt::WindowCloseButtonHint)
{
}

bool  QCalculatorUI::construct()
{
    int ret;
    const char* butnText[20]=
    {
        "<-","CE",
        "7","8","9","+","(",
        "4","5","6","-",")",
        "1","2","3","*","=",
        "0",    ".","/",
    };

    const int butnPos[20][4]=       
    {
      {10,50,90,40},{110,50,140,40},                                                  
      {10,100,40,40},{60,100,40,40},{110,100,40,40},{160,100,40,40},{210,100,40,40},    
      {10,150,40,40},{60,150,40,40},{110,150,40,40},{160,150,40,40},{210,150,40,40},   
      {10,200,40,40},{60,200,40,40},{110,200,40,40},{160,200,40,40},{210,200,40,90},    
      {10,250,90,40},               {110,250,40,40},{160,250,40,40},                   
    };

    mline  =new QLineEdit(this);
    if(mline==NULL)
        return false;
    mline->resize(240,30);
    mline->move(10,10);
    mline->setAlignment(Qt::AlignRight);
    mline->setReadOnly(1);
   // mline->setFont(QFont(0,10));        //Set font
    this->setWindowTitle("Calculator");
    for(int i=0;i<20;i++)
   {
         mbuton[i]= new  QPushButton(butnText[i],this);
         if(mbuton[i]==NULL)
             return false;

         mbuton[i]->resize(butnPos[i][2],butnPos[i][3]);
         mbuton[i]->move(butnPos[i][0],butnPos[i][1]);

         ret = QObject::connect(mbuton[i],SIGNAL(clicked()),this,SLOT(handler_clicked()));
         if(ret==false)
             return false;
   }
   return true;
}

QCalculatorUI* QCalculatorUI::NewIntance()      
{
    QCalculatorUI* ret = new QCalculatorUI();
    if(ret==NULL || !ret->construct())
    {
        delete ret;
        return NULL;
    }
    return ret;
}

int  QCalculatorUI::LastMatchingBoth(QString& str1,const char* str2)     
{
    for(int i=str1.length();i>=0;i--)
    {
        for(unsigned int j=0;j<strlen(str2);j++)
            if(str1[i]==str2[j])
                 return i;
    }
   return -1;
}

int  QCalculatorUI::MatchingBoth(QString& str1,const char* str2)         
{
    for(int i=0;i<str1.length();i++)
    {
        for(unsigned int j=0;j<strlen(str2);j++)
            if(str1[i]==str2[j])
                 return i;
    }
   return -1;
}

void QCalculatorUI::handler_clicked()      
{
    static int ClearLine=0;
    static int bracket_cnt=0;          
    QPushButton *btn =dynamic_cast<QPushButton* >(sender()); 
    QString line = mline->text();
    QString text = btn->text();  

    if(ClearLine)
    {
        mline->setText("");
        line.clear();
        ClearLine=0;
    }if(text>="0"&&text<="9")    
    {
        QString tmp= line.right(1);
        if(tmp.length() && tmp[0]==')')   
        {
            return;
        }
        line+=text;
    }

    else if(text=="." )    
    {
        QString tmp= line.right(1);
        if(tmp.length()) 
       {
            if(MatchingBoth(tmp,"0123456789")== -1) 
            {
                return;
            }
       }
       else            
       {
                return ;
       }

       int pos= LastMatchingBoth(line,"+-*/.()");   
        if(pos!= -1 &&line[pos]=='.' )      
        {
            return ;
        }
         line+=text;
    }

    else if(text=="+"||text=="-")       
    {
        QString tmp= line.right(1);
       if(tmp.length()&& tmp[0]=='.')    
       {
          return ;
       }
       tmp= line.right(2);
       if(tmp.length()==2)         
       {
           if(tmp[0]=='+'||tmp[0]=='-'||tmp[0]=='*'||tmp[0]=='/'||tmp[0]=='(')
                if(tmp[1]=='+'||tmp[1]=='-'||tmp[1]=='*'||tmp[1]=='/')
                            return ;
       }
        line+=text;
    }

    else if(text=="*"||text=="/")    
    {
         QString tmp= line.right(1);
         if(tmp.length())     
         {
             if(MatchingBoth(tmp,"(.+-*/")!= -1) 
             {
                 return;
             }
         }
         else                   
              return;

        line+=text;
    }

    else if(text=="(")      
    {
        QString tmp= line.right(1);
        if(tmp.length())             
        {
            if(MatchingBoth(tmp,")0123456789.")!= -1) 
            {
                return;
            }
        }

        tmp= line.right(2);
        if(tmp.length()==2)          
        {
             if(tmp[0]=='+'||tmp[0]=='-'||tmp[0]=='*'||tmp[0]=='/')
                 if(tmp[1]=='+'||tmp[1]=='-'||tmp[1]=='*'||tmp[1]=='/')
                             return ;
        }
         line+=text;
         bracket_cnt++;
    }

    else if(text==")")       
    {
        QString tmp= line.right(1);
        if(bracket_cnt==0)  
           return;

        if(tmp.length())           
        {
           if(MatchingBoth(tmp,"+-*/.(")!= -1) 
           {
               return;
           }
        }
        else                 
           return;

        line+=text;
        bracket_cnt--;
    }

    else if(text=="<-")       
        if(line.length())
        line.chop(1);
    }

    else if(text=="CE")     
    {
        line.clear();
        bracket_cnt=0;
    }

    else if(text=="="&& line.length())
    {
        QString ret=mDec.Result(line);
        if(ret==NULL)  
        {
            line += " : ";
            line +="The divisor cannot be zero";
        }
        else if(ret=="Error")
         {
            line += ":";
            line +="Format error";
         }
         else
         {
             line += "=";
             line += ret;
         }
        ClearLine =1;
    }
    mline->setText(line);
}

void QCalculatorUI::show()           
{
    QWidget::show();
    this->setFixedSize(this->width(),this->height());
}
