#include <iostream>
#include <string>
#include <vector>
#include "tinyxml.h"
#include <windows.h>
#include <thread>

// Declare actionBoutton struct type
struct actionBoutton {
	std::string id;
	std::string actionToPerfomPress;
	std::string argPress;
	std::string actionToPerfomHold;
	std::string argHold;
};


bool isXmlFileValid(const std::string& filePath)
{
	TiXmlDocument xmlDoc;
	if (!xmlDoc.LoadFile(filePath.c_str()))
	{
		std::cout << "Failed to parse XML file: " << filePath << std::endl;
		std::cout << "Error description: " << xmlDoc.ErrorDesc() << std::endl;
		return false;
	}

	return true;
}


void ReadConfig(const std::string& path, std::vector<actionBoutton>& buttonsAction) {
	if (isXmlFileValid(path.c_str()))
	{
		TiXmlDocument xmlDoc(path.c_str());
		if (xmlDoc.LoadFile())
		{
			// XML file loaded successfully
			TiXmlElement* rootElement = xmlDoc.RootElement();
			if (rootElement)
			{
				//Read XML files and add actions
				TiXmlElement* child = rootElement->FirstChildElement("node");
				while (child) {
					struct actionBoutton temp;
					temp.id = child->Attribute("id");
					temp.actionToPerfomPress = child->Attribute("actionPress");
					temp.argPress = child->Attribute("argPress");
					temp.actionToPerfomHold = child->Attribute("actionHold");
					temp.argHold = child->Attribute("argHold");
					buttonsAction.push_back(temp);
					child = child->NextSiblingElement();
				}
			}
		}
		std::cerr << "Syntax error on config file \n";

	}
	else
	{
		std::cerr << "Error reading on Config file \n";

	}
}

//arg press : 1 for press, 0 for hold
std::string GetAction(const std::string& id, const std::vector<actionBoutton>& buttonsAction,bool press) {

	for (int i = 0; i < buttonsAction.size(); i++)
	{
		if (id == buttonsAction[i].id)
		{
			if (press) {
			return buttonsAction[i].actionToPerfomPress;
			}
			else return buttonsAction[i].actionToPerfomHold;
		}
	}
	return "None";
}


std::string GetArg(const std::string& id, const std::vector<actionBoutton>& buttonsAction, bool press) {

	for (int i = 0; i < buttonsAction.size(); i++)
	{
		if (id == buttonsAction[i].id)
		{
			if (press) {
				return buttonsAction[i].argPress;
			}
			else return buttonsAction[i].argHold;
			
		}
	}
	return "None";
}


void StartScript(const std::string path)
{
	// Extraire le répertoire du script
	std::string::size_type pos = path.find_last_of("\\/");
	std::string scriptDir = path.substr(0, pos);

	// Sauvegarder le répertoire courant
	char originalDir[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, originalDir);

	// Changer vers le répertoire du script
	SetCurrentDirectoryA(scriptDir.c_str());


	STARTUPINFOA si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	std::string commandstd = "cmd.exe /c " + path;
	// Full command to run the batch file
	LPCSTR command = commandstd.c_str();


	// Create the process
	if (CreateProcessA(
		NULL,                // No module name (use command line)
		(LPSTR)command,      // Command line
		NULL,                // Process handle not inheritable
		NULL,                // Thread handle not inheritable
		FALSE,               // Set handle inheritance to FALSE
		CREATE_NEW_CONSOLE,            // 0 for no console
		NULL,                // Use parent's environment block
		NULL,                // Use parent's starting directory 
		&si,                 // Pointer to STARTUPINFO structure
		&pi)                 // Pointer to PROCESS_INFORMATION structure
		)
	{
		// Wait until child process exits
		WaitForSingleObject(pi.hProcess, INFINITE);

		// Get exit code
		DWORD exitCode;
		GetExitCodeProcess(pi.hProcess, &exitCode);
		std::cout << "Batch file exited with code: " << exitCode << std::endl;

		// Close process and thread handles
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		SetCurrentDirectoryA(originalDir);

	}
	else {
		std::cerr << "CreateProcess failed (" << GetLastError() << ").\n";
	}
}


