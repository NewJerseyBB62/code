#include "OSHelper.h"

#if (defined _WIN32 || defined _WIN64)
    #include <windows.h>
#else
#endif
#include <io.h>

string OSHelper::GetSysDir()
{
    string dir;
#if (defined _WIN32 || defined _WIN64)
    char buf[1024] = { 0 };
    GetSystemDirectory((LPSTR)buf, 1024);
    dir = buf;
    if (dir.back() != '\\')
        dir += "\\";
#else
#endif

    return dir;
}

bool OSHelper::IsFileExists(string file)
{
    if (FILE* pFile = fopen(file.c_str(), "r"))
    {
        fclose(pFile);
        return true;
    }
    else
        return false;
}

bool OSHelper::IsDirExists(string dir)
{
#if (defined _WIN32 || defined _WIN64)
    WIN32_FIND_DATAA  wfd;
    bool rValue = false;
    HANDLE hFind = FindFirstFileA(dir.c_str(), &wfd);
    if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        rValue = true;
    FindClose(hFind);
#else
#endif
    return rValue;
}

bool OSHelper::CreateDir(string dir)
{
#if (defined _WIN32 || defined _WIN64)
    LPCSTR subPath = dir.c_str();
    CHAR drivename[2 * MAX_PATH];
    CHAR path[2 * MAX_PATH];

    memset(drivename, 0, sizeof(drivename));
    memset(path, 0, sizeof(path));

    CHAR* per = NULL;
#ifdef __STDC_WANT_SECURE_LIB__
    strncpy_s(drivename, 2 * MAX_PATH, subPath, 3);
#else
    strncpy(drivename, subPath, 3);
#endif
    memcpy(path, dir.c_str(), 3);
    subPath += 3;
    while (subPath)
    {
        per = (char*)strchr(subPath, '\\');
        if (per == NULL)
        {
#ifdef __STDC_WANT_SECURE_LIB__
            strncat_s(path, 2 * MAX_PATH, subPath, strlen(subPath));
#else
            strncat(path, subPath, strlen(subPath));
#endif
            if (!IsDirExists(path))
                ::CreateDirectoryA(path, NULL);
            break;
        }
#ifdef __STDC_WANT_SECURE_LIB__
        strncat_s(path, 2 * MAX_PATH, subPath, per - subPath);
#else
        strncat(path, subPath, per - subPath);
#endif

        if (!IsDirExists(path))
            ::CreateDirectoryA(path, NULL);
#ifdef __STDC_WANT_SECURE_LIB__
        strcat_s(path, 2 * MAX_PATH, "\\");
#else
        strcat(path, "\\");
#endif
        subPath = per + 1;
    }
#else
#endif
    return true;
}

bool OSHelper::FindAllSubDir(string dir, vector<string>& subDirs)
{
    dir += "*";
    long handle;
    struct _finddata_t fileinfo = { 0 };
    handle = _findfirst(dir.c_str(), &fileinfo);
    int error = GetLastError();
    if (-1 == handle)
        return true;
    if (fileinfo.attrib & _A_SUBDIR && strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
        subDirs.push_back(fileinfo.name);
    while (!_findnext(handle, &fileinfo))
    {
        if (fileinfo.attrib & _A_SUBDIR && strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
            subDirs.push_back(fileinfo.name);
    }
    _findclose(handle);
    return true;
}

bool OSHelper::RemoveFile(string file)
{
    if (!IsFileExists(file))
        return true;

    int ret = remove(file.c_str());
    return ret == 0 ? true : false;
}
