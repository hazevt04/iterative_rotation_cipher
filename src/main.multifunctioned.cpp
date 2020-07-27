// C++ File for main

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <vector>
#include <tuple>

constexpr unsigned char newline_char = 10;

using str_size_type = std::string::size_type;

inline bool is_char_allowed( unsigned char c ) {
   return ( ( c == newline_char ) || !std::isspace(c) );
} 


inline std::string right_circ_shift( std::string str, int num_places ) {
   if ( ( num_places % str.size() ) == 0 ) {
      return str;
   } else {
      return str.substr( ( str.size() - ( num_places % str.size()) ), num_places ) + 
         str.substr( 0, ( str.size() - ( num_places % str.size()) ) );
   }
}


inline std::string shift_allowed_chars( std::string str, int num_places ) {
   std::string allowedchars;
   std::copy_if( str.begin(), str.end(), std::back_inserter( allowedchars ), []( unsigned char c ) { return is_char_allowed(c); } );
   return right_circ_shift( allowedchars, num_places );
}


inline std::string put_shifted_allowed_chars_back( std::string str, std::string shifted_str ) {
   for ( str_size_type index = 0, s_index = 0; index != str.size(); ++index ) {
      if ( is_char_allowed( str.at( index ) ) ) {
         str.at( index ) = shifted_str.at( s_index++ );
      }
   }
   // Add a space at end for tokenization of the last word in the string
   str += " "; 
   return str;   
}


inline std::string intra_word_shift( const std::string& str, int num_places ) {

   std::string result_str = "";
   std::string delim = " ";
   auto start = 0U;
   auto end = str.find(delim);
   while ( ( end != std::string::npos ) && ( end != start ) ) {
      std::string str_substr = str.substr( start, end - start );
      result_str += right_circ_shift( str_substr, num_places ) + " ";
      start = end + delim.length();
      end = str.find( delim, start );
   }
   return result_str.substr( 0, result_str.size() - 1 );
}


std::string encode( int num_iterations, std::string str ) {
   for ( int iteration_num = 0; iteration_num < num_iterations; ++iteration_num ) {
      std::string shifted_str = shift_allowed_chars( str, num_iterations );      
      str = put_shifted_allowed_chars_back( str, shifted_str );
      str = intra_word_shift( str, num_iterations );
   } // end of for ( int iteration_num = 0; iteration_num < num_iterations; ++iteration_num ) {

   return std::to_string( num_iterations ) + " " + str;
}

std::string decode(std::string str) {
   return "";
}

int main( int argc, char** argv ) {

   try {
      std::vector<std::pair<int, std::string>> inputs = {
         {10, "If you wish to make an apple pie from scratch, you must first invent the universe."},
         {14, "True evil is a mundane bureaucracy."},
         {22, "There is nothing more atrociously cruel than an adored child."},
         {36, "As I was going up the stair\nI met a man who wasn\'t there!\nHe wasn\'t there again today,\nOh how I wish he\'d go away!"},
         {29, "I avoid that bleak first hour of the working day during which my still sluggish senses and body make every chore a penance.\nI find that in arriving later, the work which I do perform is of a much higher quality."}
      };

      for ( auto& input: inputs ) {
         std::cout << "Number of Iterations is " << input.first << "\n"; 
         std::cout << "String is\n'" << input.second << "'\n\n"; 
         std::string encoded_str = encode( input.first, input.second );
         std::cout << "Encoded String is\n'" << encoded_str << "'\n\n"; 
      }
      return EXIT_SUCCESS;
   
   } catch( std::exception& ex ) {
      printf( "ERROR: %s\n", ex.what() ); 
      return EXIT_FAILURE;
   }
   
}

