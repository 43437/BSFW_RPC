#include "httplib.h"
#include "msgdata.h"
#include <iostream>

int main()
{
    // HTTP
    httplib::Client cli("http://localhost:22222");

    // auto res = cli.Get("/hi");
    // std::cout << "status: " << res->status << std::endl;
    // std::cout << "body: " << res->body << std::endl;
    MyStruct stuMySt;
    auto& stuDat = stuMySt.m_mpData[0];
    stuDat.m_aaa = 0;
    stuDat.m_bbb = "client 0";

    auto& stuDat1 = stuMySt.m_mpData[1];
    stuDat1.m_aaa = 1;
    stuDat1.m_bbb = "client 1";

	auto postMsg = ToString(stuMySt);

    auto res = cli.Post("/msg", postMsg.c_str(), postMsg.size(), "tttttt");
    std::cout << "status: " << res->status << std::endl;

    {
        MyStruct stuRecv;
        FromString(res->body, stuRecv);

        std::cout << "recv body: " << std::endl;
        PrintParam(stuRecv.m_mpData);
    }

    return 0;
}