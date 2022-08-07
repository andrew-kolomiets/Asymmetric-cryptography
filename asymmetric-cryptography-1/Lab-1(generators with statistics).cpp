//******************************************************************

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

#include <NTL/ZZ.h>

//******************************************************************

using namespace std;
using namespace NTL;

//******************************************************************

typedef int typei;
typedef long long  int lltypei;
typedef unsigned long int ultypei;

//******************************************************************

template <typename different_type_first, typename different_type_second> //okey

void array_null(different_type_first* array, different_type_second size)//okey
{
	for (ultypei i = 0; i < size; i++)
	{
		array[i] = 0;
	}
}


template <typename different_type_first, typename different_type_second> //okey

void matrix_null(different_type_first** matrix, different_type_second size)//okey
{
	for (ultypei i = 0; i < size; i++)
	{
		for (ultypei j = 0; j < size; j++)
		{
			matrix[i][j] = 0;
		}
	}
}


template <typename different_type_first, typename different_type_second> //okey

void output_array_number_bit_representation(different_type_first* array, different_type_second size)//okey
{

	for (ultypei i = 0; i < size; i++)
	{
		cout << array[i];
	}

	cout << endl;
}

//******************************************************************

void bild_in_generator(ultypei* array, ultypei size) //okey
{


	array_null(array, size);

	for (ultypei i = 0; i < size; i++)
	{
		array[i] = rand()%2;
	}

	cout << endl << "-bild_in generation:" << endl;

	output_array_number_bit_representation(array, size);

}


void lehmer_generation_low_byte(lltypei* array_decimal, lltypei* array_binary, lltypei size_decimal, lltypei size_binary)//okey
{

	for (lltypei i =0;i<size_decimal;i++)
	{
		lltypei* byte = new lltypei[8];
		array_null(byte, 8);


		for (lltypei length =7; length >= 0; length--)
		{
			lltypei temp = array_decimal[i] >> length;

			if (temp & 1)
				byte[length] = 1;
			else
				byte[length] = 0;
		}

		lltypei temp = 8*i;

		for (lltypei j=0;j<8;j++)
		{
			array_binary[temp+j] = byte[j];
		}
		
		delete[] byte;
	}
}

void lehmer_generation_low_byte_modify(lltypei* array_decimal, lltypei* array_binary, lltypei size_decimal, lltypei size_binary)//okey
{

	for (lltypei i = 0; i < size_decimal; i++)
	{
		lltypei* byte = new lltypei[8];
		array_null(byte, 8);


		for (lltypei length = 0; length <8; length++)
		{
			lltypei temp = array_decimal[i] >> 7-length;

			if (temp & 1)
				byte[7 - length] = 1;
			else
				byte[7 - length] = 0;
		}

		lltypei temp = 8 * i;

		for (lltypei j = 0; j < 8; j++)
		{
			array_binary[temp + j] = byte[j];
		}

		delete[] byte;
	}
}

void lehmer_low_generator(lltypei* array_binary, lltypei a, lltypei c, lltypei  m, lltypei size)//okey
{

	lltypei* array_decimal = new lltypei[size/8];

	array_null(array_binary, size);
	array_null(array_decimal, size/8);

		while (array_decimal[0] == 0)
		{
			array_decimal[0] = rand();
		}

		for (lltypei i = 1; i < (size/8); i++)
		{
			array_decimal[i] = (((a%m) *( array_decimal[i-1]%m))%m + c) % m;
		}

		lehmer_generation_low_byte_modify(array_decimal, array_binary,size/8,size);

	output_array_number_bit_representation(array_binary, size);
	
	delete[] array_decimal;

}


void lehmer_generation_high_byte(lltypei* array_decimal, lltypei* array_binary, lltypei size_decimal, lltypei size_binary)//okey
{

	for (lltypei i = 0; i < size_decimal; i++)
	{
		lltypei* byte = new lltypei[8];	array_null(byte, 8);

		lltypei size_type = sizeof(lltypei);
		
		lltypei trige = 0;

		for (lltypei length = size_type; trige<8; length--)
		{
			lltypei temp = array_decimal[i] >> length;

			if (temp & 1)
				byte[length] = 1;
			else
				byte[length] = 0;

			trige++;
		}

		lltypei temp = 8 * i;

		for (lltypei j = 0; j < 8; j++)
		{
			array_binary[temp + j] = byte[j];
		}

		delete[] byte;
	}
}

