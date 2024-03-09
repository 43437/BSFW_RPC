#ifndef __MSG_DATA_H__
#define __MSG_DATA_H__

#include "cereal/types/unordered_map.hpp"
#include "cereal/types/string.hpp"
#include "cereal/archives/portable_binary.hpp"
#include <iostream>

struct MData
{
	int m_aaa;
	std::string m_bbb;

	template<typename Arch>
	void serialize(Arch& ar)
	{
		ar(m_aaa, m_bbb);
	}

    friend std::ostream& operator<<(std::ostream& os, const MData& dt);
};

std::ostream& operator<<(std::ostream& os, const MData& dt)
{
    os << dt.m_aaa << '/' << dt.m_bbb;
    return os;
}

struct MyStruct
{
	std::unordered_map<int, MData> m_mpData;
	//int a;
	//int b;

	template<typename Arch>
	void serialize(Arch& ar)
	{
		ar(m_mpData);
	}


};

template<typename T>
std::string ToString(T& stuMySt)
{
	std::stringstream ss;
	{
		cereal::PortableBinaryOutputArchive bos(ss);
		bos(stuMySt);
	}
    
    return ss.str();
}

template<typename T>
void FromString(const std::string& str, T& stuMySt)
{
    std::stringstream strsrv(str);
    
    {
        cereal::PortableBinaryInputArchive bis(strsrv);
        bis(stuMySt);
    }
}


template<typename T>
void PrintParam(const T& val)
{
    for(auto itVal = val.begin(); val.end() != itVal; ++itVal)
    {
        std::cout << "key: " << itVal->first << "\tvalue: " << itVal->second << std::endl;
    }
}

#endif