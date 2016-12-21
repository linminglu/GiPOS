#pragma once

class CSoftwareKey2
{
public:
	CSoftwareKey2(void);
	~CSoftwareKey2(void);
    int VerifySoftwareKey(int module,CString& strExpire);
};
