//include part***********************************************************************

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

#define SIZE_KEY 256
#define PRECISION_OF_TEST_PRIME 100

//inverse element********************************************************************

ZZ mod(ZZ number, ZZ module)
{
	ZZ numb_by_module;

	if (number < 0)
	{
		if (number / module != 0)
		{
			numb_by_module = module - (abs(number) - module * (abs(number) / module));
		}
		else
		{
			numb_by_module = module - abs(number);
		}
	}
	else if (number / module != 0)
	{
		numb_by_module = number - module * (number / module);
	}
	else
	{
		numb_by_module = number;
	}

	return numb_by_module;
}

ZZ gcd(ZZ  first_number, ZZ second_number)
{
    ZZ  result;

    if(first_number<second_number)
    {
        ZZ shift=second_number;

        second_number=first_number;

        first_number=shift;
    }

    while (first_number % second_number != 0)
    {
        ZZ shift = second_number;

        second_number = first_number % second_number;

        first_number = shift;
    }

    if (first_number % second_number == 0)
    {
        result=second_number;
    }
    else
    {
        cout<<endl<<"Error function gcd."<<endl;
    }

    return result;
}

ZZ gcd_modify(ZZ first_num, ZZ second_num)
{
	ZZ gcd_value;

	ZZ r_1 = first_num;
	ZZ r_2 = second_num;

	if (first_num == conv<ZZ>(0))
	{
		if (second_num == conv<ZZ>(0))
		{
			return conv<ZZ>(0);
		}
		return second_num;
	}
	else if (second_num == conv<ZZ>(0))
	{
		if (first_num == conv<ZZ>(0))
		{
			return conv<ZZ>(0);
		}
		return first_num;
	}
	else
	{
		ZZ q_1;
		ZZ q_2 = conv<ZZ>(-1);

		while (q_2 != 0)
		{
			if (r_1 < r_2)
			{
				ZZ temp;
				temp = r_1;
				r_1 = r_2;
				r_2 = temp;
				gcd_modify(r_1, r_2);
			}
			else
			{
				q_1 = r_1 / r_2;
				q_2 = r_1 - (q_1 * r_2);
				r_1 = r_2;
				r_2 = q_2;
			}
		}
		gcd_value = r_1;

		return gcd_value;
	}
}

ZZ inverted_element(ZZ number, ZZ moduls)
{
	number = mod(number, moduls);

	if (gcd_modify(number, moduls) == conv<ZZ>(1))
	{
		ZZ b0 = moduls, t, q;
		ZZ x0 = conv<ZZ>(0), x1 = conv<ZZ>(1);
		if (moduls == conv<ZZ>(1)) return conv<ZZ>(1);
		while (number > conv<ZZ>(1)) {
			q = number / moduls;
			t = moduls, moduls = number % moduls, number = t;
			t = x0, x0 = x1 - q * x0, x1 = t;
		}
		if (x1 < conv<ZZ>(0)) x1 += b0;

		return x1;
	}
	if (gcd_modify(number, moduls) > conv<ZZ>(1))
	{ 
		return conv<ZZ>(-1); //code number if roots more or does`t exist
	}
}

//horner algorithm evelation to degree***********************************************


void convert_to_decimal_modify_for_conversation(vector<int> &binary_representation,ZZ &result)
{
    result=conv<ZZ>(0);

    for(int i=0;i<binary_representation.size();i++)
    {
        result+=conv<ZZ>(pow(2,binary_representation.size()-i-1))*conv<ZZ>(binary_representation[i]);
    }

}

void convert_to_binary_modify_for_conversation(ZZ number, vector<int> &binary_representation)
{

    for (unsigned long long int i = 0; number > 0; i++)
    {
        binary_representation.push_back(conv<int>(conv<ZZ>(number) & conv<ZZ>(1)));
        number = number >> 1;
    }

    reverse(binary_representation.begin(),binary_representation.end());
}

