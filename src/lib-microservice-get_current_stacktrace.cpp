// =-=-=-=-=-=-=-
// irods includes
#include "irods_error.hpp"
#include "irods_ms_plugin.hpp"
#include "irods_stacktrace.hpp"

// =-=-=-=-=-=-=-
// stl includes
#include <cstring>
#include <cstdlib>
#include <string>
#include <cstring>
#include <regex.h>

int msiget_current_stacktrace(
    msParam_t*      stacktrace_out,
    ruleExecInfo_t* _rei ) 
{
    int i;
    irods::stacktrace st; 
    std::string buffer {st.dump()};
    try
    {
       fillStrInMsParam(stacktrace_out, buffer.c_str());
       return 0;
    }
    catch (irods::error& e) {
       i = e.code();
       rodsLog(LOG_ERROR, "In msiget_current_stacktrace: irods error [%d]",i);
    }
    catch (std::exception& e) {
       i = -1;
       rodsLog(LOG_ERROR, "In msiget_current_stacktrace: something went wrong: %s",e.what());
    }
    return i;
}

extern "C"
irods::ms_table_entry* plugin_factory() {
    irods::ms_table_entry* msvc = new irods::ms_table_entry(1);
    msvc->add_operation<
        msParam_t*,
        ruleExecInfo_t*>("msiget_current_stacktrace",
                         std::function<int(
                             msParam_t*,
                             ruleExecInfo_t*)>(msiget_current_stacktrace));
    return msvc;
}

/*=====================================


int msiget_current_stacktrace( msParam_t* where, ruleExecInfo_t *rei ) {
    int i;
    char *writeId = ( char * ) where->inOutStruct;
    irods::stacktrace st; 
    std::string buffer {st.dump()};
    msParam_t param {};
    param.inOutStruct = const_cast<char*>(buffer.c_str());
    i = writeString( where, &param, rei );


    return i;
}

extern "C"
irods::ms_table_entry* plugin_factory() {
    irods::ms_table_entry* msvc = new irods::ms_table_entry(1);
    msvc->add_operation<
        msParam_t*,
        ruleExecInfo_t*>("msiget_current_stacktrace",
                         std::function<int(
                             msParam_t*,
                             ruleExecInfo_t*)>(msiget_current_stacktrace));
    return msvc;
}

*/
