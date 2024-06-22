#include "IpAddress.h"


IpAddress::IpAddress()
{
}

void IpAddress::set(const std::string& ipAddressString)
{
	m_ipAddressString = ipAddressString;
}

std::string IpAddress::get() const {
   return m_ipAddressString;
}