string hex_to_bin(char big_number)
{
	
	if (big_number== '0') { return "0000"; }
	if (big_number== '1') { return "0001"; }
	if (big_number== '2') { return "0010"; }
	if (big_number== '3') { return "0011"; }
	if (big_number== '4') { return "0100"; }
	if (big_number== '5') { return "0101"; }
	if (big_number== '6') { return "0110"; }
	if (big_number== '7') { return "0111"; }
	if (big_number== '8') { return "1000"; }
	if (big_number== '9') { return "1001"; }
	if (big_number== 'A') { return "1010"; }
	if (big_number== 'B') { return "1011"; }
	if (big_number== 'C') { return "1100"; }
	if (big_number== 'D') { return "1101"; }
	if (big_number== 'E') { return "1110"; }
	if (big_number== 'F') { return "1111"; }
	else
	{
		cout<<endl<<"Error in converting from hex to bin."<<endl;
	}


}

string bin_to_hex(string big_number)
{
	
	if (big_number == "0000") { return "0"; }
	if (big_number == "0001") { return "1"; }
	if (big_number == "0010") { return "2"; }
	if (big_number == "0011") { return "3"; }
	if (big_number == "0100") { return "4"; }
	if (big_number == "0101") { return "5"; }
	if (big_number == "0110") { return "6"; }
	if (big_number == "0111") { return "7"; }
	if (big_number == "1000") { return "8"; }
	if (big_number == "1001") { return "9"; }
	if (big_number == "1010") { return "A"; }
	if (big_number == "1011") { return "B"; }
	if (big_number == "1100") { return "C"; }
	if (big_number == "1101") { return "D"; }
	if (big_number == "1110") { return "E"; }
	if (big_number == "1111") { return "F"; }
	else
	{
		cout<<endl<<"Error in converting from bin to hex."<<endl;
	}
	
}

ZZ hex_to_dec(string hex)
{
   string binary="";

   for(int i=0;i<hex.length();i++)
   {
	   binary+= hex_to_bin(hex[i]);
   }
   
   binary.erase(remove(binary.begin(),binary.end(),' '),binary.end());


   vector<int> binary_representation(binary.length(),0);

	for(int i=0;i<binary.length();i++)
	{
		binary_representation[i]=(int)binary[i]-(int)'0';
	}
	
	ZZ result=conv<ZZ>(0);	convert_to_decimal_modify_for_conversation(binary_representation,result);

    return result;
}

string dec_to_hex(ZZ dec)
{
    vector<int> binary_representation;      convert_to_binary_modify_for_conversation(dec,binary_representation);    

	string binary="";

    for(int i=0;i<binary_representation.size();i++)
    {
       binary=binary+to_string(binary_representation[i]);
    }
		
	while(binary.size()%4!=0)
	{
		binary= "0"+binary;
	}

	binary.erase(remove(binary.begin(),binary.end(),' '),binary.end());


	string hex="";

	for(int i=0;i<binary.length();i=i+4)
	{
		string pattern=binary.substr(i,4);

		hex=hex+bin_to_hex(pattern);
	} 

	hex.erase(remove(hex.begin(),hex.end(),' '),hex.end());

    return hex;
}


void convert_to_decimal(vector<int> &binary_representation,ZZ &result)
{
    result=conv<ZZ>(0);

    for(int i=0;i<binary_representation.size();i++)
    {
        result+=conv<ZZ>(pow(2,binary_representation.size()-i-1))*conv<ZZ>(binary_representation[i]);
    }

}

void convert_to_binary_modify(ZZ number, vector<int> &binary_representation)
{

    for (unsigned long long int i = 0; number > 0; i++)
    {
        binary_representation.push_back(conv<int>(conv<ZZ>(number) & conv<ZZ>(1)));
        number = number >> 1;
    }
}

ZZ horner_method(ZZ number, ZZ degree, ZZ module)
{

    vector<int> binary_representation;

    convert_to_binary_modify(degree, binary_representation);

    ZZ result = conv<ZZ>(1);

    for (long long int i = (long long int)(binary_representation.size()) - 1; i >= 0; i--)
    {
        result = (result * result) % module;

        if (binary_representation[i] == 1)
        {
            result = (result * number) % module;
        }
    }

    return result;
}

//miller rabin primality test********************************************************

void l_20_generator(vector<int> & array)
{
	unsigned long long int temp = 0;

	while (temp==0)
	{
		for (unsigned long long int i = 0; i < 20; i++)
		{
			array[i]=(rand() % 2);
			temp = temp + array[i];
		}
	}

	for (long long int i = 20; i < array.size(); i++)
	{
		array[i]=(array[i-3] xor array[i-5] xor array[i-9] xor array[i-20]);
	}

}