void lehmer_generation_high_byte_modify(lltypei* array_decimal, lltypei* array_binary, lltypei size_decimal, lltypei size_binary)//okey
{

	for (lltypei i = 0; i < size_decimal; i++)
	{
		lltypei* byte = new lltypei[8];	array_null(byte, 8);

		lltypei mask = (pow(2,32) - 1) && array_decimal[i];
		
		for (lltypei bit=24,position_bite=0; bit <32; bit++, position_bite++)
		{
			lltypei temp = array_decimal[i] >> bit;

			if (temp & 1)
				byte[position_bite] = 1;
			else
				byte[position_bite] = 0;

		}

		lltypei temp = 8 * i;

		for (lltypei j = 0; j < 8; j++)
		{
			array_binary[temp + j] = byte[j];
		}

		delete[] byte;
	}
}

void lehmer_high_generator(lltypei* array_binary, lltypei a, lltypei c, lltypei  m, lltypei size)//okey
{
	lltypei* array_decimal = new lltypei[size/8];

	array_null(array_binary, size);
	array_null(array_decimal, size/8);

		while (array_decimal[0]==0)
		{
			array_decimal[0] = rand();
		}

		for (lltypei i = 1; i < (size / 8) - 1; i++)
		{
			array_decimal[i] = (((a % m) * (array_decimal[i - 1] % m)) % m + c) % m;
		}

		lehmer_generation_high_byte_modify(array_decimal, array_binary, size / 8, size);

	output_array_number_bit_representation(array_binary, size);

	delete[] array_decimal;

}



void l_20_generator(ultypei* array, ultypei size)//okey
{
	array_null(array, size);

	ultypei temp = 0;

	while (temp==0)
	{
		
		for (ultypei i = 0; i < 20; i++)
		{
			array[i] = rand() % 2;
			temp = temp + array[i];
		}
	}

	for (ultypei i = 20; i < size; i++)
	{
		array[i] = array[i-3] xor array[i-5] xor array[i-9] xor array[i-20];
	}

	cout << endl << "-l_20 generation:" << endl;

	output_array_number_bit_representation(array, size);
}


void l_89_generator(ultypei* array, ultypei size)//okey
{

	array_null(array, size);

	ultypei temp = 0;

	while (temp == 0)
	{
		for (ultypei i = 0; i < 89; i++)
		{
			array[i] = rand() % 2;
			temp = temp + array[i];
		}
	}

	for (ultypei i = 89; i < size; i++)
	{
		array[i] = array[i-38] xor array[i-89];
	}

	cout << endl << "-l_89 generation:" << endl;

	output_array_number_bit_representation(array, size);
}


ultypei* l_11(ultypei* array, ultypei size)//okey
{
	array_null(array,size);

	for (ultypei i = 0; i < 11; i++)
	{
		array[i] = rand()%2;
	}
	for (ultypei i = 0; i < size - 11; i++)
	{
		array[i + 11] = array[i] xor array[i + 2];
	}

	cout << endl << "-l_11 generation:" << endl;

	output_array_number_bit_representation(array, size);

	return array;
}

ultypei* l_9(ultypei* array, ultypei size)//okey
{
	array_null(array, size);

	for (ultypei i = 0; i < 9; i++)
	{
		array[i] = rand() % 2;
	}
	for (ultypei i = 0; i < size - 9; i++)
	{
		array[i + 9] = array[i] xor array[i + 1] xor array[i + 3] xor array[i + 4];
	}

	cout << endl << "-l_9 generation:" << endl;

	output_array_number_bit_representation(array,size);

	return array;
}

ultypei* l_10(ultypei* array, ultypei size)//okey
{
	array_null(array,size);

	for (ultypei i = 0; i < 10; i++)
	{
		array[i] = rand() % 2;
	}
	for (ultypei i = 0; i < size - 10; i++)
	{
		array[i + 10] = array[i] xor array[i + 3];
	}

	cout << endl << "-l_10 generation:" << endl;

	output_array_number_bit_representation(array,size);

	return array;
}

