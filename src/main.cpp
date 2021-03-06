#include <cppcms/service.h>
#include <cppcms/applications_pool.h>

#include "utils/DboAppender.h"
#include "utils/AuthorizeInstance.h"
#include "service/ApplicationService.h"

// test
//===============================->
#include <plog/Appenders/ColorConsoleAppender.h>
//<-===============================

int main(int argc, char* argv[])
{
    try
    {
        // debug
        //===============================->
        static plog::ColorConsoleAppender<plog::TxtFormatter> colorConsole;
        plog::init(plog::verbose, &colorConsole);
        //<-===============================

        //static DboAppender dbo;
        cppcms::service srv(argc,argv);
        DboInstance::Instance().Session(srv.settings());
        AuthorizeInstance::Instance().initialization(srv.settings());
        srv.applications_pool().mount(cppcms::applications_factory<ApplicationService>());
        //plog::init<plog::TxtFormatter>(plog::verbose, "runtime.log").addAppender(&dbo);
        srv.run();
    }
    catch (const std::exception& ex)
    {
        PLOG_ERROR << "System Error: " << ex.what();
        return -1;
    }
	return 0;
}
