#pragma once

#include "includes.h"

class ProcessManagement
{
public:

	explicit ProcessManagement(const std::string& procName);

	HANDLE m_hProcess;

	uintptr_t moduleBaseAddr;

	MODULEENTRY32 procModule;

	static DWORD GetProcessId(const std::string& procName);

	uintptr_t GetModuleBaseAddress(DWORD procId, const std::string& procName);

	MODULEENTRY32 GetModule(DWORD procId, const std::string& procName);

	uintptr_t FindPattern(const std::string& pattern);


	template <typename T> bool WriteMemory(uintptr_t addr, const T& data)
	{
		// I dont need bytes written rn, maybe some other time, get Write result
		uint64_t bytes_written = 0;
		DWORD oldProtect;

		VirtualProtectEx(m_hProcess, reinterpret_cast<void*>(addr), sizeof(data), PROCESS_VM_WRITE, &oldProtect);
		bool result = WriteProcessMemory(m_hProcess, reinterpret_cast<void*>(addr), &data, sizeof(T), &bytes_written);
		VirtualProtectEx(m_hProcess, reinterpret_cast<void*>(addr), sizeof(T), oldProtect, nullptr);

		return result;
	}

	template <typename T> T ReadMemory(uintptr_t addr)
	{
		T value;
		uint64_t bytesRead = 0;
		DWORD oldProtect;
		VirtualProtectEx(m_hProcess, reinterpret_cast<void*>(addr), sizeof(T), PROCESS_VM_READ, &oldProtect);
		ReadProcessMemory(m_hProcess, reinterpret_cast<void*>(addr), &value, sizeof(T), &bytesRead);
		VirtualProtectEx(m_hProcess, reinterpret_cast<void*>(addr), sizeof(T), oldProtect, nullptr);
		return value;
	}

};