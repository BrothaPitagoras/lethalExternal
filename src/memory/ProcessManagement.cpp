#include <memory/ProcessManagement.hpp>

DWORD ProcessManagement::GetProcessId(const std::string& procName) {
	DWORD procId = 0;

	HANDLE handleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	// error check handle
	if (handleSnapshot != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);
		// get first process of snapshot into pe32
		if (Process32First(handleSnapshot, &pe32))
		{
			do {
				//verify if the process name is equal to given process name
				if (procName.compare(pe32.szExeFile) == 0) {
					procId = pe32.th32ProcessID;
					break;
				}
				// loop to the next process inside snapshot
			} while (Process32Next(handleSnapshot, &pe32));
		}
	}
	// cleanup close snapshot's handle
	CloseHandle(handleSnapshot);
	return procId;
}

uintptr_t ProcessManagement::GetModuleBaseAddress(DWORD dwProcID, const std::string& szModuleName)
{
	uintptr_t dwModuleBaseAddress = 0;
	HANDLE hndlSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcID);
	if (hndlSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 ModuleEntry32;
		ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hndlSnapshot, &ModuleEntry32))
		{
			do
			{
				if (szModuleName.compare(ModuleEntry32.szModule) == 0)
				{
					dwModuleBaseAddress = reinterpret_cast<uintptr_t>(ModuleEntry32.modBaseAddr);
					break;
				}
			} while (Module32Next(hndlSnapshot, &ModuleEntry32));
		}
		CloseHandle(hndlSnapshot);
	}


	return dwModuleBaseAddress;
}

MODULEENTRY32 ProcessManagement::GetModule(DWORD dwProcID, const std::string& szModuleName)
{
	MODULEENTRY32 moduleEntryResult = { -1 };
	HANDLE hndlSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcID);
	if (hndlSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 ModuleEntry32;
		ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hndlSnapshot, &ModuleEntry32))
		{
			do
			{
				if (szModuleName.compare(ModuleEntry32.szModule) == 0)
				{
					moduleEntryResult = ModuleEntry32;
					break;
				}
			} while (Module32Next(hndlSnapshot, &ModuleEntry32));
		}
		CloseHandle(hndlSnapshot);
	}
	return moduleEntryResult;
}

uintptr_t ScanChunk(std::vector<uint8_t> pattern, uint8_t* buffer, unsigned int size) {
	if (size < pattern.size())
	{
		return 0;
	}
	for (unsigned int offset = 0; offset < size - pattern.size(); offset++)
	{
		bool match = true;
		for (unsigned int i = 0; i < pattern.size(); i++)
		{
			if (pattern[i] != '?' && pattern[i] != *(buffer + offset + i)) {
				match = false;
				break;
			}
		}

		if (match)
		{
			// offset of pattern starting from buffer (still need buffer offset for final offset)
			return offset;
		}
	}
	// pattern not found
	return 0;
}

std::vector<uint8_t> IDAPatternToVector(const std::string& idaPattern) {
	std::vector<uint8_t> pattern;
	std::istringstream iss(idaPattern);
	std::string byteStr;

	while (iss >> byteStr) {
		if (byteStr == "??") {
			pattern.push_back('?');
		}
		else {
			auto byte = static_cast<uint8_t>(std::stoul(byteStr, nullptr, 16));
			pattern.push_back(byte);
		}
	}

	return pattern;
}

uintptr_t ProcessManagement::FindPattern(const std::string& pattern) {

	uintptr_t current = moduleBaseAddr;
	uintptr_t end = current + procModule.modBaseSize;


	while (current < end)
	{
		uint8_t buffer[4096];

		SIZE_T bytesRead = 0;
		DWORD oldProtect;

		VirtualProtectEx(m_hProcess, reinterpret_cast<void*>(current), sizeof(buffer), PROCESS_VM_READ, &oldProtect);
		ReadProcessMemory(m_hProcess, reinterpret_cast<void*>(current), &buffer, sizeof(buffer), &bytesRead);
		VirtualProtectEx(m_hProcess, reinterpret_cast<void*>(current), sizeof(buffer), oldProtect, nullptr);

		if (bytesRead == 0)
		{
			return 0;
		}

		uintptr_t offsetFromBuffer = ScanChunk(IDAPatternToVector(pattern), (uint8_t*)&buffer, bytesRead);

		if (offsetFromBuffer != 0)
		{
			return (current + offsetFromBuffer);
		}
		else {
			current = current + bytesRead;
		}
	}
	return 0;
}



ProcessManagement::ProcessManagement(const std::string& procName) {
	DWORD pid = GetProcessId(procName);
	this->moduleBaseAddr = GetModuleBaseAddress(pid, procName);
	this->procModule = GetModule(pid, procName);
	this->m_hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
}