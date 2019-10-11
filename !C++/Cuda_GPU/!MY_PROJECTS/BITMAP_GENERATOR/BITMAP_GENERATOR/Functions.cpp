#include "Functions.hpp"

void Functions::Read_BitMap(const char * filename)
{
	_STD fstream file;
	file.open(filename, std::ios_base::in | std::ios_base::binary);

	if (file.good() == false)
	{
		_STD cerr << "UNABLE TO OPEN THE FILE [CHECK THE NAME OR CORRECT FILE PATH]" << _STD endl;
		exit(0);
	}
	else
	{
		//uint16_t value{};
		char four_bytes_array[4]{};
		size_t size{};
		char value{};
		while (file.eof() == false)
		{
			//file.read(value, sizeof(uint16_t));
			file.read(&value, sizeof(char));
			printf("%c |", value);
			value = ' ';
			//four_bytes_array[size++] = value;
			/*_STD cout << sizeof(four_bytes_array);
			if (size % sizeof(four_bytes_array) == 0)
			{
				size = 0;
				if (four_bytes_array == "IEND")
				{
					printf("%s |", four_bytes_array);
					break;
				}
			}*/
			//_STD cin.get();
			//break;
		}
		

	}

	file.close();
}
