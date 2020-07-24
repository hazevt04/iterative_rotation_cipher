// C++ File for main

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <vector>
#include <tuple>

inline bool is_char_allowed( unsigned char c ) {
   return ( c == 10 || !std::isspace(c) );
} 

inline std::string right_circ_shift( std::string str, int num_places ) {
   if ( ( num_places % str.size() ) == 0 ) {
      return str;
   } else {
      return str.substr( ( str.size() - ( num_places % str.size()) ), num_places ) + 
         str.substr( 0, ( str.size() - ( num_places % str.size()) ) );
   }
}

std::string encode( int num_iterations, std::string str ) {
   using str_size_type = std::string::size_type;
   for ( int iteration_num = 0; iteration_num < num_iterations; ++iteration_num ) {
      std::string allowedchars;
      std::cout << "Iteration " << iteration_num << ": str is\n'" << str << "'\n"; 
      std::copy_if( str.begin(), str.end(), std::back_inserter( allowedchars ), []( unsigned char c ) { return is_char_allowed(c); } );
      
      std::string shifted_str = right_circ_shift( allowedchars, num_iterations );
      std::cout << "Iteration " << iteration_num << ": shifted_str is\n'" << str << "'\n"; 
      
      for ( str_size_type index = 0, s_index = 0; index != str.size(); ++index ) {
         if ( is_char_allowed( str.at( index ) ) ) {
            str.at( index ) = shifted_str.at( s_index++ );
         }
      }
      std::cout << "Iteration " << iteration_num << ": after putting the shifted chars back in str is\n'" << str << "'\n"; 
      
      // auto iss = std::istringstream( str );
      // std::string sub_str = "";
      // std::string result_str = "";
      // while ( iss >> sub_str ) {
      //    result_str += " " + right_circ_shift( sub_str, num_iterations );
      // }
      // str = result_str;

      str_size_type pos = 0;
      std::string result_str = "";
      while ( (pos = str.find(" ")) != std::string::npos ) {
         result_str += str.substr( 0, pos );
         std::cout << "Iteration " << iteration_num << ": pos is " << pos << " result_str is\n'" << result_str << "'\n"; 
         str.erase( 0, pos + 1 );
         std::cout << "Iteration " << iteration_num << ": pos is " << pos << " str is\n'" << str << "'\n"; 
      }
      str = result_str;
   } // end of for ( int iteration_num = 0; iteration_num < num_iterations; ++iteration_num ) {

   str = std::to_string( num_iterations ) + str;
   return str;
}

std::string decode(std::string str) {
   return "";
}

int main( int argc, char** argv ) {

   try {
 
      std::vector<std::pair<int, std::string>> inputs = {
         // {10, "If you wish to make an apple pie from scratch, you must first invent the universe."},
         // {14, "True evil is a mundane bureaucracy."},
         // {22, "There is nothing more atrociously cruel than an adored child."},
         {36, "As I was going up the stair\nI met a man who wasn\'t there!\nHe wasn\'t there again today,\nOh how I wish he\'d go away!"}
         // {29, "I avoid that bleak first hour of the working day during which my still sluggish senses and body make every chore a penance.\nI find that in arriving later, the work which I do perform is of a much higher quality."}
      };

      for ( auto& input: inputs ) {
         std::cout << "Number of Iterations is " << input.first << "\n"; 
         std::cout << "String is\n'" << input.second << "'\n"; 
         std::string encoded_str = encode( input.first, input.second );
         std::cout << "Encoded String is\n'" << encoded_str << "'\n"; 
      }
      return EXIT_SUCCESS;
   
   } catch( std::exception& ex ) {
      printf( "ERROR: %s\n", ex.what() ); 
      return EXIT_FAILURE;
   }
   
}

