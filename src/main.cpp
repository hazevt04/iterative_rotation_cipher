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
   return ( ( c == 10 ) || !std::isspace(c) );
} 

inline std::string left_circ_shift( std::string str, int num_places ) {
   if ( ( num_places % str.size() ) == 0 ) {
      return str;
   } else {
      return str.substr( ( num_places % str.size() ), ( str.size() - ( num_places % str.size() ) ) ) + 
         str.substr( 0, ( num_places % str.size() ) );
   }
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
      std::copy_if( str.begin(), str.end(), std::back_inserter( allowedchars ), []( unsigned char c ) { return is_char_allowed(c); } );
      
      std::string shifted_str = right_circ_shift( allowedchars, num_iterations );
      
      for ( str_size_type index = 0, s_index = 0; index != str.size(); ++index ) {
         if ( is_char_allowed( str.at( index ) ) ) {
            str.at( index ) = shifted_str.at( s_index++ );
         }
      }
      str += " "; 
      std::string result_str = "";
      std::string delim = " ";

      auto start = 0U;
      auto end = str.find(delim);
      while ( (end != std::string::npos) && (end != start) ) {
         std::string str_substr = str.substr( start, end - start );
         result_str += right_circ_shift( str_substr, num_iterations ) + " ";
         start = end + delim.length();
         end = str.find( delim, start );
      }

      str = result_str;
   } // end of for ( int iteration_num = 0; iteration_num < num_iterations; ++iteration_num ) {

   return std::to_string( num_iterations ) + " " + str.substr( 0, str.size() - 1 );
}

std::string decode( std::string str ) {
   using str_size_type = std::string::size_type;
   std::string delim = " ";
   char* end_ptr = nullptr;
   int num_iterations = std::strtoul( str.c_str(), &end_ptr, 10 );

   str = str.substr( str.find(" ") + 1 );
   str += " "; 

   for( int iteration_num = 0; iteration_num < num_iterations; ++iteration_num ) {
      std::string result_str = "";
      auto start = 0U;
      auto end = str.find(delim);
      while ( ( end != std::string::npos ) && ( end != start ) ) {
         std::string str_substr = str.substr( start, end - start );
         result_str += left_circ_shift( str_substr, num_iterations ) + " ";
         start = end + delim.length();
         end = str.find( delim, start );
      }
      str = result_str;
      
      std::string allowedchars;
      std::copy_if( str.begin(), str.end(), std::back_inserter( allowedchars ), []( unsigned char c ) { return is_char_allowed(c); } );
      
      std::string shifted_str = left_circ_shift( allowedchars, num_iterations );
      for ( str_size_type index = 0, s_index = 0; index != str.size(); ++index ) {
         if ( is_char_allowed( str.at( index ) ) ) {
            str.at( index ) = shifted_str.at( s_index++ );
         }
      }
      
   } // for( int iteration_num = 0; iteration_num < num_iterations; ++iteration_num ) {
    
   return str.substr( 0, str.size() - 1 );
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

      std::vector<std::string> encoded_inputs;
      std::vector<std::string> decoded_inputs;

      for ( auto& input: inputs ) {
         std::cout << "Number of Iterations is " << input.first << "\n"; 
         std::cout << "String is\n'" << input.second << "'\n\n"; 
         encoded_inputs.push_back( encode( input.first, input.second ) );
         std::cout << "Encoded String is\n'" << encoded_inputs.back() << "'\n\n"; 
         decoded_inputs.push_back( decode( encoded_inputs.back() ) );
         std::cout << "Decoded String is\n'" << decoded_inputs.back() << "'\n\n"; 
      }

      return EXIT_SUCCESS;
   
   } catch( std::exception& ex ) {
      printf( "ERROR: %s\n", ex.what() ); 
      return EXIT_FAILURE;
   }
   
}

