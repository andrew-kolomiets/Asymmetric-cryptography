//******************************************************************

#include <iostream>
#include <cmath>
#include <string>
#include <time.h>
#include <fstream>
#include <NTL/ZZ.h>

//******************************************************************

using namespace std;
using namespace NTL;

//******************************************************************

typedef  long long int type;

//******************************************************************

void array_null(type* array, type size)//okey
{
	for (type i = 0; i < size; i++)
	{
		array[i] = 0;
	}
}

void output_array_number_bit_representation(type* array, type size)//okey
{

	cout << endl << "-bit representation:" << endl;

	for (type i = 0; i < size; i++)
	{
		cout << array[i];
	}

	cout << endl;
}

//******************************************************************

void bild_in_generator(type* array, type size) //okey
{
	array_null(array, size);

	for (type i = 0; i < size; i++)
	{
		array[i] = rand()%2;
	}

	cout << endl << "-bild_in generation:" << endl;

	output_array_number_bit_representation(array, size);

}


void lehmer_generation_low_byte(type* array_decimal, type* array_binary, type size_decimal, type size_binary)//okey
{

	for (type i =0;i<size_decimal;i++)
	{
		type* byte = new type[8];	
		array_null(byte, 8);


		for (type length =7; length >= 0; length--)
		{
			type temp = array_decimal[i] >> length;

			if (temp & 1)
				byte[length] = 1;
			else
				byte[length] = 0;
		}

		type temp = 8*i;

		for (type j=0;j<8;j++)
		{
			array_binary[temp+j] = byte[j];
		}
		
		delete[] byte;
	}
}

void lehmer_low_generator(type* array_binary, type a, type c, type  m, type size)//okey
{
	type* array_decimal = new type[size/8];

	array_null(array_binary, size);
	array_null(array_decimal, size/8);

		while (array_decimal[0] == 0)
		{
			array_decimal[0] = (rand()+1) % m;
		}

		for (type i = 1; i < (size/8); i++)
		{
			array_decimal[i] = (((a%m) *( array_decimal[i-1]%m))%m + c) % m;
		}

		lehmer_generation_low_byte(array_decimal, array_binary,size/8,size);

	output_array_number_bit_representation(array_binary, size);
	
	delete[] array_decimal;

}


void lehmer_generation_high_byte(type* array_decimal, type* array_binary, type size_decimal, type size_binary)//okey
{

	for (type i = 0; i < size_decimal; i++)
	{
		type* byte = new type[8];	array_null(byte, 8);

		
		for (type length = 31; length >= 24; length--)
		{
			type temp = array_decimal[i] >> length;

			if (temp & 1)
				byte[length] = 1;
			else
				byte[length] = 0;
		}

		type temp = 8 * i;

		for (type j = 0; j < 8; j++)
		{
			array_binary[temp + j] = byte[j];
		}

		delete[] byte;
	}
}

void lehmer_high_generator(type* array_binary, type a, type c, type  m, type size)//okey
{
	type* array_decimal = new type[size / 8];

	array_null(array_binary, size);
	array_null(array_decimal, size/8);

		while (array_decimal[0] == 0)
		{
			array_decimal[0] = (abs(rand())+1) % m;
		}

		for (type i = 1; i < (size / 8) - 1; i++)
		{
			array_decimal[i] = (((a % m) * (array_decimal[i - 1] % m)) % m + c) % m;
		}

		lehmer_generation_high_byte(array_decimal, array_binary, size / 8, size);

	output_array_number_bit_representation(array_binary, size);

	delete[] array_decimal;

}


void l_20_generator(type* array, type size)//okey
{
	array_null(array, size);

	type temp = 0;

	while (temp==0)
	{
		
		for (type i = 0; i < 20; i++)
		{
			array[i] = rand() % 2;
			temp = temp + array[i];
		}
	}

	for (type i = 20; i < size; i++)
	{
		array[i] = array[i-3] xor array[i-5] xor array[i-9] xor array[i-20];
	}

	cout << endl << "-l_20 generation:" << endl;

	output_array_number_bit_representation(array, size);
}


void l_89_generator(type* array, type size)//okey
{
	array_null(array, size);

	type temp = 0;

	while (temp == 0)
	{
		for (type i = 0; i < 89; i++)
		{
			array[i] = rand() % 2;
			temp = temp + array[i];
		}
	}

	for (type i = 89; i < size; i++)
	{
		array[i] = array[i-38] xor array[i-89];
	}

	cout << endl << "-l_89 generation:" << endl;

	output_array_number_bit_representation(array, size);
}


type* l_11(type* array, type size)
{
	array_null(array,size);

	for (type i = 0; i < 11; i++)
	{
		array[i] = rand()%2;
	}
	for (type i = 0; i < size - 11; i++)
	{
		array[i + 11] = array[i] xor array[i + 2];
	}

	cout << endl << "-l_11 generation:" << endl;

	output_array_number_bit_representation(array, size);

	return array;
}