void geffe_generator(ultypei* array, ultypei size)//okey
{
	array_null(array, size);

	ultypei* array_x = new ultypei[size];
	ultypei* array_y = new ultypei[size];
	ultypei* array_s = new ultypei[size];


	array_x=l_11(array_x, size);
	array_y=l_9(array_y, size);
	array_s=l_10(array_s, size);

	for (ultypei i = 0; i < size; i++)
	{
		array[i] = array_s[i]* array_x[i] xor ((1+array_s[i])%2)* array_y[i];
	}

	cout << endl << "-geffe generation:" << endl;

	output_array_number_bit_representation(array, size);

	delete[] array_s;
	delete[] array_y;
	delete[] array_x;
}


void library_generator(string text, ultypei* array_converting_binary, ultypei array_size)//okey
{

	array_null(array_converting_binary, array_size);

	for (ultypei i = 0; i < text.length(); i++)
	{
		char temp = (char)text[i];

		ultypei* symbols = new ultypei[8];

		for (lltypei j = 7; j >= 0; --j)
		{
			symbols[j] = temp % 2;
			temp = temp / 2;
		}


		ultypei index_save = 8 * i;

		for (ultypei a = 0; a < 8; a++)
		{
			array_converting_binary[index_save + a] = symbols[a];
		}

		delete[] symbols;
	}

	cout << endl << "-library generation:" << endl;

	output_array_number_bit_representation(array_converting_binary, array_size);

}


void wolfram_generator(ultypei* array, ultypei size)//okey
{

	array_null(array, size);

	ultypei first_temp, second_temp;

	do
	{
		first_temp = rand();
	} while (first_temp == 0);


	for (ultypei i = 0; i < size; i++)
	{
		array[i] = first_temp % 2;
		second_temp = (first_temp << 1 | first_temp >> 31) xor (first_temp | (first_temp << 31 | first_temp >> 1));
		first_temp = second_temp;
	}

	cout << endl << "-wolfram generation:" << endl;

	output_array_number_bit_representation(array, size);
}


void blume_mikali_bm_generator(ultypei* array, ultypei size, ZZ low, ZZ module)//okey
{
	array_null(array, size);


	ZZ start_t = RandomBnd(module) % module;


	for (ultypei i = 0; i < size; i++)
	{
		if (start_t < ((module - 1) >>1))
		{
			array[i] =1;
		}
		else /* if (start_t >= ((module - 1) >> 1))*/
		{
			array[i] = 0;
		}


		start_t = PowerMod(low, start_t, module);

	}

	output_array_number_bit_representation(array, size);
}


void bm_bytes_generator(ultypei* array, ultypei size, ZZ low, ZZ module)//okey
{
	array_null(array, size);

	ZZ temp = RandomBnd(module);

	for (ultypei i = 0; i < size / 8; i++)
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
		
		
		ultypei type_k = conv<int>(k);

		ultypei index_save = 8 * i;

		for (lltypei j = 7; j >= 0; j--)
		{
			array[index_save + j] = type_k % 2;
			type_k = type_k / 2;
		}

		temp = PowerMod(low, temp, module);

	}

	output_array_number_bit_representation(array, size);
}


void bbs_generator(ultypei* array, ultypei size,ZZ module)//okey
{

	array_null(array, size);

		ZZ temp = RandomBnd(module);
		
		for (ultypei i = 0; i < size; i++)
		{
			temp = (temp * temp)% module;
			array[i]=conv<int>(temp % 2);
		}
	

	output_array_number_bit_representation(array, size);
}


void bbs_bytes_generator(ultypei* binary, ultypei size, ZZ module)//okey
{

	array_null(binary, size);

		ZZ temp = RandomBnd(module);

		for (ultypei i = 0; i < size/8; i++)
		{
			temp = (temp * temp) % module;
			ZZ middle = temp % conv<ZZ>(256);
			ultypei var = conv<int>(middle);

			ultypei index_save = 8 * i;

			for (lltypei j = 7; j >= 0; j--)
			{
				binary[index_save + j] = var % 2;
				var = var / 2;
			}

		}


	output_array_number_bit_representation(binary, size);
}

