#pragma once
#include <string>

class IpAddress
{
public:
	explicit  IpAddress();
	void set(std::string& ipAddressString);
	std::string IpAddress::get() const
	{
		return m_ipAddressString;
	}

private:
	std::string m_ipAddressString;
};