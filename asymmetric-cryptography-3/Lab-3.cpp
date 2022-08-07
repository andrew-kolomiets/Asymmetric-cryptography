
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

ZZ gcd_extention( ZZ a, ZZ b, ZZ &u, ZZ &v )
{
    ZZ q0, r0, r1, r2, u0, u1, u2;

    if ((a == conv<ZZ>(0)) && (b ==  conv<ZZ>(0))) { u = v =  conv<ZZ>(0); return  conv<ZZ>(0);}
    r2 = (a <  conv<ZZ>(0)) ? -a : a; r1 = (b <  conv<ZZ>(0)) ? -b : b;
    u2 =  conv<ZZ>(1); u1 =  conv<ZZ>(0);
    while (r1 !=  conv<ZZ>(0)) {
    q0 = r2 / r1;
    r0 = r2 - q0 * r1; r2 = r1; r1 = r0;
    u0 = u2 - q0 * u1; u2 = u1; u1 = u0;
    }
    u = u2; if (a <  conv<ZZ>(0)) u = -(u);
    v = (b ==  conv<ZZ>(0)) ?  conv<ZZ>(0) : (r2 -(u) * a)/b;

    return r2;
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
        result+=power(ZZ(2),binary_representation.size()-i-1)*conv<ZZ>(binary_representation[i]);
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

ZZ ZZ_pow(ZZ number, ZZ degree)
{

    vector<int> binary_representation;

    convert_to_binary_modify(degree, binary_representation);

    ZZ result = conv<ZZ>(1);

    for (long long int i = (long long int)(binary_representation.size()) - 1; i >= 0; i--)
    {
        result = (result * result);

        if (binary_representation[i] == 1)
        {
            result = (result * number) ;
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

ZZ find_any_number_fixes_size(int size)
{
  
    ZZ result=conv<ZZ>(0);

    vector<int> choosen_number(size,0);   l_20_generator(choosen_number);   convert_to_decimal(choosen_number,result);

    return result;
}

ZZ find_prime_number_fixes_size(int size)
{
    //cout<<endl<<"\t-generation prime number fixes size:"<<endl;

    ZZ result; 

    do
    {
        result=conv<ZZ>(0);   

        vector<int> choosen_number(size,0);   l_20_generator(choosen_number);   convert_to_decimal(choosen_number,result);

        //cout<<endl<<"\t"<<result<<endl;
    }
    while(!miller_rabin_primality_test(result));

    return result;
}

ZZ bloom_prime_generator(int size)
{

    //cout<<endl<<"\t-generation bloom prime number fixes size:"<<endl;

    ZZ result; 

    do
    {
        result=conv<ZZ>(0);   

        vector<int> choosen_number(size,0);     
        l_20_generator(choosen_number);    
        convert_to_decimal(choosen_number,result);

        //cout<<endl<<"\t"<<result<<endl;
    }
    while(!(miller_rabin_primality_test(result)&&result%(conv<ZZ>(4))==conv<ZZ>(3)));

    return result;
}

//jacoby symbol *********************************************************************

ZZ symbol_jacoby(ZZ x, ZZ n)
{
    bool triger=true;

    ZZ jacoby_symbol=conv<ZZ>(1);    

    ZZ degree;     ZZ prime_part;

    
    do
    {
        x=x%n;

        if(x==conv<ZZ>(0) || x%n==conv<ZZ>(0)){ triger=false; return conv<ZZ>(0); }

        if(x==conv<ZZ>(1)){ triger=false; return jacoby_symbol; }

        if(x==conv<ZZ>(2)){ triger=false; return jacoby_symbol*(ZZ_pow(conv<ZZ>(-1),(power(n,2)-conv<ZZ>(1))/conv<ZZ>(8))); }
        
        degree=conv<ZZ>(0);   prime_part=conv<ZZ>(0);   prime_part=x;

        while(prime_part%conv<ZZ>(2)==conv<ZZ>(0))  {prime_part=prime_part>>1; degree++;}

        if(degree>conv<ZZ>(1)&&degree%conv<ZZ>(2)==conv<ZZ>(0))
        {
            x=prime_part;
            continue;
        }
        if(degree>1&&degree%2==1)
        {
            jacoby_symbol*=(ZZ_pow(conv<ZZ>(-1),(power(n,2)-conv<ZZ>(1))/conv<ZZ>(8))); 
            x=prime_part;
            continue;
        }
        if(degree==1)
        {
            jacoby_symbol*=(ZZ_pow(conv<ZZ>(-1),(power(n,2)-conv<ZZ>(1))/conv<ZZ>(8))); 
            x=prime_part;
            continue;
        }
        else
        {
            jacoby_symbol*= (ZZ_pow(conv<ZZ>(-1),((x-conv<ZZ>(1))*(n-conv<ZZ>(1)))/conv<ZZ>(4)));

            ZZ temp=x;

            x=n%x;
            n=temp;

            continue;
        }

    }while (triger);

}

//rabin cryptosystem*****************************************************************

struct private_keys
{
    ZZ p;
    ZZ q;
    ZZ b;
};

struct public_keys
{
    ZZ n;
    ZZ b;

};

class Rabin
{
    private:

        private_keys key_private;


    public:

        public_keys key_public;

        Rabin()
        {
            key_private.p=bloom_prime_generator(SIZE_KEY);  key_private.q=bloom_prime_generator(SIZE_KEY); 
            
            key_public.n=key_private.p* key_private.q;

            int size=rand()%SIZE_KEY;
            
            key_private.b=find_any_number_fixes_size(size);

            key_public.b= key_private.b;

        }

        void get_public_keys()
        {
            cout<<endl<<"- public constant "<< dec_to_hex(key_public.b)<<endl;
            cout<<endl<<"- public moduls "<< dec_to_hex(key_public.n)<<endl;
        }

        void get_secrete_keys()
        {
            cout<<endl<<"- public constant "<< dec_to_hex(key_public.b)<<endl;
            cout<<endl<<"- secrete p "<< dec_to_hex(key_private.p)<<endl;
            cout<<endl<<"- secrete q "<< dec_to_hex(key_private.q)<<endl;
        }
        
        vector<ZZ> quick_calculation_of_the_square_root_of_the_bloom(ZZ y,ZZ p,ZZ q);

        ZZ difficult_to_turn_function_of_rabin(ZZ message,ZZ constant, ZZ module);

        ZZ format_message(ZZ message,ZZ module);

        ZZ unformat_message(ZZ format_message,ZZ module);

        vector<ZZ> encryption_rabin_algorithm(ZZ message,ZZ constant, ZZ module);

        bool  check_root(ZZ root,ZZ c1,ZZ c2, ZZ constant,ZZ module);

        ZZ decryption_rabin_algorithm(vector<ZZ> cipher, ZZ constant, ZZ module);

        ZZ signature_rabin_algorithm(ZZ message);

        ZZ verify_signature_rabin_algorithm(ZZ message,ZZ signature, ZZ module);


        ZZ part_by_sender_for_proof_protocol(ZZ &random_message,ZZ module);

        ZZ  part_by_receiver_for_proof_protocol(ZZ message,ZZ module);
        
        bool  proof(ZZ roots,ZZ message, ZZ module);

        ZZ  attack_part_by_sender_for_proof_protocol(ZZ &random_message,ZZ module);

        ZZ attack_part_by_receiver_for_proof_protocol(ZZ message,ZZ module);

        ZZ attack_proof(ZZ roots,ZZ message, ZZ module);


        
};

//rabin cryptosystem methods*********************************************************


vector<ZZ> Rabin::quick_calculation_of_the_square_root_of_the_bloom(ZZ y,ZZ p,ZZ q) //ok 
{
    vector<ZZ> roots;

    ZZ u,v ;   gcd_extention(p,q,u,v);

    ZZ s1=horner_method(y,(p+conv<ZZ>(1))/conv<ZZ>(4), p);    
    ZZ s2=horner_method(y,(q+conv<ZZ>(1))/conv<ZZ>(4), q);
    
    roots.push_back((u*p*s2+v*q*s1)%(p*q));  
    roots.push_back((u*p*s2-v*q*s1)%(p*q));    
    roots.push_back((-u*p*s2+v*q*s1)%(p*q));  
    roots.push_back((-u*p*s2-v*q*s1)%(p*q)); 
    
    return roots;
}

ZZ Rabin::difficult_to_turn_function_of_rabin(ZZ message,ZZ constant, ZZ module) //ok
{
    return (message*(message+constant))%module;
}

ZZ Rabin:: format_message(ZZ message,ZZ module)//ok
{

    vector<int> binary_representation_message;  convert_to_binary_modify(message,binary_representation_message);

    while(binary_representation_message.size()%8!=0)
    {  binary_representation_message.push_back(0); } 


    vector<int> binary_representation_module;   convert_to_binary_modify(module,binary_representation_module);

    while(binary_representation_module.size()%8!=0)
    {  binary_representation_module.push_back(0); } 


    int bytes_message=binary_representation_message.size()/8;   
    int bytes_module=binary_representation_module.size()/8;

    if(bytes_module-2<bytes_message)
    {
        cout<<endl<<"Number have incorect size in bytes."<<endl;
    }

    ZZ additional_number=find_any_number_fixes_size(63);

   return conv<ZZ>(255)*power(conv<ZZ>(2),(8*(bytes_module-2)))+message*power(conv<ZZ>(2),64)+additional_number;
}

ZZ Rabin:: unformat_message(ZZ format_message_,ZZ module)//ok
{
    vector<int> binary_representation_module;   convert_to_binary_modify(module,binary_representation_module);

    
    int bytes_module=binary_representation_module.size()/8;

    ZZ additional_number=format_message_& conv<ZZ>("18446744073709551615");
    
    return ((format_message_-additional_number-(conv<ZZ>(255)*power(conv<ZZ>(2),(8*(bytes_module-2)))))/power(conv<ZZ>(2),64));
}

vector<ZZ> Rabin::encryption_rabin_algorithm(ZZ message,ZZ constant, ZZ module)//ok
{
    ZZ data=format_message(message,module);

    vector<ZZ> cipher;

    cipher.push_back(difficult_to_turn_function_of_rabin(data,constant,module));

    cipher.push_back(((data+(constant*inverted_element(conv<ZZ>(2),module)))%module)%conv<ZZ>(2));

    cipher.push_back(symbol_jacoby((data+(constant*inverted_element(conv<ZZ>(2),module))),module));

    return cipher;
}

bool  Rabin::check_root(ZZ root,ZZ c1,ZZ c2, ZZ constant,ZZ module)//ok
{
    ZZ temp=difficult_to_turn_function_of_rabin(root,constant,module);

    ZZ _c1=((temp+(constant*inverted_element(conv<ZZ>(2),module)))%module)%conv<ZZ>(2);

    ZZ _c2=symbol_jacoby((temp+(constant/conv<ZZ>(2))),module);

    if(c1==_c1&&c2==_c2)        
    {
        return true;
    }
    else
    {
        return false;
    }

}

ZZ Rabin::decryption_rabin_algorithm(vector<ZZ> cipher, ZZ constant, ZZ module)//ok
{
    
    vector <ZZ> temp=quick_calculation_of_the_square_root_of_the_bloom((cipher[0]+(power(constant,2)*inverted_element(conv<ZZ>(4),module))),key_private.p,key_private.q);

    for(int i=0;i<temp.size();i++)
    {
        temp[i]=(temp[i]-(constant*inverted_element(conv<ZZ>(2),module)))%module;

        if(check_root(temp[i],cipher[1],cipher[2],constant,module));
        {
            return unformat_message(temp[i],module);
        }
    }


    cout<<endl<<"Error of decryption."<<endl;

    return conv<ZZ>(0);

   
}

ZZ Rabin::signature_rabin_algorithm(ZZ message)//ok
{
    vector <ZZ> roots;

    bool triger=true;

    ZZ temp=format_message(message,key_private.p*key_private.q);
    
    do 
    {
        if(symbol_jacoby(temp,key_private.p)==conv<ZZ>(1) && symbol_jacoby(temp,key_private.q)==conv<ZZ>(1))
        {
            triger==false;

            roots=quick_calculation_of_the_square_root_of_the_bloom(temp,key_private.p,key_private.q);

            break;
        }
        else
        {
            temp=format_message(message,key_private.p*key_private.q);
        }

    }
    while(triger);

    return  roots[0];
}

ZZ Rabin::verify_signature_rabin_algorithm(ZZ message,ZZ signature, ZZ module)//ok
{
    ZZ result=(signature*signature)%module;

    if(message==unformat_message(result,module))
    {
        cout<<endl<<"Digital signature pass examination!"<<endl;
    }
    else
    {
         cout<<endl<<"Digital signature not pass examination!"<<endl;
    }

    return unformat_message(result,module);

}


// protocol elementary functions*****************************************************

ZZ  Rabin::part_by_sender_for_proof_protocol(ZZ &random_message,ZZ module)
{
    random_message=find_any_number_fixes_size(SIZE_KEY);

    return horner_method(random_message,conv<ZZ>(4),module);
}

ZZ  Rabin::part_by_receiver_for_proof_protocol(ZZ message,ZZ module)
{
    vector<ZZ> roots=quick_calculation_of_the_square_root_of_the_bloom(message,key_private.p,key_private.q);

    for(int i=0;i<roots.size();i++)
    {
        if(symbol_jacoby(roots[i],key_public.n)==conv<ZZ>(1))
        {
            return roots[i];
        }
    }
}

bool Rabin::proof(ZZ roots,ZZ message, ZZ module)
{
    if(roots==power(message,2)%module)
    {
        cout<<endl<<"Good proof."<<endl;
        return true;
    }
    else
    {
        cout<<endl<<"Bad proof."<<endl;
        return false;
    }
}

// attack elementary functions ******************************************************


ZZ  Rabin::attack_part_by_sender_for_proof_protocol(ZZ &random_message,ZZ module)
{
    random_message=find_any_number_fixes_size(SIZE_KEY);

    return horner_method(random_message,conv<ZZ>(2),module);
}

ZZ Rabin::attack_part_by_receiver_for_proof_protocol(ZZ message,ZZ module)
{
    vector<ZZ> roots=quick_calculation_of_the_square_root_of_the_bloom(message,key_private.p,key_private.q);

    for(int i=0;i<roots.size();i++)
    {
        if(symbol_jacoby(roots[i],key_public.n)==conv<ZZ>(1))
        {
            return roots[i];
        }
    }
}

ZZ  Rabin::attack_proof(ZZ roots,ZZ message, ZZ module)
{
    return gcd(roots+message,module);
}


//total commander********************************************************************

void total_commander()
{
    cout<<endl<<"Command in use:"<<endl;

        cout<<endl<<"\t[0] - exit;"<<endl; //exelent 

        cout<<endl<<"\t[1] - encryption;"<<endl; //exelent

        cout<<endl<<"\t[2] - decription;"<<endl;

        cout<<endl<<"\t[3] - digital signature;"<<endl; //exelent

        cout<<endl<<"\t[4] - check digital signature;"<<endl; //exelent

        cout<<endl<<"\t[5] - zero knowledge protocol;"<<endl;

        cout<<endl<<"\t[6] - attack on crypto system;"<<endl;

}



int main()
{

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
            
                cout<<endl<<"Input other for encryption:"<<endl;

                Rabin User; 

                cout<<endl<<"-moduls"<<endl;

                string hex_moduls; cin>>hex_moduls; ZZ moduls=hex_to_dec(hex_moduls); 
                
                cout<<endl<<"-constant"<<endl;

                string hex_constant; cin>>hex_constant; ZZ constant=hex_to_dec(hex_constant); 
                
                cout<<endl<<"-message:"<<endl; 

                string hex_message; cin>>hex_message; ZZ message=hex_to_dec(hex_message); 
                

                cout<<endl<<"- encryption message:"<<endl;      
                
                vector<ZZ> cryptogram=User.encryption_rabin_algorithm(message,constant,moduls);

                cout<<endl<<"- ciphertext "<<dec_to_hex(cryptogram[0])<<endl;

                cout<<endl<<"- parity "<<cryptogram[1]<<endl;
                
                cout<<endl<<"- jacoby symbol "<<cryptogram[2]<<endl;


                break;
            }
            case 2:
            {
                cout<<endl<<"Input other for decryption:"<<endl;

                Rabin User; 

                User.get_public_keys();

                cout<<endl<<"- ciphertext "<<endl;

                string hex_cryptogram; cin>>hex_cryptogram; ZZ cryptogram=hex_to_dec(hex_cryptogram); 

                cout<<endl<<"- parity "<<endl;

                string parity_string; cin>>parity_string; ZZ parity=hex_to_dec(parity_string); 

                cout<<endl<<"- jacoby symbol "<<endl;

                string jacoby_symbol_string; cin>>jacoby_symbol_string; ZZ jacoby_symbol=hex_to_dec(jacoby_symbol_string); 

                vector<ZZ> cipher; cipher.push_back(cryptogram); cipher.push_back(parity); cipher.push_back(jacoby_symbol);


                cout<<endl<<"- decryption cryptogram:"<<endl;

                ZZ message=User.decryption_rabin_algorithm(cipher,User.key_public.b,User.key_public.n);

                string messages=dec_to_hex(message);

                cout<<endl<<messages<<endl;

                break;
            }
            case 3:
            {

                cout<<endl<<"Input other for digital signature:"<<endl;

                Rabin User; 
                
                User.get_public_keys();

                cout<<endl<<"-message:"<<endl; 

                string hex_message; cin>>hex_message; ZZ message=hex_to_dec(hex_message); 


                cout<<endl<<"- digital signature:"<<endl;

                ZZ signature=User.signature_rabin_algorithm(message);
                
                cout<<endl<<dec_to_hex(signature)<<endl;

                break;
            }
            case 4:
            {
                cout<<endl<<"Input other for verification:"<<endl;

                Rabin User; 

                cout<<endl<<"-moduls"<<endl;

                string hex_moduls; cin>>hex_moduls; ZZ moduls=hex_to_dec(hex_moduls); 
                
                cout<<endl<<"-message:"<<endl; 

                string hex_message; cin>>hex_message; ZZ message=hex_to_dec(hex_message); 

                cout<<endl<<"-signature:"<<endl; 

                string hex_signature; cin>>hex_signature; ZZ signature=hex_to_dec(hex_signature); 
                
                

                cout<<endl<<"- verification:"<<endl;   

                cout<<endl<<dec_to_hex(User.verify_signature_rabin_algorithm(message,signature,moduls))<<endl;

                break;
            }
            case 5:
            {
                cout<<endl<<"Zero knowledge protocol:"<<endl;

                Rabin User;

                cout<<endl<<"- input moduls"<<endl;

                string string_module; cin>>string_module;  
                
                ZZ module=hex_to_dec(string_module); 

                ZZ x;

                ZZ message=User.part_by_sender_for_proof_protocol(x,module);

                cout<<endl<<"- send number "<<dec_to_hex(message)<<endl;
                
                cout<<endl<<"- root number "<<endl;

                string string_root; cin>>string_root;  ZZ root=hex_to_dec(string_root); 

                User.proof(root,x,module);

                
                break;
            }
             case 6:
            {
                cout<<endl<<"Attack on crypto system:"<<endl;

                Rabin Alise;    Rabin Bob;



                cout<<endl<<"- public key Alise:"<<endl;

                Alise.get_public_keys();


                cout<<endl<<"- public key Bob:"<<endl;

                Bob.get_public_keys();


                cout<<endl<<"- input moduls for attack:"<<endl;
                 
                string string_module; cin>>string_module;  ZZ module=hex_to_dec(string_module); 

                ZZ message,root,factors;
                
                ZZ t;

                int iteration{0};

                do
                {
                    t=ZZ(0);
                    
                    message=Alise.attack_part_by_sender_for_proof_protocol(t,module);
 
                    root=Bob.attack_part_by_receiver_for_proof_protocol(message,module);

                    factors=Alise.attack_proof(root,t,module);

                    iteration+=1;
                }
                while(Alise.attack_proof(root,t,module)==ZZ(1)||Alise.attack_proof(root,t,module)==module);

                cout<<endl<<"- attack get key:"<<endl;

                cout<<endl<<dec_to_hex(factors)<<endl;

                cout<<endl<<"- number of iteration for cracking system:"<<endl;

                cout<<endl<<iteration<<endl;
                
                cout<<endl<<"- compare with secrete parametre Bob:"<<endl;

                Bob.get_secrete_keys();
                
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
