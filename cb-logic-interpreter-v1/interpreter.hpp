#ifndef INTERPRETER_HPP_INCLUDED
#define INTERPRETER_HPP_INCLUDED
#include<iostream>
#include<string>
#include<exception>
#include<map>


using namespace std;
class VarExp;

class Context{
public:
    virtual ~Context(){}
    bool lookup(const string) const;
    void assign(VarExp*, bool);

    map<string,VarExp*> _context;
};

class BoolExp {
public:
    BoolExp(){}
    virtual ~BoolExp() {}
    virtual bool evaluate(Context&) =0;
    virtual BoolExp* replace(const string,BoolExp&) = 0;
    virtual BoolExp* copy() const = 0;

};

class VarExp: public BoolExp {

public:
    VarExp(const string);
    virtual ~VarExp(){}

    virtual bool evaluate(Context &);
    virtual BoolExp* replace(const string, BoolExp&);
    virtual BoolExp* copy()const ;

    string _name;
    bool _value;
};

VarExp::VarExp(const string n){
  _name = n;
}

bool VarExp::evaluate(Context& context){
 return context.lookup(_name);
}

BoolExp* VarExp::copy()const {
  return new VarExp(_name);  //forward?
}

BoolExp* VarExp::replace(const string n, BoolExp& bexp){

 if(this->_name==n)
    return bexp.copy();
 else
    return this->copy();


}


bool Context::lookup(const string s) const {
 VarExp* expression = _context.at(s);

 return expression->_value;
}

void Context::assign(VarExp* ve,bool b){
   ve->_value = b;
   _context.emplace(ve->_name,ve);
}


class ANDExp: public BoolExp {
public:
    ANDExp(BoolExp*,BoolExp*);
    virtual ~ANDExp() { delete _op1;
                        delete _op2;
                        }
    virtual bool evaluate(Context &);
    virtual BoolExp* replace(const string, BoolExp&);
    virtual BoolExp* copy() const;

    BoolExp* _op1=nullptr;
    BoolExp* _op2=nullptr;



};

class ORExp:public ANDExp {
public:
    ORExp(BoolExp* a,BoolExp* b):ANDExp(a,b){}
    virtual bool evaluate(Context&) override;
};

class NOTExp:public BoolExp {
public:
    NOTExp(BoolExp* a){
        _op1 = a;
    }

    virtual ~NOTExp(){delete _op1;}
    virtual bool evaluate(Context &);
    virtual BoolExp* replace(const string, BoolExp&);
    virtual BoolExp* copy() const;
    BoolExp* _op1;
};


ANDExp::ANDExp(BoolExp* o1,  BoolExp* o2 ){
 _op1 = o1;
 _op2 = o2;

}

bool ANDExp::evaluate(Context& context){
bool r = false;
try{

    r = (_op1->evaluate(context) && _op2->evaluate(context));

}catch(exception e){
    cout << "Error in AndExp evaluate: " << e.what() << endl;
}

return r;


}

BoolExp* ANDExp::copy() const {
return new ANDExp( _op1->copy(), _op2->copy());
}

BoolExp* ANDExp::replace(const string n, BoolExp& bexp){

return new ANDExp(_op1->replace(n,bexp), _op2->replace(n,bexp));

}

bool ORExp::evaluate(Context& context){

bool r = false;
try{

    r = (_op1->evaluate(context) || _op2->evaluate(context));

}catch(exception e){
    cout << "Error in ORExp evaluate: " << e.what() << endl;
}

return r;

}
BoolExp* NOTExp::copy() const {
    return new NOTExp(_op1->copy());
}
bool NOTExp::evaluate(Context& context){
bool b = (!_op1->evaluate(context));
 return b;
}

BoolExp* NOTExp::replace(const string n, BoolExp& bex){
    return _op1->replace(n,bex);
}


#endif // INTERPRETER_HPP_INCLUDED
