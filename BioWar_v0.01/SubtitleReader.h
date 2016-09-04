#ifndef SUBTITLEHEADER_H
#define SUBTITLEHEADER_H
#include <fstream>
#include <vector>
#include <string>

class SubtitleReader
{
public:
   SubtitleReader( const std::string &filePath );
   ~SubtitleReader();

   std::pair< long, std::vector< std::string > >& GetLine( unsigned long index );
   std::vector< std::pair< long, std::vector< std::string > > >& GetSubtitles();

private:
   void readFile();

   std::fstream m_stream;
   std::vector< std::pair< long, std::vector< std::string > > > m_subtitles;
};

#endif

