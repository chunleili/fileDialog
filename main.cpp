#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#ifdef WIN32
#include <direct.h>
#define NOMINMAX
#include "windows.h"
#include <commdlg.h>
static void tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = " ")
{
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	std::string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}

static std::string normalizePath(const std::string &path)
{
	if (path.size() == 0)
		return path;
	std::string result = path;
	std::replace(result.begin(), result.end(), '\\', '/');
	std::vector<std::string> tokens;
	tokenize(result, tokens, "/");
	unsigned int index = 0;
	while (index < tokens.size())
	{
		if ((tokens[index] == "..") && (index > 0))
		{
			tokens.erase(tokens.begin() + index - 1, tokens.begin() + index + 1);
			index -= 2;
		}
		index++;
	}
	result = "";
	if (path[0] == '/')
		result = "/";
	result = result + tokens[0];
	for (unsigned int i = 1; i < tokens.size(); i++)
		result = result + "/" + tokens[i];

	return result;
}

/** Open windows file dialog.\n
 * dialogType 0 = Open file dialog\n
 * dialogType 1 = Save file dialog\n
 */
static const std::string fileDialog(int dialogType,
									const std::string &initialDir,
									const std::string &filter)
{
	std::string initDir = normalizePath(initialDir);
	std::replace(initDir.begin(), initDir.end(), '/', '\\');

	OPENFILENAME ofn; // common dialog box structure
	char fileNameBuffer[512];
	fileNameBuffer[0] = '\0';

	const std::string filterWithEscape = filter + '\0';

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = fileNameBuffer;
	ofn.nMaxFile = sizeof(fileNameBuffer);
	ofn.lpstrFilter = filterWithEscape.c_str();
	ofn.nFilterIndex = 1;
	ofn.lpstrInitialDir = (LPSTR)initDir.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if (dialogType == 0)
	{
		if (GetOpenFileName(&ofn))
			return std::string(fileNameBuffer);
	}
	else
	{
		if (GetSaveFileName(&ofn))
			return std::string(fileNameBuffer);
	}
	return "";
}
#endif

int main()
{
	std::string path = fileDialog(0, ".", "All Files (*.*)\0*.*\0");
	std::cout <<"Open file: "<< path << std::endl;
}