void ExecuteAction(const std::string& id, const std::vector<actionBoutton>& buttonsAction)
{
	//Read Acion and do it
	size_t delimiterPos = id.find('/');
	if (delimiterPos != std::string::npos) {
		std::string firstPart = id.substr(0, delimiterPos);
		std::string secondPart = id.substr(delimiterPos + 1);
		bool press = false;
		if (secondPart == "Press") press = true;

		std::string actionToPerform = GetAction(firstPart, buttonsAction, press);

		if (actionToPerform == "Start Script")
		{
			StartScript(GetArg(firstPart, buttonsAction, press));
		}
	}

}


void Loop(const std::vector<actionBoutton>& buttonsAction)
{
	HANDLE hSerial;
	DCB dcbSerialParams = { 0 };
	COMMTIMEOUTS timeouts = { 0 };
	std::vector<std::string> ports;
	ports.push_back("\\\\.\\COM0");
	ports.push_back("\\\\.\\COM1");
	ports.push_back("\\\\.\\COM2");
	ports.push_back("\\\\.\\COM3");
	ports.push_back("\\\\.\\COM4");
	ports.push_back("\\\\.\\COM5");
	ports.push_back("\\\\.\\COM6");
	ports.push_back("\\\\.\\COM7");
	ports.push_back("\\\\.\\COM8");
	ports.push_back("\\\\.\\COM9");

	//char portName[] = "\\\\.\\COM5";  

	while (true) {
		// Ouvre le port série
		for (int i = 0; i < ports.size(); i++) {
			//open serial port
			hSerial = CreateFileA(ports[i].c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
			if (hSerial == INVALID_HANDLE_VALUE) {
				std::cerr << "Error connectting to " << ports[i].c_str() << "\n";
				continue;
			}

			dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
			if (!GetCommState(hSerial, &dcbSerialParams)) {
				std::cerr << "Error GetCommState\n";
				CloseHandle(hSerial);
				continue;
			}

			dcbSerialParams.BaudRate = CBR_9600;
			dcbSerialParams.ByteSize = 8;
			dcbSerialParams.StopBits = ONESTOPBIT;
			dcbSerialParams.Parity = NOPARITY;

			if (!SetCommState(hSerial, &dcbSerialParams)) {
				std::cerr << "Error SetCommState\n";
				CloseHandle(hSerial);
				continue;
			}

			// Timeout
			timeouts.ReadIntervalTimeout = 50;
			timeouts.ReadTotalTimeoutConstant = 50;
			timeouts.ReadTotalTimeoutMultiplier = 10;
			SetCommTimeouts(hSerial, &timeouts);


			char buffer[128];
			DWORD bytesRead;
			bool noError = true;
			std::cout << "Connected to " << ports[i].c_str() << ". \n";
			// Loop reading serial
			while (noError) {

				if (ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
					if (bytesRead > 0) {
						buffer[bytesRead] = '\0';  // Fin de chaîne
						std::cout << "Received: " << buffer << ". ";
						std::string id(buffer);
						std::thread worker(ExecuteAction,id, buttonsAction);  // Launch thread
						worker.detach();  
					}
				}
				else {
					std::cerr << "Error ReadFile (message received over serial \n";
					noError = false;
				}
				Sleep(100);
			}
		}
		Sleep(2000);
	}
	CloseHandle(hSerial);
}


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Missing parameter: <exe> [in]config-file-path" << std::endl;
		return 1;
	}
	std::string configFilePath = argv[1];
	std::vector<actionBoutton> buttonsAction;

	ReadConfig(configFilePath, buttonsAction);
	Loop(buttonsAction);

	return 0;
}