#pragma once

bool InvalidCDKey(const char* a1)
{
	char v1;
	bool result;
	char v3;
	//char v4;
	//char v5;

	v1 = a1[16];
	result = false;

	if (!v1 || (*a1 & 7) != 1 && (!v1 || (*a1 & 7) != 2))						// || !sub_9FDC80("assault.dat", v5, v4, 0)
	{																			// should be automatically valid for soviet assault
		if ((v3 = a1[16]) == 0 || (*a1 & 7) != 3 && (!v3 || (*a1 & 7) != 4))	// || sub_9FDC80("assault.dat", v4, v5, 0)
			result = true;
	}

	return result;
}

bool ValidateCDKey(const char* Key)
{
	// eliminates non soviet assault keys (i think), not finished
	//if (InvalidCDKey(Key))
	//	return false;

	MMG_CdKey::Validator validator;
	validator.SetKey(Key);

	if (!validator.myIsChecksumCorrect)
		return false;

	//printf("%u", validator.GetSequenceNumber());

	return true;
}

void GenerateRandomKey(const char* dst)
{
	char key[26];
	memset(key, 0, sizeof(key));

	const char* LocCdKeyAlphabet = "ABCDEFGHIJKLMNOPRSTUVWXY23456789";
	MC_MTwister twist;

	int count = 0;
	while (count < 10000)
	{
		// pick a random letter from the alphabet
		for (int i = 0; i < 20; i++)
			key[i] = LocCdKeyAlphabet[twist.Random(0, strlen(LocCdKeyAlphabet) - 1)];

		if (ValidateCDKey(key))
		{
			// format the key for use
			//char wholekey[1024] = "";
			//sprintf(wholekey, "%s-%s-%s-%s-%s\n", key, key+4, key+8, key+12, key+16);
			//OutputDebugStringA(wholekey);

			memcpy((char*)dst, key, 4);
			memcpy((char*)dst + 5, key + 4, 4);
			memcpy((char*)dst + 10, key + 8, 4);
			memcpy((char*)dst + 15, key + 12, 4);
			memcpy((char*)dst + 20, key + 16, 4);

			break;
		}

		count++;
	}
}