void split_on_even_and_prime_parts(ZZ number, ZZ &prime_part, ZZ &degree_of_two)
{

    ZZ temp = number;  

    prime_part = conv<ZZ>(0);  

    degree_of_two = conv<ZZ>(0);
   
    while (!((temp & conv<ZZ>(1)) == conv<ZZ>(1)))
    {
        temp = temp >> 1;
        degree_of_two++;
    }

    prime_part = temp;
}

bool miller_rabin_primality_test_simple(ZZ number)
{
    
    vector<ZZ> simple_digits={conv<ZZ>(2),conv<ZZ>(3),conv<ZZ>(5),conv<ZZ>(7)};

    for(int i=0;i<simple_digits.size();i++)
    {
        if(number%simple_digits[i]==conv<ZZ>(0))
        {
            return false;
        }
    }

    ZZ degree_of_two=conv<ZZ>(0);     ZZ prime_part=conv<ZZ>(0);    ZZ test=number-conv<ZZ>(1);
   
    split_on_even_and_prime_parts(test, prime_part, degree_of_two);

    vector<int> choosen_number(256,0);   
    
    l_20_generator(choosen_number);

    ZZ result=conv<ZZ>(0);

    convert_to_decimal(choosen_number,result);

    if(gcd(result,number)>1)
    {
        return false;
    }
    
    ZZ temp=horner_method(result,prime_part,number);

    if(temp==1||temp==number-conv<ZZ>(1))
    {
        return true;
    }


    for(int i =1;i<degree_of_two;i++)
    {
        temp=(temp*temp)%number;

        if(temp==1)
        {
            return false; 
        }
        if(temp==number-conv<ZZ>(1))
        {
            return true;
        }

    }

    return false;
    

}

bool miller_rabin_primality_test(ZZ number)
{
    for(int i=0;i<PRECISION_OF_TEST_PRIME;i++)
    {
        if(miller_rabin_primality_test_simple(number))
        {
            continue;
        }
        else
        {
            return false;
        }
    }

    return true;
}

//search prime number with fixes size in bits****************************************

ZZ find_prime_number_fixes_size(int size)
{
    cout<<endl<<"\t-generation prime number fixes size:"<<endl;

    ZZ result; 

    do
    {
        result=conv<ZZ>(0);   

        vector<int> choosen_number(size,0);   

        l_20_generator(choosen_number);
          
        convert_to_decimal(choosen_number,result);

        cout<<endl<<"\t"<<result<<endl;
    }
    while(!miller_rabin_primality_test(result));

    return result;
}

//RSA generation keys****************************************************************

void generate_two_pair_key(ZZ &key_one_first,ZZ &key_one_second,ZZ &key_two_first,ZZ &key_two_second)
{
    cout<<endl<<"Generation secret keys:"<<endl;

    do
    {
        cout<<endl<<"-generation secret keys first pair:"<<endl;

        do 
        {
            key_one_first=conv<ZZ>(0);  key_one_second=conv<ZZ>(0);

            key_one_first=find_prime_number_fixes_size(SIZE_KEY);
            key_one_second=find_prime_number_fixes_size(SIZE_KEY);

        }
        while(key_one_first==key_one_second);

        cout<<endl<<"-generation secret keys second pair:"<<endl;

        do 
        {
            key_two_first=conv<ZZ>(0);  key_two_second=conv<ZZ>(0);
            
            key_two_first=find_prime_number_fixes_size(SIZE_KEY);
            key_two_second=find_prime_number_fixes_size(SIZE_KEY);
        }
        while(key_two_first==key_two_second);
        
        
       
    }
    while(!(key_one_first*key_one_second<=key_two_first*key_two_second));
}

//RSA generation public and private keys*********************************************

