
#include "iot_config.h"


static void get_string_content_value(FILE *fp, uint8_t *pszSectionName, uint8_t *pszKeyName, uint8_t *pszOutput, uint32_t iOutputLen);
static void get_complete_path(uint8_t *pszConfigFileName, uint8_t *pszWholePath);

static void get_string_content_value(FILE *fp, uint8_t *pszSectionName, uint8_t *pszKeyName, uint8_t *pszOutput, uint32_t iOutputLen)
{
    uint8_t  szSectionName[100]    = {0};
    uint8_t  szKeyName[100]        = {0};
    uint8_t  szContentLine[256]    = {0};
    uint8_t  szContentLineBak[256] = {0};
    uint32_t iContentLineLen       = 0;
    uint32_t iPositionFlag         = 0;

    if (fp == NULL || pszSectionName == NULL || pszKeyName == NULL || pszOutput == NULL)
    {
        printf("get_string_content_value: input parameter(s) is NULL!\n");
        return;
    }

    sprintf(szSectionName, "[%s]", pszSectionName);
    strcpy(szKeyName, pszKeyName);

    while (feof(fp) == 0)
    {
        memset(szContentLine, 0x00, sizeof(szContentLine));
        fgets(szContentLine, sizeof(szContentLine), fp);     

        if (szContentLine[0] == ';' || szContentLine[0] == '\r' || szContentLine[0] == '\n' || szContentLine[0] == '\0')
        {
            continue;
        }

        if (strncasecmp(szSectionName, szContentLine, strlen(szSectionName)) == 0)     
        {
            while (feof(fp) == 0)
            {
                memset(szContentLine,    0x00, sizeof(szContentLine));
                memset(szContentLineBak, 0x00, sizeof(szContentLineBak));
                fgets(szContentLine, sizeof(szContentLine), fp);    

                if (szContentLine[0] == ';')
                {
                    continue;
                }

                memcpy(szContentLineBak, szContentLine, strlen(szContentLine));

                if (strncasecmp(szKeyName, szContentLineBak, strlen(szKeyName)) == 0)     
                {
                    iContentLineLen = strlen(szContentLine);
                    for (iPositionFlag = strlen(szKeyName); iPositionFlag <= iContentLineLen; iPositionFlag ++)
                    {
                        if (szContentLine[iPositionFlag] == ' ')
                        {
                            continue;
                        }
                        if (szContentLine[iPositionFlag] == '=')
                        {
                            break;
                        }

                        iPositionFlag = iContentLineLen + 1;
                        break;
                    }

                    iPositionFlag = iPositionFlag + 1;    

                    if (iPositionFlag > iContentLineLen)
                    {
                        continue;
                    }

                    memset(szContentLine, 0x00, sizeof(szContentLine));
                    strcpy(szContentLine, szContentLineBak + iPositionFlag);


                    for (iPositionFlag = 0; iPositionFlag < strlen(szContentLine); iPositionFlag ++)
                    {
                        if (szContentLine[iPositionFlag] == '\r' || szContentLine[iPositionFlag] == '\n' || szContentLine[iPositionFlag] == '\0')
                        {
                            szContentLine[iPositionFlag] = '\0';
                            break;
                        }
                    }

    
                    strncpy(pszOutput, szContentLine, iOutputLen-1);
                    break;
                }
                else if (szContentLine[0] == '[')
                {
                    break;
                }
            }
            break;
        }
    }
}


void get_config_svalue(uint8_t *pszSectionName, uint8_t *pszKeyName, uint8_t *pDefaultVal, uint8_t *pszOutput, uint32_t iOutputLen, uint8_t *pszConfigFileName)
{
    FILE  *fp                    = NULL;
    uint8_t  szWholePath[256]      = {0};

    if (pszSectionName == NULL || pszKeyName == NULL || pszOutput == NULL || pszConfigFileName == NULL)
    {
        printf("GetConfigFileStringValue: input parameter(s) is NULL!\n");
        return;
    }

    if (pDefaultVal == NULL)
    {
        strcpy(pszOutput, "");
    }
    else
    {
        strcpy(pszOutput, pDefaultVal);
    }

    get_complete_path(pszConfigFileName, szWholePath);
    fp = fopen(szWholePath, "r");
    if (fp == NULL)
    {
        printf("GetConfigFileStringValue: open %s failed!\n", szWholePath);
        return;
    }

    get_string_content_value(fp, pszSectionName, pszKeyName, pszOutput, iOutputLen);

    fclose(fp);
    fp = NULL;
}


int get_config_ivalue(uint8_t *pszSectionName, uint8_t *pszKeyName, uint32_t iDefaultVal, uint8_t *pszConfigFileName)
{
    uint8_t  szGetValue[512] = {0};
    int  iGetValue       = 0;

    if (pszSectionName == NULL || pszKeyName == NULL || pszConfigFileName == NULL)
    {
        printf("GetConfigFileIntValue: input parameter(s) is NULL!\n");
        return -1;
    }

    get_config_svalue(pszSectionName, pszKeyName, NULL, szGetValue, 512-1, pszConfigFileName);   

    if (szGetValue[0] == '\0' || szGetValue[0] == ';') 
    {
        iGetValue = iDefaultVal;
    }
    else
    {
        iGetValue = atoi(szGetValue);
    }

    return iGetValue;
}

static void get_complete_path(uint8_t *pszConfigFileName, uint8_t *pszWholePath)
{
    uint8_t *pszHomePath      = NULL;
    uint8_t  szWholePath[256] = {0};


    if (pszConfigFileName == NULL || pszWholePath == NULL)
    {
        return;
    }

    pszHomePath = (uint8_t *)getenv("HOME");    
    if (pszHomePath == NULL)
    {
        return;
    }


    snprintf(szWholePath, sizeof(szWholePath)-1, "./%s", pszConfigFileName);

    strncpy(pszWholePath, szWholePath, strlen(szWholePath));
}

