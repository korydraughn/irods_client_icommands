#include "rodsClient.h"
#include "parseCommandLine.h"
#include "rodsPath.h"
#include "mkdirUtil.h"
#include "irods_client_api_table.hpp"
#include "irods_pack_table.hpp"

#include "utility.hpp"

void usage();

int
main( int argc, char **argv ) {

    signal( SIGPIPE, SIG_IGN );

    int status;
    rodsEnv myEnv;
    rErrMsg_t errMsg;
    rcComm_t *conn;
    rodsArguments_t myRodsArgs;
    char *optStr;
    rodsPathInp_t rodsPathInp;

    optStr = "phvV";

    status = parseCmdLineOpt( argc, argv, optStr, 0, &myRodsArgs );

    if ( status < 0 ) {
        printf( "use -h for help\n" );
        exit( 1 );
    }
    if ( myRodsArgs.help == True ) {
        usage();
        exit( 0 );
    }

    status = getRodsEnv( &myEnv );

    if ( status < 0 ) {
        rodsLogError( LOG_ERROR, status, "main: getRodsEnv error. " );
        exit( 1 );
    }

    status = parseCmdLinePath( argc, argv, optind, &myEnv,
                               UNKNOWN_OBJ_T, NO_INPUT_T, 0, &rodsPathInp );

    if ( status < 0 ) {
        rodsLogError( LOG_ERROR, status, "main: parseCmdLinePath error. " );
        exit( 1 );
    }

    // =-=-=-=-=-=-=-
    // initialize pluggable api table
    irods::pack_entry_table& pk_tbl  = irods::get_pack_table();
    irods::api_entry_table&  api_tbl = irods::get_client_api_table();
    init_api_table( api_tbl, pk_tbl );

    conn = rcConnect( myEnv.rodsHost, myEnv.rodsPort, myEnv.rodsUserName,
                      myEnv.rodsZone, 0, &errMsg );

    if ( conn == NULL ) {
        exit( 2 );
    }

    // Set the version of the iRODS server this binary is built to
    // communicate with. This is necessary for handling PackStruct XML
    // encoding issues.
    utils::store_server_version_in_client_properties(*conn);

    status = clientLogin( conn );
    if ( status != 0 ) {
        rcDisconnect( conn );
        exit( 7 );
    }

    status = mkdirUtil( conn, &myRodsArgs, &rodsPathInp );

    printErrorStack( conn->rError );
    rcDisconnect( conn );

    if ( status < 0 ) {
        exit( 3 );
    }
    else {
        exit( 0 );
    }

}


void
usage() {
    char *msgs[] = {
        "Usage: imkdir [-phvV] collection ...",
        "Create one or more new collections",
        "Options are:",
        " -p  make parent directories as needed",
        " -v  verbose",
        " -V  Very verbose",
        " -h  this help",
        ""
    };
    int i;
    for ( i = 0;; i++ ) {
        if ( strlen( msgs[i] ) == 0 ) {
            break;
        }
        printf( "%s\n", msgs[i] );
    }
    printReleaseInfo( "imkdir" );
}