void generation_public_and_private_keys(ZZ &key_one_first,ZZ &key_one_second,ZZ &key_two_first,ZZ &key_two_second,ZZ &e,ZZ &d,ZZ &e_,ZZ &d_)
{
    cout<<endl<<"****************************************************************"<<endl;

    cout<<endl<<"Procedure of generation keys..."<<endl;

    key_one_first=conv<ZZ>(0);   key_one_second=conv<ZZ>(0);      key_two_first=conv<ZZ>(0);   key_two_second=conv<ZZ>(0);

    generate_two_pair_key(key_one_first,key_one_second,key_two_first,key_two_second);

    e=conv<ZZ>((pow(2,16)+1));    d=inverted_element(e,(key_one_first-conv<ZZ>(1))*(key_one_second-conv<ZZ>(1)));
    e_=conv<ZZ>((pow(2,16)+1));   d_=inverted_element(e_,(key_two_first-conv<ZZ>(1))*(key_two_second-conv<ZZ>(1)));

    cout<<endl<<"-also inverted secret element:"<<endl;

    cout<<endl<<d<<endl; 
    cout<<endl<<d_<<endl; 

    cout<<endl<<"Generation public keys:"<<endl;
    
        cout<<endl<<"-generation public key first:"<<endl;
        
        cout<<endl<<e<<endl;    
        
        cout<<endl<<key_one_first*key_one_second<<endl;
        
        cout<<endl<<"-generation public key second:"<<endl;
        
        cout<<endl<<e_<<endl;   
        
        cout<<endl<<key_two_first*key_two_second<<endl;
        
    cout<<endl<<"****************************************************************"<<endl;

}

//RSA protocol organization**********************************************************

struct public_key
{
    ZZ e;
    ZZ n;
};

struct private_key
{
    ZZ p;
    ZZ q;
    ZZ d;
};

class RSA
{
    private:
        
        ZZ message;

        ZZ message_encrypt;
        ZZ message_decrypt;

        ZZ signature_encrypt;
        ZZ signature_decrypt;
        
        private_key keys_private;

    public:

        public_key keys_public;

        RSA(ZZ message_,ZZ key_one, ZZ key_two, ZZ e_, ZZ d_)
        {
            message= message_;                   message_encrypt=conv<ZZ>(0);                           message_decrypt=conv<ZZ>(0);
            
            signature_encrypt=conv<ZZ>(0);       signature_decrypt=conv<ZZ>(0);
            
            keys_private.d=d_;                   keys_private.p=key_one;                                 keys_private.q=key_two;
            
            keys_public.e=e_;                    keys_public.n=key_one*key_two;
        };

        ZZ rsa_encryption(ZZ message,ZZ degree,ZZ module);
        ZZ rsa_decryption(ZZ cipher,ZZ degree,ZZ module);
        
        ZZ rsa_digital_signature(ZZ message,ZZ degree,ZZ module);
        ZZ rsa_cheak_digital_signature(ZZ digital_signature,ZZ degree,ZZ module,ZZ message);

        void rsa_send_message(RSA &abonent_send,RSA &abonent_receive);
        void rsa_receive_message(RSA &abonent_send,RSA &abonent_receive);

        ZZ _get_secrete_key_d()
        {
            return keys_private.d;
        }
};

//RSA encryption*********************************************************************

ZZ RSA::rsa_encryption(ZZ message,ZZ degree,ZZ module)
{
    return horner_method(message,degree,module);
}

//RSA decryption*********************************************************************

ZZ RSA::rsa_decryption(ZZ cipher,ZZ degree,ZZ module)
{
    return horner_method(cipher,degree,module);
}

//RSA digital signature**************************************************************

ZZ RSA::rsa_digital_signature(ZZ message,ZZ degree,ZZ module)
{
    return horner_method(message,degree,module);
}

//RSA cheak digital signature********************************************************

ZZ RSA::rsa_cheak_digital_signature(ZZ digital_signature,ZZ degree,ZZ module,ZZ message)
{
    if(message==horner_method(digital_signature,degree,module)||message==module-horner_method(digital_signature,degree,module))
    {
        cout<<"Digital signature is real."<<endl;

        cout<<endl;
    }
    else
    {
        cout<<endl<<"Digital signature is not real."<<endl;
    }

    return horner_method(digital_signature,degree,module);
   
}

//RSA send  message******************************************************************

