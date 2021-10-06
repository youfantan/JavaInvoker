//
// Created by shandiankulishe on 2021/10/5.
//
#include "JVMLocator.h"
bool whereJvmDll(string path,string* out){
    ifstream jdksjvm(path+R"(\jre\bin\server\jvm.dll)");
    if (!jdksjvm.good()){
        ifstream jdkcjvm(path+R"(\jre\bin\client\jvm.dll)");
        if (!jdkcjvm.good()){
            ifstream jresjvm(path+R"(\bin\server\jvm.dll)");
            if(!jresjvm.good()){
                ifstream jrecjvm(path+R"(\bin\client\jvm.dll)");
                if (!jrecjvm.good()){
                    return false;
                } else{
                    *out=path+R"(\bin\server\client.dll)";
                }
            } else{
                *out=path+R"(\bin\server\jvm.dll)";
            }
        } else{
            *out=path+R"(\jre\bin\client\jvm.dll)";
        }
    } else{
        *out=R"(\jre\bin\server\jvm.dll)";
    }
    return true;
}
std::string TCHAR2STRING(TCHAR* str)
{
    std::string strstr;
    try
    {
        int iLen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

        char* chRtn = new char[iLen * sizeof(char)];

        WideCharToMultiByte(CP_ACP, 0, str, -1, chRtn, iLen, NULL, NULL);

        strstr = chRtn;
    }
    catch (std::exception e)
    {
    }

    return strstr;
}
bool JVMLocator::findInDefaultDir(vector<string> *result) {
    string programPath = getenv("ProgramFiles");
    string jPath=programPath+"\\Java\\*";
    _finddata_t fi;
    long long dirHandle = _findfirst(jPath.c_str(), &fi);
    if (dirHandle==-1L){
        return false;
    }
    do {
        if (fi.attrib&_A_SUBDIR)
        {
            if ((strcmp(fi.name, ".") != 0) && (strcmp(fi.name, "..") != 0))
            {
                string javaHome=programPath+"\\Java\\"+fi.name;
                string jvmHome;
                if (!whereJvmDll(javaHome,&jvmHome)){
                    return false;
                }
                result->push_back(jvmHome);
            }
        }
    } while (_findnext(dirHandle, &fi) == 0);
    _findclose(dirHandle);
    return true;
}

bool JVMLocator::findInEnv(vector<string> *result) {
    string JAVA_HOME = getenv("JAVA_HOME");
    if (JAVA_HOME.empty()){
        return false;
    }
    string jvmHome;
    if (!whereJvmDll(JAVA_HOME,&jvmHome)){
        return false;
    }
    result->push_back(jvmHome);
    return true;
}

bool JVMLocator::findInPath(vector<string> *result) {
    FILE* pp = _popen("where java", "r");
    if (!pp) {
        return false;
    }
    char tmp[1024];
    while (fgets(tmp, sizeof(tmp), pp) != NULL) {
        if (tmp[strlen(tmp) - 1] == '\n') {
            tmp[strlen(tmp) - 1] = '\0';
        }
        string javaHome=tmp;
        string jvmHome;
        javaHome=javaHome.replace(javaHome.find_last_of("\\bin")-4, 13, "");
        if (!whereJvmDll(javaHome,&jvmHome)){
            return false;
        }
        result->push_back(jvmHome);
        _pclose(pp);
        return true;
    }
    return false;
}

bool JVMLocator::findInReg(vector<string> *result) {
    HKEY hKey = NULL;
    DWORD dwType = REG_SZ;
    DWORD dwIndexs = 0;
    wchar_t data[MAX_PATH];
    DWORD dwMaxLen = MAX_PATH;
    TCHAR keyName[MAX_PATH] = { 0 };
    DWORD charLength = 256;
    TCHAR* subKey = L"SOFTWARE\\JavaSoft\\Java Runtime Environment";

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, subKey, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        while (RegEnumKeyEx(hKey, dwIndexs, keyName, &charLength, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
        {
            wstring key = subKey;
            key.append(L"\\");
            key.append(keyName);
            HKEY subkey = hKey;
            if (ERROR_SUCCESS== RegOpenKeyEx(HKEY_LOCAL_MACHINE, key.c_str(), 0, KEY_READ, &subkey))
            {
                if (ERROR_SUCCESS== RegQueryValueExW(subkey, L"RuntimeLib", 0, &dwType, (LPBYTE)data, &dwMaxLen))
                {
                    result->push_back(TCHAR2STRING(data));
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
            ++dwIndexs;
            charLength = 256;
        }
        return true;
    }
    else {
        return false;
    }
    if (hKey != NULL)
    {
        RegCloseKey(hKey);
    }
}
