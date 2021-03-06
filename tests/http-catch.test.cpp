#include "regexp/regexp.hpp"
#include <cstdio>

using namespace SRX;

std::string getStringFromCatch(const char * str, Catch ctch)
{
	return std::string(str+ctch.begin, ctch.length);
}

int main ()
{
	using Protocol = OneCatch<1, Plus<CRange<'a','z'>> >;
	using Domain = OneCatch<2, Plus<CRange<'a','z'>> >;
	using NextDomains = Star<Seq<Chr<0x2e>>, StaticCatch<3, 8, Plus<CRange<'a','z'>>>>;
	using Path = OneCatch<4, Star<Any>>;
	using HTTPCatch = RegularExpression<Begin, Protocol, Str<0x3a,0x2f,0x2f>, Domain, NextDomains, Chr<0x2f>, Path, End>;
	
	//RegularExpression< Begin, OneCatch<1, Plus<CRange<'a','z'>> >, Str<0x3a,0x2f,0x2f>, OneCatch<2, Plus<CRange<'a','z'>> >, Star<Seq<Chr<0x2e>>>, DynamicCatch<3, Plus<CRange<'a','z'>>>, Chr<0x2f>, OneCatch<4, Star<Any>>, End> regexp;
	
	class Blabla
	{
	};
	
	HTTPCatch regexp;
	
	//printf("sizeof(HTTPCatch) = %zu\n",sizeof(HTTPCatch));
	//printf("sizeof(Begin) = %zu\n",sizeof(Begin));
	//printf("sizeof(Sequence<Begin,End>) = %zu\n",sizeof(Sequence<Begin,End>));
	//printf("sizeof(Protocol) = %zu\n",sizeof(Protocol));
	//printf("sizeof(Plus<CRange<'a','z'>>) = %zu\n",sizeof(Plus<CRange<'a','z'>>));
	//printf("sizeof(NextDomains) = %zu\n",sizeof(NextDomains));
	//printf("sizeof(Str<0x3a,0x2f,0x2f>) = %zu\n",sizeof(Str<0x3a,0x2f,0x2f>));
	//printf("sizeof(Domain) = %zu\n",sizeof(Domain));
	const char * url{"http://pano.hanicka.net/something"};
	if (regexp(url))
	{
		printf("yes:\n");
		unsigned int id{0};
		
		if (getStringFromCatch(url, regexp.getCatch<1>()[0]) != "http")
		{
			fprintf(stderr,"%u: catch != http\n",__LINE__);
			return 1;
		}
		if (getStringFromCatch(url, regexp.getCatch<2>()[0]) != "pano")
		{
			fprintf(stderr,"%u: catch != pano\n",__LINE__);
			return 1;
		}
		if (getStringFromCatch(url, regexp.getCatch<3>()[0]) != "hanicka")
		{
			fprintf(stderr,"%u: catch != hanicka\n",__LINE__);
			return 1;
		}
		if (getStringFromCatch(url, regexp.getCatch<3>()[1]) != "net")
		{
			fprintf(stderr,"%u: catch != net\n",__LINE__);
			return 1;
		}
		if (getStringFromCatch(url, regexp.getCatch<4>()[0]) != "something")
		{
			fprintf(stderr,"%u: catch != something\n",__LINE__);
			return 1;
		}
		
		for (auto tmp: regexp.getCatch<0>()) printf("0.%u: '%.*s'\n",id++,(int)tmp.length,url+tmp.begin);
		id = 0;
		for (auto tmp: regexp.getCatch<1>()) printf("1.%u: '%.*s'\n",id++,(int)tmp.length,url+tmp.begin);
		id = 0;
		for (auto tmp: regexp.getCatch<2>()) printf("2.%u: '%.*s'\n",id++,(int)tmp.length,url+tmp.begin);
		id = 0;
		for (auto tmp: regexp.getCatch<3>()) printf("3.%u: '%.*s'\n",id++,(int)tmp.length,url+tmp.begin);
		id = 0;
		for (auto tmp: regexp.getCatch<4>()) printf("4.%u: '%.*s'\n",id++,(int)tmp.length,url+tmp.begin);
		
		regexp.reset();
		
		unsigned int count{0};
		
		id = 0;
		for (auto tmp: regexp.getCatch<0>()) { printf("0.%u: '%.*s'\n",id++,(int)tmp.length,url+tmp.begin); count++; }
		id = 0;
		for (auto tmp: regexp.getCatch<1>()) { printf("1.%u: '%.*s'\n",id++,(int)tmp.length,url+tmp.begin); count++; }
		id = 0;
		for (auto tmp: regexp.getCatch<2>()) { printf("2.%u: '%.*s'\n",id++,(int)tmp.length,url+tmp.begin); count++; }
		id = 0;
		for (auto tmp: regexp.getCatch<3>()) { printf("3.%u: '%.*s'\n",id++,(int)tmp.length,url+tmp.begin); count++; }
		id = 0;
		for (auto tmp: regexp.getCatch<4>()) { printf("4.%u: '%.*s'\n",id++,(int)tmp.length,url+tmp.begin); count++; }
		
		if (count != 0)
		{
			fprintf(stderr,"%u: catches after reset should be zero!\n",__LINE__);
			return 1;
		}
		
		return 0;
	}
	else
	{
		return 1;
	}
}
