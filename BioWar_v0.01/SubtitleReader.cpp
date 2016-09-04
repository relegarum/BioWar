#include "SubtitleReader.h"
#include <sstream>
#include <string>


SubtitleReader::SubtitleReader( const std::string &filePath ) :
   m_stream( filePath, std::fstream::in )
{
   readFile();
}


std::pair< long, std::vector< std::string > >& SubtitleReader::GetLine( unsigned long index ) 
{
   return m_subtitles.at( index );
}

std::vector< std::pair< long, std::vector< std::string > > >& SubtitleReader::GetSubtitles()
{
   return m_subtitles;
}

void SubtitleReader::readFile()
{
   std::string lineString;
   while( std::getline( m_stream, lineString ) )
   {
      std::vector< std::string > sceneLines;
      long time;
      std::string text;
      std::string strinTime;
      int pos = lineString.find( '|' );
     
      strinTime = lineString.substr( 0, pos );
      text      = lineString.substr( pos + 1, std::string::npos );
      

      std::istringstream ss( text );
      while (!ss.eof())         // See the WARNING above for WHY we're doing this!
      {
         std::string x;               // here's a nice, empty string
         std::getline( ss, x, '%' );  // try to read the next field into it
         if( !x.empty() )
            sceneLines.push_back( x );
      }

      time = atoi( strinTime.c_str() );

      m_subtitles.push_back( std::make_pair( time, sceneLines ) );
   }
}

SubtitleReader::~SubtitleReader(void)
{
   m_stream.close();
}
