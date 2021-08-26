#include <iostream>
#include <fstream>
#include <google/vcencoder.h>  // Read this file for interface details
#include <google/vcdecoder.h>  // Read this file for interface details
#include <google/output_string.h>  // Read this file for interface details

#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>


using namespace std;

int main(){

	// Load dictionary into memory
	ifstream file("files/ex0.json");
	string str((istreambuf_iterator<char>(file)),
							istreambuf_iterator<char>());

	const char* s1 = str.c_str();
	size_t size_str = str.size();

	// for( unsigned int a = 0; a < size_str; a = a + 1 )
	// {
	// 	cout << s1[a];
	// }


	/*
	// Create a HashedDictionary object using the dictionary address and length

	open_vcdiff::HashedDictionary dictionary(s1, size_str);
	dictionary.Init();

	// Create a VCDiffStreamingEncoder object 

	open_vcdiff::VCDiffStreamingEncoder streamEncoder(&dictionary, open_vcdiff::VCD_STANDARD_FORMAT, false);

	// Create a string object in which to store the delta encoding and start encoding
	string delta;
	// open_vcdiff::OutputString<string> delta(&d);

	streamEncoder.StartEncoding(&delta);

	// Read data

	ifstream file2("files/ex1.json");
	string str2((istreambuf_iterator<char>(file2)),
							istreambuf_iterator<char>());
	const char* s2 = str2.c_str();
	size_t size_str2 = str2.size();

	// Encode data

	streamEncoder.EncodeChunk(s2, size_str2, &delta);

	streamEncoder.FinishEncoding(&delta);

	cout << delta << endl;
	*/


  ifstream file2("files/ex1.json");
	string str2((istreambuf_iterator<char>(file2)),
							istreambuf_iterator<char>());
	const char* s2 = str2.c_str();
	size_t size_str2 = str2.size();

  string dictionary = str;
	string target = str2;
	string delta;

	open_vcdiff::VCDiffEncoder encoder(dictionary.data(), dictionary.size());

	encoder.SetFormatFlags(open_vcdiff::VCD_FORMAT_INTERLEAVED);

	encoder.Encode(target.data(), target.size(), &delta);
  
  cout << "delta: " << endl;
  cout << delta << endl;
  
  string output;

  open_vcdiff::VCDiffDecoder decoder;
  decoder.Decode(dictionary.data(), dictionary.size(), delta, &output);

  cout << endl << "output: " << endl;
  cout << output << endl;


	return 0;
}

// int size_region = sizeof(str)/sizeof(str[0]);
	// cout << size_region << endl;

	// for( unsigned int a = 0; a < size_region; ++a )
	// {
	// 	cout << region[a] << endl;
	// }



	// int fd = open("files/ex1.json", O_RDONLY);
	// size_t pagesize = getpagesize();
	// char * region = static_cast<char*> (mmap(
	// 	(void*) (pagesize * (1 << 20)), pagesize,
	// 	PROT_READ, MAP_FILE|MAP_PRIVATE,
	// 	fd, 0
	// ));
	// fwrite(region, 1, pagesize, stdout);
	// int unmap_result = munmap(region, pagesize);
	// close(fd);

	// int size_region = sizeof(region)/sizeof(region[0]);



	// string line;
	// ifstream myfile ("files/ex1.json");
	// if (myfile.is_open())
	// {
	// 	while ( getline (myfile,line) )
	// 	{
	// 	cout << line << '\n';
	// 	}
	// 	myfile.close();
	// }