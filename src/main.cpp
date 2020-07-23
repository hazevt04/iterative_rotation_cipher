// C++ File for main

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>

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
      std::string nospaces;
      std::copy_if( str.begin(), str.end(), std::back_inserter( nospaces ), []( unsigned char c ) { return !std::isspace(c); } );
      
      std::string shifted_str = right_circ_shift( nospaces, num_iterations );
      
      for ( str_size_type index = 0, s_index = 0; index != str.size(); ++index ) {
         if ( !std::isspace( str.at( index ) ) ) {
            str.at( index ) = shifted_str.at( s_index++ );
         }
      }
      auto iss = std::istringstream( str );
      std::string sub_str = "";
      std::string result_str = "";
      while ( iss >> sub_str ) {
         result_str += " " + right_circ_shift( sub_str, num_iterations ); 
      }
      str = result_str;
   } // end of for ( int iteration_num = 0; iteration_num < num_iterations; ++iteration_num ) {
   return str;
}

std::string decode(std::string str) {
   return "";
}

int main( int argc, char** argv ) {

   try {
 
      int num_iterations = 10;
      std::string str = "If you wish to make an apple pie from scratch, you must first invent the universe.";

      std::cout << "String is '" << str << "'\n"; 

      std::string encoded_str = encode( num_iterations, str );
      std::cout << "Encoded String is " << encoded_str << "\n"; 
      return EXIT_SUCCESS;
   
   } catch( std::exception& ex ) {
      printf( "ERROR: %s\n", ex.what() ); 
      return EXIT_FAILURE;
   }
   
}