//******************************************************************

template <typename any_type>

void freaquency_equinoimovirnost_symbols(any_type * bit_array, ultypei size_bit_array, ultypei * frequency, ultypei  size_frequency_array)//okey
{
	
	for (ultypei i=0;i<size_bit_array/8;i++)
	{
		typei* byte = new typei[8];

		for (ultypei j = 0; j < 8; j++)
		{
			byte[j] = bit_array[8*i+j];
		}

		ultypei decimal_representation = 0;

		for (typei k=0;k<8;k++)
		{
			decimal_representation += byte[k] * pow(2,7-k);
		}

		(frequency[decimal_representation])++;

		delete[] byte;
	}
	
}


template <typename any_type>

void  criterian_check_equinoimovirnost_symbols(any_type * bit_array, ultypei  size_bit_array, long double statistic_constant)//okey
{
	ultypei * frequency = new ultypei [256];	array_null(frequency, 256);

	freaquency_equinoimovirnost_symbols(bit_array, size_bit_array, frequency, 256.0);

	long double statistic = 0;			 long double critical_statistic = 0;


	long  double expect = (long double)(size_bit_array / (8*256));

	for (ultypei i=0;i<256;i++)
	{
		statistic += pow((long double)frequency[i] - expect, 2) / expect;
	}


	critical_statistic = sqrt(2 * 255) * statistic_constant + 255;

	if (statistic<=critical_statistic)
	{
		cout << endl << "\t \t hypothesis H_0 does not contradict experimental data: " << endl;
			
			cout << endl << "\t \t \tstatistic experimental: " << statistic << endl;
			cout << endl << "\t \t \tstatistic critical: " << critical_statistic << endl;
			
	}
	else
	{
		cout << endl << "\t \t hypothesis H_0 does contradict experimental data:" << endl;

			cout << endl << "\t \t \tstatistic experimental: " << statistic << endl;
			cout << endl << "\t \t \tstatistic critical: " << critical_statistic << endl;
	}


	delete[] frequency;
}


template <typename any_type>

void frequency_independence_symbols(any_type* bit_array, ultypei size_bit_array, ultypei** frequency, ultypei size_frequency_array, ultypei* first_frequency, ultypei size_first_frequency_array, ultypei* second_frequency, ultypei size_second_frequency_array)//okey
{

		 for (ultypei i = 0; i < size_bit_array/16; i++)
		 {
			 ultypei* first_byte = new ultypei[8];				ultypei* second_byte = new ultypei[8];

			 for (ultypei j = 0; j <8; j++)
			 {
				 first_byte[j] = bit_array[8 * i + j];		second_byte[j] = bit_array[8 * i + 8 + j];
			 }

			 ultypei first_decimal_representation = 0;			ultypei second_decimal_representation = 0;

			 
			 for (typei temp = 0; temp < 8; temp++)
			 {
				 first_decimal_representation += first_byte[temp] * pow(2, 7 - temp);	
				 second_decimal_representation += second_byte[temp] * pow(2, 7 - temp);
			 }

						 (frequency[first_decimal_representation][second_decimal_representation])++;

			 (first_frequency[first_decimal_representation])++;  (second_frequency[second_decimal_representation])++;

		
			 delete[] second_byte;		delete[] first_byte;
		 }


}


template <typename any_type>

