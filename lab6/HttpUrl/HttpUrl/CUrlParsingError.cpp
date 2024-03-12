#include "CUrlParsingError.h"

const std::string INVALID_URL = "Invalid url.";
const std::string INVALID_PORT = "Invalid port. It must be between 1 and 65565.";
const std::string INVALID_PROTOCOL = "Invalid protocol. It must be HTTP or HTTPS.";
const std::string INVALID_DOCUMENT = "Invalid document. Domain must only contain english letters, digits, '-', '.'.";
const std::string INVALID_DOMAIN = "Invalid domain. Document mustn't contain spaces.";

CUrlParsingError::CUrlParsingError(std::string const& message)
	: invalid_argument(message)
{
}

CUrlParsingError CUrlParsingError::InvalidUrl()
{
	return CUrlParsingError(INVALID_URL);
}

CUrlParsingError CUrlParsingError::InvalidPort()
{
	return CUrlParsingError(INVALID_PORT);
}

CUrlParsingError CUrlParsingError::InvalidProtocol()
{
	return CUrlParsingError(INVALID_PROTOCOL);
}

CUrlParsingError CUrlParsingError::InvalidDocument()
{
	return CUrlParsingError(INVALID_DOCUMENT);
}

CUrlParsingError CUrlParsingError::InvalidDomain()
{
	return CUrlParsingError(INVALID_DOMAIN);
}