void RSA::rsa_send_message(RSA &abonent_send,RSA &abonent_receive)
{
    cout<<endl<<"Send keys:"<<endl;

    abonent_receive.message_encrypt=abonent_send.rsa_encryption(abonent_send.message,abonent_receive.keys_public.e, abonent_receive.keys_public.n);
                                                                
    cout<<endl<<"-encryption key parameters:"<<endl;

    cout<<endl<<dec_to_hex(abonent_send.message)<<endl;
    cout<<endl<<dec_to_hex(abonent_receive.keys_public.e)<<endl;
    cout<<endl<<dec_to_hex(abonent_receive.keys_public.n)<<endl;

    abonent_send.signature_encrypt=abonent_send.rsa_digital_signature(abonent_send.message,abonent_send.keys_private.d,abonent_send.keys_public.n);
                                                                      
    cout<<endl<<"-digital signature parameters:"<<endl;

    cout<<endl<<dec_to_hex(abonent_send.message)<<endl;
    cout<<endl<<dec_to_hex(abonent_send.keys_public.e)<<endl;
    cout<<endl<<dec_to_hex(abonent_send.keys_public.n)<<endl;

    abonent_receive.signature_encrypt=abonent_send.rsa_encryption(abonent_send.signature_encrypt,abonent_receive.keys_public.e,abonent_receive.keys_public.n);
                                                                  
    cout<<endl<<"-encryption digital signature parameters:"<<endl;

    cout<<endl<<dec_to_hex(abonent_send.signature_encrypt)<<endl;
    cout<<endl<<dec_to_hex(abonent_receive.keys_public.e)<<endl;
    cout<<endl<<dec_to_hex(abonent_receive.keys_public.n)<<endl;

    cout<<endl<<"-results procedure sending:"<<endl;

    cout<<endl<<"-message encrypt: "<<dec_to_hex(abonent_receive.message_encrypt)<<endl;
    cout<<endl<<"-digital signature: "<<dec_to_hex(abonent_send.signature_encrypt)<<endl;
    cout<<endl<<"-signature encrypt: "<< dec_to_hex(abonent_receive.signature_encrypt)<<endl;

}

//RSA receive message****************************************************************

void RSA::rsa_receive_message(RSA &abonent_send,RSA &abonent_receive)
{
    cout<<endl<<"Receive keys:"<<endl;

    abonent_receive.message_decrypt=abonent_receive.rsa_decryption(abonent_receive.message_encrypt,abonent_receive.keys_private.d,abonent_receive.keys_public.n);

    cout<<endl<<"-decryption key parameters:"<<endl;

    cout<<endl<<dec_to_hex(abonent_receive.message_encrypt)<<endl;
    cout<<endl<<dec_to_hex(abonent_receive.keys_private.d)<<endl;
    cout<<endl<<dec_to_hex(abonent_receive.keys_public.n)<<endl;

    abonent_receive.signature_decrypt=abonent_receive.rsa_decryption(abonent_receive.signature_encrypt,abonent_receive.keys_private.d,abonent_receive.keys_public.n);

    cout<<endl<<"-decryption digital signature parameters:"<<endl;

    cout<<endl<<dec_to_hex(abonent_receive.signature_encrypt)<<endl;
    cout<<endl<<dec_to_hex(abonent_receive.keys_private.d)<<endl;
    cout<<endl<<dec_to_hex(abonent_receive.keys_public.n)<<endl;    

    cout<<endl<<"-check digital signature parameters:"<<endl;

    cout<<endl;

    ZZ temp=abonent_receive.rsa_cheak_digital_signature(abonent_receive.signature_decrypt,abonent_send.keys_public.e,abonent_send.keys_public.n,abonent_receive.message_decrypt);

    
    cout<<dec_to_hex(abonent_receive.signature_decrypt)<<endl;
    cout<<endl<<dec_to_hex(abonent_send.keys_public.e)<<endl;
    cout<<endl<<dec_to_hex(abonent_send.keys_public.n)<<endl;
    cout<<endl<<dec_to_hex(abonent_receive.message_decrypt)<<endl;

    cout<<endl<<"-results procedure receiving:"<<endl;

    cout<<endl<<"-message decrypt: "<<dec_to_hex(abonent_receive.message_decrypt)<<endl;
    cout<<endl<<"-digital signature: "<<dec_to_hex(abonent_receive.signature_decrypt)<<endl;
    cout<<endl<<"-check signature with message decrypt: "<<dec_to_hex(temp)<<endl;

}

//total commander********************************************************************