type* l_9(type* array, type size)
{
	array_null(array, size);

	for (type i = 0; i < 9; i++)
	{
		array[i] = rand() % 2;
	}
	for (type i = 0; i < size - 9; i++)
	{
		array[i + 9] = array[i] xor array[i + 1] xor array[i + 3] xor array[i + 4];
	}

	cout << endl << "-l_9 generation:" << endl;

	output_array_number_bit_representation(array,size);

	return array;
}

type* l_10(type* array, type size)
{
	array_null(array,size);

	for (type i = 0; i < 10; i++)
	{
		array[i] = rand() % 2;
	}
	for (type i = 0; i < size - 10; i++)
	{
		array[i + 10] = array[i] xor array[i + 3];
	}

	cout << endl << "-l_10 generation:" << endl;

	output_array_number_bit_representation(array,size);

	return array;
}

void geffe_generator(type* array, type size)//okey
{
	array_null(array, size);

	type* array_x = new type[size];
	type* array_y = new type[size];
	type* array_s = new type[size];


	array_x=l_11(array_x, size);
	array_y=l_9(array_y, size);
	array_s=l_10(array_s, size);

	for (type i = 0; i < size; i++)
	{
		array[i] = array_s[i]* array_x[i] xor ((1+array_s[i])%2)* array_y[i];
	}

	cout << endl << "-geffe generation:" << endl;

	output_array_number_bit_representation(array, size);

	delete[] array_s;
	delete[] array_y;
	delete[] array_x;
}


void library_generator(string text, type* array_converting_binary, type array_size)//okey
{

	array_null(array_converting_binary, array_size);

	for (type i = 0; i < text.length(); i++)
	{
		char temp = (char)text[i];

		type* symbols = new type[8];

		for (type j = 7; j >= 0; --j)
		{
			symbols[j] = temp % 2;
			temp = temp / 2;
		}


		type index_save = 8 * i;

		for (type a = 0; a < 8; a++)
		{
			array_converting_binary[index_save + a] = symbols[a];
		}

		delete[] symbols;
	}

	cout << endl << "-library generation:" << endl;

	output_array_number_bit_representation(array_converting_binary, array_size);

}


void wolfram_generator(type* array, type size)//okey
{
	array_null(array, size);

	type first_temp, second_temp;

	do
	{
		first_temp = rand();
	} while (first_temp == 0);


	for (type i = 0; i < size; i++)
	{
		array[i] = first_temp % 2;
		second_temp = (first_temp << 1 | first_temp >> 31) xor (first_temp | (first_temp << 31 | first_temp >> 1));
		first_temp = second_temp;
	}

	cout << endl << "-wolfram generation:" << endl;

	output_array_number_bit_representation(array, size);
}


void blume_mikali_bm_generator(type* array, type size, ZZ low, ZZ module)//okey
{
	array_null(array, size);


	ZZ start_t = RandomBnd(module) % module;


	for (type i = 0; i < size; i++)
	{
		if (start_t < (module - 1) / 2)
		{
			array[i] = 1;
		}
		else if (start_t >= (module - 1) / 2)
		{
			array[i] = 0;
		}

		start_t = PowerMod(low, start_t, module);

	}

	output_array_number_bit_representation(array, size);
}


void bm_bytes_generator(type* array, type size, ZZ low, ZZ module)//okey
{
	array_null(array, size);

	ZZ temp = RandomBnd(module);

	for (type i = 0; i < size / 8; i++)
	{
		ZZ k = (conv<ZZ>(256) * temp) / (module - 1);

		
		while (!((((k * (module - 1)) / 256) < temp) && (temp <= (((k + 1) * (module - 1)) / 256))))
		{
			while ((!(((k * (module - 1)) / 256) < temp)) && (temp <= (((k + 1) * (module - 1)) / 256)))
			{
				k--;
			}
			while ((((k * (module - 1)) / 256) < temp) && (!(temp <= (((k + 1) * (module - 1)) / 256))))
			{
				k++;
			}
		}
		
		
		type type_k = conv<int>(k);

		type index_save = 8 * i;

		for (type j = 7; j >= 0; j--)
		{
			array[index_save + j] = type_k % 2;
			type_k = type_k / 2;
		}

		temp = PowerMod(low, temp, module);

	}

	output_array_number_bit_representation(array, size);
}

void bbs_generator(type* array, type size,ZZ module)//okey
{
	array_null(array, size);

		ZZ temp = RandomBnd(module);
		
		for (type i = 0; i < size; i++)
		{
			temp = (temp * temp)% module;
			array[i]=conv<int>(temp % 2);
		}
	

	output_array_number_bit_representation(array, size);
}


void bbs_bytes_generator(type* binary, type size, ZZ module)//okey
{
	array_null(binary, size);

		ZZ temp = RandomBnd(module);

		for (type i = 0; i < size/8; i++)
		{
			temp = (temp * temp) % module;
			ZZ middle = temp % conv<ZZ>(256);
			type var = conv<int>(middle);

			type index_save = 8 * i;

			for (type j = 7; j >= 0; j--)
			{
				binary[index_save + j] = var % 2;
				var = var / 2;
			}

		}


	output_array_number_bit_representation(binary, size);
}


