#include <iostream>
#include "interpreter.hpp"

using namespace std;

int main()
{
// (r and x) or (y and (not x))
try{
BoolExp* expression = nullptr;
Context context;
VarExp* x = new VarExp("X");
VarExp* y = new VarExp("Y");
VarExp* r = new VarExp("R");
expression = new ORExp(
                        new ANDExp(r,x),
                       new ANDExp(y,new NOTExp(x))
                       );
context.assign(r,true);
context.assign(x,false);
context.assign(y,true);




bool eval_res = expression->evaluate(context);

cout << "Evaluation the expression: (r and x) or ( y and (not x)):being r=true and x=false and y=true, results in " << (eval_res?"TRUE":"FALSE") << endl;
delete r, x, y;
}catch(exception & e){

cout << "Error in interpreter: " << e.what() << endl;

}






    cout << "Hello world!" << endl;
    return 0;
}
