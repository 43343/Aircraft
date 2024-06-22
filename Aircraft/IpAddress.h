#pragma once
#include <string>

class IpAddress
{
public:
	explicit  IpAddress();
	void set(const std::string& ipAddressString);
	std::string get() const;

private:
	std::string m_ipAddressString;
};
