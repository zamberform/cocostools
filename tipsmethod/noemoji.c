std::string check_input_str(const std::string& str )
{
	if (!str.compare(""))
	{
		return "";
	}
	unsigned unicode;
	std::string ret;
	for (int i = 0; i < str.size(); i++) 
	{
		char codePoint = str[i];
		if (codePoint&0x80) 
		{
			switch ((unsigned)(codePoint & 0xf0)) 
			{
				case 0xf0:
				//0x9f -> emoji
				if ((unsigned)(str[i + 1] & 0x9f) != 0x9f)
				{
					for (int j = 0; j < 4; ++j)
					{
						ret.push_back(str[i + j]);
                        char a = str[i + j];
					}
					i+=3;
				}
				break;
				
				case 0xe0:
				for (int j = 0; j < 3; ++j)
				{
				ret.push_back(str[i + j]);
				}
				i+=2;
				break;


				case 0xc0:
				for (int j = 0; j < 2; ++j)
				{
				ret.push_back(str[i + j]);
				}
				i+=1;
				break;
				default:
				CCAssert(0, "");
				break;
			}
		}
	}
	return ret;
}