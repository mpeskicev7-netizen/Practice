   #include "lexer.hpp"
   #include <iostream>

   int main() {
       std::string test_json = "{ [ ] } , :";
       Lexer lexer(test_json);
       
       while (true) {
           Token t = lexer.nextToken();
           std::cout << "Type: " << static_cast<int>(t.type) 
                     << ", Line: " << t.line 
                     << ", Pos: " << t.position << "\n";
                     
           if (t.type == TokenType::End) break;
       }
       return 0;
   }