void total_commander()
{
    cout<<endl<<"Command in use:"<<endl;

        cout<<endl<<"\t[0] - exit;"<<endl;

        cout<<endl<<"\t[1] - ordinary encryption, decription, digital signature for the message;"<<endl;

        cout<<endl<<"\t[2] - protocol algorithm for secrete keys;"<<endl;

}

//main*******************************************************************************

int main()
{
    ZZ key_one_first;   ZZ key_one_second;     ZZ e;   ZZ d;         ZZ key_two_first;   ZZ key_two_second;     ZZ e_;  ZZ d_; 
   
        generation_public_and_private_keys(key_one_first, key_one_second, key_two_first, key_two_second,e, d, e_, d_);

    cout<<endl<<"In hex representation all generated keys, which we will be using:"<<endl;

    cout<<endl<<"\t - first user:"<<endl;

    cout<<endl<<"\t\t - secrete keys:"<<endl;
    cout<<endl<<"\t\t"<<dec_to_hex(key_one_first)<<endl;
    cout<<endl<<"\t\t"<<dec_to_hex(key_one_second)<<endl;
    cout<<endl<<"\t\t"<<dec_to_hex(d)<<endl;

    cout<<endl<<"\t\t - public keys:"<<endl;
    cout<<endl<<"\t\t"<<dec_to_hex(e)<<endl;
    cout<<endl<<"\t\t"<<dec_to_hex(key_one_first*key_one_second)<<endl;

     cout<<endl<<"\t - second user:"<<endl;
    
    cout<<endl<<"\t\t - secrete keys:"<<endl;
    cout<<endl<<"\t\t"<<dec_to_hex(key_two_first)<<endl;
    cout<<endl<<"\t\t"<<dec_to_hex(key_two_second)<<endl;
    cout<<endl<<"\t\t"<<dec_to_hex(d_)<<endl;

    cout<<endl<<"\t\t - public keys:"<<endl;
    cout<<endl<<"\t\t"<<dec_to_hex(e_)<<endl;
    cout<<endl<<"\t\t"<<dec_to_hex(key_two_first*key_two_second)<<endl;

    cout<<endl<<"****************************************************************"<<endl;

    total_commander();

    int answer;

    do
    {
        cout << endl << "Input your choose:" << endl;		cin >> answer;

        switch (answer)
        {
            case 0:
            {

                cout << endl << "Exit with program." << endl;

                break;
            }
            case 1:
            {

                cout<<endl<<"Input message:"<<endl;
                
                cout<<endl;

                string hex; cin>>hex;
                
                ZZ message=hex_to_dec(hex); 

                RSA Alise(conv<ZZ>(0),key_one_first, key_one_second, e, d);     RSA Bob(conv<ZZ>(0),key_two_first, key_two_second, e_,d_); 

                cout<<endl<<"- encryption message:"<<endl;

                    ZZ cryptogram=Bob.rsa_encryption(message,e,key_one_first*key_one_second);

                    cout<<endl<<dec_to_hex(cryptogram)<<endl;

                cout<<endl<<"- decryption cryptogram:"<<endl;

                    cout<<endl<<dec_to_hex(Alise.rsa_decryption(cryptogram,d,key_one_first*key_one_second))<<endl;

                cout<<endl<<"- digital signature of message:"<<endl;

                    ZZ signature=Alise.rsa_digital_signature(message,d,key_one_first*key_one_second);

                    cout<<endl<<dec_to_hex(signature)<<endl;

                cout<<endl<<"- check digital signature of message:"<<endl;

                    cout<<endl<<dec_to_hex(Bob.rsa_cheak_digital_signature(signature,e,key_one_first*key_one_second,message))<<endl;

                break;
            }
            case 2:
            {
                cout<<endl<<"Input secret keys which we want to send using protocol sending:"<<endl;

                cout<<endl;

                string hex; cin>>hex;
                
                ZZ key=hex_to_dec(hex); 

                RSA Alise(key,key_one_first, key_one_second, e, d);     RSA Bob(conv<ZZ>(0),key_two_first, key_two_second, e_,d_); 
                Alise.rsa_send_message(Alise,Bob);                      Bob.rsa_receive_message(Alise,Bob);
               
                break;
            }
            default:
            {
                cout << endl << "Error." << endl;
            }
               	
            
        }
    }
    while(answer!=0);



    return 0;
}