void  criterian_check_independence_symbols(any_type* bit_array, ultypei size_bit_array, double statistic_constant)//okey
{
	ultypei* first_frequency = new ultypei[256];		array_null(first_frequency, 256);

	ultypei* second_frequency = new ultypei[256];		array_null(second_frequency, 256);

	ultypei** frequency = new ultypei * [256];

	for (ultypei i = 0; i < 256; i++)
	{
		frequency[i] = new ultypei[256];
	}

	matrix_null(frequency, 256);

	frequency_independence_symbols(bit_array, size_bit_array, frequency, 256, first_frequency, 256, second_frequency, 256);


	long double statistic = 0;			long double critical_statistic = 0;		


	for (ultypei i = 0; i < 256; i++)
	{
		for (ultypei j= 0; j < 256; j++)
		{
			if (!(first_frequency[i]==0|| second_frequency[j]==0))
			{
				statistic += (long double)(pow(frequency[i][j], 2) / (long double)(first_frequency[i] * second_frequency[j]));
			}
			else
			{
				continue;
			}
		}
	}

	ultypei temp = (size_bit_array / 16);

	statistic = (long double)temp * statistic - (long double)temp;

	critical_statistic = sqrt(2 * pow(255,2)) * statistic_constant +pow(255,2);


	if (statistic <= critical_statistic)
	{
		cout << endl << "\t \t hypothesis H_0 does not contradict experimental data: " << endl;

			cout << endl << "\t \t \tstatistic experimental: " << statistic << endl;
			cout << endl << "\t \t \tstatistic critical: " << critical_statistic << endl;
	}
	else
	{
		cout << endl << "\t \t hypothesis H_0 does contradict experimental data:" << endl;

			cout << endl << "\t \t \tstatistic experimental: " << statistic << endl;
			cout << endl << "\t \t \tstatistic critical: " << critical_statistic << endl;
	}



	for (ultypei i=0;i<256;i++)
	{
		delete frequency[i];
	}

						delete[] frequency;

	delete[] second_frequency;		delete[] first_frequency;

	
}


template <typename any_type>

void frequency_uniformity_of_a_binary_sequence(any_type* bit_array, ultypei size_bit_array, ultypei** frequency, ultypei size_frequency_array,ultypei segments)//okey
{
	for (ultypei i = 0; i < segments; i++)
	{
		for (ultypei j=0;j< size_bit_array/(8*segments)-8;j++)
		{
			ultypei* byte = new ultypei[8];


			for (ultypei k = 0; k < 8; k++)
			{
				byte[k] = bit_array[(size_bit_array /segments)*i+8*j+k];
			}


			ultypei decimal_representation = 0;

			for (typei temp = 0; temp < 8; temp++)
			{
				decimal_representation += byte[temp] * pow(2, 7 - temp);
			}

			(frequency[i][decimal_representation])++;


			delete[] byte;
		}
	}
}


template <typename any_type>

void  criterian_for_checking_the_uniformity_of_a_binary_sequence(any_type* bit_array, ultypei size_bit_array,ultypei segments, long double statistic_constant)//okey
{
	ultypei** frequency = new ultypei * [segments];


	for (ultypei i = 0; i < segments; i++)	
	{
		frequency[i] = new ultypei[256];
	}

	for (ultypei i = 0; i < segments; i++)
	{
		for (ultypei j = 0; j < 256; j++)
		{
			frequency[i][j] = 0;
		}
	}


	long double statistic = 0;			long double critical_statistic = 0;

	frequency_uniformity_of_a_binary_sequence(bit_array, size_bit_array, frequency,  256, segments);

	for (ultypei j = 0; j < segments; j++)
	{
		for (ultypei i = 0; i < 256; i++)
		{
			ultypei sum_first = 0;		ultypei sum_second = 0;

			for (ultypei t = 0; t < segments; t++)
			{
				sum_first += frequency[t][i];
			}

			for (ultypei t = 0; t < 256; t++)
			{
				sum_second += frequency[j][t];
			}

			if (sum_first!=0|| sum_second!=0)
			{
				statistic += (pow(frequency[j][i], 2) / (long double)(sum_first * sum_second));
			}
			
		}
	}


	ultypei temp = (size_bit_array / 8);

	statistic = (long double)temp * statistic - (long double)temp;

	critical_statistic = sqrt(2 * 255*(segments-1)) * statistic_constant+255*(segments-1);


	if (statistic <= critical_statistic)
	{
		cout << endl << "\t \t hypothesis H_0 does not contradict experimental data: " << endl;

			cout << endl << "\t \t \tstatistic experimental: " << statistic << endl;
			cout << endl << "\t \t \tstatistic critical: " << critical_statistic << endl;
	}
	else
	{
		cout << endl << "\t \t hypothesis H_0 does contradict experimental data:" << endl;

			cout << endl << "\t \t \tstatistic experimental: " << statistic << endl;
			cout << endl << "\t \t \tstatistic critical: " << critical_statistic << endl;
	}


	for (ultypei i = 0; i < segments; i++)
	{
		delete frequency[i];
	}


	delete[] frequency;

}

