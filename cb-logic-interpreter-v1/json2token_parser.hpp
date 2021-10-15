#ifndef JSON_PARSER_HPP_INCLUDED
#define JSON_PARSER_HPP_INCLUDED
/*
json_parser.hpp
Trying to find a serializable format for communication, thus json

Json format candidates:
1-
Keynames table: s:symbol := ( | ) |
                o:operand:= AND | OR | NOT | XOR?
                p: propositions:= "Mary stares at the sky" | "Dogs bark"
                constants??
VarExp has name, proposition, value

Error while parsing json: NOT ordered sops|sps | sopospops <<HERE!! Recursive

expressions = [{s="(",p="Many Birds are flying", o="AND",s="(",p="It snows",o="OR",p="We are in Spring",s=")",s=")"},
{ s="(",p="One plus One is two",o="AND",p="We are currently living in the earth",s=")",o="OR",s="(",o="NOT", p="We can fly by ourselves",s=")" },
{                                                                                                            }]

expression[0], let's say: We are in Spring is = FALSE AND Many Birds are flying false
Does it snow?
Result: FALSE

read file, write to json tree
for expresion in expressions
while expression has tokens
    getelement:
    is s
    is o
    is p
   if(well formed)
    create VarExp
        random letter
        set proposition

2- Approach 2nd degree logic
s:symbol
o: operand
p: proposition { value="", likelihood= }

expressions = [{s:"(",p:{v="speed of light is 128000m/s",l="0.89"}, o="AND", p={v="Whales fly",l="0.0005"},s=")"]



*/






#endif // JSON_PARSER_HPP_INCLUDED
