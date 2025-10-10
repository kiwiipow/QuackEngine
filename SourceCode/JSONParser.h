#include <nlohmann/json.hpp>

class JSONParser
{
private:
	const char* filePath = "filepath";
public:
	JSONParser();
	~JSONParser();

	bool ReadFile();
	bool WriteFile();

	void GetData();

};