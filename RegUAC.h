#ifndef REG_UAC_h

#define REG_UAC_H
#include"common.h"
BOOL uac_bypass_wsreset();
BOOL uac_bypass_fodhelpercleanup();
BOOL uac_bypass_eventviewer();
BOOL ucompmgmtlauncher();
BOOL computerdefaults();
BOOL sdclt_uacbypass();
BOOL sdclt_isolatedcommand();
BOOL slui();
BOOL uac_silentcleanup();
BOOL uac_mockdir();
BOOL uac_perfmon();
BOOL uac_runas();
BOOL uac_cliconfg();
BOOL uac_cmstp();


#endif