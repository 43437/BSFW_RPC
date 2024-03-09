#include "httplib.h"
#include "msgdata.h"
#include <iostream>
#include <thread>

#define POS_MARK std::cout << __FUNCTION__ << " " << std::this_thread::get_id() << std::endl

int main()
{
    httplib::Server svr;

    svr.Get("/hi", [](const httplib::Request &req, httplib::Response &res) {
        POS_MARK;

        res.set_content("Hello World!", "text/plain");
    }).Post("/msg", [](const httplib::Request &req, httplib::Response &res) {
        POS_MARK;

        std::cout << "recv post" << std::endl;

        MyStruct stuMySt;
        FromString(req.body, stuMySt);
        PrintParam(stuMySt.m_mpData);

        std::cout << "addr " << req.remote_addr << std::endl;
        std::cout << "param: " << std::endl;
        PrintParam(req.params);
        std::cout << "headers: " << std::endl;
        PrintParam(req.headers);

        {
            //response
            MyStruct stuRet;
            auto& dat100 = stuRet.m_mpData[100];
            dat100.m_aaa = 100;
            dat100.m_bbb = "server 100";

            auto& dat101 = stuRet.m_mpData[101];
            dat101.m_aaa = 101;
            dat101.m_bbb = "server 101";

            auto strRet = ToString(stuRet);
            res.set_content(strRet, "text/plain");
        }
        
    });

    svr.listen("0.0.0.0", 22222);

    return 0;
}