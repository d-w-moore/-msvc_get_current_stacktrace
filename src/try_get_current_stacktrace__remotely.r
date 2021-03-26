test() {

    *rc = 12345678
    *stktrace = ""

    remote("*to_host",""){
      *rc = msiget_current_stacktrace( *stktrace )
    }
    if (*rc == 0) {
        writeLine("stdout", "----- Stacktrace OUTPUT from Microservice (BEGIN) ----- ")
        writeLine("stdout", *stktrace )
        writeLine("stdout", "----- Stacktrace OUTPUT from Microservice ( END ) ----- ")
    }
    else {
        if (*rc == 12345678) {
          writeLine("stderr", "Did not call msiget_current_stacktrace")
        } else {
          writeLine("stderr", "Error code [*rc] returned from msiget_current_stacktrace")
        }
    }
}

INPUT  *to_host=$"localhost"
OUTPUT ruleExecOut