//******************************************************************

void total_commander()//okey
{
	cout << endl << "\n" << endl;

	cout << endl << "All possible random generation of number sequences:" << endl;

		cout << endl << "[0]\t -exit with total commander and program;" << endl;
		cout << endl << "[1]\t -bild_in_generator;" << endl;						//unsigned long int or int, but int is not good type in this programs
		cout << endl << "[2]\t -lehmer_low_generator;" << endl;						//long long  int
		cout << endl << "[3]\t -lehmer_high_generator;" << endl;					//long long  int
		cout << endl << "[4]\t -l_20_generator;" << endl;							//unsigned long int
		cout << endl << "[5]\t -l_89_generator;" << endl;							//unsigned long int
		cout << endl << "[6]\t -geffe_generator;" << endl;							//unsigned long int
		cout << endl << "[7]\t -library_generator;" << endl;						//unsigned long int
		cout << endl << "[8]\t -wolfram_generator;" << endl;						//unsigned long int
		cout << endl << "[9]\t -blume_mikali_bm_generator;" << endl;				//unsigned long int (no data about this, need to do experiment on OS Linux, Windows is very slow)
		cout << endl << "[10]\t -bm_bytes_generator;" << endl;						//unsigned long int (no data about this, need to do experiment on OS Linux, Windows is very slow)
		cout << endl << "[11]\t -bbs_generator;" << endl;							//unsigned long int
		cout << endl << "[12]\t -bbs_bytes_generator;" << endl;						//unsigned long int mix with long long int
	

	cout << endl << "\n" << endl;

	cout << endl << "All possible statistics, which we use:" << endl;

		cout << endl << "\t -criterian_check_equinoimovirnost_symbols;" << endl;
		cout << endl << "\t -criterian_check_independence_symbols;" << endl;
		cout << endl << "\t -criterian_for_checking_the_uniformity_of_a_binary_sequence;" << endl;


	cout << endl << "\n" << endl;

	cout << endl << "Enter only number of generator in task bar, which we wount to choose." << endl;
}

//******************************************************************