void total_commander()
{
	cout << endl << "All possible random generation of number sequences:" << endl;

		cout << endl << "[0]\t -exit with total commander and program;" << endl;
		cout << endl << "[1]\t -bild_in_generator;" << endl;
		cout << endl << "[2]\t -lehmer_low_generator;" << endl;
		cout << endl << "[3]\t -lehmer_high_generator;" << endl;
		cout << endl << "[4]\t -l_20_generator;" << endl;
		cout << endl << "[5]\t -l_89_generator;" << endl;
		cout << endl << "[6]\t -geffe_generator;" << endl;
		cout << endl << "[7]\t -library_generator;" << endl;
		cout << endl << "[8]\t -wolfram_generator;" << endl;
		cout << endl << "[9]\t -blume_mikali_bm_generator;" << endl;
		cout << endl << "[10]\t -bm_bytes_generator;" << endl;
		cout << endl << "[11]\t -bbs_generator;" << endl;
		cout << endl << "[12]\t -bbs_bytes_generator;" << endl;
	

	cout << endl << "Enter only number of generator in task bar, which we wount to choose." << endl;
}

//******************************************************************

int main()
{
	total_commander();

	type answer=NULL;

	do
	{
		cout << endl << "Input generator index:" << endl;
		cin >> answer;

		switch (answer)
		{
			
			case 0://okey
			{
				break;
			}
			case 1://okey
			{
				cout << endl << "-input size of generation number:" << endl;
				type size;
				cin >> size;

				type* array = new type[size];
				
				bild_in_generator(array,size);

				delete[] array;

				break;
			}
			case 2://okey
			{
				cout << endl << "-input size of generation number:" << endl;
				type size;
				cin >> size;

				
				type* array = new type[8*size];

				lehmer_low_generator(array, 65537,119,4294967296,8 * size);

				
				delete[] array;

				break;
			}
			case 3://okey
			{
				cout << endl << "-input size of generation number:" << endl;
				type size;
				cin >> size;

				type* array = new type[8 * size];

				lehmer_high_generator(array, 65537, 119, 4294967296, 8 * size);


				delete[] array;


				break;
			}
			case 4://okey
			{
				cout << endl << "-input size of generation number:" << endl;
				type size;
				cin >> size;

				type* array = new type[size];

				l_20_generator(array,size);

				delete[] array;

				break;
			}
			case 5://okey
			{
				cout << endl << "-input size of generation number:" << endl;
				type size;
				cin >> size;

				type* array = new type[size];
			
				l_89_generator(array,size);

				delete[] array;

				break;
			}
			case 6://okey
			{
				cout << endl << "-input size of generation number:" << endl;
				type size;
				cin >> size;

				type* array = new type[size];
			
				geffe_generator(array, size);

				delete[] array;

				break;
			}
			case 7://okey
			{
				cout << endl << "-input text for generation number:" << endl;
				string text;
				cin >> text;

				type* array = new type[8*text.length()];

				library_generator(text,array, 8*text.length());

				delete[] array;

				break;
			}
			case 8://okey
			{
				cout << endl << "-input size of generation number:" << endl;
				type size;
				cin >> size;

				type* array = new type[size];

				wolfram_generator(array, size);

				delete[] array;

				break;
			}
			case 9://okey
			{

				cout << endl << "-input size of generation number:" << endl;
				type size;
				cin >> size;

				type* array = new type[size];

				blume_mikali_bm_generator(array, size, conv<ZZ>("41402113656871763270073938229168765778879686959780184368336806110280536326998"), conv<ZZ>("93466510612868436543809057926265637055082661966786875228460721852868821292003"));

				delete[] array;
			

				break;
			}
			case 10://okey
			{
				
				cout << endl << "-input size of generation number:" << endl;
				type size;
				cin >> size;

				type* array = new type[8*size];

				bm_bytes_generator(array, 8*size, conv<ZZ>("41402113656871763270073938229168765778879686959780184368336806110280536326998"), conv<ZZ>("93466510612868436543809057926265637055082661966786875228460721852868821292003"));

				delete[] array;

				break;
			}
			case 11://okey
			{
			
				cout << endl << "-input size of generation number:" << endl; type size; cin >> size;

				type* array = new type[size];

				bbs_generator(array, size, conv<ZZ>("284100283511244958272321698211826428679")* conv<ZZ>("22582480853028265529707582510375286184991"));

				delete[] array;


				break;
			}
			case 12://okey
			{
				
				cout << endl << "-input size of generation number:" << endl; type size; cin >> size;
			
				type* array = new type[8*size];

				bbs_bytes_generator(array, 8*size, conv<ZZ>("284100283511244958272321698211826428679")* conv<ZZ>("22582480853028265529707582510375286184991"));

				delete[] array;

				break;
			}
			default://okey
			{
				cout << endl << "Error." << endl;
			}
		}
	} 
	while (answer != 0);


	return 0;
}

//******************************************************************