int main()//okey
{
	total_commander();

	ultypei answer=0;

	do
	{
		cout << endl << "Input generator index:" << endl;		cin >> answer;

		long double start_time=clock();

		switch (answer)
		{

			case 0://okey
			{
				break;
			}
			case 1://okey
			{
				cout << endl << "-input size of generation number:" << endl;
				lltypei size;
				cin >> size;

				ultypei* array = new ultypei[size];
				
				bild_in_generator(array,size);

				{	//statistics  data

					{
						cout << endl << "-statistics tests for alpha:"<<0.1<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,1.28);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 1.28);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 1.28);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.05<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,1.64);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 1.64);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 1.64);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.01<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,2.31);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 2.31);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 2.31);
					}


				}

				delete[] array;

				break;
			}
			case 2://okey
			{
				cout << endl << "-input size of generation number:" << endl;
				lltypei size;
				cin >> size;

				
				lltypei* array = new lltypei[8*size];

				lehmer_low_generator(array, 65537,119,4294967296,8 * size);

				{	//statistics  data

					{
						cout << endl << "-statistics tests for alpha:"<<0.1<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, 8 * size,1.28);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array,8 * size, 1.28);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array,8 * size, 16, 1.28);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.05<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array,8 * size,1.64);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array,8 * size, 1.64);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array,8 * size, 16, 1.64);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.01<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array,8 * size,2.31);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array,8 * size, 2.31);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array,8 * size, 16, 2.31);
					}


				}
				delete[] array;

				break;
			}
			case 3://okey
			{
				cout << endl << "-input size of generation number:" << endl;
				lltypei size;
				cin >> size;

				lltypei* array = new lltypei[8 * size];

				lehmer_high_generator(array, 65537, 119, 4294967296, 8 * size);

				{	//statistics  data

					{
						cout << endl << "-statistics tests for alpha:"<<0.1<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, 8 * size,1.28);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array,8 * size, 1.28);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array,8 * size, 16, 1.28);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.05<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, 8 * size,1.64);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array,8 * size, 1.64);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, 8 * size, 16, 1.64);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.01<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, 8 * size,2.31);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, 8 * size, 2.31);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, 8 * size, 16, 2.31);
					}


				}

				delete[] array;


				break;
			}
			case 4://okey
			{
				cout << endl << "-input size of generation number:" << endl;
				ultypei size;
				cin >> size;

				ultypei* array = new ultypei[size];

				l_20_generator(array,size);
				
				{	//statistics  data

					{
						cout << endl << "-statistics tests for alpha:"<<0.1<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,1.28);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 1.28);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 1.28);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.05<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,1.64);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 1.64);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 1.64);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.01<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,2.31);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 2.31);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 2.31);
					}


				}

				delete[] array;

				break;
			}
			case 5://okey
			{
				cout << endl << "-input size of generation number:" << endl;
				ultypei size;
				cin >> size;

				ultypei* array = new ultypei[size];
			
				l_89_generator(array,size);

				{	//statistics  data

					{
						cout << endl << "-statistics tests for alpha:"<<0.1<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,1.28);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 1.28);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 1.28);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.05<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,1.64);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 1.64);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 1.64);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.01<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,2.31);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 2.31);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 2.31);
					}


				}

				delete[] array;

				break;
			}
			case 6://okey
			{
				cout << endl << "-input size of generation number:" << endl;
				ultypei size;
				cin >> size;

				ultypei* array = new ultypei[size];
			
				geffe_generator(array, size);

				{	//statistics  data

					{
						cout << endl << "-statistics tests for alpha:"<<0.1<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,1.28);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 1.28);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 1.28);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.05<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,1.64);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 1.64);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 1.64);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.01<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,2.31);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 2.31);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 2.31);
					}


				}

				delete[] array;

				break;
			}
			case 7://okey
			{
				cout << endl << "-input text for generation number:" << endl;
				string text;
				cin >> text;

				ultypei* array = new ultypei[8*text.length()];

				library_generator(text,array, 8*text.length());
				
				{	//statistics  data

					{
						cout << endl << "-statistics tests for alpha:"<<0.1<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array,8*text.length(),1.28);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, 8*text.length(), 1.28);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, 8*text.length(), 16, 1.28);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.05<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, 8*text.length(),1.64);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, 8*text.length(), 1.64);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, 8*text.length(), 16, 1.64);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.01<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, 8*text.length(),2.31);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, 8*text.length(), 2.31);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array,8*text.length(), 16, 2.31);
					}


				}

				delete[] array;

				break;
			}
			case 8://okey
			{
				cout << endl << "-input size of generation number:" << endl;
				ultypei size;
				cin >> size;

				ultypei* array = new ultypei[size];

				wolfram_generator(array, size);

				{	//statistics  data

					{
						cout << endl << "-statistics tests for alpha:"<<0.1<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,1.28);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 1.28);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 1.28);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.05<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,1.64);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 1.64);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 1.64);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.01<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,2.31);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 2.31);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 2.31);
					}


				}

				delete[] array;

				break;
			}
			case 9://okey
			{

				cout << endl << "-input size of generation number:" << endl;
				ultypei size;
				cin >> size;

				ultypei* array = new ultypei[size];

				blume_mikali_bm_generator(array, size, conv<ZZ>("41402113656871763270073938229168765778879686959780184368336806110280536326998"), conv<ZZ>("93466510612868436543809057926265637055082661966786875228460721852868821292003"));

				{	//statistics  data

					{
						cout << endl << "-statistics tests for alpha:"<<0.1<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,1.28);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 1.28);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 1.28);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.05<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,1.64);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 1.64);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 1.64);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.01<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,2.31);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 2.31);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 2.31);
					}


				}

				delete[] array;
			

				break;
			}
			case 10://okey
			{
				
				cout << endl << "-input size of generation number:" << endl;
				ultypei size;
				cin >> size;

				ultypei* array = new ultypei[8*size];

				bm_bytes_generator(array, 8*size, conv<ZZ>("41402113656871763270073938229168765778879686959780184368336806110280536326998"), conv<ZZ>("93466510612868436543809057926265637055082661966786875228460721852868821292003"));

				{	//statistics  data

					{
						cout << endl << "-statistics tests for alpha:"<<0.1<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, 8*size,1.28);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, 8*size, 1.28);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, 8*size, 16, 1.28);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.05<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, 8*size,1.64);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array,8*size, 1.64);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, 8*size, 16, 1.64);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.01<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array,8*size,2.31);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array,8*size, 2.31);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array,8*size, 16, 2.31);
					}


				}

				delete[] array;

				break;
			}
			case 11://okey
			{
			
				cout << endl << "-input size of generation number:" << endl; ultypei size; cin >> size;

				ultypei* array = new ultypei[size];

				bbs_generator(array, size, conv<ZZ>("284100283511244958272321698211826428679")* conv<ZZ>("22582480853028265529707582510375286184991"));
				
				{	//statistics  data

					{
						cout << endl << "-statistics tests for alpha:"<<0.1<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,1.28);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 1.28);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 1.28);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.05<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,1.64);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 1.64);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 1.64);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.01<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, size,2.31);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, size, 2.31);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, size, 16, 2.31);
					}


				}

				delete[] array;


				break;
			}
			case 12://okey
			{
				
				cout << endl << "-input size of generation number:" << endl; ultypei size; cin >> size;
			
				ultypei* array = new ultypei[8*size];

				bbs_bytes_generator(array, 8*size, conv<ZZ>("284100283511244958272321698211826428679")* conv<ZZ>("22582480853028265529707582510375286184991"));

				{	//statistics  data

					{
						cout << endl << "-statistics tests for alpha:"<<0.1<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, 8*size,1.28);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, 8*size, 1.28);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, 8*size, 16, 1.28);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.05<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, 8*size,1.64);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, 8*size, 1.64);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, 8*size, 16, 1.64);
					}

					{
						cout << endl << "-statistics tests for alpha:"<<0.01<< endl;


						cout << endl << "\t - criterian_check_equinoimovirnost_symbols:" << endl;

						criterian_check_equinoimovirnost_symbols(array, 8*size,2.31);


						cout << endl << "\t - criterian_check_independence_symbols:" << endl;

						criterian_check_independence_symbols(array, 8*size, 2.31);


						cout << endl << "\t - criterian_for_checking_the_uniformity_of_a_binary_sequence:" << endl;

						criterian_for_checking_the_uniformity_of_a_binary_sequence( array, 8*size, 16, 2.31);
					}


				}
				
				delete[] array;

				break;
			}
			default://okey
			{
				cout << endl << "Error." << endl;
			}

		}

		long double end_time=clock();

		long double time_work=0;

		time_work=(end_time-start_time)/(long double)CLOCKS_PER_SEC;

		cout<<endl<<"- time work program: "<<time_work<<" seconds"<<endl;
	} 
	while (answer != 0);

	return 0;
}

//******************************************************************

//additional code
//void convert_to_binary(ZZ number, vector<int>& binary_representation)
//{
//
//	for (int i = 0; number > 0; i++)
//	{
//		binary_representation.push_back(number % 2);		number = number / 2;
//	}
//
//}
//
//void convert_to_binary_modify(ZZ number, vector<int>& binary_representation)
//{
//
//	for (long long int i = 0; number > 0; i++)
//	{
//		binary_representation.push_back(conv<int>(conv<ZZ>(number) & conv<ZZ>(1)));  number = number >> 1;
//	}
//}
//
//
//ZZ Power_Mod(ZZ number, ZZ degree, ZZ module)
//{
//
//	vector<int> binary_representation;		convert_to_binary_modify(degree, binary_representation);		ZZ result = conv<ZZ>(1);
//
//
//	for (long long int i = (long long int)binary_representation.size() - 1; i >= 0; i--)
//	{
//		result =(result*result)%module;
//
//			if (binary_representation[i] == 1)
//			{
//				result = (result * number) % module;
//			}
//	}
//
//	return result;
//}
//typedef int typei;
//typedef long int ltypei;
//typedef unsigned int utypei;
//typedef long long int lltypei;
//typedef unsigned long int ultypei;
